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
 * See param.h.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */

#pragma once
#include "${x}_validation_layer.h"
#include "${n}_entry_points.h"


namespace validation_layer
{

    class ${N}ParameterValidation : public ${N}ValidationEntryPoints {
    public:
    %for obj in th.extract_objs(specs, r"function"):
        ${x}_result_t ${th.make_func_name(n, tags, obj)}Prologue( \
%for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"]):
${line} \
%endfor
) override;
    %endfor
    };
}