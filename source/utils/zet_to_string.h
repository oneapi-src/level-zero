/*
 * ***THIS FILE IS GENERATED. ***
 * See to_string.h.mako for modifications
 *
 * Copyright (C) 2025-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_to_string.h
 * 
 * to_string functions for Level Zero types
 */

#ifndef _ZET_TO_STRING_H
#define _ZET_TO_STRING_H

#include "ze_api.h"
#include <string>
#include <sstream>
#include <iomanip>

// Include ze_to_string.h for common definitions
#include "ze_to_string.h"

namespace loader {
// Struct to_string functions
inline std::string to_string(const zet_base_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_base_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_base_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_base_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_typed_value_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "type=" << to_string(&desc->type);
    oss << ", value=" << to_string(&desc->value);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_typed_value_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_device_debug_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_device_debug_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_config_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "pid=" << to_string(desc->pid);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_config_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_event_info_detached_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "reason=" << to_string(&desc->reason);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_event_info_detached_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_event_info_module_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "format=" << to_string(&desc->format);
    oss << ", moduleBegin=" << to_string(desc->moduleBegin);
    oss << ", moduleEnd=" << to_string(desc->moduleEnd);
    oss << ", load=" << to_string(desc->load);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_event_info_module_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_event_info_thread_stopped_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "thread=" << to_string(&desc->thread);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_event_info_thread_stopped_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_event_info_page_fault_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "address=" << to_string(desc->address);
    oss << ", mask=" << to_string(desc->mask);
    oss << ", reason=" << to_string(&desc->reason);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_event_info_page_fault_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_event_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "type=" << to_string(&desc->type);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", info=" << to_string(&desc->info);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_event_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_memory_space_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", address=" << to_string(desc->address);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_memory_space_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_debug_regset_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(desc->type);
    oss << ", version=" << to_string(desc->version);
    oss << ", generalFlags=" << to_string(&desc->generalFlags);
    oss << ", deviceFlags=" << to_string(desc->deviceFlags);
    oss << ", count=" << to_string(desc->count);
    oss << ", bitSize=" << to_string(desc->bitSize);
    oss << ", byteSize=" << to_string(desc->byteSize);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_debug_regset_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_group_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", name=" << to_string(desc->name);
    oss << ", description=" << to_string(desc->description);
    oss << ", samplingType=" << to_string(&desc->samplingType);
    oss << ", domain=" << to_string(desc->domain);
    oss << ", metricCount=" << to_string(desc->metricCount);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_group_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", name=" << to_string(desc->name);
    oss << ", description=" << to_string(desc->description);
    oss << ", component=" << to_string(desc->component);
    oss << ", tierNumber=" << to_string(desc->tierNumber);
    oss << ", metricType=" << to_string(&desc->metricType);
    oss << ", resultType=" << to_string(&desc->resultType);
    oss << ", resultUnits=" << to_string(desc->resultUnits);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_streamer_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", notifyEveryNReports=" << to_string(desc->notifyEveryNReports);
    oss << ", samplingPeriod=" << to_string(desc->samplingPeriod);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_streamer_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_query_pool_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", count=" << to_string(desc->count);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_query_pool_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_profile_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", numTokens=" << to_string(desc->numTokens);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_profile_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_profile_free_register_token_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "type=" << to_string(&desc->type);
    oss << ", size=" << to_string(desc->size);
    oss << ", count=" << to_string(desc->count);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_profile_free_register_token_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_profile_register_sequence_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "start=" << to_string(desc->start);
    oss << ", count=" << to_string(desc->count);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_profile_register_sequence_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_tracer_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", pUserData=" << to_string(desc->pUserData);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_tracer_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_tracer_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", notifyEveryNBytes=" << to_string(desc->notifyEveryNBytes);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_tracer_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_entry_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "value=" << to_string(&desc->value);
    oss << ", timeStamp=" << to_string(desc->timeStamp);
    oss << ", metricIndex=" << to_string(desc->metricIndex);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_entry_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_group_type_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_group_type_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_export_dma_buf_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", fd=" << to_string(desc->fd);
    oss << ", size=" << to_string(desc->size);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_export_dma_buf_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_source_id_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", sourceId=" << to_string(desc->sourceId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_source_id_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_global_timestamps_resolution_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", timerResolution=" << to_string(desc->timerResolution);
    oss << ", timestampValidBits=" << to_string(desc->timestampValidBits);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_global_timestamps_resolution_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_calculate_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", rawReportSkipCount=" << to_string(desc->rawReportSkipCount);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_calculate_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_programmable_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", name=" << to_string(desc->name);
    oss << ", description=" << to_string(desc->description);
    oss << ", component=" << to_string(desc->component);
    oss << ", tierNumber=" << to_string(desc->tierNumber);
    oss << ", domain=" << to_string(desc->domain);
    oss << ", parameterCount=" << to_string(desc->parameterCount);
    oss << ", samplingType=" << to_string(&desc->samplingType);
    oss << ", sourceId=" << to_string(desc->sourceId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_programmable_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_value_uint64_range_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "ui64Min=" << to_string(desc->ui64Min);
    oss << ", ui64Max=" << to_string(desc->ui64Max);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_value_uint64_range_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_value_fp64_range_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "fp64Min=" << to_string(desc->fp64Min);
    oss << ", fp64Max=" << to_string(desc->fp64Max);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_value_fp64_range_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_programmable_param_info_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", name=" << to_string(desc->name);
    oss << ", valueInfoType=" << to_string(&desc->valueInfoType);
    oss << ", defaultValue=" << to_string(&desc->defaultValue);
    oss << ", valueInfoCount=" << to_string(desc->valueInfoCount);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_programmable_param_info_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_programmable_param_value_info_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", valueInfo=" << to_string(&desc->valueInfo);
    oss << ", description=" << to_string(desc->description);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_programmable_param_value_info_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zet_metric_programmable_param_value_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "value=" << to_string(&desc->value);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zet_metric_programmable_param_value_exp_t& desc) {
    return to_string(&desc);
}

} // namespace loader

#endif // _ZET_TO_STRING_H
