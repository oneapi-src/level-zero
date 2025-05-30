/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_libddi.cpp
 *
 */
#include "ze_lib.h"
#ifndef L0_STATIC_LOADER_BUILD
#include "ze_ddi.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef L0_STATIC_LOADER_BUILD
    __zedlllocal ze_result_t context_t::zeDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetGlobalProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Global );
            initialzeDdiTable.Global.pfnInit = reinterpret_cast<ze_pfnInit_t>(
                GET_FUNCTION_PTR(loader, "zeInit") );
            initialzeDdiTable.Global.pfnInitDrivers = reinterpret_cast<ze_pfnInitDrivers_t>(
                GET_FUNCTION_PTR(loader, "zeInitDrivers") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetRTASBuilderProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASBuilderProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.RTASBuilder );
            initialzeDdiTable.RTASBuilder.pfnCreateExt = reinterpret_cast<ze_pfnRTASBuilderCreateExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderCreateExt") );
            initialzeDdiTable.RTASBuilder.pfnGetBuildPropertiesExt = reinterpret_cast<ze_pfnRTASBuilderGetBuildPropertiesExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderGetBuildPropertiesExt") );
            initialzeDdiTable.RTASBuilder.pfnBuildExt = reinterpret_cast<ze_pfnRTASBuilderBuildExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderBuildExt") );
            initialzeDdiTable.RTASBuilder.pfnCommandListAppendCopyExt = reinterpret_cast<ze_pfnRTASBuilderCommandListAppendCopyExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderCommandListAppendCopyExt") );
            initialzeDdiTable.RTASBuilder.pfnDestroyExt = reinterpret_cast<ze_pfnRTASBuilderDestroyExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderDestroyExt") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetRTASBuilderExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASBuilderExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.RTASBuilderExp );
            initialzeDdiTable.RTASBuilderExp.pfnCreateExp = reinterpret_cast<ze_pfnRTASBuilderCreateExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderCreateExp") );
            initialzeDdiTable.RTASBuilderExp.pfnGetBuildPropertiesExp = reinterpret_cast<ze_pfnRTASBuilderGetBuildPropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderGetBuildPropertiesExp") );
            initialzeDdiTable.RTASBuilderExp.pfnBuildExp = reinterpret_cast<ze_pfnRTASBuilderBuildExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderBuildExp") );
            initialzeDdiTable.RTASBuilderExp.pfnDestroyExp = reinterpret_cast<ze_pfnRTASBuilderDestroyExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASBuilderDestroyExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetRTASParallelOperationProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASParallelOperationProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.RTASParallelOperation );
            initialzeDdiTable.RTASParallelOperation.pfnCreateExt = reinterpret_cast<ze_pfnRTASParallelOperationCreateExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationCreateExt") );
            initialzeDdiTable.RTASParallelOperation.pfnGetPropertiesExt = reinterpret_cast<ze_pfnRTASParallelOperationGetPropertiesExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationGetPropertiesExt") );
            initialzeDdiTable.RTASParallelOperation.pfnJoinExt = reinterpret_cast<ze_pfnRTASParallelOperationJoinExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationJoinExt") );
            initialzeDdiTable.RTASParallelOperation.pfnDestroyExt = reinterpret_cast<ze_pfnRTASParallelOperationDestroyExt_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationDestroyExt") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetRTASParallelOperationExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASParallelOperationExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.RTASParallelOperationExp );
            initialzeDdiTable.RTASParallelOperationExp.pfnCreateExp = reinterpret_cast<ze_pfnRTASParallelOperationCreateExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationCreateExp") );
            initialzeDdiTable.RTASParallelOperationExp.pfnGetPropertiesExp = reinterpret_cast<ze_pfnRTASParallelOperationGetPropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationGetPropertiesExp") );
            initialzeDdiTable.RTASParallelOperationExp.pfnJoinExp = reinterpret_cast<ze_pfnRTASParallelOperationJoinExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationJoinExp") );
            initialzeDdiTable.RTASParallelOperationExp.pfnDestroyExp = reinterpret_cast<ze_pfnRTASParallelOperationDestroyExp_t>(
                GET_FUNCTION_PTR(loader, "zeRTASParallelOperationDestroyExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDriverProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Driver );
            initialzeDdiTable.Driver.pfnGet = reinterpret_cast<ze_pfnDriverGet_t>(
                GET_FUNCTION_PTR(loader, "zeDriverGet") );
            initialzeDdiTable.Driver.pfnGetApiVersion = reinterpret_cast<ze_pfnDriverGetApiVersion_t>(
                GET_FUNCTION_PTR(loader, "zeDriverGetApiVersion") );
            initialzeDdiTable.Driver.pfnGetProperties = reinterpret_cast<ze_pfnDriverGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDriverGetProperties") );
            initialzeDdiTable.Driver.pfnGetIpcProperties = reinterpret_cast<ze_pfnDriverGetIpcProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDriverGetIpcProperties") );
            initialzeDdiTable.Driver.pfnGetExtensionProperties = reinterpret_cast<ze_pfnDriverGetExtensionProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDriverGetExtensionProperties") );
            initialzeDdiTable.Driver.pfnGetExtensionFunctionAddress = reinterpret_cast<ze_pfnDriverGetExtensionFunctionAddress_t>(
                GET_FUNCTION_PTR(loader, "zeDriverGetExtensionFunctionAddress") );
            initialzeDdiTable.Driver.pfnRTASFormatCompatibilityCheckExt = reinterpret_cast<ze_pfnDriverRTASFormatCompatibilityCheckExt_t>(
                GET_FUNCTION_PTR(loader, "zeDriverRTASFormatCompatibilityCheckExt") );
            initialzeDdiTable.Driver.pfnGetLastErrorDescription = reinterpret_cast<ze_pfnDriverGetLastErrorDescription_t>(
                GET_FUNCTION_PTR(loader, "zeDriverGetLastErrorDescription") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetDriverExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDriverExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.DriverExp );
            initialzeDdiTable.DriverExp.pfnRTASFormatCompatibilityCheckExp = reinterpret_cast<ze_pfnDriverRTASFormatCompatibilityCheckExp_t>(
                GET_FUNCTION_PTR(loader, "zeDriverRTASFormatCompatibilityCheckExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDeviceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Device );
            initialzeDdiTable.Device.pfnGet = reinterpret_cast<ze_pfnDeviceGet_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGet") );
            initialzeDdiTable.Device.pfnGetSubDevices = reinterpret_cast<ze_pfnDeviceGetSubDevices_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetSubDevices") );
            initialzeDdiTable.Device.pfnGetProperties = reinterpret_cast<ze_pfnDeviceGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetProperties") );
            initialzeDdiTable.Device.pfnGetComputeProperties = reinterpret_cast<ze_pfnDeviceGetComputeProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetComputeProperties") );
            initialzeDdiTable.Device.pfnGetModuleProperties = reinterpret_cast<ze_pfnDeviceGetModuleProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetModuleProperties") );
            initialzeDdiTable.Device.pfnGetCommandQueueGroupProperties = reinterpret_cast<ze_pfnDeviceGetCommandQueueGroupProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetCommandQueueGroupProperties") );
            initialzeDdiTable.Device.pfnGetMemoryProperties = reinterpret_cast<ze_pfnDeviceGetMemoryProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetMemoryProperties") );
            initialzeDdiTable.Device.pfnGetMemoryAccessProperties = reinterpret_cast<ze_pfnDeviceGetMemoryAccessProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetMemoryAccessProperties") );
            initialzeDdiTable.Device.pfnGetCacheProperties = reinterpret_cast<ze_pfnDeviceGetCacheProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetCacheProperties") );
            initialzeDdiTable.Device.pfnGetImageProperties = reinterpret_cast<ze_pfnDeviceGetImageProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetImageProperties") );
            initialzeDdiTable.Device.pfnGetExternalMemoryProperties = reinterpret_cast<ze_pfnDeviceGetExternalMemoryProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetExternalMemoryProperties") );
            initialzeDdiTable.Device.pfnGetP2PProperties = reinterpret_cast<ze_pfnDeviceGetP2PProperties_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetP2PProperties") );
            initialzeDdiTable.Device.pfnCanAccessPeer = reinterpret_cast<ze_pfnDeviceCanAccessPeer_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceCanAccessPeer") );
            initialzeDdiTable.Device.pfnGetStatus = reinterpret_cast<ze_pfnDeviceGetStatus_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetStatus") );
            initialzeDdiTable.Device.pfnGetGlobalTimestamps = reinterpret_cast<ze_pfnDeviceGetGlobalTimestamps_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetGlobalTimestamps") );
            initialzeDdiTable.Device.pfnImportExternalSemaphoreExt = reinterpret_cast<ze_pfnDeviceImportExternalSemaphoreExt_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceImportExternalSemaphoreExt") );
            initialzeDdiTable.Device.pfnReleaseExternalSemaphoreExt = reinterpret_cast<ze_pfnDeviceReleaseExternalSemaphoreExt_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceReleaseExternalSemaphoreExt") );
            initialzeDdiTable.Device.pfnGetVectorWidthPropertiesExt = reinterpret_cast<ze_pfnDeviceGetVectorWidthPropertiesExt_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetVectorWidthPropertiesExt") );
            initialzeDdiTable.Device.pfnReserveCacheExt = reinterpret_cast<ze_pfnDeviceReserveCacheExt_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceReserveCacheExt") );
            initialzeDdiTable.Device.pfnSetCacheAdviceExt = reinterpret_cast<ze_pfnDeviceSetCacheAdviceExt_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceSetCacheAdviceExt") );
            initialzeDdiTable.Device.pfnPciGetPropertiesExt = reinterpret_cast<ze_pfnDevicePciGetPropertiesExt_t>(
                GET_FUNCTION_PTR(loader, "zeDevicePciGetPropertiesExt") );
            initialzeDdiTable.Device.pfnGetRootDevice = reinterpret_cast<ze_pfnDeviceGetRootDevice_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetRootDevice") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDeviceExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.DeviceExp );
            initialzeDdiTable.DeviceExp.pfnGetFabricVertexExp = reinterpret_cast<ze_pfnDeviceGetFabricVertexExp_t>(
                GET_FUNCTION_PTR(loader, "zeDeviceGetFabricVertexExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetContextProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Context );
            initialzeDdiTable.Context.pfnCreate = reinterpret_cast<ze_pfnContextCreate_t>(
                GET_FUNCTION_PTR(loader, "zeContextCreate") );
            initialzeDdiTable.Context.pfnDestroy = reinterpret_cast<ze_pfnContextDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeContextDestroy") );
            initialzeDdiTable.Context.pfnGetStatus = reinterpret_cast<ze_pfnContextGetStatus_t>(
                GET_FUNCTION_PTR(loader, "zeContextGetStatus") );
            initialzeDdiTable.Context.pfnSystemBarrier = reinterpret_cast<ze_pfnContextSystemBarrier_t>(
                GET_FUNCTION_PTR(loader, "zeContextSystemBarrier") );
            initialzeDdiTable.Context.pfnMakeMemoryResident = reinterpret_cast<ze_pfnContextMakeMemoryResident_t>(
                GET_FUNCTION_PTR(loader, "zeContextMakeMemoryResident") );
            initialzeDdiTable.Context.pfnEvictMemory = reinterpret_cast<ze_pfnContextEvictMemory_t>(
                GET_FUNCTION_PTR(loader, "zeContextEvictMemory") );
            initialzeDdiTable.Context.pfnMakeImageResident = reinterpret_cast<ze_pfnContextMakeImageResident_t>(
                GET_FUNCTION_PTR(loader, "zeContextMakeImageResident") );
            initialzeDdiTable.Context.pfnEvictImage = reinterpret_cast<ze_pfnContextEvictImage_t>(
                GET_FUNCTION_PTR(loader, "zeContextEvictImage") );
            initialzeDdiTable.Context.pfnCreateEx = reinterpret_cast<ze_pfnContextCreateEx_t>(
                GET_FUNCTION_PTR(loader, "zeContextCreateEx") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandQueueProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.CommandQueue );
            initialzeDdiTable.CommandQueue.pfnCreate = reinterpret_cast<ze_pfnCommandQueueCreate_t>(
                GET_FUNCTION_PTR(loader, "zeCommandQueueCreate") );
            initialzeDdiTable.CommandQueue.pfnDestroy = reinterpret_cast<ze_pfnCommandQueueDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeCommandQueueDestroy") );
            initialzeDdiTable.CommandQueue.pfnExecuteCommandLists = reinterpret_cast<ze_pfnCommandQueueExecuteCommandLists_t>(
                GET_FUNCTION_PTR(loader, "zeCommandQueueExecuteCommandLists") );
            initialzeDdiTable.CommandQueue.pfnSynchronize = reinterpret_cast<ze_pfnCommandQueueSynchronize_t>(
                GET_FUNCTION_PTR(loader, "zeCommandQueueSynchronize") );
            initialzeDdiTable.CommandQueue.pfnGetOrdinal = reinterpret_cast<ze_pfnCommandQueueGetOrdinal_t>(
                GET_FUNCTION_PTR(loader, "zeCommandQueueGetOrdinal") );
            initialzeDdiTable.CommandQueue.pfnGetIndex = reinterpret_cast<ze_pfnCommandQueueGetIndex_t>(
                GET_FUNCTION_PTR(loader, "zeCommandQueueGetIndex") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandListProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.CommandList );
            initialzeDdiTable.CommandList.pfnCreate = reinterpret_cast<ze_pfnCommandListCreate_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListCreate") );
            initialzeDdiTable.CommandList.pfnCreateImmediate = reinterpret_cast<ze_pfnCommandListCreateImmediate_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListCreateImmediate") );
            initialzeDdiTable.CommandList.pfnDestroy = reinterpret_cast<ze_pfnCommandListDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListDestroy") );
            initialzeDdiTable.CommandList.pfnClose = reinterpret_cast<ze_pfnCommandListClose_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListClose") );
            initialzeDdiTable.CommandList.pfnReset = reinterpret_cast<ze_pfnCommandListReset_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListReset") );
            initialzeDdiTable.CommandList.pfnAppendWriteGlobalTimestamp = reinterpret_cast<ze_pfnCommandListAppendWriteGlobalTimestamp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendWriteGlobalTimestamp") );
            initialzeDdiTable.CommandList.pfnAppendBarrier = reinterpret_cast<ze_pfnCommandListAppendBarrier_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendBarrier") );
            initialzeDdiTable.CommandList.pfnAppendMemoryRangesBarrier = reinterpret_cast<ze_pfnCommandListAppendMemoryRangesBarrier_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendMemoryRangesBarrier") );
            initialzeDdiTable.CommandList.pfnAppendMemoryCopy = reinterpret_cast<ze_pfnCommandListAppendMemoryCopy_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendMemoryCopy") );
            initialzeDdiTable.CommandList.pfnAppendMemoryFill = reinterpret_cast<ze_pfnCommandListAppendMemoryFill_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendMemoryFill") );
            initialzeDdiTable.CommandList.pfnAppendMemoryCopyRegion = reinterpret_cast<ze_pfnCommandListAppendMemoryCopyRegion_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendMemoryCopyRegion") );
            initialzeDdiTable.CommandList.pfnAppendMemoryCopyFromContext = reinterpret_cast<ze_pfnCommandListAppendMemoryCopyFromContext_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendMemoryCopyFromContext") );
            initialzeDdiTable.CommandList.pfnAppendImageCopy = reinterpret_cast<ze_pfnCommandListAppendImageCopy_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendImageCopy") );
            initialzeDdiTable.CommandList.pfnAppendImageCopyRegion = reinterpret_cast<ze_pfnCommandListAppendImageCopyRegion_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendImageCopyRegion") );
            initialzeDdiTable.CommandList.pfnAppendImageCopyToMemory = reinterpret_cast<ze_pfnCommandListAppendImageCopyToMemory_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendImageCopyToMemory") );
            initialzeDdiTable.CommandList.pfnAppendImageCopyFromMemory = reinterpret_cast<ze_pfnCommandListAppendImageCopyFromMemory_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendImageCopyFromMemory") );
            initialzeDdiTable.CommandList.pfnAppendMemoryPrefetch = reinterpret_cast<ze_pfnCommandListAppendMemoryPrefetch_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendMemoryPrefetch") );
            initialzeDdiTable.CommandList.pfnAppendMemAdvise = reinterpret_cast<ze_pfnCommandListAppendMemAdvise_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendMemAdvise") );
            initialzeDdiTable.CommandList.pfnAppendSignalEvent = reinterpret_cast<ze_pfnCommandListAppendSignalEvent_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendSignalEvent") );
            initialzeDdiTable.CommandList.pfnAppendWaitOnEvents = reinterpret_cast<ze_pfnCommandListAppendWaitOnEvents_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendWaitOnEvents") );
            initialzeDdiTable.CommandList.pfnAppendEventReset = reinterpret_cast<ze_pfnCommandListAppendEventReset_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendEventReset") );
            initialzeDdiTable.CommandList.pfnAppendQueryKernelTimestamps = reinterpret_cast<ze_pfnCommandListAppendQueryKernelTimestamps_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendQueryKernelTimestamps") );
            initialzeDdiTable.CommandList.pfnAppendLaunchKernel = reinterpret_cast<ze_pfnCommandListAppendLaunchKernel_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendLaunchKernel") );
            initialzeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel = reinterpret_cast<ze_pfnCommandListAppendLaunchCooperativeKernel_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendLaunchCooperativeKernel") );
            initialzeDdiTable.CommandList.pfnAppendLaunchKernelIndirect = reinterpret_cast<ze_pfnCommandListAppendLaunchKernelIndirect_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendLaunchKernelIndirect") );
            initialzeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect = reinterpret_cast<ze_pfnCommandListAppendLaunchMultipleKernelsIndirect_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendLaunchMultipleKernelsIndirect") );
            initialzeDdiTable.CommandList.pfnAppendSignalExternalSemaphoreExt = reinterpret_cast<ze_pfnCommandListAppendSignalExternalSemaphoreExt_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendSignalExternalSemaphoreExt") );
            initialzeDdiTable.CommandList.pfnAppendWaitExternalSemaphoreExt = reinterpret_cast<ze_pfnCommandListAppendWaitExternalSemaphoreExt_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendWaitExternalSemaphoreExt") );
            initialzeDdiTable.CommandList.pfnAppendImageCopyToMemoryExt = reinterpret_cast<ze_pfnCommandListAppendImageCopyToMemoryExt_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendImageCopyToMemoryExt") );
            initialzeDdiTable.CommandList.pfnAppendImageCopyFromMemoryExt = reinterpret_cast<ze_pfnCommandListAppendImageCopyFromMemoryExt_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListAppendImageCopyFromMemoryExt") );
            initialzeDdiTable.CommandList.pfnHostSynchronize = reinterpret_cast<ze_pfnCommandListHostSynchronize_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListHostSynchronize") );
            initialzeDdiTable.CommandList.pfnGetDeviceHandle = reinterpret_cast<ze_pfnCommandListGetDeviceHandle_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListGetDeviceHandle") );
            initialzeDdiTable.CommandList.pfnGetContextHandle = reinterpret_cast<ze_pfnCommandListGetContextHandle_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListGetContextHandle") );
            initialzeDdiTable.CommandList.pfnGetOrdinal = reinterpret_cast<ze_pfnCommandListGetOrdinal_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListGetOrdinal") );
            initialzeDdiTable.CommandList.pfnImmediateGetIndex = reinterpret_cast<ze_pfnCommandListImmediateGetIndex_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListImmediateGetIndex") );
            initialzeDdiTable.CommandList.pfnIsImmediate = reinterpret_cast<ze_pfnCommandListIsImmediate_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListIsImmediate") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetCommandListExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandListExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.CommandListExp );
            initialzeDdiTable.CommandListExp.pfnGetNextCommandIdWithKernelsExp = reinterpret_cast<ze_pfnCommandListGetNextCommandIdWithKernelsExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListGetNextCommandIdWithKernelsExp") );
            initialzeDdiTable.CommandListExp.pfnUpdateMutableCommandKernelsExp = reinterpret_cast<ze_pfnCommandListUpdateMutableCommandKernelsExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListUpdateMutableCommandKernelsExp") );
            initialzeDdiTable.CommandListExp.pfnCreateCloneExp = reinterpret_cast<ze_pfnCommandListCreateCloneExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListCreateCloneExp") );
            initialzeDdiTable.CommandListExp.pfnImmediateAppendCommandListsExp = reinterpret_cast<ze_pfnCommandListImmediateAppendCommandListsExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListImmediateAppendCommandListsExp") );
            initialzeDdiTable.CommandListExp.pfnGetNextCommandIdExp = reinterpret_cast<ze_pfnCommandListGetNextCommandIdExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListGetNextCommandIdExp") );
            initialzeDdiTable.CommandListExp.pfnUpdateMutableCommandsExp = reinterpret_cast<ze_pfnCommandListUpdateMutableCommandsExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListUpdateMutableCommandsExp") );
            initialzeDdiTable.CommandListExp.pfnUpdateMutableCommandSignalEventExp = reinterpret_cast<ze_pfnCommandListUpdateMutableCommandSignalEventExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListUpdateMutableCommandSignalEventExp") );
            initialzeDdiTable.CommandListExp.pfnUpdateMutableCommandWaitEventsExp = reinterpret_cast<ze_pfnCommandListUpdateMutableCommandWaitEventsExp_t>(
                GET_FUNCTION_PTR(loader, "zeCommandListUpdateMutableCommandWaitEventsExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Event );
            initialzeDdiTable.Event.pfnCreate = reinterpret_cast<ze_pfnEventCreate_t>(
                GET_FUNCTION_PTR(loader, "zeEventCreate") );
            initialzeDdiTable.Event.pfnDestroy = reinterpret_cast<ze_pfnEventDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeEventDestroy") );
            initialzeDdiTable.Event.pfnHostSignal = reinterpret_cast<ze_pfnEventHostSignal_t>(
                GET_FUNCTION_PTR(loader, "zeEventHostSignal") );
            initialzeDdiTable.Event.pfnHostSynchronize = reinterpret_cast<ze_pfnEventHostSynchronize_t>(
                GET_FUNCTION_PTR(loader, "zeEventHostSynchronize") );
            initialzeDdiTable.Event.pfnQueryStatus = reinterpret_cast<ze_pfnEventQueryStatus_t>(
                GET_FUNCTION_PTR(loader, "zeEventQueryStatus") );
            initialzeDdiTable.Event.pfnHostReset = reinterpret_cast<ze_pfnEventHostReset_t>(
                GET_FUNCTION_PTR(loader, "zeEventHostReset") );
            initialzeDdiTable.Event.pfnQueryKernelTimestamp = reinterpret_cast<ze_pfnEventQueryKernelTimestamp_t>(
                GET_FUNCTION_PTR(loader, "zeEventQueryKernelTimestamp") );
            initialzeDdiTable.Event.pfnQueryKernelTimestampsExt = reinterpret_cast<ze_pfnEventQueryKernelTimestampsExt_t>(
                GET_FUNCTION_PTR(loader, "zeEventQueryKernelTimestampsExt") );
            initialzeDdiTable.Event.pfnGetEventPool = reinterpret_cast<ze_pfnEventGetEventPool_t>(
                GET_FUNCTION_PTR(loader, "zeEventGetEventPool") );
            initialzeDdiTable.Event.pfnGetSignalScope = reinterpret_cast<ze_pfnEventGetSignalScope_t>(
                GET_FUNCTION_PTR(loader, "zeEventGetSignalScope") );
            initialzeDdiTable.Event.pfnGetWaitScope = reinterpret_cast<ze_pfnEventGetWaitScope_t>(
                GET_FUNCTION_PTR(loader, "zeEventGetWaitScope") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetEventExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.EventExp );
            initialzeDdiTable.EventExp.pfnQueryTimestampsExp = reinterpret_cast<ze_pfnEventQueryTimestampsExp_t>(
                GET_FUNCTION_PTR(loader, "zeEventQueryTimestampsExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventPoolProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.EventPool );
            initialzeDdiTable.EventPool.pfnCreate = reinterpret_cast<ze_pfnEventPoolCreate_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolCreate") );
            initialzeDdiTable.EventPool.pfnDestroy = reinterpret_cast<ze_pfnEventPoolDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolDestroy") );
            initialzeDdiTable.EventPool.pfnGetIpcHandle = reinterpret_cast<ze_pfnEventPoolGetIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolGetIpcHandle") );
            initialzeDdiTable.EventPool.pfnOpenIpcHandle = reinterpret_cast<ze_pfnEventPoolOpenIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolOpenIpcHandle") );
            initialzeDdiTable.EventPool.pfnCloseIpcHandle = reinterpret_cast<ze_pfnEventPoolCloseIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolCloseIpcHandle") );
            initialzeDdiTable.EventPool.pfnPutIpcHandle = reinterpret_cast<ze_pfnEventPoolPutIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolPutIpcHandle") );
            initialzeDdiTable.EventPool.pfnGetContextHandle = reinterpret_cast<ze_pfnEventPoolGetContextHandle_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolGetContextHandle") );
            initialzeDdiTable.EventPool.pfnGetFlags = reinterpret_cast<ze_pfnEventPoolGetFlags_t>(
                GET_FUNCTION_PTR(loader, "zeEventPoolGetFlags") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFenceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Fence );
            initialzeDdiTable.Fence.pfnCreate = reinterpret_cast<ze_pfnFenceCreate_t>(
                GET_FUNCTION_PTR(loader, "zeFenceCreate") );
            initialzeDdiTable.Fence.pfnDestroy = reinterpret_cast<ze_pfnFenceDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeFenceDestroy") );
            initialzeDdiTable.Fence.pfnHostSynchronize = reinterpret_cast<ze_pfnFenceHostSynchronize_t>(
                GET_FUNCTION_PTR(loader, "zeFenceHostSynchronize") );
            initialzeDdiTable.Fence.pfnQueryStatus = reinterpret_cast<ze_pfnFenceQueryStatus_t>(
                GET_FUNCTION_PTR(loader, "zeFenceQueryStatus") );
            initialzeDdiTable.Fence.pfnReset = reinterpret_cast<ze_pfnFenceReset_t>(
                GET_FUNCTION_PTR(loader, "zeFenceReset") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetImageProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Image );
            initialzeDdiTable.Image.pfnGetProperties = reinterpret_cast<ze_pfnImageGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zeImageGetProperties") );
            initialzeDdiTable.Image.pfnCreate = reinterpret_cast<ze_pfnImageCreate_t>(
                GET_FUNCTION_PTR(loader, "zeImageCreate") );
            initialzeDdiTable.Image.pfnDestroy = reinterpret_cast<ze_pfnImageDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeImageDestroy") );
            initialzeDdiTable.Image.pfnGetAllocPropertiesExt = reinterpret_cast<ze_pfnImageGetAllocPropertiesExt_t>(
                GET_FUNCTION_PTR(loader, "zeImageGetAllocPropertiesExt") );
            initialzeDdiTable.Image.pfnViewCreateExt = reinterpret_cast<ze_pfnImageViewCreateExt_t>(
                GET_FUNCTION_PTR(loader, "zeImageViewCreateExt") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetImageExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetImageExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.ImageExp );
            initialzeDdiTable.ImageExp.pfnGetMemoryPropertiesExp = reinterpret_cast<ze_pfnImageGetMemoryPropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zeImageGetMemoryPropertiesExp") );
            initialzeDdiTable.ImageExp.pfnViewCreateExp = reinterpret_cast<ze_pfnImageViewCreateExp_t>(
                GET_FUNCTION_PTR(loader, "zeImageViewCreateExp") );
            initialzeDdiTable.ImageExp.pfnGetDeviceOffsetExp = reinterpret_cast<ze_pfnImageGetDeviceOffsetExp_t>(
                GET_FUNCTION_PTR(loader, "zeImageGetDeviceOffsetExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetKernelProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Kernel );
            initialzeDdiTable.Kernel.pfnCreate = reinterpret_cast<ze_pfnKernelCreate_t>(
                GET_FUNCTION_PTR(loader, "zeKernelCreate") );
            initialzeDdiTable.Kernel.pfnDestroy = reinterpret_cast<ze_pfnKernelDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeKernelDestroy") );
            initialzeDdiTable.Kernel.pfnSetCacheConfig = reinterpret_cast<ze_pfnKernelSetCacheConfig_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSetCacheConfig") );
            initialzeDdiTable.Kernel.pfnSetGroupSize = reinterpret_cast<ze_pfnKernelSetGroupSize_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSetGroupSize") );
            initialzeDdiTable.Kernel.pfnSuggestGroupSize = reinterpret_cast<ze_pfnKernelSuggestGroupSize_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSuggestGroupSize") );
            initialzeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount = reinterpret_cast<ze_pfnKernelSuggestMaxCooperativeGroupCount_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSuggestMaxCooperativeGroupCount") );
            initialzeDdiTable.Kernel.pfnSetArgumentValue = reinterpret_cast<ze_pfnKernelSetArgumentValue_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSetArgumentValue") );
            initialzeDdiTable.Kernel.pfnSetIndirectAccess = reinterpret_cast<ze_pfnKernelSetIndirectAccess_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSetIndirectAccess") );
            initialzeDdiTable.Kernel.pfnGetIndirectAccess = reinterpret_cast<ze_pfnKernelGetIndirectAccess_t>(
                GET_FUNCTION_PTR(loader, "zeKernelGetIndirectAccess") );
            initialzeDdiTable.Kernel.pfnGetSourceAttributes = reinterpret_cast<ze_pfnKernelGetSourceAttributes_t>(
                GET_FUNCTION_PTR(loader, "zeKernelGetSourceAttributes") );
            initialzeDdiTable.Kernel.pfnGetProperties = reinterpret_cast<ze_pfnKernelGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zeKernelGetProperties") );
            initialzeDdiTable.Kernel.pfnGetName = reinterpret_cast<ze_pfnKernelGetName_t>(
                GET_FUNCTION_PTR(loader, "zeKernelGetName") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetKernelExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetKernelExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.KernelExp );
            initialzeDdiTable.KernelExp.pfnSetGlobalOffsetExp = reinterpret_cast<ze_pfnKernelSetGlobalOffsetExp_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSetGlobalOffsetExp") );
            initialzeDdiTable.KernelExp.pfnGetBinaryExp = reinterpret_cast<ze_pfnKernelGetBinaryExp_t>(
                GET_FUNCTION_PTR(loader, "zeKernelGetBinaryExp") );
            initialzeDdiTable.KernelExp.pfnSchedulingHintExp = reinterpret_cast<ze_pfnKernelSchedulingHintExp_t>(
                GET_FUNCTION_PTR(loader, "zeKernelSchedulingHintExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetMemProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Mem );
            initialzeDdiTable.Mem.pfnAllocShared = reinterpret_cast<ze_pfnMemAllocShared_t>(
                GET_FUNCTION_PTR(loader, "zeMemAllocShared") );
            initialzeDdiTable.Mem.pfnAllocDevice = reinterpret_cast<ze_pfnMemAllocDevice_t>(
                GET_FUNCTION_PTR(loader, "zeMemAllocDevice") );
            initialzeDdiTable.Mem.pfnAllocHost = reinterpret_cast<ze_pfnMemAllocHost_t>(
                GET_FUNCTION_PTR(loader, "zeMemAllocHost") );
            initialzeDdiTable.Mem.pfnFree = reinterpret_cast<ze_pfnMemFree_t>(
                GET_FUNCTION_PTR(loader, "zeMemFree") );
            initialzeDdiTable.Mem.pfnGetAllocProperties = reinterpret_cast<ze_pfnMemGetAllocProperties_t>(
                GET_FUNCTION_PTR(loader, "zeMemGetAllocProperties") );
            initialzeDdiTable.Mem.pfnGetAddressRange = reinterpret_cast<ze_pfnMemGetAddressRange_t>(
                GET_FUNCTION_PTR(loader, "zeMemGetAddressRange") );
            initialzeDdiTable.Mem.pfnGetIpcHandle = reinterpret_cast<ze_pfnMemGetIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeMemGetIpcHandle") );
            initialzeDdiTable.Mem.pfnOpenIpcHandle = reinterpret_cast<ze_pfnMemOpenIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeMemOpenIpcHandle") );
            initialzeDdiTable.Mem.pfnCloseIpcHandle = reinterpret_cast<ze_pfnMemCloseIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeMemCloseIpcHandle") );
            initialzeDdiTable.Mem.pfnFreeExt = reinterpret_cast<ze_pfnMemFreeExt_t>(
                GET_FUNCTION_PTR(loader, "zeMemFreeExt") );
            initialzeDdiTable.Mem.pfnPutIpcHandle = reinterpret_cast<ze_pfnMemPutIpcHandle_t>(
                GET_FUNCTION_PTR(loader, "zeMemPutIpcHandle") );
            initialzeDdiTable.Mem.pfnGetPitchFor2dImage = reinterpret_cast<ze_pfnMemGetPitchFor2dImage_t>(
                GET_FUNCTION_PTR(loader, "zeMemGetPitchFor2dImage") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetMemExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetMemExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.MemExp );
            initialzeDdiTable.MemExp.pfnGetIpcHandleFromFileDescriptorExp = reinterpret_cast<ze_pfnMemGetIpcHandleFromFileDescriptorExp_t>(
                GET_FUNCTION_PTR(loader, "zeMemGetIpcHandleFromFileDescriptorExp") );
            initialzeDdiTable.MemExp.pfnGetFileDescriptorFromIpcHandleExp = reinterpret_cast<ze_pfnMemGetFileDescriptorFromIpcHandleExp_t>(
                GET_FUNCTION_PTR(loader, "zeMemGetFileDescriptorFromIpcHandleExp") );
            initialzeDdiTable.MemExp.pfnSetAtomicAccessAttributeExp = reinterpret_cast<ze_pfnMemSetAtomicAccessAttributeExp_t>(
                GET_FUNCTION_PTR(loader, "zeMemSetAtomicAccessAttributeExp") );
            initialzeDdiTable.MemExp.pfnGetAtomicAccessAttributeExp = reinterpret_cast<ze_pfnMemGetAtomicAccessAttributeExp_t>(
                GET_FUNCTION_PTR(loader, "zeMemGetAtomicAccessAttributeExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Module );
            initialzeDdiTable.Module.pfnCreate = reinterpret_cast<ze_pfnModuleCreate_t>(
                GET_FUNCTION_PTR(loader, "zeModuleCreate") );
            initialzeDdiTable.Module.pfnDestroy = reinterpret_cast<ze_pfnModuleDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeModuleDestroy") );
            initialzeDdiTable.Module.pfnDynamicLink = reinterpret_cast<ze_pfnModuleDynamicLink_t>(
                GET_FUNCTION_PTR(loader, "zeModuleDynamicLink") );
            initialzeDdiTable.Module.pfnGetNativeBinary = reinterpret_cast<ze_pfnModuleGetNativeBinary_t>(
                GET_FUNCTION_PTR(loader, "zeModuleGetNativeBinary") );
            initialzeDdiTable.Module.pfnGetGlobalPointer = reinterpret_cast<ze_pfnModuleGetGlobalPointer_t>(
                GET_FUNCTION_PTR(loader, "zeModuleGetGlobalPointer") );
            initialzeDdiTable.Module.pfnGetKernelNames = reinterpret_cast<ze_pfnModuleGetKernelNames_t>(
                GET_FUNCTION_PTR(loader, "zeModuleGetKernelNames") );
            initialzeDdiTable.Module.pfnGetProperties = reinterpret_cast<ze_pfnModuleGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zeModuleGetProperties") );
            initialzeDdiTable.Module.pfnGetFunctionPointer = reinterpret_cast<ze_pfnModuleGetFunctionPointer_t>(
                GET_FUNCTION_PTR(loader, "zeModuleGetFunctionPointer") );
            initialzeDdiTable.Module.pfnInspectLinkageExt = reinterpret_cast<ze_pfnModuleInspectLinkageExt_t>(
                GET_FUNCTION_PTR(loader, "zeModuleInspectLinkageExt") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleBuildLogProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.ModuleBuildLog );
            initialzeDdiTable.ModuleBuildLog.pfnDestroy = reinterpret_cast<ze_pfnModuleBuildLogDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeModuleBuildLogDestroy") );
            initialzeDdiTable.ModuleBuildLog.pfnGetString = reinterpret_cast<ze_pfnModuleBuildLogGetString_t>(
                GET_FUNCTION_PTR(loader, "zeModuleBuildLogGetString") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetPhysicalMemProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.PhysicalMem );
            initialzeDdiTable.PhysicalMem.pfnCreate = reinterpret_cast<ze_pfnPhysicalMemCreate_t>(
                GET_FUNCTION_PTR(loader, "zePhysicalMemCreate") );
            initialzeDdiTable.PhysicalMem.pfnDestroy = reinterpret_cast<ze_pfnPhysicalMemDestroy_t>(
                GET_FUNCTION_PTR(loader, "zePhysicalMemDestroy") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetSamplerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Sampler );
            initialzeDdiTable.Sampler.pfnCreate = reinterpret_cast<ze_pfnSamplerCreate_t>(
                GET_FUNCTION_PTR(loader, "zeSamplerCreate") );
            initialzeDdiTable.Sampler.pfnDestroy = reinterpret_cast<ze_pfnSamplerDestroy_t>(
                GET_FUNCTION_PTR(loader, "zeSamplerDestroy") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetVirtualMemProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.VirtualMem );
            initialzeDdiTable.VirtualMem.pfnReserve = reinterpret_cast<ze_pfnVirtualMemReserve_t>(
                GET_FUNCTION_PTR(loader, "zeVirtualMemReserve") );
            initialzeDdiTable.VirtualMem.pfnFree = reinterpret_cast<ze_pfnVirtualMemFree_t>(
                GET_FUNCTION_PTR(loader, "zeVirtualMemFree") );
            initialzeDdiTable.VirtualMem.pfnQueryPageSize = reinterpret_cast<ze_pfnVirtualMemQueryPageSize_t>(
                GET_FUNCTION_PTR(loader, "zeVirtualMemQueryPageSize") );
            initialzeDdiTable.VirtualMem.pfnMap = reinterpret_cast<ze_pfnVirtualMemMap_t>(
                GET_FUNCTION_PTR(loader, "zeVirtualMemMap") );
            initialzeDdiTable.VirtualMem.pfnUnmap = reinterpret_cast<ze_pfnVirtualMemUnmap_t>(
                GET_FUNCTION_PTR(loader, "zeVirtualMemUnmap") );
            initialzeDdiTable.VirtualMem.pfnSetAccessAttribute = reinterpret_cast<ze_pfnVirtualMemSetAccessAttribute_t>(
                GET_FUNCTION_PTR(loader, "zeVirtualMemSetAccessAttribute") );
            initialzeDdiTable.VirtualMem.pfnGetAccessAttribute = reinterpret_cast<ze_pfnVirtualMemGetAccessAttribute_t>(
                GET_FUNCTION_PTR(loader, "zeVirtualMemGetAccessAttribute") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetFabricEdgeExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFabricEdgeExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.FabricEdgeExp );
            initialzeDdiTable.FabricEdgeExp.pfnGetExp = reinterpret_cast<ze_pfnFabricEdgeGetExp_t>(
                GET_FUNCTION_PTR(loader, "zeFabricEdgeGetExp") );
            initialzeDdiTable.FabricEdgeExp.pfnGetVerticesExp = reinterpret_cast<ze_pfnFabricEdgeGetVerticesExp_t>(
                GET_FUNCTION_PTR(loader, "zeFabricEdgeGetVerticesExp") );
            initialzeDdiTable.FabricEdgeExp.pfnGetPropertiesExp = reinterpret_cast<ze_pfnFabricEdgeGetPropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zeFabricEdgeGetPropertiesExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetFabricVertexExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFabricVertexExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.FabricVertexExp );
            initialzeDdiTable.FabricVertexExp.pfnGetExp = reinterpret_cast<ze_pfnFabricVertexGetExp_t>(
                GET_FUNCTION_PTR(loader, "zeFabricVertexGetExp") );
            initialzeDdiTable.FabricVertexExp.pfnGetSubVerticesExp = reinterpret_cast<ze_pfnFabricVertexGetSubVerticesExp_t>(
                GET_FUNCTION_PTR(loader, "zeFabricVertexGetSubVerticesExp") );
            initialzeDdiTable.FabricVertexExp.pfnGetPropertiesExp = reinterpret_cast<ze_pfnFabricVertexGetPropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zeFabricVertexGetPropertiesExp") );
            initialzeDdiTable.FabricVertexExp.pfnGetDeviceExp = reinterpret_cast<ze_pfnFabricVertexGetDeviceExp_t>(
                GET_FUNCTION_PTR(loader, "zeFabricVertexGetDeviceExp") );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zeDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetGlobalProcAddrTable( version, &initialzeDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetRTASBuilderProcAddrTable( version, &initialzeDdiTable.RTASBuilder );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetRTASBuilderExpProcAddrTable( version, &initialzeDdiTable.RTASBuilderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetRTASParallelOperationProcAddrTable( version, &initialzeDdiTable.RTASParallelOperation );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetRTASParallelOperationExpProcAddrTable( version, &initialzeDdiTable.RTASParallelOperationExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDriverProcAddrTable( version, &initialzeDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetDriverExpProcAddrTable( version, &initialzeDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDeviceProcAddrTable( version, &initialzeDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetDeviceExpProcAddrTable( version, &initialzeDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetContextProcAddrTable( version, &initialzeDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetCommandQueueProcAddrTable( version, &initialzeDdiTable.CommandQueue );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetCommandListProcAddrTable( version, &initialzeDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetCommandListExpProcAddrTable( version, &initialzeDdiTable.CommandListExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetEventProcAddrTable( version, &initialzeDdiTable.Event );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetEventExpProcAddrTable( version, &initialzeDdiTable.EventExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetEventPoolProcAddrTable( version, &initialzeDdiTable.EventPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetFenceProcAddrTable( version, &initialzeDdiTable.Fence );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetImageProcAddrTable( version, &initialzeDdiTable.Image );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetImageExpProcAddrTable( version, &initialzeDdiTable.ImageExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetKernelProcAddrTable( version, &initialzeDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetKernelExpProcAddrTable( version, &initialzeDdiTable.KernelExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetMemProcAddrTable( version, &initialzeDdiTable.Mem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetMemExpProcAddrTable( version, &initialzeDdiTable.MemExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetModuleProcAddrTable( version, &initialzeDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetModuleBuildLogProcAddrTable( version, &initialzeDdiTable.ModuleBuildLog );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetPhysicalMemProcAddrTable( version, &initialzeDdiTable.PhysicalMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetSamplerProcAddrTable( version, &initialzeDdiTable.Sampler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetVirtualMemProcAddrTable( version, &initialzeDdiTable.VirtualMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetFabricEdgeExpProcAddrTable( version, &initialzeDdiTable.FabricEdgeExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetFabricVertexExpProcAddrTable( version, &initialzeDdiTable.FabricVertexExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
