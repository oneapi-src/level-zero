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
 * Copyright (C) 2019-2023 Intel Corporation
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
    virtual ${x}_result_t ${th.make_func_name(n, tags, obj)}( \
%for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"]):
${line} \
%endfor
) {return ZE_RESULT_SUCCESS;}
    %endfor
    virtual ~${N}ValidationEntryPoints() {}
};
}