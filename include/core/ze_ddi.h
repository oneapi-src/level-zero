/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_ddi.h
 *
 */
#ifndef _ZE_DDI_H
#define _ZE_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "ze_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeInit 
typedef ze_result_t (__zecall *ze_pfnInit_t)(
    ze_init_flag_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global functions pointers
typedef struct _ze_global_dditable_t
{
    ze_pfnInit_t                                                pfnInit;
} ze_global_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetGlobalProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetGlobalProcAddrTable_t)(
    ze_api_version_t,
    ze_global_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGet 
typedef ze_result_t (__zecall *ze_pfnDriverGet_t)(
    uint32_t*,
    ze_driver_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGetApiVersion 
typedef ze_result_t (__zecall *ze_pfnDriverGetApiVersion_t)(
    ze_driver_handle_t,
    ze_api_version_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGetProperties 
typedef ze_result_t (__zecall *ze_pfnDriverGetProperties_t)(
    ze_driver_handle_t,
    ze_driver_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGetIPCProperties 
typedef ze_result_t (__zecall *ze_pfnDriverGetIPCProperties_t)(
    ze_driver_handle_t,
    ze_driver_ipc_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGetExtensionFunctionAddress 
typedef ze_result_t (__zecall *ze_pfnDriverGetExtensionFunctionAddress_t)(
    ze_driver_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverAllocSharedMem 
typedef ze_result_t (__zecall *ze_pfnDriverAllocSharedMem_t)(
    ze_driver_handle_t,
    const ze_device_mem_alloc_desc_t*,
    const ze_host_mem_alloc_desc_t*,
    size_t,
    size_t,
    ze_device_handle_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverAllocDeviceMem 
typedef ze_result_t (__zecall *ze_pfnDriverAllocDeviceMem_t)(
    ze_driver_handle_t,
    const ze_device_mem_alloc_desc_t*,
    size_t,
    size_t,
    ze_device_handle_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverAllocHostMem 
typedef ze_result_t (__zecall *ze_pfnDriverAllocHostMem_t)(
    ze_driver_handle_t,
    const ze_host_mem_alloc_desc_t*,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverFreeMem 
typedef ze_result_t (__zecall *ze_pfnDriverFreeMem_t)(
    ze_driver_handle_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGetMemAllocProperties 
typedef ze_result_t (__zecall *ze_pfnDriverGetMemAllocProperties_t)(
    ze_driver_handle_t,
    const void*,
    ze_memory_allocation_properties_t*,
    ze_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGetMemAddressRange 
typedef ze_result_t (__zecall *ze_pfnDriverGetMemAddressRange_t)(
    ze_driver_handle_t,
    const void*,
    void**,
    size_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverGetMemIpcHandle 
typedef ze_result_t (__zecall *ze_pfnDriverGetMemIpcHandle_t)(
    ze_driver_handle_t,
    const void*,
    ze_ipc_mem_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverOpenMemIpcHandle 
typedef ze_result_t (__zecall *ze_pfnDriverOpenMemIpcHandle_t)(
    ze_driver_handle_t,
    ze_device_handle_t,
    ze_ipc_mem_handle_t,
    ze_ipc_memory_flag_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDriverCloseMemIpcHandle 
typedef ze_result_t (__zecall *ze_pfnDriverCloseMemIpcHandle_t)(
    ze_driver_handle_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Driver functions pointers
typedef struct _ze_driver_dditable_t
{
    ze_pfnDriverGet_t                                           pfnGet;
    ze_pfnDriverGetApiVersion_t                                 pfnGetApiVersion;
    ze_pfnDriverGetProperties_t                                 pfnGetProperties;
    ze_pfnDriverGetIPCProperties_t                              pfnGetIPCProperties;
    ze_pfnDriverGetExtensionFunctionAddress_t                   pfnGetExtensionFunctionAddress;
    ze_pfnDriverAllocSharedMem_t                                pfnAllocSharedMem;
    ze_pfnDriverAllocDeviceMem_t                                pfnAllocDeviceMem;
    ze_pfnDriverAllocHostMem_t                                  pfnAllocHostMem;
    ze_pfnDriverFreeMem_t                                       pfnFreeMem;
    ze_pfnDriverGetMemAllocProperties_t                         pfnGetMemAllocProperties;
    ze_pfnDriverGetMemAddressRange_t                            pfnGetMemAddressRange;
    ze_pfnDriverGetMemIpcHandle_t                               pfnGetMemIpcHandle;
    ze_pfnDriverOpenMemIpcHandle_t                              pfnOpenMemIpcHandle;
    ze_pfnDriverCloseMemIpcHandle_t                             pfnCloseMemIpcHandle;
} ze_driver_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetDriverProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetDriverProcAddrTable_t)(
    ze_api_version_t,
    ze_driver_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGet 
typedef ze_result_t (__zecall *ze_pfnDeviceGet_t)(
    ze_driver_handle_t,
    uint32_t*,
    ze_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetSubDevices 
typedef ze_result_t (__zecall *ze_pfnDeviceGetSubDevices_t)(
    ze_device_handle_t,
    uint32_t*,
    ze_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetProperties_t)(
    ze_device_handle_t,
    ze_device_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetComputeProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetComputeProperties_t)(
    ze_device_handle_t,
    ze_device_compute_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetKernelProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetKernelProperties_t)(
    ze_device_handle_t,
    ze_device_kernel_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetMemoryProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetMemoryProperties_t)(
    ze_device_handle_t,
    uint32_t*,
    ze_device_memory_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetMemoryAccessProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetMemoryAccessProperties_t)(
    ze_device_handle_t,
    ze_device_memory_access_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetCacheProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetCacheProperties_t)(
    ze_device_handle_t,
    ze_device_cache_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetImageProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetImageProperties_t)(
    ze_device_handle_t,
    ze_device_image_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceGetP2PProperties 
typedef ze_result_t (__zecall *ze_pfnDeviceGetP2PProperties_t)(
    ze_device_handle_t,
    ze_device_handle_t,
    ze_device_p2p_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceCanAccessPeer 
typedef ze_result_t (__zecall *ze_pfnDeviceCanAccessPeer_t)(
    ze_device_handle_t,
    ze_device_handle_t,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceSetLastLevelCacheConfig 
typedef ze_result_t (__zecall *ze_pfnDeviceSetLastLevelCacheConfig_t)(
    ze_device_handle_t,
    ze_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceSystemBarrier 
typedef ze_result_t (__zecall *ze_pfnDeviceSystemBarrier_t)(
    ze_device_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceMakeMemoryResident 
typedef ze_result_t (__zecall *ze_pfnDeviceMakeMemoryResident_t)(
    ze_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceEvictMemory 
typedef ze_result_t (__zecall *ze_pfnDeviceEvictMemory_t)(
    ze_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceMakeImageResident 
typedef ze_result_t (__zecall *ze_pfnDeviceMakeImageResident_t)(
    ze_device_handle_t,
    ze_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceEvictImage 
typedef ze_result_t (__zecall *ze_pfnDeviceEvictImage_t)(
    ze_device_handle_t,
    ze_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceRegisterCLMemory 
#if ZE_ENABLE_OCL_INTEROP
typedef ze_result_t (__zecall *ze_pfnDeviceRegisterCLMemory_t)(
    ze_device_handle_t,
    cl_context,
    cl_mem,
    void**
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceRegisterCLProgram 
#if ZE_ENABLE_OCL_INTEROP
typedef ze_result_t (__zecall *ze_pfnDeviceRegisterCLProgram_t)(
    ze_device_handle_t,
    cl_context,
    cl_program,
    ze_module_handle_t*
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeDeviceRegisterCLCommandQueue 
#if ZE_ENABLE_OCL_INTEROP
typedef ze_result_t (__zecall *ze_pfnDeviceRegisterCLCommandQueue_t)(
    ze_device_handle_t,
    cl_context,
    cl_command_queue,
    ze_command_queue_handle_t*
    );
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _ze_device_dditable_t
{
    ze_pfnDeviceGet_t                                           pfnGet;
    ze_pfnDeviceGetSubDevices_t                                 pfnGetSubDevices;
    ze_pfnDeviceGetProperties_t                                 pfnGetProperties;
    ze_pfnDeviceGetComputeProperties_t                          pfnGetComputeProperties;
    ze_pfnDeviceGetKernelProperties_t                           pfnGetKernelProperties;
    ze_pfnDeviceGetMemoryProperties_t                           pfnGetMemoryProperties;
    ze_pfnDeviceGetMemoryAccessProperties_t                     pfnGetMemoryAccessProperties;
    ze_pfnDeviceGetCacheProperties_t                            pfnGetCacheProperties;
    ze_pfnDeviceGetImageProperties_t                            pfnGetImageProperties;
    ze_pfnDeviceGetP2PProperties_t                              pfnGetP2PProperties;
    ze_pfnDeviceCanAccessPeer_t                                 pfnCanAccessPeer;
    ze_pfnDeviceSetLastLevelCacheConfig_t                       pfnSetLastLevelCacheConfig;
    ze_pfnDeviceSystemBarrier_t                                 pfnSystemBarrier;
    ze_pfnDeviceMakeMemoryResident_t                            pfnMakeMemoryResident;
    ze_pfnDeviceEvictMemory_t                                   pfnEvictMemory;
    ze_pfnDeviceMakeImageResident_t                             pfnMakeImageResident;
    ze_pfnDeviceEvictImage_t                                    pfnEvictImage;
#if ZE_ENABLE_OCL_INTEROP
    ze_pfnDeviceRegisterCLMemory_t                              pfnRegisterCLMemory;
#else
    void*                                                       pfnRegisterCLMemory;
#endif // ZE_ENABLE_OCL_INTEROP
#if ZE_ENABLE_OCL_INTEROP
    ze_pfnDeviceRegisterCLProgram_t                             pfnRegisterCLProgram;
#else
    void*                                                       pfnRegisterCLProgram;
#endif // ZE_ENABLE_OCL_INTEROP
#if ZE_ENABLE_OCL_INTEROP
    ze_pfnDeviceRegisterCLCommandQueue_t                        pfnRegisterCLCommandQueue;
#else
    void*                                                       pfnRegisterCLCommandQueue;
#endif // ZE_ENABLE_OCL_INTEROP
} ze_device_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetDeviceProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetDeviceProcAddrTable_t)(
    ze_api_version_t,
    ze_device_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandQueueCreate 
typedef ze_result_t (__zecall *ze_pfnCommandQueueCreate_t)(
    ze_device_handle_t,
    const ze_command_queue_desc_t*,
    ze_command_queue_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandQueueDestroy 
typedef ze_result_t (__zecall *ze_pfnCommandQueueDestroy_t)(
    ze_command_queue_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandQueueExecuteCommandLists 
typedef ze_result_t (__zecall *ze_pfnCommandQueueExecuteCommandLists_t)(
    ze_command_queue_handle_t,
    uint32_t,
    ze_command_list_handle_t*,
    ze_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandQueueSynchronize 
typedef ze_result_t (__zecall *ze_pfnCommandQueueSynchronize_t)(
    ze_command_queue_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandQueue functions pointers
typedef struct _ze_command_queue_dditable_t
{
    ze_pfnCommandQueueCreate_t                                  pfnCreate;
    ze_pfnCommandQueueDestroy_t                                 pfnDestroy;
    ze_pfnCommandQueueExecuteCommandLists_t                     pfnExecuteCommandLists;
    ze_pfnCommandQueueSynchronize_t                             pfnSynchronize;
} ze_command_queue_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetCommandQueueProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetCommandQueueProcAddrTable_t)(
    ze_api_version_t,
    ze_command_queue_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListCreate 
typedef ze_result_t (__zecall *ze_pfnCommandListCreate_t)(
    ze_device_handle_t,
    const ze_command_list_desc_t*,
    ze_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListCreateImmediate 
typedef ze_result_t (__zecall *ze_pfnCommandListCreateImmediate_t)(
    ze_device_handle_t,
    const ze_command_queue_desc_t*,
    ze_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListDestroy 
typedef ze_result_t (__zecall *ze_pfnCommandListDestroy_t)(
    ze_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListClose 
typedef ze_result_t (__zecall *ze_pfnCommandListClose_t)(
    ze_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListReset 
typedef ze_result_t (__zecall *ze_pfnCommandListReset_t)(
    ze_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendBarrier 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendBarrier_t)(
    ze_command_list_handle_t,
    ze_event_handle_t,
    uint32_t,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendMemoryRangesBarrier 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendMemoryRangesBarrier_t)(
    ze_command_list_handle_t,
    uint32_t,
    const size_t*,
    const void**,
    ze_event_handle_t,
    uint32_t,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendLaunchKernel 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendLaunchKernel_t)(
    ze_command_list_handle_t,
    ze_kernel_handle_t,
    const ze_group_count_t*,
    ze_event_handle_t,
    uint32_t,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendLaunchCooperativeKernel 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendLaunchCooperativeKernel_t)(
    ze_command_list_handle_t,
    ze_kernel_handle_t,
    const ze_group_count_t*,
    ze_event_handle_t,
    uint32_t,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendLaunchKernelIndirect 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendLaunchKernelIndirect_t)(
    ze_command_list_handle_t,
    ze_kernel_handle_t,
    const ze_group_count_t*,
    ze_event_handle_t,
    uint32_t,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendLaunchMultipleKernelsIndirect 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendLaunchMultipleKernelsIndirect_t)(
    ze_command_list_handle_t,
    uint32_t,
    ze_kernel_handle_t*,
    const uint32_t*,
    const ze_group_count_t*,
    ze_event_handle_t,
    uint32_t,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendSignalEvent 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendSignalEvent_t)(
    ze_command_list_handle_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendWaitOnEvents 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendWaitOnEvents_t)(
    ze_command_list_handle_t,
    uint32_t,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendEventReset 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendEventReset_t)(
    ze_command_list_handle_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendMemoryCopy 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendMemoryCopy_t)(
    ze_command_list_handle_t,
    void*,
    const void*,
    size_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendMemoryFill 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendMemoryFill_t)(
    ze_command_list_handle_t,
    void*,
    const void*,
    size_t,
    size_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendMemoryCopyRegion 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendMemoryCopyRegion_t)(
    ze_command_list_handle_t,
    void*,
    const ze_copy_region_t*,
    uint32_t,
    uint32_t,
    const void*,
    const ze_copy_region_t*,
    uint32_t,
    uint32_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendImageCopy 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendImageCopy_t)(
    ze_command_list_handle_t,
    ze_image_handle_t,
    ze_image_handle_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendImageCopyRegion 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendImageCopyRegion_t)(
    ze_command_list_handle_t,
    ze_image_handle_t,
    ze_image_handle_t,
    const ze_image_region_t*,
    const ze_image_region_t*,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendImageCopyToMemory 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendImageCopyToMemory_t)(
    ze_command_list_handle_t,
    void*,
    ze_image_handle_t,
    const ze_image_region_t*,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendImageCopyFromMemory 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendImageCopyFromMemory_t)(
    ze_command_list_handle_t,
    ze_image_handle_t,
    const void*,
    const ze_image_region_t*,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendMemoryPrefetch 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendMemoryPrefetch_t)(
    ze_command_list_handle_t,
    const void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeCommandListAppendMemAdvise 
typedef ze_result_t (__zecall *ze_pfnCommandListAppendMemAdvise_t)(
    ze_command_list_handle_t,
    ze_device_handle_t,
    const void*,
    size_t,
    ze_memory_advice_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _ze_command_list_dditable_t
{
    ze_pfnCommandListCreate_t                                   pfnCreate;
    ze_pfnCommandListCreateImmediate_t                          pfnCreateImmediate;
    ze_pfnCommandListDestroy_t                                  pfnDestroy;
    ze_pfnCommandListClose_t                                    pfnClose;
    ze_pfnCommandListReset_t                                    pfnReset;
    ze_pfnCommandListAppendBarrier_t                            pfnAppendBarrier;
    ze_pfnCommandListAppendMemoryRangesBarrier_t                pfnAppendMemoryRangesBarrier;
    ze_pfnCommandListAppendLaunchKernel_t                       pfnAppendLaunchKernel;
    ze_pfnCommandListAppendLaunchCooperativeKernel_t            pfnAppendLaunchCooperativeKernel;
    ze_pfnCommandListAppendLaunchKernelIndirect_t               pfnAppendLaunchKernelIndirect;
    ze_pfnCommandListAppendLaunchMultipleKernelsIndirect_t      pfnAppendLaunchMultipleKernelsIndirect;
    ze_pfnCommandListAppendSignalEvent_t                        pfnAppendSignalEvent;
    ze_pfnCommandListAppendWaitOnEvents_t                       pfnAppendWaitOnEvents;
    ze_pfnCommandListAppendEventReset_t                         pfnAppendEventReset;
    ze_pfnCommandListAppendMemoryCopy_t                         pfnAppendMemoryCopy;
    ze_pfnCommandListAppendMemoryFill_t                         pfnAppendMemoryFill;
    ze_pfnCommandListAppendMemoryCopyRegion_t                   pfnAppendMemoryCopyRegion;
    ze_pfnCommandListAppendImageCopy_t                          pfnAppendImageCopy;
    ze_pfnCommandListAppendImageCopyRegion_t                    pfnAppendImageCopyRegion;
    ze_pfnCommandListAppendImageCopyToMemory_t                  pfnAppendImageCopyToMemory;
    ze_pfnCommandListAppendImageCopyFromMemory_t                pfnAppendImageCopyFromMemory;
    ze_pfnCommandListAppendMemoryPrefetch_t                     pfnAppendMemoryPrefetch;
    ze_pfnCommandListAppendMemAdvise_t                          pfnAppendMemAdvise;
} ze_command_list_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetCommandListProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetCommandListProcAddrTable_t)(
    ze_api_version_t,
    ze_command_list_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeImageGetProperties 
typedef ze_result_t (__zecall *ze_pfnImageGetProperties_t)(
    ze_device_handle_t,
    const ze_image_desc_t*,
    ze_image_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeImageCreate 
typedef ze_result_t (__zecall *ze_pfnImageCreate_t)(
    ze_device_handle_t,
    const ze_image_desc_t*,
    ze_image_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeImageDestroy 
typedef ze_result_t (__zecall *ze_pfnImageDestroy_t)(
    ze_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Image functions pointers
typedef struct _ze_image_dditable_t
{
    ze_pfnImageGetProperties_t                                  pfnGetProperties;
    ze_pfnImageCreate_t                                         pfnCreate;
    ze_pfnImageDestroy_t                                        pfnDestroy;
} ze_image_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetImageProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetImageProcAddrTable_t)(
    ze_api_version_t,
    ze_image_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleCreate 
typedef ze_result_t (__zecall *ze_pfnModuleCreate_t)(
    ze_device_handle_t,
    const ze_module_desc_t*,
    ze_module_handle_t*,
    ze_module_build_log_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleDestroy 
typedef ze_result_t (__zecall *ze_pfnModuleDestroy_t)(
    ze_module_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleGetNativeBinary 
typedef ze_result_t (__zecall *ze_pfnModuleGetNativeBinary_t)(
    ze_module_handle_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleGetGlobalPointer 
typedef ze_result_t (__zecall *ze_pfnModuleGetGlobalPointer_t)(
    ze_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleGetKernelNames 
typedef ze_result_t (__zecall *ze_pfnModuleGetKernelNames_t)(
    ze_module_handle_t,
    uint32_t*,
    const char**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleGetFunctionPointer 
typedef ze_result_t (__zecall *ze_pfnModuleGetFunctionPointer_t)(
    ze_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module functions pointers
typedef struct _ze_module_dditable_t
{
    ze_pfnModuleCreate_t                                        pfnCreate;
    ze_pfnModuleDestroy_t                                       pfnDestroy;
    ze_pfnModuleGetNativeBinary_t                               pfnGetNativeBinary;
    ze_pfnModuleGetGlobalPointer_t                              pfnGetGlobalPointer;
    ze_pfnModuleGetKernelNames_t                                pfnGetKernelNames;
    ze_pfnModuleGetFunctionPointer_t                            pfnGetFunctionPointer;
} ze_module_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetModuleProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetModuleProcAddrTable_t)(
    ze_api_version_t,
    ze_module_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleBuildLogDestroy 
typedef ze_result_t (__zecall *ze_pfnModuleBuildLogDestroy_t)(
    ze_module_build_log_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeModuleBuildLogGetString 
typedef ze_result_t (__zecall *ze_pfnModuleBuildLogGetString_t)(
    ze_module_build_log_handle_t,
    size_t*,
    char*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ModuleBuildLog functions pointers
typedef struct _ze_module_build_log_dditable_t
{
    ze_pfnModuleBuildLogDestroy_t                               pfnDestroy;
    ze_pfnModuleBuildLogGetString_t                             pfnGetString;
} ze_module_build_log_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetModuleBuildLogProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetModuleBuildLogProcAddrTable_t)(
    ze_api_version_t,
    ze_module_build_log_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelCreate 
typedef ze_result_t (__zecall *ze_pfnKernelCreate_t)(
    ze_module_handle_t,
    const ze_kernel_desc_t*,
    ze_kernel_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelDestroy 
typedef ze_result_t (__zecall *ze_pfnKernelDestroy_t)(
    ze_kernel_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelSetIntermediateCacheConfig 
typedef ze_result_t (__zecall *ze_pfnKernelSetIntermediateCacheConfig_t)(
    ze_kernel_handle_t,
    ze_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelSetGroupSize 
typedef ze_result_t (__zecall *ze_pfnKernelSetGroupSize_t)(
    ze_kernel_handle_t,
    uint32_t,
    uint32_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelSuggestGroupSize 
typedef ze_result_t (__zecall *ze_pfnKernelSuggestGroupSize_t)(
    ze_kernel_handle_t,
    uint32_t,
    uint32_t,
    uint32_t,
    uint32_t*,
    uint32_t*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelSuggestMaxCooperativeGroupCount 
typedef ze_result_t (__zecall *ze_pfnKernelSuggestMaxCooperativeGroupCount_t)(
    ze_kernel_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelSetArgumentValue 
typedef ze_result_t (__zecall *ze_pfnKernelSetArgumentValue_t)(
    ze_kernel_handle_t,
    uint32_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelSetAttribute 
typedef ze_result_t (__zecall *ze_pfnKernelSetAttribute_t)(
    ze_kernel_handle_t,
    ze_kernel_attribute_t,
    uint32_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelGetAttribute 
typedef ze_result_t (__zecall *ze_pfnKernelGetAttribute_t)(
    ze_kernel_handle_t,
    ze_kernel_attribute_t,
    uint32_t*,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeKernelGetProperties 
typedef ze_result_t (__zecall *ze_pfnKernelGetProperties_t)(
    ze_kernel_handle_t,
    ze_kernel_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Kernel functions pointers
typedef struct _ze_kernel_dditable_t
{
    ze_pfnKernelCreate_t                                        pfnCreate;
    ze_pfnKernelDestroy_t                                       pfnDestroy;
    ze_pfnKernelSetIntermediateCacheConfig_t                    pfnSetIntermediateCacheConfig;
    ze_pfnKernelSetGroupSize_t                                  pfnSetGroupSize;
    ze_pfnKernelSuggestGroupSize_t                              pfnSuggestGroupSize;
    ze_pfnKernelSuggestMaxCooperativeGroupCount_t               pfnSuggestMaxCooperativeGroupCount;
    ze_pfnKernelSetArgumentValue_t                              pfnSetArgumentValue;
    ze_pfnKernelSetAttribute_t                                  pfnSetAttribute;
    ze_pfnKernelGetAttribute_t                                  pfnGetAttribute;
    ze_pfnKernelGetProperties_t                                 pfnGetProperties;
} ze_kernel_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetKernelProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetKernelProcAddrTable_t)(
    ze_api_version_t,
    ze_kernel_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventPoolCreate 
typedef ze_result_t (__zecall *ze_pfnEventPoolCreate_t)(
    ze_driver_handle_t,
    const ze_event_pool_desc_t*,
    uint32_t,
    ze_device_handle_t*,
    ze_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventPoolDestroy 
typedef ze_result_t (__zecall *ze_pfnEventPoolDestroy_t)(
    ze_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventPoolGetIpcHandle 
typedef ze_result_t (__zecall *ze_pfnEventPoolGetIpcHandle_t)(
    ze_event_pool_handle_t,
    ze_ipc_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventPoolOpenIpcHandle 
typedef ze_result_t (__zecall *ze_pfnEventPoolOpenIpcHandle_t)(
    ze_driver_handle_t,
    ze_ipc_event_pool_handle_t,
    ze_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventPoolCloseIpcHandle 
typedef ze_result_t (__zecall *ze_pfnEventPoolCloseIpcHandle_t)(
    ze_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of EventPool functions pointers
typedef struct _ze_event_pool_dditable_t
{
    ze_pfnEventPoolCreate_t                                     pfnCreate;
    ze_pfnEventPoolDestroy_t                                    pfnDestroy;
    ze_pfnEventPoolGetIpcHandle_t                               pfnGetIpcHandle;
    ze_pfnEventPoolOpenIpcHandle_t                              pfnOpenIpcHandle;
    ze_pfnEventPoolCloseIpcHandle_t                             pfnCloseIpcHandle;
} ze_event_pool_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetEventPoolProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetEventPoolProcAddrTable_t)(
    ze_api_version_t,
    ze_event_pool_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventCreate 
typedef ze_result_t (__zecall *ze_pfnEventCreate_t)(
    ze_event_pool_handle_t,
    const ze_event_desc_t*,
    ze_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventDestroy 
typedef ze_result_t (__zecall *ze_pfnEventDestroy_t)(
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventHostSignal 
typedef ze_result_t (__zecall *ze_pfnEventHostSignal_t)(
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventHostSynchronize 
typedef ze_result_t (__zecall *ze_pfnEventHostSynchronize_t)(
    ze_event_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventQueryStatus 
typedef ze_result_t (__zecall *ze_pfnEventQueryStatus_t)(
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventHostReset 
typedef ze_result_t (__zecall *ze_pfnEventHostReset_t)(
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeEventGetTimestamp 
typedef ze_result_t (__zecall *ze_pfnEventGetTimestamp_t)(
    ze_event_handle_t,
    ze_event_timestamp_type_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Event functions pointers
typedef struct _ze_event_dditable_t
{
    ze_pfnEventCreate_t                                         pfnCreate;
    ze_pfnEventDestroy_t                                        pfnDestroy;
    ze_pfnEventHostSignal_t                                     pfnHostSignal;
    ze_pfnEventHostSynchronize_t                                pfnHostSynchronize;
    ze_pfnEventQueryStatus_t                                    pfnQueryStatus;
    ze_pfnEventHostReset_t                                      pfnHostReset;
    ze_pfnEventGetTimestamp_t                                   pfnGetTimestamp;
} ze_event_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetEventProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetEventProcAddrTable_t)(
    ze_api_version_t,
    ze_event_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeFenceCreate 
typedef ze_result_t (__zecall *ze_pfnFenceCreate_t)(
    ze_command_queue_handle_t,
    const ze_fence_desc_t*,
    ze_fence_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeFenceDestroy 
typedef ze_result_t (__zecall *ze_pfnFenceDestroy_t)(
    ze_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeFenceHostSynchronize 
typedef ze_result_t (__zecall *ze_pfnFenceHostSynchronize_t)(
    ze_fence_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeFenceQueryStatus 
typedef ze_result_t (__zecall *ze_pfnFenceQueryStatus_t)(
    ze_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeFenceReset 
typedef ze_result_t (__zecall *ze_pfnFenceReset_t)(
    ze_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Fence functions pointers
typedef struct _ze_fence_dditable_t
{
    ze_pfnFenceCreate_t                                         pfnCreate;
    ze_pfnFenceDestroy_t                                        pfnDestroy;
    ze_pfnFenceHostSynchronize_t                                pfnHostSynchronize;
    ze_pfnFenceQueryStatus_t                                    pfnQueryStatus;
    ze_pfnFenceReset_t                                          pfnReset;
} ze_fence_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetFenceProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetFenceProcAddrTable_t)(
    ze_api_version_t,
    ze_fence_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeSamplerCreate 
typedef ze_result_t (__zecall *ze_pfnSamplerCreate_t)(
    ze_device_handle_t,
    const ze_sampler_desc_t*,
    ze_sampler_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeSamplerDestroy 
typedef ze_result_t (__zecall *ze_pfnSamplerDestroy_t)(
    ze_sampler_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sampler functions pointers
typedef struct _ze_sampler_dditable_t
{
    ze_pfnSamplerCreate_t                                       pfnCreate;
    ze_pfnSamplerDestroy_t                                      pfnDestroy;
} ze_sampler_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zeGetSamplerProcAddrTable
typedef ze_result_t (__zecall *ze_pfnGetSamplerProcAddrTable_t)(
    ze_api_version_t,
    ze_sampler_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _ze_dditable_t
{
    ze_global_dditable_t                Global;
    ze_driver_dditable_t                Driver;
    ze_device_dditable_t                Device;
    ze_command_queue_dditable_t         CommandQueue;
    ze_command_list_dditable_t          CommandList;
    ze_image_dditable_t                 Image;
    ze_module_dditable_t                Module;
    ze_module_build_log_dditable_t      ModuleBuildLog;
    ze_kernel_dditable_t                Kernel;
    ze_event_pool_dditable_t            EventPool;
    ze_event_dditable_t                 Event;
    ze_fence_dditable_t                 Fence;
    ze_sampler_dditable_t               Sampler;
} ze_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_DDI_H