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
zelLoaderDriverCheck(ze_init_flags_t flags, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly)
{
    return loader::context->check_drivers(flags, globalInitStored, sysmanGlobalInitStored, requireDdiReinit, sysmanOnly);
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
zelReloadDriversInternal(
    ze_init_flags_t flags)
{
    for( auto& drv : loader::context->zeDrivers ) {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;

        if (drv.handle) {
            auto free_result = FREE_DRIVER_LIBRARY( drv.handle );
            auto failure = FREE_DRIVER_LIBRARY_FAILURE_CHECK(free_result);
            if (failure)
                return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        drv.handle = LOAD_DRIVER_LIBRARY( drv.name.c_str() );
        if (NULL == drv.handle)
            return ZE_RESULT_ERROR_UNINITIALIZED;

        auto zeGetGlobalProcAddrTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetGlobalProcAddrTable") );
        if (!zeGetGlobalProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetGlobalProcAddrTableResult = zeGetGlobalProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Global);
        if (zeGetGlobalProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetGlobalProcAddrTableResult;

        auto zeGetRTASBuilderExpProcAddrTable = reinterpret_cast<ze_pfnGetRTASBuilderExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetRTASBuilderExpProcAddrTable") );
        if (!zeGetRTASBuilderExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetRTASBuilderExpProcAddrTableResult = zeGetRTASBuilderExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.RTASBuilderExp);
        if (zeGetRTASBuilderExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetRTASBuilderExpProcAddrTableResult;

        auto zeGetRTASParallelOperationExpProcAddrTable = reinterpret_cast<ze_pfnGetRTASParallelOperationExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetRTASParallelOperationExpProcAddrTable") );
        if (!zeGetRTASParallelOperationExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetRTASParallelOperationExpProcAddrTableResult = zeGetRTASParallelOperationExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.RTASParallelOperationExp);
        if (zeGetRTASParallelOperationExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetRTASParallelOperationExpProcAddrTableResult;

        auto zeGetDriverProcAddrTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDriverProcAddrTable") );
        if (!zeGetDriverProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetDriverProcAddrTableResult = zeGetDriverProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Driver);
        if (zeGetDriverProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetDriverProcAddrTableResult;

        auto zeGetDriverExpProcAddrTable = reinterpret_cast<ze_pfnGetDriverExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDriverExpProcAddrTable") );
        if (!zeGetDriverExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetDriverExpProcAddrTableResult = zeGetDriverExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.DriverExp);
        if (zeGetDriverExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetDriverExpProcAddrTableResult;

        auto zeGetDeviceProcAddrTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDeviceProcAddrTable") );
        if (!zeGetDeviceProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetDeviceProcAddrTableResult = zeGetDeviceProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Device);
        if (zeGetDeviceProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetDeviceProcAddrTableResult;

        auto zeGetDeviceExpProcAddrTable = reinterpret_cast<ze_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDeviceExpProcAddrTable") );
        if (!zeGetDeviceExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetDeviceExpProcAddrTableResult = zeGetDeviceExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.DeviceExp);
        if (zeGetDeviceExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetDeviceExpProcAddrTableResult;

        auto zeGetContextProcAddrTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetContextProcAddrTable") );
        if (!zeGetContextProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetContextProcAddrTableResult = zeGetContextProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Context);
        if (zeGetContextProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetContextProcAddrTableResult;

        auto zeGetCommandQueueProcAddrTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetCommandQueueProcAddrTable") );
        if (!zeGetCommandQueueProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetCommandQueueProcAddrTableResult = zeGetCommandQueueProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.CommandQueue);
        if (zeGetCommandQueueProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetCommandQueueProcAddrTableResult;

        auto zeGetCommandListProcAddrTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetCommandListProcAddrTable") );
        if (!zeGetCommandListProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetCommandListProcAddrTableResult = zeGetCommandListProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.CommandList);
        if (zeGetCommandListProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetCommandListProcAddrTableResult;

        auto zeGetCommandListExpProcAddrTable = reinterpret_cast<ze_pfnGetCommandListExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetCommandListExpProcAddrTable") );
        if (!zeGetCommandListExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetCommandListExpProcAddrTableResult = zeGetCommandListExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.CommandListExp);
        if (zeGetCommandListExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetCommandListExpProcAddrTableResult;

        auto zeGetEventProcAddrTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetEventProcAddrTable") );
        if (!zeGetEventProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetEventProcAddrTableResult = zeGetEventProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Event);
        if (zeGetEventProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetEventProcAddrTableResult;

        auto zeGetEventExpProcAddrTable = reinterpret_cast<ze_pfnGetEventExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetEventExpProcAddrTable") );
        if (!zeGetEventExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetEventExpProcAddrTableResult = zeGetEventExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.EventExp);
        if (zeGetEventExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetEventExpProcAddrTableResult;

        auto zeGetEventPoolProcAddrTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetEventPoolProcAddrTable") );
        if (!zeGetEventPoolProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetEventPoolProcAddrTableResult = zeGetEventPoolProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.EventPool);
        if (zeGetEventPoolProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetEventPoolProcAddrTableResult;

        auto zeGetFenceProcAddrTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetFenceProcAddrTable") );
        if (!zeGetFenceProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetFenceProcAddrTableResult = zeGetFenceProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Fence);
        if (zeGetFenceProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetFenceProcAddrTableResult;

        auto zeGetImageProcAddrTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetImageProcAddrTable") );
        if (!zeGetImageProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetImageProcAddrTableResult = zeGetImageProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Image);
        if (zeGetImageProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetImageProcAddrTableResult;

        auto zeGetImageExpProcAddrTable = reinterpret_cast<ze_pfnGetImageExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetImageExpProcAddrTable") );
        if (!zeGetImageExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetImageExpProcAddrTableResult = zeGetImageExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.ImageExp);
        if (zeGetImageExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetImageExpProcAddrTableResult;

        auto zeGetKernelProcAddrTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetKernelProcAddrTable") );
        if (!zeGetKernelProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetKernelProcAddrTableResult = zeGetKernelProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Kernel);
        if (zeGetKernelProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetKernelProcAddrTableResult;

        auto zeGetKernelExpProcAddrTable = reinterpret_cast<ze_pfnGetKernelExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetKernelExpProcAddrTable") );
        if (!zeGetKernelExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetKernelExpProcAddrTableResult = zeGetKernelExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.KernelExp);
        if (zeGetKernelExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetKernelExpProcAddrTableResult;

        auto zeGetMemProcAddrTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetMemProcAddrTable") );
        if (!zeGetMemProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetMemProcAddrTableResult = zeGetMemProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Mem);
        if (zeGetMemProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetMemProcAddrTableResult;

        auto zeGetMemExpProcAddrTable = reinterpret_cast<ze_pfnGetMemExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetMemExpProcAddrTable") );
        if (!zeGetMemExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetMemExpProcAddrTableResult = zeGetMemExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.MemExp);
        if (zeGetMemExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetMemExpProcAddrTableResult;

        auto zeGetModuleProcAddrTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetModuleProcAddrTable") );
        if (!zeGetModuleProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetModuleProcAddrTableResult = zeGetModuleProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Module);
        if (zeGetModuleProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetModuleProcAddrTableResult;

        auto zeGetModuleBuildLogProcAddrTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetModuleBuildLogProcAddrTable") );
        if (!zeGetModuleBuildLogProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetModuleBuildLogProcAddrTableResult = zeGetModuleBuildLogProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.ModuleBuildLog);
        if (zeGetModuleBuildLogProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetModuleBuildLogProcAddrTableResult;

        auto zeGetPhysicalMemProcAddrTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetPhysicalMemProcAddrTable") );
        if (!zeGetPhysicalMemProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetPhysicalMemProcAddrTableResult = zeGetPhysicalMemProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.PhysicalMem);
        if (zeGetPhysicalMemProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetPhysicalMemProcAddrTableResult;

        auto zeGetSamplerProcAddrTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetSamplerProcAddrTable") );
        if (!zeGetSamplerProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetSamplerProcAddrTableResult = zeGetSamplerProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.Sampler);
        if (zeGetSamplerProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetSamplerProcAddrTableResult;

        auto zeGetVirtualMemProcAddrTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetVirtualMemProcAddrTable") );
        if (!zeGetVirtualMemProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetVirtualMemProcAddrTableResult = zeGetVirtualMemProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.VirtualMem);
        if (zeGetVirtualMemProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetVirtualMemProcAddrTableResult;

        auto zeGetFabricEdgeExpProcAddrTable = reinterpret_cast<ze_pfnGetFabricEdgeExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetFabricEdgeExpProcAddrTable") );
        if (!zeGetFabricEdgeExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetFabricEdgeExpProcAddrTableResult = zeGetFabricEdgeExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.FabricEdgeExp);
        if (zeGetFabricEdgeExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetFabricEdgeExpProcAddrTableResult;

        auto zeGetFabricVertexExpProcAddrTable = reinterpret_cast<ze_pfnGetFabricVertexExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetFabricVertexExpProcAddrTable") );
        if (!zeGetFabricVertexExpProcAddrTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        auto zeGetFabricVertexExpProcAddrTableResult = zeGetFabricVertexExpProcAddrTable(ZE_API_VERSION_CURRENT, &drv.dditable.ze.FabricVertexExp);
        if (zeGetFabricVertexExpProcAddrTableResult != ZE_RESULT_SUCCESS)
            return zeGetFabricVertexExpProcAddrTableResult;

        auto initResult = drv.dditable.ze.Global.pfnInit(flags);
        // Bail out if any drivers that previously succeeded fail
        if (initResult != ZE_RESULT_SUCCESS)
            return initResult;
    }

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