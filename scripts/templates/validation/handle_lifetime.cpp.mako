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
 * See handle_lifetime.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#include "${x}_validation_layer.h"
#include "${x}_handle_lifetime.h"

namespace validation_layer
{
    %for obj in th.extract_objs(specs, r"function"):
    ## don't genrate function if it has no handles as parameters
    %if th.obj_traits.is_function_with_input_handles(obj):
    ${x}_result_t
    ${N}HandleLifetimeValidation::${th.make_func_name(n, tags, obj)}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
        )
    { 
        <% func_name = th.make_func_name(n, tags, obj)
        %>
        %if re.match(r"\w+Destroy$", func_name):
        %for i, item in enumerate(th.get_loader_prologue(n, tags, obj, meta)):
        if (${item['name']} && context.handleLifetime->isHandleValid( ${item['name']} )){
            if (context.handleLifetime->hasDependents( ${item['name']} )){
                return ${X}_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( ${item['name']});
            context.handleLifetime->removeHandle( ${item['name']} );
        } else if (!context.handleLifetime->isHandleValid( ${item['name']} )) {
            return ${X}_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        %endfor
        %else: ## Not Destroy
        %for i, item in enumerate(th.get_loader_prologue(n, tags, obj, meta)):
        %if not 'range' in item:
        ## if item is optional, check if it is not null before checking if it is valid
        %if item['optional']:
        if (${item['name']} && !context.handleLifetime->isHandleValid( ${item['name']} )){
                return ${X}_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        %else:
        if ( !context.handleLifetime->isHandleValid( ${item['name']} )){
                return ${X}_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        %endif ## if item['optional']
        %if re.match(r"\w+CommandListAppend\w+$", func_name) and (0 == i) : ## i = 0, first parameter is command list
        if (!context.handleLifetime->isOpen( ${item['name']} )){
            return ${X}_RESULT_ERROR_INVALID_ARGUMENT;
        }
        %endif
        %if re.match(r"\w+CommandListClose$", func_name):
        context.handleLifetime->close( ${item['name']} );
        %endif
        %if re.match(r"\w+CommandListReset$", func_name):
        context.handleLifetime->reset( ${item['name']} );
        %endif
        %else: ## if 'range' in item
        for (size_t i = ${item['range'][0]}; ( nullptr != ${item['name']}) && (i < ${item['range'][1]}); ++i){
            if (!context.handleLifetime->isHandleValid( ${item['name']}[i] )){
                return ${X}_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        %if re.match(r"\w+ExecuteCommandLists$", func_name) and (1 == i):
        for (size_t i = ${item['range'][0]}; ( nullptr != ${item['name']}) && (i < ${item['range'][1]}); ++i){
            if (context.handleLifetime->isOpen( ${item['name']}[i] )){
                return ${X}_RESULT_ERROR_INVALID_ARGUMENT;
            }
        }
        %endif
        %endif ## if 'range' in item
        %endfor ## for i, item in enumerate(th.get_loader_prologue(n, tags, obj, meta))
        %endif ## if re.match(r"\w+Destroy$", func_name)
        return ${X}_RESULT_SUCCESS;
    }
    %endif
    %endfor
}