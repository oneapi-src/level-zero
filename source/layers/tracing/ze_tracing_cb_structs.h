/*
 *
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_tracing_cb_structs.h
 *
 */
#ifndef ze_tracing_cb_structs_H
#define ze_tracing_cb_structs_H
#if defined(__cplusplus)
#pragma once
#endif

#include "ze_api.h"
#include "layers/zel_tracing_register_cb.h"



///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _zel_global_callbacks_t
{
    ze_pfnInitCb_t                                                  pfnInitCb;
} zel_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of RTASBuilder callback functions pointers
typedef struct _zel_rtas_builder_callbacks_t
{
    ze_pfnRTASBuilderCreateExpCb_t                                  pfnCreateExpCb;
    ze_pfnRTASBuilderGetBuildPropertiesExpCb_t                      pfnGetBuildPropertiesExpCb;
    ze_pfnRTASBuilderBuildExpCb_t                                   pfnBuildExpCb;
    ze_pfnRTASBuilderDestroyExpCb_t                                 pfnDestroyExpCb;
} zel_rtas_builder_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of RTASParallelOperation callback functions pointers
typedef struct _zel_rtas_parallel_operation_callbacks_t
{
    ze_pfnRTASParallelOperationCreateExpCb_t                        pfnCreateExpCb;
    ze_pfnRTASParallelOperationGetPropertiesExpCb_t                 pfnGetPropertiesExpCb;
    ze_pfnRTASParallelOperationJoinExpCb_t                          pfnJoinExpCb;
    ze_pfnRTASParallelOperationDestroyExpCb_t                       pfnDestroyExpCb;
} zel_rtas_parallel_operation_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Driver callback functions pointers
typedef struct _zel_driver_callbacks_t
{
    ze_pfnDriverGetCb_t                                             pfnGetCb;
    ze_pfnDriverGetApiVersionCb_t                                   pfnGetApiVersionCb;
    ze_pfnDriverGetPropertiesCb_t                                   pfnGetPropertiesCb;
    ze_pfnDriverGetIpcPropertiesCb_t                                pfnGetIpcPropertiesCb;
    ze_pfnDriverGetExtensionPropertiesCb_t                          pfnGetExtensionPropertiesCb;
    ze_pfnDriverGetExtensionFunctionAddressCb_t                     pfnGetExtensionFunctionAddressCb;
    ze_pfnDriverGetLastErrorDescriptionCb_t                         pfnGetLastErrorDescriptionCb;
    ze_pfnDriverRTASFormatCompatibilityCheckExpCb_t                 pfnRTASFormatCompatibilityCheckExpCb;
} zel_driver_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device callback functions pointers
typedef struct _zel_device_callbacks_t
{
    ze_pfnDeviceGetCb_t                                             pfnGetCb;
    ze_pfnDeviceGetSubDevicesCb_t                                   pfnGetSubDevicesCb;
    ze_pfnDeviceGetPropertiesCb_t                                   pfnGetPropertiesCb;
    ze_pfnDeviceGetComputePropertiesCb_t                            pfnGetComputePropertiesCb;
    ze_pfnDeviceGetModulePropertiesCb_t                             pfnGetModulePropertiesCb;
    ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t                  pfnGetCommandQueueGroupPropertiesCb;
    ze_pfnDeviceGetMemoryPropertiesCb_t                             pfnGetMemoryPropertiesCb;
    ze_pfnDeviceGetMemoryAccessPropertiesCb_t                       pfnGetMemoryAccessPropertiesCb;
    ze_pfnDeviceGetCachePropertiesCb_t                              pfnGetCachePropertiesCb;
    ze_pfnDeviceGetImagePropertiesCb_t                              pfnGetImagePropertiesCb;
    ze_pfnDeviceGetExternalMemoryPropertiesCb_t                     pfnGetExternalMemoryPropertiesCb;
    ze_pfnDeviceGetP2PPropertiesCb_t                                pfnGetP2PPropertiesCb;
    ze_pfnDeviceCanAccessPeerCb_t                                   pfnCanAccessPeerCb;
    ze_pfnDeviceGetStatusCb_t                                       pfnGetStatusCb;
    ze_pfnDeviceGetGlobalTimestampsCb_t                             pfnGetGlobalTimestampsCb;
    ze_pfnDeviceReserveCacheExtCb_t                                 pfnReserveCacheExtCb;
    ze_pfnDeviceSetCacheAdviceExtCb_t                               pfnSetCacheAdviceExtCb;
    ze_pfnDevicePciGetPropertiesExtCb_t                             pfnPciGetPropertiesExtCb;
    ze_pfnDeviceGetFabricVertexExpCb_t                              pfnGetFabricVertexExpCb;
    ze_pfnDeviceGetRootDeviceCb_t                                   pfnGetRootDeviceCb;
} zel_device_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Context callback functions pointers
typedef struct _zel_context_callbacks_t
{
    ze_pfnContextCreateCb_t                                         pfnCreateCb;
    ze_pfnContextDestroyCb_t                                        pfnDestroyCb;
    ze_pfnContextGetStatusCb_t                                      pfnGetStatusCb;
    ze_pfnContextSystemBarrierCb_t                                  pfnSystemBarrierCb;
    ze_pfnContextMakeMemoryResidentCb_t                             pfnMakeMemoryResidentCb;
    ze_pfnContextEvictMemoryCb_t                                    pfnEvictMemoryCb;
    ze_pfnContextMakeImageResidentCb_t                              pfnMakeImageResidentCb;
    ze_pfnContextEvictImageCb_t                                     pfnEvictImageCb;
    ze_pfnContextCreateExCb_t                                       pfnCreateExCb;
} zel_context_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandQueue callback functions pointers
typedef struct _zel_command_queue_callbacks_t
{
    ze_pfnCommandQueueCreateCb_t                                    pfnCreateCb;
    ze_pfnCommandQueueDestroyCb_t                                   pfnDestroyCb;
    ze_pfnCommandQueueExecuteCommandListsCb_t                       pfnExecuteCommandListsCb;
    ze_pfnCommandQueueSynchronizeCb_t                               pfnSynchronizeCb;
} zel_command_queue_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList callback functions pointers
typedef struct _zel_command_list_callbacks_t
{
    ze_pfnCommandListCreateCb_t                                     pfnCreateCb;
    ze_pfnCommandListCreateImmediateCb_t                            pfnCreateImmediateCb;
    ze_pfnCommandListDestroyCb_t                                    pfnDestroyCb;
    ze_pfnCommandListCloseCb_t                                      pfnCloseCb;
    ze_pfnCommandListResetCb_t                                      pfnResetCb;
    ze_pfnCommandListAppendWriteGlobalTimestampCb_t                 pfnAppendWriteGlobalTimestampCb;
    ze_pfnCommandListAppendBarrierCb_t                              pfnAppendBarrierCb;
    ze_pfnCommandListAppendMemoryRangesBarrierCb_t                  pfnAppendMemoryRangesBarrierCb;
    ze_pfnCommandListAppendMemoryCopyCb_t                           pfnAppendMemoryCopyCb;
    ze_pfnCommandListAppendMemoryFillCb_t                           pfnAppendMemoryFillCb;
    ze_pfnCommandListAppendMemoryCopyRegionCb_t                     pfnAppendMemoryCopyRegionCb;
    ze_pfnCommandListAppendMemoryCopyFromContextCb_t                pfnAppendMemoryCopyFromContextCb;
    ze_pfnCommandListAppendImageCopyCb_t                            pfnAppendImageCopyCb;
    ze_pfnCommandListAppendImageCopyRegionCb_t                      pfnAppendImageCopyRegionCb;
    ze_pfnCommandListAppendImageCopyToMemoryCb_t                    pfnAppendImageCopyToMemoryCb;
    ze_pfnCommandListAppendImageCopyFromMemoryCb_t                  pfnAppendImageCopyFromMemoryCb;
    ze_pfnCommandListAppendMemoryPrefetchCb_t                       pfnAppendMemoryPrefetchCb;
    ze_pfnCommandListAppendMemAdviseCb_t                            pfnAppendMemAdviseCb;
    ze_pfnCommandListAppendSignalEventCb_t                          pfnAppendSignalEventCb;
    ze_pfnCommandListAppendWaitOnEventsCb_t                         pfnAppendWaitOnEventsCb;
    ze_pfnCommandListAppendEventResetCb_t                           pfnAppendEventResetCb;
    ze_pfnCommandListAppendQueryKernelTimestampsCb_t                pfnAppendQueryKernelTimestampsCb;
    ze_pfnCommandListAppendLaunchKernelCb_t                         pfnAppendLaunchKernelCb;
    ze_pfnCommandListAppendLaunchCooperativeKernelCb_t              pfnAppendLaunchCooperativeKernelCb;
    ze_pfnCommandListAppendLaunchKernelIndirectCb_t                 pfnAppendLaunchKernelIndirectCb;
    ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t        pfnAppendLaunchMultipleKernelsIndirectCb;
    ze_pfnCommandListAppendImageCopyToMemoryExtCb_t                 pfnAppendImageCopyToMemoryExtCb;
    ze_pfnCommandListAppendImageCopyFromMemoryExtCb_t               pfnAppendImageCopyFromMemoryExtCb;
    ze_pfnCommandListHostSynchronizeCb_t                            pfnHostSynchronizeCb;
} zel_command_list_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Event callback functions pointers
typedef struct _zel_event_callbacks_t
{
    ze_pfnEventCreateCb_t                                           pfnCreateCb;
    ze_pfnEventDestroyCb_t                                          pfnDestroyCb;
    ze_pfnEventHostSignalCb_t                                       pfnHostSignalCb;
    ze_pfnEventHostSynchronizeCb_t                                  pfnHostSynchronizeCb;
    ze_pfnEventQueryStatusCb_t                                      pfnQueryStatusCb;
    ze_pfnEventHostResetCb_t                                        pfnHostResetCb;
    ze_pfnEventQueryKernelTimestampCb_t                             pfnQueryKernelTimestampCb;
    ze_pfnEventQueryTimestampsExpCb_t                               pfnQueryTimestampsExpCb;
    ze_pfnEventQueryKernelTimestampsExtCb_t                         pfnQueryKernelTimestampsExtCb;
} zel_event_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of EventPool callback functions pointers
typedef struct _zel_event_pool_callbacks_t
{
    ze_pfnEventPoolCreateCb_t                                       pfnCreateCb;
    ze_pfnEventPoolDestroyCb_t                                      pfnDestroyCb;
    ze_pfnEventPoolGetIpcHandleCb_t                                 pfnGetIpcHandleCb;
    ze_pfnEventPoolOpenIpcHandleCb_t                                pfnOpenIpcHandleCb;
    ze_pfnEventPoolCloseIpcHandleCb_t                               pfnCloseIpcHandleCb;
    ze_pfnEventPoolPutIpcHandleCb_t                                 pfnPutIpcHandleCb;
} zel_event_pool_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Fence callback functions pointers
typedef struct _zel_fence_callbacks_t
{
    ze_pfnFenceCreateCb_t                                           pfnCreateCb;
    ze_pfnFenceDestroyCb_t                                          pfnDestroyCb;
    ze_pfnFenceHostSynchronizeCb_t                                  pfnHostSynchronizeCb;
    ze_pfnFenceQueryStatusCb_t                                      pfnQueryStatusCb;
    ze_pfnFenceResetCb_t                                            pfnResetCb;
} zel_fence_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Image callback functions pointers
typedef struct _zel_image_callbacks_t
{
    ze_pfnImageGetPropertiesCb_t                                    pfnGetPropertiesCb;
    ze_pfnImageCreateCb_t                                           pfnCreateCb;
    ze_pfnImageDestroyCb_t                                          pfnDestroyCb;
    ze_pfnImageGetMemoryPropertiesExpCb_t                           pfnGetMemoryPropertiesExpCb;
    ze_pfnImageViewCreateExpCb_t                                    pfnViewCreateExpCb;
    ze_pfnImageGetAllocPropertiesExtCb_t                            pfnGetAllocPropertiesExtCb;
    ze_pfnImageViewCreateExtCb_t                                    pfnViewCreateExtCb;
} zel_image_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Kernel callback functions pointers
typedef struct _zel_kernel_callbacks_t
{
    ze_pfnKernelCreateCb_t                                          pfnCreateCb;
    ze_pfnKernelDestroyCb_t                                         pfnDestroyCb;
    ze_pfnKernelSetCacheConfigCb_t                                  pfnSetCacheConfigCb;
    ze_pfnKernelSetGroupSizeCb_t                                    pfnSetGroupSizeCb;
    ze_pfnKernelSuggestGroupSizeCb_t                                pfnSuggestGroupSizeCb;
    ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t                 pfnSuggestMaxCooperativeGroupCountCb;
    ze_pfnKernelSetArgumentValueCb_t                                pfnSetArgumentValueCb;
    ze_pfnKernelSetIndirectAccessCb_t                               pfnSetIndirectAccessCb;
    ze_pfnKernelGetIndirectAccessCb_t                               pfnGetIndirectAccessCb;
    ze_pfnKernelGetSourceAttributesCb_t                             pfnGetSourceAttributesCb;
    ze_pfnKernelGetPropertiesCb_t                                   pfnGetPropertiesCb;
    ze_pfnKernelGetNameCb_t                                         pfnGetNameCb;
    ze_pfnKernelSetGlobalOffsetExpCb_t                              pfnSetGlobalOffsetExpCb;
    ze_pfnKernelSchedulingHintExpCb_t                               pfnSchedulingHintExpCb;
} zel_kernel_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Mem callback functions pointers
typedef struct _zel_mem_callbacks_t
{
    ze_pfnMemAllocSharedCb_t                                        pfnAllocSharedCb;
    ze_pfnMemAllocDeviceCb_t                                        pfnAllocDeviceCb;
    ze_pfnMemAllocHostCb_t                                          pfnAllocHostCb;
    ze_pfnMemFreeCb_t                                               pfnFreeCb;
    ze_pfnMemGetAllocPropertiesCb_t                                 pfnGetAllocPropertiesCb;
    ze_pfnMemGetAddressRangeCb_t                                    pfnGetAddressRangeCb;
    ze_pfnMemGetIpcHandleCb_t                                       pfnGetIpcHandleCb;
    ze_pfnMemOpenIpcHandleCb_t                                      pfnOpenIpcHandleCb;
    ze_pfnMemCloseIpcHandleCb_t                                     pfnCloseIpcHandleCb;
    ze_pfnMemFreeExtCb_t                                            pfnFreeExtCb;
    ze_pfnMemGetIpcHandleFromFileDescriptorExpCb_t                  pfnGetIpcHandleFromFileDescriptorExpCb;
    ze_pfnMemGetFileDescriptorFromIpcHandleExpCb_t                  pfnGetFileDescriptorFromIpcHandleExpCb;
    ze_pfnMemPutIpcHandleCb_t                                       pfnPutIpcHandleCb;
    ze_pfnMemSetAtomicAccessAttributeExpCb_t                        pfnSetAtomicAccessAttributeExpCb;
    ze_pfnMemGetAtomicAccessAttributeExpCb_t                        pfnGetAtomicAccessAttributeExpCb;
} zel_mem_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module callback functions pointers
typedef struct _zel_module_callbacks_t
{
    ze_pfnModuleCreateCb_t                                          pfnCreateCb;
    ze_pfnModuleDestroyCb_t                                         pfnDestroyCb;
    ze_pfnModuleDynamicLinkCb_t                                     pfnDynamicLinkCb;
    ze_pfnModuleGetNativeBinaryCb_t                                 pfnGetNativeBinaryCb;
    ze_pfnModuleGetGlobalPointerCb_t                                pfnGetGlobalPointerCb;
    ze_pfnModuleGetKernelNamesCb_t                                  pfnGetKernelNamesCb;
    ze_pfnModuleGetPropertiesCb_t                                   pfnGetPropertiesCb;
    ze_pfnModuleGetFunctionPointerCb_t                              pfnGetFunctionPointerCb;
    ze_pfnModuleInspectLinkageExtCb_t                               pfnInspectLinkageExtCb;
} zel_module_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ModuleBuildLog callback functions pointers
typedef struct _zel_module_build_log_callbacks_t
{
    ze_pfnModuleBuildLogDestroyCb_t                                 pfnDestroyCb;
    ze_pfnModuleBuildLogGetStringCb_t                               pfnGetStringCb;
} zel_module_build_log_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of PhysicalMem callback functions pointers
typedef struct _zel_physical_mem_callbacks_t
{
    ze_pfnPhysicalMemCreateCb_t                                     pfnCreateCb;
    ze_pfnPhysicalMemDestroyCb_t                                    pfnDestroyCb;
} zel_physical_mem_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sampler callback functions pointers
typedef struct _zel_sampler_callbacks_t
{
    ze_pfnSamplerCreateCb_t                                         pfnCreateCb;
    ze_pfnSamplerDestroyCb_t                                        pfnDestroyCb;
} zel_sampler_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of VirtualMem callback functions pointers
typedef struct _zel_virtual_mem_callbacks_t
{
    ze_pfnVirtualMemReserveCb_t                                     pfnReserveCb;
    ze_pfnVirtualMemFreeCb_t                                        pfnFreeCb;
    ze_pfnVirtualMemQueryPageSizeCb_t                               pfnQueryPageSizeCb;
    ze_pfnVirtualMemMapCb_t                                         pfnMapCb;
    ze_pfnVirtualMemUnmapCb_t                                       pfnUnmapCb;
    ze_pfnVirtualMemSetAccessAttributeCb_t                          pfnSetAccessAttributeCb;
    ze_pfnVirtualMemGetAccessAttributeCb_t                          pfnGetAccessAttributeCb;
} zel_virtual_mem_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of FabricEdge callback functions pointers
typedef struct _zel_fabric_edge_callbacks_t
{
    ze_pfnFabricEdgeGetExpCb_t                                      pfnGetExpCb;
    ze_pfnFabricEdgeGetVerticesExpCb_t                              pfnGetVerticesExpCb;
    ze_pfnFabricEdgeGetPropertiesExpCb_t                            pfnGetPropertiesExpCb;
} zel_fabric_edge_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of FabricVertex callback functions pointers
typedef struct _zel_fabric_vertex_callbacks_t
{
    ze_pfnFabricVertexGetExpCb_t                                    pfnGetExpCb;
    ze_pfnFabricVertexGetSubVerticesExpCb_t                         pfnGetSubVerticesExpCb;
    ze_pfnFabricVertexGetPropertiesExpCb_t                          pfnGetPropertiesExpCb;
    ze_pfnFabricVertexGetDeviceExpCb_t                              pfnGetDeviceExpCb;
} zel_fabric_vertex_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _zel_all_core_callbacks_t
{
    zel_global_callbacks_t              Global;
    zel_rtas_builder_callbacks_t        RTASBuilder;
    zel_rtas_parallel_operation_callbacks_t RTASParallelOperation;
    zel_driver_callbacks_t              Driver;
    zel_device_callbacks_t              Device;
    zel_context_callbacks_t             Context;
    zel_command_queue_callbacks_t       CommandQueue;
    zel_command_list_callbacks_t        CommandList;
    zel_event_callbacks_t               Event;
    zel_event_pool_callbacks_t          EventPool;
    zel_fence_callbacks_t               Fence;
    zel_image_callbacks_t               Image;
    zel_kernel_callbacks_t              Kernel;
    zel_mem_callbacks_t                 Mem;
    zel_module_callbacks_t              Module;
    zel_module_build_log_callbacks_t    ModuleBuildLog;
    zel_physical_mem_callbacks_t        PhysicalMem;
    zel_sampler_callbacks_t             Sampler;
    zel_virtual_mem_callbacks_t         VirtualMem;
    zel_fabric_edge_callbacks_t         FabricEdge;
    zel_fabric_vertex_callbacks_t       FabricVertex;
} zel_all_core_callbacks_t;



#endif // ze_tracing_cb_structs_H
