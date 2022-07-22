<%
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.h
 *
 */
#ifndef ${name}_H
#define ${name}_H
#if defined(__cplusplus)
#pragma once
#endif

#include "../${x}_api.h"


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of tracer object
typedef struct _zel_tracer_handle_t *zel_tracer_handle_t;

/// Callback definitions for all API released in LevelZero spec 1.1 or newer
/// Callbacks for APIs included in spec 1.0 are contained in ze_api.helper

%for tbl in th.get_new_pfncbtables(specs, meta, n, tags):
%for obj in tbl['functions']:
///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for ${th.make_func_name(n, tags, obj)}
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _${th.make_pfncb_param_type(n, tags, obj)}
{
    %for line in th.make_param_lines(n, tags, obj, format=["type*", "name"]):
    ${line};
    %endfor
} ${th.make_pfncb_param_type(n, tags, obj)};


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for ${th.make_func_name(n, tags, obj)}
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (${X}_APICALL *${th.make_pfncb_type(n, tags, obj)})(
    ${th.make_pfncb_param_type(n, tags, obj)}* params,
    ${x}_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

%endfor
%endfor

typedef enum _zel_tracer_reg_t
{
    ZEL_REGISTER_PROLOGUE = 0,
    ZEL_REGISTER_EPILOGUE = 1     
} zel_tracer_reg_t;

/// APIs to register callbacks for each core API
%for s in specs:
%for obj in th.filter_items(s['objects'], 'type', 'function'):

${X}_APIEXPORT ${x}_result_t ${X}_APICALL
${th.make_tracing_func_name(n, tags, obj)}(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ${th.make_pfncb_type(n, tags, obj)} ${th.make_pfncb_name(n, tags, obj)}
    );

%endfor
%endfor #s in specs:

${X}_APIEXPORT ${x}_result_t ${X}_APICALL
zelTracerResetAllCallbacks(zel_tracer_handle_t hTracer);


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // ${name}_H
