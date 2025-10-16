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
/// @deprecated This function is deprecated and will be removed in a future release.
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderDriverCheck(ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly)
{
    return ZE_RESULT_SUCCESS;
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
/// @brief Internal function for Setting the ZE ddi table for the Tracing Layer.
///
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderTracingLayerInit(std::atomic<ze_dditable_t *> &zeDdiTable) {
    zeDdiTable.store(&loader::context->tracing_dditable.ze);
    return ZE_RESULT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Internal function for Setting the ZER ddi table for the Tracing Layer.
///
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderZerTracingLayerInit(std::atomic<zer_dditable_t *> &zerDdiTable) {
    zerDdiTable.store(&loader::context->tracing_dditable.zer);
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
        {
            // Determine if legacy loader intercept is enabled 
	    // i.e., loader object exists for that handle by checking two conditions:
            // 1. DDI Ext is disabled in loader by default OR
            // 2. The input handle's function pointer matches the loader's dispatch table pointer,
            //    indicating that the handle was created through the legacy loader intercept layer
	    
	    bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Driver->pfnGet ==
                                                 loader::loaderDispatch->pCore->Driver->pfnGet);
            if (legacy_ldr_intercept_enabled && loader::context->ze_driver_factory.hasInstance(reinterpret_cast<loader::ze_driver_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_driver_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_DEVICE:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Device->pfnGet ==
                                                 loader::loaderDispatch->pCore->Device->pfnGet);
            if (legacy_ldr_intercept_enabled && loader::context->ze_device_factory.hasInstance(reinterpret_cast<loader::ze_device_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_device_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_CONTEXT:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Context->pfnCreate ==
                                                 loader::loaderDispatch->pCore->Context->pfnCreate);
            if (legacy_ldr_intercept_enabled &&
                loader::context->ze_context_factory.hasInstance(reinterpret_cast<loader::ze_context_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_context_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_COMMAND_QUEUE:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->CommandQueue->pfnCreate ==
                                                 loader::loaderDispatch->pCore->CommandQueue->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_command_queue_factory.hasInstance(reinterpret_cast<loader::ze_command_queue_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_command_queue_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_COMMAND_LIST:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->CommandList->pfnCreate ==
                                                 loader::loaderDispatch->pCore->CommandList->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_command_list_factory.hasInstance(reinterpret_cast<loader::ze_command_list_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_command_list_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_FENCE:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Fence->pfnCreate ==
                                                 loader::loaderDispatch->pCore->Fence->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_fence_factory.hasInstance(reinterpret_cast<loader::ze_fence_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_fence_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_EVENT_POOL:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->EventPool->pfnCreate ==
                                                 loader::loaderDispatch->pCore->EventPool->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_event_pool_factory.hasInstance(reinterpret_cast<loader::ze_event_pool_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_event_pool_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_EVENT:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Event->pfnCreate ==
                                                 loader::loaderDispatch->pCore->Event->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_event_factory.hasInstance(reinterpret_cast<loader::ze_event_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_event_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_IMAGE:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Image->pfnCreate ==
                                                 loader::loaderDispatch->pCore->Image->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_image_factory.hasInstance(reinterpret_cast<loader::ze_image_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_image_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_MODULE:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Module->pfnCreate ==
                                                 loader::loaderDispatch->pCore->Module->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_module_factory.hasInstance(reinterpret_cast<loader::ze_module_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_module_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_MODULE_BUILD_LOG:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->ModuleBuildLog->pfnGetString ==
                                                 loader::loaderDispatch->pCore->ModuleBuildLog->pfnGetString);
            if (legacy_ldr_intercept_enabled && loader::context->ze_module_build_log_factory.hasInstance(reinterpret_cast<loader::ze_module_build_log_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_module_build_log_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_KERNEL:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Kernel->pfnCreate ==
                                                 loader::loaderDispatch->pCore->Kernel->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_kernel_factory.hasInstance(reinterpret_cast<loader::ze_kernel_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_kernel_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_SAMPLER:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->Sampler->pfnCreate ==
                                                 loader::loaderDispatch->pCore->Sampler->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_sampler_factory.hasInstance(reinterpret_cast<loader::ze_sampler_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_sampler_object_t *>(handleIn)->handle;
            }
            break;
        }
        case ZEL_HANDLE_PHYSICAL_MEM:
        {
            bool legacy_ldr_intercept_enabled = (!loader::context->driverDDIPathDefault) ||
                                                (reinterpret_cast<ze_handle_t *>(handleIn)->pCore->PhysicalMem->pfnCreate ==
                                                 loader::loaderDispatch->pCore->PhysicalMem->pfnCreate);
            if (legacy_ldr_intercept_enabled && loader::context->ze_physical_mem_factory.hasInstance(reinterpret_cast<loader::ze_physical_mem_object_t *>(handleIn)->handle))
            {
                *handleOut = reinterpret_cast<loader::ze_physical_mem_object_t *>(handleIn)->handle;
            }
            break;
        }
        default:
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;
        }
	    
	    
    return ZE_RESULT_SUCCESS;
}


#if defined(__cplusplus)
}
#endif
