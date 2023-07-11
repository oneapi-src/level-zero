/*
 *
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_tracing_register_cb.h
 *
 */
#ifndef zel_tracing_register_cb_H
#define zel_tracing_register_cb_H
#if defined(__cplusplus)
#pragma once
#endif

#include "../ze_api.h"


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of tracer object
typedef struct _zel_tracer_handle_t *zel_tracer_handle_t;

/// Callback definitions for all API released in LevelZero spec 1.1 or newer
/// Callbacks for APIs included in spec 1.0 are contained in ze_api.helper

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASBuilderCreateExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_builder_create_exp_params_t
{
    ze_driver_handle_t* phDriver;
    const ze_rtas_builder_exp_desc_t** ppDescriptor;
    ze_rtas_builder_exp_handle_t** pphBuilder;
} ze_rtas_builder_create_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASBuilderCreateExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASBuilderCreateExpCb_t)(
    ze_rtas_builder_create_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASBuilderGetBuildPropertiesExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_builder_get_build_properties_exp_params_t
{
    ze_rtas_builder_exp_handle_t* phBuilder;
    const ze_rtas_builder_build_op_exp_desc_t** ppBuildOpDescriptor;
    ze_rtas_builder_exp_properties_t** ppProperties;
} ze_rtas_builder_get_build_properties_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASBuilderGetBuildPropertiesExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASBuilderGetBuildPropertiesExpCb_t)(
    ze_rtas_builder_get_build_properties_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASBuilderBuildExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_builder_build_exp_params_t
{
    ze_rtas_builder_exp_handle_t* phBuilder;
    const ze_rtas_builder_build_op_exp_desc_t** ppBuildOpDescriptor;
    void** ppScratchBuffer;
    size_t* pscratchBufferSizeBytes;
    void** ppRtasBuffer;
    size_t* prtasBufferSizeBytes;
    ze_rtas_parallel_operation_exp_handle_t* phParallelOperation;
    void** ppBuildUserPtr;
    ze_rtas_aabb_exp_t** ppBounds;
    size_t** ppRtasBufferSizeBytes;
} ze_rtas_builder_build_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASBuilderBuildExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASBuilderBuildExpCb_t)(
    ze_rtas_builder_build_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASBuilderDestroyExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_builder_destroy_exp_params_t
{
    ze_rtas_builder_exp_handle_t* phBuilder;
} ze_rtas_builder_destroy_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASBuilderDestroyExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASBuilderDestroyExpCb_t)(
    ze_rtas_builder_destroy_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASParallelOperationCreateExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_parallel_operation_create_exp_params_t
{
    ze_driver_handle_t* phDriver;
    ze_rtas_parallel_operation_exp_handle_t** pphParallelOperation;
} ze_rtas_parallel_operation_create_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASParallelOperationCreateExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASParallelOperationCreateExpCb_t)(
    ze_rtas_parallel_operation_create_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASParallelOperationGetPropertiesExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_parallel_operation_get_properties_exp_params_t
{
    ze_rtas_parallel_operation_exp_handle_t* phParallelOperation;
    ze_rtas_parallel_operation_exp_properties_t** ppProperties;
} ze_rtas_parallel_operation_get_properties_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASParallelOperationGetPropertiesExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASParallelOperationGetPropertiesExpCb_t)(
    ze_rtas_parallel_operation_get_properties_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASParallelOperationJoinExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_parallel_operation_join_exp_params_t
{
    ze_rtas_parallel_operation_exp_handle_t* phParallelOperation;
} ze_rtas_parallel_operation_join_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASParallelOperationJoinExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASParallelOperationJoinExpCb_t)(
    ze_rtas_parallel_operation_join_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeRTASParallelOperationDestroyExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_rtas_parallel_operation_destroy_exp_params_t
{
    ze_rtas_parallel_operation_exp_handle_t* phParallelOperation;
} ze_rtas_parallel_operation_destroy_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeRTASParallelOperationDestroyExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnRTASParallelOperationDestroyExpCb_t)(
    ze_rtas_parallel_operation_destroy_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetExtensionFunctionAddress
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_driver_get_extension_function_address_params_t
{
    ze_driver_handle_t* phDriver;
    const char** pname;
    void*** pppFunctionAddress;
} ze_driver_get_extension_function_address_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetExtensionFunctionAddress
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDriverGetExtensionFunctionAddressCb_t)(
    ze_driver_get_extension_function_address_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverGetLastErrorDescription
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_driver_get_last_error_description_params_t
{
    ze_driver_handle_t* phDriver;
    const char*** pppString;
} ze_driver_get_last_error_description_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverGetLastErrorDescription
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDriverGetLastErrorDescriptionCb_t)(
    ze_driver_get_last_error_description_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDriverRTASFormatCompatibilityCheckExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_driver_rtas_format_compatibility_check_exp_params_t
{
    ze_driver_handle_t* phDriver;
    ze_rtas_format_exp_t* prtasFormatA;
    ze_rtas_format_exp_t* prtasFormatB;
} ze_driver_rtas_format_compatibility_check_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDriverRTASFormatCompatibilityCheckExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDriverRTASFormatCompatibilityCheckExpCb_t)(
    ze_driver_rtas_format_compatibility_check_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetGlobalTimestamps
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_device_get_global_timestamps_params_t
{
    ze_device_handle_t* phDevice;
    uint64_t** phostTimestamp;
    uint64_t** pdeviceTimestamp;
} ze_device_get_global_timestamps_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetGlobalTimestamps
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDeviceGetGlobalTimestampsCb_t)(
    ze_device_get_global_timestamps_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceReserveCacheExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_device_reserve_cache_ext_params_t
{
    ze_device_handle_t* phDevice;
    size_t* pcacheLevel;
    size_t* pcacheReservationSize;
} ze_device_reserve_cache_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceReserveCacheExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDeviceReserveCacheExtCb_t)(
    ze_device_reserve_cache_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceSetCacheAdviceExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_device_set_cache_advice_ext_params_t
{
    ze_device_handle_t* phDevice;
    void** pptr;
    size_t* pregionSize;
    ze_cache_ext_region_t* pcacheRegion;
} ze_device_set_cache_advice_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceSetCacheAdviceExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDeviceSetCacheAdviceExtCb_t)(
    ze_device_set_cache_advice_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDevicePciGetPropertiesExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_device_pci_get_properties_ext_params_t
{
    ze_device_handle_t* phDevice;
    ze_pci_ext_properties_t** ppPciProperties;
} ze_device_pci_get_properties_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDevicePciGetPropertiesExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDevicePciGetPropertiesExtCb_t)(
    ze_device_pci_get_properties_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetFabricVertexExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_device_get_fabric_vertex_exp_params_t
{
    ze_device_handle_t* phDevice;
    ze_fabric_vertex_handle_t** pphVertex;
} ze_device_get_fabric_vertex_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetFabricVertexExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDeviceGetFabricVertexExpCb_t)(
    ze_device_get_fabric_vertex_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeDeviceGetRootDevice
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_device_get_root_device_params_t
{
    ze_device_handle_t* phDevice;
    ze_device_handle_t** pphRootDevice;
} ze_device_get_root_device_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeDeviceGetRootDevice
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnDeviceGetRootDeviceCb_t)(
    ze_device_get_root_device_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeContextCreateEx
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_context_create_ex_params_t
{
    ze_driver_handle_t* phDriver;
    const ze_context_desc_t** pdesc;
    uint32_t* pnumDevices;
    ze_device_handle_t** pphDevices;
    ze_context_handle_t** pphContext;
} ze_context_create_ex_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeContextCreateEx
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnContextCreateExCb_t)(
    ze_context_create_ex_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendImageCopyToMemoryExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_command_list_append_image_copy_to_memory_ext_params_t
{
    ze_command_list_handle_t* phCommandList;
    void** pdstptr;
    ze_image_handle_t* phSrcImage;
    const ze_image_region_t** ppSrcRegion;
    uint32_t* pdestRowPitch;
    uint32_t* pdestSlicePitch;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_image_copy_to_memory_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendImageCopyToMemoryExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnCommandListAppendImageCopyToMemoryExtCb_t)(
    ze_command_list_append_image_copy_to_memory_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListAppendImageCopyFromMemoryExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_command_list_append_image_copy_from_memory_ext_params_t
{
    ze_command_list_handle_t* phCommandList;
    ze_image_handle_t* phDstImage;
    const void** psrcptr;
    const ze_image_region_t** ppDstRegion;
    uint32_t* psrcRowPitch;
    uint32_t* psrcSlicePitch;
    ze_event_handle_t* phSignalEvent;
    uint32_t* pnumWaitEvents;
    ze_event_handle_t** pphWaitEvents;
} ze_command_list_append_image_copy_from_memory_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListAppendImageCopyFromMemoryExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnCommandListAppendImageCopyFromMemoryExtCb_t)(
    ze_command_list_append_image_copy_from_memory_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeCommandListHostSynchronize
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_command_list_host_synchronize_params_t
{
    ze_command_list_handle_t* phCommandList;
    uint64_t* ptimeout;
} ze_command_list_host_synchronize_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeCommandListHostSynchronize
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnCommandListHostSynchronizeCb_t)(
    ze_command_list_host_synchronize_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventQueryTimestampsExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_event_query_timestamps_exp_params_t
{
    ze_event_handle_t* phEvent;
    ze_device_handle_t* phDevice;
    uint32_t** ppCount;
    ze_kernel_timestamp_result_t** ppTimestamps;
} ze_event_query_timestamps_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventQueryTimestampsExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnEventQueryTimestampsExpCb_t)(
    ze_event_query_timestamps_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventQueryKernelTimestampsExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_event_query_kernel_timestamps_ext_params_t
{
    ze_event_handle_t* phEvent;
    ze_device_handle_t* phDevice;
    uint32_t** ppCount;
    ze_event_query_kernel_timestamps_results_ext_properties_t** ppResults;
} ze_event_query_kernel_timestamps_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventQueryKernelTimestampsExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnEventQueryKernelTimestampsExtCb_t)(
    ze_event_query_kernel_timestamps_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeEventPoolPutIpcHandle
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_event_pool_put_ipc_handle_params_t
{
    ze_context_handle_t* phContext;
    ze_ipc_event_pool_handle_t* phIpc;
} ze_event_pool_put_ipc_handle_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeEventPoolPutIpcHandle
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnEventPoolPutIpcHandleCb_t)(
    ze_event_pool_put_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeImageGetMemoryPropertiesExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_image_get_memory_properties_exp_params_t
{
    ze_image_handle_t* phImage;
    ze_image_memory_properties_exp_t** ppMemoryProperties;
} ze_image_get_memory_properties_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeImageGetMemoryPropertiesExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnImageGetMemoryPropertiesExpCb_t)(
    ze_image_get_memory_properties_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeImageViewCreateExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_image_view_create_exp_params_t
{
    ze_context_handle_t* phContext;
    ze_device_handle_t* phDevice;
    const ze_image_desc_t** pdesc;
    ze_image_handle_t* phImage;
    ze_image_handle_t** pphImageView;
} ze_image_view_create_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeImageViewCreateExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnImageViewCreateExpCb_t)(
    ze_image_view_create_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeImageGetAllocPropertiesExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_image_get_alloc_properties_ext_params_t
{
    ze_context_handle_t* phContext;
    ze_image_handle_t* phImage;
    ze_image_allocation_ext_properties_t** ppImageAllocProperties;
} ze_image_get_alloc_properties_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeImageGetAllocPropertiesExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnImageGetAllocPropertiesExtCb_t)(
    ze_image_get_alloc_properties_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeImageViewCreateExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_image_view_create_ext_params_t
{
    ze_context_handle_t* phContext;
    ze_device_handle_t* phDevice;
    const ze_image_desc_t** pdesc;
    ze_image_handle_t* phImage;
    ze_image_handle_t** pphImageView;
} ze_image_view_create_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeImageViewCreateExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnImageViewCreateExtCb_t)(
    ze_image_view_create_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSetGlobalOffsetExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_kernel_set_global_offset_exp_params_t
{
    ze_kernel_handle_t* phKernel;
    uint32_t* poffsetX;
    uint32_t* poffsetY;
    uint32_t* poffsetZ;
} ze_kernel_set_global_offset_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSetGlobalOffsetExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnKernelSetGlobalOffsetExpCb_t)(
    ze_kernel_set_global_offset_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeKernelSchedulingHintExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_kernel_scheduling_hint_exp_params_t
{
    ze_kernel_handle_t* phKernel;
    ze_scheduling_hint_exp_desc_t** ppHint;
} ze_kernel_scheduling_hint_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeKernelSchedulingHintExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnKernelSchedulingHintExpCb_t)(
    ze_kernel_scheduling_hint_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeMemFreeExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_mem_free_ext_params_t
{
    ze_context_handle_t* phContext;
    const ze_memory_free_ext_desc_t** ppMemFreeDesc;
    void** pptr;
} ze_mem_free_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeMemFreeExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnMemFreeExtCb_t)(
    ze_mem_free_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeMemGetIpcHandleFromFileDescriptorExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_mem_get_ipc_handle_from_file_descriptor_exp_params_t
{
    ze_context_handle_t* phContext;
    uint64_t* phandle;
    ze_ipc_mem_handle_t** ppIpcHandle;
} ze_mem_get_ipc_handle_from_file_descriptor_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeMemGetIpcHandleFromFileDescriptorExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnMemGetIpcHandleFromFileDescriptorExpCb_t)(
    ze_mem_get_ipc_handle_from_file_descriptor_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeMemGetFileDescriptorFromIpcHandleExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_mem_get_file_descriptor_from_ipc_handle_exp_params_t
{
    ze_context_handle_t* phContext;
    ze_ipc_mem_handle_t* pipcHandle;
    uint64_t** ppHandle;
} ze_mem_get_file_descriptor_from_ipc_handle_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeMemGetFileDescriptorFromIpcHandleExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnMemGetFileDescriptorFromIpcHandleExpCb_t)(
    ze_mem_get_file_descriptor_from_ipc_handle_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeMemPutIpcHandle
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_mem_put_ipc_handle_params_t
{
    ze_context_handle_t* phContext;
    ze_ipc_mem_handle_t* phandle;
} ze_mem_put_ipc_handle_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeMemPutIpcHandle
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnMemPutIpcHandleCb_t)(
    ze_mem_put_ipc_handle_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeMemSetAtomicAccessAttributeExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_mem_set_atomic_access_attribute_exp_params_t
{
    ze_context_handle_t* phContext;
    ze_device_handle_t* phDevice;
    const void** pptr;
    size_t* psize;
    ze_memory_atomic_attr_exp_flags_t* pattr;
} ze_mem_set_atomic_access_attribute_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeMemSetAtomicAccessAttributeExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnMemSetAtomicAccessAttributeExpCb_t)(
    ze_mem_set_atomic_access_attribute_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeMemGetAtomicAccessAttributeExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_mem_get_atomic_access_attribute_exp_params_t
{
    ze_context_handle_t* phContext;
    ze_device_handle_t* phDevice;
    const void** pptr;
    size_t* psize;
    ze_memory_atomic_attr_exp_flags_t** ppAttr;
} ze_mem_get_atomic_access_attribute_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeMemGetAtomicAccessAttributeExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnMemGetAtomicAccessAttributeExpCb_t)(
    ze_mem_get_atomic_access_attribute_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeModuleInspectLinkageExt
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_module_inspect_linkage_ext_params_t
{
    ze_linkage_inspection_ext_desc_t** ppInspectDesc;
    uint32_t* pnumModules;
    ze_module_handle_t** pphModules;
    ze_module_build_log_handle_t** pphLog;
} ze_module_inspect_linkage_ext_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeModuleInspectLinkageExt
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnModuleInspectLinkageExtCb_t)(
    ze_module_inspect_linkage_ext_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFabricEdgeGetExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_fabric_edge_get_exp_params_t
{
    ze_fabric_vertex_handle_t* phVertexA;
    ze_fabric_vertex_handle_t* phVertexB;
    uint32_t** ppCount;
    ze_fabric_edge_handle_t** pphEdges;
} ze_fabric_edge_get_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFabricEdgeGetExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnFabricEdgeGetExpCb_t)(
    ze_fabric_edge_get_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFabricEdgeGetVerticesExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_fabric_edge_get_vertices_exp_params_t
{
    ze_fabric_edge_handle_t* phEdge;
    ze_fabric_vertex_handle_t** pphVertexA;
    ze_fabric_vertex_handle_t** pphVertexB;
} ze_fabric_edge_get_vertices_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFabricEdgeGetVerticesExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnFabricEdgeGetVerticesExpCb_t)(
    ze_fabric_edge_get_vertices_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFabricEdgeGetPropertiesExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_fabric_edge_get_properties_exp_params_t
{
    ze_fabric_edge_handle_t* phEdge;
    ze_fabric_edge_exp_properties_t** ppEdgeProperties;
} ze_fabric_edge_get_properties_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFabricEdgeGetPropertiesExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnFabricEdgeGetPropertiesExpCb_t)(
    ze_fabric_edge_get_properties_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFabricVertexGetExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_fabric_vertex_get_exp_params_t
{
    ze_driver_handle_t* phDriver;
    uint32_t** ppCount;
    ze_fabric_vertex_handle_t** pphVertices;
} ze_fabric_vertex_get_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFabricVertexGetExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnFabricVertexGetExpCb_t)(
    ze_fabric_vertex_get_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFabricVertexGetSubVerticesExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_fabric_vertex_get_sub_vertices_exp_params_t
{
    ze_fabric_vertex_handle_t* phVertex;
    uint32_t** ppCount;
    ze_fabric_vertex_handle_t** pphSubvertices;
} ze_fabric_vertex_get_sub_vertices_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFabricVertexGetSubVerticesExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnFabricVertexGetSubVerticesExpCb_t)(
    ze_fabric_vertex_get_sub_vertices_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFabricVertexGetPropertiesExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_fabric_vertex_get_properties_exp_params_t
{
    ze_fabric_vertex_handle_t* phVertex;
    ze_fabric_vertex_exp_properties_t** ppVertexProperties;
} ze_fabric_vertex_get_properties_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFabricVertexGetPropertiesExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnFabricVertexGetPropertiesExpCb_t)(
    ze_fabric_vertex_get_properties_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function parameters for zeFabricVertexGetDeviceExp
/// @details Each entry is a pointer to the parameter passed to the function;
///     allowing the callback the ability to modify the parameter's value

typedef struct _ze_fabric_vertex_get_device_exp_params_t
{
    ze_fabric_vertex_handle_t* phVertex;
    ze_device_handle_t** pphDevice;
} ze_fabric_vertex_get_device_exp_params_t;


///////////////////////////////////////////////////////////////////////////////
/// @brief Callback function-pointer for zeFabricVertexGetDeviceExp
/// @param[in] params Parameters passed to this instance
/// @param[in] result Return value
/// @param[in] pTracerUserData Per-Tracer user data
/// @param[in,out] ppTracerInstanceUserData Per-Tracer, Per-Instance user data

typedef void (ZE_APICALL *ze_pfnFabricVertexGetDeviceExpCb_t)(
    ze_fabric_vertex_get_device_exp_params_t* params,
    ze_result_t result,
    void* pTracerUserData,
    void** ppTracerInstanceUserData
    );


typedef enum _zel_tracer_reg_t
{
    ZEL_REGISTER_PROLOGUE = 0,
    ZEL_REGISTER_EPILOGUE = 1     
} zel_tracer_reg_t;

/// APIs to register callbacks for each core API

ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerInitRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnInitCb_t pfnInitCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetCb_t pfnGetCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetApiVersionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetApiVersionCb_t pfnGetApiVersionCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetPropertiesCb_t pfnGetPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetIpcPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetIpcPropertiesCb_t pfnGetIpcPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetExtensionPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetExtensionPropertiesCb_t pfnGetExtensionPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetExtensionFunctionAddressRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetExtensionFunctionAddressCb_t pfnGetExtensionFunctionAddressCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetLastErrorDescriptionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetLastErrorDescriptionCb_t pfnGetLastErrorDescriptionCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetCb_t pfnGetCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetRootDeviceRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetRootDeviceCb_t pfnGetRootDeviceCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetSubDevicesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetSubDevicesCb_t pfnGetSubDevicesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetPropertiesCb_t pfnGetPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetComputePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetComputePropertiesCb_t pfnGetComputePropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetModulePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetModulePropertiesCb_t pfnGetModulePropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetCommandQueueGroupPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t pfnGetCommandQueueGroupPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetMemoryPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetMemoryPropertiesCb_t pfnGetMemoryPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetMemoryAccessPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetMemoryAccessPropertiesCb_t pfnGetMemoryAccessPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetCachePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetCachePropertiesCb_t pfnGetCachePropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetImagePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetImagePropertiesCb_t pfnGetImagePropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetExternalMemoryPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetExternalMemoryPropertiesCb_t pfnGetExternalMemoryPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetP2PPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetP2PPropertiesCb_t pfnGetP2PPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceCanAccessPeerRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceCanAccessPeerCb_t pfnCanAccessPeerCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetStatusCb_t pfnGetStatusCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetGlobalTimestampsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetGlobalTimestampsCb_t pfnGetGlobalTimestampsCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextCreateExRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextCreateExCb_t pfnCreateExCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextGetStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextGetStatusCb_t pfnGetStatusCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueExecuteCommandListsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueExecuteCommandListsCb_t pfnExecuteCommandListsCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueSynchronizeCb_t pfnSynchronizeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListCreateImmediateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListCreateImmediateCb_t pfnCreateImmediateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListCloseRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListCloseCb_t pfnCloseCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListResetCb_t pfnResetCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendWriteGlobalTimestampRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendWriteGlobalTimestampCb_t pfnAppendWriteGlobalTimestampCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListHostSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListHostSynchronizeCb_t pfnHostSynchronizeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendBarrierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendBarrierCb_t pfnAppendBarrierCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryRangesBarrierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryRangesBarrierCb_t pfnAppendMemoryRangesBarrierCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextSystemBarrierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextSystemBarrierCb_t pfnSystemBarrierCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryCopyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryCopyCb_t pfnAppendMemoryCopyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryFillRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryFillCb_t pfnAppendMemoryFillCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryCopyRegionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryCopyRegionCb_t pfnAppendMemoryCopyRegionCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryCopyFromContextRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryCopyFromContextCb_t pfnAppendMemoryCopyFromContextCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyCb_t pfnAppendImageCopyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyRegionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyRegionCb_t pfnAppendImageCopyRegionCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyToMemoryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyToMemoryCb_t pfnAppendImageCopyToMemoryCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyFromMemoryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyFromMemoryCb_t pfnAppendImageCopyFromMemoryCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryPrefetchRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryPrefetchCb_t pfnAppendMemoryPrefetchCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemAdviseRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemAdviseCb_t pfnAppendMemAdviseCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolGetIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolGetIpcHandleCb_t pfnGetIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolPutIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolPutIpcHandleCb_t pfnPutIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolOpenIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolOpenIpcHandleCb_t pfnOpenIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolCloseIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolCloseIpcHandleCb_t pfnCloseIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendSignalEventRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendSignalEventCb_t pfnAppendSignalEventCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendWaitOnEventsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendWaitOnEventsCb_t pfnAppendWaitOnEventsCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventHostSignalRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventHostSignalCb_t pfnHostSignalCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventHostSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventHostSynchronizeCb_t pfnHostSynchronizeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryStatusCb_t pfnQueryStatusCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendEventResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendEventResetCb_t pfnAppendEventResetCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventHostResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventHostResetCb_t pfnHostResetCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryKernelTimestampRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryKernelTimestampCb_t pfnQueryKernelTimestampCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendQueryKernelTimestampsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendQueryKernelTimestampsCb_t pfnAppendQueryKernelTimestampsCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceHostSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceHostSynchronizeCb_t pfnHostSynchronizeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceQueryStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceQueryStatusCb_t pfnQueryStatusCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceResetCb_t pfnResetCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageGetPropertiesCb_t pfnGetPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemAllocSharedRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemAllocSharedCb_t pfnAllocSharedCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemAllocDeviceRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemAllocDeviceCb_t pfnAllocDeviceCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemAllocHostRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemAllocHostCb_t pfnAllocHostCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemFreeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemFreeCb_t pfnFreeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetAllocPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetAllocPropertiesCb_t pfnGetAllocPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetAddressRangeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetAddressRangeCb_t pfnGetAddressRangeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetIpcHandleCb_t pfnGetIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetIpcHandleFromFileDescriptorExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetIpcHandleFromFileDescriptorExpCb_t pfnGetIpcHandleFromFileDescriptorExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetFileDescriptorFromIpcHandleExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetFileDescriptorFromIpcHandleExpCb_t pfnGetFileDescriptorFromIpcHandleExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemPutIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemPutIpcHandleCb_t pfnPutIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemOpenIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemOpenIpcHandleCb_t pfnOpenIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemCloseIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemCloseIpcHandleCb_t pfnCloseIpcHandleCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemSetAtomicAccessAttributeExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemSetAtomicAccessAttributeExpCb_t pfnSetAtomicAccessAttributeExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetAtomicAccessAttributeExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetAtomicAccessAttributeExpCb_t pfnGetAtomicAccessAttributeExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleDynamicLinkRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleDynamicLinkCb_t pfnDynamicLinkCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleBuildLogDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleBuildLogDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleBuildLogGetStringRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleBuildLogGetStringCb_t pfnGetStringCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetNativeBinaryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetNativeBinaryCb_t pfnGetNativeBinaryCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetGlobalPointerRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetGlobalPointerCb_t pfnGetGlobalPointerCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetKernelNamesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetKernelNamesCb_t pfnGetKernelNamesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetPropertiesCb_t pfnGetPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetFunctionPointerRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetFunctionPointerCb_t pfnGetFunctionPointerCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetGroupSizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetGroupSizeCb_t pfnSetGroupSizeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSuggestGroupSizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSuggestGroupSizeCb_t pfnSuggestGroupSizeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSuggestMaxCooperativeGroupCountRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t pfnSuggestMaxCooperativeGroupCountCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetArgumentValueRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetArgumentValueCb_t pfnSetArgumentValueCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetIndirectAccessRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetIndirectAccessCb_t pfnSetIndirectAccessCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetIndirectAccessRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetIndirectAccessCb_t pfnGetIndirectAccessCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetSourceAttributesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetSourceAttributesCb_t pfnGetSourceAttributesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetCacheConfigRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetCacheConfigCb_t pfnSetCacheConfigCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetPropertiesCb_t pfnGetPropertiesCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetNameRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetNameCb_t pfnGetNameCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchKernelRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchKernelCb_t pfnAppendLaunchKernelCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchCooperativeKernelRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchCooperativeKernelCb_t pfnAppendLaunchCooperativeKernelCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchKernelIndirectRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchKernelIndirectCb_t pfnAppendLaunchKernelIndirectCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchMultipleKernelsIndirectRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t pfnAppendLaunchMultipleKernelsIndirectCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextMakeMemoryResidentRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextMakeMemoryResidentCb_t pfnMakeMemoryResidentCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextEvictMemoryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextEvictMemoryCb_t pfnEvictMemoryCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextMakeImageResidentRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextMakeImageResidentCb_t pfnMakeImageResidentCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextEvictImageRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextEvictImageCb_t pfnEvictImageCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerSamplerCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnSamplerCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerSamplerDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnSamplerDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemReserveRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemReserveCb_t pfnReserveCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemFreeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemFreeCb_t pfnFreeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemQueryPageSizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemQueryPageSizeCb_t pfnQueryPageSizeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerPhysicalMemCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnPhysicalMemCreateCb_t pfnCreateCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerPhysicalMemDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnPhysicalMemDestroyCb_t pfnDestroyCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemMapRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemMapCb_t pfnMapCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemUnmapRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemUnmapCb_t pfnUnmapCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemSetAccessAttributeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemSetAccessAttributeCb_t pfnSetAccessAttributeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemGetAccessAttributeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemGetAccessAttributeCb_t pfnGetAccessAttributeCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetGlobalOffsetExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetGlobalOffsetExpCb_t pfnSetGlobalOffsetExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceReserveCacheExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceReserveCacheExtCb_t pfnReserveCacheExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceSetCacheAdviceExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceSetCacheAdviceExtCb_t pfnSetCacheAdviceExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryTimestampsExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryTimestampsExpCb_t pfnQueryTimestampsExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageGetMemoryPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageGetMemoryPropertiesExpCb_t pfnGetMemoryPropertiesExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageViewCreateExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageViewCreateExtCb_t pfnViewCreateExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageViewCreateExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageViewCreateExpCb_t pfnViewCreateExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSchedulingHintExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSchedulingHintExpCb_t pfnSchedulingHintExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDevicePciGetPropertiesExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDevicePciGetPropertiesExtCb_t pfnPciGetPropertiesExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyToMemoryExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyToMemoryExtCb_t pfnAppendImageCopyToMemoryExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyFromMemoryExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyFromMemoryExtCb_t pfnAppendImageCopyFromMemoryExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageGetAllocPropertiesExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageGetAllocPropertiesExtCb_t pfnGetAllocPropertiesExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleInspectLinkageExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleInspectLinkageExtCb_t pfnInspectLinkageExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemFreeExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemFreeExtCb_t pfnFreeExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetExpCb_t pfnGetExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetSubVerticesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetSubVerticesExpCb_t pfnGetSubVerticesExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetPropertiesExpCb_t pfnGetPropertiesExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetDeviceExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetDeviceExpCb_t pfnGetDeviceExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetFabricVertexExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetFabricVertexExpCb_t pfnGetFabricVertexExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricEdgeGetExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricEdgeGetExpCb_t pfnGetExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricEdgeGetVerticesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricEdgeGetVerticesExpCb_t pfnGetVerticesExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricEdgeGetPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricEdgeGetPropertiesExpCb_t pfnGetPropertiesExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryKernelTimestampsExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryKernelTimestampsExtCb_t pfnQueryKernelTimestampsExtCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderCreateExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderCreateExpCb_t pfnCreateExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderGetBuildPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderGetBuildPropertiesExpCb_t pfnGetBuildPropertiesExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverRTASFormatCompatibilityCheckExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverRTASFormatCompatibilityCheckExpCb_t pfnRTASFormatCompatibilityCheckExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderBuildExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderBuildExpCb_t pfnBuildExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderDestroyExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderDestroyExpCb_t pfnDestroyExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationCreateExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationCreateExpCb_t pfnCreateExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationGetPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationGetPropertiesExpCb_t pfnGetPropertiesExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationJoinExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationJoinExpCb_t pfnJoinExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationDestroyExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationDestroyExpCb_t pfnDestroyExpCb
    );


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerResetAllCallbacks(zel_tracer_handle_t hTracer);


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // zel_tracing_register_cb_H
