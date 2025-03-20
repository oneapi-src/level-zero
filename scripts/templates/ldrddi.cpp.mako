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
        %if re.match(r"Init", obj['name']) and namespace == "zes":
            if (!drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}) {
                drv.initDriversStatus = ZE_RESULT_ERROR_UNINITIALIZED;
                continue;
            }
        %endif
            drv.initStatus = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
            if(drv.initStatus == ZE_RESULT_SUCCESS)
                atLeastOneDriverValid = true;
        }

        if(!atLeastOneDriverValid)
            result=ZE_RESULT_ERROR_UNINITIALIZED;

        %elif re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)) or re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
        uint32_t total_driver_handle_count = 0;

        if (!loader::context->sortingInProgress.exchange(true) && !loader::context->instrumentationEnabled) {
            %if namespace != "zes":
            %if not re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)):
            std::call_once(loader::context->coreDriverSortOnce, []() {
                loader::context->driverSorting(&loader::context->zeDrivers, nullptr);
            });
            %else:
            std::call_once(loader::context->coreDriverSortOnce, [desc]() {
                loader::context->driverSorting(&loader::context->zeDrivers, desc);
            });
            %endif
            %else:
            std::call_once(loader::context->sysmanDriverSortOnce, []() {
                loader::context->driverSorting(loader::context->sysmanInstanceDrivers, nullptr);
            });
            %endif
            loader::context->sortingInProgress.store(false);
        }

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
                        ${obj['params'][1]['name']}[ driver_index ] = reinterpret_cast<${n}_driver_handle_t>(
                            context->${n}_driver_factory.getInstance( ${obj['params'][1]['name']}[ driver_index ], &drv.dditable ) );
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
        // extract driver's function pointer table
        %if 'range' in item:
        auto dditable = reinterpret_cast<${item['obj']}*>( ${item['name']}[ 0 ] )->dditable;
        %else:
        auto dditable = reinterpret_cast<${item['obj']}*>( ${item['name']} )->dditable;
        %endif
        auto ${th.make_pfn_name(n, tags, obj)} = dditable->${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
        if( nullptr == ${th.make_pfn_name(n, tags, obj)} )
            return ${X}_RESULT_ERROR_UNINITIALIZED;

        %endif
        %if 'range' in item:
        <%
        add_local = True%>// convert loader handles to driver handles
        auto ${item['name']}Local = new ${item['type']} [${item['range'][1]}];
        <%
        arrays_to_delete.append(item['name']+ 'Local')
        %>for( size_t i = ${item['range'][0]}; ( nullptr != ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
            ${item['name']}Local[ i ] = reinterpret_cast<${item['obj']}*>( ${item['name']}[ i ] )->handle;
        %else:
        %if item['optional']:
        // convert loader handle to driver handle
        ${item['name']} = ( ${item['name']} ) ? reinterpret_cast<${item['obj']}*>( ${item['name']} )->handle : nullptr;
        %else:
        %if re.match(r"\w+ImageDestroy$", th.make_func_name(n, tags, obj)):
        // remove the handle from the kernel arugment map
        {
            std::lock_guard<std::mutex> lock(context->image_handle_map_lock);
            context->image_handle_map.erase(reinterpret_cast<ze_image_object_t*>(hImage));
        }
        %endif
        %if re.match(r"\w+SamplerDestroy$", th.make_func_name(n, tags, obj)):
        // remove the handle from the kernel arugment map
        {
            std::lock_guard<std::mutex> lock(context->sampler_handle_map_lock);
            context->sampler_handle_map.erase(reinterpret_cast<ze_sampler_object_t*>(hSampler));
        }
        %endif
        // convert loader handle to driver handle
        ${item['name']} = reinterpret_cast<${item['obj']}*>( ${item['name']} )->handle;
        %endif
        %endif

        %endfor
        %if re.match(r"\w+KernelSetArgumentValue$", th.make_func_name(n, tags, obj)):
        // convert pArgValue to correct handle if applicable
        void *internalArgValue = const_cast<void *>(pArgValue);
        if (pArgValue) {
            // check if the arg value is a translated handle
            ze_image_object_t **imageHandle = static_cast<ze_image_object_t **>(internalArgValue);
            ze_sampler_object_t **samplerHandle = static_cast<ze_sampler_object_t **>(internalArgValue);
            {
                std::lock_guard<std::mutex> image_lock(context->image_handle_map_lock);
                std::lock_guard<std::mutex> sampler_lock(context->sampler_handle_map_lock);
                if( context->image_handle_map.find(*imageHandle) != context->image_handle_map.end() ) {
                    internalArgValue = &context->image_handle_map[*imageHandle];
                } else if( context->sampler_handle_map.find(*samplerHandle) != context->sampler_handle_map.end() ) {
                    internalArgValue = &context->sampler_handle_map[*samplerHandle];
                }
            }
        }
        %endif
        ## Workaround due to incorrect defintion of phWaitEvents in the ze headers which missed the range values.
        ## To be removed once the headers have been updated in a new spec release.
        %if re.match(r"\w+CommandListAppendMetricQueryEnd$", th.make_func_name(n, tags, obj)):
        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;
        %else:
        // forward to device-driver
        %if add_local:
        result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name", "local"]))} );
        %for array_name in arrays_to_delete:
        delete []${array_name};
        %endfor
        %else:
        %if re.match(r"\w+KernelSetArgumentValue$", th.make_func_name(n, tags, obj)):
        result = pfnSetArgumentValue( hKernel, argIndex, argSize, const_cast<const void *>(internalArgValue) );
        %else:
        result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
        %endif
        %endif
        %endif
<%
        del arrays_to_delete
        del add_local%>
        %for i, item in enumerate(th.get_loader_epilogue(n, tags, obj, meta)):
        %if 0 == i:
        %if not re.match(r"\w+ModuleDynamicLink$", th.make_func_name(n, tags, obj)) and not re.match(r"\w+ModuleCreate$", th.make_func_name(n, tags, obj)):
        if( ${X}_RESULT_SUCCESS != result )
            return result;

        %endif
        %endif
        %if item['release']:
        // release loader handle
        context->${item['factory']}.release( ${item['name']} );
        %else:
        try
        {
            %if 'range' in item:
            // convert driver handles to loader handles
            for( size_t i = ${item['range'][0]}; ( nullptr != ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
                ${item['name']}[ i ] = reinterpret_cast<${item['type']}>(
                    context->${item['factory']}.getInstance( ${item['name']}[ i ], dditable ) );
            %else:
            // convert driver handle to loader handle
            %if item['optional']:
            if( nullptr != ${item['name']} )
                *${item['name']} = reinterpret_cast<${item['type']}>(
                    context->${item['factory']}.getInstance( *${item['name']}, dditable ) );
            %else:
            %if re.match(r"\w+ImageCreate$", th.make_func_name(n, tags, obj)) or re.match(r"\w+SamplerCreate$", th.make_func_name(n, tags, obj)) or re.match(r"\w+ImageViewCreateExp$", th.make_func_name(n, tags, obj)):
            ${item['type']} internalHandlePtr = *${item['name']};
            %endif
            *${item['name']} = reinterpret_cast<${item['type']}>(
                context->${item['factory']}.getInstance( *${item['name']}, dditable ) );
            %if re.match(r"\w+ImageCreate$", th.make_func_name(n, tags, obj)) or re.match(r"\w+ImageViewCreateExp$", th.make_func_name(n, tags, obj)):
            // convert loader handle to driver handle and store in map
            {
                std::lock_guard<std::mutex> lock(context->image_handle_map_lock);
                context->image_handle_map.insert({context->ze_image_factory.getInstance( internalHandlePtr, dditable ), internalHandlePtr});
            }
            %endif
            %if re.match(r"\w+SamplerCreate$", th.make_func_name(n, tags, obj)):
            // convert loader handle to driver handle and store in map
            {
                std::lock_guard<std::mutex> lock(context->sampler_handle_map_lock);
                context->sampler_handle_map.insert({context->ze_sampler_factory.getInstance( internalHandlePtr, dditable ), internalHandlePtr});
            }
            %endif
            %endif
            %endif
        }
        catch( std::bad_alloc& )
        {
            result = ${X}_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }
        %endif

        %if 0 == i:
        %if re.match(r"\w+ModuleDynamicLink$", th.make_func_name(n, tags, obj)) or re.match(r"\w+ModuleCreate$", th.make_func_name(n, tags, obj)):
        if( ${X}_RESULT_SUCCESS != result )
            return result;

        %endif
        %endif
        %endfor
        %endif
        return result;
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endfor
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
