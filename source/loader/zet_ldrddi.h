/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_ldrddi.h
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    // Forward declaration for driver_t so this header can reference loader::driver_t*
    // without requiring inclusion of ze_loader_internal.h (which includes this file).
    struct driver_t;
    ///////////////////////////////////////////////////////////////////////////////
    using zet_driver_object_t                 = object_t < zet_driver_handle_t >;
    using zet_driver_factory_t                = singleton_factory_t < zet_driver_object_t, zet_driver_handle_t >;

    using zet_device_object_t                 = object_t < zet_device_handle_t >;
    using zet_device_factory_t                = singleton_factory_t < zet_device_object_t, zet_device_handle_t >;

    using zet_context_object_t                = object_t < zet_context_handle_t >;
    using zet_context_factory_t               = singleton_factory_t < zet_context_object_t, zet_context_handle_t >;

    using zet_command_list_object_t           = object_t < zet_command_list_handle_t >;
    using zet_command_list_factory_t          = singleton_factory_t < zet_command_list_object_t, zet_command_list_handle_t >;

    using zet_module_object_t                 = object_t < zet_module_handle_t >;
    using zet_module_factory_t                = singleton_factory_t < zet_module_object_t, zet_module_handle_t >;

    using zet_kernel_object_t                 = object_t < zet_kernel_handle_t >;
    using zet_kernel_factory_t                = singleton_factory_t < zet_kernel_object_t, zet_kernel_handle_t >;

    using zet_metric_group_object_t           = object_t < zet_metric_group_handle_t >;
    using zet_metric_group_factory_t          = singleton_factory_t < zet_metric_group_object_t, zet_metric_group_handle_t >;

    using zet_metric_object_t                 = object_t < zet_metric_handle_t >;
    using zet_metric_factory_t                = singleton_factory_t < zet_metric_object_t, zet_metric_handle_t >;

    using zet_metric_streamer_object_t        = object_t < zet_metric_streamer_handle_t >;
    using zet_metric_streamer_factory_t       = singleton_factory_t < zet_metric_streamer_object_t, zet_metric_streamer_handle_t >;

    using zet_metric_query_pool_object_t      = object_t < zet_metric_query_pool_handle_t >;
    using zet_metric_query_pool_factory_t     = singleton_factory_t < zet_metric_query_pool_object_t, zet_metric_query_pool_handle_t >;

    using zet_metric_query_object_t           = object_t < zet_metric_query_handle_t >;
    using zet_metric_query_factory_t          = singleton_factory_t < zet_metric_query_object_t, zet_metric_query_handle_t >;

    using zet_tracer_exp_object_t             = object_t < zet_tracer_exp_handle_t >;
    using zet_tracer_exp_factory_t            = singleton_factory_t < zet_tracer_exp_object_t, zet_tracer_exp_handle_t >;

    using zet_debug_session_object_t          = object_t < zet_debug_session_handle_t >;
    using zet_debug_session_factory_t         = singleton_factory_t < zet_debug_session_object_t, zet_debug_session_handle_t >;

    using zet_metric_tracer_exp_object_t      = object_t < zet_metric_tracer_exp_handle_t >;
    using zet_metric_tracer_exp_factory_t     = singleton_factory_t < zet_metric_tracer_exp_object_t, zet_metric_tracer_exp_handle_t >;

    using zet_metric_decoder_exp_object_t     = object_t < zet_metric_decoder_exp_handle_t >;
    using zet_metric_decoder_exp_factory_t    = singleton_factory_t < zet_metric_decoder_exp_object_t, zet_metric_decoder_exp_handle_t >;

    using zet_metric_programmable_exp_object_t    = object_t < zet_metric_programmable_exp_handle_t >;
    using zet_metric_programmable_exp_factory_t   = singleton_factory_t < zet_metric_programmable_exp_object_t, zet_metric_programmable_exp_handle_t >;

    __zedlllocal ze_result_t ZE_APICALL
    zetloaderInitDriverDDITables(loader::driver_t *driver);
}

namespace loader_driver_ddi
{
    __zedlllocal void ZE_APICALL
    zetDestroyDDiDriverTables(zet_dditable_driver_t* pDdiTable);
    __zedlllocal ze_result_t ZE_APICALL
    zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceGetDebugProperties(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        zet_device_debug_properties_t* pDebugProperties ///< [in,out] query result for debug properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugAttach(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* phDebug             ///< [out] debug session handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugReadEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the event;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        zet_debug_event_t* event                        ///< [in,out] a pointer to a ::zet_debug_event_t.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugAcknowledgeEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        const zet_debug_event_t* event                  ///< [in] a pointer to a ::zet_debug_event_t.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to interrupt
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to resume
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugReadMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugWriteMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugGetRegisterSetProperties(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of register set properties available.
                                                        ///< if count is greater than the number of register set properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of registry set properties available.
        zet_debug_regset_properties_t* pRegisterSetProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< register set properties.
                                                        ///< if count is less than the number of register set properties available,
                                                        ///< then driver shall only retrieve that number of register set properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugGetThreadRegisterSetProperties(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier specifying a single stopped thread
        uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of register set properties available.
                                                        ///< if count is greater than the number of register set properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of registry set properties available.
        zet_debug_regset_properties_t* pRegisterSetProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< register set properties.
                                                        ///< if count is less than the number of register set properties available,
                                                        ///< then driver shall only retrieve that number of register set properties.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugReadRegisters(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier
        uint32_t type,                                  ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        uint32_t count,                                 ///< [in] the number of registers to read; start+count must be less than or
                                                        ///< equal to the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugWriteRegisters(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier
        uint32_t type,                                  ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        uint32_t count,                                 ///< [in] the number of registers to write; start+count must be less than
                                                        ///< or equal to the `count` member of ::zet_debug_regset_properties_t for
                                                        ///< the type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGet(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric groups available.
                                                        ///< if count is greater than the number of metric groups available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< groups available.
        zet_metric_group_handle_t* phMetricGroups       ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups.
                                                        ///< if count is less than the number of metric groups available, then
                                                        ///< driver shall only retrieve that number of metric groups.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCalculateMetricValues(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric values to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric values to be calculated.
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated metrics.
                                                        ///< if count is less than the number available in the raw data buffer,
                                                        ///< then driver shall only calculate that number of metric values.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGet(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metrics available.
                                                        ///< if count is greater than the number of metrics available, then the
                                                        ///< driver shall update the value with the correct number of metrics available.
        zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metrics.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetContextActivateMetricGroups(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate; must be 0 if `nullptr ==
                                                        ///< phMetricGroups`
        zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to activate.
                                                        ///< nullptr deactivates all previously used metric groups.
                                                        ///< all metrics groups must come from a different domains.
                                                        ///< metric query and metric stream must use activated metric groups.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerOpen(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_streamer_desc_t* desc,               ///< [in,out] metric streamer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification
        zet_metric_streamer_handle_t* phMetricStreamer  ///< [out] handle of metric streamer
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricStreamerMarker(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
        uint32_t value                                  ///< [in] streamer marker value
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerClose(
        zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerReadData(
        zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
        uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                        ///< if `UINT32_MAX`, then function will retrieve all reports available
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing streamer
                                                        ///< reports in raw format
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryPoolCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in] must be zero
        ze_event_handle_t* phWaitEvents                 ///< [in][mbz] must be nullptr
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryGetData(
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                        ///< reports in raw format
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_properties_t* pProfileProperties    ///< [out] pointer to profile properties
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        const zet_tracer_exp_desc_t* desc,              ///< [in] pointer to tracer descriptor
        zet_tracer_exp_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpDestroy(
        zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetPrologues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEpilogues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEnabled(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceGetConcurrentMetricGroupsExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t metricGroupCount,                      ///< [in] metric group count
        zet_metric_group_handle_t * phMetricGroups,     ///< [in,out] metrics groups to be re-arranged to be sets of concurrent
                                                        ///< groups
        uint32_t * pMetricGroupsCountPerConcurrentGroup,///< [in,out][optional][*pConcurrentGroupCount] count of metric groups per
                                                        ///< concurrent group.
        uint32_t * pConcurrentGroupCount                ///< [out] number of concurrent groups.
                                                        ///< The value of this parameter could be used to determine the number of
                                                        ///< replays necessary.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerCreateExp(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t metricGroupCount,                      ///< [in] metric group count
        zet_metric_group_handle_t* phMetricGroups,      ///< [in][range(0, metricGroupCount )] handles of the metric groups to
                                                        ///< trace
        zet_metric_tracer_exp_desc_t* desc,             ///< [in,out] metric tracer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Note:
                                                        ///< If buffer is not drained when the event it flagged, there is a risk of
                                                        ///< HW event buffer being overrun
        zet_metric_tracer_exp_handle_t* phMetricTracer  ///< [out] handle of the metric tracer
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerDestroyExp(
        zet_metric_tracer_exp_handle_t hMetricTracer    ///< [in] handle of the metric tracer
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerEnableExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                        ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                        ///< and checking the return status: ::ZE_RESULT_NOT_READY will be returned
                                                        ///< when the tracer is inactive. ::ZE_RESULT_SUCCESS will be returned 
                                                        ///< when the tracer is active.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerDisableExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                        ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                        ///< and checking the return status: ::ZE_RESULT_SUCCESS will be returned
                                                        ///< when the tracer is active or when it is inactive but still has data. 
                                                        ///< ::ZE_RESULT_NOT_READY will be returned when the tracer is inactive and
                                                        ///< has no more data to be retrieved.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerReadDataExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all data available.
                                                        ///< if size is non-zero, then driver will only retrieve that amount of
                                                        ///< data. 
                                                        ///< if size is larger than size needed for all data, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< data in raw format
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderCreateExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        zet_metric_decoder_exp_handle_t* phMetricDecoder///< [out] handle of the metric decoder object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderDestroyExp(
        zet_metric_decoder_exp_handle_t phMetricDecoder ///< [in] handle of the metric decoder object
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderGetDecodableMetricsExp(
        zet_metric_decoder_exp_handle_t hMetricDecoder, ///< [in] handle of the metric decoder object
        uint32_t* pCount,                               ///< [in,out] pointer to number of decodable metric in the hMetricDecoder
                                                        ///< handle. If count is zero, then the driver shall 
                                                        ///< update the value with the total number of decodable metrics available
                                                        ///< in the decoder. if count is greater than zero 
                                                        ///< but less than the total number of decodable metrics available in the
                                                        ///< decoder, then only that number will be returned. 
                                                        ///< if count is greater than the number of decodable metrics available in
                                                        ///< the decoder, then the driver shall update the 
                                                        ///< value with the actual number of decodable metrics available. 
        zet_metric_handle_t* phMetrics                  ///< [in,out] [range(0, *pCount)] array of handles of decodable metrics in
                                                        ///< the hMetricDecoder handle provided.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerDecodeExp(
        zet_metric_decoder_exp_handle_t phMetricDecoder,///< [in] handle of the metric decoder object
        size_t* pRawDataSize,                           ///< [in,out] size in bytes of raw data buffer. If pMetricEntriesCount is
                                                        ///< greater than zero but less than total number of 
                                                        ///< decodable metrics available in the raw data buffer, then driver shall
                                                        ///< update this value with actual number of raw 
                                                        ///< data bytes processed.
        uint8_t* pRawData,                              ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< data in raw format
        uint32_t metricsCount,                          ///< [in] number of decodable metrics in the tracer for which the
                                                        ///< hMetricDecoder handle was provided. See 
                                                        ///< ::zetMetricDecoderGetDecodableMetricsExp(). If metricCount is greater
                                                        ///< than zero but less than the number decodable 
                                                        ///< metrics available in the raw data buffer, then driver shall only
                                                        ///< decode those.
        zet_metric_handle_t* phMetrics,                 ///< [in] [range(0, metricsCount)] array of handles of decodable metrics in
                                                        ///< the decoder for which the hMetricDecoder handle was 
                                                        ///< provided. Metrics handles are expected to be for decodable metrics,
                                                        ///< see ::zetMetricDecoderGetDecodableMetricsExp() 
        uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets. If count is zero, then the
                                                        ///< driver shall update the value with the total
                                                        ///< number of metric sets to be decoded. If count is greater than the
                                                        ///< number available in the raw data buffer, then the
                                                        ///< driver shall update the value with the actual number of metric sets to
                                                        ///< be decoded. There is a 1:1 relation between
                                                        ///< the number of sets and sub-devices returned in the decoded entries.
        uint32_t* pMetricEntriesCountPerSet,            ///< [in,out][optional][range(0, *pSetCount)] buffer of metric entries
                                                        ///< counts per metric set, one value per set.
        uint32_t* pMetricEntriesCount,                  ///< [in,out]  pointer to the total number of metric entries decoded, for
                                                        ///< all metric sets. If count is zero, then the
                                                        ///< driver shall update the value with the total number of metric entries
                                                        ///< to be decoded. If count is greater than zero
                                                        ///< but less than the total number of metric entries available in the raw
                                                        ///< data, then user provided number will be decoded.
                                                        ///< If count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with
                                                        ///< the actual number of decodable metric entries decoded. If set to null,
                                                        ///< then driver will only update the value of
                                                        ///< pSetCount.
        zet_metric_entry_exp_t* pMetricEntries          ///< [in,out][optional][range(0, *pMetricEntriesCount)] buffer containing
                                                        ///< decoded metric entries
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMarkerExp(
        zet_command_list_handle_t hCommandList,         ///< [in] handle to the command list
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle to the marker metric group.
                                                        ///< ::zet_metric_group_type_exp_flags_t could be used to check whether
                                                        ///< marker is supoported by the metric group.
        uint32_t value                                  ///< [in] marker value
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceEnableMetricsExp(
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be enabled.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceDisableMetricsExp(
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be disabled
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCalculateMultipleMetricValuesExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric sets to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric sets to be calculated.
        uint32_t* pTotalMetricValueCount,               ///< [in,out] pointer to number of the total number of metric values
                                                        ///< calculated, for all metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric values to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric values to be calculated.
        uint32_t* pMetricCounts,                        ///< [in,out][optional][range(0, *pSetCount)] buffer of metric counts per
                                                        ///< metric set.
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pTotalMetricValueCount)] buffer of
                                                        ///< calculated metrics.
                                                        ///< if count is less than the number available in the raw data buffer,
                                                        ///< then driver shall only calculate that number of metric values.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetGlobalTimestampsExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        ze_bool_t synchronizedWithHost,                 ///< [in] Returns the timestamps synchronized to the host or the device.
        uint64_t* globalTimestamp,                      ///< [out] Device timestamp.
        uint64_t* metricTimestamp                       ///< [out] Metric timestamp.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetExportDataExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        const uint8_t* pRawData,                        ///< [in] buffer of raw data
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        size_t* pExportDataSize,                        ///< [in,out] size in bytes of export data buffer
                                                        ///< if size is zero, then the driver shall update the value with the
                                                        ///< number of bytes necessary to store the exported data.
                                                        ///< if size is greater than required, then the driver shall update the
                                                        ///< value with the actual number of bytes necessary to store the exported data.
        uint8_t * pExportData                           ///< [in,out][optional][range(0, *pExportDataSize)] buffer of exported data.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCalculateMetricExportDataExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
        size_t exportDataSize,                          ///< [in] size in bytes of exported data buffer
        const uint8_t* pExportData,                     ///< [in][range(0, exportDataSize)] buffer of exported data to calculate
        zet_metric_calculate_exp_desc_t* pCalculateDescriptor,  ///< [in] descriptor specifying calculation specific parameters
        uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric sets to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric sets to be calculated.
        uint32_t* pTotalMetricValueCount,               ///< [in,out] pointer to number of the total number of metric values
                                                        ///< calculated, for all metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric values to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric values to be calculated.
        uint32_t* pMetricCounts,                        ///< [in,out][optional][range(0, *pSetCount)] buffer of metric counts per
                                                        ///< metric set.
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pTotalMetricValueCount)] buffer of
                                                        ///< calculated metrics.
                                                        ///< if count is less than the number available in the raw data buffer,
                                                        ///< then driver shall only calculate that number of metric values.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric programmable handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric programmable handles available.
                                                        ///< if count is greater than the number of metric programmable handles
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of metric programmable handles available.
        zet_metric_programmable_exp_handle_t* phMetricProgrammables ///< [in,out][optional][range(0, *pCount)] array of handle of metric programmables.
                                                        ///< if count is less than the number of metric programmables available,
                                                        ///< then driver shall only retrieve that number of metric programmables.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetPropertiesExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        zet_metric_programmable_exp_properties_t* pProperties   ///< [in,out] properties of the metric programmable
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetParamInfoExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t* pParameterCount,                      ///< [in,out] count of the parameters to retrieve parameter info.
                                                        ///< if value pParameterCount is greater than count of parameters
                                                        ///< available, then pParameterCount will be updated with count of
                                                        ///< parameters available.
                                                        ///< The count of parameters available can be queried using ::zetMetricProgrammableGetPropertiesExp.
        zet_metric_programmable_param_info_exp_t* pParameterInfo///< [in,out][range(1, *pParameterCount)] array of parameter info.
                                                        ///< if parameterCount is less than the number of parameters available,
                                                        ///< then driver shall only retrieve that number of parameter info.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetParamValueInfoExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t parameterOrdinal,                      ///< [in] ordinal of the parameter in the metric programmable
        uint32_t* pValueInfoCount,                      ///< [in,out] count of parameter value information to retrieve.
                                                        ///< if value at pValueInfoCount is greater than count of value info
                                                        ///< available, then pValueInfoCount will be updated with count of value
                                                        ///< info available.
                                                        ///< The count of parameter value info available can be queried using ::zetMetricProgrammableGetParamInfoExp.
        zet_metric_programmable_param_value_info_exp_t* pValueInfo  ///< [in,out][range(1, *pValueInfoCount)] array of parameter value info.
                                                        ///< if pValueInfoCount is less than the number of value info available,
                                                        ///< then driver shall only retrieve that number of value info.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricCreateFromProgrammableExp2(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t parameterCount,                        ///< [in] Count of parameters to set.
        zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
        const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                        ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
        const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_DESCRIPTION.
        uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< number of metric handles available for this programmable.
                                                        ///< if count is greater than the number of metric handles available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< handles available.
        zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metric handles.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricCreateFromProgrammableExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
        uint32_t parameterCount,                        ///< [in] Count of parameters to set.
        const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                        ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
        const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_DESCRIPTION.
        uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< number of metric handles available for this programmable.
                                                        ///< if count is greater than the number of metric handles available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< handles available.
        zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metric handles.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceCreateMetricGroupsFromMetricsExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device.
        uint32_t metricCount,                           ///< [in] number of metric handles.
        zet_metric_handle_t * phMetrics,                ///< [in] metric handles to be added to the metric groups.
        const char * pMetricGroupNamePrefix,            ///< [in] prefix to the name created for the metric groups. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_NAME_PREFIX_EXP.
        const char * pDescription,                      ///< [in] pointer to description of the metric groups. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
        uint32_t * pMetricGroupCount,                   ///< [in,out] pointer to the number of metric group handles to be created.
                                                        ///< if pMetricGroupCount is zero, then the driver shall update the value
                                                        ///< with the maximum possible number of metric group handles that could be created.
                                                        ///< if pMetricGroupCount is greater than the number of metric group
                                                        ///< handles that could be created, then the driver shall update the value
                                                        ///< with the correct number of metric group handles generated.
                                                        ///< if pMetricGroupCount is lesser than the number of metric group handles
                                                        ///< that could be created, then ::ZE_RESULT_ERROR_INVALID_ARGUMENT is returned.
        zet_metric_group_handle_t* phMetricGroup        ///< [in,out][optional][range(0, *pMetricGroupCount)] array of handle of
                                                        ///< metric group handles.
                                                        ///< Created Metric group handles.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCreateExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        const char* pName,                              ///< [in] pointer to metric group name. Must point to a null-terminated
                                                        ///< character array no longer than ::ZET_MAX_METRIC_GROUP_NAME.
        const char* pDescription,                       ///< [in] pointer to metric group description. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
        zet_metric_group_sampling_type_flags_t samplingType,///< [in] Sampling type for the metric group.
        zet_metric_group_handle_t* phMetricGroup        ///< [in,out] Created Metric group handle
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupAddMetricExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
        zet_metric_handle_t hMetric,                    ///< [in] Metric to be added to the group.
        size_t * pErrorStringSize,                      ///< [in,out][optional] Size of the error string to query, if an error was
                                                        ///< reported during adding the metric handle.
                                                        ///< if *pErrorStringSize is zero, then the driver shall update the value
                                                        ///< with the size of the error string in bytes.
        char* pErrorString                              ///< [in,out][optional][range(0, *pErrorStringSize)] Error string.
                                                        ///< if *pErrorStringSize is less than the length of the error string
                                                        ///< available, then driver shall only retrieve that length of error string.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupRemoveMetricExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
        zet_metric_handle_t hMetric                     ///< [in] Metric handle to be removed from the metric group.
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCloseExp(
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupDestroyExp(
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group to destroy
        );
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDestroyExp(
        zet_metric_handle_t hMetric                     ///< [in] Handle of the metric to destroy
        );
}

#if defined(__cplusplus)
extern "C" {
#endif

__zedlllocal void ZE_APICALL
zetGetMetricDecoderExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricDecoderExpProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricProgrammableExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricProgrammableExpProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricTracerExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricTracerExpProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetDeviceProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetDeviceProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetDeviceExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetDeviceExpProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetContextProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetContextProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetCommandListProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetCommandListProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetCommandListExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetCommandListExpProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetKernelProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetKernelProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetModuleProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetModuleProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetDebugProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetDebugProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricExpProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricGroupProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricGroupProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricGroupExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricGroupExpProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricQueryProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricQueryProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricQueryPoolProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricQueryPoolProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetMetricStreamerProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetMetricStreamerProcAddrTableFromDriver(loader::driver_t *driver);
__zedlllocal void ZE_APICALL
zetGetTracerExpProcAddrTableLegacy();
__zedlllocal ze_result_t ZE_APICALL
zetGetTracerExpProcAddrTableFromDriver(loader::driver_t *driver);

#if defined(__cplusplus)
};
#endif
