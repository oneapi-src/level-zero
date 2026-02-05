/*
 * ***THIS FILE IS GENERATED. ***
 * See to_string.h.mako for modifications
 *
 * Copyright (C) 2025-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_to_string.h
 * 
 * to_string functions for Level Zero types
 */

#ifndef _ZES_TO_STRING_H
#define _ZES_TO_STRING_H

#include "ze_api.h"
#include <string>
#include <sstream>
#include <iomanip>

// Include ze_to_string.h for common definitions
#include "ze_to_string.h"

namespace loader {
// Struct to_string functions
inline std::string to_string(const zes_base_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_base_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_base_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_base_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_base_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_base_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_base_config_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_base_config_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_base_capability_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_base_capability_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_driver_extension_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "name=" << to_string(desc->name);
    oss << ", version=" << to_string(desc->version);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_driver_extension_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_device_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", reset=" << to_string(&desc->reset);
    oss << ", repaired=" << to_string(&desc->repaired);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_device_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_reset_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", force=" << to_string(&desc->force);
    oss << ", resetType=" << to_string(&desc->resetType);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_reset_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_uuid_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "id=" << to_string(desc->id);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_uuid_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_device_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", core=" << to_string(&desc->core);
    oss << ", numSubdevices=" << to_string(desc->numSubdevices);
    oss << ", serialNumber=" << to_string(desc->serialNumber);
    oss << ", boardNumber=" << to_string(desc->boardNumber);
    oss << ", brandName=" << to_string(desc->brandName);
    oss << ", modelName=" << to_string(desc->modelName);
    oss << ", vendorName=" << to_string(desc->vendorName);
    oss << ", driverVersion=" << to_string(desc->driverVersion);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_device_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_device_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << ", type=" << to_string(&desc->type);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_device_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_process_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", processId=" << to_string(desc->processId);
    oss << ", memSize=" << to_string(desc->memSize);
    oss << ", sharedSize=" << to_string(desc->sharedSize);
    oss << ", engines=" << to_string(&desc->engines);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_process_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_address_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "domain=" << to_string(desc->domain);
    oss << ", bus=" << to_string(desc->bus);
    oss << ", device=" << to_string(desc->device);
    oss << ", function=" << to_string(desc->function);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_address_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_speed_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "gen=" << to_string(desc->gen);
    oss << ", width=" << to_string(desc->width);
    oss << ", maxBandwidth=" << to_string(desc->maxBandwidth);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_speed_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", address=" << to_string(&desc->address);
    oss << ", maxSpeed=" << to_string(&desc->maxSpeed);
    oss << ", haveBandwidthCounters=" << to_string(&desc->haveBandwidthCounters);
    oss << ", havePacketCounters=" << to_string(&desc->havePacketCounters);
    oss << ", haveReplayCounters=" << to_string(&desc->haveReplayCounters);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", status=" << to_string(&desc->status);
    oss << ", qualityIssues=" << to_string(&desc->qualityIssues);
    oss << ", stabilityIssues=" << to_string(&desc->stabilityIssues);
    oss << ", speed=" << to_string(&desc->speed);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_bar_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", index=" << to_string(desc->index);
    oss << ", base=" << to_string(desc->base);
    oss << ", size=" << to_string(desc->size);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_bar_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_bar_properties_1_2_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", index=" << to_string(desc->index);
    oss << ", base=" << to_string(desc->base);
    oss << ", size=" << to_string(desc->size);
    oss << ", resizableBarSupported=" << to_string(&desc->resizableBarSupported);
    oss << ", resizableBarEnabled=" << to_string(&desc->resizableBarEnabled);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_bar_properties_1_2_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_stats_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "timestamp=" << to_string(desc->timestamp);
    oss << ", replayCounter=" << to_string(desc->replayCounter);
    oss << ", packetCounter=" << to_string(desc->packetCounter);
    oss << ", rxCounter=" << to_string(desc->rxCounter);
    oss << ", txCounter=" << to_string(desc->txCounter);
    oss << ", speed=" << to_string(&desc->speed);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_stats_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_overclock_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", domainType=" << to_string(&desc->domainType);
    oss << ", AvailableControls=" << to_string(desc->AvailableControls);
    oss << ", VFProgramType=" << to_string(&desc->VFProgramType);
    oss << ", NumberOfVFPoints=" << to_string(desc->NumberOfVFPoints);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_overclock_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_control_property_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "MinValue=" << to_string(desc->MinValue);
    oss << ", MaxValue=" << to_string(desc->MaxValue);
    oss << ", StepValue=" << to_string(desc->StepValue);
    oss << ", RefValue=" << to_string(desc->RefValue);
    oss << ", DefaultValue=" << to_string(desc->DefaultValue);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_control_property_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_property_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "MinFreq=" << to_string(desc->MinFreq);
    oss << ", MaxFreq=" << to_string(desc->MaxFreq);
    oss << ", StepFreq=" << to_string(desc->StepFreq);
    oss << ", MinVolt=" << to_string(desc->MinVolt);
    oss << ", MaxVolt=" << to_string(desc->MaxVolt);
    oss << ", StepVolt=" << to_string(desc->StepVolt);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_property_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_diag_test_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "index=" << to_string(desc->index);
    oss << ", name=" << to_string(desc->name);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_diag_test_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_diag_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", name=" << to_string(desc->name);
    oss << ", haveTests=" << to_string(&desc->haveTests);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_diag_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_device_ecc_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", state=" << to_string(&desc->state);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_device_ecc_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_device_ecc_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", currentState=" << to_string(&desc->currentState);
    oss << ", pendingState=" << to_string(&desc->pendingState);
    oss << ", pendingAction=" << to_string(&desc->pendingAction);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_device_ecc_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_engine_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_engine_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_engine_stats_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "activeTime=" << to_string(desc->activeTime);
    oss << ", timestamp=" << to_string(desc->timestamp);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_engine_stats_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_port_id_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "fabricId=" << to_string(desc->fabricId);
    oss << ", attachId=" << to_string(desc->attachId);
    oss << ", portNumber=" << to_string(desc->portNumber);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_port_id_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_port_speed_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "bitRate=" << to_string(desc->bitRate);
    oss << ", width=" << to_string(desc->width);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_port_speed_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_port_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", model=" << to_string(desc->model);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", portId=" << to_string(&desc->portId);
    oss << ", maxRxSpeed=" << to_string(&desc->maxRxSpeed);
    oss << ", maxTxSpeed=" << to_string(&desc->maxTxSpeed);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_port_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_link_type_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "desc=" << to_string(desc->desc);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_link_type_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_port_config_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", enabled=" << to_string(&desc->enabled);
    oss << ", beaconing=" << to_string(&desc->beaconing);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_port_config_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_port_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", status=" << to_string(&desc->status);
    oss << ", qualityIssues=" << to_string(&desc->qualityIssues);
    oss << ", failureReasons=" << to_string(&desc->failureReasons);
    oss << ", remotePortId=" << to_string(&desc->remotePortId);
    oss << ", rxSpeed=" << to_string(&desc->rxSpeed);
    oss << ", txSpeed=" << to_string(&desc->txSpeed);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_port_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_port_throughput_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "timestamp=" << to_string(desc->timestamp);
    oss << ", rxCounter=" << to_string(desc->rxCounter);
    oss << ", txCounter=" << to_string(desc->txCounter);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_port_throughput_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fabric_port_error_counters_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", linkFailureCount=" << to_string(desc->linkFailureCount);
    oss << ", fwCommErrorCount=" << to_string(desc->fwCommErrorCount);
    oss << ", fwErrorCount=" << to_string(desc->fwErrorCount);
    oss << ", linkDegradeCount=" << to_string(desc->linkDegradeCount);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fabric_port_error_counters_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fan_speed_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "speed=" << to_string(desc->speed);
    oss << ", units=" << to_string(&desc->units);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fan_speed_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fan_temp_speed_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "temperature=" << to_string(desc->temperature);
    oss << ", speed=" << to_string(&desc->speed);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fan_temp_speed_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fan_speed_table_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "numPoints=" << to_string(desc->numPoints);
    oss << ", table=" << to_string(desc->table);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fan_speed_table_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fan_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", canControl=" << to_string(&desc->canControl);
    oss << ", supportedModes=" << to_string(desc->supportedModes);
    oss << ", supportedUnits=" << to_string(desc->supportedUnits);
    oss << ", maxRPM=" << to_string(desc->maxRPM);
    oss << ", maxPoints=" << to_string(desc->maxPoints);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fan_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_fan_config_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", mode=" << to_string(&desc->mode);
    oss << ", speedFixed=" << to_string(&desc->speedFixed);
    oss << ", speedTable=" << to_string(&desc->speedTable);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_fan_config_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_firmware_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", canControl=" << to_string(&desc->canControl);
    oss << ", name=" << to_string(desc->name);
    oss << ", version=" << to_string(desc->version);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_firmware_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_freq_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", canControl=" << to_string(&desc->canControl);
    oss << ", isThrottleEventSupported=" << to_string(&desc->isThrottleEventSupported);
    oss << ", min=" << to_string(desc->min);
    oss << ", max=" << to_string(desc->max);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_freq_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_freq_range_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "min=" << to_string(desc->min);
    oss << ", max=" << to_string(desc->max);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_freq_range_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_freq_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", currentVoltage=" << to_string(desc->currentVoltage);
    oss << ", request=" << to_string(desc->request);
    oss << ", tdp=" << to_string(desc->tdp);
    oss << ", efficient=" << to_string(desc->efficient);
    oss << ", actual=" << to_string(desc->actual);
    oss << ", throttleReasons=" << to_string(&desc->throttleReasons);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_freq_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_freq_throttle_time_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "throttleTime=" << to_string(desc->throttleTime);
    oss << ", timestamp=" << to_string(desc->timestamp);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_freq_throttle_time_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_oc_capabilities_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", isOcSupported=" << to_string(&desc->isOcSupported);
    oss << ", maxFactoryDefaultFrequency=" << to_string(desc->maxFactoryDefaultFrequency);
    oss << ", maxFactoryDefaultVoltage=" << to_string(desc->maxFactoryDefaultVoltage);
    oss << ", maxOcFrequency=" << to_string(desc->maxOcFrequency);
    oss << ", minOcVoltageOffset=" << to_string(desc->minOcVoltageOffset);
    oss << ", maxOcVoltageOffset=" << to_string(desc->maxOcVoltageOffset);
    oss << ", maxOcVoltage=" << to_string(desc->maxOcVoltage);
    oss << ", isTjMaxSupported=" << to_string(&desc->isTjMaxSupported);
    oss << ", isIccMaxSupported=" << to_string(&desc->isIccMaxSupported);
    oss << ", isHighVoltModeCapable=" << to_string(&desc->isHighVoltModeCapable);
    oss << ", isHighVoltModeEnabled=" << to_string(&desc->isHighVoltModeEnabled);
    oss << ", isExtendedModeSupported=" << to_string(&desc->isExtendedModeSupported);
    oss << ", isFixedModeSupported=" << to_string(&desc->isFixedModeSupported);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_oc_capabilities_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_led_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", canControl=" << to_string(&desc->canControl);
    oss << ", haveRGB=" << to_string(&desc->haveRGB);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_led_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_led_color_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "red=" << to_string(desc->red);
    oss << ", green=" << to_string(desc->green);
    oss << ", blue=" << to_string(desc->blue);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_led_color_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_led_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", isOn=" << to_string(&desc->isOn);
    oss << ", color=" << to_string(&desc->color);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_led_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_mem_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", location=" << to_string(&desc->location);
    oss << ", physicalSize=" << to_string(desc->physicalSize);
    oss << ", busWidth=" << to_string(desc->busWidth);
    oss << ", numChannels=" << to_string(desc->numChannels);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_mem_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_mem_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", health=" << to_string(&desc->health);
    oss << ", free=" << to_string(desc->free);
    oss << ", size=" << to_string(desc->size);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_mem_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_mem_bandwidth_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "readCounter=" << to_string(desc->readCounter);
    oss << ", writeCounter=" << to_string(desc->writeCounter);
    oss << ", maxBandwidth=" << to_string(desc->maxBandwidth);
    oss << ", timestamp=" << to_string(desc->timestamp);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_mem_bandwidth_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_mem_ext_bandwidth_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "memoryTimestampValidBits=" << to_string(desc->memoryTimestampValidBits);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_mem_ext_bandwidth_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_perf_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", engines=" << to_string(&desc->engines);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_perf_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", canControl=" << to_string(&desc->canControl);
    oss << ", isEnergyThresholdSupported=" << to_string(&desc->isEnergyThresholdSupported);
    oss << ", defaultLimit=" << to_string(desc->defaultLimit);
    oss << ", minLimit=" << to_string(desc->minLimit);
    oss << ", maxLimit=" << to_string(desc->maxLimit);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_energy_counter_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "energy=" << to_string(desc->energy);
    oss << ", timestamp=" << to_string(desc->timestamp);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_energy_counter_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_sustained_limit_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "enabled=" << to_string(&desc->enabled);
    oss << ", power=" << to_string(desc->power);
    oss << ", interval=" << to_string(desc->interval);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_sustained_limit_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_burst_limit_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "enabled=" << to_string(&desc->enabled);
    oss << ", power=" << to_string(desc->power);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_burst_limit_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_peak_limit_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "powerAC=" << to_string(desc->powerAC);
    oss << ", powerDC=" << to_string(desc->powerDC);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_peak_limit_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_energy_threshold_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "enable=" << to_string(&desc->enable);
    oss << ", threshold=" << to_string(desc->threshold);
    oss << ", processId=" << to_string(desc->processId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_energy_threshold_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_psu_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", haveFan=" << to_string(&desc->haveFan);
    oss << ", ampLimit=" << to_string(desc->ampLimit);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_psu_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_psu_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", voltStatus=" << to_string(&desc->voltStatus);
    oss << ", fanFailed=" << to_string(&desc->fanFailed);
    oss << ", temperature=" << to_string(desc->temperature);
    oss << ", current=" << to_string(desc->current);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_psu_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_ras_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_ras_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_ras_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", category=" << to_string(desc->category);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_ras_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_ras_config_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", totalThreshold=" << to_string(desc->totalThreshold);
    oss << ", detailedThresholds=" << to_string(&desc->detailedThresholds);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_ras_config_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_sched_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", canControl=" << to_string(&desc->canControl);
    oss << ", engines=" << to_string(&desc->engines);
    oss << ", supportedModes=" << to_string(desc->supportedModes);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_sched_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_sched_timeout_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", watchdogTimeout=" << to_string(desc->watchdogTimeout);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_sched_timeout_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_sched_timeslice_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", interval=" << to_string(desc->interval);
    oss << ", yieldTimeout=" << to_string(desc->yieldTimeout);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_sched_timeslice_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_standby_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_standby_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_temp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", onSubdevice=" << to_string(&desc->onSubdevice);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", maxTemperature=" << to_string(desc->maxTemperature);
    oss << ", isCriticalTempSupported=" << to_string(&desc->isCriticalTempSupported);
    oss << ", isThreshold1Supported=" << to_string(&desc->isThreshold1Supported);
    oss << ", isThreshold2Supported=" << to_string(&desc->isThreshold2Supported);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_temp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_temp_threshold_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "enableLowToHigh=" << to_string(&desc->enableLowToHigh);
    oss << ", enableHighToLow=" << to_string(&desc->enableHighToLow);
    oss << ", threshold=" << to_string(desc->threshold);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_temp_threshold_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_temp_config_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", enableCritical=" << to_string(&desc->enableCritical);
    oss << ", threshold1=" << to_string(&desc->threshold1);
    oss << ", threshold2=" << to_string(&desc->threshold2);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_temp_config_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_device_ecc_default_properties_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", defaultState=" << to_string(&desc->defaultState);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_device_ecc_default_properties_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_link_speed_downgrade_ext_state_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", pciLinkSpeedDowngradeStatus=" << to_string(&desc->pciLinkSpeedDowngradeStatus);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_link_speed_downgrade_ext_state_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_pci_link_speed_downgrade_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", pciLinkSpeedUpdateCapable=" << to_string(&desc->pciLinkSpeedUpdateCapable);
    oss << ", maxPciGenSupported=" << to_string(desc->maxPciGenSupported);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_pci_link_speed_downgrade_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_limit_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", level=" << to_string(&desc->level);
    oss << ", source=" << to_string(&desc->source);
    oss << ", limitUnit=" << to_string(&desc->limitUnit);
    oss << ", enabledStateLocked=" << to_string(&desc->enabledStateLocked);
    oss << ", enabled=" << to_string(&desc->enabled);
    oss << ", intervalValueLocked=" << to_string(&desc->intervalValueLocked);
    oss << ", interval=" << to_string(desc->interval);
    oss << ", limitValueLocked=" << to_string(&desc->limitValueLocked);
    oss << ", limit=" << to_string(desc->limit);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_limit_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", domain=" << to_string(&desc->domain);
    oss << ", defaultLimit=" << to_string(desc->defaultLimit);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_engine_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", countOfVirtualFunctionInstance=" << to_string(desc->countOfVirtualFunctionInstance);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_engine_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_ras_state_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "category=" << to_string(&desc->category);
    oss << ", errorCounter=" << to_string(desc->errorCounter);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_ras_state_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_mem_page_offline_state_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", memoryPageOffline=" << to_string(desc->memoryPageOffline);
    oss << ", maxMemoryPageOffline=" << to_string(desc->maxMemoryPageOffline);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_mem_page_offline_state_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_mem_bandwidth_counter_bits_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", validBitsCount=" << to_string(desc->validBitsCount);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_mem_bandwidth_counter_bits_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_power_domain_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", powerDomain=" << to_string(&desc->powerDomain);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_power_domain_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_subdevice_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_subdevice_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", address=" << to_string(&desc->address);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_util_mem_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", memTypeFlags=" << to_string(&desc->memTypeFlags);
    oss << ", free=" << to_string(desc->free);
    oss << ", size=" << to_string(desc->size);
    oss << ", timestamp=" << to_string(desc->timestamp);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_util_mem_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_util_engine_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", activeCounterValue=" << to_string(desc->activeCounterValue);
    oss << ", samplingCounterValue=" << to_string(desc->samplingCounterValue);
    oss << ", timestamp=" << to_string(desc->timestamp);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_util_engine_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_exp_capabilities_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", address=" << to_string(&desc->address);
    oss << ", vfDeviceMemSize=" << to_string(desc->vfDeviceMemSize);
    oss << ", vfID=" << to_string(desc->vfID);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_exp_capabilities_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_exp2_capabilities_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", address=" << to_string(&desc->address);
    oss << ", vfDeviceMemSize=" << to_string(desc->vfDeviceMemSize);
    oss << ", vfID=" << to_string(desc->vfID);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_exp2_capabilities_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_util_mem_exp2_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", vfMemLocation=" << to_string(&desc->vfMemLocation);
    oss << ", vfMemUtilized=" << to_string(desc->vfMemUtilized);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_util_mem_exp2_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const zes_vf_util_engine_exp2_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", vfEngineType=" << to_string(&desc->vfEngineType);
    oss << ", activeCounterValue=" << to_string(desc->activeCounterValue);
    oss << ", samplingCounterValue=" << to_string(desc->samplingCounterValue);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const zes_vf_util_engine_exp2_t& desc) {
    return to_string(&desc);
}

} // namespace loader

#endif // _ZES_TO_STRING_H
