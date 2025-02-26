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
#include "${x}_loader_internal.h"

namespace loader
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
        ${x}_result_t result = ${X}_RESULT_SUCCESS;<%
        add_local = False
        arrays_to_delete = []
    %>

        %if re.match(r"Init", obj['name']) and not re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
        bool atLeastOneDriverValid = false;
        %if namespace != "zes":
        for( auto& drv : loader::context->zeDrivers )
        %else:
        for( auto& drv : *loader::context->sysmanInstanceDrivers )
        %endif
        {
            if(drv.initStatus != ZE_RESULT_SUCCESS)
                continue;
            drv.initStatus = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
            if(drv.initStatus == ZE_RESULT_SUCCESS)
                atLeastOneDriverValid = true;
        }

        if(!atLeastOneDriverValid)
            result=ZE_RESULT_ERROR_UNINITIALIZED;

        %elif re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)) or re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
        uint32_t total_driver_handle_count = 0;

        %if namespace != "zes":
        for( auto& drv : loader::context->zeDrivers )
        %else:
        for( auto& drv : *loader::context->sysmanInstanceDrivers )
        %endif
        {
            %if not re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
            if(drv.initStatus != ZE_RESULT_SUCCESS)
                continue;
            %else:
            if (!drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}) {
                %if re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
                drv.initDriversStatus = ${X}_RESULT_ERROR_UNINITIALIZED;
                %else:
                drv.initStatus = ${X}_RESULT_ERROR_UNINITIALIZED;
                %endif
                continue;
            }
            %endif

            if( ( 0 < *${obj['params'][0]['name']} ) && ( *${obj['params'][0]['name']} == total_driver_handle_count))
                break;

            uint32_t library_driver_handle_count = 0;

            %if re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
            result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &library_driver_handle_count, nullptr, desc );
            %else:
            result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &library_driver_handle_count, nullptr );
            %endif
            if( ${X}_RESULT_SUCCESS != result ) {
                // If Get Drivers fails with Uninitialized, then update the driver init status to prevent reporting this driver in the next get call.
                if (${X}_RESULT_ERROR_UNINITIALIZED == result) {
                    %if re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
                    drv.initDriversStatus = result;
                    %else:
                    drv.initStatus = result;
                    %endif
                }
                continue;
            }

            if( nullptr != ${obj['params'][1]['name']} && *${obj['params'][0]['name']} !=0)
            {
                if( total_driver_handle_count + library_driver_handle_count > *${obj['params'][0]['name']}) {
                    library_driver_handle_count = *${obj['params'][0]['name']} - total_driver_handle_count;
                }
                %if re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
                result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &library_driver_handle_count, &${obj['params'][1]['name']}[ total_driver_handle_count ], desc );
                %else:
                result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &library_driver_handle_count, &${obj['params'][1]['name']}[ total_driver_handle_count ] );
                %endif
                if( ${X}_RESULT_SUCCESS != result ) break;

                drv.driverInuse = true;

                try
                {
                    for( uint32_t i = 0; i < library_driver_handle_count; ++i ) {
                        uint32_t driver_index = total_driver_handle_count + i;
                        if (!drv.driverSupportsDDIHandles) {
                            ${obj['params'][1]['name']}[ driver_index ] = reinterpret_cast<${n}_driver_handle_t>(
                                context->${n}_driver_factory.getInstance( ${obj['params'][1]['name']}[ driver_index ], &drv.dditable ) );
                        }
                    }
                }
                catch( std::bad_alloc& )
                {
                    result = ${X}_RESULT_ERROR_OUT_OF_HOST_MEMORY;
                }
            }

            total_driver_handle_count += library_driver_handle_count;
        }

        // If the last driver get failed, but at least one driver succeeded, then return success with total count.
        if( ${X}_RESULT_SUCCESS == result || total_driver_handle_count > 0)
            *${obj['params'][0]['name']} = total_driver_handle_count;
        if (total_driver_handle_count > 0) {
            result = ${X}_RESULT_SUCCESS;
        }

        %else:
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
    %if re.match(r"Init", obj['name']) or re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)) or re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)):
        return result;
    }
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

} // namespace loader

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
///     - ::${X}_RESULT_ERROR_UNINITIALIZED
///     - ::${X}_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::${X}_RESULT_ERROR_UNSUPPORTED_VERSION
${X}_DLLEXPORT ${x}_result_t ${X}_APICALL
${tbl['export']['name']}(
    %for line in th.make_param_lines(n, tags, tbl['export']):
    ${line}
    %endfor
    )
{
    %if namespace != "zes":
    if( loader::context->zeDrivers.size() < 1 ) {
    %else:
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
    %endif
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ${X}_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %if tbl['experimental'] is False: #//Experimental Tables may not be implemented in driver
    bool atLeastOneDriverValid = false;
    %endif
    // Load the device-driver DDI tables
    %if namespace != "zes":
    for( auto& drv : loader::context->zeDrivers )
    %else:
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    %endif
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<${tbl['pfn']}>(
            GET_FUNCTION_PTR( drv.handle, "${tbl['export']['name']}") );
        if(!getTable) 
        %if th.isNewProcTable(tbl['export']['name']) is True:
        {
            atLeastOneDriverValid = true;
            //It is valid to not have this proc addr table
            continue; 
        }
        %else:
            continue; 
        %endif
        %if tbl['experimental'] is False: #//Experimental Tables may not be implemented in driver
        auto getTableResult = getTable( version, &drv.dditable.${n}.${tbl['name']});
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
        %if namespace != "zes":
        %if tbl['name'] == "Global":
        if (drv.dditable.ze.Global.pfnInitDrivers) {
            loader::context->initDriversSupport = true;
        }
        %endif
        %endif
        %else:
        result = getTable( version, &drv.dditable.${n}.${tbl['name']});
        %endif
    }

    %if tbl['experimental'] is False: #//Experimental Tables may not be implemented in driver
    if(!atLeastOneDriverValid)
        result = ${X}_RESULT_ERROR_UNINITIALIZED;
    else
        result = ${X}_RESULT_SUCCESS;
    %endif

    if( ${X}_RESULT_SUCCESS == result )
    {
        %if namespace != "zes":
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        %else:
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        %endif
        {
            // return pointers to loader's DDIs
            %if namespace == "ze":
            loader::loaderDispatch->pCore->${tbl['name']} = new ${tbl['type']};
            %elif namespace == "zet":
            loader::loaderDispatch->pTools->${tbl['name']} = new ${tbl['type']};
            %elif namespace == "zes":
            loader::loaderDispatch->pSysman->${tbl['name']} = new ${tbl['type']};
            %endif
            %for obj in tbl['functions']:
            %if 'condition' in obj:
        #if ${th.subt(n, tags, obj['condition'])}
            %endif
            pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 43)} = loader::${th.make_func_name(n, tags, obj)};
            %if 'condition' in obj:
        #else
            pDdiTable->${th.append_ws(th.make_pfn_name(n, tags, obj), 43)} = nullptr;
        #endif
            %endif
            %endfor
            ${tbl['export']['name']}Legacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            %if namespace != "zes":
            *pDdiTable = loader::context->zeDrivers.front().dditable.${n}.${tbl['name']};
            %else:
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.${n}.${tbl['name']};
            %endif
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ${X}_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<${tbl['pfn']}>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "${tbl['export']['name']}") );
        if(!getTable)
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    %if namespace == "ze":
    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ${X}_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<${tbl['pfn']}>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "${tbl['export']['name']}") );
        if(!getTable)
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        ${tbl['type']} dditable;
        memcpy(&dditable, pDdiTable, sizeof(${tbl['type']}));
        result = getTable( version, &dditable );
        loader::context->tracing_dditable.${n}.${tbl['name']} = dditable;
        if ( loader::context->tracingLayerEnabled ) {
            result = getTable( version, pDdiTable );
        }
    }

    %endif
    return result;
}

%endfor

#if defined(__cplusplus)
};
#endif