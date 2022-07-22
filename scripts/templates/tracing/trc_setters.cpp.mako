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

#include "tracing.h"
#include "ze_tracing_layer.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "layers/zel_tracing_register_cb.h"
#include "${x}_api.h"

extern "C" { 

/// APIs to register callbacks for each core API
%for s in specs:
%for obj in th.filter_items(s['objects'], 'type', 'function'):

${X}_DLLEXPORT ${x}_result_t ${X}_APICALL
${th.make_tracing_func_name(n, tags, obj)}(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ${th.make_pfncb_type(n, tags, obj)} ${th.make_pfncb_name(n, tags, obj)}
    ) {

    ze_result_t result;
    auto& cbs = tracing_layer::APITracer::fromHandle(hTracer)->getProEpilogues(callback_type, result);
    if (result == ZE_RESULT_SUCCESS)
        cbs.${th.get_callback_table_name(n, tags, obj)}.${th.make_pfncb_name(n, tags, obj)} = ${th.make_pfncb_name(n, tags, obj)};

    return result;
}

%endfor
%endfor #s in specs:


} //extern C