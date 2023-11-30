/*
 * ***THIS FILE IS GENERATED. ***
 * See entry_points.h.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_entry_points.h
 *
 */
#pragma once
#include "zet_api.h"

namespace validation_layer
{

class ZETValidationEntryPoints {
public:
    virtual ze_result_t zetModuleGetDebugInfo( zet_module_handle_t hModule, zet_module_debug_info_format_t format, size_t* pSize, uint8_t* pDebugInfo ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceGetDebugProperties( zet_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugAttach( zet_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugDetach( zet_debug_session_handle_t hDebug ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadEvent( zet_debug_session_handle_t hDebug, uint64_t timeout, zet_debug_event_t* event ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugAcknowledgeEvent( zet_debug_session_handle_t hDebug, const zet_debug_event_t* event ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugInterrupt( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugResume( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadMemory( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, void* buffer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugWriteMemory( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, const void* buffer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugGetRegisterSetProperties( zet_device_handle_t hDevice, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugGetThreadRegisterSetProperties( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadRegisters( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugWriteRegisters( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGet( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetProperties( zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMetricValues( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGet( zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGetProperties( zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetContextActivateMetricGroups( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerOpen( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricStreamerMarker( zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerClose( zet_metric_streamer_handle_t hMetricStreamer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerReadData( zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryPoolCreate( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t* desc, zet_metric_query_pool_handle_t* phMetricQueryPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryPoolDestroy( zet_metric_query_pool_handle_t hMetricQueryPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryCreate( zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryDestroy( zet_metric_query_handle_t hMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryReset( zet_metric_query_handle_t hMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricQueryBegin( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricQueryEnd( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricMemoryBarrier( zet_command_list_handle_t hCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryGetData( zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetKernelGetProfileInfo( zet_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpCreate( zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpDestroy( zet_tracer_exp_handle_t hTracer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetPrologues( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetEpilogues( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetEnabled( zet_tracer_exp_handle_t hTracer, ze_bool_t enable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMultipleMetricValuesExp( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetGlobalTimestampsExp( zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetExportDataExp( zet_metric_group_handle_t hMetricGroup, const uint8_t* pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t * pExportData ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMetricExportDataExp( ze_driver_handle_t hDriver, zet_metric_group_calculation_type_t type, size_t exportDataSize, const uint8_t* pExportData, zet_metric_calculate_exp_desc_t* pCalculateDescriptor, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) {return ZE_RESULT_SUCCESS;}
    virtual ~ZETValidationEntryPoints() {}
};
}