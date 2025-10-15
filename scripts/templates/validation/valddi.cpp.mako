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
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#include "${x}_validation_layer.h"

namespace validation_layer
{
%if n == 'ze':
    // Forward declaration for Intel experimental extension
    // This is needed because zeDriverGetExtensionFunctionAddress needs to reference zexCounterBasedEventCreate2
    __zedlllocal ze_result_t ZE_APICALL zexCounterBasedEventCreate2(
        ze_context_handle_t hContext,
        ze_device_handle_t hDevice,
        const void *desc,
        ze_event_handle_t *phEvent
    );

%endif
    static ze_result_t logAndPropagateResult(const char* fname, ze_result_t result) {
        if (result != ${X}_RESULT_SUCCESS) {
            context.logger->log_trace("Error (" + loader::to_string(result) + ") in " + std::string(fname));
        }
        return result;
    }

    %for obj in th.extract_objs(specs, r"function"):
    <%
    ret_type = obj['return_type']
    failure_return = None
    if ret_type != 'ze_result_t':
        failure_return = th.get_first_failure_return(obj)
    param_lines = [line for line in th.make_param_lines(n, tags, obj, format=['name','delim'])]
    is_void_params = len(param_lines) == 0
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
        context.logger->log_trace("${th.make_func_name(n, tags, obj)}(${", ".join(th.make_param_lines(n, tags, obj, format=["name", "local"]))})");

        auto ${th.make_pfn_name(n, tags, obj)} = context.${n}DdiTable.${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};

        if( nullptr == ${th.make_pfn_name(n, tags, obj)} )
        %if ret_type == "ze_result_t":
            return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE);
        %else:
            return ${failure_return};
        %endif

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->${n}Validation->${th.make_func_name(n, tags, obj)}Prologue( \
% for line in param_lines:
${line} \
%endfor
);
            if(result!=${X}_RESULT_SUCCESS) \
%if ret_type == "ze_result_t":
return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", result);
%else:
return ${failure_return};
%endif
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
% for line in param_lines:
${line} \
%endfor
);
            if(result!=${X}_RESULT_SUCCESS) \
%if ret_type == "ze_result_t":
return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", result);
%else:
return ${failure_return};
%endif
        }

        auto driver_result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
%if 'ppFunctionAddress' in [p.get('name', '') for p in obj.get('params', [])] and n == 'ze':

        // For Intel experimental extensions, we need to return our validation layer function
        // instead of the raw driver function so that validation/leak tracking works
        if (driver_result == ZE_RESULT_SUCCESS && ppFunctionAddress && name) {
            if (strcmp(name, "zexCounterBasedEventCreate2") == 0) {
                // Return our validation layer intercept function instead of the raw driver function
                *ppFunctionAddress = (void*)zexCounterBasedEventCreate2;
            }
        }
%endif

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->${n}Validation->${th.make_func_name(n, tags, obj)}Epilogue( \
%if not is_void_params:
% for line in param_lines:
${line} \
%endfor
,driver_result);
%else:
driver_result );
%endif
            if(result!=${X}_RESULT_SUCCESS) \
%if ret_type == "ze_result_t":
return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", result);
%else:
return ${failure_return};
%endif
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
        %if ret_type == "ze_result_t":
        return logAndPropagateResult("${th.make_func_name(n, tags, obj)}", driver_result);
        %else:
        return driver_result;
        %endif
    }
    %if 'condition' in obj:
    #endif // ${th.subt(n, tags, obj['condition'])}
    %endif

    %endfor
%if n == 'ze':
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zexCounterBasedEventCreate2
    __zedlllocal ze_result_t ZE_APICALL zexCounterBasedEventCreate2(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const void* desc,                               ///< [in] pointer to counter-based event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        context.logger->log_trace("zexCounterBasedEventCreate2(hContext, hDevice, desc, phEvent)");

        // Note: This is an experimental function that may not have a DDI table entry.
        // For now, we'll return unsupported feature as this function should be
        // accessed through zeDriverGetExtensionFunctionAddress mechanism, but we
        // still want to track it in the validation layers for leak checking purposes.

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zexCounterBasedEventCreate2Prologue( hContext, hDevice, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zexCounterBasedEventCreate2", result);
        }

        if(context.enableThreadingValidation){
            //Unimplemented
        }

        if(context.enableHandleLifetime){
            auto result = context.handleLifetime->zeHandleLifetime.zexCounterBasedEventCreate2Prologue( hContext, hDevice, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zexCounterBasedEventCreate2", result);
        }

        // This is an experimental function that must be accessed through the extension mechanism
        // We need to get the function pointer through zeDriverGetExtensionFunctionAddress
        ze_result_t driver_result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        // Get the real Intel experimental function through the extension mechanism
        auto pfnGetExtensionFunctionAddress = context.zeDdiTable.Driver.pfnGetExtensionFunctionAddress;

        if (pfnGetExtensionFunctionAddress) {
            // Get the driver handle - use the first available driver
            ze_driver_handle_t hDriver = nullptr;

            if (context.zeDdiTable.Driver.pfnGet) {
                uint32_t driverCount = 1;
                ze_driver_handle_t drivers[1] = {nullptr};
                auto result = context.zeDdiTable.Driver.pfnGet(&driverCount, drivers);
                if (result == ZE_RESULT_SUCCESS && driverCount > 0) {
                    hDriver = drivers[0];
                }
            }

            if (hDriver) {
                // Get the real Intel experimental function
                typedef ze_result_t (*zexCounterBasedEventCreate2_t)(ze_context_handle_t, ze_device_handle_t, const void*, ze_event_handle_t*);
                zexCounterBasedEventCreate2_t pfnRealFunction = nullptr;

                auto ext_result = pfnGetExtensionFunctionAddress(hDriver, "zexCounterBasedEventCreate2", (void**)&pfnRealFunction);

                if (ext_result == ZE_RESULT_SUCCESS && pfnRealFunction) {
                    // Call the real Intel experimental function
                    driver_result = pfnRealFunction(hContext, hDevice, desc, phEvent);
                } else {
                    // Extension not available in this driver
                    driver_result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
                }
            }
        }

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zexCounterBasedEventCreate2Epilogue( hContext, hDevice, desc, phEvent, driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zexCounterBasedEventCreate2", result);
        }

        if(driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime){
            if (phEvent){
                context.handleLifetime->addHandle( *phEvent );
                // Note: counter-based events may not have a traditional event pool dependency
            }
        }
        return logAndPropagateResult("zexCounterBasedEventCreate2", driver_result);
    }
%endif
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
