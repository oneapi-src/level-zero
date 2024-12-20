/*
 * ***THIS FILE IS GENERATED. ***
 * See entry_points.h.mako for modifications
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_entry_points.h
 *
 */
#pragma once
#include "ze_api.h"

namespace validation_layer
{

class ZEValidationEntryPoints {
public:
    virtual ze_result_t zeInitPrologue( ze_init_flags_t flags ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeInitEpilogue( ze_init_flags_t flags , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetPrologue( uint32_t* pCount, ze_driver_handle_t* phDrivers ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetEpilogue( uint32_t* pCount, ze_driver_handle_t* phDrivers , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeInitDriversPrologue( uint32_t* pCount, ze_driver_handle_t* phDrivers, ze_init_driver_type_desc_t* desc ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeInitDriversEpilogue( uint32_t* pCount, ze_driver_handle_t* phDrivers, ze_init_driver_type_desc_t* desc , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetApiVersionPrologue( ze_driver_handle_t hDriver, ze_api_version_t* version ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetApiVersionEpilogue( ze_driver_handle_t hDriver, ze_api_version_t* version , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetPropertiesPrologue( ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetPropertiesEpilogue( ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetIpcPropertiesPrologue( ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetIpcPropertiesEpilogue( ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetExtensionPropertiesPrologue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetExtensionPropertiesEpilogue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetExtensionFunctionAddressPrologue( ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetExtensionFunctionAddressEpilogue( ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetLastErrorDescriptionPrologue( ze_driver_handle_t hDriver, const char** ppString ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverGetLastErrorDescriptionEpilogue( ze_driver_handle_t hDriver, const char** ppString , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetPrologue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetEpilogue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetRootDevicePrologue( ze_device_handle_t hDevice, ze_device_handle_t* phRootDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetRootDeviceEpilogue( ze_device_handle_t hDevice, ze_device_handle_t* phRootDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetSubDevicesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetSubDevicesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetPropertiesPrologue( ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetComputePropertiesPrologue( ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetComputePropertiesEpilogue( ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetModulePropertiesPrologue( ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetModulePropertiesEpilogue( ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetCommandQueueGroupPropertiesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetCommandQueueGroupPropertiesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetMemoryPropertiesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetMemoryPropertiesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetMemoryAccessPropertiesPrologue( ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetMemoryAccessPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetCachePropertiesPrologue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetCachePropertiesEpilogue( ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetImagePropertiesPrologue( ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetImagePropertiesEpilogue( ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetExternalMemoryPropertiesPrologue( ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetExternalMemoryPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetP2PPropertiesPrologue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetP2PPropertiesEpilogue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceCanAccessPeerPrologue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceCanAccessPeerEpilogue( ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetStatusPrologue( ze_device_handle_t hDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetStatusEpilogue( ze_device_handle_t hDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetGlobalTimestampsPrologue( ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetGlobalTimestampsEpilogue( ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextCreatePrologue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextCreateEpilogue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextCreateExPrologue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextCreateExEpilogue( ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextDestroyPrologue( ze_context_handle_t hContext ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextDestroyEpilogue( ze_context_handle_t hContext , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextGetStatusPrologue( ze_context_handle_t hContext ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextGetStatusEpilogue( ze_context_handle_t hContext , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueDestroyPrologue( ze_command_queue_handle_t hCommandQueue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueDestroyEpilogue( ze_command_queue_handle_t hCommandQueue , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueExecuteCommandListsPrologue( ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueExecuteCommandListsEpilogue( ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueSynchronizePrologue( ze_command_queue_handle_t hCommandQueue, uint64_t timeout ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueSynchronizeEpilogue( ze_command_queue_handle_t hCommandQueue, uint64_t timeout , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueGetOrdinalPrologue( ze_command_queue_handle_t hCommandQueue, uint32_t* pOrdinal ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueGetOrdinalEpilogue( ze_command_queue_handle_t hCommandQueue, uint32_t* pOrdinal , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueGetIndexPrologue( ze_command_queue_handle_t hCommandQueue, uint32_t* pIndex ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandQueueGetIndexEpilogue( ze_command_queue_handle_t hCommandQueue, uint32_t* pIndex , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListCreateImmediatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListCreateImmediateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListDestroyPrologue( ze_command_list_handle_t hCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListDestroyEpilogue( ze_command_list_handle_t hCommandList , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListClosePrologue( ze_command_list_handle_t hCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListCloseEpilogue( ze_command_list_handle_t hCommandList , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListResetPrologue( ze_command_list_handle_t hCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListResetEpilogue( ze_command_list_handle_t hCommandList , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendWriteGlobalTimestampPrologue( ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendWriteGlobalTimestampEpilogue( ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListHostSynchronizePrologue( ze_command_list_handle_t hCommandList, uint64_t timeout ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListHostSynchronizeEpilogue( ze_command_list_handle_t hCommandList, uint64_t timeout , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetDeviceHandlePrologue( ze_command_list_handle_t hCommandList, ze_device_handle_t* phDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetDeviceHandleEpilogue( ze_command_list_handle_t hCommandList, ze_device_handle_t* phDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetContextHandlePrologue( ze_command_list_handle_t hCommandList, ze_context_handle_t* phContext ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetContextHandleEpilogue( ze_command_list_handle_t hCommandList, ze_context_handle_t* phContext , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetOrdinalPrologue( ze_command_list_handle_t hCommandList, uint32_t* pOrdinal ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetOrdinalEpilogue( ze_command_list_handle_t hCommandList, uint32_t* pOrdinal , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListImmediateGetIndexPrologue( ze_command_list_handle_t hCommandListImmediate, uint32_t* pIndex ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListImmediateGetIndexEpilogue( ze_command_list_handle_t hCommandListImmediate, uint32_t* pIndex , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListIsImmediatePrologue( ze_command_list_handle_t hCommandList, ze_bool_t* pIsImmediate ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListIsImmediateEpilogue( ze_command_list_handle_t hCommandList, ze_bool_t* pIsImmediate , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendBarrierPrologue( ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendBarrierEpilogue( ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryRangesBarrierPrologue( ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryRangesBarrierEpilogue( ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextSystemBarrierPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextSystemBarrierEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryCopyPrologue( ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryCopyEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryFillPrologue( ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryFillEpilogue( ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryCopyRegionPrologue( ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryCopyRegionEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryCopyFromContextPrologue( ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryCopyFromContextEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyRegionPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, const ze_image_region_t* pDstRegion, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyRegionEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, const ze_image_region_t* pDstRegion, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyToMemoryPrologue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyToMemoryEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyFromMemoryPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyFromMemoryEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryPrefetchPrologue( ze_command_list_handle_t hCommandList, const void* ptr, size_t size ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemoryPrefetchEpilogue( ze_command_list_handle_t hCommandList, const void* ptr, size_t size , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemAdvisePrologue( ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendMemAdviseEpilogue( ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolCreatePrologue( ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolCreateEpilogue( ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolDestroyPrologue( ze_event_pool_handle_t hEventPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolDestroyEpilogue( ze_event_pool_handle_t hEventPool , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventCreatePrologue( ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventCreateEpilogue( ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventDestroyPrologue( ze_event_handle_t hEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventDestroyEpilogue( ze_event_handle_t hEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolGetIpcHandlePrologue( ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolGetIpcHandleEpilogue( ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolPutIpcHandlePrologue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolPutIpcHandleEpilogue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolOpenIpcHandlePrologue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolOpenIpcHandleEpilogue( ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolCloseIpcHandlePrologue( ze_event_pool_handle_t hEventPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolCloseIpcHandleEpilogue( ze_event_pool_handle_t hEventPool , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendSignalEventPrologue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendSignalEventEpilogue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendWaitOnEventsPrologue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendWaitOnEventsEpilogue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventHostSignalPrologue( ze_event_handle_t hEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventHostSignalEpilogue( ze_event_handle_t hEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventHostSynchronizePrologue( ze_event_handle_t hEvent, uint64_t timeout ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventHostSynchronizeEpilogue( ze_event_handle_t hEvent, uint64_t timeout , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryStatusPrologue( ze_event_handle_t hEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryStatusEpilogue( ze_event_handle_t hEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendEventResetPrologue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendEventResetEpilogue( ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventHostResetPrologue( ze_event_handle_t hEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventHostResetEpilogue( ze_event_handle_t hEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryKernelTimestampPrologue( ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryKernelTimestampEpilogue( ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendQueryKernelTimestampsPrologue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendQueryKernelTimestampsEpilogue( ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventGetEventPoolPrologue( ze_event_handle_t hEvent, ze_event_pool_handle_t* phEventPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventGetEventPoolEpilogue( ze_event_handle_t hEvent, ze_event_pool_handle_t* phEventPool , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventGetSignalScopePrologue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pSignalScope ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventGetSignalScopeEpilogue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pSignalScope , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventGetWaitScopePrologue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pWaitScope ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventGetWaitScopeEpilogue( ze_event_handle_t hEvent, ze_event_scope_flags_t* pWaitScope , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolGetContextHandlePrologue( ze_event_pool_handle_t hEventPool, ze_context_handle_t* phContext ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolGetContextHandleEpilogue( ze_event_pool_handle_t hEventPool, ze_context_handle_t* phContext , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolGetFlagsPrologue( ze_event_pool_handle_t hEventPool, ze_event_pool_flags_t* pFlags ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventPoolGetFlagsEpilogue( ze_event_pool_handle_t hEventPool, ze_event_pool_flags_t* pFlags , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceCreatePrologue( ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceCreateEpilogue( ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceDestroyPrologue( ze_fence_handle_t hFence ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceDestroyEpilogue( ze_fence_handle_t hFence , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceHostSynchronizePrologue( ze_fence_handle_t hFence, uint64_t timeout ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceHostSynchronizeEpilogue( ze_fence_handle_t hFence, uint64_t timeout , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceQueryStatusPrologue( ze_fence_handle_t hFence ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceQueryStatusEpilogue( ze_fence_handle_t hFence , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceResetPrologue( ze_fence_handle_t hFence ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFenceResetEpilogue( ze_fence_handle_t hFence , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetPropertiesPrologue( ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetPropertiesEpilogue( ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageDestroyPrologue( ze_image_handle_t hImage ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageDestroyEpilogue( ze_image_handle_t hImage , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemAllocSharedPrologue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemAllocSharedEpilogue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemAllocDevicePrologue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemAllocDeviceEpilogue( ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemAllocHostPrologue( ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemAllocHostEpilogue( ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemFreePrologue( ze_context_handle_t hContext, void* ptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemFreeEpilogue( ze_context_handle_t hContext, void* ptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetAllocPropertiesPrologue( ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetAllocPropertiesEpilogue( ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetAddressRangePrologue( ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetAddressRangeEpilogue( ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetIpcHandlePrologue( ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetIpcHandleEpilogue( ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetIpcHandleFromFileDescriptorExpPrologue( ze_context_handle_t hContext, uint64_t handle, ze_ipc_mem_handle_t* pIpcHandle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetIpcHandleFromFileDescriptorExpEpilogue( ze_context_handle_t hContext, uint64_t handle, ze_ipc_mem_handle_t* pIpcHandle , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetFileDescriptorFromIpcHandleExpPrologue( ze_context_handle_t hContext, ze_ipc_mem_handle_t ipcHandle, uint64_t* pHandle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetFileDescriptorFromIpcHandleExpEpilogue( ze_context_handle_t hContext, ze_ipc_mem_handle_t ipcHandle, uint64_t* pHandle , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemPutIpcHandlePrologue( ze_context_handle_t hContext, ze_ipc_mem_handle_t handle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemPutIpcHandleEpilogue( ze_context_handle_t hContext, ze_ipc_mem_handle_t handle , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemOpenIpcHandlePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemOpenIpcHandleEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemCloseIpcHandlePrologue( ze_context_handle_t hContext, const void* ptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemCloseIpcHandleEpilogue( ze_context_handle_t hContext, const void* ptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemSetAtomicAccessAttributeExpPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t attr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemSetAtomicAccessAttributeExpEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t attr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetAtomicAccessAttributeExpPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t* pAttr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetAtomicAccessAttributeExpEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_atomic_attr_exp_flags_t* pAttr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleDestroyPrologue( ze_module_handle_t hModule ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleDestroyEpilogue( ze_module_handle_t hModule , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleDynamicLinkPrologue( uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleDynamicLinkEpilogue( uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleBuildLogDestroyPrologue( ze_module_build_log_handle_t hModuleBuildLog ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleBuildLogDestroyEpilogue( ze_module_build_log_handle_t hModuleBuildLog , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleBuildLogGetStringPrologue( ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleBuildLogGetStringEpilogue( ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetNativeBinaryPrologue( ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetNativeBinaryEpilogue( ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetGlobalPointerPrologue( ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetGlobalPointerEpilogue( ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetKernelNamesPrologue( ze_module_handle_t hModule, uint32_t* pCount, const char** pNames ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetKernelNamesEpilogue( ze_module_handle_t hModule, uint32_t* pCount, const char** pNames , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetPropertiesPrologue( ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetPropertiesEpilogue( ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelCreatePrologue( ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelCreateEpilogue( ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelDestroyPrologue( ze_kernel_handle_t hKernel ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelDestroyEpilogue( ze_kernel_handle_t hKernel , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetFunctionPointerPrologue( ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleGetFunctionPointerEpilogue( ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetGroupSizePrologue( ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetGroupSizeEpilogue( ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSuggestGroupSizePrologue( ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSuggestGroupSizeEpilogue( ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSuggestMaxCooperativeGroupCountPrologue( ze_kernel_handle_t hKernel, uint32_t* totalGroupCount ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSuggestMaxCooperativeGroupCountEpilogue( ze_kernel_handle_t hKernel, uint32_t* totalGroupCount , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetArgumentValuePrologue( ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetArgumentValueEpilogue( ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetIndirectAccessPrologue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetIndirectAccessEpilogue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetIndirectAccessPrologue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetIndirectAccessEpilogue( ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetSourceAttributesPrologue( ze_kernel_handle_t hKernel, uint32_t* pSize, char** pString ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetSourceAttributesEpilogue( ze_kernel_handle_t hKernel, uint32_t* pSize, char** pString , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetCacheConfigPrologue( ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetCacheConfigEpilogue( ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetPropertiesPrologue( ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetPropertiesEpilogue( ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetNamePrologue( ze_kernel_handle_t hKernel, size_t* pSize, char* pName ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetNameEpilogue( ze_kernel_handle_t hKernel, size_t* pSize, char* pName , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchKernelPrologue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchKernelEpilogue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchCooperativeKernelPrologue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchCooperativeKernelEpilogue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchKernelIndirectPrologue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchKernelIndirectEpilogue( ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirectPrologue( ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirectEpilogue( ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextMakeMemoryResidentPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextMakeMemoryResidentEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextEvictMemoryPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextEvictMemoryEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextMakeImageResidentPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextMakeImageResidentEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextEvictImagePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeContextEvictImageEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_image_handle_t hImage , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeSamplerCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_sampler_desc_t* desc, ze_sampler_handle_t* phSampler ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeSamplerCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_sampler_desc_t* desc, ze_sampler_handle_t* phSampler , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeSamplerDestroyPrologue( ze_sampler_handle_t hSampler ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeSamplerDestroyEpilogue( ze_sampler_handle_t hSampler , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemReservePrologue( ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemReserveEpilogue( ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemFreePrologue( ze_context_handle_t hContext, const void* ptr, size_t size ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemFreeEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemQueryPageSizePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemQueryPageSizeEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zePhysicalMemCreatePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zePhysicalMemCreateEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zePhysicalMemDestroyPrologue( ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zePhysicalMemDestroyEpilogue( ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemMapPrologue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemMapEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemUnmapPrologue( ze_context_handle_t hContext, const void* ptr, size_t size ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemUnmapEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemSetAccessAttributePrologue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemSetAccessAttributeEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemGetAccessAttributePrologue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeVirtualMemGetAccessAttributeEpilogue( ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetGlobalOffsetExpPrologue( ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSetGlobalOffsetExpEpilogue( ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetBinaryExpPrologue( ze_kernel_handle_t hKernel, size_t* pSize, uint8_t* pKernelBinary ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelGetBinaryExpEpilogue( ze_kernel_handle_t hKernel, size_t* pSize, uint8_t* pKernelBinary , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceImportExternalSemaphoreExtPrologue( ze_device_handle_t hDevice, const ze_external_semaphore_ext_desc_t* desc, ze_external_semaphore_ext_handle_t* phSemaphore ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceImportExternalSemaphoreExtEpilogue( ze_device_handle_t hDevice, const ze_external_semaphore_ext_desc_t* desc, ze_external_semaphore_ext_handle_t* phSemaphore , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceReleaseExternalSemaphoreExtPrologue( ze_external_semaphore_ext_handle_t hSemaphore ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceReleaseExternalSemaphoreExtEpilogue( ze_external_semaphore_ext_handle_t hSemaphore , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendSignalExternalSemaphoreExtPrologue( ze_command_list_handle_t hCommandList, uint32_t numSemaphores, ze_external_semaphore_ext_handle_t* phSemaphores, ze_external_semaphore_signal_params_ext_t* signalParams, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendSignalExternalSemaphoreExtEpilogue( ze_command_list_handle_t hCommandList, uint32_t numSemaphores, ze_external_semaphore_ext_handle_t* phSemaphores, ze_external_semaphore_signal_params_ext_t* signalParams, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendWaitExternalSemaphoreExtPrologue( ze_command_list_handle_t hCommandList, uint32_t numSemaphores, ze_external_semaphore_ext_handle_t* phSemaphores, ze_external_semaphore_wait_params_ext_t* waitParams, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendWaitExternalSemaphoreExtEpilogue( ze_command_list_handle_t hCommandList, uint32_t numSemaphores, ze_external_semaphore_ext_handle_t* phSemaphores, ze_external_semaphore_wait_params_ext_t* waitParams, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceReserveCacheExtPrologue( ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceReserveCacheExtEpilogue( ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceSetCacheAdviceExtPrologue( ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceSetCacheAdviceExtEpilogue( ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryTimestampsExpPrologue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryTimestampsExpEpilogue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetMemoryPropertiesExpPrologue( ze_image_handle_t hImage, ze_image_memory_properties_exp_t* pMemoryProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetMemoryPropertiesExpEpilogue( ze_image_handle_t hImage, ze_image_memory_properties_exp_t* pMemoryProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageViewCreateExtPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageViewCreateExtEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageViewCreateExpPrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageViewCreateExpEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSchedulingHintExpPrologue( ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeKernelSchedulingHintExpEpilogue( ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDevicePciGetPropertiesExtPrologue( ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDevicePciGetPropertiesExtEpilogue( ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyToMemoryExtPrologue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, uint32_t destRowPitch, uint32_t destSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyToMemoryExtEpilogue( ze_command_list_handle_t hCommandList, void* dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t* pSrcRegion, uint32_t destRowPitch, uint32_t destSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyFromMemoryExtPrologue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, uint32_t srcRowPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListAppendImageCopyFromMemoryExtEpilogue( ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void* srcptr, const ze_image_region_t* pDstRegion, uint32_t srcRowPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetAllocPropertiesExtPrologue( ze_context_handle_t hContext, ze_image_handle_t hImage, ze_image_allocation_ext_properties_t* pImageAllocProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetAllocPropertiesExtEpilogue( ze_context_handle_t hContext, ze_image_handle_t hImage, ze_image_allocation_ext_properties_t* pImageAllocProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleInspectLinkageExtPrologue( ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeModuleInspectLinkageExtEpilogue( ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemFreeExtPrologue( ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemFreeExtEpilogue( ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetExpPrologue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetExpEpilogue( ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetSubVerticesExpPrologue( ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetSubVerticesExpEpilogue( ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetPropertiesExpPrologue( ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetPropertiesExpEpilogue( ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetDeviceExpPrologue( ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* phDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricVertexGetDeviceExpEpilogue( ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* phDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetFabricVertexExpPrologue( ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* phVertex ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDeviceGetFabricVertexExpEpilogue( ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* phVertex , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricEdgeGetExpPrologue( ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricEdgeGetExpEpilogue( ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricEdgeGetVerticesExpPrologue( ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricEdgeGetVerticesExpEpilogue( ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricEdgeGetPropertiesExpPrologue( ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeFabricEdgeGetPropertiesExpEpilogue( ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryKernelTimestampsExtPrologue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeEventQueryKernelTimestampsExtEpilogue( ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderCreateExpPrologue( ze_driver_handle_t hDriver, const ze_rtas_builder_exp_desc_t* pDescriptor, ze_rtas_builder_exp_handle_t* phBuilder ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderCreateExpEpilogue( ze_driver_handle_t hDriver, const ze_rtas_builder_exp_desc_t* pDescriptor, ze_rtas_builder_exp_handle_t* phBuilder , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderGetBuildPropertiesExpPrologue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, ze_rtas_builder_exp_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderGetBuildPropertiesExpEpilogue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, ze_rtas_builder_exp_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverRTASFormatCompatibilityCheckExpPrologue( ze_driver_handle_t hDriver, ze_rtas_format_exp_t rtasFormatA, ze_rtas_format_exp_t rtasFormatB ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeDriverRTASFormatCompatibilityCheckExpEpilogue( ze_driver_handle_t hDriver, ze_rtas_format_exp_t rtasFormatA, ze_rtas_format_exp_t rtasFormatB , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderBuildExpPrologue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, void* pScratchBuffer, size_t scratchBufferSizeBytes, void* pRtasBuffer, size_t rtasBufferSizeBytes, ze_rtas_parallel_operation_exp_handle_t hParallelOperation, void* pBuildUserPtr, ze_rtas_aabb_exp_t* pBounds, size_t* pRtasBufferSizeBytes ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderBuildExpEpilogue( ze_rtas_builder_exp_handle_t hBuilder, const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor, void* pScratchBuffer, size_t scratchBufferSizeBytes, void* pRtasBuffer, size_t rtasBufferSizeBytes, ze_rtas_parallel_operation_exp_handle_t hParallelOperation, void* pBuildUserPtr, ze_rtas_aabb_exp_t* pBounds, size_t* pRtasBufferSizeBytes , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderDestroyExpPrologue( ze_rtas_builder_exp_handle_t hBuilder ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASBuilderDestroyExpEpilogue( ze_rtas_builder_exp_handle_t hBuilder , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationCreateExpPrologue( ze_driver_handle_t hDriver, ze_rtas_parallel_operation_exp_handle_t* phParallelOperation ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationCreateExpEpilogue( ze_driver_handle_t hDriver, ze_rtas_parallel_operation_exp_handle_t* phParallelOperation , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationGetPropertiesExpPrologue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ze_rtas_parallel_operation_exp_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationGetPropertiesExpEpilogue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ze_rtas_parallel_operation_exp_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationJoinExpPrologue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationJoinExpEpilogue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationDestroyExpPrologue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeRTASParallelOperationDestroyExpEpilogue( ze_rtas_parallel_operation_exp_handle_t hParallelOperation , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetPitchFor2dImagePrologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t imageWidth, size_t imageHeight, unsigned int elementSizeInBytes, size_t * rowPitch ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeMemGetPitchFor2dImageEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t imageWidth, size_t imageHeight, unsigned int elementSizeInBytes, size_t * rowPitch , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetDeviceOffsetExpPrologue( ze_image_handle_t hImage, uint64_t* pDeviceOffset ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeImageGetDeviceOffsetExpEpilogue( ze_image_handle_t hImage, uint64_t* pDeviceOffset , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListCreateCloneExpPrologue( ze_command_list_handle_t hCommandList, ze_command_list_handle_t* phClonedCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListCreateCloneExpEpilogue( ze_command_list_handle_t hCommandList, ze_command_list_handle_t* phClonedCommandList , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListImmediateAppendCommandListsExpPrologue( ze_command_list_handle_t hCommandListImmediate, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListImmediateAppendCommandListsExpEpilogue( ze_command_list_handle_t hCommandListImmediate, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetNextCommandIdExpPrologue( ze_command_list_handle_t hCommandList, const ze_mutable_command_id_exp_desc_t* desc, uint64_t* pCommandId ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetNextCommandIdExpEpilogue( ze_command_list_handle_t hCommandList, const ze_mutable_command_id_exp_desc_t* desc, uint64_t* pCommandId , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetNextCommandIdWithKernelsExpPrologue( ze_command_list_handle_t hCommandList, const ze_mutable_command_id_exp_desc_t* desc, uint32_t numKernels, ze_kernel_handle_t* phKernels, uint64_t* pCommandId ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListGetNextCommandIdWithKernelsExpEpilogue( ze_command_list_handle_t hCommandList, const ze_mutable_command_id_exp_desc_t* desc, uint32_t numKernels, ze_kernel_handle_t* phKernels, uint64_t* pCommandId , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandsExpPrologue( ze_command_list_handle_t hCommandList, const ze_mutable_commands_exp_desc_t* desc ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandsExpEpilogue( ze_command_list_handle_t hCommandList, const ze_mutable_commands_exp_desc_t* desc , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandSignalEventExpPrologue( ze_command_list_handle_t hCommandList, uint64_t commandId, ze_event_handle_t hSignalEvent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandSignalEventExpEpilogue( ze_command_list_handle_t hCommandList, uint64_t commandId, ze_event_handle_t hSignalEvent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandWaitEventsExpPrologue( ze_command_list_handle_t hCommandList, uint64_t commandId, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandWaitEventsExpEpilogue( ze_command_list_handle_t hCommandList, uint64_t commandId, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandKernelsExpPrologue( ze_command_list_handle_t hCommandList, uint32_t numKernels, uint64_t* pCommandId, ze_kernel_handle_t* phKernels ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zeCommandListUpdateMutableCommandKernelsExpEpilogue( ze_command_list_handle_t hCommandList, uint32_t numKernels, uint64_t* pCommandId, ze_kernel_handle_t* phKernels , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ~ZEValidationEntryPoints() {}
};
}