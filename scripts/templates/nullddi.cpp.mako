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
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 *
 */
#include "${x}_null.h"
#include <cstring>

namespace driver
{
    %for obj in th.extract_objs(specs, r"function"):
    ///////////////////////////////////////////////////////////////////////////////
    <%
        fname = th.make_func_name(n, tags, obj)
    %>/// @brief Intercept function for ${fname}
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    __${x}dlllocal ${x}_result_t ${X}_APICALL
    ${fname}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
        )
    {
        ${x}_result_t result = ${X}_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto ${th.make_pfn_name(n, tags, obj)} = context.${n}DdiTable.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
        if( nullptr != ${th.make_pfn_name(n, tags, obj)} )
        {
            result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
        }
        else
        {
            // generic implementation
            %if re.match("Init", obj['name']):
            %if re.match("InitDrivers", obj['name']):
            auto driver_type = getenv_string( "ZEL_TEST_NULL_DRIVER_TYPE" );
            if (std::strcmp(driver_type.c_str(), "GPU") == 0) {
                if (!(desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_GPU)) {
                    return ${X}_RESULT_ERROR_UNINITIALIZED;
                }
            }
            if (std::strcmp(driver_type.c_str(), "NPU") == 0) {
                if (!(desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_NPU)) {
                    return ${X}_RESULT_ERROR_UNINITIALIZED;
                }
            }

            if (phDrivers == nullptr) {
                *pCount = 1;
            }
            %else:
            auto driver_type = getenv_string( "ZEL_TEST_NULL_DRIVER_TYPE" );
            if (std::strcmp(driver_type.c_str(), "GPU") == 0) {
                if (!(flags & ZE_INIT_FLAG_GPU_ONLY)) {
                    return ${X}_RESULT_ERROR_UNINITIALIZED;
                }
            }
            if (std::strcmp(driver_type.c_str(), "NPU") == 0) {
                if (!(flags & ZE_INIT_FLAG_VPU_ONLY)) {
                    return ${X}_RESULT_ERROR_UNINITIALIZED;
                }
            }
            %endif
            %endif
            %for item in th.get_loader_epilogue(n, tags, obj, meta):
            %if 'range' in item:
            for( size_t i = ${item['range'][0]}; ( nullptr != ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
                ${item['name']}[ i ] = reinterpret_cast<${item['type']}>( context.get() );
            %elif not item['release']:
            %if item['optional']:
            if( nullptr != ${item['name']} ) *${item['name']} = reinterpret_cast<${item['type']}>( context.get() );
            %else:
            *${item['name']} = reinterpret_cast<${item['type']}>( context.get() );
            %endif
            %endif

            %endfor
        }

        return result;
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endfor
} // namespace driver

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
    if( nullptr == pDdiTable )
        return ${X}_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

% if tbl['name'] == 'Global' and n == 'ze':
    pDdiTable->pfnInit                                   = driver::zeInit;

    auto missing_api = getenv_string( "ZEL_TEST_MISSING_API" );
    auto missing_api_driver_id = getenv_string( "ZEL_TEST_MISSING_API_DRIVER_ID" );
    std::string zeInitDriversWithNullDriverId = "zeInitDrivers:" + std::to_string(ZEL_NULL_DRIVER_ID);
    if (std::strcmp(missing_api_driver_id.c_str(), zeInitDriversWithNullDriverId.c_str()) == 0) {
        pDdiTable->pfnInitDrivers                            = nullptr;
    } else if (std::strcmp(missing_api.c_str(), "zeInitDrivers") == 0) {
        pDdiTable->pfnInitDrivers                            = nullptr;
    } else {
        pDdiTable->pfnInitDrivers                            = driver::zeInitDrivers;
    }
%else:
    %for obj in tbl['functions']:
    %if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
    %endif
    pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 41)} = driver::${th.make_func_name(n, tags, obj)};
    %if 'condition' in obj:
#else
    pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 41)} = nullptr;
#endif
    %endif

    %endfor
%endif
    return result;
}

%endfor
#if defined(__cplusplus)
};
#endif
