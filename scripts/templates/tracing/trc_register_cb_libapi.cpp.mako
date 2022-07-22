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
 * @file ${name}.cpp
 *
 */

#include "ze_lib.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "layers/zel_tracing_register_cb.h"
#include "${x}_api.h"

extern "C" { 

/// APIs to register callbacks for each core API
%for s in specs:
%for obj in th.filter_items(s['objects'], 'type', 'function'):

${X}_APIEXPORT ${x}_result_t ${X}_APICALL
${th.make_tracing_func_name(n, tags, obj)}(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ${th.make_pfncb_type(n, tags, obj)} ${th.make_pfncb_name(n, tags, obj)}
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ${th.make_pfncb_type(n, tags, obj)} ${th.make_pfncb_name(n, tags, obj)}
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "${th.make_tracing_func_name(n, tags, obj)}") );

    if(func)
        return func(hTracer, callback_type, ${th.make_pfncb_name(n, tags, obj)});

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}

%endfor
%endfor #s in specs:

} //Extern C