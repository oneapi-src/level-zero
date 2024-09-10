/*
 * ***THIS FILE IS GENERATED. ***
 * See handle_lifetime.h.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_handle_lifetime.h
 *
 */

#pragma once
#include "zes_entry_points.h"


namespace validation_layer
{

    class ZESHandleLifetimeValidation : public ZESValidationEntryPoints {
    public:
                        ze_result_t zesDriverGetExtensionPropertiesPrologue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_driver_extension_properties_t* pExtensionProperties ) override;
        ze_result_t zesDriverGetExtensionFunctionAddressPrologue( zes_driver_handle_t hDriver, const char* name, void** ppFunctionAddress ) override;
        ze_result_t zesDeviceGetPrologue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_device_handle_t* phDevices ) override;
        ze_result_t zesDeviceGetPropertiesPrologue( zes_device_handle_t hDevice, zes_device_properties_t* pProperties ) override;
        ze_result_t zesDeviceGetStatePrologue( zes_device_handle_t hDevice, zes_device_state_t* pState ) override;
        ze_result_t zesDeviceResetPrologue( zes_device_handle_t hDevice, ze_bool_t force ) override;
        ze_result_t zesDeviceResetExtPrologue( zes_device_handle_t hDevice, zes_reset_properties_t* pProperties ) override;
        ze_result_t zesDeviceProcessesGetStatePrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses ) override;
        ze_result_t zesDevicePciGetPropertiesPrologue( zes_device_handle_t hDevice, zes_pci_properties_t* pProperties ) override;
        ze_result_t zesDevicePciGetStatePrologue( zes_device_handle_t hDevice, zes_pci_state_t* pState ) override;
        ze_result_t zesDevicePciGetBarsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties ) override;
        ze_result_t zesDevicePciGetStatsPrologue( zes_device_handle_t hDevice, zes_pci_stats_t* pStats ) override;
        ze_result_t zesDeviceSetOverclockWaiverPrologue( zes_device_handle_t hDevice ) override;
        ze_result_t zesDeviceGetOverclockDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pOverclockDomains ) override;
        ze_result_t zesDeviceGetOverclockControlsPrologue( zes_device_handle_t hDevice, zes_overclock_domain_t domainType, uint32_t* pAvailableControls ) override;
        ze_result_t zesDeviceResetOverclockSettingsPrologue( zes_device_handle_t hDevice, ze_bool_t onShippedState ) override;
        ze_result_t zesDeviceReadOverclockStatePrologue( zes_device_handle_t hDevice, zes_overclock_mode_t* pOverclockMode, ze_bool_t* pWaiverSetting, ze_bool_t* pOverclockState, zes_pending_action_t* pPendingAction, ze_bool_t* pPendingReset ) override;
        ze_result_t zesDeviceEnumOverclockDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_overclock_handle_t* phDomainHandle ) override;
        ze_result_t zesOverclockGetDomainPropertiesPrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_properties_t* pDomainProperties ) override;
        ze_result_t zesOverclockGetDomainVFPropertiesPrologue( zes_overclock_handle_t hDomainHandle, zes_vf_property_t* pVFProperties ) override;
        ze_result_t zesOverclockGetDomainControlPropertiesPrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_property_t* pControlProperties ) override;
        ze_result_t zesOverclockGetControlCurrentValuePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) override;
        ze_result_t zesOverclockGetControlPendingValuePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) override;
        ze_result_t zesOverclockSetControlUserValuePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double pValue, zes_pending_action_t* pPendingAction ) override;
        ze_result_t zesOverclockGetControlStatePrologue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_state_t* pControlState, zes_pending_action_t* pPendingAction ) override;
        ze_result_t zesOverclockGetVFPointValuesPrologue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, zes_vf_array_type_t VFArrayType, uint32_t PointIndex, uint32_t* PointValue ) override;
        ze_result_t zesOverclockSetVFPointValuesPrologue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, uint32_t PointIndex, uint32_t PointValue ) override;
        ze_result_t zesDeviceEnumDiagnosticTestSuitesPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_diag_handle_t* phDiagnostics ) override;
        ze_result_t zesDiagnosticsGetPropertiesPrologue( zes_diag_handle_t hDiagnostics, zes_diag_properties_t* pProperties ) override;
        ze_result_t zesDiagnosticsGetTestsPrologue( zes_diag_handle_t hDiagnostics, uint32_t* pCount, zes_diag_test_t* pTests ) override;
        ze_result_t zesDiagnosticsRunTestsPrologue( zes_diag_handle_t hDiagnostics, uint32_t startIndex, uint32_t endIndex, zes_diag_result_t* pResult ) override;
        ze_result_t zesDeviceEccAvailablePrologue( zes_device_handle_t hDevice, ze_bool_t* pAvailable ) override;
        ze_result_t zesDeviceEccConfigurablePrologue( zes_device_handle_t hDevice, ze_bool_t* pConfigurable ) override;
        ze_result_t zesDeviceGetEccStatePrologue( zes_device_handle_t hDevice, zes_device_ecc_properties_t* pState ) override;
        ze_result_t zesDeviceSetEccStatePrologue( zes_device_handle_t hDevice, const zes_device_ecc_desc_t* newState, zes_device_ecc_properties_t* pState ) override;
        ze_result_t zesDeviceEnumEngineGroupsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine ) override;
        ze_result_t zesEngineGetPropertiesPrologue( zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties ) override;
        ze_result_t zesEngineGetActivityPrologue( zes_engine_handle_t hEngine, zes_engine_stats_t* pStats ) override;
        ze_result_t zesDeviceEventRegisterPrologue( zes_device_handle_t hDevice, zes_event_type_flags_t events ) override;
        ze_result_t zesDriverEventListenPrologue( ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) override;
        ze_result_t zesDriverEventListenExPrologue( ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) override;
        ze_result_t zesDeviceEnumFabricPortsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fabric_port_handle_t* phPort ) override;
        ze_result_t zesFabricPortGetPropertiesPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_properties_t* pProperties ) override;
        ze_result_t zesFabricPortGetLinkTypePrologue( zes_fabric_port_handle_t hPort, zes_fabric_link_type_t* pLinkType ) override;
        ze_result_t zesFabricPortGetConfigPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_config_t* pConfig ) override;
        ze_result_t zesFabricPortSetConfigPrologue( zes_fabric_port_handle_t hPort, const zes_fabric_port_config_t* pConfig ) override;
        ze_result_t zesFabricPortGetStatePrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_state_t* pState ) override;
        ze_result_t zesFabricPortGetThroughputPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_throughput_t* pThroughput ) override;
        ze_result_t zesFabricPortGetFabricErrorCountersPrologue( zes_fabric_port_handle_t hPort, zes_fabric_port_error_counters_t* pErrors ) override;
        ze_result_t zesFabricPortGetMultiPortThroughputPrologue( zes_device_handle_t hDevice, uint32_t numPorts, zes_fabric_port_handle_t* phPort, zes_fabric_port_throughput_t** pThroughput ) override;
        ze_result_t zesDeviceEnumFansPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fan_handle_t* phFan ) override;
        ze_result_t zesFanGetPropertiesPrologue( zes_fan_handle_t hFan, zes_fan_properties_t* pProperties ) override;
        ze_result_t zesFanGetConfigPrologue( zes_fan_handle_t hFan, zes_fan_config_t* pConfig ) override;
        ze_result_t zesFanSetDefaultModePrologue( zes_fan_handle_t hFan ) override;
        ze_result_t zesFanSetFixedSpeedModePrologue( zes_fan_handle_t hFan, const zes_fan_speed_t* speed ) override;
        ze_result_t zesFanSetSpeedTableModePrologue( zes_fan_handle_t hFan, const zes_fan_speed_table_t* speedTable ) override;
        ze_result_t zesFanGetStatePrologue( zes_fan_handle_t hFan, zes_fan_speed_units_t units, int32_t* pSpeed ) override;
        ze_result_t zesDeviceEnumFirmwaresPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_firmware_handle_t* phFirmware ) override;
        ze_result_t zesFirmwareGetPropertiesPrologue( zes_firmware_handle_t hFirmware, zes_firmware_properties_t* pProperties ) override;
        ze_result_t zesFirmwareFlashPrologue( zes_firmware_handle_t hFirmware, void* pImage, uint32_t size ) override;
        ze_result_t zesFirmwareGetFlashProgressPrologue( zes_firmware_handle_t hFirmware, uint32_t* pCompletionPercent ) override;
        ze_result_t zesFirmwareGetConsoleLogsPrologue( zes_firmware_handle_t hFirmware, size_t* pSize, char* pFirmwareLog ) override;
        ze_result_t zesDeviceEnumFrequencyDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency ) override;
        ze_result_t zesFrequencyGetPropertiesPrologue( zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties ) override;
        ze_result_t zesFrequencyGetAvailableClocksPrologue( zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency ) override;
        ze_result_t zesFrequencyGetRangePrologue( zes_freq_handle_t hFrequency, zes_freq_range_t* pLimits ) override;
        ze_result_t zesFrequencySetRangePrologue( zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits ) override;
        ze_result_t zesFrequencyGetStatePrologue( zes_freq_handle_t hFrequency, zes_freq_state_t* pState ) override;
        ze_result_t zesFrequencyGetThrottleTimePrologue( zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime ) override;
        ze_result_t zesFrequencyOcGetCapabilitiesPrologue( zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities ) override;
        ze_result_t zesFrequencyOcGetFrequencyTargetPrologue( zes_freq_handle_t hFrequency, double* pCurrentOcFrequency ) override;
        ze_result_t zesFrequencyOcSetFrequencyTargetPrologue( zes_freq_handle_t hFrequency, double CurrentOcFrequency ) override;
        ze_result_t zesFrequencyOcGetVoltageTargetPrologue( zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset ) override;
        ze_result_t zesFrequencyOcSetVoltageTargetPrologue( zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset ) override;
        ze_result_t zesFrequencyOcSetModePrologue( zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode ) override;
        ze_result_t zesFrequencyOcGetModePrologue( zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode ) override;
        ze_result_t zesFrequencyOcGetIccMaxPrologue( zes_freq_handle_t hFrequency, double* pOcIccMax ) override;
        ze_result_t zesFrequencyOcSetIccMaxPrologue( zes_freq_handle_t hFrequency, double ocIccMax ) override;
        ze_result_t zesFrequencyOcGetTjMaxPrologue( zes_freq_handle_t hFrequency, double* pOcTjMax ) override;
        ze_result_t zesFrequencyOcSetTjMaxPrologue( zes_freq_handle_t hFrequency, double ocTjMax ) override;
        ze_result_t zesDeviceEnumLedsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_led_handle_t* phLed ) override;
        ze_result_t zesLedGetPropertiesPrologue( zes_led_handle_t hLed, zes_led_properties_t* pProperties ) override;
        ze_result_t zesLedGetStatePrologue( zes_led_handle_t hLed, zes_led_state_t* pState ) override;
        ze_result_t zesLedSetStatePrologue( zes_led_handle_t hLed, ze_bool_t enable ) override;
        ze_result_t zesLedSetColorPrologue( zes_led_handle_t hLed, const zes_led_color_t* pColor ) override;
        ze_result_t zesDeviceEnumMemoryModulesPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory ) override;
        ze_result_t zesMemoryGetPropertiesPrologue( zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties ) override;
        ze_result_t zesMemoryGetStatePrologue( zes_mem_handle_t hMemory, zes_mem_state_t* pState ) override;
        ze_result_t zesMemoryGetBandwidthPrologue( zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth ) override;
        ze_result_t zesDeviceEnumPerformanceFactorDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf ) override;
        ze_result_t zesPerformanceFactorGetPropertiesPrologue( zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties ) override;
        ze_result_t zesPerformanceFactorGetConfigPrologue( zes_perf_handle_t hPerf, double* pFactor ) override;
        ze_result_t zesPerformanceFactorSetConfigPrologue( zes_perf_handle_t hPerf, double factor ) override;
        ze_result_t zesDeviceEnumPowerDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower ) override;
        ze_result_t zesDeviceGetCardPowerDomainPrologue( zes_device_handle_t hDevice, zes_pwr_handle_t* phPower ) override;
        ze_result_t zesPowerGetPropertiesPrologue( zes_pwr_handle_t hPower, zes_power_properties_t* pProperties ) override;
        ze_result_t zesPowerGetEnergyCounterPrologue( zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy ) override;
        ze_result_t zesPowerGetLimitsPrologue( zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak ) override;
        ze_result_t zesPowerSetLimitsPrologue( zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak ) override;
        ze_result_t zesPowerGetEnergyThresholdPrologue( zes_pwr_handle_t hPower, zes_energy_threshold_t* pThreshold ) override;
        ze_result_t zesPowerSetEnergyThresholdPrologue( zes_pwr_handle_t hPower, double threshold ) override;
        ze_result_t zesDeviceEnumPsusPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_psu_handle_t* phPsu ) override;
        ze_result_t zesPsuGetPropertiesPrologue( zes_psu_handle_t hPsu, zes_psu_properties_t* pProperties ) override;
        ze_result_t zesPsuGetStatePrologue( zes_psu_handle_t hPsu, zes_psu_state_t* pState ) override;
        ze_result_t zesDeviceEnumRasErrorSetsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas ) override;
        ze_result_t zesRasGetPropertiesPrologue( zes_ras_handle_t hRas, zes_ras_properties_t* pProperties ) override;
        ze_result_t zesRasGetConfigPrologue( zes_ras_handle_t hRas, zes_ras_config_t* pConfig ) override;
        ze_result_t zesRasSetConfigPrologue( zes_ras_handle_t hRas, const zes_ras_config_t* pConfig ) override;
        ze_result_t zesRasGetStatePrologue( zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState ) override;
        ze_result_t zesDeviceEnumSchedulersPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler ) override;
        ze_result_t zesSchedulerGetPropertiesPrologue( zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties ) override;
        ze_result_t zesSchedulerGetCurrentModePrologue( zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode ) override;
        ze_result_t zesSchedulerGetTimeoutModePropertiesPrologue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig ) override;
        ze_result_t zesSchedulerGetTimesliceModePropertiesPrologue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig ) override;
        ze_result_t zesSchedulerSetTimeoutModePrologue( zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload ) override;
        ze_result_t zesSchedulerSetTimesliceModePrologue( zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload ) override;
        ze_result_t zesSchedulerSetExclusiveModePrologue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) override;
        ze_result_t zesSchedulerSetComputeUnitDebugModePrologue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) override;
        ze_result_t zesDeviceEnumStandbyDomainsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby ) override;
        ze_result_t zesStandbyGetPropertiesPrologue( zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties ) override;
        ze_result_t zesStandbyGetModePrologue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode ) override;
        ze_result_t zesStandbySetModePrologue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode ) override;
        ze_result_t zesDeviceEnumTemperatureSensorsPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature ) override;
        ze_result_t zesTemperatureGetPropertiesPrologue( zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties ) override;
        ze_result_t zesTemperatureGetConfigPrologue( zes_temp_handle_t hTemperature, zes_temp_config_t* pConfig ) override;
        ze_result_t zesTemperatureSetConfigPrologue( zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig ) override;
        ze_result_t zesTemperatureGetStatePrologue( zes_temp_handle_t hTemperature, double* pTemperature ) override;
        ze_result_t zesPowerGetLimitsExtPrologue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) override;
        ze_result_t zesPowerSetLimitsExtPrologue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) override;
        ze_result_t zesEngineGetActivityExtPrologue( zes_engine_handle_t hEngine, uint32_t* pCount, zes_engine_stats_t* pStats ) override;
        ze_result_t zesRasGetStateExpPrologue( zes_ras_handle_t hRas, uint32_t* pCount, zes_ras_state_exp_t* pState ) override;
        ze_result_t zesRasClearStateExpPrologue( zes_ras_handle_t hRas, zes_ras_error_category_exp_t category ) override;
        ze_result_t zesFirmwareGetSecurityVersionExpPrologue( zes_firmware_handle_t hFirmware, char* pVersion ) override;
        ze_result_t zesFirmwareSetSecurityVersionExpPrologue( zes_firmware_handle_t hFirmware ) override;
        ze_result_t zesDeviceGetSubDevicePropertiesExpPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_subdevice_exp_properties_t* pSubdeviceProps ) override;
        ze_result_t zesDriverGetDeviceByUuidExpPrologue( zes_driver_handle_t hDriver, zes_uuid_t uuid, zes_device_handle_t* phDevice, ze_bool_t* onSubdevice, uint32_t* subdeviceId ) override;
        ze_result_t zesDeviceEnumEnabledVFExpPrologue( zes_device_handle_t hDevice, uint32_t* pCount, zes_vf_handle_t* phVFhandle ) override;
        ze_result_t zesVFManagementGetVFCapabilitiesExpPrologue( zes_vf_handle_t hVFhandle, zes_vf_exp_capabilities_t* pCapability ) override;
        ze_result_t zesVFManagementGetVFMemoryUtilizationExpPrologue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_mem_exp_t* pMemUtil ) override;
        ze_result_t zesVFManagementGetVFEngineUtilizationExpPrologue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_engine_exp_t* pEngineUtil ) override;
    };

}
