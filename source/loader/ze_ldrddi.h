/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_ldrddi.h
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using ze_driver_object_t                  = object_t < ze_driver_handle_t >;
    using ze_driver_factory_t                 = singleton_factory_t < ze_driver_object_t, ze_driver_handle_t >;

    using ze_device_object_t                  = object_t < ze_device_handle_t >;
    using ze_device_factory_t                 = singleton_factory_t < ze_device_object_t, ze_device_handle_t >;

    using ze_context_object_t                 = object_t < ze_context_handle_t >;
    using ze_context_factory_t                = singleton_factory_t < ze_context_object_t, ze_context_handle_t >;

    using ze_command_queue_object_t           = object_t < ze_command_queue_handle_t >;
    using ze_command_queue_factory_t          = singleton_factory_t < ze_command_queue_object_t, ze_command_queue_handle_t >;

    using ze_command_list_object_t            = object_t < ze_command_list_handle_t >;
    using ze_command_list_factory_t           = singleton_factory_t < ze_command_list_object_t, ze_command_list_handle_t >;

    using ze_fence_object_t                   = object_t < ze_fence_handle_t >;
    using ze_fence_factory_t                  = singleton_factory_t < ze_fence_object_t, ze_fence_handle_t >;

    using ze_event_pool_object_t              = object_t < ze_event_pool_handle_t >;
    using ze_event_pool_factory_t             = singleton_factory_t < ze_event_pool_object_t, ze_event_pool_handle_t >;

    using ze_event_object_t                   = object_t < ze_event_handle_t >;
    using ze_event_factory_t                  = singleton_factory_t < ze_event_object_t, ze_event_handle_t >;

    using ze_image_object_t                   = object_t < ze_image_handle_t >;
    using ze_image_factory_t                  = singleton_factory_t < ze_image_object_t, ze_image_handle_t >;

    using ze_module_object_t                  = object_t < ze_module_handle_t >;
    using ze_module_factory_t                 = singleton_factory_t < ze_module_object_t, ze_module_handle_t >;

    using ze_module_build_log_object_t        = object_t < ze_module_build_log_handle_t >;
    using ze_module_build_log_factory_t       = singleton_factory_t < ze_module_build_log_object_t, ze_module_build_log_handle_t >;

    using ze_kernel_object_t                  = object_t < ze_kernel_handle_t >;
    using ze_kernel_factory_t                 = singleton_factory_t < ze_kernel_object_t, ze_kernel_handle_t >;

    using ze_sampler_object_t                 = object_t < ze_sampler_handle_t >;
    using ze_sampler_factory_t                = singleton_factory_t < ze_sampler_object_t, ze_sampler_handle_t >;

    using ze_physical_mem_object_t            = object_t < ze_physical_mem_handle_t >;
    using ze_physical_mem_factory_t           = singleton_factory_t < ze_physical_mem_object_t, ze_physical_mem_handle_t >;

    using ze_fabric_vertex_object_t           = object_t < ze_fabric_vertex_handle_t >;
    using ze_fabric_vertex_factory_t          = singleton_factory_t < ze_fabric_vertex_object_t, ze_fabric_vertex_handle_t >;

    using ze_fabric_edge_object_t             = object_t < ze_fabric_edge_handle_t >;
    using ze_fabric_edge_factory_t            = singleton_factory_t < ze_fabric_edge_object_t, ze_fabric_edge_handle_t >;

    using ze_external_semaphore_ext_object_t  = object_t < ze_external_semaphore_ext_handle_t >;
    using ze_external_semaphore_ext_factory_t = singleton_factory_t < ze_external_semaphore_ext_object_t, ze_external_semaphore_ext_handle_t >;

    using ze_rtas_builder_ext_object_t        = object_t < ze_rtas_builder_ext_handle_t >;
    using ze_rtas_builder_ext_factory_t       = singleton_factory_t < ze_rtas_builder_ext_object_t, ze_rtas_builder_ext_handle_t >;

    using ze_rtas_parallel_operation_ext_object_t = object_t < ze_rtas_parallel_operation_ext_handle_t >;
    using ze_rtas_parallel_operation_ext_factory_t    = singleton_factory_t < ze_rtas_parallel_operation_ext_object_t, ze_rtas_parallel_operation_ext_handle_t >;

    using ze_rtas_builder_exp_object_t        = object_t < ze_rtas_builder_exp_handle_t >;
    using ze_rtas_builder_exp_factory_t       = singleton_factory_t < ze_rtas_builder_exp_object_t, ze_rtas_builder_exp_handle_t >;

    using ze_rtas_parallel_operation_exp_object_t = object_t < ze_rtas_parallel_operation_exp_handle_t >;
    using ze_rtas_parallel_operation_exp_factory_t    = singleton_factory_t < ze_rtas_parallel_operation_exp_object_t, ze_rtas_parallel_operation_exp_handle_t >;

}

namespace loader_driver_ddi
{
    __zedlllocal void ZE_APICALL
    zeDestroyDDiDriverTables(ze_dditable_driver_t* pDdiTable);
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of extension properties available.
                                                        ///< if count is greater than the number of extension properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< extension properties available.
        ze_driver_extension_properties_t* pExtensionProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< extension properties.
                                                        ///< if count is less than the number of extension properties available,
                                                        ///< then driver shall only retrieve that number of extension properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetLastErrorDescription(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        );
    __zedlllocal ze_context_handle_t ZE_APICALL
    zeDriverGetDefaultContext(
        ze_driver_handle_t hDriver                      ///< [in] handle of the driver instance
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGet(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of devices available.
                                                        ///< if count is greater than the number of devices available, then the
                                                        ///< driver shall update the value with the correct number of devices available.
        ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices.
                                                        ///< if count is less than the number of devices available, then driver
                                                        ///< shall only retrieve that number of devices.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetRootDevice(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetSubDevices(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sub-devices available.
                                                        ///< if count is greater than the number of sub-devices available, then the
                                                        ///< driver shall update the value with the correct number of sub-devices available.
        ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices.
                                                        ///< if count is less than the number of sub-devices available, then driver
                                                        ///< shall only retrieve that number of sub-devices.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetModuleProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCommandQueueGroupProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of command queue group properties available.
                                                        ///< if count is greater than the number of command queue group properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of command queue group properties available.
        ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< command queue group properties.
                                                        ///< if count is less than the number of command queue group properties
                                                        ///< available, then driver shall only retrieve that number of command
                                                        ///< queue group properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of memory properties available.
                                                        ///< if count is greater than the number of memory properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< memory properties available.
        ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties.
                                                        ///< if count is less than the number of memory properties available, then
                                                        ///< driver shall only retrieve that number of memory properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of cache properties available.
                                                        ///< if count is greater than the number of cache properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< cache properties available.
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for cache properties.
                                                        ///< if count is less than the number of cache properties available, then
                                                        ///< driver shall only retrieve that number of cache properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetExternalMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetP2PProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceCanAccessPeer(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetStatus(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetGlobalTimestamps(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                        ///< Device's global timestamp value.
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceSynchronize(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextCreateEx(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                        ///< phDevices`
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< context has visibility.
                                                        ///< if nullptr, then all devices and any sub-devices supported by the
                                                        ///< driver instance are
                                                        ///< visible to the context.
                                                        ///< otherwise, the context only has visibility to the devices and any
                                                        ///< sub-devices of the
                                                        ///< devices in this array.
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextDestroy(
        ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextGetStatus(
        ze_context_handle_t hContext                    ///< [in] handle of context object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueExecuteCommandLists(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueSynchronize(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the command queue;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetOrdinal(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetIndex(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pIndex                                ///< [out] command queue index within the group
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateImmediate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWriteGlobalTimestamp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t* dstptr,                               ///< [in,out] pointer to memory where timestamp value will be written; must
                                                        ///< be 8byte-aligned.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing query
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListHostSynchronize(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the immediate command list
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the immediate command list;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetDeviceHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_device_handle_t* phDevice                    ///< [out] handle of the device on which the command list was created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetContextHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the command list was created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetOrdinal(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal to which command list is submitted
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListImmediateGetIndex(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t* pIndex                                ///< [out] command queue index within the group to which the immediate
                                                        ///< command list is submitted
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListIsImmediate(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_bool_t* pIsImmediate                         ///< [out] Boolean indicating whether the command list is an immediate
                                                        ///< command list (true) or not (false)
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryRangesBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextSystemBarrier(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryFill(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                        ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                        ///< otherwise it's ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                        ///< otherwise it's ignored.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopyFromContext(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_context_handle_t hContextSrc,                ///< [in] handle of source context object
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyToMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyFromMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryPrefetch(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemAdvise(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                        ///< phDevices`
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventCreate(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event pool handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                        ///< continuing
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSynchronize(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestamp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendQueryKernelTimestamps(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] the number of timestamp events to query
        ze_event_handle_t* phEvents,                    ///< [in][range(0, numEvents)] handles of timestamp events to query
        void* dstptr,                                   ///< [in,out] pointer to memory where ::ze_kernel_timestamp_result_t will
                                                        ///< be written; must be size-aligned.
        const size_t* pOffsets,                         ///< [in][optional][range(0, numEvents)] offset, in bytes, to write
                                                        ///< results; address must be 4byte-aligned and offsets must be
                                                        ///< size-aligned.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing query
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetEventPool(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_pool_handle_t* phEventPool             ///< [out] handle of the event pool for the event
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetSignalScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pSignalScope            ///< [out] signal event scope. This is the scope of relevant cache
                                                        ///< hierarchies that are flushed on a signal action before the event is
                                                        ///< triggered. May be 0 or a valid combination of ::ze_event_scope_flag_t.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetWaitScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pWaitScope              ///< [out] wait event scope. This is the scope of relevant cache
                                                        ///< hierarchies invalidated on a wait action after the event is complete.
                                                        ///< May be 0 or a valid combination of ::ze_event_scope_flag_t.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetContextHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the event pool was created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetFlags(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_event_pool_flags_t* pFlags                   ///< [out] creation flags used to create the event pool; may be 0 or a
                                                        ///< valid combination of ::ze_event_pool_flag_t
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceCreate(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceHostSynchronize(
        ze_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocShared(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
        void** pptr                                     ///< [out] pointer to shared allocation
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocDevice(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void** pptr                                     ///< [out] pointer to device allocation
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocHost(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        void** pptr                                     ///< [out] pointer to host allocation
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAllocProperties(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAddressRange(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandleFromFileDescriptorExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        uint64_t handle,                                ///< [in] file descriptor
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetFileDescriptorFromIpcHandleExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t ipcHandle,                  ///< [in] IPC memory handle
        uint64_t* pHandle                               ///< [out] Returned file descriptor
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation.
                                                        ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
        void** pptr                                     ///< [out] pointer to device allocation in this process
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemCloseIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemSetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t attr          ///< [in] Atomic access attributes to set for the specified range.
                                                        ///< Must be 0 (default) or a valid combination of ::ze_memory_atomic_attr_exp_flag_t.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t* pAttr        ///< [out] Atomic access attributes for the specified range
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDynamicLink(
        uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to
                                                        ///< dynamically link together.
        ze_module_build_log_handle_t* phLinkLog         ///< [out][optional] pointer to handle of dynamic link log.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogGetString(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetNativeBinary(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pGlobalName,                        ///< [in] name of global variable in module
        size_t* pSize,                                  ///< [in,out][optional] size of global variable
        void** pptr                                     ///< [in,out][optional] device visible pointer
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetKernelNames(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of names available.
                                                        ///< if count is greater than the number of names available, then the
                                                        ///< driver shall update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions.
                                                        ///< if count is less than the number of names available, then driver shall
                                                        ///< only retrieve that number of names.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetProperties(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelCreate(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetFunctionPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetArgumentValue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetSourceAttributes(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes, including
                                                        ///< null-terminating character.
        char** pString                                  ///< [in,out][optional] pointer to application-managed character array
                                                        ///< (string data).
                                                        ///< If NULL, the string length of the kernel source attributes, including
                                                        ///< a null-terminating character, is returned in pSize. Otherwise, pString
                                                        ///< must point to valid application memory that is greater than or equal
                                                        ///< to *pSize bytes in length, and on return the pointed-to string will
                                                        ///< contain a space-separated list of kernel source attributes. Note: This
                                                        ///< API was originally intended to ship with a char *pString, however this
                                                        ///< typo was introduced. Thus the API has to stay this way for backwards
                                                        ///< compatible reasons. It can be corrected in v2.0. Suggestion is to
                                                        ///< create your own char *pString and then pass to this API with &pString.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                        ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetName(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                        ///< bytes.
        char* pName                                     ///< [in,out][optional] char pointer to kernel name.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernelWithParameters(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pGroupCounts,           ///< [in] thread group launch arguments
        const void * pNext,                             ///< [in][optional] additional parameters passed to the function
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernelWithArguments(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t groupCounts,             ///< [in] thread group counts
        const ze_group_size_t groupSizes,               ///< [in] thread group sizes
        void ** pArguments,                             ///< [in]pointer to an array of pointers
        const void * pNext,                             ///< [in][optional] additional extensions passed to the function
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchCooperativeKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernelIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchMultipleKernelsIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less than or equal to
                                                        ///< numKernels
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeMemoryResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictMemory(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeImageResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictImage(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemReserve(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in][optional] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to free.
        size_t size                                     ///< [in] size in bytes to free; must be page aligned.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemQueryPageSize(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t size,                                    ///< [in] unaligned allocation size in bytes
        size_t* pagesize                                ///< [out] pointer to page size to use for start address and size
                                                        ///< alignments.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object, can be `nullptr` if creating
                                                        ///< physical host memory.
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemDestroy(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemMap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address range to map.
        size_t size,                                    ///< [in] size in bytes of virtual address range to map; must be page
                                                        ///< aligned.
        ze_physical_mem_handle_t hPhysicalMemory,       ///< [in] handle to physical memory object.
        size_t offset,                                  ///< [in] offset into physical memory allocation object; must be page
                                                        ///< aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemUnmap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to unmap.
        size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemSetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemGetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t* access,           ///< [out] query result for page access attribute.
        size_t* outSize                                 ///< [out] query result for size of virtual address range, starting at ptr,
                                                        ///< that shares same access attribute.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGlobalOffsetExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t offsetX,                               ///< [in] global offset for X dimension to use for this kernel
        uint32_t offsetY,                               ///< [in] global offset for Y dimension to use for this kernel
        uint32_t offsetZ                                ///< [in] global offset for Z dimension to use for this kernel
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetBinaryExp(
        ze_kernel_handle_t hKernel,                     ///< [in] Kernel handle.
        size_t* pSize,                                  ///< [in,out] pointer to variable with size of GEN ISA binary.
        uint8_t* pKernelBinary                          ///< [in,out] pointer to storage area for GEN ISA binary function.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceImportExternalSemaphoreExt(
        ze_device_handle_t hDevice,                     ///< [in] The device handle.
        const ze_external_semaphore_ext_desc_t* desc,   ///< [in] The pointer to external semaphore descriptor.
        ze_external_semaphore_ext_handle_t* phSemaphore ///< [out] The handle of the external semaphore imported.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceReleaseExternalSemaphoreExt(
        ze_external_semaphore_ext_handle_t hSemaphore   ///< [in] The handle of the external semaphore.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalExternalSemaphoreExt(
        ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
        uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
        ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in][range(0, numSemaphores)] The vector of external semaphore handles
                                                        ///< to be appended into command list.
        ze_external_semaphore_signal_params_ext_t* signalParams,///< [in] Signal parameters.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWaitExternalSemaphoreExt(
        ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
        uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
        ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in] [range(0,numSemaphores)] The vector of external semaphore handles
                                                        ///< to append into command list.
        ze_external_semaphore_wait_params_ext_t* waitParams,///< [in] Wait parameters.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCreateExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_ext_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_ext_handle_t* phBuilder         ///< [out] handle of builder object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderGetBuildPropertiesExt(
        ze_rtas_builder_ext_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_ext_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_ext_properties_t* pProperties   ///< [in,out] query result for builder properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverRTASFormatCompatibilityCheckExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_ext_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_ext_t rtasFormatB                ///< [in] operand B
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderBuildExt(
        ze_rtas_builder_ext_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_ext_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        void* pScratchBuffer,                           ///< [in][range(0, `scratchBufferSizeBytes`)] scratch buffer to be used
                                                        ///< during acceleration structure construction
        size_t scratchBufferSizeBytes,                  ///< [in] size of scratch buffer, in bytes
        void* pRtasBuffer,                              ///< [in] pointer to destination buffer
        size_t rtasBufferSizeBytes,                     ///< [in] destination buffer size, in bytes
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation, ///< [in][optional] handle to parallel operation object
        void* pBuildUserPtr,                            ///< [in][optional] pointer passed to callbacks
        ze_rtas_aabb_ext_t* pBounds,                    ///< [in,out][optional] pointer to destination address for acceleration
                                                        ///< structure bounds
        size_t* pRtasBufferSizeBytes                    ///< [out][optional] updated acceleration structure size requirement, in
                                                        ///< bytes
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCommandListAppendCopyExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination in device memory to copy the ray tracing
                                                        ///< acceleration structure to
        const void* srcptr,                             ///< [in] pointer to a valid source ray tracing acceleration structure in
                                                        ///< host memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExt(
        ze_rtas_builder_ext_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_ext_handle_t* phParallelOperation///< [out] handle of parallel operation object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_ext_properties_t* pProperties///< [in,out] query result for parallel operation properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetVectorWidthPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of vector width properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of vector width properties available.
                                                        ///< if count is greater than the number of vector width properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of vector width properties available.
        ze_device_vector_width_properties_ext_t* pVectorWidthProperties ///< [in,out][optional][range(0, *pCount)] array of vector width properties.
                                                        ///< if count is less than the number of properties available, then the
                                                        ///< driver will return only the number requested.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetAllocationPropertiesExp(
        ze_kernel_handle_t hKernel,                     ///< [in] Kernel handle.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of kernel allocation properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of kernel allocation properties available.
                                                        ///< if count is greater than the number of kernel allocation properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of kernel allocation properties.
        ze_kernel_allocation_exp_properties_t* pAllocationProperties///< [in,out][optional][range(0, *pCount)] array of kernel allocation properties.
                                                        ///< if count is less than the number of kernel allocation properties
                                                        ///< available, then driver shall only retrieve that number of kernel
                                                        ///< allocation properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceReserveCacheExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t cacheLevel,                              ///< [in] cache level where application want to reserve. If zero, then the
                                                        ///< driver shall default to last level of cache and attempt to reserve in
                                                        ///< that cache.
        size_t cacheReservationSize                     ///< [in] value for reserving size, in bytes. If zero, then the driver
                                                        ///< shall remove prior reservation
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceSetCacheAdviceExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        void* ptr,                                      ///< [in] memory pointer to query
        size_t regionSize,                              ///< [in] region size, in pages
        ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryTimestampsExp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
        uint32_t* pCount,                               ///< [in,out] pointer to the number of timestamp results.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of timestamps available.
                                                        ///< if count is greater than the number of timestamps available, then the
                                                        ///< driver shall update the value with the correct number of timestamps available.
        ze_kernel_timestamp_result_t* pTimestamps       ///< [in,out][optional][range(0, *pCount)] array of timestamp results.
                                                        ///< if count is less than the number of timestamps available, then driver
                                                        ///< shall only retrieve that number of timestamps.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetMemoryPropertiesExp(
        ze_image_handle_t hImage,                       ///< [in] handle of image object
        ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSchedulingHintExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDevicePciGetPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
        ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyToMemoryExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        uint32_t destRowPitch,                          ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                        ///< image or each image of a 1D or 2D image array being written
        uint32_t destSlicePitch,                        ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                        ///< each image of a 1D or 2D image array being written
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyFromMemoryExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        uint32_t srcRowPitch,                           ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                        ///< image or each image of a 1D or 2D image array being read
        uint32_t srcSlicePitch,                         ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                        ///< each image of a 1D or 2D image array being read
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetAllocPropertiesExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_image_handle_t hImage,                       ///< [in] handle of image object to query
        ze_image_allocation_ext_properties_t* pImageAllocProperties ///< [in,out] query result for image allocation properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleInspectLinkageExt(
        ze_linkage_inspection_ext_desc_t* pInspectDesc, ///< [in] pointer to linkage inspection descriptor structure.
        uint32_t numModules,                            ///< [in] number of modules to be inspected pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to be
                                                        ///< inspected for import dependencies.
        ze_module_build_log_handle_t* phLog             ///< [out] pointer to handle of linkage inspection log. Log object will
                                                        ///< contain separate lists of imports, un-resolvable imports, and exports.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFreeExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
        void* ptr                                       ///< [in][release] pointer to memory to free
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric vertices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of fabric vertices available.
                                                        ///< if count is greater than the number of fabric vertices available, then
                                                        ///< the driver shall update the value with the correct number of fabric
                                                        ///< vertices available.
        ze_fabric_vertex_handle_t* phVertices           ///< [in,out][optional][range(0, *pCount)] array of handle of fabric vertices.
                                                        ///< if count is less than the number of fabric vertices available, then
                                                        ///< driver shall only retrieve that number of fabric vertices.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetSubVerticesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-vertices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sub-vertices available.
                                                        ///< if count is greater than the number of sub-vertices available, then
                                                        ///< the driver shall update the value with the correct number of
                                                        ///< sub-vertices available.
        ze_fabric_vertex_handle_t* phSubvertices        ///< [in,out][optional][range(0, *pCount)] array of handle of sub-vertices.
                                                        ///< if count is less than the number of sub-vertices available, then
                                                        ///< driver shall only retrieve that number of sub-vertices.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetPropertiesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetDeviceExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetFabricVertexExp(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetExp(
        ze_fabric_vertex_handle_t hVertexA,             ///< [in] handle of first fabric vertex instance
        ze_fabric_vertex_handle_t hVertexB,             ///< [in] handle of second fabric vertex instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric edges.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of fabric edges available.
                                                        ///< if count is greater than the number of fabric edges available, then
                                                        ///< the driver shall update the value with the correct number of fabric
                                                        ///< edges available.
        ze_fabric_edge_handle_t* phEdges                ///< [in,out][optional][range(0, *pCount)] array of handle of fabric edges.
                                                        ///< if count is less than the number of fabric edges available, then
                                                        ///< driver shall only retrieve that number of fabric edges.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetVerticesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge instance
        ze_fabric_vertex_handle_t* phVertexA,           ///< [out] fabric vertex connected to one end of the given fabric edge.
        ze_fabric_vertex_handle_t* phVertexB            ///< [out] fabric vertex connected to other end of the given fabric edge.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetPropertiesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
        ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestampsExt(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
        uint32_t* pCount,                               ///< [in,out] pointer to the number of event packets available.
                                                        ///<    - This value is implementation specific.
                                                        ///<    - if `*pCount` is zero, then the driver shall update the value with
                                                        ///< the total number of event packets available.
                                                        ///<    - if `*pCount` is greater than the number of event packets
                                                        ///< available, the driver shall update the value with the correct value.
                                                        ///<    - Buffer(s) for query results must be sized by the application to
                                                        ///< accommodate a minimum of `*pCount` elements.
        ze_event_query_kernel_timestamps_results_ext_properties_t* pResults ///< [in,out][optional][range(0, *pCount)] pointer to event query
                                                        ///< properties structure(s).
                                                        ///<    - This parameter may be null when `*pCount` is zero.
                                                        ///<    - if `*pCount` is less than the number of event packets available,
                                                        ///< the driver may only update `*pCount` elements, starting at element zero.
                                                        ///<    - if `*pCount` is greater than the number of event packets
                                                        ///< available, the driver may only update the valid elements.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderGetBuildPropertiesExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverRTASFormatCompatibilityCheckExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_exp_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_exp_t rtasFormatB                ///< [in] operand B
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderBuildExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        void* pScratchBuffer,                           ///< [in][range(0, `scratchBufferSizeBytes`)] scratch buffer to be used
                                                        ///< during acceleration structure construction
        size_t scratchBufferSizeBytes,                  ///< [in] size of scratch buffer, in bytes
        void* pRtasBuffer,                              ///< [in] pointer to destination buffer
        size_t rtasBufferSizeBytes,                     ///< [in] destination buffer size, in bytes
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in][optional] handle to parallel operation object
        void* pBuildUserPtr,                            ///< [in][optional] pointer passed to callbacks
        ze_rtas_aabb_exp_t* pBounds,                    ///< [in,out][optional] pointer to destination address for acceleration
                                                        ///< structure bounds
        size_t* pRtasBufferSizeBytes                    ///< [out][optional] updated acceleration structure size requirement, in
                                                        ///< bytes
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExp(
        ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetPitchFor2dImage(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        size_t imageWidth,                              ///< [in] imageWidth
        size_t imageHeight,                             ///< [in] imageHeight
        unsigned int elementSizeInBytes,                ///< [in] Element size in bytes
        size_t * rowPitch                               ///< [out] rowPitch
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetDeviceOffsetExp(
        ze_image_handle_t hImage,                       ///< [in] handle of the image
        uint64_t* pDeviceOffset                         ///< [out] bindless device offset for image
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateCloneExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle to source command list (the command list to clone)
        ze_command_list_handle_t* phClonedCommandList   ///< [out] pointer to handle of the cloned command list
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListImmediateAppendCommandListsExp(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t numCommandLists,                       ///< [in] number of command lists
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] handles of command lists
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
                                                        ///<    - if not null, this event is signaled after the completion of all
                                                        ///< appended command lists
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing appended
                                                        ///< command lists; must be 0 if nullptr == phWaitEvents
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing appended command lists.
                                                        ///<    - if not null, all wait events must be satisfied prior to the start
                                                        ///< of any appended command list(s)
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetNextCommandIdExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_command_id_exp_desc_t* desc,   ///< [in] pointer to mutable command identifier descriptor
        uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetNextCommandIdWithKernelsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_command_id_exp_desc_t* desc,   ///< [in][out] pointer to mutable command identifier descriptor
        uint32_t numKernels,                            ///< [in][optional] number of entries on phKernels list
        ze_kernel_handle_t* phKernels,                  ///< [in][optional][range(0, numKernels)] list of kernels that user can
                                                        ///< switch between using ::zeCommandListUpdateMutableCommandKernelsExp
                                                        ///< call
        uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_commands_exp_desc_t* desc      ///< [in] pointer to mutable commands descriptor; multiple descriptors may
                                                        ///< be chained via `pNext` member
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandSignalEventExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        ze_event_handle_t hSignalEvent                  ///< [in][optional] handle of the event to signal on completion
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandWaitEventsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        uint32_t numWaitEvents,                         ///< [in][optional] the number of wait events
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        );
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandKernelsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] the number of kernels to update
        uint64_t* pCommandId,                           ///< [in][range(0, numKernels)] command identifier
        ze_kernel_handle_t* phKernels                   ///< [in][range(0, numKernels)] handle of the kernel for a command
                                                        ///< identifier to switch to
        );
}

#if defined(__cplusplus)
extern "C" {
#endif

__zedlllocal void ZE_APICALL
zeGetGlobalProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetRTASBuilderProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetRTASBuilderExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetRTASParallelOperationProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetRTASParallelOperationExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDriverProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDriverExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDeviceProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDeviceExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetContextProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetCommandQueueProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetCommandListProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetCommandListExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetEventProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetEventExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetEventPoolProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetFenceProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetImageProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetImageExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetKernelProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetKernelExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetMemProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetMemExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetModuleProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetModuleBuildLogProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetPhysicalMemProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetSamplerProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetVirtualMemProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetFabricEdgeExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetFabricVertexExpProcAddrTableLegacy();

#if defined(__cplusplus)
};
#endif
