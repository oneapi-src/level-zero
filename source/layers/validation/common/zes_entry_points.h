/*
 * ***THIS FILE IS GENERATED. ***
 * See entry_points.h.mako for modifications
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_entry_points.h
 *
 */
#pragma once
#include "zes_api.h"

namespace validation_layer
{

class ZESValidationEntryPoints {
public:
    virtual ze_result_t zesInitPrologue( zes_init_flags_t flags ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesInitEpilogue( zes_init_flags_t flags , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetPrologue( uint32_t* pCount, zes_driver_handle_t* phDrivers ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetEpilogue( uint32_t* pCount, zes_driver_handle_t* phDrivers , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetExtensionPropertiesPrologue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_driver_extension_properties_t* pExtensionProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetExtensionPropertiesEpilogue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_driver_extension_properties_t* pExtensionProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetExtensionFunctionAddressPrologue( zes_driver_handle_t hDriver, const char* name, void** ppFunctionAddress ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetExtensionFunctionAddressEpilogue( zes_driver_handle_t hDriver, const char* name, void** ppFunctionAddress , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetPrologue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_device_handle_t* phDevices ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetEpilogue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_device_handle_t* phDevices , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetPropertiesPrologue( zes_device_handle_t hDevice, zes_device_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetPropertiesEpilogue( zes_device_handle_t hDevice, zes_device_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetStatePrologue( zes_device_handle_t hDevice, zes_device_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetStateEpilogue( zes_device_handle_t hDevice, zes_device_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetPrologue( zes_device_handle_t hDevice, ze_bool_t force ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetEpilogue( zes_device_handle_t hDevice, ze_bool_t force , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetExtPrologue( zes_device_handle_t hDevice, zes_reset_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetExtEpilogue( zes_device_handle_t hDevice, zes_reset_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceProcessesGetStatePrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceProcessesGetStateEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetPropertiesPrologue( zes_device_handle_t hDevice, zes_pci_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetPropertiesEpilogue( zes_device_handle_t hDevice, zes_pci_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetStatePrologue( zes_device_handle_t hDevice, zes_pci_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetStateEpilogue( zes_device_handle_t hDevice, zes_pci_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetBarsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetBarsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetStatsPrologue( zes_device_handle_t hDevice, zes_pci_stats_t* pStats ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetStatsEpilogue( zes_device_handle_t hDevice, zes_pci_stats_t* pStats , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceSetOverclockWaiverPrologue( zes_device_handle_t hDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceSetOverclockWaiverEpilogue( zes_device_handle_t hDevice , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetOverclockDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pOverclockDomains ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetOverclockDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pOverclockDomains , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetOverclockControlsPrologue( zes_device_handle_t hDevice, zes_overclock_domain_t domainType, uint32_t* pAvailableControls ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetOverclockControlsEpilogue( zes_device_handle_t hDevice, zes_overclock_domain_t domainType, uint32_t* pAvailableControls , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetOverclockSettingsPrologue( zes_device_handle_t hDevice, ze_bool_t onShippedState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetOverclockSettingsEpilogue( zes_device_handle_t hDevice, ze_bool_t onShippedState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceReadOverclockStatePrologue( zes_device_handle_t hDevice, zes_overclock_mode_t* pOverclockMode, ze_bool_t* pWaiverSetting, ze_bool_t* pOverclockState, zes_pending_action_t* pPendingAction, ze_bool_t* pPendingReset ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceReadOverclockStateEpilogue( zes_device_handle_t hDevice, zes_overclock_mode_t* pOverclockMode, ze_bool_t* pWaiverSetting, ze_bool_t* pOverclockState, zes_pending_action_t* pPendingAction, ze_bool_t* pPendingReset , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumOverclockDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_overclock_handle_t* phDomainHandle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumOverclockDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_overclock_handle_t* phDomainHandle , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainPropertiesPrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_properties_t* pDomainProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainPropertiesEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_properties_t* pDomainProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainVFPropertiesPrologue( zes_overclock_handle_t hDomainHandle, zes_vf_property_t* pVFProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainVFPropertiesEpilogue( zes_overclock_handle_t hDomainHandle, zes_vf_property_t* pVFProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainControlPropertiesPrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_property_t* pControlProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainControlPropertiesEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_property_t* pControlProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlCurrentValuePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlCurrentValueEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlPendingValuePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlPendingValueEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockSetControlUserValuePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double pValue, zes_pending_action_t* pPendingAction ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockSetControlUserValueEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double pValue, zes_pending_action_t* pPendingAction , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlStatePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_state_t* pControlState, zes_pending_action_t* pPendingAction ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlStateEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_state_t* pControlState, zes_pending_action_t* pPendingAction , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetVFPointValuesPrologue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, zes_vf_array_type_t VFArrayType, uint32_t PointIndex, uint32_t* PointValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetVFPointValuesEpilogue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, zes_vf_array_type_t VFArrayType, uint32_t PointIndex, uint32_t* PointValue , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockSetVFPointValuesPrologue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, uint32_t PointIndex, uint32_t PointValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockSetVFPointValuesEpilogue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, uint32_t PointIndex, uint32_t PointValue , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumDiagnosticTestSuitesPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_diag_handle_t* phDiagnostics ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumDiagnosticTestSuitesEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_diag_handle_t* phDiagnostics , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsGetPropertiesPrologue( zes_diag_handle_t hDiagnostics, zes_diag_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsGetPropertiesEpilogue( zes_diag_handle_t hDiagnostics, zes_diag_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsGetTestsPrologue( zes_diag_handle_t hDiagnostics, uint32_t* pCount, zes_diag_test_t* pTests ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsGetTestsEpilogue( zes_diag_handle_t hDiagnostics, uint32_t* pCount, zes_diag_test_t* pTests , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsRunTestsPrologue( zes_diag_handle_t hDiagnostics, uint32_t startIndex, uint32_t endIndex, zes_diag_result_t* pResult ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsRunTestsEpilogue( zes_diag_handle_t hDiagnostics, uint32_t startIndex, uint32_t endIndex, zes_diag_result_t* pResult , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEccAvailablePrologue( zes_device_handle_t hDevice, ze_bool_t* pAvailable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEccAvailableEpilogue( zes_device_handle_t hDevice, ze_bool_t* pAvailable , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEccConfigurablePrologue( zes_device_handle_t hDevice, ze_bool_t* pConfigurable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEccConfigurableEpilogue( zes_device_handle_t hDevice, ze_bool_t* pConfigurable , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetEccStatePrologue( zes_device_handle_t hDevice, zes_device_ecc_properties_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetEccStateEpilogue( zes_device_handle_t hDevice, zes_device_ecc_properties_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceSetEccStatePrologue( zes_device_handle_t hDevice, const zes_device_ecc_desc_t* newState, zes_device_ecc_properties_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceSetEccStateEpilogue( zes_device_handle_t hDevice, const zes_device_ecc_desc_t* newState, zes_device_ecc_properties_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumEngineGroupsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumEngineGroupsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetPropertiesPrologue( zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetPropertiesEpilogue( zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetActivityPrologue( zes_engine_handle_t hEngine, zes_engine_stats_t* pStats ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetActivityEpilogue( zes_engine_handle_t hEngine, zes_engine_stats_t* pStats , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEventRegisterPrologue( zes_device_handle_t hDevice, zes_event_type_flags_t events ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEventRegisterEpilogue( zes_device_handle_t hDevice, zes_event_type_flags_t events , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverEventListenPrologue( ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverEventListenEpilogue( ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverEventListenExPrologue( ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverEventListenExEpilogue( ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFabricPortsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fabric_port_handle_t* phPort ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFabricPortsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fabric_port_handle_t* phPort , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetPropertiesPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetPropertiesEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetLinkTypePrologue( zes_fabric_port_handle_t hPort, zes_fabric_link_type_t* pLinkType ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetLinkTypeEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_link_type_t* pLinkType , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetConfigPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetConfigEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_config_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortSetConfigPrologue( zes_fabric_port_handle_t hPort, const zes_fabric_port_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortSetConfigEpilogue( zes_fabric_port_handle_t hPort, const zes_fabric_port_config_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetStatePrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetStateEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetThroughputPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_throughput_t* pThroughput ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetThroughputEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_throughput_t* pThroughput , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetFabricErrorCountersPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_error_counters_t* pErrors ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetFabricErrorCountersEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_error_counters_t* pErrors , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetMultiPortThroughputPrologue( zes_device_handle_t hDevice, uint32_t numPorts, zes_fabric_port_handle_t* phPort, zes_fabric_port_throughput_t** pThroughput ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetMultiPortThroughputEpilogue( zes_device_handle_t hDevice, uint32_t numPorts, zes_fabric_port_handle_t* phPort, zes_fabric_port_throughput_t** pThroughput , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFansPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fan_handle_t* phFan ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFansEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fan_handle_t* phFan , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetPropertiesPrologue( zes_fan_handle_t hFan, zes_fan_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetPropertiesEpilogue( zes_fan_handle_t hFan, zes_fan_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetConfigPrologue( zes_fan_handle_t hFan, zes_fan_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetConfigEpilogue( zes_fan_handle_t hFan, zes_fan_config_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetDefaultModePrologue( zes_fan_handle_t hFan ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetDefaultModeEpilogue( zes_fan_handle_t hFan , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetFixedSpeedModePrologue( zes_fan_handle_t hFan, const zes_fan_speed_t* speed ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetFixedSpeedModeEpilogue( zes_fan_handle_t hFan, const zes_fan_speed_t* speed , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetSpeedTableModePrologue( zes_fan_handle_t hFan, const zes_fan_speed_table_t* speedTable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetSpeedTableModeEpilogue( zes_fan_handle_t hFan, const zes_fan_speed_table_t* speedTable , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetStatePrologue( zes_fan_handle_t hFan, zes_fan_speed_units_t units, int32_t* pSpeed ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetStateEpilogue( zes_fan_handle_t hFan, zes_fan_speed_units_t units, int32_t* pSpeed , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFirmwaresPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_firmware_handle_t* phFirmware ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFirmwaresEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_firmware_handle_t* phFirmware , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetPropertiesPrologue( zes_firmware_handle_t hFirmware, zes_firmware_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetPropertiesEpilogue( zes_firmware_handle_t hFirmware, zes_firmware_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareFlashPrologue( zes_firmware_handle_t hFirmware, void* pImage, uint32_t size ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareFlashEpilogue( zes_firmware_handle_t hFirmware, void* pImage, uint32_t size , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetFlashProgressPrologue( zes_firmware_handle_t hFirmware, uint32_t* pCompletionPercent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetFlashProgressEpilogue( zes_firmware_handle_t hFirmware, uint32_t* pCompletionPercent , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetConsoleLogsPrologue( zes_firmware_handle_t hFirmware, size_t* pSize, char* pFirmwareLog ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetConsoleLogsEpilogue( zes_firmware_handle_t hFirmware, size_t* pSize, char* pFirmwareLog , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFrequencyDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFrequencyDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetPropertiesPrologue( zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetPropertiesEpilogue( zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetAvailableClocksPrologue( zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetAvailableClocksEpilogue( zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetRangePrologue( zes_freq_handle_t hFrequency, zes_freq_range_t* pLimits ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetRangeEpilogue( zes_freq_handle_t hFrequency, zes_freq_range_t* pLimits , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencySetRangePrologue( zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencySetRangeEpilogue( zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetStatePrologue( zes_freq_handle_t hFrequency, zes_freq_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetStateEpilogue( zes_freq_handle_t hFrequency, zes_freq_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetThrottleTimePrologue( zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetThrottleTimeEpilogue( zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetCapabilitiesPrologue( zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetCapabilitiesEpilogue( zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetFrequencyTargetPrologue( zes_freq_handle_t hFrequency, double* pCurrentOcFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetFrequencyTargetEpilogue( zes_freq_handle_t hFrequency, double* pCurrentOcFrequency , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetFrequencyTargetPrologue( zes_freq_handle_t hFrequency, double CurrentOcFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetFrequencyTargetEpilogue( zes_freq_handle_t hFrequency, double CurrentOcFrequency , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetVoltageTargetPrologue( zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetVoltageTargetEpilogue( zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetVoltageTargetPrologue( zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetVoltageTargetEpilogue( zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetModePrologue( zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetModeEpilogue( zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetModePrologue( zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetModeEpilogue( zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetIccMaxPrologue( zes_freq_handle_t hFrequency, double* pOcIccMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetIccMaxEpilogue( zes_freq_handle_t hFrequency, double* pOcIccMax , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetIccMaxPrologue( zes_freq_handle_t hFrequency, double ocIccMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetIccMaxEpilogue( zes_freq_handle_t hFrequency, double ocIccMax , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetTjMaxPrologue( zes_freq_handle_t hFrequency, double* pOcTjMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetTjMaxEpilogue( zes_freq_handle_t hFrequency, double* pOcTjMax , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetTjMaxPrologue( zes_freq_handle_t hFrequency, double ocTjMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetTjMaxEpilogue( zes_freq_handle_t hFrequency, double ocTjMax , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumLedsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_led_handle_t* phLed ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumLedsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_led_handle_t* phLed , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedGetPropertiesPrologue( zes_led_handle_t hLed, zes_led_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedGetPropertiesEpilogue( zes_led_handle_t hLed, zes_led_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedGetStatePrologue( zes_led_handle_t hLed, zes_led_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedGetStateEpilogue( zes_led_handle_t hLed, zes_led_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedSetStatePrologue( zes_led_handle_t hLed, ze_bool_t enable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedSetStateEpilogue( zes_led_handle_t hLed, ze_bool_t enable , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedSetColorPrologue( zes_led_handle_t hLed, const zes_led_color_t* pColor ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedSetColorEpilogue( zes_led_handle_t hLed, const zes_led_color_t* pColor , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumMemoryModulesPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumMemoryModulesEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetPropertiesPrologue( zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetPropertiesEpilogue( zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetStatePrologue( zes_mem_handle_t hMemory, zes_mem_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetStateEpilogue( zes_mem_handle_t hMemory, zes_mem_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetBandwidthPrologue( zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetBandwidthEpilogue( zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPerformanceFactorDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPerformanceFactorDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorGetPropertiesPrologue( zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorGetPropertiesEpilogue( zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorGetConfigPrologue( zes_perf_handle_t hPerf, double* pFactor ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorGetConfigEpilogue( zes_perf_handle_t hPerf, double* pFactor , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorSetConfigPrologue( zes_perf_handle_t hPerf, double factor ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorSetConfigEpilogue( zes_perf_handle_t hPerf, double factor , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPowerDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPowerDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetCardPowerDomainPrologue( zes_device_handle_t hDevice, zes_pwr_handle_t* phPower ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetCardPowerDomainEpilogue( zes_device_handle_t hDevice, zes_pwr_handle_t* phPower , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetPropertiesPrologue( zes_pwr_handle_t hPower, zes_power_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetPropertiesEpilogue( zes_pwr_handle_t hPower, zes_power_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetEnergyCounterPrologue( zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetEnergyCounterEpilogue( zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetLimitsPrologue( zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetLimitsEpilogue( zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetLimitsPrologue( zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetLimitsEpilogue( zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetEnergyThresholdPrologue( zes_pwr_handle_t hPower, zes_energy_threshold_t* pThreshold ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetEnergyThresholdEpilogue( zes_pwr_handle_t hPower, zes_energy_threshold_t* pThreshold , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetEnergyThresholdPrologue( zes_pwr_handle_t hPower, double threshold ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetEnergyThresholdEpilogue( zes_pwr_handle_t hPower, double threshold , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPsusPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_psu_handle_t* phPsu ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPsusEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_psu_handle_t* phPsu , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPsuGetPropertiesPrologue( zes_psu_handle_t hPsu, zes_psu_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPsuGetPropertiesEpilogue( zes_psu_handle_t hPsu, zes_psu_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPsuGetStatePrologue( zes_psu_handle_t hPsu, zes_psu_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPsuGetStateEpilogue( zes_psu_handle_t hPsu, zes_psu_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumRasErrorSetsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumRasErrorSetsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetPropertiesPrologue( zes_ras_handle_t hRas, zes_ras_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetPropertiesEpilogue( zes_ras_handle_t hRas, zes_ras_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetConfigPrologue( zes_ras_handle_t hRas, zes_ras_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetConfigEpilogue( zes_ras_handle_t hRas, zes_ras_config_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasSetConfigPrologue( zes_ras_handle_t hRas, const zes_ras_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasSetConfigEpilogue( zes_ras_handle_t hRas, const zes_ras_config_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetStatePrologue( zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetStateEpilogue( zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumSchedulersPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumSchedulersEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetPropertiesPrologue( zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetPropertiesEpilogue( zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetCurrentModePrologue( zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetCurrentModeEpilogue( zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetTimeoutModePropertiesPrologue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetTimeoutModePropertiesEpilogue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetTimesliceModePropertiesPrologue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetTimesliceModePropertiesEpilogue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetTimeoutModePrologue( zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetTimeoutModeEpilogue( zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetTimesliceModePrologue( zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetTimesliceModeEpilogue( zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetExclusiveModePrologue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetExclusiveModeEpilogue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetComputeUnitDebugModePrologue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetComputeUnitDebugModeEpilogue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumStandbyDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumStandbyDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbyGetPropertiesPrologue( zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbyGetPropertiesEpilogue( zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbyGetModePrologue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbyGetModeEpilogue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbySetModePrologue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbySetModeEpilogue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumTemperatureSensorsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumTemperatureSensorsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetPropertiesPrologue( zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetPropertiesEpilogue( zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetConfigPrologue( zes_temp_handle_t hTemperature, zes_temp_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetConfigEpilogue( zes_temp_handle_t hTemperature, zes_temp_config_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureSetConfigPrologue( zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureSetConfigEpilogue( zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetStatePrologue( zes_temp_handle_t hTemperature, double* pTemperature ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetStateEpilogue( zes_temp_handle_t hTemperature, double* pTemperature , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetLimitsExtPrologue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetLimitsExtEpilogue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetLimitsExtPrologue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetLimitsExtEpilogue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetActivityExtPrologue( zes_engine_handle_t hEngine, uint32_t* pCount, zes_engine_stats_t* pStats ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetActivityExtEpilogue( zes_engine_handle_t hEngine, uint32_t* pCount, zes_engine_stats_t* pStats , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetStateExpPrologue( zes_ras_handle_t hRas, uint32_t* pCount, zes_ras_state_exp_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetStateExpEpilogue( zes_ras_handle_t hRas, uint32_t* pCount, zes_ras_state_exp_t* pState , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasClearStateExpPrologue( zes_ras_handle_t hRas, zes_ras_error_category_exp_t category ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasClearStateExpEpilogue( zes_ras_handle_t hRas, zes_ras_error_category_exp_t category , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetSecurityVersionExpPrologue( zes_firmware_handle_t hFirmware, char* pVersion ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetSecurityVersionExpEpilogue( zes_firmware_handle_t hFirmware, char* pVersion , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareSetSecurityVersionExpPrologue( zes_firmware_handle_t hFirmware ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareSetSecurityVersionExpEpilogue( zes_firmware_handle_t hFirmware , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetSubDevicePropertiesExpPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_subdevice_exp_properties_t* pSubdeviceProps ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetSubDevicePropertiesExpEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_subdevice_exp_properties_t* pSubdeviceProps , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetDeviceByUuidExpPrologue( zes_driver_handle_t hDriver, zes_uuid_t uuid, zes_device_handle_t* phDevice, ze_bool_t* onSubdevice, uint32_t* subdeviceId ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetDeviceByUuidExpEpilogue( zes_driver_handle_t hDriver, zes_uuid_t uuid, zes_device_handle_t* phDevice, ze_bool_t* onSubdevice, uint32_t* subdeviceId , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumActiveVFExpPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_vf_handle_t* phVFhandle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumActiveVFExpEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_vf_handle_t* phVFhandle , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFPropertiesExpPrologue( zes_vf_handle_t hVFhandle, zes_vf_exp_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFPropertiesExpEpilogue( zes_vf_handle_t hVFhandle, zes_vf_exp_properties_t* pProperties , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFMemoryUtilizationExpPrologue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_mem_exp_t* pMemUtil ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFMemoryUtilizationExpEpilogue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_mem_exp_t* pMemUtil , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFEngineUtilizationExpPrologue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_engine_exp_t* pEngineUtil ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFEngineUtilizationExpEpilogue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_engine_exp_t* pEngineUtil , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementSetVFTelemetryModeExpPrologue( zes_vf_handle_t hVFhandle, zes_vf_info_util_exp_flags_t flags, ze_bool_t enable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementSetVFTelemetryModeExpEpilogue( zes_vf_handle_t hVFhandle, zes_vf_info_util_exp_flags_t flags, ze_bool_t enable , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementSetVFTelemetrySamplingIntervalExpPrologue( zes_vf_handle_t hVFhandle, zes_vf_info_util_exp_flags_t flag, uint64_t samplingInterval ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementSetVFTelemetrySamplingIntervalExpEpilogue( zes_vf_handle_t hVFhandle, zes_vf_info_util_exp_flags_t flag, uint64_t samplingInterval , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumEnabledVFExpPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_vf_handle_t* phVFhandle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumEnabledVFExpEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_vf_handle_t* phVFhandle , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFCapabilitiesExpPrologue( zes_vf_handle_t hVFhandle, zes_vf_exp_capabilities_t* pCapability ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFCapabilitiesExpEpilogue( zes_vf_handle_t hVFhandle, zes_vf_exp_capabilities_t* pCapability , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFMemoryUtilizationExp2Prologue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_mem_exp2_t* pMemUtil ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFMemoryUtilizationExp2Epilogue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_mem_exp2_t* pMemUtil , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFEngineUtilizationExp2Prologue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_engine_exp2_t* pEngineUtil ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFEngineUtilizationExp2Epilogue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_engine_exp2_t* pEngineUtil , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFCapabilitiesExp2Prologue( zes_vf_handle_t hVFhandle, zes_vf_exp2_capabilities_t* pCapability ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesVFManagementGetVFCapabilitiesExp2Epilogue( zes_vf_handle_t hVFhandle, zes_vf_exp2_capabilities_t* pCapability , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ~ZESValidationEntryPoints() {}
};
}