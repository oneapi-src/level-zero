/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "zet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the handle to access Sysman features for a device
/// 
/// @details
///     - The returned handle is unique.
///     - ::zet_device_handle_t returned by ::zeDeviceGetSubDevices() are not
///       support. Only use handles returned by ::zeDeviceGet(). All resources
///       on sub-devices can be enumerated through the primary device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + version
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phSysman`
ze_result_t __zecall
zetSysmanGet(
    zet_device_handle_t hDevice,                    ///< [in] Handle of the device
    zet_sysman_version_t version,                   ///< [in] Sysman version that application was built with
    zet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing Sysman features
    )
{
    auto pfnGet = zet_lib::context.ddiTable.Sysman.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGet( hDevice, version, phSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanDeviceGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
    )
{
    auto pfnDeviceGetProperties = zet_lib::context.ddiTable.Sysman.pfnDeviceGetProperties;
    if( nullptr == pfnDeviceGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceGetProperties( hSysman, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get a list of supported scheduler modes
/// 
/// @details
///     - If zero modes are returned, control of scheduler modes are not
///       supported.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanSchedulerGetSupportedModes(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of scheduler modes.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of supported modes.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< supported scheduler modes.
                                                    ///< if count is larger than the number of supported scheduler modes, then
                                                    ///< the driver will update the value with the correct number of supported
                                                    ///< scheduler modes that are returned.
    zet_sched_mode_t* pModes                        ///< [in,out][optional][range(0, *pCount)] Array of supported scheduler
                                                    ///< modes
    )
{
    auto pfnSchedulerGetSupportedModes = zet_lib::context.ddiTable.Sysman.pfnSchedulerGetSupportedModes;
    if( nullptr == pfnSchedulerGetSupportedModes )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerGetSupportedModes( hSysman, pCount, pModes );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduler mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Device does not support scheduler modes (check using ::zetSysmanSchedulerGetSupportedModes()).
ze_result_t __zecall
zetSysmanSchedulerGetCurrentMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
    )
{
    auto pfnSchedulerGetCurrentMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerGetCurrentMode;
    if( nullptr == pfnSchedulerGetCurrentMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerGetCurrentMode( hSysman, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMEOUT
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler mode is not supported (check using ::zetSysmanSchedulerGetSupportedModes()).
ze_result_t __zecall
zetSysmanSchedulerGetTimeoutModeProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeout_properties_t* pConfig         ///< [in] Will contain the current parameters for this mode.
    )
{
    auto pfnSchedulerGetTimeoutModeProperties = zet_lib::context.ddiTable.Sysman.pfnSchedulerGetTimeoutModeProperties;
    if( nullptr == pfnSchedulerGetTimeoutModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerGetTimeoutModeProperties( hSysman, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMESLICE
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler mode is not supported (check using ::zetSysmanSchedulerGetSupportedModes()).
ze_result_t __zecall
zetSysmanSchedulerGetTimesliceModeProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeslice_properties_t* pConfig       ///< [in] Will contain the current parameters for this mode.
    )
{
    auto pfnSchedulerGetTimesliceModeProperties = zet_lib::context.ddiTable.Sysman.pfnSchedulerGetTimesliceModeProperties;
    if( nullptr == pfnSchedulerGetTimesliceModeProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerGetTimesliceModeProperties( hSysman, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_TIMEOUT or update scheduler
///        mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized for multiple applications or contexts
///       submitting work to the hardware. When higher priority work arrives,
///       the scheduler attempts to pause the current executing work within some
///       timeout interval, then submits the other work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReboot`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler mode is not supported (check using ::zetSysmanSchedulerGetSupportedModes()).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetTimeoutMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    )
{
    auto pfnSchedulerSetTimeoutMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetTimeoutMode;
    if( nullptr == pfnSchedulerSetTimeoutMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerSetTimeoutMode( hSysman, pProperties, pNeedReboot );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_TIMESLICE or update
///        scheduler mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized to provide fair sharing of hardware execution
///       time between multiple contexts submitting work to the hardware
///       concurrently.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReboot`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler mode is not supported (check using ::zetSysmanSchedulerGetSupportedModes()).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetTimesliceMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    )
{
    auto pfnSchedulerSetTimesliceMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetTimesliceMode;
    if( nullptr == pfnSchedulerSetTimesliceMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerSetTimesliceMode( hSysman, pProperties, pNeedReboot );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_EXCLUSIVE
/// 
/// @details
///     - This mode is optimized for single application/context use-cases. It
///       permits a context to run indefinitely on the hardware without being
///       preempted or terminated. All pending work for other contexts must wait
///       until the running context completes with no further submitted work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReboot`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler mode is not supported (check using ::zetSysmanSchedulerGetSupportedModes()).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetExclusiveMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    )
{
    auto pfnSchedulerSetExclusiveMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetExclusiveMode;
    if( nullptr == pfnSchedulerSetExclusiveMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerSetExclusiveMode( hSysman, pNeedReboot );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZET_SCHED_MODE_COMPUTE_UNIT_DEBUG
/// 
/// @details
///     - This mode is optimized for application debug. It ensures that only one
///       command queue can execute work on the hardware at a given time. Work
///       is permitted to run as long as needed without enforcing any scheduler
///       fairness policies.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReboot`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler mode is not supported (check using ::zetSysmanSchedulerGetSupportedModes()).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t __zecall
zetSysmanSchedulerSetComputeUnitDebugMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    )
{
    auto pfnSchedulerSetComputeUnitDebugMode = zet_lib::context.ddiTable.Sysman.pfnSchedulerSetComputeUnitDebugMode;
    if( nullptr == pfnSchedulerSetComputeUnitDebugMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSchedulerSetComputeUnitDebugMode( hSysman, pNeedReboot );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get a list of supported performance profiles that can be loaded for
///        this device
/// 
/// @details
///     - The balanced profile ::ZET_PERF_PROFILE_BALANCED is always returned in
///       the array.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanPerformanceProfileGetSupported(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of performance profiles.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of supported performance profiles.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< supported performance profiles.
                                                    ///< if count is larger than the number of supported performance profiles,
                                                    ///< then the driver will update the value with the correct number of
                                                    ///< supported performance profiles that are returned.
    zet_perf_profile_t* pProfiles                   ///< [in,out][optional][range(0, *pCount)] Array of supported performance
                                                    ///< profiles
    )
{
    auto pfnPerformanceProfileGetSupported = zet_lib::context.ddiTable.Sysman.pfnPerformanceProfileGetSupported;
    if( nullptr == pfnPerformanceProfileGetSupported )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPerformanceProfileGetSupported( hSysman, pCount, pProfiles );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current pre-configured performance profile being used by the
///        hardware
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProfile`
ze_result_t __zecall
zetSysmanPerformanceProfileGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_perf_profile_t* pProfile                    ///< [in] The performance profile currently loaded.
    )
{
    auto pfnPerformanceProfileGet = zet_lib::context.ddiTable.Sysman.pfnPerformanceProfileGet;
    if( nullptr == pfnPerformanceProfileGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPerformanceProfileGet( hSysman, pProfile );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Load a pre-configured performance profile
/// 
/// @details
///     - Performance profiles are not persistent settings. If the device is
///       reset, the device will default back to the balanced profile
///       ::ZET_PERF_PROFILE_BALANCED.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + profile
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + The specified profile is not valid or not supported on this device (use ::zetSysmanPerformanceProfileGetSupported() to get a list of supported profiles).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to change the performance profile of the hardware.
ze_result_t __zecall
zetSysmanPerformanceProfileSet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_perf_profile_t profile                      ///< [in] The performance profile to load.
    )
{
    auto pfnPerformanceProfileSet = zet_lib::context.ddiTable.Sysman.pfnPerformanceProfileSet;
    if( nullptr == pfnPerformanceProfileSet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPerformanceProfileSet( hSysman, profile );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about host processes using the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanProcessesGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of processes currently using the device.
                                                    ///< if count is non-zero, then driver will only retrieve that number of processes.
                                                    ///< if count is larger than the number of processes, then the driver will
                                                    ///< update the value with the correct number of processes that are returned.
    zet_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                    ///< one for each process currently using the device
    )
{
    auto pfnProcessesGetState = zet_lib::context.ddiTable.Sysman.pfnProcessesGetState;
    if( nullptr == pfnProcessesGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnProcessesGetState( hSysman, pCount, pProcesses );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t __zecall
zetSysmanDeviceReset(
    zet_sysman_handle_t hSysman                     ///< [in] Sysman handle for the device
    )
{
    auto pfnDeviceReset = zet_lib::context.ddiTable.Sysman.pfnDeviceReset;
    if( nullptr == pfnDeviceReset )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceReset( hSysman );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out if the device has been repaired (either by the manufacturer
///        or by running diagnostics)
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRepairStatus`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this property.
ze_result_t __zecall
zetSysmanDeviceGetRepairStatus(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    zet_repair_status_t* pRepairStatus              ///< [in] Will indicate if the device was repaired
    )
{
    auto pfnDeviceGetRepairStatus = zet_lib::context.ddiTable.Sysman.pfnDeviceGetRepairStatus;
    if( nullptr == pfnDeviceGetRepairStatus )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDeviceGetRepairStatus( hSysman, pRepairStatus );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanPciGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
    )
{
    auto pfnPciGetProperties = zet_lib::context.ddiTable.Sysman.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetProperties( hSysman, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current PCI state - current speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanPciGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
    )
{
    auto pfnPciGetState = zet_lib::context.ddiTable.Sysman.pfnPciGetState;
    if( nullptr == pfnPciGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetState( hSysman, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about each configured bar
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanPciGetBars(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of bars.
                                                    ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                    ///< if count is larger than the number of bar, then the driver will update
                                                    ///< the value with the correct number of bars that are returned.
    zet_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of bar properties
    )
{
    auto pfnPciGetBars = zet_lib::context.ddiTable.Sysman.pfnPciGetBars;
    if( nullptr == pfnPciGetBars )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetBars( hSysman, pCount, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats - bandwidth, number of packets, number of replays
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zetSysmanPciGetStats(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
    )
{
    auto pfnPciGetStats = zet_lib::context.ddiTable.Sysman.pfnPciGetStats;
    if( nullptr == pfnPciGetStats )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPciGetStats( hSysman, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanPowerGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnPowerGet = zet_lib::context.ddiTable.Sysman.pfnPowerGet;
    if( nullptr == pfnPowerGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPowerGet( hSysman, pCount, phPower );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a power domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanPowerGetProperties(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanPower.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPower, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEnergy`
ze_result_t __zecall
zetSysmanPowerGetEnergyCounter(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    )
{
    auto pfnGetEnergyCounter = zet_lib::context.ddiTable.SysmanPower.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyCounter( hPower, pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
ze_result_t __zecall
zetSysmanPowerGetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
    zet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
    zet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
    )
{
    auto pfnGetLimits = zet_lib::context.ddiTable.SysmanPower.pfnGetLimits;
    if( nullptr == pfnGetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t __zecall
zetSysmanPowerSetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    const zet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const zet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const zet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    )
{
    auto pfnSetLimits = zet_lib::context.ddiTable.SysmanPower.pfnSetLimits;
    if( nullptr == pfnSetLimits )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy threshold
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThreshold`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zet_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t __zecall
zetSysmanPowerGetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_energy_threshold_t* pThreshold              ///< [in] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    )
{
    auto pfnGetEnergyThreshold = zet_lib::context.ddiTable.SysmanPower.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetEnergyThreshold( hPower, pThreshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - An event ::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED will be
///       generated when the delta energy consumed starting from this call
///       exceeds the specified threshold. Use the function
///       ::zetSysmanEventSetConfig() to start receiving the event.
///     - Only one running process can control the energy threshold at a given
///       time. If another process attempts to change the energy threshold, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zetSysmanPowerGetEnergyThreshold() to determine the process ID
///       currently controlling this setting.
///     - Calling this function will remove any pending energy thresholds and
///       start counting from the time of this call.
///     - Once the energy threshold has been reached and the event generated,
///       the threshold is automatically removed. It is up to the application to
///       request a new threshold.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check ::zet_power_properties_t.isEnergyThresholdSupported).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process has set the energy threshold.
ze_result_t __zecall
zetSysmanPowerSetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    )
{
    auto pfnSetEnergyThreshold = zet_lib::context.ddiTable.SysmanPower.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetEnergyThreshold( hPower, threshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of frequency domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanFrequencyGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFrequencyGet = zet_lib::context.ddiTable.Sysman.pfnFrequencyGet;
    if( nullptr == pfnFrequencyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFrequencyGet( hSysman, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency properties - available frequencies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFrequencyGetProperties(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFrequency.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFrequency, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get available non-overclocked hardware clock frequencies for the
///        frequency domain
/// 
/// @details
///     - The list of available frequencies is returned in order of slowest to
///       fastest.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanFrequencyGetAvailableClocks(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of frequencies available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                    ///< If count is larger than the number of frequencies available, then the
                                                    ///< driver will update the value with the correct number of frequencies available.
    double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                    ///< MHz and sorted from slowest to fastest
    )
{
    auto pfnGetAvailableClocks = zet_lib::context.ddiTable.SysmanFrequency.pfnGetAvailableClocks;
    if( nullptr == pfnGetAvailableClocks )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
ze_result_t __zecall
zetSysmanFrequencyGetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_range_t* pLimits                       ///< [in] The range between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnGetRange = zet_lib::context.ddiTable.SysmanFrequency.pfnGetRange;
    if( nullptr == pfnGetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency range between which the hardware can operate.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencySetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    const zet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    auto pfnSetRange = zet_lib::context.ddiTable.SysmanFrequency.pfnSetRange;
    if( nullptr == pfnSetRange )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency state - frequency request, actual frequency, TDP
///        limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanFrequencyGetState(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanFrequency.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFrequency, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency throttle time
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThrottleTime`
ze_result_t __zecall
zetSysmanFrequencyGetThrottleTime(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    )
{
    auto pfnGetThrottleTime = zet_lib::context.ddiTable.SysmanFrequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThrottleTime( hFrequency, pThrottleTime );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking capabilities.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcCapabilities`
ze_result_t __zecall
zetSysmanFrequencyOcGetCapabilities(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_capabilities_t* pOcCapabilities          ///< [in] Pointer to the capabilities structure ::zet_oc_capabilities_t.
    )
{
    auto pfnOcGetCapabilities = zet_lib::context.ddiTable.SysmanFrequency.pfnOcGetCapabilities;
    if( nullptr == pfnOcGetCapabilities )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking configuration.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcConfiguration`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
ze_result_t __zecall
zetSysmanFrequencyOcGetConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_config_t* pOcConfiguration               ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
    )
{
    auto pfnOcGetConfig = zet_lib::context.ddiTable.SysmanFrequency.pfnOcGetConfig;
    if( nullptr == pfnOcGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetConfig( hFrequency, pOcConfiguration );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the overclocking configuration.
/// 
/// @details
///     - If ::zet_oc_config_t.mode is set to ::ZET_OC_MODE_OFF, overclocking
///       will be turned off and the hardware returned to run with factory
///       voltages/frequencies. Call ::zetSysmanFrequencyOcSetIccMax() and
///       ::zetSysmanFrequencyOcSetTjMax() separately with 0.0 to return those
///       settings to factory defaults.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcConfiguration`
///         + `nullptr == pDeviceRestart`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see ::zet_oc_capabilities_t.maxOcFrequency, ::zet_oc_capabilities_t.maxOcVoltage, ::zet_oc_capabilities_t.minOcVoltageOffset, ::zet_oc_capabilities_t.maxOcVoltageOffset).
///         + Requested voltage overclock is very high but ::zet_oc_capabilities_t.isHighVoltModeEnabled is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencyOcSetConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
    ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                    ///< in order to enable the new overclock settings.
    )
{
    auto pfnOcSetConfig = zet_lib::context.ddiTable.SysmanFrequency.pfnOcSetConfig;
    if( nullptr == pfnOcSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum current limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcIccMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + Capability ::zet_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
ze_result_t __zecall
zetSysmanFrequencyOcGetIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in] Will contain the maximum current limit in Amperes on successful
                                                    ///< return.
    )
{
    auto pfnOcGetIccMax = zet_lib::context.ddiTable.SysmanFrequency.pfnOcGetIccMax;
    if( nullptr == pfnOcGetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetIccMax( hFrequency, pOcIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum current limit setting.
/// 
/// @details
///     - Setting ocIccMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + Capability ::zet_oc_capabilities_t.isIccMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified current limit is too low or too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencyOcSetIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    )
{
    auto pfnOcSetIccMax = zet_lib::context.ddiTable.SysmanFrequency.pfnOcSetIccMax;
    if( nullptr == pfnOcSetIccMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetIccMax( hFrequency, ocIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum temperature limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcTjMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
ze_result_t __zecall
zetSysmanFrequencyOcGetTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in] Will contain the maximum temperature limit in degrees Celsius on
                                                    ///< successful return.
    )
{
    auto pfnOcGetTjMax = zet_lib::context.ddiTable.SysmanFrequency.pfnOcGetTjMax;
    if( nullptr == pfnOcGetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcGetTjMax( hFrequency, pOcTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum temperature limit setting.
/// 
/// @details
///     - Setting ocTjMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (::zet_oc_capabilities_t.isOcSupported)
///         + Capability ::zet_oc_capabilities_t.isTjMaxSupported is false for this frequency domain
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified temperature limit is too high
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFrequencyOcSetTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    )
{
    auto pfnOcSetTjMax = zet_lib::context.ddiTable.SysmanFrequency.pfnOcSetTjMax;
    if( nullptr == pfnOcSetTjMax )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnOcSetTjMax( hFrequency, ocTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of engine groups
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanEngineGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnEngineGet = zet_lib::context.ddiTable.Sysman.pfnEngineGet;
    if( nullptr == pfnEngineGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEngineGet( hSysman, pCount, phEngine );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine group properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanEngineGetProperties(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanEngine.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hEngine, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity stats for an engine group
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
ze_result_t __zecall
zetSysmanEngineGetActivity(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
    )
{
    auto pfnGetActivity = zet_lib::context.ddiTable.SysmanEngine.pfnGetActivity;
    if( nullptr == pfnGetActivity )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetActivity( hEngine, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of standby controls
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanStandbyGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnStandbyGet = zet_lib::context.ddiTable.Sysman.pfnStandbyGet;
    if( nullptr == pfnStandbyGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnStandbyGet( hSysman, pCount, phStandby );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get standby hardware component properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanStandbyGetProperties(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanStandby.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hStandby, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
ze_result_t __zecall
zetSysmanStandbyGetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
    )
{
    auto pfnGetMode = zet_lib::context.ddiTable.SysmanStandby.pfnGetMode;
    if( nullptr == pfnGetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetMode( hStandby, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + mode
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanStandbySetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
    )
{
    auto pfnSetMode = zet_lib::context.ddiTable.SysmanStandby.pfnSetMode;
    if( nullptr == pfnSetMode )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetMode( hStandby, mode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of firmwares
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanFirmwareGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFirmwareGet = zet_lib::context.ddiTable.Sysman.pfnFirmwareGet;
    if( nullptr == pfnFirmwareGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFirmwareGet( hSysman, pCount, phFirmware );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFirmwareGetProperties(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    zet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFirmware.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFirmware, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware checksum
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pChecksum`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t __zecall
zetSysmanFirmwareGetChecksum(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
    )
{
    auto pfnGetChecksum = zet_lib::context.ddiTable.SysmanFirmware.pfnGetChecksum;
    if( nullptr == pfnGetChecksum )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetChecksum( hFirmware, pChecksum );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Flash a new firmware image
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImage`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t __zecall
zetSysmanFirmwareFlash(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    )
{
    auto pfnFlash = zet_lib::context.ddiTable.SysmanFirmware.pfnFlash;
    if( nullptr == pfnFlash )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFlash( hFirmware, pImage, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of memory modules
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanMemoryGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnMemoryGet = zet_lib::context.ddiTable.Sysman.pfnMemoryGet;
    if( nullptr == pfnMemoryGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnMemoryGet( hSysman, pCount, phMemory );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanMemoryGetProperties(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanMemory.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hMemory, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory state - health, allocated
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanMemoryGetState(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_state_t* pState                         ///< [in] Will contain the current health and allocated memory.
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanMemory.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hMemory, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory bandwidth
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBandwidth`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zetSysmanMemoryGetBandwidth(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
    )
{
    auto pfnGetBandwidth = zet_lib::context.ddiTable.SysmanMemory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetBandwidth( hMemory, pBandwidth );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of Fabric ports in a device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanFabricPortGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_fabric_port_handle_t* phPort         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFabricPortGet = zet_lib::context.ddiTable.Sysman.pfnFabricPortGet;
    if( nullptr == pfnFabricPortGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFabricPortGet( hSysman, pCount, phPort );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFabricPortGetProperties(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_properties_t* pProperties       ///< [in] Will contain properties of the Fabric Port.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPort, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port link type
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLinkType`
ze_result_t __zecall
zetSysmanFabricPortGetLinkType(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
    zet_fabric_link_type_t* pLinkType               ///< [in] Will contain details about the link attached to the Fabric port.
    )
{
    auto pfnGetLinkType = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetLinkType;
    if( nullptr == pfnGetLinkType )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetLinkType( hPort, verbose, pLinkType );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanFabricPortGetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_config_t* pConfig               ///< [in] Will contain configuration of the Fabric Port.
    )
{
    auto pfnGetConfig = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFabricPortSetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    const zet_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    )
{
    auto pfnSetConfig = zet_lib::context.ddiTable.SysmanFabricPort.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port state - status (green/yellow/red/black), reasons for
///        link degradation or instability, current rx/tx speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanFabricPortGetState(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_state_t* pState                 ///< [in] Will contain the current state of the Fabric Port
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPort, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThroughput`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t __zecall
zetSysmanFabricPortGetThroughput(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_throughput_t* pThroughput       ///< [in] Will contain the Fabric port throughput counters and maximum
                                                    ///< bandwidth.
    )
{
    auto pfnGetThroughput = zet_lib::context.ddiTable.SysmanFabricPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetThroughput( hPort, pThroughput );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of temperature sensors
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanTemperatureGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnTemperatureGet = zet_lib::context.ddiTable.Sysman.pfnTemperatureGet;
    if( nullptr == pfnTemperatureGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnTemperatureGet( hSysman, pCount, phTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanTemperatureGetProperties(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanTemperature.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hTemperature, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature configuration for this sensor - which events are
///        triggered and the trigger conditions
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally this is only supported for temperature sensor ::ZET_TEMP_SENSORS_GLOBAL
///         + One or both of the thresholds is not supported - check ::zet_temp_properties_t.isThreshold1Supported and ::zet_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t __zecall
zetSysmanTemperatureGetConfig(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zet_temp_config_t* pConfig                      ///< [in] Returns current configuration.
    )
{
    auto pfnGetConfig = zet_lib::context.ddiTable.SysmanTemperature.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature configuration for this sensor - indicates which events
///        are triggered and the trigger conditions
/// 
/// @details
///     - Events ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL will be triggered when
///       temperature reaches the critical range. Use the function
///       ::zetSysmanEventSetConfig() to start receiving this event.
///     - Events ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 and
///       ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 will be generated when
///       temperature cross the thresholds set using this function. Use the
///       function ::zetSysmanEventSetConfig() to start receiving these events.
///     - Only one running process can set the temperature configuration at a
///       time. If another process attempts to change the configuration, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zetSysmanTemperatureGetConfig() will return the process ID currently
///       controlling these settings.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally they are only supported for temperature sensor ::ZET_TEMP_SENSORS_GLOBAL
///         + Enabling the critical temperature event is not supported - check ::zet_temp_properties_t.isCriticalTempSupported
///         + One or both of the thresholds is not supported - check ::zet_temp_properties_t.isThreshold1Supported and ::zet_temp_properties_t.isThreshold2Supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or both the thresholds is above TjMax (see ::zetSysmanFrequencyOcGetTjMax()). Temperature thresholds must be below this value.
ze_result_t __zecall
zetSysmanTemperatureSetConfig(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    const zet_temp_config_t* pConfig                ///< [in] New configuration.
    )
{
    auto pfnSetConfig = zet_lib::context.ddiTable.SysmanTemperature.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the temperature from a specified sensor
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTemperature`
ze_result_t __zecall
zetSysmanTemperatureGetState(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    double* pTemperature                            ///< [in] Will contain the temperature read from the specified sensor in
                                                    ///< degrees Celcius.
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanTemperature.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hTemperature, pTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power supplies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanPsuGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnPsuGet = zet_lib::context.ddiTable.Sysman.pfnPsuGet;
    if( nullptr == pfnPsuGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnPsuGet( hSysman, pCount, phPsu );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power supply properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanPsuGetProperties(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanPsu.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hPsu, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current power supply state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanPsuGetState(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanPsu.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hPsu, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of fans
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanFanGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnFanGet = zet_lib::context.ddiTable.Sysman.pfnFanGet;
    if( nullptr == pfnFanGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnFanGet( hSysman, pCount, phFan );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanFanGetProperties(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanFan.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hFan, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current fan configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanFanGetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
    )
{
    auto pfnGetConfig = zet_lib::context.ddiTable.SysmanFan.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set fan configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanFanSetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
    )
{
    auto pfnSetConfig = zet_lib::context.ddiTable.SysmanFan.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a fan - current mode and speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + units
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSpeed`
ze_result_t __zecall
zetSysmanFanGetState(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    uint32_t* pSpeed                                ///< [in] Will contain the current speed of the fan in the units requested.
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanFan.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hFan, units, pSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of LEDs
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanLedGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnLedGet = zet_lib::context.ddiTable.Sysman.pfnLedGet;
    if( nullptr == pfnLedGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnLedGet( hSysman, pCount, phLed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanLedGetProperties(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanLed.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hLed, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t __zecall
zetSysmanLedGetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanLed.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t __zecall
zetSysmanLedSetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    const zet_led_state_t* pState                   ///< [in] New state of the LED.
    )
{
    auto pfnSetState = zet_lib::context.ddiTable.SysmanLed.pfnSetState;
    if( nullptr == pfnSetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of all RAS error sets on a device
/// 
/// @details
///     - A RAS error set is a collection of RAS error counters of a given type
///       (correctable/uncorrectable) from hardware blocks contained within a
///       sub-device or within the device.
///     - A device without sub-devices will typically return two handles, one
///       for correctable errors sets and one for uncorrectable error sets.
///     - A device with sub-devices will return RAS error sets for each
///       sub-device and possibly RAS error sets for hardware blocks outside the
///       sub-devices.
///     - If the function completes successfully but pCount is set to 0, RAS
///       features are not available/enabled on this device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanRasGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnRasGet = zet_lib::context.ddiTable.Sysman.pfnRasGet;
    if( nullptr == pfnRasGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnRasGet( hSysman, pCount, phRas );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS properties of a given RAS error set - this enables discovery
///        of the type of RAS error set (correctable/uncorrectable) and if
///        located on a sub-device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanRasGetProperties(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanRas.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hRas, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the configured
///       threshold, the event ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
///       will be triggered.
///     - When a particular RAS uncorrectable error counter exceeds the
///       configured threshold, the event
///       ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be triggered.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanRasGetConfig(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zet_ras_config_t* pConfig                       ///< [in] Will be populed with the current RAS configuration - thresholds
                                                    ///< used to trigger events
    )
{
    auto pfnGetConfig = zet_lib::context.ddiTable.SysmanRas.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the specified
///       threshold, the event ::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS
///       will be generated.
///     - When a particular RAS uncorrectable error counter exceeds the
///       specified threshold, the event
///       ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS will be generated.
///     - Call ::zetSysmanRasGetState() and set the clear flag to true to
///       restart event generation once counters have exceeded thresholds.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to set thresholds.
ze_result_t __zecall
zetSysmanRasSetConfig(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    const zet_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    )
{
    auto pfnSetConfig = zet_lib::context.ddiTable.SysmanRas.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current value of RAS error counters for a particular error set
/// 
/// @details
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTotalErrors`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t __zecall
zetSysmanRasGetState(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
    zet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanRas.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hRas, clear, pTotalErrors, pDetails );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the event handle for the specified device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvent`
ze_result_t __zecall
zetSysmanEventGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    zet_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
    )
{
    auto pfnEventGet = zet_lib::context.ddiTable.Sysman.pfnEventGet;
    if( nullptr == pfnEventGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnEventGet( hSysman, phEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find out which events are currently registered on the specified device
///        event handler
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanEventGetConfig(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    zet_event_config_t* pConfig                     ///< [in] Will contain the current event configuration (list of registered
                                                    ///< events).
    )
{
    auto pfnGetConfig = zet_lib::context.ddiTable.SysmanEvent.pfnGetConfig;
    if( nullptr == pfnGetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetConfig( hEvent, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set a new event configuration (list of registered events) on the
///        specified device event handler
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t __zecall
zetSysmanEventSetConfig(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    const zet_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
    )
{
    auto pfnSetConfig = zet_lib::context.ddiTable.SysmanEvent.pfnSetConfig;
    if( nullptr == pfnSetConfig )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnSetConfig( hEvent, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get events that have been triggered for a specific device
/// 
/// @details
///     - If events have occurred on the specified device event handle, they are
///       returned and the corresponding event status is cleared if the argument
///       clear = true.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEvents`
ze_result_t __zecall
zetSysmanEventGetState(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device.
    ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
    uint32_t* pEvents                               ///< [in] Bitfield of events ::zet_sysman_event_type_t that have been
                                                    ///< triggered by this device.
    )
{
    auto pfnGetState = zet_lib::context.ddiTable.SysmanEvent.pfnGetState;
    if( nullptr == pfnGetState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetState( hEvent, clear, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for the specified list of event handles to receive any registered
///        events
/// 
/// @details
///     - If previous events arrived and were not cleared using
///       ::zetSysmanEventGetState(), this call will return immediately.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied event handles are for devices that belong to a different driver handle.
ze_result_t __zecall
zetSysmanEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                    ///< ::ZET_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                    ///< ::ZET_EVENT_WAIT_INFINITE to block until events arrive.
    uint32_t count,                                 ///< [in] Number of handles in phEvents
    zet_sysman_event_handle_t* phEvents,            ///< [in][range(0, count)] Handle of events that should be listened to
    uint32_t* pEvents                               ///< [in] Bitfield of events ::zet_sysman_event_type_t that have been
                                                    ///< triggered by any of the supplied event handles. If timeout is not
                                                    ///< ::ZET_EVENT_WAIT_INFINITE and this value is
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
    )
{
    auto pfnListen = zet_lib::context.ddiTable.SysmanEvent.pfnListen;
    if( nullptr == pfnListen )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnListen( hDriver, timeout, count, phEvents, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of diagnostics test suites
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSysman`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanDiagnosticsGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of components of this type.
                                                    ///< if count is non-zero, then driver will only retrieve that number of components.
                                                    ///< if count is larger than the number of components available, then the
                                                    ///< driver will update the value with the correct number of components
                                                    ///< that are returned.
    zet_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type
    )
{
    auto pfnDiagnosticsGet = zet_lib::context.ddiTable.Sysman.pfnDiagnosticsGet;
    if( nullptr == pfnDiagnosticsGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a diagnostics test suite
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t __zecall
zetSysmanDiagnosticsGetProperties(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    zet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
    )
{
    auto pfnGetProperties = zet_lib::context.ddiTable.SysmanDiagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetProperties( hDiagnostics, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get individual tests that can be run separately. Not all test suites
///        permit running individual tests - check
///        ::zet_diag_properties_t.haveTests
/// 
/// @details
///     - The list of available tests is returned in order of increasing test
///       index ::zet_diag_test_t.index.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t __zecall
zetSysmanDiagnosticsGetTests(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                    ///< If count is zero, then the driver will update the value with the total
                                                    ///< number of tests available.
                                                    ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                    ///< If count is larger than the number of tests available, then the driver
                                                    ///< will update the value with the correct number of tests available.
    zet_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                    ///< increasing value of ::zet_diag_test_t.index
    )
{
    auto pfnGetTests = zet_lib::context.ddiTable.SysmanDiagnostics.pfnGetTests;
    if( nullptr == pfnGetTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetTests( hDiagnostics, pCount, pTests );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - To run all tests in a test suite, set start =
///       ::ZET_DIAG_FIRST_TEST_INDEX and end = ::ZET_DIAG_LAST_TEST_INDEX.
///     - If the test suite permits running individual tests,
///       ::zet_diag_properties_t.haveTests will be true. In this case, the
///       function ::zetSysmanDiagnosticsGetTests() can be called to get the
///       list of tests and corresponding indices that can be supplied to the
///       arguments start and end in this function.
///     - This function will block until the diagnostics have completed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pResult`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform diagnostics.
ze_result_t __zecall
zetSysmanDiagnosticsRunTests(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
    )
{
    auto pfnRunTests = zet_lib::context.ddiTable.SysmanDiagnostics.pfnRunTests;
    if( nullptr == pfnRunTests )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnRunTests( hDiagnostics, start, end, pResult );
}

} // extern "C"
