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
 * See param.cpp.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#include "${x}_validation_layer.h"
#include "param_validation.h"

namespace validation_layer
{
    %if 'ze' == n:
    class parameterValidationChecker parameterChecker;

    parameterValidationChecker::parameterValidationChecker() {
        enableParameterValidation = getenv_tobool( "ZE_ENABLE_PARAMETER_VALIDATION" );
        if(enableParameterValidation) {
            ZEParameterValidation *zeChecker = new ZEParameterValidation;
            ZESParameterValidation *zesChecker = new ZESParameterValidation;
            ZETParameterValidation *zetChecker = new ZETParameterValidation;
            ZERParameterValidation *zerChecker = new ZERParameterValidation;
            parameterChecker.zeValidation = zeChecker;
            parameterChecker.zetValidation = zetChecker;
            parameterChecker.zesValidation = zesChecker;
            parameterChecker.zerValidation = zerChecker;
            validation_layer::context.getInstance().validationHandlers.push_back(&parameterChecker);
        }
    }

    parameterValidationChecker::~parameterValidationChecker() {
        if(enableParameterValidation) {
            delete parameterChecker.zeValidation;
            delete parameterChecker.zetValidation;
            delete parameterChecker.zesValidation;
            delete parameterChecker.zerValidation;
        }
    }
    %endif
    %for obj in th.extract_objs(specs, r"function"):

    ${x}_result_t
    ${N}ParameterValidation::${th.make_func_name(n, tags, obj)}Prologue(
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