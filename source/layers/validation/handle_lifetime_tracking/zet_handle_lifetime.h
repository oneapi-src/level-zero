/*
 * ***THIS FILE IS GENERATED. ***
 * See handle_lifetime.h.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_handle_lifetime.h
 *
 */

#pragma once
#include "zet_entry_points.h"


namespace validation_layer
{

    class ZETHandleLifetimeValidation : public ZETValidationEntryPoints {
    public:
        ze_result_t zetModuleGetDebugInfoEpilogue( zet_module_handle_t hModule, zet_module_debug_info_format_t format, size_t* pSize, uint8_t* pDebugInfo ) override;
        ze_result_t zetDeviceGetDebugPropertiesEpilogue( zet_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties ) override;
        ze_result_t zetDebugAttachEpilogue( zet_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug ) override;
        ze_result_t zetDebugDetachEpilogue( zet_debug_session_handle_t hDebug ) override;
        ze_result_t zetDebugReadEventEpilogue( zet_debug_session_handle_t hDebug, uint64_t timeout, zet_debug_event_t* event ) override;
        ze_result_t zetDebugAcknowledgeEventEpilogue( zet_debug_session_handle_t hDebug, const zet_debug_event_t* event ) override;
        ze_result_t zetDebugInterruptEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) override;
        ze_result_t zetDebugResumeEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread ) override;
        ze_result_t zetDebugReadMemoryEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, void* buffer ) override;
        ze_result_t zetDebugWriteMemoryEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, const zet_debug_memory_space_desc_t* desc, size_t size, const void* buffer ) override;
        ze_result_t zetDebugGetRegisterSetPropertiesEpilogue( zet_device_handle_t hDevice, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) override;
        ze_result_t zetDebugGetThreadRegisterSetPropertiesEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t* pCount, zet_debug_regset_properties_t* pRegisterSetProperties ) override;
        ze_result_t zetDebugReadRegistersEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) override;
        ze_result_t zetDebugWriteRegistersEpilogue( zet_debug_session_handle_t hDebug, ze_device_thread_t thread, uint32_t type, uint32_t start, uint32_t count, void* pRegisterValues ) override;
        ze_result_t zetMetricGroupGetEpilogue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups ) override;
        ze_result_t zetMetricGroupGetPropertiesEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties ) override;
        ze_result_t zetMetricGroupCalculateMetricValuesEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues ) override;
        ze_result_t zetMetricGetEpilogue( zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics ) override;
        ze_result_t zetMetricGetPropertiesEpilogue( zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties ) override;
        ze_result_t zetContextActivateMetricGroupsEpilogue( zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups ) override;
        ze_result_t zetMetricStreamerOpenEpilogue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer ) override;
        ze_result_t zetCommandListAppendMetricStreamerMarkerEpilogue( zet_command_list_handle_t hCommandList, zet_metric_streamer_handle_t hMetricStreamer, uint32_t value ) override;
        ze_result_t zetMetricStreamerCloseEpilogue( zet_metric_streamer_handle_t hMetricStreamer ) override;
        ze_result_t zetMetricStreamerReadDataEpilogue( zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData ) override;
        ze_result_t zetMetricQueryPoolCreateEpilogue( zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, const zet_metric_query_pool_desc_t* desc, zet_metric_query_pool_handle_t* phMetricQueryPool ) override;
        ze_result_t zetMetricQueryPoolDestroyEpilogue( zet_metric_query_pool_handle_t hMetricQueryPool ) override;
        ze_result_t zetMetricQueryCreateEpilogue( zet_metric_query_pool_handle_t hMetricQueryPool, uint32_t index, zet_metric_query_handle_t* phMetricQuery ) override;
        ze_result_t zetMetricQueryDestroyEpilogue( zet_metric_query_handle_t hMetricQuery ) override;
        ze_result_t zetMetricQueryResetEpilogue( zet_metric_query_handle_t hMetricQuery ) override;
        ze_result_t zetCommandListAppendMetricQueryBeginEpilogue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery ) override;
        ze_result_t zetCommandListAppendMetricQueryEndEpilogue( zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents ) override;
        ze_result_t zetCommandListAppendMetricMemoryBarrierEpilogue( zet_command_list_handle_t hCommandList ) override;
        ze_result_t zetMetricQueryGetDataEpilogue( zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData ) override;
        ze_result_t zetKernelGetProfileInfoEpilogue( zet_kernel_handle_t hKernel, zet_profile_properties_t* pProfileProperties ) override;
        ze_result_t zetTracerExpCreateEpilogue( zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer ) override;
        ze_result_t zetTracerExpDestroyEpilogue( zet_tracer_exp_handle_t hTracer ) override;
        ze_result_t zetTracerExpSetProloguesEpilogue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) override;
        ze_result_t zetTracerExpSetEpiloguesEpilogue( zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs ) override;
        ze_result_t zetTracerExpSetEnabledEpilogue( zet_tracer_exp_handle_t hTracer, ze_bool_t enable ) override;
        ze_result_t zetMetricGroupCalculateMultipleMetricValuesExpEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t* pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) override;
        ze_result_t zetMetricGroupGetGlobalTimestampsExpEpilogue( zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp ) override;
        ze_result_t zetMetricGroupGetExportDataExpEpilogue( zet_metric_group_handle_t hMetricGroup, const uint8_t* pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t * pExportData ) override;
        ze_result_t zetMetricGroupCalculateMetricExportDataExpEpilogue( ze_driver_handle_t hDriver, zet_metric_group_calculation_type_t type, size_t exportDataSize, const uint8_t* pExportData, zet_metric_calculate_exp_desc_t* pCalculateDescriptor, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues ) override;
        ze_result_t zetMetricProgrammableGetExpEpilogue( zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_programmable_exp_handle_t* phMetricProgrammables ) override;
        ze_result_t zetMetricProgrammableGetPropertiesExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_exp_properties_t* pProperties ) override;
        ze_result_t zetMetricProgrammableGetParamInfoExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t* pParameterCount, zet_metric_programmable_param_info_exp_t* pParameterInfo ) override;
        ze_result_t zetMetricProgrammableGetParamValueInfoExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, uint32_t parameterOrdinal, uint32_t* pValueInfoCount, zet_metric_programmable_param_value_info_exp_t* pValueInfo ) override;
        ze_result_t zetMetricCreateFromProgrammableExpEpilogue( zet_metric_programmable_exp_handle_t hMetricProgrammable, zet_metric_programmable_param_value_exp_t* pParameterValues, uint32_t parameterCount, const char* pName, const char* pDescription, uint32_t* pMetricHandleCount, zet_metric_handle_t* phMetricHandles ) override;
        ze_result_t zetMetricGroupCreateExpEpilogue( zet_device_handle_t hDevice, const char* pName, const char* pDescription, zet_metric_group_sampling_type_flags_t samplingType, zet_metric_group_handle_t* phMetricGroup ) override;
        ze_result_t zetMetricGroupAddMetricExpEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric, size_t * pErrorStringSize, char* pErrorString ) override;
        ze_result_t zetMetricGroupRemoveMetricExpEpilogue( zet_metric_group_handle_t hMetricGroup, zet_metric_handle_t hMetric ) override;
        ze_result_t zetMetricGroupCloseExpEpilogue( zet_metric_group_handle_t hMetricGroup ) override;
        ze_result_t zetMetricGroupDestroyExpEpilogue( zet_metric_group_handle_t hMetricGroup ) override;
        ze_result_t zetMetricDestroyExpEpilogue( zet_metric_handle_t hMetric ) override;
    };

}
