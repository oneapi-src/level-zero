/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_ddi.h
 *
 */
#ifndef _ZET_DDI_H
#define _ZET_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "zet_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetInit 
typedef ze_result_t (__zecall *zet_pfnInit_t)(
    ze_init_flag_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global functions pointers
typedef struct _zet_global_dditable_t
{
    zet_pfnInit_t                                               pfnInit;
} zet_global_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetGlobalProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetGlobalProcAddrTable_t)(
    ze_api_version_t,
    zet_global_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDeviceActivateMetricGroups 
typedef ze_result_t (__zecall *zet_pfnDeviceActivateMetricGroups_t)(
    zet_device_handle_t,
    uint32_t,
    zet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _zet_device_dditable_t
{
    zet_pfnDeviceActivateMetricGroups_t                         pfnActivateMetricGroups;
} zet_device_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetDeviceProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetDeviceProcAddrTable_t)(
    ze_api_version_t,
    zet_device_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricTracerMarker 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricTracerMarker_t)(
    zet_command_list_handle_t,
    zet_metric_tracer_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricQueryBegin 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricQueryBegin_t)(
    zet_command_list_handle_t,
    zet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricQueryEnd 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricQueryEnd_t)(
    zet_command_list_handle_t,
    zet_metric_query_handle_t,
    ze_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetCommandListAppendMetricMemoryBarrier 
typedef ze_result_t (__zecall *zet_pfnCommandListAppendMetricMemoryBarrier_t)(
    zet_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _zet_command_list_dditable_t
{
    zet_pfnCommandListAppendMetricTracerMarker_t                pfnAppendMetricTracerMarker;
    zet_pfnCommandListAppendMetricQueryBegin_t                  pfnAppendMetricQueryBegin;
    zet_pfnCommandListAppendMetricQueryEnd_t                    pfnAppendMetricQueryEnd;
    zet_pfnCommandListAppendMetricMemoryBarrier_t               pfnAppendMetricMemoryBarrier;
} zet_command_list_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetCommandListProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetCommandListProcAddrTable_t)(
    ze_api_version_t,
    zet_command_list_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanGet 
typedef ze_result_t (__zecall *zet_pfnSysmanGet_t)(
    zet_device_handle_t,
    zet_sysman_version_t,
    zet_sysman_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanDeviceGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanDeviceGetProperties_t)(
    zet_sysman_handle_t,
    zet_sysman_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerGetSupportedModes 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerGetSupportedModes_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sched_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerGetCurrentMode 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerGetCurrentMode_t)(
    zet_sysman_handle_t,
    zet_sched_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerGetTimeoutModeProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerGetTimeoutModeProperties_t)(
    zet_sysman_handle_t,
    ze_bool_t,
    zet_sched_timeout_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerGetTimesliceModeProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerGetTimesliceModeProperties_t)(
    zet_sysman_handle_t,
    ze_bool_t,
    zet_sched_timeslice_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerSetTimeoutMode 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerSetTimeoutMode_t)(
    zet_sysman_handle_t,
    zet_sched_timeout_properties_t*,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerSetTimesliceMode 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerSetTimesliceMode_t)(
    zet_sysman_handle_t,
    zet_sched_timeslice_properties_t*,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerSetExclusiveMode 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerSetExclusiveMode_t)(
    zet_sysman_handle_t,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanSchedulerSetComputeUnitDebugMode 
typedef ze_result_t (__zecall *zet_pfnSysmanSchedulerSetComputeUnitDebugMode_t)(
    zet_sysman_handle_t,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPerformanceProfileGetSupported 
typedef ze_result_t (__zecall *zet_pfnSysmanPerformanceProfileGetSupported_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_perf_profile_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPerformanceProfileGet 
typedef ze_result_t (__zecall *zet_pfnSysmanPerformanceProfileGet_t)(
    zet_sysman_handle_t,
    zet_perf_profile_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPerformanceProfileSet 
typedef ze_result_t (__zecall *zet_pfnSysmanPerformanceProfileSet_t)(
    zet_sysman_handle_t,
    zet_perf_profile_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanProcessesGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanProcessesGetState_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_process_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanDeviceReset 
typedef ze_result_t (__zecall *zet_pfnSysmanDeviceReset_t)(
    zet_sysman_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanDeviceGetRepairStatus 
typedef ze_result_t (__zecall *zet_pfnSysmanDeviceGetRepairStatus_t)(
    zet_sysman_handle_t,
    zet_repair_status_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPciGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanPciGetProperties_t)(
    zet_sysman_handle_t,
    zet_pci_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPciGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanPciGetState_t)(
    zet_sysman_handle_t,
    zet_pci_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPciGetBars 
typedef ze_result_t (__zecall *zet_pfnSysmanPciGetBars_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_pci_bar_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPciGetStats 
typedef ze_result_t (__zecall *zet_pfnSysmanPciGetStats_t)(
    zet_sysman_handle_t,
    zet_pci_stats_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPowerGet 
typedef ze_result_t (__zecall *zet_pfnSysmanPowerGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_pwr_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyGet 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_freq_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEngineGet 
typedef ze_result_t (__zecall *zet_pfnSysmanEngineGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_engine_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanStandbyGet 
typedef ze_result_t (__zecall *zet_pfnSysmanStandbyGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_standby_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFirmwareGet 
typedef ze_result_t (__zecall *zet_pfnSysmanFirmwareGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_firmware_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanMemoryGet 
typedef ze_result_t (__zecall *zet_pfnSysmanMemoryGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_mem_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFabricPortGet 
typedef ze_result_t (__zecall *zet_pfnSysmanFabricPortGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_fabric_port_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanTemperatureGet 
typedef ze_result_t (__zecall *zet_pfnSysmanTemperatureGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_temp_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPsuGet 
typedef ze_result_t (__zecall *zet_pfnSysmanPsuGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_psu_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFanGet 
typedef ze_result_t (__zecall *zet_pfnSysmanFanGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_fan_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanLedGet 
typedef ze_result_t (__zecall *zet_pfnSysmanLedGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_led_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanRasGet 
typedef ze_result_t (__zecall *zet_pfnSysmanRasGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_ras_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEventGet 
typedef ze_result_t (__zecall *zet_pfnSysmanEventGet_t)(
    zet_sysman_handle_t,
    zet_sysman_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanDiagnosticsGet 
typedef ze_result_t (__zecall *zet_pfnSysmanDiagnosticsGet_t)(
    zet_sysman_handle_t,
    uint32_t*,
    zet_sysman_diag_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sysman functions pointers
typedef struct _zet_sysman_dditable_t
{
    zet_pfnSysmanGet_t                                          pfnGet;
    zet_pfnSysmanDeviceGetProperties_t                          pfnDeviceGetProperties;
    zet_pfnSysmanSchedulerGetSupportedModes_t                   pfnSchedulerGetSupportedModes;
    zet_pfnSysmanSchedulerGetCurrentMode_t                      pfnSchedulerGetCurrentMode;
    zet_pfnSysmanSchedulerGetTimeoutModeProperties_t            pfnSchedulerGetTimeoutModeProperties;
    zet_pfnSysmanSchedulerGetTimesliceModeProperties_t          pfnSchedulerGetTimesliceModeProperties;
    zet_pfnSysmanSchedulerSetTimeoutMode_t                      pfnSchedulerSetTimeoutMode;
    zet_pfnSysmanSchedulerSetTimesliceMode_t                    pfnSchedulerSetTimesliceMode;
    zet_pfnSysmanSchedulerSetExclusiveMode_t                    pfnSchedulerSetExclusiveMode;
    zet_pfnSysmanSchedulerSetComputeUnitDebugMode_t             pfnSchedulerSetComputeUnitDebugMode;
    zet_pfnSysmanPerformanceProfileGetSupported_t               pfnPerformanceProfileGetSupported;
    zet_pfnSysmanPerformanceProfileGet_t                        pfnPerformanceProfileGet;
    zet_pfnSysmanPerformanceProfileSet_t                        pfnPerformanceProfileSet;
    zet_pfnSysmanProcessesGetState_t                            pfnProcessesGetState;
    zet_pfnSysmanDeviceReset_t                                  pfnDeviceReset;
    zet_pfnSysmanDeviceGetRepairStatus_t                        pfnDeviceGetRepairStatus;
    zet_pfnSysmanPciGetProperties_t                             pfnPciGetProperties;
    zet_pfnSysmanPciGetState_t                                  pfnPciGetState;
    zet_pfnSysmanPciGetBars_t                                   pfnPciGetBars;
    zet_pfnSysmanPciGetStats_t                                  pfnPciGetStats;
    zet_pfnSysmanPowerGet_t                                     pfnPowerGet;
    zet_pfnSysmanFrequencyGet_t                                 pfnFrequencyGet;
    zet_pfnSysmanEngineGet_t                                    pfnEngineGet;
    zet_pfnSysmanStandbyGet_t                                   pfnStandbyGet;
    zet_pfnSysmanFirmwareGet_t                                  pfnFirmwareGet;
    zet_pfnSysmanMemoryGet_t                                    pfnMemoryGet;
    zet_pfnSysmanFabricPortGet_t                                pfnFabricPortGet;
    zet_pfnSysmanTemperatureGet_t                               pfnTemperatureGet;
    zet_pfnSysmanPsuGet_t                                       pfnPsuGet;
    zet_pfnSysmanFanGet_t                                       pfnFanGet;
    zet_pfnSysmanLedGet_t                                       pfnLedGet;
    zet_pfnSysmanRasGet_t                                       pfnRasGet;
    zet_pfnSysmanEventGet_t                                     pfnEventGet;
    zet_pfnSysmanDiagnosticsGet_t                               pfnDiagnosticsGet;
} zet_sysman_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPowerGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanPowerGetProperties_t)(
    zet_sysman_pwr_handle_t,
    zet_power_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPowerGetEnergyCounter 
typedef ze_result_t (__zecall *zet_pfnSysmanPowerGetEnergyCounter_t)(
    zet_sysman_pwr_handle_t,
    zet_power_energy_counter_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPowerGetLimits 
typedef ze_result_t (__zecall *zet_pfnSysmanPowerGetLimits_t)(
    zet_sysman_pwr_handle_t,
    zet_power_sustained_limit_t*,
    zet_power_burst_limit_t*,
    zet_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPowerSetLimits 
typedef ze_result_t (__zecall *zet_pfnSysmanPowerSetLimits_t)(
    zet_sysman_pwr_handle_t,
    const zet_power_sustained_limit_t*,
    const zet_power_burst_limit_t*,
    const zet_power_peak_limit_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPowerGetEnergyThreshold 
typedef ze_result_t (__zecall *zet_pfnSysmanPowerGetEnergyThreshold_t)(
    zet_sysman_pwr_handle_t,
    zet_energy_threshold_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPowerSetEnergyThreshold 
typedef ze_result_t (__zecall *zet_pfnSysmanPowerSetEnergyThreshold_t)(
    zet_sysman_pwr_handle_t,
    double
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanPower functions pointers
typedef struct _zet_sysman_power_dditable_t
{
    zet_pfnSysmanPowerGetProperties_t                           pfnGetProperties;
    zet_pfnSysmanPowerGetEnergyCounter_t                        pfnGetEnergyCounter;
    zet_pfnSysmanPowerGetLimits_t                               pfnGetLimits;
    zet_pfnSysmanPowerSetLimits_t                               pfnSetLimits;
    zet_pfnSysmanPowerGetEnergyThreshold_t                      pfnGetEnergyThreshold;
    zet_pfnSysmanPowerSetEnergyThreshold_t                      pfnSetEnergyThreshold;
} zet_sysman_power_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanPowerProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanPowerProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_power_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyGetProperties_t)(
    zet_sysman_freq_handle_t,
    zet_freq_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyGetAvailableClocks 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyGetAvailableClocks_t)(
    zet_sysman_freq_handle_t,
    uint32_t*,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyGetRange 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyGetRange_t)(
    zet_sysman_freq_handle_t,
    zet_freq_range_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencySetRange 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencySetRange_t)(
    zet_sysman_freq_handle_t,
    const zet_freq_range_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyGetState_t)(
    zet_sysman_freq_handle_t,
    zet_freq_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyGetThrottleTime 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyGetThrottleTime_t)(
    zet_sysman_freq_handle_t,
    zet_freq_throttle_time_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyOcGetCapabilities 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyOcGetCapabilities_t)(
    zet_sysman_freq_handle_t,
    zet_oc_capabilities_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyOcGetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyOcGetConfig_t)(
    zet_sysman_freq_handle_t,
    zet_oc_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyOcSetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyOcSetConfig_t)(
    zet_sysman_freq_handle_t,
    zet_oc_config_t*,
    ze_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyOcGetIccMax 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyOcGetIccMax_t)(
    zet_sysman_freq_handle_t,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyOcSetIccMax 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyOcSetIccMax_t)(
    zet_sysman_freq_handle_t,
    double
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyOcGetTjMax 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyOcGetTjMax_t)(
    zet_sysman_freq_handle_t,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFrequencyOcSetTjMax 
typedef ze_result_t (__zecall *zet_pfnSysmanFrequencyOcSetTjMax_t)(
    zet_sysman_freq_handle_t,
    double
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFrequency functions pointers
typedef struct _zet_sysman_frequency_dditable_t
{
    zet_pfnSysmanFrequencyGetProperties_t                       pfnGetProperties;
    zet_pfnSysmanFrequencyGetAvailableClocks_t                  pfnGetAvailableClocks;
    zet_pfnSysmanFrequencyGetRange_t                            pfnGetRange;
    zet_pfnSysmanFrequencySetRange_t                            pfnSetRange;
    zet_pfnSysmanFrequencyGetState_t                            pfnGetState;
    zet_pfnSysmanFrequencyGetThrottleTime_t                     pfnGetThrottleTime;
    zet_pfnSysmanFrequencyOcGetCapabilities_t                   pfnOcGetCapabilities;
    zet_pfnSysmanFrequencyOcGetConfig_t                         pfnOcGetConfig;
    zet_pfnSysmanFrequencyOcSetConfig_t                         pfnOcSetConfig;
    zet_pfnSysmanFrequencyOcGetIccMax_t                         pfnOcGetIccMax;
    zet_pfnSysmanFrequencyOcSetIccMax_t                         pfnOcSetIccMax;
    zet_pfnSysmanFrequencyOcGetTjMax_t                          pfnOcGetTjMax;
    zet_pfnSysmanFrequencyOcSetTjMax_t                          pfnOcSetTjMax;
} zet_sysman_frequency_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanFrequencyProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanFrequencyProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_frequency_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEngineGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanEngineGetProperties_t)(
    zet_sysman_engine_handle_t,
    zet_engine_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEngineGetActivity 
typedef ze_result_t (__zecall *zet_pfnSysmanEngineGetActivity_t)(
    zet_sysman_engine_handle_t,
    zet_engine_stats_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanEngine functions pointers
typedef struct _zet_sysman_engine_dditable_t
{
    zet_pfnSysmanEngineGetProperties_t                          pfnGetProperties;
    zet_pfnSysmanEngineGetActivity_t                            pfnGetActivity;
} zet_sysman_engine_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanEngineProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanEngineProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_engine_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanStandbyGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanStandbyGetProperties_t)(
    zet_sysman_standby_handle_t,
    zet_standby_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanStandbyGetMode 
typedef ze_result_t (__zecall *zet_pfnSysmanStandbyGetMode_t)(
    zet_sysman_standby_handle_t,
    zet_standby_promo_mode_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanStandbySetMode 
typedef ze_result_t (__zecall *zet_pfnSysmanStandbySetMode_t)(
    zet_sysman_standby_handle_t,
    zet_standby_promo_mode_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanStandby functions pointers
typedef struct _zet_sysman_standby_dditable_t
{
    zet_pfnSysmanStandbyGetProperties_t                         pfnGetProperties;
    zet_pfnSysmanStandbyGetMode_t                               pfnGetMode;
    zet_pfnSysmanStandbySetMode_t                               pfnSetMode;
} zet_sysman_standby_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanStandbyProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanStandbyProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_standby_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFirmwareGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanFirmwareGetProperties_t)(
    zet_sysman_firmware_handle_t,
    zet_firmware_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFirmwareGetChecksum 
typedef ze_result_t (__zecall *zet_pfnSysmanFirmwareGetChecksum_t)(
    zet_sysman_firmware_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFirmwareFlash 
typedef ze_result_t (__zecall *zet_pfnSysmanFirmwareFlash_t)(
    zet_sysman_firmware_handle_t,
    void*,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFirmware functions pointers
typedef struct _zet_sysman_firmware_dditable_t
{
    zet_pfnSysmanFirmwareGetProperties_t                        pfnGetProperties;
    zet_pfnSysmanFirmwareGetChecksum_t                          pfnGetChecksum;
    zet_pfnSysmanFirmwareFlash_t                                pfnFlash;
} zet_sysman_firmware_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanFirmwareProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanFirmwareProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_firmware_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanMemoryGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanMemoryGetProperties_t)(
    zet_sysman_mem_handle_t,
    zet_mem_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanMemoryGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanMemoryGetState_t)(
    zet_sysman_mem_handle_t,
    zet_mem_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanMemoryGetBandwidth 
typedef ze_result_t (__zecall *zet_pfnSysmanMemoryGetBandwidth_t)(
    zet_sysman_mem_handle_t,
    zet_mem_bandwidth_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanMemory functions pointers
typedef struct _zet_sysman_memory_dditable_t
{
    zet_pfnSysmanMemoryGetProperties_t                          pfnGetProperties;
    zet_pfnSysmanMemoryGetState_t                               pfnGetState;
    zet_pfnSysmanMemoryGetBandwidth_t                           pfnGetBandwidth;
} zet_sysman_memory_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanMemoryProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanMemoryProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_memory_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFabricPortGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanFabricPortGetProperties_t)(
    zet_sysman_fabric_port_handle_t,
    zet_fabric_port_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFabricPortGetLinkType 
typedef ze_result_t (__zecall *zet_pfnSysmanFabricPortGetLinkType_t)(
    zet_sysman_fabric_port_handle_t,
    ze_bool_t,
    zet_fabric_link_type_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFabricPortGetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanFabricPortGetConfig_t)(
    zet_sysman_fabric_port_handle_t,
    zet_fabric_port_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFabricPortSetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanFabricPortSetConfig_t)(
    zet_sysman_fabric_port_handle_t,
    const zet_fabric_port_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFabricPortGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanFabricPortGetState_t)(
    zet_sysman_fabric_port_handle_t,
    zet_fabric_port_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFabricPortGetThroughput 
typedef ze_result_t (__zecall *zet_pfnSysmanFabricPortGetThroughput_t)(
    zet_sysman_fabric_port_handle_t,
    zet_fabric_port_throughput_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFabricPort functions pointers
typedef struct _zet_sysman_fabric_port_dditable_t
{
    zet_pfnSysmanFabricPortGetProperties_t                      pfnGetProperties;
    zet_pfnSysmanFabricPortGetLinkType_t                        pfnGetLinkType;
    zet_pfnSysmanFabricPortGetConfig_t                          pfnGetConfig;
    zet_pfnSysmanFabricPortSetConfig_t                          pfnSetConfig;
    zet_pfnSysmanFabricPortGetState_t                           pfnGetState;
    zet_pfnSysmanFabricPortGetThroughput_t                      pfnGetThroughput;
} zet_sysman_fabric_port_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fabric_port_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanFabricPortProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanFabricPortProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_fabric_port_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanTemperatureGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanTemperatureGetProperties_t)(
    zet_sysman_temp_handle_t,
    zet_temp_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanTemperatureGetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanTemperatureGetConfig_t)(
    zet_sysman_temp_handle_t,
    zet_temp_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanTemperatureSetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanTemperatureSetConfig_t)(
    zet_sysman_temp_handle_t,
    const zet_temp_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanTemperatureGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanTemperatureGetState_t)(
    zet_sysman_temp_handle_t,
    double*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanTemperature functions pointers
typedef struct _zet_sysman_temperature_dditable_t
{
    zet_pfnSysmanTemperatureGetProperties_t                     pfnGetProperties;
    zet_pfnSysmanTemperatureGetConfig_t                         pfnGetConfig;
    zet_pfnSysmanTemperatureSetConfig_t                         pfnSetConfig;
    zet_pfnSysmanTemperatureGetState_t                          pfnGetState;
} zet_sysman_temperature_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanTemperatureProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanTemperatureProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_temperature_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPsuGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanPsuGetProperties_t)(
    zet_sysman_psu_handle_t,
    zet_psu_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanPsuGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanPsuGetState_t)(
    zet_sysman_psu_handle_t,
    zet_psu_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanPsu functions pointers
typedef struct _zet_sysman_psu_dditable_t
{
    zet_pfnSysmanPsuGetProperties_t                             pfnGetProperties;
    zet_pfnSysmanPsuGetState_t                                  pfnGetState;
} zet_sysman_psu_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanPsuProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanPsuProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_psu_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFanGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanFanGetProperties_t)(
    zet_sysman_fan_handle_t,
    zet_fan_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFanGetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanFanGetConfig_t)(
    zet_sysman_fan_handle_t,
    zet_fan_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFanSetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanFanSetConfig_t)(
    zet_sysman_fan_handle_t,
    const zet_fan_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanFanGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanFanGetState_t)(
    zet_sysman_fan_handle_t,
    zet_fan_speed_units_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanFan functions pointers
typedef struct _zet_sysman_fan_dditable_t
{
    zet_pfnSysmanFanGetProperties_t                             pfnGetProperties;
    zet_pfnSysmanFanGetConfig_t                                 pfnGetConfig;
    zet_pfnSysmanFanSetConfig_t                                 pfnSetConfig;
    zet_pfnSysmanFanGetState_t                                  pfnGetState;
} zet_sysman_fan_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanFanProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanFanProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_fan_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanLedGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanLedGetProperties_t)(
    zet_sysman_led_handle_t,
    zet_led_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanLedGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanLedGetState_t)(
    zet_sysman_led_handle_t,
    zet_led_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanLedSetState 
typedef ze_result_t (__zecall *zet_pfnSysmanLedSetState_t)(
    zet_sysman_led_handle_t,
    const zet_led_state_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanLed functions pointers
typedef struct _zet_sysman_led_dditable_t
{
    zet_pfnSysmanLedGetProperties_t                             pfnGetProperties;
    zet_pfnSysmanLedGetState_t                                  pfnGetState;
    zet_pfnSysmanLedSetState_t                                  pfnSetState;
} zet_sysman_led_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanLedProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanLedProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_led_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanRasGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanRasGetProperties_t)(
    zet_sysman_ras_handle_t,
    zet_ras_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanRasGetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanRasGetConfig_t)(
    zet_sysman_ras_handle_t,
    zet_ras_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanRasSetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanRasSetConfig_t)(
    zet_sysman_ras_handle_t,
    const zet_ras_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanRasGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanRasGetState_t)(
    zet_sysman_ras_handle_t,
    ze_bool_t,
    uint64_t*,
    zet_ras_details_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanRas functions pointers
typedef struct _zet_sysman_ras_dditable_t
{
    zet_pfnSysmanRasGetProperties_t                             pfnGetProperties;
    zet_pfnSysmanRasGetConfig_t                                 pfnGetConfig;
    zet_pfnSysmanRasSetConfig_t                                 pfnSetConfig;
    zet_pfnSysmanRasGetState_t                                  pfnGetState;
} zet_sysman_ras_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanRasProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanRasProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_ras_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEventGetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanEventGetConfig_t)(
    zet_sysman_event_handle_t,
    zet_event_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEventSetConfig 
typedef ze_result_t (__zecall *zet_pfnSysmanEventSetConfig_t)(
    zet_sysman_event_handle_t,
    const zet_event_config_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEventGetState 
typedef ze_result_t (__zecall *zet_pfnSysmanEventGetState_t)(
    zet_sysman_event_handle_t,
    ze_bool_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanEventListen 
typedef ze_result_t (__zecall *zet_pfnSysmanEventListen_t)(
    ze_driver_handle_t,
    uint32_t,
    uint32_t,
    zet_sysman_event_handle_t*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanEvent functions pointers
typedef struct _zet_sysman_event_dditable_t
{
    zet_pfnSysmanEventGetConfig_t                               pfnGetConfig;
    zet_pfnSysmanEventSetConfig_t                               pfnSetConfig;
    zet_pfnSysmanEventGetState_t                                pfnGetState;
    zet_pfnSysmanEventListen_t                                  pfnListen;
} zet_sysman_event_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEvent table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_event_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanEventProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanEventProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_event_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanDiagnosticsGetProperties 
typedef ze_result_t (__zecall *zet_pfnSysmanDiagnosticsGetProperties_t)(
    zet_sysman_diag_handle_t,
    zet_diag_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanDiagnosticsGetTests 
typedef ze_result_t (__zecall *zet_pfnSysmanDiagnosticsGetTests_t)(
    zet_sysman_diag_handle_t,
    uint32_t*,
    zet_diag_test_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetSysmanDiagnosticsRunTests 
typedef ze_result_t (__zecall *zet_pfnSysmanDiagnosticsRunTests_t)(
    zet_sysman_diag_handle_t,
    uint32_t,
    uint32_t,
    zet_diag_result_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of SysmanDiagnostics functions pointers
typedef struct _zet_sysman_diagnostics_dditable_t
{
    zet_pfnSysmanDiagnosticsGetProperties_t                     pfnGetProperties;
    zet_pfnSysmanDiagnosticsGetTests_t                          pfnGetTests;
    zet_pfnSysmanDiagnosticsRunTests_t                          pfnRunTests;
} zet_sysman_diagnostics_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetSysmanDiagnosticsProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetSysmanDiagnosticsProcAddrTable_t)(
    ze_api_version_t,
    zet_sysman_diagnostics_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetModuleGetDebugInfo 
typedef ze_result_t (__zecall *zet_pfnModuleGetDebugInfo_t)(
    zet_module_handle_t,
    zet_module_debug_info_format_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module functions pointers
typedef struct _zet_module_dditable_t
{
    zet_pfnModuleGetDebugInfo_t                                 pfnGetDebugInfo;
} zet_module_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetModuleProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetModuleProcAddrTable_t)(
    ze_api_version_t,
    zet_module_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetKernelGetProfileInfo 
typedef ze_result_t (__zecall *zet_pfnKernelGetProfileInfo_t)(
    zet_kernel_handle_t,
    zet_profile_info_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Kernel functions pointers
typedef struct _zet_kernel_dditable_t
{
    zet_pfnKernelGetProfileInfo_t                               pfnGetProfileInfo;
} zet_kernel_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetKernelProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetKernelProcAddrTable_t)(
    ze_api_version_t,
    zet_kernel_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGroupGet 
typedef ze_result_t (__zecall *zet_pfnMetricGroupGet_t)(
    zet_device_handle_t,
    uint32_t*,
    zet_metric_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGroupGetProperties 
typedef ze_result_t (__zecall *zet_pfnMetricGroupGetProperties_t)(
    zet_metric_group_handle_t,
    zet_metric_group_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGroupCalculateMetricValues 
typedef ze_result_t (__zecall *zet_pfnMetricGroupCalculateMetricValues_t)(
    zet_metric_group_handle_t,
    size_t,
    const uint8_t*,
    uint32_t*,
    zet_typed_value_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricGroup functions pointers
typedef struct _zet_metric_group_dditable_t
{
    zet_pfnMetricGroupGet_t                                     pfnGet;
    zet_pfnMetricGroupGetProperties_t                           pfnGetProperties;
    zet_pfnMetricGroupCalculateMetricValues_t                   pfnCalculateMetricValues;
} zet_metric_group_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricGroupProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricGroupProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_group_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGet 
typedef ze_result_t (__zecall *zet_pfnMetricGet_t)(
    zet_metric_group_handle_t,
    uint32_t*,
    zet_metric_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricGetProperties 
typedef ze_result_t (__zecall *zet_pfnMetricGetProperties_t)(
    zet_metric_handle_t,
    zet_metric_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Metric functions pointers
typedef struct _zet_metric_dditable_t
{
    zet_pfnMetricGet_t                                          pfnGet;
    zet_pfnMetricGetProperties_t                                pfnGetProperties;
} zet_metric_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricTracerOpen 
typedef ze_result_t (__zecall *zet_pfnMetricTracerOpen_t)(
    zet_device_handle_t,
    zet_metric_group_handle_t,
    zet_metric_tracer_desc_t*,
    ze_event_handle_t,
    zet_metric_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricTracerClose 
typedef ze_result_t (__zecall *zet_pfnMetricTracerClose_t)(
    zet_metric_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricTracerReadData 
typedef ze_result_t (__zecall *zet_pfnMetricTracerReadData_t)(
    zet_metric_tracer_handle_t,
    uint32_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricTracer functions pointers
typedef struct _zet_metric_tracer_dditable_t
{
    zet_pfnMetricTracerOpen_t                                   pfnOpen;
    zet_pfnMetricTracerClose_t                                  pfnClose;
    zet_pfnMetricTracerReadData_t                               pfnReadData;
} zet_metric_tracer_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricTracerProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricTracerProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_tracer_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryPoolCreate 
typedef ze_result_t (__zecall *zet_pfnMetricQueryPoolCreate_t)(
    zet_device_handle_t,
    zet_metric_group_handle_t,
    const zet_metric_query_pool_desc_t*,
    zet_metric_query_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryPoolDestroy 
typedef ze_result_t (__zecall *zet_pfnMetricQueryPoolDestroy_t)(
    zet_metric_query_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQueryPool functions pointers
typedef struct _zet_metric_query_pool_dditable_t
{
    zet_pfnMetricQueryPoolCreate_t                              pfnCreate;
    zet_pfnMetricQueryPoolDestroy_t                             pfnDestroy;
} zet_metric_query_pool_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricQueryPoolProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricQueryPoolProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_query_pool_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryCreate 
typedef ze_result_t (__zecall *zet_pfnMetricQueryCreate_t)(
    zet_metric_query_pool_handle_t,
    uint32_t,
    zet_metric_query_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryDestroy 
typedef ze_result_t (__zecall *zet_pfnMetricQueryDestroy_t)(
    zet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryReset 
typedef ze_result_t (__zecall *zet_pfnMetricQueryReset_t)(
    zet_metric_query_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetMetricQueryGetData 
typedef ze_result_t (__zecall *zet_pfnMetricQueryGetData_t)(
    zet_metric_query_handle_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of MetricQuery functions pointers
typedef struct _zet_metric_query_dditable_t
{
    zet_pfnMetricQueryCreate_t                                  pfnCreate;
    zet_pfnMetricQueryDestroy_t                                 pfnDestroy;
    zet_pfnMetricQueryReset_t                                   pfnReset;
    zet_pfnMetricQueryGetData_t                                 pfnGetData;
} zet_metric_query_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetMetricQueryProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetMetricQueryProcAddrTable_t)(
    ze_api_version_t,
    zet_metric_query_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerCreate 
typedef ze_result_t (__zecall *zet_pfnTracerCreate_t)(
    zet_driver_handle_t,
    const zet_tracer_desc_t*,
    zet_tracer_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerDestroy 
typedef ze_result_t (__zecall *zet_pfnTracerDestroy_t)(
    zet_tracer_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerSetPrologues 
typedef ze_result_t (__zecall *zet_pfnTracerSetPrologues_t)(
    zet_tracer_handle_t,
    zet_core_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerSetEpilogues 
typedef ze_result_t (__zecall *zet_pfnTracerSetEpilogues_t)(
    zet_tracer_handle_t,
    zet_core_callbacks_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetTracerSetEnabled 
typedef ze_result_t (__zecall *zet_pfnTracerSetEnabled_t)(
    zet_tracer_handle_t,
    ze_bool_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Tracer functions pointers
typedef struct _zet_tracer_dditable_t
{
    zet_pfnTracerCreate_t                                       pfnCreate;
    zet_pfnTracerDestroy_t                                      pfnDestroy;
    zet_pfnTracerSetPrologues_t                                 pfnSetPrologues;
    zet_pfnTracerSetEpilogues_t                                 pfnSetEpilogues;
    zet_pfnTracerSetEnabled_t                                   pfnSetEnabled;
} zet_tracer_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetTracerProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetTracerProcAddrTable_t)(
    ze_api_version_t,
    zet_tracer_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugAttach 
typedef ze_result_t (__zecall *zet_pfnDebugAttach_t)(
    zet_device_handle_t,
    const zet_debug_config_t*,
    zet_debug_session_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugDetach 
typedef ze_result_t (__zecall *zet_pfnDebugDetach_t)(
    zet_debug_session_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugGetNumThreads 
typedef ze_result_t (__zecall *zet_pfnDebugGetNumThreads_t)(
    zet_debug_session_handle_t,
    uint64_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugReadEvent 
typedef ze_result_t (__zecall *zet_pfnDebugReadEvent_t)(
    zet_debug_session_handle_t,
    uint64_t,
    size_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugInterrupt 
typedef ze_result_t (__zecall *zet_pfnDebugInterrupt_t)(
    zet_debug_session_handle_t,
    uint64_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugResume 
typedef ze_result_t (__zecall *zet_pfnDebugResume_t)(
    zet_debug_session_handle_t,
    uint64_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugReadMemory 
typedef ze_result_t (__zecall *zet_pfnDebugReadMemory_t)(
    zet_debug_session_handle_t,
    uint64_t,
    int,
    uint64_t,
    size_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugWriteMemory 
typedef ze_result_t (__zecall *zet_pfnDebugWriteMemory_t)(
    zet_debug_session_handle_t,
    uint64_t,
    int,
    uint64_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugReadState 
typedef ze_result_t (__zecall *zet_pfnDebugReadState_t)(
    zet_debug_session_handle_t,
    uint64_t,
    uint64_t,
    size_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetDebugWriteState 
typedef ze_result_t (__zecall *zet_pfnDebugWriteState_t)(
    zet_debug_session_handle_t,
    uint64_t,
    uint64_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Debug functions pointers
typedef struct _zet_debug_dditable_t
{
    zet_pfnDebugAttach_t                                        pfnAttach;
    zet_pfnDebugDetach_t                                        pfnDetach;
    zet_pfnDebugGetNumThreads_t                                 pfnGetNumThreads;
    zet_pfnDebugReadEvent_t                                     pfnReadEvent;
    zet_pfnDebugInterrupt_t                                     pfnInterrupt;
    zet_pfnDebugResume_t                                        pfnResume;
    zet_pfnDebugReadMemory_t                                    pfnReadMemory;
    zet_pfnDebugWriteMemory_t                                   pfnWriteMemory;
    zet_pfnDebugReadState_t                                     pfnReadState;
    zet_pfnDebugWriteState_t                                    pfnWriteState;
} zet_debug_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Debug table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for zetGetDebugProcAddrTable
typedef ze_result_t (__zecall *zet_pfnGetDebugProcAddrTable_t)(
    ze_api_version_t,
    zet_debug_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _zet_dditable_t
{
    zet_global_dditable_t               Global;
    zet_device_dditable_t               Device;
    zet_command_list_dditable_t         CommandList;
    zet_sysman_dditable_t               Sysman;
    zet_sysman_power_dditable_t         SysmanPower;
    zet_sysman_frequency_dditable_t     SysmanFrequency;
    zet_sysman_engine_dditable_t        SysmanEngine;
    zet_sysman_standby_dditable_t       SysmanStandby;
    zet_sysman_firmware_dditable_t      SysmanFirmware;
    zet_sysman_memory_dditable_t        SysmanMemory;
    zet_sysman_fabric_port_dditable_t   SysmanFabricPort;
    zet_sysman_temperature_dditable_t   SysmanTemperature;
    zet_sysman_psu_dditable_t           SysmanPsu;
    zet_sysman_fan_dditable_t           SysmanFan;
    zet_sysman_led_dditable_t           SysmanLed;
    zet_sysman_ras_dditable_t           SysmanRas;
    zet_sysman_event_dditable_t         SysmanEvent;
    zet_sysman_diagnostics_dditable_t   SysmanDiagnostics;
    zet_module_dditable_t               Module;
    zet_kernel_dditable_t               Kernel;
    zet_metric_group_dditable_t         MetricGroup;
    zet_metric_dditable_t               Metric;
    zet_metric_tracer_dditable_t        MetricTracer;
    zet_metric_query_pool_dditable_t    MetricQueryPool;
    zet_metric_query_dditable_t         MetricQuery;
    zet_tracer_dditable_t               Tracer;
    zet_debug_dditable_t                Debug;
} zet_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_DDI_H