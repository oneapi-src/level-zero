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
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#include "${x}_validation_layer.h"
#include "${x}_parameter_validation.h"

namespace validation_layer
{
    %for obj in th.extract_objs(specs, r"function"):

    ${x}_result_t
    ${N}ParameterValidation::${th.make_func_name(n, tags, obj)}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
        )
    {
        %for key, values in th.make_param_checks(n, tags, obj, meta=meta).items():
        %for val in values:
        if( ${val} )
            return ${key};

        %endfor
        %endfor
<%
    descs = th.get_func_descs(n, tags, obj)
%>\
        %if len(descs) == 0:
        return ${X}_RESULT_SUCCESS;
        %elif len(descs) == 1:
        return ParameterValidation::validateExtensions(${descs[0]});
        %else:
        auto retVal = ${X}_RESULT_SUCCESS;
        %for i, desc in enumerate(descs):
        retVal = ParameterValidation::validateExtensions(${desc});
        %if i < len(descs)-1:
        if(retVal)
            return retVal;
        %endif
        %endfor
        return retVal;
        %endif
    }

    %endfor
}