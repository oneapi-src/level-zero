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
                        ze_result_t zesDriverGetExtensionPropertiesEpilogue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_driver_extension_properties_t* pExtensionProperties ) override;
        ze_result_t zesDriverGetExtensionFunctionAddressEpilogue( zes_driver_handle_t hDriver, const char* name, void** ppFunctionAddress ) override;
        ze_result_t zesDeviceGetEpilogue( zes_driver_handle_t hDriver, uint32_t* pCount, zes_device_handle_t* phDevices ) override;
        ze_result_t zesDeviceGetPropertiesEpilogue( zes_device_handle_t hDevice, zes_device_properties_t* pProperties ) override;
        ze_result_t zesDeviceGetStateEpilogue( zes_device_handle_t hDevice, zes_device_state_t* pState ) override;
        ze_result_t zesDeviceResetEpilogue( zes_device_handle_t hDevice, ze_bool_t force ) override;
        ze_result_t zesDeviceResetExtEpilogue( zes_device_handle_t hDevice, zes_reset_properties_t* pProperties ) override;
        ze_result_t zesDeviceProcessesGetStateEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses ) override;
        ze_result_t zesDevicePciGetPropertiesEpilogue( zes_device_handle_t hDevice, zes_pci_properties_t* pProperties ) override;
        ze_result_t zesDevicePciGetStateEpilogue( zes_device_handle_t hDevice, zes_pci_state_t* pState ) override;
        ze_result_t zesDevicePciGetBarsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties ) override;
        ze_result_t zesDevicePciGetStatsEpilogue( zes_device_handle_t hDevice, zes_pci_stats_t* pStats ) override;
        ze_result_t zesDeviceSetOverclockWaiverEpilogue( zes_device_handle_t hDevice ) override;
        ze_result_t zesDeviceGetOverclockDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pOverclockDomains ) override;
        ze_result_t zesDeviceGetOverclockControlsEpilogue( zes_device_handle_t hDevice, zes_overclock_domain_t domainType, uint32_t* pAvailableControls ) override;
        ze_result_t zesDeviceResetOverclockSettingsEpilogue( zes_device_handle_t hDevice, ze_bool_t onShippedState ) override;
        ze_result_t zesDeviceReadOverclockStateEpilogue( zes_device_handle_t hDevice, zes_overclock_mode_t* pOverclockMode, ze_bool_t* pWaiverSetting, ze_bool_t* pOverclockState, zes_pending_action_t* pPendingAction, ze_bool_t* pPendingReset ) override;
        ze_result_t zesDeviceEnumOverclockDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_overclock_handle_t* phDomainHandle ) override;
        ze_result_t zesOverclockGetDomainPropertiesEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_properties_t* pDomainProperties ) override;
        ze_result_t zesOverclockGetDomainVFPropertiesEpilogue( zes_overclock_handle_t hDomainHandle, zes_vf_property_t* pVFProperties ) override;
        ze_result_t zesOverclockGetDomainControlPropertiesEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_property_t* pControlProperties ) override;
        ze_result_t zesOverclockGetControlCurrentValueEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) override;
        ze_result_t zesOverclockGetControlPendingValueEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double* pValue ) override;
        ze_result_t zesOverclockSetControlUserValueEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, double pValue, zes_pending_action_t* pPendingAction ) override;
        ze_result_t zesOverclockGetControlStateEpilogue( zes_overclock_handle_t hDomainHandle, zes_overclock_control_t DomainControl, zes_control_state_t* pControlState, zes_pending_action_t* pPendingAction ) override;
        ze_result_t zesOverclockGetVFPointValuesEpilogue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, zes_vf_array_type_t VFArrayType, uint32_t PointIndex, uint32_t* PointValue ) override;
        ze_result_t zesOverclockSetVFPointValuesEpilogue( zes_overclock_handle_t hDomainHandle, zes_vf_type_t VFType, uint32_t PointIndex, uint32_t PointValue ) override;
        ze_result_t zesDeviceEnumDiagnosticTestSuitesEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_diag_handle_t* phDiagnostics ) override;
        ze_result_t zesDiagnosticsGetPropertiesEpilogue( zes_diag_handle_t hDiagnostics, zes_diag_properties_t* pProperties ) override;
        ze_result_t zesDiagnosticsGetTestsEpilogue( zes_diag_handle_t hDiagnostics, uint32_t* pCount, zes_diag_test_t* pTests ) override;
        ze_result_t zesDiagnosticsRunTestsEpilogue( zes_diag_handle_t hDiagnostics, uint32_t startIndex, uint32_t endIndex, zes_diag_result_t* pResult ) override;
        ze_result_t zesDeviceEccAvailableEpilogue( zes_device_handle_t hDevice, ze_bool_t* pAvailable ) override;
        ze_result_t zesDeviceEccConfigurableEpilogue( zes_device_handle_t hDevice, ze_bool_t* pConfigurable ) override;
        ze_result_t zesDeviceGetEccStateEpilogue( zes_device_handle_t hDevice, zes_device_ecc_properties_t* pState ) override;
        ze_result_t zesDeviceSetEccStateEpilogue( zes_device_handle_t hDevice, const zes_device_ecc_desc_t* newState, zes_device_ecc_properties_t* pState ) override;
        ze_result_t zesDeviceEnumEngineGroupsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine ) override;
        ze_result_t zesEngineGetPropertiesEpilogue( zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties ) override;
        ze_result_t zesEngineGetActivityEpilogue( zes_engine_handle_t hEngine, zes_engine_stats_t* pStats ) override;
        ze_result_t zesDeviceEventRegisterEpilogue( zes_device_handle_t hDevice, zes_event_type_flags_t events ) override;
        ze_result_t zesDriverEventListenEpilogue( ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) override;
        ze_result_t zesDriverEventListenExEpilogue( ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents ) override;
        ze_result_t zesDeviceEnumFabricPortsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fabric_port_handle_t* phPort ) override;
        ze_result_t zesFabricPortGetPropertiesEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_properties_t* pProperties ) override;
        ze_result_t zesFabricPortGetLinkTypeEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_link_type_t* pLinkType ) override;
        ze_result_t zesFabricPortGetConfigEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_config_t* pConfig ) override;
        ze_result_t zesFabricPortSetConfigEpilogue( zes_fabric_port_handle_t hPort, const zes_fabric_port_config_t* pConfig ) override;
        ze_result_t zesFabricPortGetStateEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_state_t* pState ) override;
        ze_result_t zesFabricPortGetThroughputEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_throughput_t* pThroughput ) override;
        ze_result_t zesFabricPortGetFabricErrorCountersEpilogue( zes_fabric_port_handle_t hPort, zes_fabric_port_error_counters_t* pErrors ) override;
        ze_result_t zesFabricPortGetMultiPortThroughputEpilogue( zes_device_handle_t hDevice, uint32_t numPorts, zes_fabric_port_handle_t* phPort, zes_fabric_port_throughput_t** pThroughput ) override;
        ze_result_t zesDeviceEnumFansEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_fan_handle_t* phFan ) override;
        ze_result_t zesFanGetPropertiesEpilogue( zes_fan_handle_t hFan, zes_fan_properties_t* pProperties ) override;
        ze_result_t zesFanGetConfigEpilogue( zes_fan_handle_t hFan, zes_fan_config_t* pConfig ) override;
        ze_result_t zesFanSetDefaultModeEpilogue( zes_fan_handle_t hFan ) override;
        ze_result_t zesFanSetFixedSpeedModeEpilogue( zes_fan_handle_t hFan, const zes_fan_speed_t* speed ) override;
        ze_result_t zesFanSetSpeedTableModeEpilogue( zes_fan_handle_t hFan, const zes_fan_speed_table_t* speedTable ) override;
        ze_result_t zesFanGetStateEpilogue( zes_fan_handle_t hFan, zes_fan_speed_units_t units, int32_t* pSpeed ) override;
        ze_result_t zesDeviceEnumFirmwaresEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_firmware_handle_t* phFirmware ) override;
        ze_result_t zesFirmwareGetPropertiesEpilogue( zes_firmware_handle_t hFirmware, zes_firmware_properties_t* pProperties ) override;
        ze_result_t zesFirmwareFlashEpilogue( zes_firmware_handle_t hFirmware, void* pImage, uint32_t size ) override;
        ze_result_t zesFirmwareGetFlashProgressEpilogue( zes_firmware_handle_t hFirmware, uint32_t* pCompletionPercent ) override;
        ze_result_t zesFirmwareGetConsoleLogsEpilogue( zes_firmware_handle_t hFirmware, size_t* pSize, char* pFirmwareLog ) override;
        ze_result_t zesDeviceEnumFrequencyDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency ) override;
        ze_result_t zesFrequencyGetPropertiesEpilogue( zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties ) override;
        ze_result_t zesFrequencyGetAvailableClocksEpilogue( zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency ) override;
        ze_result_t zesFrequencyGetRangeEpilogue( zes_freq_handle_t hFrequency, zes_freq_range_t* pLimits ) override;
        ze_result_t zesFrequencySetRangeEpilogue( zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits ) override;
        ze_result_t zesFrequencyGetStateEpilogue( zes_freq_handle_t hFrequency, zes_freq_state_t* pState ) override;
        ze_result_t zesFrequencyGetThrottleTimeEpilogue( zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime ) override;
        ze_result_t zesFrequencyOcGetCapabilitiesEpilogue( zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities ) override;
        ze_result_t zesFrequencyOcGetFrequencyTargetEpilogue( zes_freq_handle_t hFrequency, double* pCurrentOcFrequency ) override;
        ze_result_t zesFrequencyOcSetFrequencyTargetEpilogue( zes_freq_handle_t hFrequency, double CurrentOcFrequency ) override;
        ze_result_t zesFrequencyOcGetVoltageTargetEpilogue( zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset ) override;
        ze_result_t zesFrequencyOcSetVoltageTargetEpilogue( zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset ) override;
        ze_result_t zesFrequencyOcSetModeEpilogue( zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode ) override;
        ze_result_t zesFrequencyOcGetModeEpilogue( zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode ) override;
        ze_result_t zesFrequencyOcGetIccMaxEpilogue( zes_freq_handle_t hFrequency, double* pOcIccMax ) override;
        ze_result_t zesFrequencyOcSetIccMaxEpilogue( zes_freq_handle_t hFrequency, double ocIccMax ) override;
        ze_result_t zesFrequencyOcGetTjMaxEpilogue( zes_freq_handle_t hFrequency, double* pOcTjMax ) override;
        ze_result_t zesFrequencyOcSetTjMaxEpilogue( zes_freq_handle_t hFrequency, double ocTjMax ) override;
        ze_result_t zesDeviceEnumLedsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_led_handle_t* phLed ) override;
        ze_result_t zesLedGetPropertiesEpilogue( zes_led_handle_t hLed, zes_led_properties_t* pProperties ) override;
        ze_result_t zesLedGetStateEpilogue( zes_led_handle_t hLed, zes_led_state_t* pState ) override;
        ze_result_t zesLedSetStateEpilogue( zes_led_handle_t hLed, ze_bool_t enable ) override;
        ze_result_t zesLedSetColorEpilogue( zes_led_handle_t hLed, const zes_led_color_t* pColor ) override;
        ze_result_t zesDeviceEnumMemoryModulesEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory ) override;
        ze_result_t zesMemoryGetPropertiesEpilogue( zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties ) override;
        ze_result_t zesMemoryGetStateEpilogue( zes_mem_handle_t hMemory, zes_mem_state_t* pState ) override;
        ze_result_t zesMemoryGetBandwidthEpilogue( zes_mem_handle_t hMemory, zes_mem_bandwidth_t* pBandwidth ) override;
        ze_result_t zesDeviceEnumPerformanceFactorDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf ) override;
        ze_result_t zesPerformanceFactorGetPropertiesEpilogue( zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties ) override;
        ze_result_t zesPerformanceFactorGetConfigEpilogue( zes_perf_handle_t hPerf, double* pFactor ) override;
        ze_result_t zesPerformanceFactorSetConfigEpilogue( zes_perf_handle_t hPerf, double factor ) override;
        ze_result_t zesDeviceEnumPowerDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower ) override;
        ze_result_t zesDeviceGetCardPowerDomainEpilogue( zes_device_handle_t hDevice, zes_pwr_handle_t* phPower ) override;
        ze_result_t zesPowerGetPropertiesEpilogue( zes_pwr_handle_t hPower, zes_power_properties_t* pProperties ) override;
        ze_result_t zesPowerGetEnergyCounterEpilogue( zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy ) override;
        ze_result_t zesPowerGetLimitsEpilogue( zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak ) override;
        ze_result_t zesPowerSetLimitsEpilogue( zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak ) override;
        ze_result_t zesPowerGetEnergyThresholdEpilogue( zes_pwr_handle_t hPower, zes_energy_threshold_t* pThreshold ) override;
        ze_result_t zesPowerSetEnergyThresholdEpilogue( zes_pwr_handle_t hPower, double threshold ) override;
        ze_result_t zesDeviceEnumPsusEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_psu_handle_t* phPsu ) override;
        ze_result_t zesPsuGetPropertiesEpilogue( zes_psu_handle_t hPsu, zes_psu_properties_t* pProperties ) override;
        ze_result_t zesPsuGetStateEpilogue( zes_psu_handle_t hPsu, zes_psu_state_t* pState ) override;
        ze_result_t zesDeviceEnumRasErrorSetsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas ) override;
        ze_result_t zesRasGetPropertiesEpilogue( zes_ras_handle_t hRas, zes_ras_properties_t* pProperties ) override;
        ze_result_t zesRasGetConfigEpilogue( zes_ras_handle_t hRas, zes_ras_config_t* pConfig ) override;
        ze_result_t zesRasSetConfigEpilogue( zes_ras_handle_t hRas, const zes_ras_config_t* pConfig ) override;
        ze_result_t zesRasGetStateEpilogue( zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState ) override;
        ze_result_t zesDeviceEnumSchedulersEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler ) override;
        ze_result_t zesSchedulerGetPropertiesEpilogue( zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties ) override;
        ze_result_t zesSchedulerGetCurrentModeEpilogue( zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode ) override;
        ze_result_t zesSchedulerGetTimeoutModePropertiesEpilogue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig ) override;
        ze_result_t zesSchedulerGetTimesliceModePropertiesEpilogue( zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig ) override;
        ze_result_t zesSchedulerSetTimeoutModeEpilogue( zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload ) override;
        ze_result_t zesSchedulerSetTimesliceModeEpilogue( zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload ) override;
        ze_result_t zesSchedulerSetExclusiveModeEpilogue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) override;
        ze_result_t zesSchedulerSetComputeUnitDebugModeEpilogue( zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload ) override;
        ze_result_t zesDeviceEnumStandbyDomainsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby ) override;
        ze_result_t zesStandbyGetPropertiesEpilogue( zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties ) override;
        ze_result_t zesStandbyGetModeEpilogue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode ) override;
        ze_result_t zesStandbySetModeEpilogue( zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode ) override;
        ze_result_t zesDeviceEnumTemperatureSensorsEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature ) override;
        ze_result_t zesTemperatureGetPropertiesEpilogue( zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties ) override;
        ze_result_t zesTemperatureGetConfigEpilogue( zes_temp_handle_t hTemperature, zes_temp_config_t* pConfig ) override;
        ze_result_t zesTemperatureSetConfigEpilogue( zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig ) override;
        ze_result_t zesTemperatureGetStateEpilogue( zes_temp_handle_t hTemperature, double* pTemperature ) override;
        ze_result_t zesPowerGetLimitsExtEpilogue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) override;
        ze_result_t zesPowerSetLimitsExtEpilogue( zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained ) override;
        ze_result_t zesEngineGetActivityExtEpilogue( zes_engine_handle_t hEngine, uint32_t* pCount, zes_engine_stats_t* pStats ) override;
        ze_result_t zesRasGetStateExpEpilogue( zes_ras_handle_t hRas, uint32_t* pCount, zes_ras_state_exp_t* pState ) override;
        ze_result_t zesRasClearStateExpEpilogue( zes_ras_handle_t hRas, zes_ras_error_category_exp_t category ) override;
        ze_result_t zesFirmwareGetSecurityVersionExpEpilogue( zes_firmware_handle_t hFirmware, char* pVersion ) override;
        ze_result_t zesFirmwareSetSecurityVersionExpEpilogue( zes_firmware_handle_t hFirmware ) override;
        ze_result_t zesDeviceGetSubDevicePropertiesExpEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_subdevice_exp_properties_t* pSubdeviceProps ) override;
        ze_result_t zesDriverGetDeviceByUuidExpEpilogue( zes_driver_handle_t hDriver, zes_uuid_t uuid, zes_device_handle_t* phDevice, ze_bool_t* onSubdevice, uint32_t* subdeviceId ) override;
        ze_result_t zesDeviceEnumActiveVFExpEpilogue( zes_device_handle_t hDevice, uint32_t* pCount, zes_vf_handle_t* phVFhandle ) override;
        ze_result_t zesVFManagementGetVFPropertiesExpEpilogue( zes_vf_handle_t hVFhandle, zes_vf_exp_properties_t* pProperties ) override;
        ze_result_t zesVFManagementGetVFMemoryUtilizationExpEpilogue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_mem_exp_t* pMemUtil ) override;
        ze_result_t zesVFManagementGetVFEngineUtilizationExpEpilogue( zes_vf_handle_t hVFhandle, uint32_t* pCount, zes_vf_util_engine_exp_t* pEngineUtil ) override;
        ze_result_t zesVFManagementSetVFTelemetryModeExpEpilogue( zes_vf_handle_t hVFhandle, zes_vf_info_util_exp_flags_t flags, ze_bool_t enable ) override;
        ze_result_t zesVFManagementSetVFTelemetrySamplingIntervalExpEpilogue( zes_vf_handle_t hVFhandle, zes_vf_info_util_exp_flags_t flag, uint64_t samplingInterval ) override;
    };

}
