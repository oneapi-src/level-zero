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
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 *
 */
#include "${x}_loader_internal.h"

namespace loader_driver_ddi
{
    %for obj in th.extract_objs(specs, r"function"):
    %if not (re.match(r"Init", obj['name']) or re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)) or re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj))):
    <%
    ret_type = obj['return_type']
    failure_return = None
    if ret_type != 'ze_result_t':
        failure_return = th.get_first_failure_return(obj)
    %>///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for ${th.make_func_name(n, tags, obj)}
    %if 'condition' in obj:
    #if ${th.subt(n, tags, obj['condition'])}
    %endif
    __${x}dlllocal ${ret_type} ${X}_APICALL
    ${th.make_func_name(n, tags, obj)}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
        )
    {
        %if ret_type == 'ze_result_t':
        ${x}_result_t result = ${X}_RESULT_SUCCESS;
        %else:
        ${ret_type} result {};
        %endif

        %if namespace != "zer":
        %for i, item in enumerate(th.get_loader_prologue(n, tags, obj, meta)):
        %if 0 == i:
        // extract handle's function pointer table
        %if 'range' in item:
        %if namespace == "ze":
        auto dditable = reinterpret_cast<ze_handle_t*>( ${item['name']}[ 0 ] )->pCore;
        %elif namespace == "zet":
        auto dditable = reinterpret_cast<ze_handle_t*>( ${item['name']}[ 0 ] )->pTools;
        %elif namespace == "zes":
        auto dditable = reinterpret_cast<ze_handle_t*>( ${item['name']}[ 0 ] )->pSysman;
        %endif
        %else:
        %if namespace == "ze":
        auto dditable = reinterpret_cast<ze_handle_t*>( ${item['name']} )->pCore;
        %elif namespace == "zet":
        auto dditable = reinterpret_cast<ze_handle_t*>( ${item['name']} )->pTools;
        %elif namespace == "zes":
        auto dditable = reinterpret_cast<ze_handle_t*>( ${item['name']} )->pSysman;
        %endif
        %endif
        if (dditable->isValidFlag == 0)
            %if ret_type == 'ze_result_t':
            return ${X}_RESULT_ERROR_UNINITIALIZED;
            %else:
            return ${failure_return};
            %endif
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ${th.get_version(obj)}) {
            %if ret_type == 'ze_result_t':
            return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;
            %else:
            return ${failure_return};
            %endif
        }
        // Check that the driver has the function pointer table init
        if (dditable->${th.get_table_name(n, tags, obj)} == nullptr) {
            %if ret_type == 'ze_result_t':
            return ${X}_RESULT_ERROR_UNINITIALIZED;
            %else:
            return ${failure_return};
            %endif
        }
        auto ${th.make_pfn_name(n, tags, obj)} = dditable->${th.get_table_name(n, tags, obj)}->${th.make_pfn_name(n, tags, obj)};
        %endif
        %endfor
        %else: ## for zer API's
        %if re.match(r"\w+GetLastErrorDescription", th.make_func_name(n, tags, obj)):
        error_state::getErrorDesc(ppString);
        if (ppString && *ppString && strlen(*ppString) > 0)
        {
            return ZE_RESULT_SUCCESS;
        }

        %endif
        // Check if the default driver supports DDI Handles
        if (loader::context->defaultZerDriverHandle == nullptr) {
            %if ret_type == 'ze_result_t':
            if (loader::context->zeDrivers.front().zerddiInitResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
                return ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;
            }
            return ${X}_RESULT_ERROR_UNINITIALIZED;
            %else:
            if (loader::context->zeDrivers.front().zerddiInitResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
                error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
                return ${failure_return};
            }
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return ${failure_return};
            %endif
        }
        auto dditable = reinterpret_cast<ze_handle_t*>( loader::context->defaultZerDriverHandle )->pRuntime;
        if (dditable->isValidFlag == 0) {
            %if ret_type == 'ze_result_t':
            return ${X}_RESULT_ERROR_UNINITIALIZED;
            %else:
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return ${failure_return};
            %endif
        }
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ${th.get_version(obj)}) {
            %if ret_type == 'ze_result_t':
            return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;
            %else:
            error_state::setErrorDesc("ERROR UNSUPPORTED VERSION");
            return ${failure_return};
            %endif
        }
        // Check that the driver has the function pointer table init
        if (dditable->${th.get_table_name(n, tags, obj)} == nullptr) {
            %if ret_type == 'ze_result_t':
            return ${X}_RESULT_ERROR_UNINITIALIZED;
            %else:
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return ${failure_return};
            %endif
        }
        auto ${th.make_pfn_name(n, tags, obj)} = dditable->${th.get_table_name(n, tags, obj)}->${th.make_pfn_name(n, tags, obj)};
        %endif
        if( nullptr == ${th.make_pfn_name(n, tags, obj)} ) {
            %if ret_type == 'ze_result_t':
            return ${X}_RESULT_ERROR_UNINITIALIZED;
            %else:
            %if n == 'zer':
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            %endif
            return ${failure_return};
            %endif
        }
        // forward to device-driver
        result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
        return result;
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endif
    %endfor

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief function for removing the ddi driver tables for ${n}
    __${x}dlllocal void ${X}_APICALL
    ${n}DestroyDDiDriverTables(${n}_dditable_driver_t* pDdiTable)
    {
        // Delete ddi tables
%for tbl in th.get_pfntables(specs, meta, n, tags):
        delete pDdiTable->${tbl['name']};
%endfor
        delete pDdiTable;
    }

} // namespace loader_driver_ddi