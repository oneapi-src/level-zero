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
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#include "${x}_validation_layer.h"

namespace validation_layer
{
    static ze_result_t logAndPropagateResult(const char* fname, ze_result_t result) {
        if (result != ${X}_RESULT_SUCCESS) {
            context.logger->log_trace("Error (" + loader::to_string(result) + ") in " + std::string(fname));
        }
        return result;
    }

    %for obj in th.extract_objs(specs, r"function"):
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for ${th.make_func_name(n, tags, obj)}
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    __${x}dlllocal ${x}_result_t ${X}_APICALL
    ${th.make_func_name(n, tags, obj)}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
        )
    {
        context.logger->log_trace("${th.make_func_name(n, tags, obj)}(${", ".join(th.make_param_lines(n, tags, obj, format=["name", "local"]))})");

        auto ${th.make_pfn_name(n, tags, obj)} = context.${n}DdiTable.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};

        if( nullptr == ${th.make_pfn_name(n, tags, obj)} )
            return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->${n}Validation->${th.make_func_name(n, tags, obj)}Prologue( \
% for line in th.make_param_lines(n, tags, obj, format=['name','delim']):
${line} \
%endfor
);
            if(result!=${X}_RESULT_SUCCESS) return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        <% 
        func_name = th.make_func_name(n, tags, obj)
        generate_post_call = re.match(r"\w+Create\w*$|\w+Get$|\w+Get\w*Exp$|\w+GetIpcHandle$|\w+GetSubDevices$", func_name)
        %>
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->${n}HandleLifetime.${th.make_func_name(n, tags, obj)}Prologue( \
% for line in th.make_param_lines(n, tags, obj, format=['name','delim']):
${line} \
%endfor
);
            if(result!=${X}_RESULT_SUCCESS) return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", result);
        }

        auto driver_result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->${n}Validation->${th.make_func_name(n, tags, obj)}Epilogue( \
% for line in th.make_param_lines(n, tags, obj, format=['name','delim']):
${line} \
%endfor
,driver_result);
            if(result!=${X}_RESULT_SUCCESS) return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", result);
        }

        %if generate_post_call:

        if( driver_result == ${X}_RESULT_SUCCESS && context.enableHandleLifetime ){
            ## Add 'Created' handles/objects to dependent maps
            <% lines = th.make_param_lines(n, tags, obj, format=['name','delim'])
            %>
            %for i, item in enumerate(th.get_loader_epilogue(n, tags, obj, meta)):
            %if 'range' in item:
            for (size_t i = ${item['range'][0]}; ( nullptr != ${item['name']}) && (i < ${item['range'][1]}); ++i){
                if (${item['name']}[i]){
                    context.handleLifetime->addHandle( ${item['name']}[i] );
                    %if th.type_traits.is_handle(item['type']):
                    context.handleLifetime->addDependent( ${lines[0]} ${item['name']}[i] );
                    %endif
                }
            }
            %else:
            if (${item['name']}){
                %if re.match(r"\w+Immediate$", func_name):
                context.handleLifetime->addHandle( *${item['name']} , false);
                %else:
                context.handleLifetime->addHandle( *${item['name']} );
                %if th.type_traits.is_handle(item['type']):
                context.handleLifetime->addDependent( ${lines[0]} *${item['name']} );
                %endif

                %endif
            }
            %endif
            %endfor
        }
        %endif
        return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", driver_result);
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endfor
} // namespace validation_layer

#if defined(__cplusplus)
extern "C" {
#endif

%for tbl in th.get_pfntables(specs, meta, n, tags):
///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ${tbl['name']} table
///        with current process' addresses
///
/// @returns
///     - ::${X}_RESULT_SUCCESS
///     - ::${X}_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::${X}_RESULT_ERROR_UNSUPPORTED_VERSION
${X}_DLLEXPORT ${x}_result_t ${X}_APICALL
${tbl['export']['name']}(
    %for line in th.make_param_lines(n, tags, tbl['export']):
    ${line}
    %endfor
    )
{
    auto& dditable = validation_layer::context.${n}DdiTable.${tbl['name']};

    if( nullptr == pDdiTable )
        return ${X}_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for obj in tbl['functions']:
    if (version >= ${th.get_version(obj)}) {
    %if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
    %endif
        dditable.${th.append_ws(th.make_pfn_name(n, tags, obj), 43)} = pDdiTable->${th.make_pfn_name(n, tags, obj)};
        pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 41)} = validation_layer::${th.make_func_name(n, tags, obj)};
    %if 'condition' in obj:
#else
        dditable.${th.append_ws(th.make_pfn_name(n, tags, obj), 43)} = nullptr;
        pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 41)} = nullptr;
#endif
    %endif
    }
    %endfor
    return result;
}

%endfor
#if defined(__cplusplus)
};
#endif
