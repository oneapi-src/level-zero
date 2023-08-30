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
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 *
 */
#include "${x}_loader_internal.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    %for obj in th.extract_objs(specs, r"handle"):
    %if 'class' in obj:
    <%
        _handle_t = th.subt(n, tags, obj['name'])
        _factory_t = re.sub(r"(\w+)_handle_t", r"\1_factory_t", _handle_t)
        _factory = re.sub(r"(\w+)_handle_t", r"\1_factory", _handle_t)
    %>${th.append_ws(_factory_t, 35)} ${_factory};
    %endif
    %endfor
    %if re.match(r"ze_ldrddi", name):
    ///////////////////////////////////////////////////////////////////////////////
    std::unordered_map<ze_image_object_t *, ze_image_handle_t>            image_handle_map;
    std::unordered_map<ze_sampler_object_t *, ze_sampler_handle_t>        sampler_handle_map;
    %endif

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

        %if re.match(r"Init", obj['name']):
        bool atLeastOneDriverValid = false;
        for( auto& drv : context->drivers )
        {
            if(drv.initStatus != ZE_RESULT_SUCCESS)
                continue;
            drv.initStatus = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
            if(drv.initStatus == ZE_RESULT_SUCCESS)
                atLeastOneDriverValid = true;
        }

        if(!atLeastOneDriverValid)
            result=ZE_RESULT_ERROR_UNINITIALIZED;

        %elif re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)):
        uint32_t total_driver_handle_count = 0;

        for( auto& drv : context->drivers )
        {
            if(drv.initStatus != ZE_RESULT_SUCCESS)
                continue;

            if( ( 0 < *${obj['params'][0]['name']} ) && ( *${obj['params'][0]['name']} == total_driver_handle_count))
                break;

            uint32_t library_driver_handle_count = 0;

            result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &library_driver_handle_count, nullptr );
            if( ${X}_RESULT_SUCCESS != result ) break;

            if( nullptr != ${obj['params'][1]['name']} && *${obj['params'][0]['name']} !=0)
            {
                if( total_driver_handle_count + library_driver_handle_count > *${obj['params'][0]['name']}) {
                    library_driver_handle_count = *${obj['params'][0]['name']} - total_driver_handle_count;
                }
                result = drv.dditable.${n}.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)}( &library_driver_handle_count, &${obj['params'][1]['name']}[ total_driver_handle_count ] );
                if( ${X}_RESULT_SUCCESS != result ) break;

                try
                {
                    for( uint32_t i = 0; i < library_driver_handle_count; ++i ) {
                        uint32_t driver_index = total_driver_handle_count + i;
                        ${obj['params'][1]['name']}[ driver_index ] = reinterpret_cast<${n}_driver_handle_t>(
                            ${n}_driver_factory.getInstance( ${obj['params'][1]['name']}[ driver_index ], &drv.dditable ) );
                    }
                }
                catch( std::bad_alloc& )
                {
                    result = ${X}_RESULT_ERROR_OUT_OF_HOST_MEMORY;
                }
            }

            total_driver_handle_count += library_driver_handle_count;
        }

        if( ${X}_RESULT_SUCCESS == result )
            *${obj['params'][0]['name']} = total_driver_handle_count;

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
        image_handle_map.erase(reinterpret_cast<ze_image_object_t*>(hImage));
        %endif
        %if re.match(r"\w+SamplerDestroy$", th.make_func_name(n, tags, obj)):
        // remove the handle from the kernel arugment map
        sampler_handle_map.erase(reinterpret_cast<ze_sampler_object_t*>(hSampler));
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
            if( image_handle_map.find(*imageHandle) != image_handle_map.end() ) {
                internalArgValue = &image_handle_map[*imageHandle];
            } else if( sampler_handle_map.find(*samplerHandle) != sampler_handle_map.end() ) {
                internalArgValue = &sampler_handle_map[*samplerHandle];
            }
        }
        %endif
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
        ${item['factory']}.release( ${item['name']} );
        %else:
        try
        {
            %if 'range' in item:
            // convert driver handles to loader handles
            for( size_t i = ${item['range'][0]}; ( nullptr != ${item['name']} ) && ( i < ${item['range'][1]} ); ++i )
                ${item['name']}[ i ] = reinterpret_cast<${item['type']}>(
                    ${item['factory']}.getInstance( ${item['name']}[ i ], dditable ) );
            %else:
            // convert driver handle to loader handle
            %if item['optional']:
            if( nullptr != ${item['name']} )
                *${item['name']} = reinterpret_cast<${item['type']}>(
                    ${item['factory']}.getInstance( *${item['name']}, dditable ) );
            %else:
            %if re.match(r"\w+ImageCreate$", th.make_func_name(n, tags, obj)) or re.match(r"\w+SamplerCreate$", th.make_func_name(n, tags, obj)) or re.match(r"\w+ImageViewCreateExp$", th.make_func_name(n, tags, obj)):
            ${item['type']} internalHandlePtr = *${item['name']};
            %endif
            *${item['name']} = reinterpret_cast<${item['type']}>(
                ${item['factory']}.getInstance( *${item['name']}, dditable ) );
            %if re.match(r"\w+ImageCreate$", th.make_func_name(n, tags, obj)) or re.match(r"\w+ImageViewCreateExp$", th.make_func_name(n, tags, obj)):
            // convert loader handle to driver handle and store in map
            image_handle_map.insert({ze_image_factory.getInstance( internalHandlePtr, dditable ), internalHandlePtr});
            %endif
            %if re.match(r"\w+SamplerCreate$", th.make_func_name(n, tags, obj)):
            // convert loader handle to driver handle and store in map
            sampler_handle_map.insert({ze_sampler_factory.getInstance( internalHandlePtr, dditable ), internalHandlePtr});
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
    if( loader::context->drivers.size() < 1 )
        return ${X}_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ${X}_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ${X}_RESULT_ERROR_UNSUPPORTED_VERSION;

    ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %if tbl['experimental'] is False: #//Experimental Tables may not be implemented in driver
    bool atLeastOneDriverValid = false;
    %endif
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
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
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
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
            *pDdiTable = loader::context->drivers.front().dditable.${n}.${tbl['name']};
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
        result = getTable( version, pDdiTable );
    }

    %endif
    return result;
}

%endfor

#if defined(__cplusplus)
};
#endif
