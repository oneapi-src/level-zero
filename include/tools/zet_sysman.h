/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_sysman.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for System Resource Management (Sysman)
 *
 */
 
#ifndef _ZET_SYSMAN_H
#define _ZET_SYSMAN_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of Sysman
typedef enum _zet_sysman_version_t
{
    ZET_SYSMAN_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

} zet_sysman_version_t;

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
__ze_api_export ze_result_t __zecall
zetSysmanGet(
    zet_device_handle_t hDevice,                    ///< [in] Handle of the device
    zet_sysman_version_t version,                   ///< [in] Sysman version that application was built with
    zet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing Sysman features
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define ZET_STRING_PROPERTY_SIZE  64
#endif // ZET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Types of accelerator engines
typedef enum _zet_engine_type_t
{
    ZET_ENGINE_TYPE_OTHER = 0,                      ///< Undefined types of accelerators.
    ZET_ENGINE_TYPE_COMPUTE,                        ///< Engines that process compute kernels.
    ZET_ENGINE_TYPE_3D,                             ///< Engines that process 3D content
    ZET_ENGINE_TYPE_MEDIA,                          ///< Engines that process media workloads
    ZET_ENGINE_TYPE_DMA,                            ///< Engines that copy blocks of data

} zet_engine_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties
typedef struct _zet_sysman_properties_t
{
    ze_device_properties_t core;                    ///< [out] Core device properties
    uint32_t numSubdevices;                         ///< [out] Number of sub-devices
    int8_t serialNumber[ZET_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
    int8_t boardNumber[ZET_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
    int8_t brandName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
    int8_t modelName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
    int8_t vendorName[ZET_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
    int8_t driverVersion[ZET_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)

} zet_sysman_properties_t;

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
__ze_api_export ze_result_t __zecall
zetSysmanDeviceGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sysman_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Scheduler mode
typedef enum _zet_sched_mode_t
{
    ZET_SCHED_MODE_TIMEOUT = 0,                     ///< Multiple applications or contexts are submitting work to the hardware.
                                                    ///< When higher priority work arrives, the scheduler attempts to pause the
                                                    ///< current executing work within some timeout interval, then submits the
                                                    ///< other work.
    ZET_SCHED_MODE_TIMESLICE,                       ///< The scheduler attempts to fairly timeslice hardware execution time
                                                    ///< between multiple contexts submitting work to the hardware
                                                    ///< concurrently.
    ZET_SCHED_MODE_EXCLUSIVE,                       ///< Any application or context can run indefinitely on the hardware
                                                    ///< without being preempted or terminated. All pending work for other
                                                    ///< contexts must wait until the running context completes with no further
                                                    ///< submitted work.
    ZET_SCHED_MODE_COMPUTE_UNIT_DEBUG,              ///< Scheduler ensures that submission of workloads to the hardware is
                                                    ///< optimized for compute unit debugging.

} zet_sched_mode_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_SCHED_WATCHDOG_DISABLE
/// @brief Disable forward progress guard timeout.
#define ZET_SCHED_WATCHDOG_DISABLE  (~(0ULL))
#endif // ZET_SCHED_WATCHDOG_DISABLE

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for timeout scheduler mode (::ZET_SCHED_MODE_TIMEOUT)
typedef struct _zet_sched_timeout_properties_t
{
    uint64_t watchdogTimeout;                       ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< for a batch of work submitted to a hardware engine to complete or to
                                                    ///< be preempted so as to run another context.
                                                    ///< If this time is exceeded, the hardware engine is reset and the context terminated.
                                                    ///< If set to ::ZET_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                    ///< long as it wants without being terminated, but preemption attempts to
                                                    ///< run other contexts are permitted but not enforced.

} zet_sched_timeout_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Configuration for timeslice scheduler mode
///        (::ZET_SCHED_MODE_TIMESLICE)
typedef struct _zet_sched_timeslice_properties_t
{
    uint64_t interval;                              ///< [in,out] The average interval in microseconds that a submission for a
                                                    ///< context will run on a hardware engine before being preempted out to
                                                    ///< run a pending submission for another context.
    uint64_t yieldTimeout;                          ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                    ///< to preempt a workload running on an engine before deciding to reset
                                                    ///< the hardware engine and terminating the associated context.

} zet_sched_timeslice_properties_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanSchedulerGetCurrentMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanSchedulerGetTimeoutModeProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanSchedulerGetTimesliceModeProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zet_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanSchedulerSetTimeoutMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanSchedulerSetTimesliceMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanSchedulerSetExclusiveMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanSchedulerSetComputeUnitDebugMode(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                    ///< scheduler mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Workload performance profiles
typedef enum _zet_perf_profile_t
{
    ZET_PERF_PROFILE_BALANCED = 0,                  ///< The hardware is configured to strike a balance between compute and
                                                    ///< memory resources. This is the default profile when the device
                                                    ///< boots/resets.
    ZET_PERF_PROFILE_COMPUTE_BOUNDED,               ///< The hardware is configured to prioritize performance of the compute
                                                    ///< units.
    ZET_PERF_PROFILE_MEMORY_BOUNDED,                ///< The hardware is configured to prioritize memory throughput.

} zet_perf_profile_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPerformanceProfileGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_perf_profile_t* pProfile                    ///< [in,out] The performance profile currently loaded.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPerformanceProfileSet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_perf_profile_t profile                      ///< [in] The performance profile to load.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Contains information about a process that has an open connection with
///        this device
/// 
/// @details
///     - The application can use the process ID to query the OS for the owner
///       and the path to the executable.
typedef struct _zet_process_state_t
{
    uint32_t processId;                             ///< [out] Host OS process ID.
    int64_t memSize;                                ///< [out] Device memory size in bytes allocated by this process (may not
                                                    ///< necessarily be resident on the device at the time of reading).
    int64_t engines;                                ///< [out] Bitfield of accelerator engines being used by this process (or
                                                    ///< 1<<::zet_engine_type_t together).

} zet_process_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about host processes using the device
/// 
/// @details
///     - The number of processes connected to the device is dynamic. This means
///       that between a call to determine the correct value of pCount and the
///       subsequent call, the number of processes may have increased. It is
///       recommended that a large array be passed in so as to avoid receiving
///       the error ::ZE_RESULT_ERROR_INVALID_SIZE.
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
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The provided value of pCount is not big enough to store information about all the processes currently attached to the device.
__ze_api_export ze_result_t __zecall
zetSysmanProcessesGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of processes currently using the device.
                                                    ///< if count is non-zero but less than the number of processes, the driver
                                                    ///< will set to the number of processes currently using the device and
                                                    ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                    ///< if count is larger than the number of processes, then the driver will
                                                    ///< update the value with the correct number of processes that are returned.
    zet_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                    ///< one for each process currently using the device
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanDeviceReset(
    zet_sysman_handle_t hSysman                     ///< [in] Sysman handle for the device
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Device repair status
typedef enum _zet_repair_status_t
{
    ZET_REPAIR_STATUS_UNSUPPORTED = 0,              ///< The device does not support in-field repairs.
    ZET_REPAIR_STATUS_NOT_PERFORMED,                ///< The device has never been repaired.
    ZET_REPAIR_STATUS_PERFORMED,                    ///< The device has been repaired.

} zet_repair_status_t;

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
__ze_api_export ze_result_t __zecall
zetSysmanDeviceGetRepairStatus(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    zet_repair_status_t* pRepairStatus              ///< [in,out] Will indicate if the device was repaired
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI address
typedef struct _zet_pci_address_t
{
    uint32_t domain;                                ///< [out] BDF domain
    uint32_t bus;                                   ///< [out] BDF bus
    uint32_t device;                                ///< [out] BDF device
    uint32_t function;                              ///< [out] BDF function

} zet_pci_address_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI speed
typedef struct _zet_pci_speed_t
{
    uint32_t gen;                                   ///< [out] The link generation
    uint32_t width;                                 ///< [out] The number of lanes
    uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

} zet_pci_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static PCI properties
typedef struct _zet_pci_properties_t
{
    zet_pci_address_t address;                      ///< [out] The BDF address
    zet_pci_speed_t maxSpeed;                       ///< [out] Fastest port configuration supported by the device.

} zet_pci_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI link status
typedef enum _zet_pci_link_status_t
{
    ZET_PCI_LINK_STATUS_GREEN = 0,                  ///< The link is up and operating as expected
    ZET_PCI_LINK_STATUS_YELLOW,                     ///< The link is up but has quality and/or bandwidth degradation
    ZET_PCI_LINK_STATUS_RED,                        ///< The link has stability issues and preventing workloads making forward
                                                    ///< progress

} zet_pci_link_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI link quality degradation reasons
typedef enum _zet_pci_link_qual_issues_t
{
    ZET_PCI_LINK_QUAL_ISSUES_NONE = 0,              ///< There are no quality issues with the link at this time
    ZET_PCI_LINK_QUAL_ISSUES_REPLAYS = ZE_BIT( 0 ), ///< An significant number of replays are occurring
    ZET_PCI_LINK_QUAL_ISSUES_SPEED = ZE_BIT( 1 ),   ///< There is a degradation in the maximum bandwidth of the link

} zet_pci_link_qual_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI link stability issues
typedef enum _zet_pci_link_stab_issues_t
{
    ZET_PCI_LINK_STAB_ISSUES_NONE = 0,              ///< There are no connection stability issues at this time
    ZET_PCI_LINK_STAB_ISSUES_RETRAINING = ZE_BIT( 0 ),  ///< Link retraining has occurred to deal with quality issues

} zet_pci_link_stab_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic PCI state
typedef struct _zet_pci_state_t
{
    zet_pci_link_status_t status;                   ///< [out] The current status of the port
    zet_pci_link_qual_issues_t qualityIssues;       ///< [out] If status is ::ZET_PCI_LINK_STATUS_YELLOW, this gives a bitfield
                                                    ///< of quality issues that have been detected
    zet_pci_link_stab_issues_t stabilityIssues;     ///< [out] If status is ::ZET_PCI_LINK_STATUS_RED, this gives a bitfield of
                                                    ///< reasons for the connection instability
    zet_pci_speed_t speed;                          ///< [out] The current port configure speed

} zet_pci_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI bar types
typedef enum _zet_pci_bar_type_t
{
    ZET_PCI_BAR_TYPE_CONFIG = 0,                    ///< PCI configuration space
    ZET_PCI_BAR_TYPE_MMIO,                          ///< MMIO registers
    ZET_PCI_BAR_TYPE_VRAM,                          ///< VRAM aperture
    ZET_PCI_BAR_TYPE_ROM,                           ///< ROM aperture
    ZET_PCI_BAR_TYPE_VGA_IO,                        ///< Legacy VGA IO ports
    ZET_PCI_BAR_TYPE_VGA_MEM,                       ///< Legacy VGA memory
    ZET_PCI_BAR_TYPE_INDIRECT_IO,                   ///< Indirect IO port access
    ZET_PCI_BAR_TYPE_INDIRECT_MEM,                  ///< Indirect memory access
    ZET_PCI_BAR_TYPE_OTHER,                         ///< Other type of PCI bar

} zet_pci_bar_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Properties of a pci bar
typedef struct _zet_pci_bar_properties_t
{
    zet_pci_bar_type_t type;                        ///< [out] The type of bar
    uint32_t index;                                 ///< [out] The index of the bar
    uint64_t base;                                  ///< [out] Base address of the bar.
    uint64_t size;                                  ///< [out] Size of the bar.

} zet_pci_bar_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief PCI stats counters
/// 
/// @details
///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.rxCounter - s1.rxCounter) +
///       (s2.txCounter - s1.txCounter)) / (s2.maxBandwidth * (s2.timestamp -
///       s1.timestamp))
///     - Percent replays is calculated by taking two snapshots (s1, s2) and
///       using the equation: %replay = 10^6 * (s2.replayCounter -
///       s1.replayCounter) / (s2.maxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _zet_pci_stats_t
{
    uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when the measurement
                                                    ///< was made.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.
    uint64_t replayCounter;                         ///< [out] Monotonic counter for the number of replay packets
    uint64_t packetCounter;                         ///< [out] Monotonic counter for the number of packets
    uint64_t rxCounter;                             ///< [out] Monotonic counter for the number of bytes received
    uint64_t txCounter;                             ///< [out] Monotonic counter for the number of bytes transmitted (including
                                                    ///< replays)
    uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec under the current
                                                    ///< configuration

} zet_pci_stats_t;

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
__ze_api_export ze_result_t __zecall
zetSysmanPciGetProperties(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPciGetState(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPciGetBars(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of bars.
                                                    ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                    ///< if count is larger than the number of bar, then the driver will update
                                                    ///< the value with the correct number of bars that are returned.
    zet_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of bar properties
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPciGetStats(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
    zet_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Properties related to device power settings
typedef struct _zet_power_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Software can change the power limits of this domain assuming the
                                                    ///< user has permissions.
    ze_bool_t isEnergyThresholdSupported;           ///< [out] Indicates if this power domain supports the energy threshold
                                                    ///< event (::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED).
    uint32_t maxLimit;                              ///< [out] The maximum power limit in milliwatts that can be requested.

} zet_power_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy counter snapshot
/// 
/// @details
///     - Average power is calculated by taking two snapshots (s1, s2) and using
///       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
///       s1.timestamp)
typedef struct _zet_power_energy_counter_t
{
    uint64_t energy;                                ///< [out] The monotonic energy counter in microjoules.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when energy was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zet_power_energy_counter_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sustained power limits
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency if
///       the power averaged over a window (typically seconds) exceeds this
///       limit.
typedef struct _zet_power_sustained_limit_t
{
    ze_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts
    uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

} zet_power_sustained_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Burst power limit
/// 
/// @details
///     - The power controller (Punit) will throttle the operating frequency of
///       the device if the power averaged over a few milliseconds exceeds a
///       limit known as PL2. Typically PL2 > PL1 so that it permits the
///       frequency to burst higher for short periods than would be otherwise
///       permitted by PL1.
typedef struct _zet_power_burst_limit_t
{
    ze_bool_t enabled;                              ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
    uint32_t power;                                 ///< [in,out] power limit in milliwatts

} zet_power_burst_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Peak power limit
/// 
/// @details
///     - The power controller (Punit) will preemptively throttle the operating
///       frequency of the device when the instantaneous power exceeds this
///       limit. The limit is known as PL4. It expresses the maximum power that
///       can be drawn from the power supply.
///     - If this power limit is removed or set too high, the power supply will
///       generate an interrupt when it detects an overcurrent condition and the
///       power controller will throttle the device frequencies down to min. It
///       is thus better to tune the PL4 value in order to avoid such
///       excursions.
typedef struct _zet_power_peak_limit_t
{
    uint32_t powerAC;                               ///< [in,out] power limit in milliwatts for the AC power source.
    uint32_t powerDC;                               ///< [in,out] power limit in milliwatts for the DC power source. This is
                                                    ///< ignored if the product does not have a battery.

} zet_power_peak_limit_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Energy threshold
/// 
/// @details
///     - .
typedef struct _zet_energy_threshold_t
{
    ze_bool_t enable;                               ///< [in,out] Indicates if the energy threshold is enabled.
    double threshold;                               ///< [in,out] The energy threshold in Joules. Will be 0.0 if no threshold
                                                    ///< has been set.
    uint32_t processId;                             ///< [in,out] The host process ID that set the energy threshold. Will be
                                                    ///< 0xFFFFFFFF if no threshold has been set.

} zet_energy_threshold_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPowerGetProperties(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPowerGetEnergyCounter(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPowerGetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit.
    zet_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit.
    zet_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPowerSetLimits(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    const zet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
    const zet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
    const zet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPowerGetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    zet_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPowerSetEnergyThreshold(
    zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency domains.
typedef enum _zet_freq_domain_t
{
    ZET_FREQ_DOMAIN_GPU = 0,                        ///< GPU Core Domain.
    ZET_FREQ_DOMAIN_MEMORY,                         ///< Local Memory Domain.

} zet_freq_domain_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency properties
/// 
/// @details
///     - Indicates if this frequency domain can be overclocked (if true,
///       functions such as ::zetSysmanFrequencyOcSetConfig() are supported).
///     - The min/max hardware frequencies are specified for non-overclock
///       configurations. For overclock configurations, use
///       ::zetSysmanFrequencyOcGetConfig() to determine the maximum frequency
///       that can be requested.
///     - If step is non-zero, the available frequencies are (min, min + step,
///       min + 2xstep, ..., max). Otherwise, call
///       ::zetSysmanFrequencyGetAvailableClocks() to get the list of
///       frequencies that can be requested.
typedef struct _zet_freq_properties_t
{
    zet_freq_domain_t type;                         ///< [out] The hardware block that this frequency domain controls (GPU,
                                                    ///< memory, ...)
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the frequency of this domain
                                                    ///< assuming the user has permissions
    ze_bool_t isThrottleEventSupported;             ///< [out] Indicates if software can register to receive event
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED
    double min;                                     ///< [out] The minimum hardware clock frequency in units of MHz
    double max;                                     ///< [out] The maximum non-overclock hardware clock frequency in units of
                                                    ///< MHz.
    double step;                                    ///< [out] The minimum step-size for clock frequencies in units of MHz. The
                                                    ///< hardware will clamp intermediate frequencies to lowest multiplier of
                                                    ///< this number.

} zet_freq_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency range between which the hardware can operate.
typedef struct _zet_freq_range_t
{
    double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.
    double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                    ///< management will not request frequencies. Setting to 0 will use the
                                                    ///< hardware default value.

} zet_freq_range_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle reasons
typedef enum _zet_freq_throttle_reasons_t
{
    ZET_FREQ_THROTTLE_REASONS_NONE = 0,             ///< frequency not throttled
    ZET_FREQ_THROTTLE_REASONS_AVE_PWR_CAP = ZE_BIT( 0 ),///< frequency throttled due to average power excursion (PL1)
    ZET_FREQ_THROTTLE_REASONS_BURST_PWR_CAP = ZE_BIT( 1 ),  ///< frequency throttled due to burst power excursion (PL2)
    ZET_FREQ_THROTTLE_REASONS_CURRENT_LIMIT = ZE_BIT( 2 ),  ///< frequency throttled due to current excursion (PL4)
    ZET_FREQ_THROTTLE_REASONS_THERMAL_LIMIT = ZE_BIT( 3 ),  ///< frequency throttled due to thermal excursion (T > TjMax)
    ZET_FREQ_THROTTLE_REASONS_PSU_ALERT = ZE_BIT( 4 ),  ///< frequency throttled due to power supply assertion
    ZET_FREQ_THROTTLE_REASONS_SW_RANGE = ZE_BIT( 5 ),   ///< frequency throttled due to software supplied frequency range
    ZET_FREQ_THROTTLE_REASONS_HW_RANGE = ZE_BIT( 6 ),   ///< frequency throttled due to a sub block that has a lower frequency
                                                    ///< range when it receives clocks

} zet_freq_throttle_reasons_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency state
typedef struct _zet_freq_state_t
{
    double request;                                 ///< [out] The current frequency request in MHz.
    double tdp;                                     ///< [out] The maximum frequency in MHz supported under the current TDP
                                                    ///< conditions
    double efficient;                               ///< [out] The efficient minimum frequency in MHz
    double actual;                                  ///< [out] The resolved frequency in MHz
    uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the hardware
                                                    ///< (Bitfield of ::zet_freq_throttle_reasons_t).

} zet_freq_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Frequency throttle time snapshot
/// 
/// @details
///     - Percent time throttled is calculated by taking two snapshots (s1, s2)
///       and using the equation: %throttled = (s2.throttleTime -
///       s1.throttleTime) / (s2.timestamp - s1.timestamp)
typedef struct _zet_freq_throttle_time_t
{
    uint64_t throttleTime;                          ///< [out] The monotonic counter of time in microseconds that the frequency
                                                    ///< has been limited by the hardware.
    uint64_t timestamp;                             ///< [out] Microsecond timestamp when throttleTime was captured.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zet_freq_throttle_time_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking modes
typedef enum _zet_oc_mode_t
{
    ZET_OC_MODE_OFF = 0,                            ///< Overclocking if off - hardware is running using factory default
                                                    ///< voltages/frequencies.
    ZET_OC_MODE_OVERRIDE,                           ///< Overclock override mode - In this mode, a fixed user-supplied voltage
                                                    ///< is applied independent of the frequency request. The maximum permitted
                                                    ///< frequency can also be increased.
    ZET_OC_MODE_INTERPOLATIVE,                      ///< Overclock interpolative mode - In this mode, the voltage/frequency
                                                    ///< curve can be extended with a new voltage/frequency point that will be
                                                    ///< interpolated. The existing voltage/frequency points can also be offset
                                                    ///< (up or down) by a fixed voltage.

} zet_oc_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking properties
/// 
/// @details
///     - Provides all the overclocking capabilities and properties supported by
///       the device for the frequency domain.
typedef struct _zet_oc_capabilities_t
{
    ze_bool_t isOcSupported;                        ///< [out] Indicates if any overclocking features are supported on this
                                                    ///< frequency domain.
    double maxFactoryDefaultFrequency;              ///< [out] Factory default non-overclock maximum frequency in Mhz.
    double maxFactoryDefaultVoltage;                ///< [out] Factory default voltage used for the non-overclock maximum
                                                    ///< frequency in MHz.
    double maxOcFrequency;                          ///< [out] Maximum hardware overclocking frequency limit in Mhz.
    double minOcVoltageOffset;                      ///< [out] The minimum voltage offset that can be applied to the
                                                    ///< voltage/frequency curve. Note that this number can be negative.
    double maxOcVoltageOffset;                      ///< [out] The maximum voltage offset that can be applied to the
                                                    ///< voltage/frequency curve.
    double maxOcVoltage;                            ///< [out] The maximum overclock voltage that hardware supports.
    ze_bool_t isTjMaxSupported;                     ///< [out] Indicates if the maximum temperature limit (TjMax) can be
                                                    ///< changed for this frequency domain.
    ze_bool_t isIccMaxSupported;                    ///< [out] Indicates if the maximum current (IccMax) can be changed for
                                                    ///< this frequency domain.
    ze_bool_t isHighVoltModeCapable;                ///< [out] Indicates if this frequency domains supports a feature to set
                                                    ///< very high voltages.
    ze_bool_t isHighVoltModeEnabled;                ///< [out] Indicates if very high voltages are permitted on this frequency
                                                    ///< domain.

} zet_oc_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Overclocking configuration
/// 
/// @details
///     - Overclock settings
typedef struct _zet_oc_config_t
{
    zet_oc_mode_t mode;                             ///< [in,out] Overclock Mode ::zet_oc_mode_t.
    double frequency;                               ///< [in,out] Overclocking Frequency in MHz. This cannot be greater than
                                                    ///< ::zet_oc_capabilities_t.maxOcFrequency.
    double voltageTarget;                           ///< [in,out] Overclock voltage in Volts. This cannot be greater than
                                                    ///< ::zet_oc_capabilities_t.maxOcVoltage.
    double voltageOffset;                           ///< [in,out] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                    ///< can be in the range (::zet_oc_capabilities_t.minOcVoltageOffset,
                                                    ///< ::zet_oc_capabilities_t.maxOcVoltageOffset).

} zet_oc_config_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyGetProperties(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
    );

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyGetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                    ///< specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencySetRange(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    const zet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyGetState(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyGetThrottleTime(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyOcGetCapabilities(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                    ///< ::zet_oc_capabilities_t.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyOcGetConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_config_t* pOcConfiguration               ///< [in,out] Pointer to the configuration structure ::zet_oc_config_t.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyOcSetConfig(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    zet_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
    ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                    ///< in order to enable the new overclock settings.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyOcGetIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                    ///< successful return.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyOcSetIccMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyOcGetTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                    ///< on successful return.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFrequencyOcSetTjMax(
    zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Accelerator engine groups
typedef enum _zet_engine_group_t
{
    ZET_ENGINE_GROUP_ALL = 0,                       ///< Access information about all engines combined.
    ZET_ENGINE_GROUP_COMPUTE_ALL,                   ///< Access information about all compute engines combined.
    ZET_ENGINE_GROUP_MEDIA_ALL,                     ///< Access information about all media engines combined.
    ZET_ENGINE_GROUP_COPY_ALL,                      ///< Access information about all copy (blitter) engines combined.

} zet_engine_group_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine group properties
typedef struct _zet_engine_properties_t
{
    zet_engine_group_t type;                        ///< [out] The engine group
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zet_engine_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Engine activity counters
/// 
/// @details
///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
///       using the equation: %util = (s2.activeTime - s1.activeTime) /
///       (s2.timestamp - s1.timestamp)
typedef struct _zet_engine_stats_t
{
    uint64_t activeTime;                            ///< [out] Monotonic counter for time in microseconds that this resource is
                                                    ///< actively running workloads.
    uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when activeTime
                                                    ///< counter was sampled.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zet_engine_stats_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanEngineGetProperties(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanEngineGetActivity(
    zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
    zet_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                    ///< counters.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware components
typedef enum _zet_standby_type_t
{
    ZET_STANDBY_TYPE_GLOBAL = 0,                    ///< Control the overall standby policy of the device/sub-device

} zet_standby_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby hardware component properties
typedef struct _zet_standby_properties_t
{
    zet_standby_type_t type;                        ///< [out] Which standby hardware component this controls
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zet_standby_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Standby promotion modes
typedef enum _zet_standby_promo_mode_t
{
    ZET_STANDBY_PROMO_MODE_DEFAULT = 0,             ///< Best compromise between performance and energy savings.
    ZET_STANDBY_PROMO_MODE_NEVER,                   ///< The device/component will never shutdown. This can improve performance
                                                    ///< but uses more energy.

} zet_standby_promo_mode_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanStandbyGetProperties(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanStandbyGetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanStandbySetMode(
    zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
    zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Firmware properties
typedef struct _zet_firmware_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can flash the firmware assuming the user
                                                    ///< has permissions
    int8_t name[ZET_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
    int8_t version[ZET_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

} zet_firmware_properties_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFirmwareGetProperties(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    zet_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                    ///< firmware
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFirmwareGetChecksum(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFirmwareFlash(
    zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory module types
typedef enum _zet_mem_type_t
{
    ZET_MEM_TYPE_HBM = 0,                           ///< HBM memory
    ZET_MEM_TYPE_DDR,                               ///< DDR memory
    ZET_MEM_TYPE_SRAM,                              ///< SRAM memory
    ZET_MEM_TYPE_L1,                                ///< L1 cache
    ZET_MEM_TYPE_L3,                                ///< L3 cache
    ZET_MEM_TYPE_GRF,                               ///< Execution unit register file
    ZET_MEM_TYPE_SLM,                               ///< Execution unit shared local memory

} zet_mem_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory health
typedef enum _zet_mem_health_t
{
    ZET_MEM_HEALTH_OK = 0,                          ///< All memory channels are healthy
    ZET_MEM_HEALTH_DEGRADED,                        ///< Excessive correctable errors have been detected on one or more
                                                    ///< channels. Device should be reset.
    ZET_MEM_HEALTH_CRITICAL,                        ///< Operating with reduced memory to cover banks with too many
                                                    ///< uncorrectable errors.
    ZET_MEM_HEALTH_REPLACE,                         ///< Device should be replaced due to excessive uncorrectable errors.

} zet_mem_health_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory properties
typedef struct _zet_mem_properties_t
{
    zet_mem_type_t type;                            ///< [out] The memory type
    ze_bool_t onSubdevice;                          ///< [out] True if this resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    uint64_t physicalSize;                          ///< [out] Physical memory size in bytes

} zet_mem_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory state - health, allocated
/// 
/// @details
///     - Percent allocation is given by 100 * allocatedSize / maxSize.
///     - Percent free is given by 100 * (maxSize - allocatedSize) / maxSize.
typedef struct _zet_mem_state_t
{
    zet_mem_health_t health;                        ///< [out] Indicates the health of the memory
    uint64_t allocatedSize;                         ///< [out] The total allocated bytes
    uint64_t maxSize;                               ///< [out] The total allocatable memory in bytes (can be less than
                                                    ///< ::zet_mem_properties_t.physicalSize)

} zet_mem_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory bandwidth
/// 
/// @details
///     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
///       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
///       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
///       (s2.timestamp - s1.timestamp))
typedef struct _zet_mem_bandwidth_t
{
    uint64_t readCounter;                           ///< [out] Total bytes read from memory
    uint64_t writeCounter;                          ///< [out] Total bytes written to memory
    uint64_t maxBandwidth;                          ///< [out] Current maximum bandwidth in units of bytes/sec
    uint64_t timestamp;                             ///< [out] The timestamp when these measurements were sampled.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.

} zet_mem_bandwidth_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanMemoryGetProperties(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanMemoryGetState(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanMemoryGetBandwidth(
    zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
    zet_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain a snapshot of the bandwidth counters.
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_FABRIC_PORT_MODEL_SIZE
/// @brief Maximum Fabric port model string size
#define ZET_MAX_FABRIC_PORT_MODEL_SIZE  256
#endif // ZET_MAX_FABRIC_PORT_MODEL_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_FABRIC_PORT_UUID_SIZE
/// @brief Maximum fabric port uuid size in bytes
#define ZET_MAX_FABRIC_PORT_UUID_SIZE  72
#endif // ZET_MAX_FABRIC_PORT_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_FABRIC_LINK_TYPE_SIZE
/// @brief Maximum size of the buffer that will return information about link
///        types
#define ZET_MAX_FABRIC_LINK_TYPE_SIZE  256
#endif // ZET_MAX_FABRIC_LINK_TYPE_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port status
typedef enum _zet_fabric_port_status_t
{
    ZET_FABRIC_PORT_STATUS_GREEN = 0,               ///< The port is up and operating as expected
    ZET_FABRIC_PORT_STATUS_YELLOW,                  ///< The port is up but has quality and/or bandwidth degradation
    ZET_FABRIC_PORT_STATUS_RED,                     ///< Port connection instabilities are preventing workloads making forward
                                                    ///< progress
    ZET_FABRIC_PORT_STATUS_BLACK,                   ///< The port is configured down

} zet_fabric_port_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port quality degradation reasons
typedef enum _zet_fabric_port_qual_issues_t
{
    ZET_FABRIC_PORT_QUAL_ISSUES_NONE = 0,           ///< There are no quality issues with the link at this time
    ZET_FABRIC_PORT_QUAL_ISSUES_FEC = ZE_BIT( 0 ),  ///< Excessive FEC (forward error correction) are occurring
    ZET_FABRIC_PORT_QUAL_ISSUES_LTP_CRC = ZE_BIT( 1 ),  ///< Excessive LTP CRC failure induced replays are occurring
    ZET_FABRIC_PORT_QUAL_ISSUES_SPEED = ZE_BIT( 2 ),///< There is a degradation in the maximum bandwidth of the port

} zet_fabric_port_qual_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port stability issues
typedef enum _zet_fabric_port_stab_issues_t
{
    ZET_FABRIC_PORT_STAB_ISSUES_NONE = 0,           ///< There are no connection stability issues at this time
    ZET_FABRIC_PORT_STAB_ISSUES_TOO_MANY_REPLAYS = ZE_BIT( 0 ), ///< Sequential replay failure is inducing link retraining
    ZET_FABRIC_PORT_STAB_ISSUES_NO_CONNECT = ZE_BIT( 1 ),   ///< A connection was never able to be established through the link
    ZET_FABRIC_PORT_STAB_ISSUES_FLAPPING = ZE_BIT( 2 ), ///< The port is flapping

} zet_fabric_port_stab_issues_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port universal unique id (UUID)
typedef struct _zet_fabric_port_uuid_t
{
    uint8_t id[ZET_MAX_FABRIC_PORT_UUID_SIZE];      ///< [out] Frabric port universal unique id

} zet_fabric_port_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port speed in one direction
typedef struct _zet_fabric_port_speed_t
{
    uint64_t bitRate;                               ///< [out] Bits/sec that the link is operating at
    uint32_t width;                                 ///< [out] The number of lanes
    uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

} zet_fabric_port_speed_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port properties
typedef struct _zet_fabric_port_properties_t
{
    int8_t model[ZET_MAX_FABRIC_PORT_MODEL_SIZE];   ///< [out] Description of port technology
    ze_bool_t onSubdevice;                          ///< [out] True if the port is located on a sub-device; false means that
                                                    ///< the port is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    zet_fabric_port_uuid_t portUuid;                ///< [out] The port universal unique id
    zet_fabric_port_speed_t maxRxSpeed;             ///< [out] Maximum bandwidth supported by the receive side of the port
    zet_fabric_port_speed_t maxTxSpeed;             ///< [out] Maximum bandwidth supported by the transmit side of the port

} zet_fabric_port_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides information about the fabric link attached to a port
typedef struct _zet_fabric_link_type_t
{
    int8_t desc[ZET_MAX_FABRIC_LINK_TYPE_SIZE];     ///< [out] This provides a textural description of a link attached to a
                                                    ///< port. It contains the following information:
                                                    ///< - Link material
                                                    ///< - Link technology
                                                    ///< - Cable manufacturer
                                                    ///< - Temperature
                                                    ///< - Power
                                                    ///< - Attachment type:
                                                    ///<    - Disconnected
                                                    ///<    - Hardwired/fixed/etched connector
                                                    ///<    - Active copper
                                                    ///<    - QSOP
                                                    ///<    - AOC

} zet_fabric_link_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port configuration
typedef struct _zet_fabric_port_config_t
{
    ze_bool_t enabled;                              ///< [in,out] Port is configured up/down
    ze_bool_t beaconing;                            ///< [in,out] Beaconing is configured on/off

} zet_fabric_port_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port state
typedef struct _zet_fabric_port_state_t
{
    zet_fabric_port_status_t status;                ///< [out] The current status of the port
    zet_fabric_port_qual_issues_t qualityIssues;    ///< [out] If status is ::ZET_FABRIC_PORT_STATUS_YELLOW, this gives a
                                                    ///< bitfield of quality issues that have been detected
    zet_fabric_port_stab_issues_t stabilityIssues;  ///< [out] If status is ::ZET_FABRIC_PORT_STATUS_RED, this gives a bitfield
                                                    ///< of reasons for the connection instability
    zet_fabric_port_speed_t rxSpeed;                ///< [out] Current maximum receive speed
    zet_fabric_port_speed_t txSpeed;                ///< [out] Current maximum transmit speed

} zet_fabric_port_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fabric port throughput
/// 
/// @details
///     - Percent throughput is calculated by taking two snapshots (s1, s2) and
///       using the equation:
///     -     %rx_bandwidth = 10^6 * (s2.rxCounter - s1.rxCounter) /
///       (s2.rxMaxBandwidth * (s2.timestamp - s1.timestamp))
///     -     %tx_bandwidth = 10^6 * (s2.txCounter - s1.txCounter) /
///       (s2.txMaxBandwidth * (s2.timestamp - s1.timestamp))
typedef struct _zet_fabric_port_throughput_t
{
    uint64_t timestamp;                             ///< [out] Monotonic timestamp counter in microseconds when the measurement
                                                    ///< was made.
                                                    ///< No assumption should be made about the absolute value of the timestamp.
                                                    ///< It should only be used to calculate delta time between two snapshots
                                                    ///< of the same structure.
                                                    ///< Never take the delta of this timestamp with the timestamp from a
                                                    ///< different structure.
    uint64_t rxCounter;                             ///< [out] Monotonic counter for the number of bytes received
    uint64_t txCounter;                             ///< [out] Monotonic counter for the number of bytes transmitted
    uint64_t rxMaxBandwidth;                        ///< [out] The current maximum bandwidth in bytes/sec for receiving packats
    uint64_t txMaxBandwidth;                        ///< [out] The current maximum bandwidth in bytes/sec for transmitting
                                                    ///< packets

} zet_fabric_port_throughput_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFabricPortGetProperties(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFabricPortGetLinkType(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
    zet_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                    ///< port.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFabricPortGetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFabricPortSetConfig(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    const zet_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFabricPortGetState(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFabricPortGetThroughput(
    zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
    zet_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters and maximum
                                                    ///< bandwidth.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensors
typedef enum _zet_temp_sensors_t
{
    ZET_TEMP_SENSORS_GLOBAL = 0,                    ///< The maximum temperature across all device sensors
    ZET_TEMP_SENSORS_GPU,                           ///< The maximum temperature across all sensors in the GPU
    ZET_TEMP_SENSORS_MEMORY,                        ///< The maximum temperature across all sensors in the local memory

} zet_temp_sensors_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor properties
typedef struct _zet_temp_properties_t
{
    zet_temp_sensors_t type;                        ///< [out] Which part of the device the temperature sensor measures
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t isCriticalTempSupported;              ///< [out] Indicates if the critical temperature event
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL is supported
    ze_bool_t isThreshold1Supported;                ///< [out] Indicates if the temperature threshold 1 event
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 is supported
    ze_bool_t isThreshold2Supported;                ///< [out] Indicates if the temperature threshold 2 event
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 is supported

} zet_temp_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature sensor threshold
typedef struct _zet_temp_threshold_t
{
    ze_bool_t enableLowToHigh;                      ///< [in,out] Trigger an event when the temperature crosses from below the
                                                    ///< threshold to above.
    ze_bool_t enableHighToLow;                      ///< [in,out] Trigger an event when the temperature crosses from above the
                                                    ///< threshold to below.
    double threshold;                               ///< [in,out] The threshold in degrees Celcius.

} zet_temp_threshold_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Temperature configuration - which events should be triggered and the
///        trigger conditions.
typedef struct _zet_temp_config_t
{
    ze_bool_t enableCritical;                       ///< [in,out] Indicates if event ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL
                                                    ///< should be triggered by the driver.
    zet_temp_threshold_t threshold1;                ///< [in,out] Configuration controlling if and when event
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 should be triggered by the
                                                    ///< driver.
    zet_temp_threshold_t threshold2;                ///< [in,out] Configuration controlling if and when event
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 should be triggered by the
                                                    ///< driver.
    uint32_t processId;                             ///< [out] Host processId that set this configuration (ignored when setting
                                                    ///< the configuration).

} zet_temp_config_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanTemperatureGetProperties(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zet_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanTemperatureGetConfig(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    zet_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanTemperatureSetConfig(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    const zet_temp_config_t* pConfig                ///< [in] New configuration.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanTemperatureGetState(
    zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
    double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                    ///< in degrees Celcius.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief PSU voltage status
typedef enum _zet_psu_voltage_status_t
{
    ZET_PSU_VOLTAGE_STATUS_NORMAL = 0,              ///< No unusual voltages have been detected
    ZET_PSU_VOLTAGE_STATUS_OVER,                    ///< Over-voltage has occurred
    ZET_PSU_VOLTAGE_STATUS_UNDER,                   ///< Under-voltage has occurred

} zet_psu_voltage_status_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Static properties of the power supply
typedef struct _zet_psu_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t haveFan;                              ///< [out] True if the power supply has a fan
    uint32_t ampLimit;                              ///< [out] The maximum electrical current in amperes that can be drawn

} zet_psu_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamic state of the power supply
typedef struct _zet_psu_state_t
{
    zet_psu_voltage_status_t voltStatus;            ///< [out] The current PSU voltage status
    ze_bool_t fanFailed;                            ///< [out] Indicates if the fan has failed
    uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees Celsius.
    uint32_t current;                               ///< [out] The amps being drawn in amperes

} zet_psu_state_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPsuGetProperties(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanPsuGetState(
    zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
    zet_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan resource speed mode
typedef enum _zet_fan_speed_mode_t
{
    ZET_FAN_SPEED_MODE_DEFAULT = 0,                 ///< The fan speed is operating using the hardware default settings
    ZET_FAN_SPEED_MODE_FIXED,                       ///< The fan speed is currently set to a fixed value
    ZET_FAN_SPEED_MODE_TABLE,                       ///< The fan speed is currently controlled dynamically by hardware based on
                                                    ///< a temp/speed table

} zet_fan_speed_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan speed units
typedef enum _zet_fan_speed_units_t
{
    ZET_FAN_SPEED_UNITS_RPM = 0,                    ///< The fan speed is in units of revolutions per minute (rpm)
    ZET_FAN_SPEED_UNITS_PERCENT,                    ///< The fan speed is a percentage of the maximum speed of the fan

} zet_fan_speed_units_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan temperature/speed pair
typedef struct _zet_fan_temp_speed_t
{
    uint32_t temperature;                           ///< [in,out] Temperature in degrees Celsius.
    uint32_t speed;                                 ///< [in,out] The speed of the fan
    zet_fan_speed_units_t units;                    ///< [in,out] The units of the member speed

} zet_fan_temp_speed_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define ZET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // ZET_FAN_TEMP_SPEED_PAIR_COUNT

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan properties
typedef struct _zet_fan_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the fan speed assuming the
                                                    ///< user has permissions
    uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan
    uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

} zet_fan_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Fan configuration
typedef struct _zet_fan_config_t
{
    zet_fan_speed_mode_t mode;                      ///< [in,out] The fan speed mode (fixed, temp-speed table)
    uint32_t speed;                                 ///< [in,out] The fixed fan speed setting
    zet_fan_speed_units_t speedUnits;               ///< [in,out] The units of the fixed fan speed setting
    uint32_t numPoints;                             ///< [in,out] The number of valid points in the fan speed table
    zet_fan_temp_speed_t table[ZET_FAN_TEMP_SPEED_PAIR_COUNT];  ///< [in,out] Array of temperature/fan speed pairs

} zet_fan_config_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFanGetProperties(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFanGetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFanSetConfig(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanFanGetState(
    zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
    zet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                    ///< requested.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief LED properties
typedef struct _zet_led_properties_t
{
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    ze_bool_t canControl;                           ///< [out] Indicates if software can control the LED assuming the user has
                                                    ///< permissions
    ze_bool_t haveRGB;                              ///< [out] Indicates if the LED is RGB capable

} zet_led_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief LED state
typedef struct _zet_led_state_t
{
    ze_bool_t isOn;                                 ///< [in,out] Indicates if the LED is on or off
    uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
    uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
    uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

} zet_led_state_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanLedGetProperties(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanLedGetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    zet_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanLedSetState(
    zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
    const zet_led_state_t* pState                   ///< [in] New state of the LED.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error type
typedef enum _zet_ras_error_type_t
{
    ZET_RAS_ERROR_TYPE_CORRECTABLE = 0,             ///< Errors were corrected by hardware
    ZET_RAS_ERROR_TYPE_UNCORRECTABLE,               ///< Error were not corrected

} zet_ras_error_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS properties
typedef struct _zet_ras_properties_t
{
    zet_ras_error_type_t type;                      ///< [out] The type of RAS error
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

} zet_ras_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error details
typedef struct _zet_ras_details_t
{
    uint64_t numResets;                             ///< [out] The number of device resets that have taken place
    uint64_t numProgrammingErrors;                  ///< [out] The number of hardware exceptions generated by the way workloads
                                                    ///< have programmed the hardware
    uint64_t numDriverErrors;                       ///< [out] The number of low level driver communication errors have
                                                    ///< occurred
    uint64_t numComputeErrors;                      ///< [out] The number of errors that have occurred in the compute
                                                    ///< accelerator hardware
    uint64_t numNonComputeErrors;                   ///< [out] The number of errors that have occurred in the fixed-function
                                                    ///< accelerator hardware
    uint64_t numCacheErrors;                        ///< [out] The number of errors that have occurred in caches
                                                    ///< (L1/L3/register file/shared local memory/sampler)
    uint64_t numDisplayErrors;                      ///< [out] The number of errors that have occurred in the display

} zet_ras_details_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief RAS error configuration - thresholds used for triggering RAS events
///        (::ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS,
///        ::ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS)
/// 
/// @details
///     - The driver maintains a total counter which is updated every time a
///       hardware block covered by the corresponding RAS error set notifies
///       that an error has occurred. When this total count goes above the
///       totalThreshold specified below, a RAS event is triggered.
///     - The driver also maintains a counter for each category of RAS error
///       (see ::zet_ras_details_t for a breakdown). Each time a hardware block
///       of that category notifies that an error has occurred, that
///       corresponding category counter is updated. When it goes above the
///       threshold specified in detailedThresholds, a RAS event is triggered.
typedef struct _zet_ras_config_t
{
    uint64_t totalThreshold;                        ///< [in,out] If the total RAS errors exceeds this threshold, the event
                                                    ///< will be triggered. A value of 0ULL disables triggering the event based
                                                    ///< on the total counter.
    zet_ras_details_t detailedThresholds;           ///< [in,out] If the RAS errors for each category exceed the threshold for
                                                    ///< that category, the event will be triggered. A value of 0ULL will
                                                    ///< disable an event being triggered for that category.
    uint32_t processId;                             ///< [out] Host processId that set this configuration (ignored when setting
                                                    ///< the configuration).

} zet_ras_config_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanRasGetProperties(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zet_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanRasGetConfig(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    zet_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                    ///< thresholds used to trigger events
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanRasSetConfig(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    const zet_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanRasGetState(
    zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    uint64_t* pTotalErrors,                         ///< [in,out] The number total number of errors that have occurred
    zet_ras_details_t* pDetails                     ///< [in,out][optional] Breakdown of where errors have occurred
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Event types
typedef enum _zet_sysman_event_type_t
{
    ZET_SYSMAN_EVENT_TYPE_NONE = 0,                 ///< Specifies no events
    ZET_SYSMAN_EVENT_TYPE_DEVICE_RESET = ZE_BIT( 0 ),   ///< Event is triggered when the driver is going to reset the device
    ZET_SYSMAN_EVENT_TYPE_DEVICE_SLEEP_STATE_ENTER = ZE_BIT( 1 ),   ///< Event is triggered when the driver is about to put the device into a
                                                    ///< deep sleep state
    ZET_SYSMAN_EVENT_TYPE_DEVICE_SLEEP_STATE_EXIT = ZE_BIT( 2 ),///< Event is triggered when the driver is waking the device up from a deep
                                                    ///< sleep state
    ZET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED = ZE_BIT( 3 ), ///< Event is triggered when the frequency starts being throttled
    ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED = ZE_BIT( 4 ),   ///< Event is triggered when the energy consumption threshold is reached
                                                    ///< (use ::zetSysmanPowerSetEnergyThreshold() to configure).
    ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL = ZE_BIT( 5 ),  ///< Event is triggered when the critical temperature is reached (use
                                                    ///< ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
    ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 = ZE_BIT( 6 ),///< Event is triggered when the temperature crosses threshold 1 (use
                                                    ///< ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
    ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 = ZE_BIT( 7 ),///< Event is triggered when the temperature crosses threshold 2 (use
                                                    ///< ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
    ZET_SYSMAN_EVENT_TYPE_MEM_HEALTH = ZE_BIT( 8 ), ///< Event is triggered when the health of device memory changes.
    ZET_SYSMAN_EVENT_TYPE_FABRIC_PORT_HEALTH = ZE_BIT( 9 ), ///< Event is triggered when the health of fabric ports change.
    ZET_SYSMAN_EVENT_TYPE_PCI_LINK_HEALTH = ZE_BIT( 10 ),   ///< Event is triggered when the health of the PCI link changes.
    ZET_SYSMAN_EVENT_TYPE_RAS_CORRECTABLE_ERRORS = ZE_BIT( 11 ),///< Event is triggered when accelerator RAS correctable errors cross
                                                    ///< thresholds (use ::zetSysmanRasSetConfig() to configure - disabled by
                                                    ///< default).
    ZET_SYSMAN_EVENT_TYPE_RAS_UNCORRECTABLE_ERRORS = ZE_BIT( 12 ),  ///< Event is triggered when accelerator RAS uncorrectable errors cross
                                                    ///< thresholds (use ::zetSysmanRasSetConfig() to configure - disabled by
                                                    ///< default).
    ZET_SYSMAN_EVENT_TYPE_ALL = 0x0FFF,             ///< Specifies all events

} zet_sysman_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event configuration for a device
typedef struct _zet_event_config_t
{
    uint32_t registered;                            ///< [in,out] List of registered events (Bitfield of events
                                                    ///< ::zet_sysman_event_type_t). ::ZET_SYSMAN_EVENT_TYPE_NONE indicates
                                                    ///< there are no registered events. ::ZET_SYSMAN_EVENT_TYPE_ALL indicates
                                                    ///< that all events are registered.

} zet_event_config_t;

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
__ze_api_export ze_result_t __zecall
zetSysmanEventGet(
    zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
    zet_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanEventGetConfig(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    zet_event_config_t* pConfig                     ///< [in,out] Will contain the current event configuration (list of
                                                    ///< registered events).
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanEventSetConfig(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
    const zet_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanEventGetState(
    zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device.
    ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                    ///< triggered by this device.
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_EVENT_WAIT_NONE
/// @brief Don't wait - just check if there are any new events
#define ZET_EVENT_WAIT_NONE  0x0
#endif // ZET_EVENT_WAIT_NONE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_EVENT_WAIT_INFINITE
/// @brief Wait infinitely for events to arrive.
#define ZET_EVENT_WAIT_INFINITE  0xFFFFFFFF
#endif // ZET_EVENT_WAIT_INFINITE

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
__ze_api_export ze_result_t __zecall
zetSysmanEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                    ///< ::ZET_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                    ///< ::ZET_EVENT_WAIT_INFINITE to block until events arrive.
    uint32_t count,                                 ///< [in] Number of handles in phEvents
    zet_sysman_event_handle_t* phEvents,            ///< [in][range(0, count)] Handle of events that should be listened to
    uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                    ///< triggered by any of the supplied event handles. If timeout is not
                                                    ///< ::ZET_EVENT_WAIT_INFINITE and this value is
                                                    ///< ::ZET_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic test suite type
typedef enum _zet_diag_type_t
{
    ZET_DIAG_TYPE_SCAN = 0,                         ///< Run SCAN diagnostics
    ZET_DIAG_TYPE_ARRAY,                            ///< Run Array diagnostics

} zet_diag_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic results
typedef enum _zet_diag_result_t
{
    ZET_DIAG_RESULT_NO_ERRORS = 0,                  ///< Diagnostic completed without finding errors to repair
    ZET_DIAG_RESULT_ABORT,                          ///< Diagnostic had problems running tests
    ZET_DIAG_RESULT_FAIL_CANT_REPAIR,               ///< Diagnostic had problems setting up repairs
    ZET_DIAG_RESULT_REBOOT_FOR_REPAIR,              ///< Diagnostics found errors, setup for repair and reboot is required to
                                                    ///< complete the process

} zet_diag_result_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DIAG_FIRST_TEST_INDEX
/// @brief Diagnostic test index to use for the very first test.
#define ZET_DIAG_FIRST_TEST_INDEX  0x0
#endif // ZET_DIAG_FIRST_TEST_INDEX

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DIAG_LAST_TEST_INDEX
/// @brief Diagnostic test index to use for the very last test.
#define ZET_DIAG_LAST_TEST_INDEX  0xFFFFFFFF
#endif // ZET_DIAG_LAST_TEST_INDEX

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostic test
typedef struct _zet_diag_test_t
{
    uint32_t index;                                 ///< [out] Index of the test
    char name[ZET_STRING_PROPERTY_SIZE];            ///< [out] Name of the test

} zet_diag_test_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Diagnostics test suite properties
typedef struct _zet_diag_properties_t
{
    zet_diag_type_t type;                           ///< [out] The type of diagnostics test suite
    ze_bool_t onSubdevice;                          ///< [out] True if the resource is located on a sub-device; false means
                                                    ///< that the resource is on the device of the calling Sysman handle
    uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    char name[ZET_STRING_PROPERTY_SIZE];            ///< [out] Name of the diagnostics test suite
    ze_bool_t haveTests;                            ///< [out] Indicates if this test suite has individual tests which can be
                                                    ///< run separately (use the function $SysmanDiagnosticsGetTests() to get
                                                    ///< the list of these tests)

} zet_diag_properties_t;

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanDiagnosticsGetProperties(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    zet_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                    ///< suite
    );

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
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetSysmanDiagnosticsRunTests(
    zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
    uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zet_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_SYSMAN_H
