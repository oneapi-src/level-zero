/*
 * ***THIS FILE IS GENERATED. ***
 * See entry_points.h.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
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
    virtual ze_result_t zesInit( zes_init_flags_t flags ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGet( uint32_t* pCount, zes_driver_handle_t* phDrivers ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetExtensionProperties( zes_driver_handle_t hDriver, uint32_t* pCount, zes_driver_extension_properties_t* pExtensionProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverGetExtensionFunctionAddress( zes_driver_handle_t hDriver, const char* name, void** ppFunctionAddress ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGet( zes_driver_handle_t hDriver, uint32_t* pCount, zes_device_handle_t* phDevices ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetProperties( zes_device_handle_t hDevice, zes_device_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetState( zes_device_handle_t hDevice, zes_device_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceReset( zes_device_handle_t hDevice, ze_bool_t force ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetExt( zes_device_handle_t hDevice, zes_reset_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceProcessesGetState( zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetProperties( zes_device_handle_t hDevice, zes_pci_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetState( zes_device_handle_t hDevice, zes_pci_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetBars( zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDevicePciGetStats( zes_device_handle_t hDevice, zes_pci_stats_t* pStats ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceSetOverclockWaiver( zes_device_handle_t hDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetOverclockDomains( zes_device_handle_t hDevice, uint32_t* pOverclockDomains ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetOverclockControls( zes_device_handle_t hDevice, zes_overclock_domain_t domainType, uint32_t* pAvailableControls ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceResetOverclockSettings( zes_device_handle_t hDevice, ze_bool_t onShippedState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceReadOverclockState( zes_device_handle_t hDevice, zes_overclock_mode_t* pOverclockMode, ze_bool_t* pWaiverSetting, ze_bool_t* pOverclockState, zes_pending_action_t* pPendingAction, ze_bool_t* pPendingReset ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumOverclockDomains( zes_device_handle_t hDevice, uint32_t* pCount, zes_overclock_handle_t* phDomainHandle ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainProperties( zes_overclock_handle_t hDomainHandle, zes_overclock_properties_t* pDomainProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainVFProperties( zes_overclock_handle_t hDomainHandle, zes_vf_property_t* pVFProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetDomainControlProperties( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_property_t* pControlProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlCurrentValue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlPendingValue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockSetControlUserValue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double pValue, zes_pending_action_t* pPendingAction ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetControlState( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_state_t* pControlState, zes_pending_action_t* pPendingAction ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockGetVFPointValues( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, zes_vf_array_type_t VFArrayType, uint32_t PointIndex, uint32_t* PointValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesOverclockSetVFPointValues( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, uint32_t PointIndex, uint32_t PointValue ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumDiagnosticTestSuites( zes_device_handle_t hDevice, uint32_t* pCount, zes_diag_handle_t* phDiagnostics ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsGetProperties( zes_diag_handle_t hDiagnostics, zes_diag_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsGetTests( zes_diag_handle_t hDiagnostics, uint32_t* pCount, zes_diag_test_t* pTests ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDiagnosticsRunTests( zes_diag_handle_t hDiagnostics, uint32_t startIndex, uint32_t endIndex, zes_diag_result_t* pResult ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEccAvailable( zes_device_handle_t hDevice, ze_bool_t* pAvailable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEccConfigurable( zes_device_handle_t hDevice, ze_bool_t* pConfigurable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetEccState( zes_device_handle_t hDevice, zes_device_ecc_properties_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceSetEccState( zes_device_handle_t hDevice, const zes_device_ecc_desc_t* newState, zes_device_ecc_properties_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumEngineGroups( zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetProperties( zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetActivity( zes_engine_handle_t hEngine, zes_engine_stats_t* pStats ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEventRegister( zes_device_handle_t hDevice, zes_event_type_flags_t events ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverEventListen( ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDriverEventListenEx( ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFabricPorts( zes_device_handle_t hDevice, uint32_t* pCount, zes_fabric_port_handle_t* phPort ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetProperties( zes_fabric_port_handle_t hPort, zes_fabric_port_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetLinkType( zes_fabric_port_handle_t hPort, zes_fabric_link_type_t* pLinkType ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetConfig( zes_fabric_port_handle_t hPort, zes_fabric_port_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortSetConfig( zes_fabric_port_handle_t hPort, const zes_fabric_port_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetState( zes_fabric_port_handle_t hPort, zes_fabric_port_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetThroughput( zes_fabric_port_handle_t hPort, zes_fabric_port_throughput_t* pThroughput ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetFabricErrorCounters( zes_fabric_port_handle_t hPort, zes_fabric_port_error_counters_t* pErrors ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFabricPortGetMultiPortThroughput( zes_device_handle_t hDevice, uint32_t numPorts, zes_fabric_port_handle_t* phPort, zes_fabric_port_throughput_t** pThroughput ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFans( zes_device_handle_t hDevice, uint32_t* pCount, zes_fan_handle_t* phFan ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetProperties( zes_fan_handle_t hFan, zes_fan_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetConfig( zes_fan_handle_t hFan, zes_fan_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetDefaultMode( zes_fan_handle_t hFan ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetFixedSpeedMode( zes_fan_handle_t hFan, const zes_fan_speed_t* speed ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanSetSpeedTableMode( zes_fan_handle_t hFan, const zes_fan_speed_table_t* speedTable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFanGetState( zes_fan_handle_t hFan, zes_fan_speed_units_t units, int32_t* pSpeed ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFirmwares( zes_device_handle_t hDevice, uint32_t* pCount, zes_firmware_handle_t* phFirmware ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetProperties( zes_firmware_handle_t hFirmware, zes_firmware_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareFlash( zes_firmware_handle_t hFirmware, void* pImage, uint32_t size ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFirmwareGetFlashProgress( zes_firmware_handle_t hFirmware, uint32_t* pCompletionPercent ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumFrequencyDomains( zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetProperties( zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetAvailableClocks( zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetRange( zes_freq_handle_t hFrequency, zes_freq_range_t* pLimits ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencySetRange( zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetState( zes_freq_handle_t hFrequency, zes_freq_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyGetThrottleTime( zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetCapabilities( zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetFrequencyTarget( zes_freq_handle_t hFrequency, double* pCurrentOcFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetFrequencyTarget( zes_freq_handle_t hFrequency, double CurrentOcFrequency ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetVoltageTarget( zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetVoltageTarget( zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetMode( zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetMode( zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetIccMax( zes_freq_handle_t hFrequency, double* pOcIccMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetIccMax( zes_freq_handle_t hFrequency, double ocIccMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcGetTjMax( zes_freq_handle_t hFrequency, double* pOcTjMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesFrequencyOcSetTjMax( zes_freq_handle_t hFrequency, double ocTjMax ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumLeds( zes_device_handle_t hDevice, uint32_t* pCount, zes_led_handle_t* phLed ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedGetProperties( zes_led_handle_t hLed, zes_led_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedGetState( zes_led_handle_t hLed, zes_led_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedSetState( zes_led_handle_t hLed, ze_bool_t enable ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesLedSetColor( zes_led_handle_t hLed, const zes_led_color_t* pColor ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumMemoryModules( zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetProperties( zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetState( zes_mem_handle_t hMemory, zes_mem_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesMemoryGetBandwidth( zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPerformanceFactorDomains( zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorGetProperties( zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorGetConfig( zes_perf_handle_t hPerf, double* pFactor ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPerformanceFactorSetConfig( zes_perf_handle_t hPerf, double factor ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPowerDomains( zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceGetCardPowerDomain( zes_device_handle_t hDevice, zes_pwr_handle_t* phPower ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetProperties( zes_pwr_handle_t hPower, zes_power_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetEnergyCounter( zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetLimits( zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetLimits( zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetEnergyThreshold( zes_pwr_handle_t hPower, zes_energy_threshold_t* pThreshold ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetEnergyThreshold( zes_pwr_handle_t hPower, double threshold ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumPsus( zes_device_handle_t hDevice, uint32_t* pCount, zes_psu_handle_t* phPsu ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPsuGetProperties( zes_psu_handle_t hPsu, zes_psu_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPsuGetState( zes_psu_handle_t hPsu, zes_psu_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumRasErrorSets( zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetProperties( zes_ras_handle_t hRas, zes_ras_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetConfig( zes_ras_handle_t hRas, zes_ras_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasSetConfig( zes_ras_handle_t hRas, const zes_ras_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetState( zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumSchedulers( zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetProperties( zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetCurrentMode( zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetTimeoutModeProperties( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerGetTimesliceModeProperties( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetTimeoutMode( zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetTimesliceMode( zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetExclusiveMode( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesSchedulerSetComputeUnitDebugMode( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumStandbyDomains( zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbyGetProperties( zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbyGetMode( zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesStandbySetMode( zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesDeviceEnumTemperatureSensors( zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetProperties( zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetConfig( zes_temp_handle_t hTemperature, zes_temp_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureSetConfig( zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesTemperatureGetState( zes_temp_handle_t hTemperature, double* pTemperature ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerGetLimitsExt( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesPowerSetLimitsExt( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesEngineGetActivityExt( zes_engine_handle_t hEngine, uint32_t* pCount, zes_engine_stats_t* pStats ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasGetStateExp( zes_ras_handle_t hRas, uint32_t* pCount, zes_ras_state_exp_t* pState ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zesRasClearStateExp( zes_ras_handle_t hRas, zes_ras_error_category_exp_t category ) {return ZE_RESULT_SUCCESS;}
    virtual ~ZESValidationEntryPoints() {}
};
}