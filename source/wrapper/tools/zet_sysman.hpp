/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_sysman.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for System Resource Management (Sysman)
 *
 */
#ifndef _ZET_SYSMAN_HPP
#define _ZET_SYSMAN_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_STRING_PROPERTY_SIZE
/// @brief Maximum number of characters in string properties.
#define ZET_STRING_PROPERTY_SIZE  64
#endif // ZET_STRING_PROPERTY_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_SCHED_WATCHDOG_DISABLE
/// @brief Disable forward progress guard timeout.
#define ZET_SCHED_WATCHDOG_DISABLE  (~(0ULL))
#endif // ZET_SCHED_WATCHDOG_DISABLE

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
#ifndef ZET_FAN_TEMP_SPEED_PAIR_COUNT
/// @brief Maximum number of fan temperature/speed pairs in the fan speed table.
#define ZET_FAN_TEMP_SPEED_PAIR_COUNT  32
#endif // ZET_FAN_TEMP_SPEED_PAIR_COUNT

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
#ifndef ZET_DIAG_FIRST_TEST_INDEX
/// @brief Diagnostic test index to use for the very first test.
#define ZET_DIAG_FIRST_TEST_INDEX  0x0
#endif // ZET_DIAG_FIRST_TEST_INDEX

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DIAG_LAST_TEST_INDEX
/// @brief Diagnostic test index to use for the very last test.
#define ZET_DIAG_LAST_TEST_INDEX  0xFFFFFFFF
#endif // ZET_DIAG_LAST_TEST_INDEX

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device
    class Sysman
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of Sysman
        enum class version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Types of accelerator engines
        enum class engine_type_t
        {
            OTHER = 0,                                      ///< Undefined types of accelerators.
            COMPUTE,                                        ///< Engines that process compute kernels.
            _3D,                                            ///< Engines that process 3D content
            MEDIA,                                          ///< Engines that process media workloads
            DMA,                                            ///< Engines that copy blocks of data

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Scheduler mode
        enum class sched_mode_t
        {
            TIMEOUT = 0,                                    ///< Multiple applications or contexts are submitting work to the hardware.
                                                            ///< When higher priority work arrives, the scheduler attempts to pause the
                                                            ///< current executing work within some timeout interval, then submits the
                                                            ///< other work.
            TIMESLICE,                                      ///< The scheduler attempts to fairly timeslice hardware execution time
                                                            ///< between multiple contexts submitting work to the hardware
                                                            ///< concurrently.
            EXCLUSIVE,                                      ///< Any application or context can run indefinitely on the hardware
                                                            ///< without being preempted or terminated. All pending work for other
                                                            ///< contexts must wait until the running context completes with no further
                                                            ///< submitted work.
            COMPUTE_UNIT_DEBUG,                             ///< Scheduler ensures that submission of workloads to the hardware is
                                                            ///< optimized for compute unit debugging.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Workload performance profiles
        enum class perf_profile_t
        {
            BALANCED = 0,                                   ///< The hardware is configured to strike a balance between compute and
                                                            ///< memory resources. This is the default profile when the device
                                                            ///< boots/resets.
            COMPUTE_BOUNDED,                                ///< The hardware is configured to prioritize performance of the compute
                                                            ///< units.
            MEMORY_BOUNDED,                                 ///< The hardware is configured to prioritize memory throughput.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device repair status
        enum class repair_status_t
        {
            UNSUPPORTED = 0,                                ///< The device does not support in-field repairs.
            NOT_PERFORMED,                                  ///< The device has never been repaired.
            PERFORMED,                                      ///< The device has been repaired.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI link status
        enum class pci_link_status_t
        {
            GREEN = 0,                                      ///< The link is up and operating as expected
            YELLOW,                                         ///< The link is up but has quality and/or bandwidth degradation
            RED,                                            ///< The link has stability issues and preventing workloads making forward
                                                            ///< progress

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI link quality degradation reasons
        enum class pci_link_qual_issues_t
        {
            NONE = 0,                                       ///< There are no quality issues with the link at this time
            REPLAYS = ZE_BIT( 0 ),                          ///< An significant number of replays are occurring
            SPEED = ZE_BIT( 1 ),                            ///< There is a degradation in the maximum bandwidth of the link

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI link stability issues
        enum class pci_link_stab_issues_t
        {
            NONE = 0,                                       ///< There are no connection stability issues at this time
            RETRAINING = ZE_BIT( 0 ),                       ///< Link retraining has occurred to deal with quality issues

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI bar types
        enum class pci_bar_type_t
        {
            CONFIG = 0,                                     ///< PCI configuration space
            MMIO,                                           ///< MMIO registers
            VRAM,                                           ///< VRAM aperture
            ROM,                                            ///< ROM aperture
            VGA_IO,                                         ///< Legacy VGA IO ports
            VGA_MEM,                                        ///< Legacy VGA memory
            INDIRECT_IO,                                    ///< Indirect IO port access
            INDIRECT_MEM,                                   ///< Indirect memory access
            OTHER,                                          ///< Other type of PCI bar

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency domains.
        enum class freq_domain_t
        {
            GPU = 0,                                        ///< GPU Core Domain.
            MEMORY,                                         ///< Local Memory Domain.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event types
        enum class event_type_t
        {
            NONE = 0,                                       ///< Specifies no events
            DEVICE_RESET = ZE_BIT( 0 ),                     ///< Event is triggered when the driver is going to reset the device
            DEVICE_SLEEP_STATE_ENTER = ZE_BIT( 1 ),         ///< Event is triggered when the driver is about to put the device into a
                                                            ///< deep sleep state
            DEVICE_SLEEP_STATE_EXIT = ZE_BIT( 2 ),          ///< Event is triggered when the driver is waking the device up from a deep
                                                            ///< sleep state
            FREQ_THROTTLED = ZE_BIT( 3 ),                   ///< Event is triggered when the frequency starts being throttled
            ENERGY_THRESHOLD_CROSSED = ZE_BIT( 4 ),         ///< Event is triggered when the energy consumption threshold is reached
                                                            ///< (use ::zetSysmanPowerSetEnergyThreshold() to configure).
            TEMP_CRITICAL = ZE_BIT( 5 ),                    ///< Event is triggered when the critical temperature is reached (use
                                                            ///< ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
            TEMP_THRESHOLD1 = ZE_BIT( 6 ),                  ///< Event is triggered when the temperature crosses threshold 1 (use
                                                            ///< ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
            TEMP_THRESHOLD2 = ZE_BIT( 7 ),                  ///< Event is triggered when the temperature crosses threshold 2 (use
                                                            ///< ::zetSysmanTemperatureSetConfig() to configure - disabled by default).
            MEM_HEALTH = ZE_BIT( 8 ),                       ///< Event is triggered when the health of device memory changes.
            FABRIC_PORT_HEALTH = ZE_BIT( 9 ),               ///< Event is triggered when the health of fabric ports change.
            PCI_LINK_HEALTH = ZE_BIT( 10 ),                 ///< Event is triggered when the health of the PCI link changes.
            RAS_CORRECTABLE_ERRORS = ZE_BIT( 11 ),          ///< Event is triggered when accelerator RAS correctable errors cross
                                                            ///< thresholds (use ::zetSysmanRasSetConfig() to configure - disabled by
                                                            ///< default).
            RAS_UNCORRECTABLE_ERRORS = ZE_BIT( 12 ),        ///< Event is triggered when accelerator RAS uncorrectable errors cross
                                                            ///< thresholds (use ::zetSysmanRasSetConfig() to configure - disabled by
                                                            ///< default).
            ALL = 0x0FFF,                                   ///< Specifies all events

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties
        struct properties_t
        {
            ze::Device::properties_t core;                  ///< [out] Core device properties
            uint32_t numSubdevices;                         ///< [out] Number of sub-devices
            int8_t serialNumber[ZET_STRING_PROPERTY_SIZE];  ///< [out] Manufacturing serial number (NULL terminated string value)
            int8_t boardNumber[ZET_STRING_PROPERTY_SIZE];   ///< [out] Manufacturing board number (NULL terminated string value)
            int8_t brandName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Brand name of the device (NULL terminated string value)
            int8_t modelName[ZET_STRING_PROPERTY_SIZE];     ///< [out] Model name of the device (NULL terminated string value)
            int8_t vendorName[ZET_STRING_PROPERTY_SIZE];    ///< [out] Vendor name of the device (NULL terminated string value)
            int8_t driverVersion[ZET_STRING_PROPERTY_SIZE]; ///< [out] Installed driver version (NULL terminated string value)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Configuration for timeout scheduler mode (::ZET_SCHED_MODE_TIMEOUT)
        struct sched_timeout_properties_t
        {
            uint64_t watchdogTimeout;                       ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                            ///< for a batch of work submitted to a hardware engine to complete or to
                                                            ///< be preempted so as to run another context.
                                                            ///< If this time is exceeded, the hardware engine is reset and the context terminated.
                                                            ///< If set to ::ZET_SCHED_WATCHDOG_DISABLE, a running workload can run as
                                                            ///< long as it wants without being terminated, but preemption attempts to
                                                            ///< run other contexts are permitted but not enforced.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Configuration for timeslice scheduler mode
        ///        (::ZET_SCHED_MODE_TIMESLICE)
        struct sched_timeslice_properties_t
        {
            uint64_t interval;                              ///< [in,out] The average interval in microseconds that a submission for a
                                                            ///< context will run on a hardware engine before being preempted out to
                                                            ///< run a pending submission for another context.
            uint64_t yieldTimeout;                          ///< [in,out] The maximum time in microseconds that the scheduler will wait
                                                            ///< to preempt a workload running on an engine before deciding to reset
                                                            ///< the hardware engine and terminating the associated context.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Contains information about a process that has an open connection with
        ///        this device
        /// 
        /// @details
        ///     - The application can use the process ID to query the OS for the owner
        ///       and the path to the executable.
        struct process_state_t
        {
            uint32_t processId;                             ///< [out] Host OS process ID.
            int64_t memSize;                                ///< [out] Device memory size in bytes allocated by this process (may not
                                                            ///< necessarily be resident on the device at the time of reading).
            int64_t engines;                                ///< [out] Bitfield of accelerator engines being used by this process (or
                                                            ///< 1<<::zet_engine_type_t together).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI address
        struct pci_address_t
        {
            uint32_t domain;                                ///< [out] BDF domain
            uint32_t bus;                                   ///< [out] BDF bus
            uint32_t device;                                ///< [out] BDF device
            uint32_t function;                              ///< [out] BDF function

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PCI speed
        struct pci_speed_t
        {
            uint32_t gen;                                   ///< [out] The link generation
            uint32_t width;                                 ///< [out] The number of lanes
            uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Static PCI properties
        struct pci_properties_t
        {
            pci_address_t address;                          ///< [out] The BDF address
            pci_speed_t maxSpeed;                           ///< [out] Fastest port configuration supported by the device.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamic PCI state
        struct pci_state_t
        {
            pci_link_status_t status;                       ///< [out] The current status of the port
            pci_link_qual_issues_t qualityIssues;           ///< [out] If status is ::ZET_PCI_LINK_STATUS_YELLOW, this gives a bitfield
                                                            ///< of quality issues that have been detected
            pci_link_stab_issues_t stabilityIssues;         ///< [out] If status is ::ZET_PCI_LINK_STATUS_RED, this gives a bitfield of
                                                            ///< reasons for the connection instability
            pci_speed_t speed;                              ///< [out] The current port configure speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Properties of a pci bar
        struct pci_bar_properties_t
        {
            pci_bar_type_t type;                            ///< [out] The type of bar
            uint32_t index;                                 ///< [out] The index of the bar
            uint64_t base;                                  ///< [out] Base address of the bar.
            uint64_t size;                                  ///< [out] Size of the bar.

        };

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
        struct pci_stats_t
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

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_handle_t m_handle = nullptr;             ///< [in] handle of Sysman object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sysman( void ) = delete;
        Sysman( 
            sysman_handle_t handle,                         ///< [in] handle of Sysman object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~Sysman( void ) = default;

        Sysman( Sysman const& other ) = delete;
        void operator=( Sysman const& other ) = delete;

        Sysman( Sysman&& other ) = delete;
        void operator=( Sysman&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the handle to access Sysman features for a device
        /// 
        /// @details
        ///     - The returned handle is unique.
        ///     - ::zet_device_handle_t returned by ::zeDeviceGetSubDevices() are not
        ///       support. Only use handles returned by ::zeDeviceGet(). All resources
        ///       on sub-devices can be enumerated through the primary device.
        /// @returns
        ///     - Sysman*: Handle for accessing Sysman features
        /// 
        /// @throws result_t
        static Sysman* __zecall
        Get(
            Device* pDevice,                                ///< [in] Handle of the device
            version_t version                               ///< [in] Sysman version that application was built with
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties about the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        DeviceGetProperties(
            properties_t* pProperties                       ///< [in,out] Structure that will contain information about the device.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get a list of supported scheduler modes
        /// 
        /// @details
        ///     - If zero modes are returned, control of scheduler modes are not
        ///       supported.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SchedulerGetSupportedModes(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of scheduler modes.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of supported modes.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< supported scheduler modes.
                                                            ///< if count is larger than the number of supported scheduler modes, then
                                                            ///< the driver will update the value with the correct number of supported
                                                            ///< scheduler modes that are returned.
            sched_mode_t* pModes = nullptr                  ///< [in,out][optional][range(0, *pCount)] Array of supported scheduler
                                                            ///< modes
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current scheduler mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SchedulerGetCurrentMode(
            sched_mode_t* pMode                             ///< [in,out] Will contain the current scheduler mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMEOUT
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SchedulerGetTimeoutModeProperties(
            ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                            ///< this mode, otherwise it will return the current properties.
            sched_timeout_properties_t* pConfig             ///< [in,out] Will contain the current parameters for this mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get scheduler config for mode ::ZET_SCHED_MODE_TIMESLICE
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SchedulerGetTimesliceModeProperties(
            ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                            ///< this mode, otherwise it will return the current properties.
            sched_timeslice_properties_t* pConfig           ///< [in,out] Will contain the current parameters for this mode.
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
        /// @throws result_t
        void __zecall
        SchedulerSetTimeoutMode(
            sched_timeout_properties_t* pProperties,        ///< [in] The properties to use when configurating this mode.
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
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
        /// @throws result_t
        void __zecall
        SchedulerSetTimesliceMode(
            sched_timeslice_properties_t* pProperties,      ///< [in] The properties to use when configurating this mode.
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
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
        /// @throws result_t
        void __zecall
        SchedulerSetExclusiveMode(
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
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
        /// @throws result_t
        void __zecall
        SchedulerSetComputeUnitDebugMode(
            ze::bool_t* pNeedReboot                         ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                            ///< scheduler mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get a list of supported performance profiles that can be loaded for
        ///        this device
        /// 
        /// @details
        ///     - The balanced profile ::ZET_PERF_PROFILE_BALANCED is always returned in
        ///       the array.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PerformanceProfileGetSupported(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of performance profiles.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of supported performance profiles.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< supported performance profiles.
                                                            ///< if count is larger than the number of supported performance profiles,
                                                            ///< then the driver will update the value with the correct number of
                                                            ///< supported performance profiles that are returned.
            perf_profile_t* pProfiles = nullptr             ///< [in,out][optional][range(0, *pCount)] Array of supported performance
                                                            ///< profiles
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current pre-configured performance profile being used by the
        ///        hardware
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PerformanceProfileGet(
            perf_profile_t* pProfile                        ///< [in,out] The performance profile currently loaded.
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
        /// @throws result_t
        void __zecall
        PerformanceProfileSet(
            perf_profile_t profile                          ///< [in] The performance profile to load.
            );

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
        /// @throws result_t
        void __zecall
        ProcessesGetState(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of processes currently using the device.
                                                            ///< if count is non-zero but less than the number of processes, the driver
                                                            ///< will set to the number of processes currently using the device and
                                                            ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                            ///< if count is larger than the number of processes, then the driver will
                                                            ///< update the value with the correct number of processes that are returned.
            process_state_t* pProcesses = nullptr           ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                            ///< one for each process currently using the device
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset device
        /// @throws result_t
        void __zecall
        DeviceReset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Find out if the device has been repaired (either by the manufacturer
        ///        or by running diagnostics)
        /// @throws result_t
        void __zecall
        DeviceGetRepairStatus(
            repair_status_t* pRepairStatus                  ///< [in,out] Will indicate if the device was repaired
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PCI properties - address, max speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetProperties(
            pci_properties_t* pProperties                   ///< [in,out] Will contain the PCI properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current PCI state - current speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetState(
            pci_state_t* pState                             ///< [in,out] Will contain the PCI properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get information about each configured bar
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetBars(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of bars.
                                                            ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                            ///< if count is larger than the number of bar, then the driver will update
                                                            ///< the value with the correct number of bars that are returned.
            pci_bar_properties_t* pProperties = nullptr     ///< [in,out][optional][range(0, *pCount)] array of bar properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get PCI stats - bandwidth, number of packets, number of replays
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PciGetStats(
            pci_stats_t* pStats                             ///< [in,out] Will contain a snapshot of the latest stats.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of power domains
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PowerGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanPower** ppPower = nullptr                 ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of frequency domains
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        FrequencyGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanFrequency** ppFrequency = nullptr         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of engine groups
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        EngineGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanEngine** ppEngine = nullptr               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of standby controls
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        StandbyGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanStandby** ppStandby = nullptr             ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of firmwares
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        FirmwareGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanFirmware** ppFirmware = nullptr           ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of memory modules
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        MemoryGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanMemory** ppMemory = nullptr               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of Fabric ports in a device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        FabricPortGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanFabricPort** ppPort = nullptr             ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of temperature sensors
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        TemperatureGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanTemperature** ppTemperature = nullptr     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of power supplies
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        PsuGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanPsu** ppPsu = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of fans
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        FanGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanFan** ppFan = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of LEDs
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        LedGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanLed** ppLed = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

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
        /// @throws result_t
        void __zecall
        RasGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanRas** ppRas = nullptr                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the event handle for the specified device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - SysmanEvent*: The event handle for the specified device.
        /// 
        /// @throws result_t
        SysmanEvent* __zecall
        EventGet(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get handle of diagnostics test suites
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        DiagnosticsGet(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of components of this type.
                                                            ///< if count is non-zero, then driver will only retrieve that number of components.
                                                            ///< if count is larger than the number of components available, then the
                                                            ///< driver will update the value with the correct number of components
                                                            ///< that are returned.
            SysmanDiagnostics** ppDiagnostics = nullptr     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                            ///< of this type
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device power domain
    class SysmanPower
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Properties related to device power settings
        struct power_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Software can change the power limits of this domain assuming the
                                                            ///< user has permissions.
            ze::bool_t isEnergyThresholdSupported;          ///< [out] Indicates if this power domain supports the energy threshold
                                                            ///< event (::ZET_SYSMAN_EVENT_TYPE_ENERGY_THRESHOLD_CROSSED).
            uint32_t maxLimit;                              ///< [out] The maximum power limit in milliwatts that can be requested.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Energy counter snapshot
        /// 
        /// @details
        ///     - Average power is calculated by taking two snapshots (s1, s2) and using
        ///       the equation: PowerWatts = (s2.energy - s1.energy) / (s2.timestamp -
        ///       s1.timestamp)
        struct power_energy_counter_t
        {
            uint64_t energy;                                ///< [out] The monotonic energy counter in microjoules.
            uint64_t timestamp;                             ///< [out] Microsecond timestamp when energy was captured.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sustained power limits
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency if
        ///       the power averaged over a window (typically seconds) exceeds this
        ///       limit.
        struct power_sustained_limit_t
        {
            ze::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts
            uint32_t interval;                              ///< [in,out] power averaging window (Tau) in milliseconds

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Burst power limit
        /// 
        /// @details
        ///     - The power controller (Punit) will throttle the operating frequency of
        ///       the device if the power averaged over a few milliseconds exceeds a
        ///       limit known as PL2. Typically PL2 > PL1 so that it permits the
        ///       frequency to burst higher for short periods than would be otherwise
        ///       permitted by PL1.
        struct power_burst_limit_t
        {
            ze::bool_t enabled;                             ///< [in,out] indicates if the limit is enabled (true) or ignored (false)
            uint32_t power;                                 ///< [in,out] power limit in milliwatts

        };

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
        struct power_peak_limit_t
        {
            uint32_t powerAC;                               ///< [in,out] power limit in milliwatts for the AC power source.
            uint32_t powerDC;                               ///< [in,out] power limit in milliwatts for the DC power source. This is
                                                            ///< ignored if the product does not have a battery.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Energy threshold
        /// 
        /// @details
        ///     - .
        struct energy_threshold_t
        {
            ze::bool_t enable;                              ///< [in,out] Indicates if the energy threshold is enabled.
            double threshold;                               ///< [in,out] The energy threshold in Joules. Will be 0.0 if no threshold
                                                            ///< has been set.
            uint32_t processId;                             ///< [in,out] The host process ID that set the energy threshold. Will be
                                                            ///< 0xFFFFFFFF if no threshold has been set.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_pwr_handle_t m_handle = nullptr;         ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanPower( void ) = delete;
        SysmanPower( 
            sysman_pwr_handle_t handle,                     ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanPower( void ) = default;

        SysmanPower( SysmanPower const& other ) = delete;
        void operator=( SysmanPower const& other ) = delete;

        SysmanPower( SysmanPower&& other ) = delete;
        void operator=( SysmanPower&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties related to a power domain
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            power_properties_t* pProperties                 ///< [in,out] Structure that will contain property data.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get energy counter
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetEnergyCounter(
            power_energy_counter_t* pEnergy                 ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                            ///< timestamp when the last counter value was measured.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetLimits(
            power_sustained_limit_t* pSustained = nullptr,  ///< [in,out][optional] The sustained power limit.
            power_burst_limit_t* pBurst = nullptr,          ///< [in,out][optional] The burst power limit.
            power_peak_limit_t* pPeak = nullptr             ///< [in,out][optional] The peak power limit.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set power limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetLimits(
            const power_sustained_limit_t* pSustained = nullptr,///< [in][optional] The sustained power limit.
            const power_burst_limit_t* pBurst = nullptr,    ///< [in][optional] The burst power limit.
            const power_peak_limit_t* pPeak = nullptr       ///< [in][optional] The peak power limit.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get energy threshold
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetEnergyThreshold(
            energy_threshold_t* pThreshold                  ///< [in,out] Returns information about the energy threshold setting -
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
        /// @throws result_t
        void __zecall
        SetEnergyThreshold(
            double threshold                                ///< [in] The energy threshold to be set in joules.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device frequency domain
    class SysmanFrequency
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency throttle reasons
        enum class freq_throttle_reasons_t
        {
            NONE = 0,                                       ///< frequency not throttled
            AVE_PWR_CAP = ZE_BIT( 0 ),                      ///< frequency throttled due to average power excursion (PL1)
            BURST_PWR_CAP = ZE_BIT( 1 ),                    ///< frequency throttled due to burst power excursion (PL2)
            CURRENT_LIMIT = ZE_BIT( 2 ),                    ///< frequency throttled due to current excursion (PL4)
            THERMAL_LIMIT = ZE_BIT( 3 ),                    ///< frequency throttled due to thermal excursion (T > TjMax)
            PSU_ALERT = ZE_BIT( 4 ),                        ///< frequency throttled due to power supply assertion
            SW_RANGE = ZE_BIT( 5 ),                         ///< frequency throttled due to software supplied frequency range
            HW_RANGE = ZE_BIT( 6 ),                         ///< frequency throttled due to a sub block that has a lower frequency
                                                            ///< range when it receives clocks

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Overclocking modes
        enum class oc_mode_t
        {
            OFF = 0,                                        ///< Overclocking if off - hardware is running using factory default
                                                            ///< voltages/frequencies.
            OVERRIDE,                                       ///< Overclock override mode - In this mode, a fixed user-supplied voltage
                                                            ///< is applied independent of the frequency request. The maximum permitted
                                                            ///< frequency can also be increased.
            INTERPOLATIVE,                                  ///< Overclock interpolative mode - In this mode, the voltage/frequency
                                                            ///< curve can be extended with a new voltage/frequency point that will be
                                                            ///< interpolated. The existing voltage/frequency points can also be offset
                                                            ///< (up or down) by a fixed voltage.

        };

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
        struct freq_properties_t
        {
            Sysman::freq_domain_t type;                     ///< [out] The hardware block that this frequency domain controls (GPU,
                                                            ///< memory, ...)
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can control the frequency of this domain
                                                            ///< assuming the user has permissions
            ze::bool_t isThrottleEventSupported;            ///< [out] Indicates if software can register to receive event
                                                            ///< ::ZET_SYSMAN_EVENT_TYPE_FREQ_THROTTLED
            double min;                                     ///< [out] The minimum hardware clock frequency in units of MHz
            double max;                                     ///< [out] The maximum non-overclock hardware clock frequency in units of
                                                            ///< MHz.
            double step;                                    ///< [out] The minimum step-size for clock frequencies in units of MHz. The
                                                            ///< hardware will clamp intermediate frequencies to lowest multiplier of
                                                            ///< this number.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency range between which the hardware can operate.
        struct freq_range_t
        {
            double min;                                     ///< [in,out] The min frequency in MHz below which hardware frequency
                                                            ///< management will not request frequencies. Setting to 0 will use the
                                                            ///< hardware default value.
            double max;                                     ///< [in,out] The max frequency in MHz above which hardware frequency
                                                            ///< management will not request frequencies. Setting to 0 will use the
                                                            ///< hardware default value.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency state
        struct freq_state_t
        {
            double request;                                 ///< [out] The current frequency request in MHz.
            double tdp;                                     ///< [out] The maximum frequency in MHz supported under the current TDP
                                                            ///< conditions
            double efficient;                               ///< [out] The efficient minimum frequency in MHz
            double actual;                                  ///< [out] The resolved frequency in MHz
            uint32_t throttleReasons;                       ///< [out] The reasons that the frequency is being limited by the hardware
                                                            ///< (Bitfield of ::zet_freq_throttle_reasons_t).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frequency throttle time snapshot
        /// 
        /// @details
        ///     - Percent time throttled is calculated by taking two snapshots (s1, s2)
        ///       and using the equation: %throttled = (s2.throttleTime -
        ///       s1.throttleTime) / (s2.timestamp - s1.timestamp)
        struct freq_throttle_time_t
        {
            uint64_t throttleTime;                          ///< [out] The monotonic counter of time in microseconds that the frequency
                                                            ///< has been limited by the hardware.
            uint64_t timestamp;                             ///< [out] Microsecond timestamp when throttleTime was captured.
                                                            ///< No assumption should be made about the absolute value of the timestamp.
                                                            ///< It should only be used to calculate delta time between two snapshots
                                                            ///< of the same structure.
                                                            ///< Never take the delta of this timestamp with the timestamp from a
                                                            ///< different structure.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Overclocking properties
        /// 
        /// @details
        ///     - Provides all the overclocking capabilities and properties supported by
        ///       the device for the frequency domain.
        struct oc_capabilities_t
        {
            ze::bool_t isOcSupported;                       ///< [out] Indicates if any overclocking features are supported on this
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
            ze::bool_t isTjMaxSupported;                    ///< [out] Indicates if the maximum temperature limit (TjMax) can be
                                                            ///< changed for this frequency domain.
            ze::bool_t isIccMaxSupported;                   ///< [out] Indicates if the maximum current (IccMax) can be changed for
                                                            ///< this frequency domain.
            ze::bool_t isHighVoltModeCapable;               ///< [out] Indicates if this frequency domains supports a feature to set
                                                            ///< very high voltages.
            ze::bool_t isHighVoltModeEnabled;               ///< [out] Indicates if very high voltages are permitted on this frequency
                                                            ///< domain.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Overclocking configuration
        /// 
        /// @details
        ///     - Overclock settings
        struct oc_config_t
        {
            oc_mode_t mode;                                 ///< [in,out] Overclock Mode ::zet_oc_mode_t.
            double frequency;                               ///< [in,out] Overclocking Frequency in MHz. This cannot be greater than
                                                            ///< ::zet_oc_capabilities_t.maxOcFrequency.
            double voltageTarget;                           ///< [in,out] Overclock voltage in Volts. This cannot be greater than
                                                            ///< ::zet_oc_capabilities_t.maxOcVoltage.
            double voltageOffset;                           ///< [in,out] This voltage offset is applied to all points on the
                                                            ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                            ///< can be in the range (::zet_oc_capabilities_t.minOcVoltageOffset,
                                                            ///< ::zet_oc_capabilities_t.maxOcVoltageOffset).

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_freq_handle_t m_handle = nullptr;        ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanFrequency( void ) = delete;
        SysmanFrequency( 
            sysman_freq_handle_t handle,                    ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanFrequency( void ) = default;

        SysmanFrequency( SysmanFrequency const& other ) = delete;
        void operator=( SysmanFrequency const& other ) = delete;

        SysmanFrequency( SysmanFrequency&& other ) = delete;
        void operator=( SysmanFrequency&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency properties - available frequencies
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            freq_properties_t* pProperties                  ///< [in,out] The frequency properties for the specified domain.
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
        /// @throws result_t
        void __zecall
        GetAvailableClocks(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                            ///< If count is zero, then the driver will update the value with the total
                                                            ///< number of frequencies available.
                                                            ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                            ///< If count is larger than the number of frequencies available, then the
                                                            ///< driver will update the value with the correct number of frequencies available.
            double* phFrequency = nullptr                   ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                            ///< MHz and sorted from slowest to fastest
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current frequency limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetRange(
            freq_range_t* pLimits                           ///< [in,out] The range between which the hardware can operate for the
                                                            ///< specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set frequency range between which the hardware can operate.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetRange(
            const freq_range_t* pLimits                     ///< [in] The limits between which the hardware can operate for the
                                                            ///< specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current frequency state - frequency request, actual frequency, TDP
        ///        limits
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            freq_state_t* pState                            ///< [in,out] Frequency state for the specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get frequency throttle time
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetThrottleTime(
            freq_throttle_time_t* pThrottleTime             ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                            ///< specified domain.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the overclocking capabilities.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        OcGetCapabilities(
            oc_capabilities_t* pOcCapabilities              ///< [in,out] Pointer to the capabilities structure
                                                            ///< ::zet_oc_capabilities_t.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the current overclocking configuration.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        OcGetConfig(
            oc_config_t* pOcConfiguration                   ///< [in,out] Pointer to the configuration structure ::zet_oc_config_t.
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
        /// @throws result_t
        void __zecall
        OcSetConfig(
            oc_config_t* pOcConfiguration,                  ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
            ze::bool_t* pDeviceRestart                      ///< [in,out] This will be set to true if the device needs to be restarted
                                                            ///< in order to enable the new overclock settings.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the maximum current limit setting.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        OcGetIccMax(
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
        /// @throws result_t
        void __zecall
        OcSetIccMax(
            double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the maximum temperature limit setting.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        OcGetTjMax(
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
        /// @throws result_t
        void __zecall
        OcSetTjMax(
            double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device engine group
    class SysmanEngine
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Accelerator engine groups
        enum class engine_group_t
        {
            ALL = 0,                                        ///< Access information about all engines combined.
            COMPUTE_ALL,                                    ///< Access information about all compute engines combined.
            MEDIA_ALL,                                      ///< Access information about all media engines combined.
            COPY_ALL,                                       ///< Access information about all copy (blitter) engines combined.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Engine group properties
        struct engine_properties_t
        {
            engine_group_t type;                            ///< [out] The engine group
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Engine activity counters
        /// 
        /// @details
        ///     - Percent utilization is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %util = (s2.activeTime - s1.activeTime) /
        ///       (s2.timestamp - s1.timestamp)
        struct engine_stats_t
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

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_engine_handle_t m_handle = nullptr;      ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanEngine( void ) = delete;
        SysmanEngine( 
            sysman_engine_handle_t handle,                  ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanEngine( void ) = default;

        SysmanEngine( SysmanEngine const& other ) = delete;
        void operator=( SysmanEngine const& other ) = delete;

        SysmanEngine( SysmanEngine&& other ) = delete;
        void operator=( SysmanEngine&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get engine group properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            engine_properties_t* pProperties                ///< [in,out] The properties for the specified engine group.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the activity stats for an engine group
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetActivity(
            engine_stats_t* pStats                          ///< [in,out] Will contain a snapshot of the engine group activity
                                                            ///< counters.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman standby control
    class SysmanStandby
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby hardware components
        enum class standby_type_t
        {
            GLOBAL = 0,                                     ///< Control the overall standby policy of the device/sub-device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby promotion modes
        enum class standby_promo_mode_t
        {
            DEFAULT = 0,                                    ///< Best compromise between performance and energy savings.
            NEVER,                                          ///< The device/component will never shutdown. This can improve performance
                                                            ///< but uses more energy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Standby hardware component properties
        struct standby_properties_t
        {
            standby_type_t type;                            ///< [out] Which standby hardware component this controls
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_standby_handle_t m_handle = nullptr;     ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanStandby( void ) = delete;
        SysmanStandby( 
            sysman_standby_handle_t handle,                 ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanStandby( void ) = default;

        SysmanStandby( SysmanStandby const& other ) = delete;
        void operator=( SysmanStandby const& other ) = delete;

        SysmanStandby( SysmanStandby&& other ) = delete;
        void operator=( SysmanStandby&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get standby hardware component properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            standby_properties_t* pProperties               ///< [in,out] Will contain the standby hardware properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the current standby promotion mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetMode(
            standby_promo_mode_t* pMode                     ///< [in,out] Will contain the current standby mode.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set standby promotion mode
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetMode(
            standby_promo_mode_t mode                       ///< [in] New standby mode.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device firmware
    class SysmanFirmware
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Firmware properties
        struct firmware_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can flash the firmware assuming the user
                                                            ///< has permissions
            int8_t name[ZET_STRING_PROPERTY_SIZE];          ///< [out] NULL terminated string value
            int8_t version[ZET_STRING_PROPERTY_SIZE];       ///< [out] NULL terminated string value

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_firmware_handle_t m_handle = nullptr;    ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanFirmware( void ) = delete;
        SysmanFirmware( 
            sysman_firmware_handle_t handle,                ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanFirmware( void ) = default;

        SysmanFirmware( SysmanFirmware const& other ) = delete;
        void operator=( SysmanFirmware const& other ) = delete;

        SysmanFirmware( SysmanFirmware&& other ) = delete;
        void operator=( SysmanFirmware&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            firmware_properties_t* pProperties              ///< [in,out] Pointer to an array that will hold the properties of the
                                                            ///< firmware
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get firmware checksum
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetChecksum(
            uint32_t* pChecksum                             ///< [in,out] Calculated checksum of the installed firmware.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Flash a new firmware image
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        Flash(
            void* pImage,                                   ///< [in] Image of the new firmware to flash.
            uint32_t size                                   ///< [in] Size of the flash image.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device memory module
    class SysmanMemory
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory module types
        enum class mem_type_t
        {
            HBM = 0,                                        ///< HBM memory
            DDR,                                            ///< DDR memory
            SRAM,                                           ///< SRAM memory
            L1,                                             ///< L1 cache
            L3,                                             ///< L3 cache
            GRF,                                            ///< Execution unit register file
            SLM,                                            ///< Execution unit shared local memory

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory health
        enum class mem_health_t
        {
            OK = 0,                                         ///< All memory channels are healthy
            DEGRADED,                                       ///< Excessive correctable errors have been detected on one or more
                                                            ///< channels. Device should be reset.
            CRITICAL,                                       ///< Operating with reduced memory to cover banks with too many
                                                            ///< uncorrectable errors.
            REPLACE,                                        ///< Device should be replaced due to excessive uncorrectable errors.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory properties
        struct mem_properties_t
        {
            mem_type_t type;                                ///< [out] The memory type
            ze::bool_t onSubdevice;                         ///< [out] True if this resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            uint64_t physicalSize;                          ///< [out] Physical memory size in bytes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory state - health, allocated
        /// 
        /// @details
        ///     - Percent allocation is given by 100 * allocatedSize / maxSize.
        ///     - Percent free is given by 100 * (maxSize - allocatedSize) / maxSize.
        struct mem_state_t
        {
            mem_health_t health;                            ///< [out] Indicates the health of the memory
            uint64_t allocatedSize;                         ///< [out] The total allocated bytes
            uint64_t maxSize;                               ///< [out] The total allocatable memory in bytes (can be less than
                                                            ///< ::zet_mem_properties_t.physicalSize)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory bandwidth
        /// 
        /// @details
        ///     - Percent bandwidth is calculated by taking two snapshots (s1, s2) and
        ///       using the equation: %bw = 10^6 * ((s2.readCounter - s1.readCounter) +
        ///       (s2.writeCounter - s1.writeCounter)) / (s2.maxBandwidth *
        ///       (s2.timestamp - s1.timestamp))
        struct mem_bandwidth_t
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

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_mem_handle_t m_handle = nullptr;         ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanMemory( void ) = delete;
        SysmanMemory( 
            sysman_mem_handle_t handle,                     ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanMemory( void ) = default;

        SysmanMemory( SysmanMemory const& other ) = delete;
        void operator=( SysmanMemory const& other ) = delete;

        SysmanMemory( SysmanMemory&& other ) = delete;
        void operator=( SysmanMemory&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            mem_properties_t* pProperties                   ///< [in,out] Will contain memory properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory state - health, allocated
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            mem_state_t* pState                             ///< [in,out] Will contain the current health and allocated memory.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory bandwidth
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetBandwidth(
            mem_bandwidth_t* pBandwidth                     ///< [in,out] Will contain a snapshot of the bandwidth counters.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device Fabric port
    class SysmanFabricPort
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port status
        enum class fabric_port_status_t
        {
            GREEN = 0,                                      ///< The port is up and operating as expected
            YELLOW,                                         ///< The port is up but has quality and/or bandwidth degradation
            RED,                                            ///< Port connection instabilities are preventing workloads making forward
                                                            ///< progress
            BLACK,                                          ///< The port is configured down

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port quality degradation reasons
        enum class fabric_port_qual_issues_t
        {
            NONE = 0,                                       ///< There are no quality issues with the link at this time
            FEC = ZE_BIT( 0 ),                              ///< Excessive FEC (forward error correction) are occurring
            LTP_CRC = ZE_BIT( 1 ),                          ///< Excessive LTP CRC failure induced replays are occurring
            SPEED = ZE_BIT( 2 ),                            ///< There is a degradation in the maximum bandwidth of the port

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port stability issues
        enum class fabric_port_stab_issues_t
        {
            NONE = 0,                                       ///< There are no connection stability issues at this time
            TOO_MANY_REPLAYS = ZE_BIT( 0 ),                 ///< Sequential replay failure is inducing link retraining
            NO_CONNECT = ZE_BIT( 1 ),                       ///< A connection was never able to be established through the link
            FLAPPING = ZE_BIT( 2 ),                         ///< The port is flapping

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port universal unique id (UUID)
        struct fabric_port_uuid_t
        {
            uint8_t id[ZET_MAX_FABRIC_PORT_UUID_SIZE];      ///< [out] Frabric port universal unique id

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port speed in one direction
        struct fabric_port_speed_t
        {
            uint64_t bitRate;                               ///< [out] Bits/sec that the link is operating at
            uint32_t width;                                 ///< [out] The number of lanes
            uint64_t maxBandwidth;                          ///< [out] The maximum bandwidth in bytes/sec

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port properties
        struct fabric_port_properties_t
        {
            int8_t model[ZET_MAX_FABRIC_PORT_MODEL_SIZE];   ///< [out] Description of port technology
            ze::bool_t onSubdevice;                         ///< [out] True if the port is located on a sub-device; false means that
                                                            ///< the port is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            fabric_port_uuid_t portUuid;                    ///< [out] The port universal unique id
            fabric_port_speed_t maxRxSpeed;                 ///< [out] Maximum bandwidth supported by the receive side of the port
            fabric_port_speed_t maxTxSpeed;                 ///< [out] Maximum bandwidth supported by the transmit side of the port

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Provides information about the fabric link attached to a port
        struct fabric_link_type_t
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

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port configuration
        struct fabric_port_config_t
        {
            ze::bool_t enabled;                             ///< [in,out] Port is configured up/down
            ze::bool_t beaconing;                           ///< [in,out] Beaconing is configured on/off

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fabric port state
        struct fabric_port_state_t
        {
            fabric_port_status_t status;                    ///< [out] The current status of the port
            fabric_port_qual_issues_t qualityIssues;        ///< [out] If status is ::ZET_FABRIC_PORT_STATUS_YELLOW, this gives a
                                                            ///< bitfield of quality issues that have been detected
            fabric_port_stab_issues_t stabilityIssues;      ///< [out] If status is ::ZET_FABRIC_PORT_STATUS_RED, this gives a bitfield
                                                            ///< of reasons for the connection instability
            fabric_port_speed_t rxSpeed;                    ///< [out] Current maximum receive speed
            fabric_port_speed_t txSpeed;                    ///< [out] Current maximum transmit speed

        };

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
        struct fabric_port_throughput_t
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

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_fabric_port_handle_t m_handle = nullptr; ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanFabricPort( void ) = delete;
        SysmanFabricPort( 
            sysman_fabric_port_handle_t handle,             ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanFabricPort( void ) = default;

        SysmanFabricPort( SysmanFabricPort const& other ) = delete;
        void operator=( SysmanFabricPort const& other ) = delete;

        SysmanFabricPort( SysmanFabricPort&& other ) = delete;
        void operator=( SysmanFabricPort&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Fabric port properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            fabric_port_properties_t* pProperties           ///< [in,out] Will contain properties of the Fabric Port.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Fabric port link type
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetLinkType(
            ze::bool_t verbose,                             ///< [in] Set to true to get a more detailed report.
            fabric_link_type_t* pLinkType                   ///< [in,out] Will contain details about the link attached to the Fabric
                                                            ///< port.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Fabric port configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetConfig(
            fabric_port_config_t* pConfig                   ///< [in,out] Will contain configuration of the Fabric Port.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set Fabric port configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetConfig(
            const fabric_port_config_t* pConfig             ///< [in] Contains new configuration of the Fabric Port.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Fabric port state - status (green/yellow/red/black), reasons for
        ///        link degradation or instability, current rx/tx speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            fabric_port_state_t* pState                     ///< [in,out] Will contain the current state of the Fabric Port
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get Fabric port throughput
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetThroughput(
            fabric_port_throughput_t* pThroughput           ///< [in,out] Will contain the Fabric port throughput counters and maximum
                                                            ///< bandwidth.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device temperature sensor
    class SysmanTemperature
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensors
        enum class temp_sensors_t
        {
            GLOBAL = 0,                                     ///< The maximum temperature across all device sensors
            GPU,                                            ///< The maximum temperature across all sensors in the GPU
            MEMORY,                                         ///< The maximum temperature across all sensors in the local memory

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensor properties
        struct temp_properties_t
        {
            temp_sensors_t type;                            ///< [out] Which part of the device the temperature sensor measures
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t isCriticalTempSupported;             ///< [out] Indicates if the critical temperature event
                                                            ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL is supported
            ze::bool_t isThreshold1Supported;               ///< [out] Indicates if the temperature threshold 1 event
                                                            ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 is supported
            ze::bool_t isThreshold2Supported;               ///< [out] Indicates if the temperature threshold 2 event
                                                            ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 is supported

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature sensor threshold
        struct temp_threshold_t
        {
            ze::bool_t enableLowToHigh;                     ///< [in,out] Trigger an event when the temperature crosses from below the
                                                            ///< threshold to above.
            ze::bool_t enableHighToLow;                     ///< [in,out] Trigger an event when the temperature crosses from above the
                                                            ///< threshold to below.
            double threshold;                               ///< [in,out] The threshold in degrees Celcius.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Temperature configuration - which events should be triggered and the
        ///        trigger conditions.
        struct temp_config_t
        {
            ze::bool_t enableCritical;                      ///< [in,out] Indicates if event ::ZET_SYSMAN_EVENT_TYPE_TEMP_CRITICAL
                                                            ///< should be triggered by the driver.
            temp_threshold_t threshold1;                    ///< [in,out] Configuration controlling if and when event
                                                            ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD1 should be triggered by the
                                                            ///< driver.
            temp_threshold_t threshold2;                    ///< [in,out] Configuration controlling if and when event
                                                            ///< ::ZET_SYSMAN_EVENT_TYPE_TEMP_THRESHOLD2 should be triggered by the
                                                            ///< driver.
            uint32_t processId;                             ///< [out] Host processId that set this configuration (ignored when setting
                                                            ///< the configuration).

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_temp_handle_t m_handle = nullptr;        ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanTemperature( void ) = delete;
        SysmanTemperature( 
            sysman_temp_handle_t handle,                    ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanTemperature( void ) = default;

        SysmanTemperature( SysmanTemperature const& other ) = delete;
        void operator=( SysmanTemperature const& other ) = delete;

        SysmanTemperature( SysmanTemperature&& other ) = delete;
        void operator=( SysmanTemperature&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get temperature sensor properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            temp_properties_t* pProperties                  ///< [in,out] Will contain the temperature sensor properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get temperature configuration for this sensor - which events are
        ///        triggered and the trigger conditions
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetConfig(
            temp_config_t* pConfig                          ///< [in,out] Returns current configuration.
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
        /// @throws result_t
        void __zecall
        SetConfig(
            const temp_config_t* pConfig                    ///< [in] New configuration.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the temperature from a specified sensor
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                            ///< in degrees Celcius.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device power supply
    class SysmanPsu
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief PSU voltage status
        enum class psu_voltage_status_t
        {
            NORMAL = 0,                                     ///< No unusual voltages have been detected
            OVER,                                           ///< Over-voltage has occurred
            UNDER,                                          ///< Under-voltage has occurred

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Static properties of the power supply
        struct psu_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t haveFan;                             ///< [out] True if the power supply has a fan
            uint32_t ampLimit;                              ///< [out] The maximum electrical current in amperes that can be drawn

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamic state of the power supply
        struct psu_state_t
        {
            psu_voltage_status_t voltStatus;                ///< [out] The current PSU voltage status
            ze::bool_t fanFailed;                           ///< [out] Indicates if the fan has failed
            uint32_t temperature;                           ///< [out] Read the current heatsink temperature in degrees Celsius.
            uint32_t current;                               ///< [out] The amps being drawn in amperes

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_psu_handle_t m_handle = nullptr;         ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanPsu( void ) = delete;
        SysmanPsu( 
            sysman_psu_handle_t handle,                     ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanPsu( void ) = default;

        SysmanPsu( SysmanPsu const& other ) = delete;
        void operator=( SysmanPsu const& other ) = delete;

        SysmanPsu( SysmanPsu&& other ) = delete;
        void operator=( SysmanPsu&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get power supply properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            psu_properties_t* pProperties                   ///< [in,out] Will contain the properties of the power supply.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current power supply state
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            psu_state_t* pState                             ///< [in,out] Will contain the current state of the power supply.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device fan
    class SysmanFan
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan resource speed mode
        enum class fan_speed_mode_t
        {
            DEFAULT = 0,                                    ///< The fan speed is operating using the hardware default settings
            FIXED,                                          ///< The fan speed is currently set to a fixed value
            TABLE,                                          ///< The fan speed is currently controlled dynamically by hardware based on
                                                            ///< a temp/speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan speed units
        enum class fan_speed_units_t
        {
            RPM = 0,                                        ///< The fan speed is in units of revolutions per minute (rpm)
            PERCENT,                                        ///< The fan speed is a percentage of the maximum speed of the fan

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan temperature/speed pair
        struct fan_temp_speed_t
        {
            uint32_t temperature;                           ///< [in,out] Temperature in degrees Celsius.
            uint32_t speed;                                 ///< [in,out] The speed of the fan
            fan_speed_units_t units;                        ///< [in,out] The units of the member speed

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan properties
        struct fan_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can control the fan speed assuming the
                                                            ///< user has permissions
            uint32_t maxSpeed;                              ///< [out] The maximum RPM of the fan
            uint32_t maxPoints;                             ///< [out] The maximum number of points in the fan temp/speed table

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fan configuration
        struct fan_config_t
        {
            fan_speed_mode_t mode;                          ///< [in,out] The fan speed mode (fixed, temp-speed table)
            uint32_t speed;                                 ///< [in,out] The fixed fan speed setting
            fan_speed_units_t speedUnits;                   ///< [in,out] The units of the fixed fan speed setting
            uint32_t numPoints;                             ///< [in,out] The number of valid points in the fan speed table
            fan_temp_speed_t table[ZET_FAN_TEMP_SPEED_PAIR_COUNT];  ///< [in,out] Array of temperature/fan speed pairs

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_fan_handle_t m_handle = nullptr;         ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanFan( void ) = delete;
        SysmanFan( 
            sysman_fan_handle_t handle,                     ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanFan( void ) = default;

        SysmanFan( SysmanFan const& other ) = delete;
        void operator=( SysmanFan const& other ) = delete;

        SysmanFan( SysmanFan&& other ) = delete;
        void operator=( SysmanFan&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get fan properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            fan_properties_t* pProperties                   ///< [in,out] Will contain the properties of the fan.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current fan configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetConfig(
            fan_config_t* pConfig                           ///< [in,out] Will contain the current configuration of the fan.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set fan configuration
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetConfig(
            const fan_config_t* pConfig                     ///< [in] New fan configuration.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current state of a fan - current mode and speed
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            fan_speed_units_t units,                        ///< [in] The units in which the fan speed should be returned.
            uint32_t* pSpeed                                ///< [in,out] Will contain the current speed of the fan in the units
                                                            ///< requested.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device LED
    class SysmanLed
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED properties
        struct led_properties_t
        {
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            ze::bool_t canControl;                          ///< [out] Indicates if software can control the LED assuming the user has
                                                            ///< permissions
            ze::bool_t haveRGB;                             ///< [out] Indicates if the LED is RGB capable

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief LED state
        struct led_state_t
        {
            ze::bool_t isOn;                                ///< [in,out] Indicates if the LED is on or off
            uint8_t red;                                    ///< [in,out][range(0, 255)] The LED red value
            uint8_t green;                                  ///< [in,out][range(0, 255)] The LED green value
            uint8_t blue;                                   ///< [in,out][range(0, 255)] The LED blue value

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_led_handle_t m_handle = nullptr;         ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanLed( void ) = delete;
        SysmanLed( 
            sysman_led_handle_t handle,                     ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanLed( void ) = default;

        SysmanLed( SysmanLed const& other ) = delete;
        void operator=( SysmanLed const& other ) = delete;

        SysmanLed( SysmanLed&& other ) = delete;
        void operator=( SysmanLed&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get LED properties
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            led_properties_t* pProperties                   ///< [in,out] Will contain the properties of the LED.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get current state of a LED - on/off, color
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetState(
            led_state_t* pState                             ///< [in,out] Will contain the current state of the LED.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set state of a LED - on/off, color
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetState(
            const led_state_t* pState                       ///< [in] New state of the LED.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device RAS error set
    class SysmanRas
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error type
        enum class ras_error_type_t
        {
            CORRECTABLE = 0,                                ///< Errors were corrected by hardware
            UNCORRECTABLE,                                  ///< Error were not corrected

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS properties
        struct ras_properties_t
        {
            ras_error_type_t type;                          ///< [out] The type of RAS error
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief RAS error details
        struct ras_details_t
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

        };

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
        struct ras_config_t
        {
            uint64_t totalThreshold;                        ///< [in,out] If the total RAS errors exceeds this threshold, the event
                                                            ///< will be triggered. A value of 0ULL disables triggering the event based
                                                            ///< on the total counter.
            ras_details_t detailedThresholds;               ///< [in,out] If the RAS errors for each category exceed the threshold for
                                                            ///< that category, the event will be triggered. A value of 0ULL will
                                                            ///< disable an event being triggered for that category.
            uint32_t processId;                             ///< [out] Host processId that set this configuration (ignored when setting
                                                            ///< the configuration).

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_ras_handle_t m_handle = nullptr;         ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanRas( void ) = delete;
        SysmanRas( 
            sysman_ras_handle_t handle,                     ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanRas( void ) = default;

        SysmanRas( SysmanRas const& other ) = delete;
        void operator=( SysmanRas const& other ) = delete;

        SysmanRas( SysmanRas&& other ) = delete;
        void operator=( SysmanRas&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get RAS properties of a given RAS error set - this enables discovery
        ///        of the type of RAS error set (correctable/uncorrectable) and if
        ///        located on a sub-device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            ras_properties_t* pProperties                   ///< [in,out] Structure describing RAS properties
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
        /// @throws result_t
        void __zecall
        GetConfig(
            ras_config_t* pConfig                           ///< [in,out] Will be populed with the current RAS configuration -
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
        /// @throws result_t
        void __zecall
        SetConfig(
            const ras_config_t* pConfig                     ///< [in] Change the RAS configuration - thresholds used to trigger events
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
        /// @throws result_t
        void __zecall
        GetState(
            ze::bool_t clear,                               ///< [in] Set to 1 to clear the counters of this type
            uint64_t* pTotalErrors,                         ///< [in,out] The number total number of errors that have occurred
            ras_details_t* pDetails = nullptr               ///< [in,out][optional] Breakdown of where errors have occurred
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device diagnostic test suite
    class SysmanDiagnostics
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic test suite type
        enum class diag_type_t
        {
            SCAN = 0,                                       ///< Run SCAN diagnostics
            ARRAY,                                          ///< Run Array diagnostics

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic results
        enum class diag_result_t
        {
            NO_ERRORS = 0,                                  ///< Diagnostic completed without finding errors to repair
            ABORT,                                          ///< Diagnostic had problems running tests
            FAIL_CANT_REPAIR,                               ///< Diagnostic had problems setting up repairs
            REBOOT_FOR_REPAIR,                              ///< Diagnostics found errors, setup for repair and reboot is required to
                                                            ///< complete the process

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostic test
        struct diag_test_t
        {
            uint32_t index;                                 ///< [out] Index of the test
            char name[ZET_STRING_PROPERTY_SIZE];            ///< [out] Name of the test

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Diagnostics test suite properties
        struct diag_properties_t
        {
            diag_type_t type;                               ///< [out] The type of diagnostics test suite
            ze::bool_t onSubdevice;                         ///< [out] True if the resource is located on a sub-device; false means
                                                            ///< that the resource is on the device of the calling Sysman handle
            uint32_t subdeviceId;                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
            char name[ZET_STRING_PROPERTY_SIZE];            ///< [out] Name of the diagnostics test suite
            ze::bool_t haveTests;                           ///< [out] Indicates if this test suite has individual tests which can be
                                                            ///< run separately (use the function $SysmanDiagnosticsGetTests() to get
                                                            ///< the list of these tests)

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_diag_handle_t m_handle = nullptr;        ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanDiagnostics( void ) = delete;
        SysmanDiagnostics( 
            sysman_diag_handle_t handle,                    ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanDiagnostics( void ) = default;

        SysmanDiagnostics( SysmanDiagnostics const& other ) = delete;
        void operator=( SysmanDiagnostics const& other ) = delete;

        SysmanDiagnostics( SysmanDiagnostics&& other ) = delete;
        void operator=( SysmanDiagnostics&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get properties of a diagnostics test suite
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetProperties(
            diag_properties_t* pProperties                  ///< [in,out] Structure describing the properties of a diagnostics test
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
        /// @throws result_t
        void __zecall
        GetTests(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                            ///< If count is zero, then the driver will update the value with the total
                                                            ///< number of tests available.
                                                            ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                            ///< If count is larger than the number of tests available, then the driver
                                                            ///< will update the value with the correct number of tests available.
            diag_test_t* pTests = nullptr                   ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
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
        /// @throws result_t
        void __zecall
        RunTests(
            uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                            ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
            uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                            ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
            diag_result_t* pResult                          ///< [in,out] The result of the diagnostics
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a Sysman device event
    class SysmanEvent
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event configuration for a device
        struct event_config_t
        {
            uint32_t registered;                            ///< [in,out] List of registered events (Bitfield of events
                                                            ///< ::zet_sysman_event_type_t). ::ZET_SYSMAN_EVENT_TYPE_NONE indicates
                                                            ///< there are no registered events. ::ZET_SYSMAN_EVENT_TYPE_ALL indicates
                                                            ///< that all events are registered.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sysman_event_handle_t m_handle = nullptr;       ///< [in] handle of Sysman object
        Sysman* m_pSysman;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        SysmanEvent( void ) = delete;
        SysmanEvent( 
            sysman_event_handle_t handle,                   ///< [in] handle of Sysman object
            Sysman* pSysman                                 ///< [in] pointer to owner object
            );

        ~SysmanEvent( void ) = default;

        SysmanEvent( SysmanEvent const& other ) = delete;
        void operator=( SysmanEvent const& other ) = delete;

        SysmanEvent( SysmanEvent&& other ) = delete;
        void operator=( SysmanEvent&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getSysman( void ) const { return m_pSysman; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Find out which events are currently registered on the specified device
        ///        event handler
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetConfig(
            event_config_t* pConfig                         ///< [in,out] Will contain the current event configuration (list of
                                                            ///< registered events).
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set a new event configuration (list of registered events) on the
        ///        specified device event handler
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SetConfig(
            const event_config_t* pConfig                   ///< [in] New event configuration (list of registered events).
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
        /// @throws result_t
        void __zecall
        GetState(
            ze::bool_t clear,                               ///< [in] Indicates if the event list for this device should be cleared.
            uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                            ///< triggered by this device.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Wait for the specified list of event handles to receive any registered
        ///        events
        /// 
        /// @details
        ///     - If previous events arrived and were not cleared using
        ///       ::zetSysmanEventGetState(), this call will return immediately.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __zecall
        Listen(
            ze::Driver* pDriver,                            ///< [in] pointer to the driver instance
            uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                            ///< ::ZET_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                            ///< ::ZET_EVENT_WAIT_INFINITE to block until events arrive.
            uint32_t count,                                 ///< [in] Number of handles in phEvents
            SysmanEvent** ppEvents,                         ///< [in][range(0, count)] Handle of events that should be listened to
            uint32_t* pEvents                               ///< [in,out] Bitfield of events ::zet_sysman_event_type_t that have been
                                                            ///< triggered by any of the supplied event handles. If timeout is not
                                                            ///< ::ZET_EVENT_WAIT_INFINITE and this value is
                                                            ///< ::ZET_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::version_t to std::string
    std::string to_string( const Sysman::version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::engine_type_t to std::string
    std::string to_string( const Sysman::engine_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::properties_t to std::string
    std::string to_string( const Sysman::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_mode_t to std::string
    std::string to_string( const Sysman::sched_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeout_properties_t to std::string
    std::string to_string( const Sysman::sched_timeout_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::sched_timeslice_properties_t to std::string
    std::string to_string( const Sysman::sched_timeslice_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::perf_profile_t to std::string
    std::string to_string( const Sysman::perf_profile_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::process_state_t to std::string
    std::string to_string( const Sysman::process_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::repair_status_t to std::string
    std::string to_string( const Sysman::repair_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_address_t to std::string
    std::string to_string( const Sysman::pci_address_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_speed_t to std::string
    std::string to_string( const Sysman::pci_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_properties_t to std::string
    std::string to_string( const Sysman::pci_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_link_status_t to std::string
    std::string to_string( const Sysman::pci_link_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_link_qual_issues_t to std::string
    std::string to_string( const Sysman::pci_link_qual_issues_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_link_stab_issues_t to std::string
    std::string to_string( const Sysman::pci_link_stab_issues_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_state_t to std::string
    std::string to_string( const Sysman::pci_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_type_t to std::string
    std::string to_string( const Sysman::pci_bar_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_bar_properties_t to std::string
    std::string to_string( const Sysman::pci_bar_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::pci_stats_t to std::string
    std::string to_string( const Sysman::pci_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::freq_domain_t to std::string
    std::string to_string( const Sysman::freq_domain_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sysman::event_type_t to std::string
    std::string to_string( const Sysman::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_properties_t to std::string
    std::string to_string( const SysmanPower::power_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_energy_counter_t to std::string
    std::string to_string( const SysmanPower::power_energy_counter_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_sustained_limit_t to std::string
    std::string to_string( const SysmanPower::power_sustained_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_burst_limit_t to std::string
    std::string to_string( const SysmanPower::power_burst_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::power_peak_limit_t to std::string
    std::string to_string( const SysmanPower::power_peak_limit_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPower::energy_threshold_t to std::string
    std::string to_string( const SysmanPower::energy_threshold_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_properties_t to std::string
    std::string to_string( const SysmanFrequency::freq_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_range_t to std::string
    std::string to_string( const SysmanFrequency::freq_range_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_reasons_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_reasons_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_state_t to std::string
    std::string to_string( const SysmanFrequency::freq_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::freq_throttle_time_t to std::string
    std::string to_string( const SysmanFrequency::freq_throttle_time_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_mode_t to std::string
    std::string to_string( const SysmanFrequency::oc_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_capabilities_t to std::string
    std::string to_string( const SysmanFrequency::oc_capabilities_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFrequency::oc_config_t to std::string
    std::string to_string( const SysmanFrequency::oc_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_group_t to std::string
    std::string to_string( const SysmanEngine::engine_group_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_properties_t to std::string
    std::string to_string( const SysmanEngine::engine_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEngine::engine_stats_t to std::string
    std::string to_string( const SysmanEngine::engine_stats_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_type_t to std::string
    std::string to_string( const SysmanStandby::standby_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_properties_t to std::string
    std::string to_string( const SysmanStandby::standby_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanStandby::standby_promo_mode_t to std::string
    std::string to_string( const SysmanStandby::standby_promo_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFirmware::firmware_properties_t to std::string
    std::string to_string( const SysmanFirmware::firmware_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_type_t to std::string
    std::string to_string( const SysmanMemory::mem_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_health_t to std::string
    std::string to_string( const SysmanMemory::mem_health_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_properties_t to std::string
    std::string to_string( const SysmanMemory::mem_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_state_t to std::string
    std::string to_string( const SysmanMemory::mem_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanMemory::mem_bandwidth_t to std::string
    std::string to_string( const SysmanMemory::mem_bandwidth_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_status_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_qual_issues_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_qual_issues_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_stab_issues_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_stab_issues_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_uuid_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_speed_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_properties_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_link_type_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_link_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_config_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_state_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFabricPort::fabric_port_throughput_t to std::string
    std::string to_string( const SysmanFabricPort::fabric_port_throughput_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_sensors_t to std::string
    std::string to_string( const SysmanTemperature::temp_sensors_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_properties_t to std::string
    std::string to_string( const SysmanTemperature::temp_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_threshold_t to std::string
    std::string to_string( const SysmanTemperature::temp_threshold_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanTemperature::temp_config_t to std::string
    std::string to_string( const SysmanTemperature::temp_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_voltage_status_t to std::string
    std::string to_string( const SysmanPsu::psu_voltage_status_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_properties_t to std::string
    std::string to_string( const SysmanPsu::psu_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanPsu::psu_state_t to std::string
    std::string to_string( const SysmanPsu::psu_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_mode_t to std::string
    std::string to_string( const SysmanFan::fan_speed_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_speed_units_t to std::string
    std::string to_string( const SysmanFan::fan_speed_units_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_temp_speed_t to std::string
    std::string to_string( const SysmanFan::fan_temp_speed_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_properties_t to std::string
    std::string to_string( const SysmanFan::fan_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanFan::fan_config_t to std::string
    std::string to_string( const SysmanFan::fan_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_properties_t to std::string
    std::string to_string( const SysmanLed::led_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanLed::led_state_t to std::string
    std::string to_string( const SysmanLed::led_state_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_error_type_t to std::string
    std::string to_string( const SysmanRas::ras_error_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_properties_t to std::string
    std::string to_string( const SysmanRas::ras_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_details_t to std::string
    std::string to_string( const SysmanRas::ras_details_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanRas::ras_config_t to std::string
    std::string to_string( const SysmanRas::ras_config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_type_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_result_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_result_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_test_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_test_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanDiagnostics::diag_properties_t to std::string
    std::string to_string( const SysmanDiagnostics::diag_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts SysmanEvent::event_config_t to std::string
    std::string to_string( const SysmanEvent::event_config_t val );

} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_SYSMAN_HPP
