/*
 *
 * Copyright (C) 2020-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_loader_api.cpp
 *
 */

#include "ze_loader_internal.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for initializing loader
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeLoaderInit()
{
    return loader::context->init();
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for verifying usable L0 Drivers for Loader to report
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderDriverCheck(ze_init_flags_t flags)
{
    return loader::context->check_drivers(flags);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for getting tracing lib handle
///
/// @returns
///     - ::handle to tracing library
ZE_DLLEXPORT HMODULE ZE_APICALL
zeLoaderGetTracingHandle()
{
    return loader::context->tracingLayer;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderGetVersionsInternal(
   size_t *num_elems,                     //Pointer to num versions to get.  
   zel_component_version_t *versions)    //Pointer to array of versions. If set to NULL, num_elems is returned
{
    if(nullptr == versions){
        *num_elems = loader::context->compVersions.size();
        return ZE_RESULT_SUCCESS;
    }
    auto size = *num_elems > loader::context->compVersions.size() ? loader::context->compVersions.size() : *num_elems;
    memcpy(versions, loader::context->compVersions.data(), size * sizeof(zel_component_version_t));

    return ZE_RESULT_SUCCESS;
}


ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderTranslateHandleInternal(
   zel_handle_type_t handleType,
   void *handleIn,                       
   void **handleOut)
{

    if(!loader::context->intercept_enabled) {
        *handleOut = handleIn;
        return ZE_RESULT_SUCCESS;
    }

    switch(handleType){
        case ZEL_HANDLE_DRIVER: 
            *handleOut = reinterpret_cast<loader::ze_driver_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_DEVICE: 
            *handleOut = reinterpret_cast<loader::ze_device_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_CONTEXT: 
            *handleOut = reinterpret_cast<loader::ze_context_object_t*>( handleIn )->handle;
            break;            
        case ZEL_HANDLE_COMMAND_QUEUE: 
            *handleOut = reinterpret_cast<loader::ze_command_queue_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_COMMAND_LIST: 
            *handleOut = reinterpret_cast<loader::ze_command_list_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_FENCE: 
            *handleOut = reinterpret_cast<loader::ze_fence_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_EVENT_POOL: 
            *handleOut = reinterpret_cast<loader::ze_event_pool_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_EVENT: 
            *handleOut = reinterpret_cast<loader::ze_event_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_IMAGE: 
            *handleOut = reinterpret_cast<loader::ze_image_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_MODULE: 
            *handleOut = reinterpret_cast<loader::ze_module_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_MODULE_BUILD_LOG: 
            *handleOut = reinterpret_cast<loader::ze_module_build_log_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_KERNEL: 
            *handleOut = reinterpret_cast<loader::ze_kernel_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_SAMPLER: 
            *handleOut = reinterpret_cast<loader::ze_sampler_object_t*>( handleIn )->handle;
            break;
        case ZEL_HANDLE_PHYSICAL_MEM: 
            *handleOut = reinterpret_cast<loader::ze_physical_mem_object_t*>( handleIn )->handle;
            break;
        default:
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;
    }
        
    return ZE_RESULT_SUCCESS;
}


#if defined(__cplusplus)
}
#endif