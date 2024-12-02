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
                                ze_result_t zeDriverGetApiVersionPrologue( ze_driver_handle_t hDriver, ze_api_version_t* version ) override;
        ze_result_t zeDriverGetPropertiesPrologue( ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties ) override;
        ze_result_t zeDriverGetIpcPropertiesPrologue( ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties ) override;
        ze_result_t zeDriverGetExtensionPropertiesPrologue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties ) override;
        ze_result_t zeDriverGetExtensionFunctionAddressPrologue( ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress ) override;
        ze_result_t zeDriverGetLastErrorDescriptionPrologue( ze_driver_handle_t hDriver, const char** ppString ) override;
        ze_result_t zeDeviceGetPrologue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices ) override;
        ze_result_t zeDeviceGetRootDevicePrologue( ze_device_handle_t hDevice, ze_device_handle_t* phRootDevice ) override;
        ze_result_t zeDeviceGetSubDevicesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices ) override;
        ze_result_t zeDeviceGetPropertiesPrologue( ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties ) override;
        ze_result_t zeDeviceGetComputePropertiesPrologue( ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties ) override;
        ze_result_t zeDeviceGetModulePropertiesPrologue( ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties ) override;
        ze_result_t zeDeviceGetCommandQueueGroupPropertiesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties ) override;
        ze_result_t zeDeviceGetMemoryPropertiesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties ) override;
        ze_result_t zeDeviceGetMemoryAccessPropertiesPrologue( ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties ) override;
        ze_result_t zeDeviceGetCachePropertiesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties ) override;
        ze_result_t zeDeviceGetImagePropertiesPrologue( ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties ) override;
        ze_result_t zeDeviceGetExternalMemoryPropertiesPrologue( ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties ) override;
        ze_result_t zeDeviceGetP2PPropertiesPrologue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties ) override;
        ze_result_t zeDeviceCanAccessPeerPrologue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value ) override;
        ze_result_t zeDeviceGetStatusPrologue( ze_device_handle_t hDevice ) override;
        ze_result_t zeDeviceGetGlobalTimestampsPrologue( ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp ) override;
        ze_result_t zeContextCreatePrologue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext ) override;
        ze_result_t zeContextCreateExPrologue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext ) override;
        ze_result_t zeContextDestroyPrologue( ze_context_handle_t hContext ) override;
        ze_result_t zeContextGetStatusPrologue( ze_context_handle_t hContext ) override;
        ze_result_t zeCommandQueueCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue ) override;
        ze_result_t zeCommandQueueDestroyPrologue( ze_command_queue_handle_t hCommandQueue ) override;
        ze_result_t zeCommandQueueExecuteCommandListsPrologue( ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence ) override;
        ze_result_t zeCommandQueueSynchronizePrologue( ze_command_queue_handle_t hCommandQueue, uint64_t timeout ) override;
        ze_result_t zeCommandQueueGetOrdinalPrologue( ze_command_queue_handle_t hCommandQueue, uint32_t* pOrdinal ) override;
        ze_result_t zeCommandQueueGetIndexPrologue( ze_command_queue_handle_t hCommandQueue, uint32_t* pIndex ) override;
        ze_result_t zeCommandListCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList ) override;
        ze_result_t zeCommandListCreateImmediatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList ) override;
        ze_result_t zeCommandListDestroyPrologue( ze_command_list_handle_t hCommandList ) override;
        ze_result_t zeCommandListClosePrologue( ze_command_list_handle_t hCommandList ) override;
        ze_result_t zeCommandListResetPrologue( ze_command_list_handle_t hCommandList ) override;
        ze_result_t zeCommandListAppendWriteGlobalTimestampPrologue( ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListHostSynchronizePrologue( ze_command_list_handle_t hCommandList, uint64_t timeout ) override;
        ze_result_t zeCommandListGetDeviceHandlePrologue( ze_command_list_handle_t hCommandList, ze_device_handle_t* phDevice ) override;
        ze_result_t zeCommandListGetContextHandlePrologue( ze_command_list_handle_t hCommandList, ze_context_handle_t* phContext ) override;
        ze_result_t zeCommandListGetOrdinalPrologue( ze_command_list_handle_t hCommandList, uint32_t* pOrdinal ) override;
        ze_result_t zeCommandListImmediateGetIndexPrologue( ze_command_list_handle_t hCommandListImmediate, uint32_t* pIndex ) override;
        ze_result_t zeCommandListIsImmediatePrologue( ze_command_list_handle_t hCommandList, ze_bool_t* pIsImmediate ) override;
        ze_result_t zeCommandListAppendBarrierPrologue( ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryRangesBarrierPrologue( ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeContextSystemBarrierPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice ) override;
        ze_result_t zeCommandListAppendMemoryCopyPrologue( ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryFillPrologue( ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryCopyRegionPrologue( ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryCopyFromContextPrologue( ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyRegionPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, const ze_image_region_t* pDstRegion, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyToMemoryPrologue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyFromMemoryPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendMemoryPrefetchPrologue( ze_command_list_handle_t hCommandList, const void* ptr, size_t size ) override;
        ze_result_t zeCommandListAppendMemAdvisePrologue( ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice ) override;
        ze_result_t zeEventPoolCreatePrologue( ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool ) override;
        ze_result_t zeEventPoolDestroyPrologue( ze_event_pool_handle_t hEventPool ) override;
        ze_result_t zeEventCreatePrologue( ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent ) override;
        ze_result_t zeEventDestroyPrologue( ze_event_handle_t hEvent ) override;
        ze_result_t zeEventPoolGetIpcHandlePrologue( ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc ) override;
        ze_result_t zeEventPoolPutIpcHandlePrologue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc ) override;
        ze_result_t zeEventPoolOpenIpcHandlePrologue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool ) override;
        ze_result_t zeEventPoolCloseIpcHandlePrologue( ze_event_pool_handle_t hEventPool ) override;
        ze_result_t zeCommandListAppendSignalEventPrologue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent ) override;
        ze_result_t zeCommandListAppendWaitOnEventsPrologue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents ) override;
        ze_result_t zeEventHostSignalPrologue( ze_event_handle_t hEvent ) override;
        ze_result_t zeEventHostSynchronizePrologue( ze_event_handle_t hEvent, uint64_t timeout ) override;
        ze_result_t zeEventQueryStatusPrologue( ze_event_handle_t hEvent ) override;
        ze_result_t zeCommandListAppendEventResetPrologue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent ) override;
        ze_result_t zeEventHostResetPrologue( ze_event_handle_t hEvent ) override;
        ze_result_t zeEventQueryKernelTimestampPrologue( ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr ) override;
        ze_result_t zeCommandListAppendQueryKernelTimestampsPrologue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeEventGetEventPoolPrologue( ze_event_handle_t hEvent, ze_event_pool_handle_t* phEventPool ) override;
        ze_result_t zeEventGetSignalScopePrologue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pSignalScope ) override;
        ze_result_t zeEventGetWaitScopePrologue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pWaitScope ) override;
        ze_result_t zeEventPoolGetContextHandlePrologue( ze_event_pool_handle_t hEventPool, ze_context_handle_t* phContext ) override;
        ze_result_t zeEventPoolGetFlagsPrologue( ze_event_pool_handle_t hEventPool, ze_event_pool_flags_t* pFlags ) override;
        ze_result_t zeFenceCreatePrologue( ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence ) override;
        ze_result_t zeFenceDestroyPrologue( ze_fence_handle_t hFence ) override;
        ze_result_t zeFenceHostSynchronizePrologue( ze_fence_handle_t hFence, uint64_t timeout ) override;
        ze_result_t zeFenceQueryStatusPrologue( ze_fence_handle_t hFence ) override;
        ze_result_t zeFenceResetPrologue( ze_fence_handle_t hFence ) override;
        ze_result_t zeImageGetPropertiesPrologue( ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties ) override;
        ze_result_t zeImageCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage ) override;
        ze_result_t zeImageDestroyPrologue( ze_image_handle_t hImage ) override;
        ze_result_t zeMemAllocSharedPrologue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr ) override;
        ze_result_t zeMemAllocDevicePrologue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr ) override;
        ze_result_t zeMemAllocHostPrologue( ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr ) override;
        ze_result_t zeMemFreePrologue( ze_context_handle_t hContext, void* ptr ) override;
        ze_result_t zeMemGetAllocPropertiesPrologue( ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice ) override;
        ze_result_t zeMemGetAddressRangePrologue( ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize ) override;
        ze_result_t zeMemGetIpcHandlePrologue( ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle ) override;
        ze_result_t zeMemGetIpcHandleFromFileDescriptorExpPrologue( ze_context_handle_t hContext, uint64_t handle, ze_ipc_mem_handle_t* pIpcHandle ) override;
        ze_result_t zeMemGetFileDescriptorFromIpcHandleExpPrologue( ze_context_handle_t hContext, ze_ipc_mem_handle_t ipcHandle, uint64_t* pHandle ) override;
        ze_result_t zeMemPutIpcHandlePrologue( ze_context_handle_t hContext, ze_ipc_mem_handle_t handle ) override;
        ze_result_t zeMemOpenIpcHandlePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr ) override;
        ze_result_t zeMemCloseIpcHandlePrologue( ze_context_handle_t hContext, const void* ptr ) override;
        ze_result_t zeMemSetAtomicAccessAttributeExpPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t attr ) override;
        ze_result_t zeMemGetAtomicAccessAttributeExpPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t* pAttr ) override;
        ze_result_t zeModuleCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog ) override;
        ze_result_t zeModuleDestroyPrologue( ze_module_handle_t hModule ) override;
        ze_result_t zeModuleDynamicLinkPrologue( uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog ) override;
        ze_result_t zeModuleBuildLogDestroyPrologue( ze_module_build_log_handle_t hModuleBuildLog ) override;
        ze_result_t zeModuleBuildLogGetStringPrologue( ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog ) override;
        ze_result_t zeModuleGetNativeBinaryPrologue( ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary ) override;
        ze_result_t zeModuleGetGlobalPointerPrologue( ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr ) override;
        ze_result_t zeModuleGetKernelNamesPrologue( ze_module_handle_t hModule, uint32_t* pCount, const char** pNames ) override;
        ze_result_t zeModuleGetPropertiesPrologue( ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties ) override;
        ze_result_t zeKernelCreatePrologue( ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel ) override;
        ze_result_t zeKernelDestroyPrologue( ze_kernel_handle_t hKernel ) override;
        ze_result_t zeModuleGetFunctionPointerPrologue( ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction ) override;
        ze_result_t zeKernelSetGroupSizePrologue( ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ ) override;
        ze_result_t zeKernelSuggestGroupSizePrologue( ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ ) override;
        ze_result_t zeKernelSuggestMaxCooperativeGroupCountPrologue( ze_kernel_handle_t hKernel, uint32_t* totalGroupCount ) override;
        ze_result_t zeKernelSetArgumentValuePrologue( ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue ) override;
        ze_result_t zeKernelSetIndirectAccessPrologue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags ) override;
        ze_result_t zeKernelGetIndirectAccessPrologue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags ) override;
        ze_result_t zeKernelGetSourceAttributesPrologue( ze_kernel_handle_t hKernel, uint32_t* pSize, char** pString ) override;
        ze_result_t zeKernelSetCacheConfigPrologue( ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags ) override;
        ze_result_t zeKernelGetPropertiesPrologue( ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties ) override;
        ze_result_t zeKernelGetNamePrologue( ze_kernel_handle_t hKernel, size_t* pSize, char* pName ) override;
        ze_result_t zeCommandListAppendLaunchKernelPrologue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendLaunchCooperativeKernelPrologue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendLaunchKernelIndirectPrologue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirectPrologue( ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeContextMakeMemoryResidentPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size ) override;
        ze_result_t zeContextEvictMemoryPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size ) override;
        ze_result_t zeContextMakeImageResidentPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage ) override;
        ze_result_t zeContextEvictImagePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage ) override;
        ze_result_t zeSamplerCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_sampler_desc_t* desc, ze_sampler_handle_t* phSampler ) override;
        ze_result_t zeSamplerDestroyPrologue( ze_sampler_handle_t hSampler ) override;
        ze_result_t zeVirtualMemReservePrologue( ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr ) override;
        ze_result_t zeVirtualMemFreePrologue( ze_context_handle_t hContext, const void* ptr, size_t size ) override;
        ze_result_t zeVirtualMemQueryPageSizePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize ) override;
        ze_result_t zePhysicalMemCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory ) override;
        ze_result_t zePhysicalMemDestroyPrologue( ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory ) override;
        ze_result_t zeVirtualMemMapPrologue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access ) override;
        ze_result_t zeVirtualMemUnmapPrologue( ze_context_handle_t hContext, const void* ptr, size_t size ) override;
        ze_result_t zeVirtualMemSetAccessAttributePrologue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access ) override;
        ze_result_t zeVirtualMemGetAccessAttributePrologue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize ) override;
        ze_result_t zeKernelSetGlobalOffsetExpPrologue( ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ ) override;
        ze_result_t zeKernelGetBinaryExpPrologue( ze_kernel_handle_t hKernel, size_t* pSize, uint8_t* pKernelBinary ) override;
        ze_result_t zeDeviceImportExternalSemaphoreExtPrologue( ze_device_handle_t hDevice, const ze_external_semaphore_ext_desc_t* desc, ze_external_semaphore_ext_handle_t* phSemaphore ) override;
        ze_result_t zeDeviceReleaseExternalSemaphoreExtPrologue( ze_external_semaphore_ext_handle_t hSemaphore ) override;
        ze_result_t zeCommandListAppendSignalExternalSemaphoreExtPrologue( ze_command_list_handle_t hCommandList, uint32_t numSemaphores, ze_external_semaphore_ext_handle_t* phSemaphores, ze_external_semaphore_signal_params_ext_t* signalParams, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendWaitExternalSemaphoreExtPrologue( ze_command_list_handle_t hCommandList, uint32_t numSemaphores, ze_external_semaphore_ext_handle_t* phSemaphores, ze_external_semaphore_wait_params_ext_t* waitParams, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeDeviceReserveCacheExtPrologue( ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize ) override;
        ze_result_t zeDeviceSetCacheAdviceExtPrologue( ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion ) override;
        ze_result_t zeEventQueryTimestampsExpPrologue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps ) override;
        ze_result_t zeImageGetMemoryPropertiesExpPrologue( ze_image_handle_t hImage, ze_image_memory_properties_exp_t* pMemoryProperties ) override;
        ze_result_t zeImageViewCreateExtPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView ) override;
        ze_result_t zeImageViewCreateExpPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView ) override;
        ze_result_t zeKernelSchedulingHintExpPrologue( ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint ) override;
        ze_result_t zeDevicePciGetPropertiesExtPrologue( ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties ) override;
        ze_result_t zeCommandListAppendImageCopyToMemoryExtPrologue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, uint32_t destRowPitch, uint32_t destSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListAppendImageCopyFromMemoryExtPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, uint32_t srcRowPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeImageGetAllocPropertiesExtPrologue( ze_context_handle_t hContext, ze_image_handle_t hImage, ze_image_allocation_ext_properties_t* pImageAllocProperties ) override;
        ze_result_t zeModuleInspectLinkageExtPrologue( ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog ) override;
        ze_result_t zeMemFreeExtPrologue( ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr ) override;
        ze_result_t zeFabricVertexGetExpPrologue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices ) override;
        ze_result_t zeFabricVertexGetSubVerticesExpPrologue( ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices ) override;
        ze_result_t zeFabricVertexGetPropertiesExpPrologue( ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties ) override;
        ze_result_t zeFabricVertexGetDeviceExpPrologue( ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* phDevice ) override;
        ze_result_t zeDeviceGetFabricVertexExpPrologue( ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* phVertex ) override;
        ze_result_t zeFabricEdgeGetExpPrologue( ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges ) override;
        ze_result_t zeFabricEdgeGetVerticesExpPrologue( ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB ) override;
        ze_result_t zeFabricEdgeGetPropertiesExpPrologue( ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties ) override;
        ze_result_t zeEventQueryKernelTimestampsExtPrologue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults ) override;
        ze_result_t zeRTASBuilderCreateExpPrologue( ze_driver_handle_t hDriver, const ze_rtas_builder_exp_desc_t* pDescriptor, ze_rtas_builder_exp_handle_t* phBuilder ) override;
        ze_result_t zeRTASBuilderGetBuildPropertiesExpPrologue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, ze_rtas_builder_exp_properties_t* pProperties ) override;
        ze_result_t zeDriverRTASFormatCompatibilityCheckExpPrologue( ze_driver_handle_t hDriver, ze_rtas_format_exp_t rtasFormatA, ze_rtas_format_exp_t rtasFormatB ) override;
        ze_result_t zeRTASBuilderBuildExpPrologue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, void* pScratchBuffer, size_t scratchBufferSizeBytes, void* pRtasBuffer, size_t rtasBufferSizeBytes, ze_rtas_parallel_operation_exp_handle_t hParallelOperation, void* pBuildUserPtr, ze_rtas_aabb_exp_t* pBounds, size_t* pRtasBufferSizeBytes ) override;
        ze_result_t zeRTASBuilderDestroyExpPrologue( ze_rtas_builder_exp_handle_t hBuilder ) override;
        ze_result_t zeRTASParallelOperationCreateExpPrologue( ze_driver_handle_t hDriver, ze_rtas_parallel_operation_exp_handle_t* phParallelOperation ) override;
        ze_result_t zeRTASParallelOperationGetPropertiesExpPrologue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ze_rtas_parallel_operation_exp_properties_t* pProperties ) override;
        ze_result_t zeRTASParallelOperationJoinExpPrologue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation ) override;
        ze_result_t zeRTASParallelOperationDestroyExpPrologue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation ) override;
        ze_result_t zeMemGetPitchFor2dImagePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t imageWidth, size_t imageHeight, unsigned int elementSizeInBytes, size_t * rowPitch ) override;
        ze_result_t zeImageGetDeviceOffsetExpPrologue( ze_image_handle_t hImage, uint64_t* pDeviceOffset ) override;
        ze_result_t zeCommandListCreateCloneExpPrologue( ze_command_list_handle_t hCommandList, ze_command_list_handle_t* phClonedCommandList ) override;
        ze_result_t zeCommandListImmediateAppendCommandListsExpPrologue( ze_command_list_handle_t hCommandListImmediate, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListGetNextCommandIdExpPrologue( ze_command_list_handle_t hCommandList, const ze_mutable_command_id_exp_desc_t* desc, uint64_t* pCommandId ) override;
        ze_result_t zeCommandListGetNextCommandIdWithKernelsExpPrologue( ze_command_list_handle_t hCommandList, const ze_mutable_command_id_exp_desc_t* desc, uint32_t numKernels, ze_kernel_handle_t* phKernels, uint64_t* pCommandId ) override;
        ze_result_t zeCommandListUpdateMutableCommandsExpPrologue( ze_command_list_handle_t hCommandList, const ze_mutable_commands_exp_desc_t* desc ) override;
        ze_result_t zeCommandListUpdateMutableCommandSignalEventExpPrologue( ze_command_list_handle_t hCommandList, uint64_t commandId, ze_event_handle_t hSignalEvent ) override;
        ze_result_t zeCommandListUpdateMutableCommandWaitEventsExpPrologue( ze_command_list_handle_t hCommandList, uint64_t commandId, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zeCommandListUpdateMutableCommandKernelsExpPrologue( ze_command_list_handle_t hCommandList, uint32_t numKernels, uint64_t* pCommandId, ze_kernel_handle_t* phKernels ) override;
    };

}
