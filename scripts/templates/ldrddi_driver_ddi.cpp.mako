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
        ${x}_result_t result = ${X}_RESULT_SUCCESS;<%
        add_local = False
        arrays_to_delete = []
    %>

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
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ${th.get_version(obj)}) {
            return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->${th.get_table_name(n, tags, obj)} == nullptr) {
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        }
        auto ${th.make_pfn_name(n, tags, obj)} = dditable->${th.get_table_name(n, tags, obj)}->${th.make_pfn_name(n, tags, obj)};
        if( nullptr == ${th.make_pfn_name(n, tags, obj)} )
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        %endif
        %endfor
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