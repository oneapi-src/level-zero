/*
 * ***THIS FILE IS GENERATED. ***
 * See param.h.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_parameter_validation.h
 *
 */

#pragma once
#include "ze_validation_layer.h"
#include "zet_entry_points.h"


namespace validation_layer
{

    class ZETParameterValidation : public ZETValidationEntryPoints {
    public:
        ze_result_t zetModuleGetDebugInfoPrologue( zet_module_handle_t hModule, zet_module_debug_info_format_t format, size_t* pSize, uint8_t* pDebugInfo ) override;
        ze_result_t zetDeviceGetDebugPropertiesPrologue( zet_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties ) override;
        ze_result_t zetDebugAttachPrologue( zet_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug ) override;
        ze_result_t zetDebugDetachPrologue( zet_debug_session_handle_t hDebug ) override;
        ze_result_t zetDebugReadEventPrologue( zet_debug_session_handle_t hDebug, uint64_t timeout, zet_debug_event_t* event ) override;
        ze_result_t zetDebugAcknowledgeEventPrologue( zet_debug_session_handle_t hDebug, const zet_debug_event_t* event ) override;
        ze_result_t zetDebugInterruptPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) override;
        ze_result_t zetDebugResumePrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) override;
        ze_result_t zetDebugReadMemoryPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, void* buffer ) override;
        ze_result_t zetDebugWriteMemoryPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, const void* buffer ) override;
        ze_result_t zetDebugGetRegisterSetPropertiesPrologue( zet_device_handle_t hDevice, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) override;
        ze_result_t zetDebugGetThreadRegisterSetPropertiesPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) override;
        ze_result_t zetDebugReadRegistersPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) override;
        ze_result_t zetDebugWriteRegistersPrologue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) override;
        ze_result_t zetMetricGroupGetPrologue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups ) override;
        ze_result_t zetMetricGroupGetPropertiesPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties ) override;
        ze_result_t zetMetricGroupCalculateMetricValuesPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues ) override;
        ze_result_t zetMetricGetPrologue( zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics ) override;
        ze_result_t zetMetricGetPropertiesPrologue( zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties ) override;
        ze_result_t zetContextActivateMetricGroupsPrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups ) override;
        ze_result_t zetMetricStreamerOpenPrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer ) override;
        ze_result_t zetCommandListAppendMetricStreamerMarkerPrologue( zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value ) override;
        ze_result_t zetMetricStreamerClosePrologue( zet_metric_streamer_handle_t hMetricStreamer ) override;
        ze_result_t zetMetricStreamerReadDataPrologue( zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData ) override;
        ze_result_t zetMetricQueryPoolCreatePrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t* desc, zet_metric_query_pool_handle_t* phMetricQueryPool ) override;
        ze_result_t zetMetricQueryPoolDestroyPrologue( zet_metric_query_pool_handle_t hMetricQueryPool ) override;
        ze_result_t zetMetricQueryCreatePrologue( zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery ) override;
        ze_result_t zetMetricQueryDestroyPrologue( zet_metric_query_handle_t hMetricQuery ) override;
        ze_result_t zetMetricQueryResetPrologue( zet_metric_query_handle_t hMetricQuery ) override;
        ze_result_t zetCommandListAppendMetricQueryBeginPrologue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery ) override;
        ze_result_t zetCommandListAppendMetricQueryEndPrologue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zetCommandListAppendMetricMemoryBarrierPrologue( zet_command_list_handle_t hCommandList ) override;
        ze_result_t zetMetricQueryGetDataPrologue( zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData ) override;
        ze_result_t zetKernelGetProfileInfoPrologue( zet_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties ) override;
        ze_result_t zetTracerExpCreatePrologue( zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer ) override;
        ze_result_t zetTracerExpDestroyPrologue( zet_tracer_exp_handle_t hTracer ) override;
        ze_result_t zetTracerExpSetProloguesPrologue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) override;
        ze_result_t zetTracerExpSetEpiloguesPrologue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) override;
        ze_result_t zetTracerExpSetEnabledPrologue( zet_tracer_exp_handle_t hTracer, ze_bool_t enable ) override;
        ze_result_t zetDeviceGetConcurrentMetricGroupsExpPrologue( zet_device_handle_t hDevice, uint32_t metricGroupCount, zet_metric_group_handle_t * phMetricGroups, uint32_t * pMetricGroupsCountPerConcurrentGroup, uint32_t * pConcurrentGroupCount ) override;
        ze_result_t zetMetricTracerCreateExpPrologue( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t metricGroupCount, zet_metric_group_handle_t* phMetricGroups, zet_metric_tracer_exp_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_tracer_exp_handle_t* phMetricTracer ) override;
        ze_result_t zetMetricTracerDestroyExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer ) override;
        ze_result_t zetMetricTracerEnableExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, ze_bool_t synchronous ) override;
        ze_result_t zetMetricTracerDisableExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, ze_bool_t synchronous ) override;
        ze_result_t zetMetricTracerReadDataExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, size_t* pRawDataSize, uint8_t* pRawData ) override;
        ze_result_t zetMetricDecoderCreateExpPrologue( zet_metric_tracer_exp_handle_t hMetricTracer, zet_metric_decoder_exp_handle_t* phMetricDecoder ) override;
        ze_result_t zetMetricDecoderDestroyExpPrologue( zet_metric_decoder_exp_handle_t phMetricDecoder ) override;
        ze_result_t zetMetricDecoderGetDecodableMetricsExpPrologue( zet_metric_decoder_exp_handle_t hMetricDecoder, uint32_t* pCount, zet_metric_handle_t* phMetrics ) override;
        ze_result_t zetMetricTracerDecodeExpPrologue( zet_metric_decoder_exp_handle_t phMetricDecoder, size_t* pRawDataSize, uint8_t* pRawData, uint32_t metricsCount, zet_metric_handle_t* phMetrics, uint32_t* pSetCount, uint32_t* pMetricEntriesCountPerSet, uint32_t* pMetricEntriesCount, zet_metric_entry_exp_t* pMetricEntries ) override;
        ze_result_t zetCommandListAppendMarkerExpPrologue( zet_command_list_handle_t hCommandList, zet_metric_group_handle_t hMetricGroup, uint32_t value ) override;
        ze_result_t zetDeviceEnableMetricsExpPrologue( zet_device_handle_t hDevice ) override;
        ze_result_t zetDeviceDisableMetricsExpPrologue( zet_device_handle_t hDevice ) override;
        ze_result_t zetMetricGroupCalculateMultipleMetricValuesExpPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) override;
        ze_result_t zetMetricGroupGetGlobalTimestampsExpPrologue( zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp ) override;
        ze_result_t zetMetricGroupGetExportDataExpPrologue( zet_metric_group_handle_t hMetricGroup, const uint8_t* pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t * pExportData ) override;
        ze_result_t zetMetricGroupCalculateMetricExportDataExpPrologue( ze_driver_handle_t hDriver, zet_metric_group_calculation_type_t type, size_t exportDataSize, const uint8_t* pExportData, zet_metric_calculate_exp_desc_t* pCalculateDescriptor, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) override;
        ze_result_t zetMetricProgrammableGetExpPrologue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_programmable_exp_handle_t* phMetricProgrammables ) override;
        ze_result_t zetMetricProgrammableGetPropertiesExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_exp_properties_t* pProperties ) override;
        ze_result_t zetMetricProgrammableGetParamInfoExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t* pParameterCount, zet_metric_programmable_param_info_exp_t* pParameterInfo ) override;
        ze_result_t zetMetricProgrammableGetParamValueInfoExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t parameterOrdinal, uint32_t* pValueInfoCount, zet_metric_programmable_param_value_info_exp_t* pValueInfo ) override;
        ze_result_t zetMetricCreateFromProgrammableExp2Prologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t parameterCount, zet_metric_programmable_param_value_exp_t* pParameterValues, const char* pName, const char* pDescription, uint32_t* pMetricHandleCount, zet_metric_handle_t* phMetricHandles ) override;
        ze_result_t zetMetricCreateFromProgrammableExpPrologue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_param_value_exp_t* pParameterValues, uint32_t parameterCount, const char* pName, const char* pDescription, uint32_t* pMetricHandleCount, zet_metric_handle_t* phMetricHandles ) override;
        ze_result_t zetDeviceCreateMetricGroupsFromMetricsExpPrologue( zet_device_handle_t hDevice, uint32_t metricCount, zet_metric_handle_t * phMetrics, const char * pMetricGroupNamePrefix, const char * pDescription, uint32_t * pMetricGroupCount, zet_metric_group_handle_t* phMetricGroup ) override;
        ze_result_t zetMetricGroupCreateExpPrologue( zet_device_handle_t hDevice, const char* pName, const char* pDescription, zet_metric_group_sampling_type_flags_t samplingType, zet_metric_group_handle_t* phMetricGroup ) override;
        ze_result_t zetMetricGroupAddMetricExpPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric, size_t * pErrorStringSize, char* pErrorString ) override;
        ze_result_t zetMetricGroupRemoveMetricExpPrologue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric ) override;
        ze_result_t zetMetricGroupCloseExpPrologue( zet_metric_group_handle_t hMetricGroup ) override;
        ze_result_t zetMetricGroupDestroyExpPrologue( zet_metric_group_handle_t hMetricGroup ) override;
        ze_result_t zetMetricDestroyExpPrologue( zet_metric_handle_t hMetric ) override;
    };
}