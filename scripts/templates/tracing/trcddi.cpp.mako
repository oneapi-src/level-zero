<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2020-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 *
 */

#include <iostream>
#include "${x}_tracing_layer.h"

namespace tracing_layer
{
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
        auto ${th.make_pfn_name(n, tags, obj)} = context.${n}DdiTable.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};

        if( nullptr == ${th.make_pfn_name(n, tags, obj)})
            return ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;

        ZE_HANDLE_TRACER_RECURSION(context.${n}DdiTable.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}, ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))});

        // capture parameters
        ${th.make_pfncb_param_type(n, tags, obj)} tracerParams = {
            &${",\n            &".join(th.make_param_lines(n, tags, obj, format=["name"]))}
        };

        tracing_layer::APITracerCallbackDataImp<${th.make_pfncb_type(n, tags, obj)}> apiCallbackData;

        ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ${th.make_pfncb_type(n, tags, obj)}, ${th.get_callback_table_name(n, tags, obj)}, ${th.make_pfncb_name(n, tags, obj)});


        return tracing_layer::APITracerWrapperImp(context.${n}DdiTable.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)},
                                                  &tracerParams,
                                                  apiCallbackData.apiOrdinal,
                                                  apiCallbackData.prologCallbacks,
                                                  apiCallbackData.epilogCallbacks,
                                                  *tracerParams.p${",\n                                                  *tracerParams.p".join(th.make_param_lines(n, tags, obj, format=["name"]))});
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endfor
} // namespace tracing_layer

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
    auto& dditable = tracing_layer::context.${n}DdiTable.${tbl['name']};

    if( nullptr == pDdiTable )
        return ${X}_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(tracing_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(tracing_layer::context.version) > ZE_MINOR_VERSION(version))
        return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for obj in tbl['functions']:
    %if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
    %endif
    dditable.${th.append_ws(th.make_pfn_name(n, tags, obj), 43)} = pDdiTable->${th.make_pfn_name(n, tags, obj)};
    pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 41)} = tracing_layer::${th.make_func_name(n, tags, obj)};
    %if 'condition' in obj:
#else
    dditable.${th.append_ws(th.make_pfn_name(n, tags, obj), 43)} = nullptr;
    pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 41)} = nullptr;
#endif
    %endif

    %endfor
    return result;
}

%endfor
#if defined(__cplusplus)
};
#endif
