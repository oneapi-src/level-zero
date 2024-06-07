/*
 * ***THIS FILE IS GENERATED. ***
 * See handle_lifetime.h.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_handle_lifetime.h
 *
 */

#pragma once
#include "ze_entry_points.h"


namespace validation_layer
{

    class ZEHandleLifetimeValidation : public ZEValidationEntryPoints {
    public:
                        ze_result_t zeDriverGetApiVersionEpilogue( ze_driver_handle_t hDriver, ze_api_version_t* version ) override;
        ze_result_t zeDriverGetPropertiesEpilogue( ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties ) override;
        ze_result_t zeDriverGetIpcPropertiesEpilogue( ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties ) override;
        ze_result_t zeDriverGetExtensionPropertiesEpilogue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties ) override;
        ze_result_t zeDriverGetExtensionFunctionAddressEpilogue( ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress ) override;
        ze_result_t zeDriverGetLastErrorDescriptionEpilogue( ze_driver_handle_t hDriver, const char** ppString ) override;
        ze_result_t zeDeviceGetEpilogue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices ) override;
        ze_result_t zeDeviceGetRootDeviceEpilogue( ze_device_handle_t hDevice, ze_device_handle_t* phRootDevice ) override;
        ze_result_t zeDeviceGetSubDevicesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices ) override;
        ze_result_t zeDeviceGetPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties ) override;
        ze_result_t zeDeviceGetComputePropertiesEpilogue( ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties ) override;
        ze_result_t zeDeviceGetModulePropertiesEpilogue( ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties ) override;
        ze_result_t zeDeviceGetCommandQueueGroupPropertiesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties ) override;
        ze_result_t zeDeviceGetMemoryPropertiesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties ) override;
        ze_result_t zeDeviceGetMemoryAccessPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties ) override;
        ze_result_t zeDeviceGetCachePropertiesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties ) override;
        ze_result_t zeDeviceGetImagePropertiesEpilogue( ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties ) override;
        ze_result_t zeDeviceGetExternalMemoryPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties ) override;
        ze_result_t zeDeviceGetP2PPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties ) override;
        ze_result_t zeDeviceCanAccessPeerEpilogue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value ) override;
        ze_result_t zeDeviceGetStatusEpilogue( ze_device_handle_t hDevice ) override;
        ze_result_t zeDeviceGetGlobalTimestampsEpilogue( ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp ) override;
        ze_result_t zeContextCreateEpilogue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext ) override;
        ze_result_t zeContextCreateExEpilogue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext ) override;
        ze_result_t zeContextDestroyEpilogue( ze_context_handle_t hContext ) override;
        ze_result_t zeContextGetStatusEpilogue( ze_context_handle_t hContext ) override;
        ze_result_t zeCommandQueueCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue ) override;
        ze_result_t zeCommandQueueDestroyEpilogue( ze_command_queue_handle_t hCommandQueue ) override;
        ze_result_t zeCommandQueueExecuteCommandListsEpilogue( ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence ) override;
        ze_result_t zeCommandQueueSynchronizeEpilogue( ze_command_queue_handle_t hCommandQueue, uint64_t timeout ) override;
        ze_result_t zeCommandQueueGetOrdinalEpilogue( ze_command_queue_handle_t hCommandQueue, uint32_t* pOrdinal ) override;
        ze_result_t zeCommandQueueGetIndexEpilogue( ze_command_queue_handle_t hCommandQueue, uint32_t* pIndex ) override;
        ze_result_t zeCommandListCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList ) override;
        ze_result_t zeCommandListCreateImmediateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList ) override;
        ze_result_t zeCommandListDestroyEpilogue( ze_command_list_handle_t hCommandList ) override;
        ze_result_t zeCommandListCloseEpilogue( ze_command_list_handle_t hCommandList ) override;
        ze_result_t zeCommandListResetEpilogue( ze_command_list_handle_t hCommandList ) override;
        ze_result_t zeCommandListAppendWriteGlobalTimestampEpilogue( ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListHostSynchronizeEpilogue( ze_command_list_handle_t hCommandList, uint64_t timeout ) override;
        ze_result_t zeCommandListGetDeviceHandleEpilogue( ze_command_list_handle_t hCommandList, ze_device_handle_t* phDevice ) override;
        ze_result_t zeCommandListGetContextHandleEpilogue( ze_command_list_handle_t hCommandList, ze_context_handle_t* phContext ) override;
        ze_result_t zeCommandListGetOrdinalEpilogue( ze_command_list_handle_t hCommandList, uint32_t* pOrdinal ) override;
        ze_result_t zeCommandListImmediateGetIndexEpilogue( ze_command_list_handle_t hCommandListImmediate, uint32_t* pIndex ) override;
        ze_result_t zeCommandListIsImmediateEpilogue( ze_command_list_handle_t hCommandList, ze_bool_t* pIsImmediate ) override;
        ze_result_t zeCommandListAppendBarrierEpilogue( ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryRangesBarrierEpilogue( ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeContextSystemBarrierEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice ) override;
        ze_result_t zeCommandListAppendMemoryCopyEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryFillEpilogue( ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryCopyRegionEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryCopyFromContextEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyRegionEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, const ze_image_region_t* pDstRegion, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyToMemoryEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyFromMemoryEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryPrefetchEpilogue( ze_command_list_handle_t hCommandList, const void* ptr, size_t size ) override;
        ze_result_t zeCommandListAppendMemAdviseEpilogue( ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice ) override;
        ze_result_t zeEventPoolCreateEpilogue( ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool ) override;
        ze_result_t zeEventPoolDestroyEpilogue( ze_event_pool_handle_t hEventPool ) override;
        ze_result_t zeEventCreateEpilogue( ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent ) override;
        ze_result_t zeEventDestroyEpilogue( ze_event_handle_t hEvent ) override;
        ze_result_t zeEventPoolGetIpcHandleEpilogue( ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc ) override;
        ze_result_t zeEventPoolPutIpcHandleEpilogue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc ) override;
        ze_result_t zeEventPoolOpenIpcHandleEpilogue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool ) override;
        ze_result_t zeEventPoolCloseIpcHandleEpilogue( ze_event_pool_handle_t hEventPool ) override;
        ze_result_t zeCommandListAppendSignalEventEpilogue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent ) override;
        ze_result_t zeCommandListAppendWaitOnEventsEpilogue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents ) override;
        ze_result_t zeEventHostSignalEpilogue( ze_event_handle_t hEvent ) override;
        ze_result_t zeEventHostSynchronizeEpilogue( ze_event_handle_t hEvent, uint64_t timeout ) override;
        ze_result_t zeEventQueryStatusEpilogue( ze_event_handle_t hEvent ) override;
        ze_result_t zeCommandListAppendEventResetEpilogue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent ) override;
        ze_result_t zeEventHostResetEpilogue( ze_event_handle_t hEvent ) override;
        ze_result_t zeEventQueryKernelTimestampEpilogue( ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr ) override;
        ze_result_t zeCommandListAppendQueryKernelTimestampsEpilogue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeEventGetEventPoolEpilogue( ze_event_handle_t hEvent, ze_event_pool_handle_t* phEventPool ) override;
        ze_result_t zeEventGetSignalScopeEpilogue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pSignalScope ) override;
        ze_result_t zeEventGetWaitScopeEpilogue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pWaitScope ) override;
        ze_result_t zeEventPoolGetContextHandleEpilogue( ze_event_pool_handle_t hEventPool, ze_context_handle_t* phContext ) override;
        ze_result_t zeEventPoolGetFlagsEpilogue( ze_event_pool_handle_t hEventPool, ze_event_pool_flags_t* pFlags ) override;
        ze_result_t zeFenceCreateEpilogue( ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence ) override;
        ze_result_t zeFenceDestroyEpilogue( ze_fence_handle_t hFence ) override;
        ze_result_t zeFenceHostSynchronizeEpilogue( ze_fence_handle_t hFence, uint64_t timeout ) override;
        ze_result_t zeFenceQueryStatusEpilogue( ze_fence_handle_t hFence ) override;
        ze_result_t zeFenceResetEpilogue( ze_fence_handle_t hFence ) override;
        ze_result_t zeImageGetPropertiesEpilogue( ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties ) override;
        ze_result_t zeImageCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage ) override;
        ze_result_t zeImageDestroyEpilogue( ze_image_handle_t hImage ) override;
        ze_result_t zeMemAllocSharedEpilogue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr ) override;
        ze_result_t zeMemAllocDeviceEpilogue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr ) override;
        ze_result_t zeMemAllocHostEpilogue( ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr ) override;
        ze_result_t zeMemFreeEpilogue( ze_context_handle_t hContext, void* ptr ) override;
        ze_result_t zeMemGetAllocPropertiesEpilogue( ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice ) override;
        ze_result_t zeMemGetAddressRangeEpilogue( ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize ) override;
        ze_result_t zeMemGetIpcHandleEpilogue( ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle ) override;
        ze_result_t zeMemGetIpcHandleFromFileDescriptorExpEpilogue( ze_context_handle_t hContext, uint64_t handle, ze_ipc_mem_handle_t* pIpcHandle ) override;
        ze_result_t zeMemGetFileDescriptorFromIpcHandleExpEpilogue( ze_context_handle_t hContext, ze_ipc_mem_handle_t ipcHandle, uint64_t* pHandle ) override;
        ze_result_t zeMemPutIpcHandleEpilogue( ze_context_handle_t hContext, ze_ipc_mem_handle_t handle ) override;
        ze_result_t zeMemOpenIpcHandleEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr ) override;
        ze_result_t zeMemCloseIpcHandleEpilogue( ze_context_handle_t hContext, const void* ptr ) override;
        ze_result_t zeMemSetAtomicAccessAttributeExpEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t attr ) override;
        ze_result_t zeMemGetAtomicAccessAttributeExpEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t* pAttr ) override;
        ze_result_t zeModuleCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog ) override;
        ze_result_t zeModuleDestroyEpilogue( ze_module_handle_t hModule ) override;
        ze_result_t zeModuleDynamicLinkEpilogue( uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog ) override;
        ze_result_t zeModuleBuildLogDestroyEpilogue( ze_module_build_log_handle_t hModuleBuildLog ) override;
        ze_result_t zeModuleBuildLogGetStringEpilogue( ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog ) override;
        ze_result_t zeModuleGetNativeBinaryEpilogue( ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary ) override;
        ze_result_t zeModuleGetGlobalPointerEpilogue( ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr ) override;
        ze_result_t zeModuleGetKernelNamesEpilogue( ze_module_handle_t hModule, uint32_t* pCount, const char** pNames ) override;
        ze_result_t zeModuleGetPropertiesEpilogue( ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties ) override;
        ze_result_t zeKernelCreateEpilogue( ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel ) override;
        ze_result_t zeKernelDestroyEpilogue( ze_kernel_handle_t hKernel ) override;
        ze_result_t zeModuleGetFunctionPointerEpilogue( ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction ) override;
        ze_result_t zeKernelSetGroupSizeEpilogue( ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ ) override;
        ze_result_t zeKernelSuggestGroupSizeEpilogue( ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ ) override;
        ze_result_t zeKernelSuggestMaxCooperativeGroupCountEpilogue( ze_kernel_handle_t hKernel, uint32_t* totalGroupCount ) override;
        ze_result_t zeKernelSetArgumentValueEpilogue( ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue ) override;
        ze_result_t zeKernelSetIndirectAccessEpilogue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags ) override;
        ze_result_t zeKernelGetIndirectAccessEpilogue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags ) override;
        ze_result_t zeKernelGetSourceAttributesEpilogue( ze_kernel_handle_t hKernel, uint32_t* pSize, char** pString ) override;
        ze_result_t zeKernelSetCacheConfigEpilogue( ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags ) override;
        ze_result_t zeKernelGetPropertiesEpilogue( ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties ) override;
        ze_result_t zeKernelGetNameEpilogue( ze_kernel_handle_t hKernel, size_t* pSize, char* pName ) override;
        ze_result_t zeCommandListAppendLaunchKernelEpilogue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendLaunchCooperativeKernelEpilogue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendLaunchKernelIndirectEpilogue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirectEpilogue( ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeContextMakeMemoryResidentEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size ) override;
        ze_result_t zeContextEvictMemoryEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size ) override;
        ze_result_t zeContextMakeImageResidentEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage ) override;
        ze_result_t zeContextEvictImageEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage ) override;
        ze_result_t zeSamplerCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_sampler_desc_t* desc, ze_sampler_handle_t* phSampler ) override;
        ze_result_t zeSamplerDestroyEpilogue( ze_sampler_handle_t hSampler ) override;
        ze_result_t zeVirtualMemReserveEpilogue( ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr ) override;
        ze_result_t zeVirtualMemFreeEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size ) override;
        ze_result_t zeVirtualMemQueryPageSizeEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize ) override;
        ze_result_t zePhysicalMemCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory ) override;
        ze_result_t zePhysicalMemDestroyEpilogue( ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory ) override;
        ze_result_t zeVirtualMemMapEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access ) override;
        ze_result_t zeVirtualMemUnmapEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size ) override;
        ze_result_t zeVirtualMemSetAccessAttributeEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access ) override;
        ze_result_t zeVirtualMemGetAccessAttributeEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize ) override;
        ze_result_t zeKernelSetGlobalOffsetExpEpilogue( ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ ) override;
        ze_result_t zeDeviceReserveCacheExtEpilogue( ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize ) override;
        ze_result_t zeDeviceSetCacheAdviceExtEpilogue( ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion ) override;
        ze_result_t zeEventQueryTimestampsExpEpilogue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps ) override;
        ze_result_t zeImageGetMemoryPropertiesExpEpilogue( ze_image_handle_t hImage, ze_image_memory_properties_exp_t* pMemoryProperties ) override;
        ze_result_t zeImageViewCreateExtEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView ) override;
        ze_result_t zeImageViewCreateExpEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView ) override;
        ze_result_t zeKernelSchedulingHintExpEpilogue( ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint ) override;
        ze_result_t zeDevicePciGetPropertiesExtEpilogue( ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties ) override;
        ze_result_t zeCommandListAppendImageCopyToMemoryExtEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, uint32_t destRowPitch, uint32_t destSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyFromMemoryExtEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, uint32_t srcRowPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeImageGetAllocPropertiesExtEpilogue( ze_context_handle_t hContext, ze_image_handle_t hImage, ze_image_allocation_ext_properties_t* pImageAllocProperties ) override;
        ze_result_t zeModuleInspectLinkageExtEpilogue( ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog ) override;
        ze_result_t zeMemFreeExtEpilogue( ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr ) override;
        ze_result_t zeFabricVertexGetExpEpilogue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices ) override;
        ze_result_t zeFabricVertexGetSubVerticesExpEpilogue( ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices ) override;
        ze_result_t zeFabricVertexGetPropertiesExpEpilogue( ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties ) override;
        ze_result_t zeFabricVertexGetDeviceExpEpilogue( ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* phDevice ) override;
        ze_result_t zeDeviceGetFabricVertexExpEpilogue( ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* phVertex ) override;
        ze_result_t zeFabricEdgeGetExpEpilogue( ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges ) override;
        ze_result_t zeFabricEdgeGetVerticesExpEpilogue( ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB ) override;
        ze_result_t zeFabricEdgeGetPropertiesExpEpilogue( ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties ) override;
        ze_result_t zeEventQueryKernelTimestampsExtEpilogue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults ) override;
        ze_result_t zeRTASBuilderCreateExpEpilogue( ze_driver_handle_t hDriver, const ze_rtas_builder_exp_desc_t* pDescriptor, ze_rtas_builder_exp_handle_t* phBuilder ) override;
        ze_result_t zeRTASBuilderGetBuildPropertiesExpEpilogue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, ze_rtas_builder_exp_properties_t* pProperties ) override;
        ze_result_t zeDriverRTASFormatCompatibilityCheckExpEpilogue( ze_driver_handle_t hDriver, ze_rtas_format_exp_t rtasFormatA, ze_rtas_format_exp_t rtasFormatB ) override;
        ze_result_t zeRTASBuilderBuildExpEpilogue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, void* pScratchBuffer, size_t scratchBufferSizeBytes, void* pRtasBuffer, size_t rtasBufferSizeBytes, ze_rtas_parallel_operation_exp_handle_t hParallelOperation, void* pBuildUserPtr, ze_rtas_aabb_exp_t* pBounds, size_t* pRtasBufferSizeBytes ) override;
        ze_result_t zeRTASBuilderDestroyExpEpilogue( ze_rtas_builder_exp_handle_t hBuilder ) override;
        ze_result_t zeRTASParallelOperationCreateExpEpilogue( ze_driver_handle_t hDriver, ze_rtas_parallel_operation_exp_handle_t* phParallelOperation ) override;
        ze_result_t zeRTASParallelOperationGetPropertiesExpEpilogue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ze_rtas_parallel_operation_exp_properties_t* pProperties ) override;
        ze_result_t zeRTASParallelOperationJoinExpEpilogue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation ) override;
        ze_result_t zeRTASParallelOperationDestroyExpEpilogue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation ) override;
        ze_result_t zeMemGetPitchFor2dImageEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t imageWidth, size_t imageHeight, unsigned int elementSizeInBytes, size_t * rowPitch ) override;
        ze_result_t zeImageGetDeviceOffsetExpEpilogue( ze_image_handle_t hImage, uint64_t* pDeviceOffset ) override;
        ze_result_t zeCommandListCreateCloneExpEpilogue( ze_command_list_handle_t hCommandList, ze_command_list_handle_t* phClonedCommandList ) override;
        ze_result_t zeCommandListImmediateAppendCommandListsExpEpilogue( ze_command_list_handle_t hCommandListImmediate, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListGetNextCommandIdExpEpilogue( ze_command_list_handle_t hCommandList, const ze_mutable_command_id_exp_desc_t* desc, uint64_t* pCommandId ) override;
        ze_result_t zeCommandListUpdateMutableCommandsExpEpilogue( ze_command_list_handle_t hCommandList, const ze_mutable_commands_exp_desc_t* desc ) override;
        ze_result_t zeCommandListUpdateMutableCommandSignalEventExpEpilogue( ze_command_list_handle_t hCommandList, uint64_t commandId, ze_event_handle_t hSignalEvent ) override;
        ze_result_t zeCommandListUpdateMutableCommandWaitEventsExpEpilogue( ze_command_list_handle_t hCommandList, uint64_t commandId, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
    };

}
