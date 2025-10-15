<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 * ***THIS FILE IS GENERATED. ***
 * See entry_points.h.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#pragma once
#include "${n}_api.h"

namespace validation_layer
{

class ${N}ValidationEntryPoints {
public:
    %for obj in th.extract_objs(specs, r"function"):
    <%
    param_lines = [line for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"])]
    is_void_params = len(param_lines) == 1 and "void" in param_lines[0]
    %>virtual ${x}_result_t ${th.make_func_name(n, tags, obj)}Prologue( \
%for line in param_lines:
${line} \
%endfor
) {return ZE_RESULT_SUCCESS;}
    virtual ${x}_result_t ${th.make_func_name(n, tags, obj)}Epilogue( \
%if not is_void_params:
%for line in param_lines:
${line} \
%endfor
, ${obj['return_type']} result) {return ZE_RESULT_SUCCESS;}
%else:
${obj['return_type']} result ) {return ZE_RESULT_SUCCESS;}
%endif
    %endfor
%if n == 'ze':
    // Experimental Intel extension for counter-based events
    virtual ze_result_t zexCounterBasedEventCreate2Prologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* desc, ze_event_handle_t* phEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zexCounterBasedEventCreate2Epilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* desc, ze_event_handle_t* phEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
%endif
    virtual ~${N}ValidationEntryPoints() {}
};
}