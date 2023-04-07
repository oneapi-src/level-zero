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
 * See handle_lifetime.h.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */

#pragma once
#include "${n}_entry_points.h"


namespace validation_layer
{

    class ${N}HandleLifetimeValidation : public ${N}ValidationEntryPoints {
    public:
    %for obj in th.extract_objs(specs, r"function"):
        %if not th.obj_traits.is_function_with_input_handles(obj):
        <% continue %>
        %endif
        ${x}_result_t ${th.make_func_name(n, tags, obj)} ( \
%for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"]):
${line} \
%endfor
) override;
    %endfor
    };

}
