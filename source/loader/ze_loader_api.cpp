/*
 *
 * Copyright (C) 2020-2025 Intel Corporation
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
zelLoaderDriverCheck(ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly)
{
    return loader::context->check_drivers(flags, desc, globalInitStored, sysmanGlobalInitStored, requireDdiReinit, sysmanOnly);
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

///////////////////////////////////////////////////////////////////////////////
/// @brief Get pointer to Loader Context
///
/// @returns
///     - ::Pointer to the Loader's Context
ZE_DLLEXPORT loader::context_t *ZE_APICALL
zelLoaderGetContext() {
    return loader::context;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Internal function for Setting the ddi table for the Tracing Layer.
///
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderTracingLayerInit(std::atomic<ze_dditable_t *> &zeDdiTable) {
    zeDdiTable.store(&loader::context->tracing_dditable.ze);
    return ZE_RESULT_SUCCESS;
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
    if (!handleIn || !handleOut) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    if(!loader::context->intercept_enabled) {
        *handleOut = handleIn;
        return ZE_RESULT_SUCCESS;
    }

    *handleOut = handleIn;
    switch(handleType){
        case ZEL_HANDLE_DRIVER: 
            if (loader::context->ze_driver_factory.hasInstance(reinterpret_cast<loader::ze_driver_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_driver_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_DEVICE: 
            if (loader::context->ze_device_factory.hasInstance(reinterpret_cast<loader::ze_device_object_t*>(handleIn)->handle)){
                *handleOut = reinterpret_cast<loader::ze_device_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_CONTEXT: 
            if (loader::context->ze_context_factory.hasInstance(reinterpret_cast<loader::ze_context_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_context_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_COMMAND_QUEUE:
            if (loader::context->ze_command_queue_factory.hasInstance(reinterpret_cast<loader::ze_command_queue_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_command_queue_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_COMMAND_LIST:
            if (loader::context->ze_command_list_factory.hasInstance(reinterpret_cast<loader::ze_command_list_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_command_list_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_FENCE:
            if (loader::context->ze_fence_factory.hasInstance(reinterpret_cast<loader::ze_fence_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_fence_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_EVENT_POOL:
            if (loader::context->ze_event_pool_factory.hasInstance(reinterpret_cast<loader::ze_event_pool_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_event_pool_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_EVENT:
            if (loader::context->ze_event_factory.hasInstance(reinterpret_cast<loader::ze_event_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_event_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_IMAGE:
            if (loader::context->ze_image_factory.hasInstance(reinterpret_cast<loader::ze_image_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_image_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_MODULE:
            if (loader::context->ze_module_factory.hasInstance(reinterpret_cast<loader::ze_module_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_module_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_MODULE_BUILD_LOG:
            if (loader::context->ze_module_build_log_factory.hasInstance(reinterpret_cast<loader::ze_module_build_log_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_module_build_log_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_KERNEL:
            if (loader::context->ze_kernel_factory.hasInstance(reinterpret_cast<loader::ze_kernel_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_kernel_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_SAMPLER:
            if (loader::context->ze_sampler_factory.hasInstance(reinterpret_cast<loader::ze_sampler_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_sampler_object_t*>( handleIn )->handle;
            }
            break;
        case ZEL_HANDLE_PHYSICAL_MEM:
            if (loader::context->ze_physical_mem_factory.hasInstance(reinterpret_cast<loader::ze_physical_mem_object_t*>(handleIn)->handle)) {
                *handleOut = reinterpret_cast<loader::ze_physical_mem_object_t*>( handleIn )->handle;
            }
            break;
        default:
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;
    }
        
    return ZE_RESULT_SUCCESS;
}


#if defined(__cplusplus)
}
#endif