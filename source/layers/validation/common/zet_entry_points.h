/*
 * ***THIS FILE IS GENERATED. ***
 * See entry_points.h.mako for modifications
 *
 * Copyright (C) 2019-2024 Intel Corporation
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
    virtual ze_result_t zetModuleGetDebugInfoPrologue( zet_module_handle_t hModule, zet_module_debug_info_format_t format, size_t* pSize, uint8_t* pDebugInfo ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetModuleGetDebugInfoEpilogue( zet_module_handle_t hModule, zet_module_debug_info_format_t format, size_t* pSize, uint8_t* pDebugInfo , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceGetDebugPropertiesPrologue( zet_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceGetDebugPropertiesEpilogue( zet_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugAttachPrologue( zet_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugAttachEpilogue( zet_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugDetachPrologue( zet_debug_session_handle_t hDebug ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugDetachEpilogue( zet_debug_session_handle_t hDebug , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadEventPrologue( zet_debug_session_handle_t hDebug, uint64_t timeout, zet_debug_event_t* event ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadEventEpilogue( zet_debug_session_handle_t hDebug, uint64_t timeout, zet_debug_event_t* event , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugAcknowledgeEventPrologue( zet_debug_session_handle_t hDebug, const zet_debug_event_t* event ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugAcknowledgeEventEpilogue( zet_debug_session_handle_t hDebug, const zet_debug_event_t* event , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugInterruptPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugInterruptEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugResumePrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugResumeEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadMemoryPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, void* buffer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadMemoryEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, void* buffer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugWriteMemoryPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, const void* buffer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugWriteMemoryEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, const void* buffer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugGetRegisterSetPropertiesPrologue( zet_device_handle_t hDevice, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugGetRegisterSetPropertiesEpilogue( zet_device_handle_t hDevice, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugGetThreadRegisterSetPropertiesPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugGetThreadRegisterSetPropertiesEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadRegistersPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugReadRegistersEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugWriteRegistersPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDebugWriteRegistersEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetPrologue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetEpilogue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetPropertiesPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetPropertiesEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMetricValuesPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMetricValuesEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGetPrologue( zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGetEpilogue( zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGetPropertiesPrologue( zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGetPropertiesEpilogue( zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetContextActivateMetricGroupsPrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetContextActivateMetricGroupsEpilogue( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerOpenPrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerOpenEpilogue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricStreamerMarkerPrologue( zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricStreamerMarkerEpilogue( zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerClosePrologue( zet_metric_streamer_handle_t hMetricStreamer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerCloseEpilogue( zet_metric_streamer_handle_t hMetricStreamer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerReadDataPrologue( zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricStreamerReadDataEpilogue( zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryPoolCreatePrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t* desc, zet_metric_query_pool_handle_t* phMetricQueryPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryPoolCreateEpilogue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t* desc, zet_metric_query_pool_handle_t* phMetricQueryPool , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryPoolDestroyPrologue( zet_metric_query_pool_handle_t hMetricQueryPool ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryPoolDestroyEpilogue( zet_metric_query_pool_handle_t hMetricQueryPool , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryCreatePrologue( zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryCreateEpilogue( zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryDestroyPrologue( zet_metric_query_handle_t hMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryDestroyEpilogue( zet_metric_query_handle_t hMetricQuery , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryResetPrologue( zet_metric_query_handle_t hMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryResetEpilogue( zet_metric_query_handle_t hMetricQuery , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricQueryBeginPrologue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricQueryBeginEpilogue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricQueryEndPrologue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricQueryEndEpilogue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricMemoryBarrierPrologue( zet_command_list_handle_t hCommandList ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMetricMemoryBarrierEpilogue( zet_command_list_handle_t hCommandList , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryGetDataPrologue( zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricQueryGetDataEpilogue( zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetKernelGetProfileInfoPrologue( zet_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetKernelGetProfileInfoEpilogue( zet_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpCreatePrologue( zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpCreateEpilogue( zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpDestroyPrologue( zet_tracer_exp_handle_t hTracer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpDestroyEpilogue( zet_tracer_exp_handle_t hTracer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetProloguesPrologue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetProloguesEpilogue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetEpiloguesPrologue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetEpiloguesEpilogue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetEnabledPrologue( zet_tracer_exp_handle_t hTracer, ze_bool_t enable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetTracerExpSetEnabledEpilogue( zet_tracer_exp_handle_t hTracer, ze_bool_t enable , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceGetConcurrentMetricGroupsExpPrologue( zet_device_handle_t hDevice, uint32_t metricGroupCount, zet_metric_group_handle_t * phMetricGroups, uint32_t * pMetricGroupsCountPerConcurrentGroup, uint32_t * pConcurrentGroupCount ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceGetConcurrentMetricGroupsExpEpilogue( zet_device_handle_t hDevice, uint32_t metricGroupCount, zet_metric_group_handle_t * phMetricGroups, uint32_t * pMetricGroupsCountPerConcurrentGroup, uint32_t * pConcurrentGroupCount , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerCreateExpPrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t metricGroupCount, zet_metric_group_handle_t* phMetricGroups, zet_metric_tracer_exp_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_tracer_exp_handle_t* phMetricTracer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerCreateExpEpilogue( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t metricGroupCount, zet_metric_group_handle_t* phMetricGroups, zet_metric_tracer_exp_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_tracer_exp_handle_t* phMetricTracer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerDestroyExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerDestroyExpEpilogue( zet_metric_tracer_exp_handle_t hMetricTracer , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerEnableExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, ze_bool_t synchronous ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerEnableExpEpilogue( zet_metric_tracer_exp_handle_t hMetricTracer, ze_bool_t synchronous , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerDisableExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, ze_bool_t synchronous ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerDisableExpEpilogue( zet_metric_tracer_exp_handle_t hMetricTracer, ze_bool_t synchronous , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerReadDataExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, size_t* pRawDataSize, uint8_t* pRawData ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerReadDataExpEpilogue( zet_metric_tracer_exp_handle_t hMetricTracer, size_t* pRawDataSize, uint8_t* pRawData , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDecoderCreateExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, zet_metric_decoder_exp_handle_t* phMetricDecoder ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDecoderCreateExpEpilogue( zet_metric_tracer_exp_handle_t hMetricTracer, zet_metric_decoder_exp_handle_t* phMetricDecoder , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDecoderDestroyExpPrologue( zet_metric_decoder_exp_handle_t phMetricDecoder ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDecoderDestroyExpEpilogue( zet_metric_decoder_exp_handle_t phMetricDecoder , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDecoderGetDecodableMetricsExpPrologue( zet_metric_decoder_exp_handle_t hMetricDecoder, uint32_t* pCount, zet_metric_handle_t* phMetrics ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDecoderGetDecodableMetricsExpEpilogue( zet_metric_decoder_exp_handle_t hMetricDecoder, uint32_t* pCount, zet_metric_handle_t* phMetrics , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerDecodeExpPrologue( zet_metric_decoder_exp_handle_t phMetricDecoder, size_t* pRawDataSize, uint8_t* pRawData, uint32_t metricsCount, zet_metric_handle_t* phMetrics, uint32_t* pSetCount, uint32_t* pMetricEntriesCountPerSet, uint32_t* pMetricEntriesCount, zet_metric_entry_exp_t* pMetricEntries ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricTracerDecodeExpEpilogue( zet_metric_decoder_exp_handle_t phMetricDecoder, size_t* pRawDataSize, uint8_t* pRawData, uint32_t metricsCount, zet_metric_handle_t* phMetrics, uint32_t* pSetCount, uint32_t* pMetricEntriesCountPerSet, uint32_t* pMetricEntriesCount, zet_metric_entry_exp_t* pMetricEntries , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMarkerExpPrologue( zet_command_list_handle_t hCommandList, zet_metric_group_handle_t hMetricGroup, uint32_t value ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetCommandListAppendMarkerExpEpilogue( zet_command_list_handle_t hCommandList, zet_metric_group_handle_t hMetricGroup, uint32_t value , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceEnableMetricsExpPrologue( zet_device_handle_t hDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceEnableMetricsExpEpilogue( zet_device_handle_t hDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceDisableMetricsExpPrologue( zet_device_handle_t hDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceDisableMetricsExpEpilogue( zet_device_handle_t hDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMultipleMetricValuesExpPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMultipleMetricValuesExpEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetGlobalTimestampsExpPrologue( zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetGlobalTimestampsExpEpilogue( zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetExportDataExpPrologue( zet_metric_group_handle_t hMetricGroup, const uint8_t* pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t * pExportData ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupGetExportDataExpEpilogue( zet_metric_group_handle_t hMetricGroup, const uint8_t* pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t * pExportData , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMetricExportDataExpPrologue( ze_driver_handle_t hDriver, zet_metric_group_calculation_type_t type, size_t exportDataSize, const uint8_t* pExportData, zet_metric_calculate_exp_desc_t* pCalculateDescriptor, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCalculateMetricExportDataExpEpilogue( ze_driver_handle_t hDriver, zet_metric_group_calculation_type_t type, size_t exportDataSize, const uint8_t* pExportData, zet_metric_calculate_exp_desc_t* pCalculateDescriptor, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetExpPrologue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_programmable_exp_handle_t* phMetricProgrammables ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetExpEpilogue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_programmable_exp_handle_t* phMetricProgrammables , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetPropertiesExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_exp_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetPropertiesExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_exp_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetParamInfoExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t* pParameterCount, zet_metric_programmable_param_info_exp_t* pParameterInfo ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetParamInfoExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t* pParameterCount, zet_metric_programmable_param_info_exp_t* pParameterInfo , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetParamValueInfoExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t parameterOrdinal, uint32_t* pValueInfoCount, zet_metric_programmable_param_value_info_exp_t* pValueInfo ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricProgrammableGetParamValueInfoExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t parameterOrdinal, uint32_t* pValueInfoCount, zet_metric_programmable_param_value_info_exp_t* pValueInfo , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricCreateFromProgrammableExp2Prologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t parameterCount, zet_metric_programmable_param_value_exp_t* pParameterValues, const char* pName, const char* pDescription, uint32_t* pMetricHandleCount, zet_metric_handle_t* phMetricHandles ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricCreateFromProgrammableExp2Epilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t parameterCount, zet_metric_programmable_param_value_exp_t* pParameterValues, const char* pName, const char* pDescription, uint32_t* pMetricHandleCount, zet_metric_handle_t* phMetricHandles , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricCreateFromProgrammableExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_param_value_exp_t* pParameterValues, uint32_t parameterCount, const char* pName, const char* pDescription, uint32_t* pMetricHandleCount, zet_metric_handle_t* phMetricHandles ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricCreateFromProgrammableExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_param_value_exp_t* pParameterValues, uint32_t parameterCount, const char* pName, const char* pDescription, uint32_t* pMetricHandleCount, zet_metric_handle_t* phMetricHandles , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceCreateMetricGroupsFromMetricsExpPrologue( zet_device_handle_t hDevice, uint32_t metricCount, zet_metric_handle_t * phMetrics, const char * pMetricGroupNamePrefix, const char * pDescription, uint32_t * pMetricGroupCount, zet_metric_group_handle_t* phMetricGroup ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetDeviceCreateMetricGroupsFromMetricsExpEpilogue( zet_device_handle_t hDevice, uint32_t metricCount, zet_metric_handle_t * phMetrics, const char * pMetricGroupNamePrefix, const char * pDescription, uint32_t * pMetricGroupCount, zet_metric_group_handle_t* phMetricGroup , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCreateExpPrologue( zet_device_handle_t hDevice, const char* pName, const char* pDescription, zet_metric_group_sampling_type_flags_t samplingType, zet_metric_group_handle_t* phMetricGroup ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCreateExpEpilogue( zet_device_handle_t hDevice, const char* pName, const char* pDescription, zet_metric_group_sampling_type_flags_t samplingType, zet_metric_group_handle_t* phMetricGroup , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupAddMetricExpPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric, size_t * pErrorStringSize, char* pErrorString ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupAddMetricExpEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric, size_t * pErrorStringSize, char* pErrorString , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupRemoveMetricExpPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupRemoveMetricExpEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCloseExpPrologue( zet_metric_group_handle_t hMetricGroup ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupCloseExpEpilogue( zet_metric_group_handle_t hMetricGroup , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupDestroyExpPrologue( zet_metric_group_handle_t hMetricGroup ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricGroupDestroyExpEpilogue( zet_metric_group_handle_t hMetricGroup , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDestroyExpPrologue( zet_metric_handle_t hMetric ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zetMetricDestroyExpEpilogue( zet_metric_handle_t hMetric , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ~ZETValidationEntryPoints() {}
};
}