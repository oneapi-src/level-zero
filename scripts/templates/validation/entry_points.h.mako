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
 * Copyright (C) 2019-2024 Intel Corporation
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
    virtual ${x}_result_t ${th.make_func_name(n, tags, obj)}Prologue( \
%for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"]):
${line} \
%endfor
) {return ZE_RESULT_SUCCESS;}
    virtual ${x}_result_t ${th.make_func_name(n, tags, obj)}Epilogue( \
%for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"]):
${line} \
%endfor
, ze_result_t result) {return ZE_RESULT_SUCCESS;}
    %endfor
    virtual ~${N}ValidationEntryPoints() {}
};
}