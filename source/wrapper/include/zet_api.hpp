/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_api.hpp
 *
 */
#ifndef _ZET_API_HPP
#define _ZET_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "zet_api.h"

// 'core' C++ API headers
#include "ze_api.hpp"

// Intel 'oneAPI' Level-Zero Tool API common types
#pragma region common
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle to a driver instance
    class Driver;
    struct _driver_handle_t;
    using driver_handle_t = _driver_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of device object
    class Device;
    struct _device_handle_t;
    using device_handle_t = _device_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of context object
    class Context;
    struct _context_handle_t;
    using context_handle_t = _context_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of module object
    class Module;
    struct _module_handle_t;
    using module_handle_t = _module_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of function object
    class Kernel;
    struct _kernel_handle_t;
    using kernel_handle_t = _kernel_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric group's object
    class MetricGroup;
    struct _metric_group_handle_t;
    using metric_group_handle_t = _metric_group_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric's object
    class Metric;
    struct _metric_handle_t;
    using metric_handle_t = _metric_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric streamer's object
    class MetricStreamer;
    struct _metric_streamer_handle_t;
    using metric_streamer_handle_t = _metric_streamer_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query pool's object
    class MetricQueryPool;
    struct _metric_query_pool_handle_t;
    using metric_query_pool_handle_t = _metric_query_pool_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of metric query's object
    class MetricQuery;
    struct _metric_query_handle_t;
    using metric_query_handle_t = _metric_query_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of tracer object
    class TracerExp;
    struct _tracer_exp_handle_t;
    using tracer_exp_handle_t = _tracer_exp_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Debug session handle
    class Debug;
    struct _debug_session_handle_t;
    using debug_session_handle_t = _debug_session_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Defines structure types
    enum class structure_type_t : uint32_t
    {
        METRIC_GROUP_PROPERTIES = 0x1,                  ///< ::zet_metric_group_properties_t
        METRIC_PROPERTIES = 0x2,                        ///< ::zet_metric_properties_t
        METRIC_STREAMER_DESC = 0x3,                     ///< ::zet_metric_streamer_desc_t
        METRIC_QUERY_POOL_DESC = 0x4,                   ///< ::zet_metric_query_pool_desc_t
        PROFILE_PROPERTIES = 0x5,                       ///< ::zet_profile_properties_t
        DEVICE_DEBUG_PROPERTIES = 0x6,                  ///< ::zet_device_debug_properties_t
        DEBUG_MEMORY_SPACE_DESC = 0x7,                  ///< ::zet_debug_memory_space_desc_t
        DEBUG_REGSET_PROPERTIES = 0x8,                  ///< ::zet_debug_regset_properties_t
        TRACER_EXP_DESC = 0x00010001,                   ///< ::zet_tracer_exp_desc_t
        FORCE_UINT32 = 0x7fffffff

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Base for all properties types
    struct base_properties_t
    {
        structure_type_t stype;                         ///< [in] type of this structure
        void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Base for all descriptor types
    struct base_desc_t
    {
        structure_type_t stype;                         ///< [in] type of this structure
        const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported value types
    enum class value_type_t : uint32_t
    {
        UINT32 = 0,                                     ///< 32-bit unsigned-integer
        UINT64 = 1,                                     ///< 64-bit unsigned-integer
        FLOAT32 = 2,                                    ///< 32-bit floating-point
        FLOAT64 = 3,                                    ///< 64-bit floating-point
        BOOL8 = 4,                                      ///< 8-bit boolean
        FORCE_UINT32 = 0x7fffffff

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Union of values
    union value_t
    {
        uint32_t ui32;                                  ///< [out] 32-bit unsigned-integer
        uint64_t ui64;                                  ///< [out] 32-bit unsigned-integer
        float fp32;                                     ///< [out] 32-bit floating-point
        double fp64;                                    ///< [out] 64-bit floating-point
        ze::bool_t b8;                                  ///< [out] 8-bit boolean

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Typed value
    struct typed_value_t
    {
        value_type_t type;                              ///< [out] type of value
        value_t value;                                  ///< [out] value

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts structure_type_t to std::string
    std::string to_string( const structure_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_properties_t to std::string
    std::string to_string( const base_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_desc_t to std::string
    std::string to_string( const base_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( const value_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_t to std::string
    std::string to_string( const value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_t to std::string
    std::string to_string( const typed_value_t val );

} // namespace zet

namespace zet
{
    using result_t = ze::result_t;
    using exception_t = ze::exception_t;

} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool APIs for Device
#pragma region device
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for driver instance
    class Driver : public ze::Driver
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Driver::Driver;
        ~Driver( void ) = default;

        Driver( Driver const& other ) = delete;
        void operator=( Driver const& other ) = delete;

        Driver( Driver&& other ) = delete;
        void operator=( Driver&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device : public ze::Device
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device debug property flags
        struct debug_property_flags_t
        {
            uint32_t value;
            debug_property_flags_t() : value(0) {}
            debug_property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum debug_property_flag_t
        {
            DEBUG_PROPERTY_FLAG_ATTACH = ZE_BIT(0),         ///< the device supports attaching for debug
            DEBUG_PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device debug properties queried using ::zetDeviceGetDebugProperties.
        struct debug_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_DEBUG_PROPERTIES; ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            debug_property_flags_t flags;                   ///< [out] returns 0 (none) or a valid combination of
                                                            ///< ::zet_device_debug_property_flag_t

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Device::Device;
        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves debug properties of the device.
        /// @throws result_t
        void ZE_APICALL
        GetDebugProperties(
            debug_properties_t* pDebugProperties            ///< [in,out] query result for debug properties
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::debug_property_flags_t to std::string
    std::string to_string( const Device::debug_property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::debug_properties_t to std::string
    std::string to_string( const Device::debug_properties_t val );

} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool APIs for Context
#pragma region context
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for context
    class Context : public ze::Context
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Context::Context;
        ~Context( void ) = default;

        Context( Context const& other ) = delete;
        void operator=( Context const& other ) = delete;

        Context( Context&& other ) = delete;
        void operator=( Context&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Activates metric groups.
        /// 
        /// @details
        ///     - Immediately reconfigures the device to activate only those metric
        ///       groups provided.
        ///     - Any metric groups previously activated but not provided will be
        ///       deactivated.
        ///     - Deactivating metric groups that are still in-use will result in
        ///       undefined behavior.
        ///     - All metric groups must have different domains, see
        ///       ::zet_metric_group_properties_t.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// @throws result_t
        void ZE_APICALL
        ActivateMetricGroups(
            Device* pDevice,                                ///< [in] pointer to the device
            uint32_t count,                                 ///< [in] metric group count to activate; must be 0 if `nullptr ==
                                                            ///< phMetricGroups`
            MetricGroup** ppMetricGroups = nullptr          ///< [in][optional][range(0, count)] handles of the metric groups to activate.
                                                            ///< nullptr deactivates all previously used metric groups.
                                                            ///< all metrics groups must come from a different domains.
                                                            ///< metric query and metric stream must use activated metric groups.
            );

    };

} // namespace zet

namespace zet
{
} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool APIs for Command List
#pragma region cmdlist
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList : public ze::CommandList
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::CommandList::CommandList;
        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Append metric streamer marker into a command list.
        /// 
        /// @details
        ///     - The application must ensure the metric streamer is accessible by the
        ///       device on which the command list was created.
        ///     - The application must ensure the command list and metric streamer were
        ///       created on the same context.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - Allow to associate metric stream time based metrics with executed
        ///       workload.
        /// @throws result_t
        void ZE_APICALL
        AppendMetricStreamerMarker(
            MetricStreamer* pMetricStreamer,                ///< [in] pointer to the metric streamer
            uint32_t value                                  ///< [in] streamer marker value
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query begin into a command list.
        /// 
        /// @details
        ///     - The application must ensure the metric query is accessible by the
        ///       device on which the command list was created.
        ///     - The application must ensure the command list and metric query were
        ///       created on the same context.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void ZE_APICALL
        AppendMetricQueryBegin(
            MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query end into a command list.
        /// 
        /// @details
        ///     - The application must ensure the metric query and events are accessible
        ///       by the device on which the command list was created.
        ///     - The application must ensure the command list, events and metric query
        ///       were created on the same context.
        ///     - The application must ensure the signal event was **not** created from
        ///       an event pool that was created using
        ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void ZE_APICALL
        AppendMetricQueryEnd(
            MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
            ze::Event* pSignalEvent = nullptr,              ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            ze::Event** ppWaitEvents = nullptr              ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query commands to flush all caches.
        /// 
        /// @details
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void ZE_APICALL
        AppendMetricMemoryBarrier(
            void
            );

    };

} // namespace zet

namespace zet
{
} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool APIs for Module
#pragma region module
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module : public ze::Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module debug info formats.
        enum class debug_info_format_t : uint32_t
        {
            ELF_DWARF = 0,                                  ///< Format is ELF/DWARF
            FORCE_UINT32 = 0x7fffffff

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Module::Module;
        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve debug info from module.
        /// 
        /// @details
        ///     - The caller can pass nullptr for pDebugInfo when querying only for
        ///       size.
        ///     - The implementation will copy the native binary into a buffer supplied
        ///       by the caller.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetDebugInfo(
            debug_info_format_t format,                     ///< [in] debug info format requested
            size_t* pSize,                                  ///< [in,out] size of debug info in bytes
            uint8_t* pDebugInfo = nullptr                   ///< [in,out][optional] byte pointer to debug info
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for kernel
    class Kernel : public ze::Kernel
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supportted profile features
        struct profile_flags_t
        {
            uint32_t value;
            profile_flags_t() : value(0) {}
            profile_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum profile_flag_t
        {
            PROFILE_FLAG_REGISTER_REALLOCATION = ZE_BIT(0), ///< request the compiler attempt to minimize register usage as much as
                                                            ///< possible to allow for instrumentation
            PROFILE_FLAG_FREE_REGISTER_INFO = ZE_BIT(1),    ///< request the compiler generate free register info
            PROFILE_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported profile token types
        enum class profile_token_type_t : uint32_t
        {
            FREE_REGISTER = 0,                              ///< GRF info
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profiling meta-data for instrumentation
        struct profile_properties_t
        {
            structure_type_t stype = structure_type_t::PROFILE_PROPERTIES;  ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            profile_flags_t flags;                          ///< [out] indicates which flags were enabled during compilation.
                                                            ///< returns 0 (none) or a combination of ::zet_profile_flag_t
            uint32_t numTokens;                             ///< [out] number of tokens immediately following this structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile free register token detailing unused registers in the current
        ///        function
        struct profile_free_register_token_t
        {
            profile_token_type_t type;                      ///< [out] type of token
            uint32_t size;                                  ///< [out] total size of the token, in bytes
            uint32_t count;                                 ///< [out] number of register sequences immediately following this
                                                            ///< structure

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Profile register sequence detailing consecutive bytes, all of which
        ///        are unused
        struct profile_register_sequence_t
        {
            uint32_t start;                                 ///< [out] starting byte in the register table, representing the start of
                                                            ///< unused bytes in the current function
            uint32_t count;                                 ///< [out] number of consecutive bytes in the sequence, starting from start

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Kernel::Kernel;
        ~Kernel( void ) = default;

        Kernel( Kernel const& other ) = delete;
        void operator=( Kernel const& other ) = delete;

        Kernel( Kernel&& other ) = delete;
        void operator=( Kernel&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve profiling information generated for the kernel.
        /// 
        /// @details
        ///     - Module must be created using the following build option:
        ///         + "-zet-profile-flags <n>" - enable generation of profile
        ///           information
        ///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - profile_properties_t: pointer to profile properties
        /// 
        /// @throws result_t
        profile_properties_t ZE_APICALL
        GetProfileInfo(
            void
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::debug_info_format_t to std::string
    std::string to_string( const Module::debug_info_format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_flags_t to std::string
    std::string to_string( const Kernel::profile_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_properties_t to std::string
    std::string to_string( const Kernel::profile_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_token_type_t to std::string
    std::string to_string( const Kernel::profile_token_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_free_register_token_t to std::string
    std::string to_string( const Kernel::profile_free_register_token_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_register_sequence_t to std::string
    std::string to_string( const Kernel::profile_register_sequence_t val );

} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool APIs for Program Debug
#pragma region debug
namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for Debug API
    class Debug
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported debug event flags.
        struct event_flags_t
        {
            uint32_t value;
            event_flags_t() : value(0) {}
            event_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum event_flag_t
        {
            EVENT_FLAG_NEED_ACK = ZE_BIT(0),                ///< The event needs to be acknowledged by calling
                                                            ///< ::zetDebugAcknowledgeEvent.
            EVENT_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported debug event types.
        enum class event_type_t : uint32_t
        {
            INVALID = 0,                                    ///< The event is invalid
            DETACHED = 1,                                   ///< The tool was detached
            PROCESS_ENTRY = 2,                              ///< The debuggee process created command queues on the device
            PROCESS_EXIT = 3,                               ///< The debuggee process destroyed all command queues on the device
            MODULE_LOAD = 4,                                ///< An in-memory module was loaded onto the device
            MODULE_UNLOAD = 5,                              ///< An in-memory module is about to get unloaded from the device
            THREAD_STOPPED = 6,                             ///< The thread stopped due to a device exception
            THREAD_UNAVAILABLE = 7,                         ///< The thread is not available to be stopped
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported debug detach reasons.
        enum class detach_reason_t : uint32_t
        {
            INVALID = 0,                                    ///< The detach reason is not valid
            HOST_EXIT = 1,                                  ///< The host process exited
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device memory space types.
        enum class memory_space_type_t : uint32_t
        {
            DEFAULT = 0,                                    ///< default memory space (attribute may be omitted)
            SLM = 1,                                        ///< shared local memory space (GPU-only)
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device register set types.
        enum class regset_type_t : uint32_t
        {
            INVALID = 0,                                    ///< An invalid register set
            GPR = 1,                                        ///< The general purpose register set
            ACC = 2,                                        ///< The accumulator register set
            ADDR = 3,                                       ///< The address register set
            FLAG = 4,                                       ///< The flags register set
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device register set flags.
        struct regset_flags_t
        {
            uint32_t value;
            regset_flags_t() : value(0) {}
            regset_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum regset_flag_t
        {
            REGSET_FLAG_READ_ONLY = ZE_BIT(0),              ///< register set is read-only
            REGSET_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug configuration provided to ::zetDebugAttach
        struct config_t
        {
            uint32_t pid;                                   ///< [in] the host process identifier

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event information for ::ZET_DEBUG_EVENT_TYPE_DETACHED
        struct event_info_detached_t
        {
            detach_reason_t reason;                         ///< [out] the detach reason

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event information for ::ZET_DEBUG_EVENT_TYPE_MODULE_LOAD and
        ///        ::ZET_DEBUG_EVENT_TYPE_MODULE_UNLOAD
        struct event_info_module_t
        {
            Module::debug_info_format_t format;             ///< [out] the module format
            uint64_t moduleBegin;                           ///< [out] the begin address of the in-memory module
            uint64_t moduleEnd;                             ///< [out] the end address of the in-memory module
            uint64_t load;                                  ///< [out] the load address of the module on the device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event information for ::ZET_DEBUG_EVENT_TYPE_THREAD_STOPPED and
        ///        ::ZET_DEBUG_EVENT_TYPE_THREAD_UNAVAILABLE
        struct event_info_thread_stopped_t
        {
            ze::Device::thread_t thread;                    ///< [out] the stopped/unavailable thread

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event type-specific information
        union event_info_t
        {
            event_info_detached_t detached;                 ///< [out] type == ::ZET_DEBUG_EVENT_TYPE_DETACHED
            event_info_module_t module;                     ///< [out] type == ::ZET_DEBUG_EVENT_TYPE_MODULE_LOAD or
                                                            ///< ::ZET_DEBUG_EVENT_TYPE_MODULE_UNLOAD
            event_info_thread_stopped_t thread;             ///< [out] type == ::ZET_DEBUG_EVENT_TYPE_THREAD_STOPPED or
                                                            ///< ::ZET_DEBUG_EVENT_TYPE_THREAD_UNAVAILABLE

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief A debug event on the device.
        struct event_t
        {
            event_type_t type;                              ///< [out] the event type
            event_flags_t flags;                            ///< [out] returns 0 (none) or a combination of ::zet_debug_event_flag_t
            event_info_t info;                              ///< [out] event type specific information

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device memory space descriptor
        struct memory_space_desc_t
        {
            structure_type_t stype = structure_type_t::DEBUG_MEMORY_SPACE_DESC; ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            memory_space_type_t type;                       ///< [in] type of memory space
            uint64_t address;                               ///< [in] the virtual address within the memory space

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device register set properties queried using
        ///        ::zetDebugGetRegisterSetProperties.
        struct regset_properties_t
        {
            structure_type_t stype = structure_type_t::DEBUG_REGSET_PROPERTIES; ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            regset_type_t type;                             ///< [out] register set type
            regset_flags_t flags;                           ///< [out] register set flags
            uint32_t count;                                 ///< [out] number of registers in the set
            value_type_t valueType;                         ///< [out] register value type
            size_t valueSize;                               ///< [out] register value size in bytes

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        debug_session_handle_t m_handle;                ///< [in] debug session handle

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Debug( void ) = delete;
        Debug( 
            debug_session_handle_t handle                   ///< [in] debug session handle
            );

        ~Debug( void ) = default;

        Debug( Debug const& other ) = delete;
        void operator=( Debug const& other ) = delete;

        Debug( Debug&& other ) = delete;
        void operator=( Debug&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Attach to a device.
        /// 
        /// @details
        ///     - The device must be enabled for debug; see
        ///       ::zesSchedulerSetComputeUnitDebugMode.
        /// @returns
        ///     - Debug*: debug session handle
        /// 
        /// @throws result_t
        static Debug* ZE_APICALL
        Attach(
            Device* pDevice,                                ///< [in] device handle
            const config_t* config                          ///< [in] the debug configuration
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Close a debug session.
        /// @throws result_t
        void ZE_APICALL
        Detach(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read the topmost debug event.
        /// @returns
        ///     - ze::bool_t:'0' when ZE::RESULT_NOT_READY
        /// @throws result_t
        ze::bool_t ZE_APICALL
        ReadEvent(
            uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                            ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then immediately returns the status of the event;
                                                            ///< if UINT64_MAX, then function will not return until complete or device
                                                            ///< is lost.
                                                            ///< Due to external dependencies, timeout may be rounded to the closest
                                                            ///< value allowed by the accuracy of those dependencies.
            event_t* event                                  ///< [in,out] a pointer to a ::zet_debug_event_t.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Acknowledge a debug event.
        /// @throws result_t
        void ZE_APICALL
        AcknowledgeEvent(
            const event_t* event                            ///< [in] a pointer to a ::zet_debug_event_t.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Interrupt device threads.
        /// @throws result_t
        void ZE_APICALL
        Interrupt(
            ze::Device::thread_t thread                     ///< [in] the thread to interrupt
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resume device threads.
        /// @throws result_t
        void ZE_APICALL
        Resume(
            ze::Device::thread_t thread                     ///< [in] the thread to resume
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read memory.
        /// 
        /// @details
        ///     - The thread identifier 'all' can be used for accessing the default
        ///       memory space, e.g. for setting breakpoints.
        /// @throws result_t
        void ZE_APICALL
        ReadMemory(
            ze::Device::thread_t thread,                    ///< [in] the thread identifier.
            const memory_space_desc_t* desc,                ///< [in] memory space descriptor
            size_t size,                                    ///< [in] the number of bytes to read
            void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Write memory.
        /// 
        /// @details
        ///     - The thread identifier 'all' can be used for accessing the default
        ///       memory space, e.g. for setting breakpoints.
        /// @throws result_t
        void ZE_APICALL
        WriteMemory(
            ze::Device::thread_t thread,                    ///< [in] the thread identifier.
            const memory_space_desc_t* desc,                ///< [in] memory space descriptor
            size_t size,                                    ///< [in] the number of bytes to write
            const void* buffer                              ///< [in] a buffer holding the pattern to write
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves debug register set properties.
        /// @throws result_t
        static void ZE_APICALL
        GetRegisterSetProperties(
            Device* pDevice,                                ///< [in] device handle
            uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of register set properties available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< register set properties.
                                                            ///< if count is larger than the number of register set properties
                                                            ///< available, then the driver will update the value with the correct
                                                            ///< number of registry set properties available.
            regset_properties_t* pRegisterSetProperties = nullptr   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                            ///< register set properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read register state.
        /// @throws result_t
        void ZE_APICALL
        ReadRegisters(
            ze::Device::thread_t thread,                    ///< [in] the thread identifier
            regset_type_t type,                             ///< [in] register set type
            uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                            ///< than ::zet_debug_regset_properties_t.count for the type
            uint32_t count,                                 ///< [in] the number of registers to read; start+count must be <=
                                                            ///< zet_debug_register_group_properties_t.count for the type
            void* pRegisterValues = nullptr                 ///< [in,out][optional][range(0, count)] buffer of register values
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Write register state.
        /// @throws result_t
        void ZE_APICALL
        WriteRegisters(
            ze::Device::thread_t thread,                    ///< [in] the thread identifier
            regset_type_t type,                             ///< [in] register set type
            uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                            ///< than ::zet_debug_regset_properties_t.count for the type
            uint32_t count,                                 ///< [in] the number of registers to write; start+count must be <=
                                                            ///< zet_debug_register_group_properties_t.count for the type
            void* pRegisterValues = nullptr                 ///< [in,out][optional][range(0, count)] buffer of register values
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_t to std::string
    std::string to_string( const Debug::config_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_flags_t to std::string
    std::string to_string( const Debug::event_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_type_t to std::string
    std::string to_string( const Debug::event_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::detach_reason_t to std::string
    std::string to_string( const Debug::detach_reason_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_detached_t to std::string
    std::string to_string( const Debug::event_info_detached_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_module_t to std::string
    std::string to_string( const Debug::event_info_module_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_thread_stopped_t to std::string
    std::string to_string( const Debug::event_info_thread_stopped_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_t to std::string
    std::string to_string( const Debug::event_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_t to std::string
    std::string to_string( const Debug::event_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_type_t to std::string
    std::string to_string( const Debug::memory_space_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_desc_t to std::string
    std::string to_string( const Debug::memory_space_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::regset_type_t to std::string
    std::string to_string( const Debug::regset_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::regset_flags_t to std::string
    std::string to_string( const Debug::regset_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::regset_properties_t to std::string
    std::string to_string( const Debug::regset_properties_t val );

} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool APIs for Metric
#pragma region metric
///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_GROUP_NAME
/// @brief Maximum metric group name string size
#define ZET_MAX_METRIC_GROUP_NAME  256
#endif // ZET_MAX_METRIC_GROUP_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_GROUP_DESCRIPTION
/// @brief Maximum metric group description string size
#define ZET_MAX_METRIC_GROUP_DESCRIPTION  256
#endif // ZET_MAX_METRIC_GROUP_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_NAME
/// @brief Maximum metric name string size
#define ZET_MAX_METRIC_NAME  256
#endif // ZET_MAX_METRIC_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_DESCRIPTION
/// @brief Maximum metric description string size
#define ZET_MAX_METRIC_DESCRIPTION  256
#endif // ZET_MAX_METRIC_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_COMPONENT
/// @brief Maximum metric component string size
#define ZET_MAX_METRIC_COMPONENT  256
#endif // ZET_MAX_METRIC_COMPONENT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_RESULT_UNITS
/// @brief Maximum metric result units string size
#define ZET_MAX_METRIC_RESULT_UNITS  256
#endif // ZET_MAX_METRIC_RESULT_UNITS

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric group
    class MetricGroup
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group sampling type
        struct sampling_type_flags_t
        {
            uint32_t value;
            sampling_type_flags_t() : value(0) {}
            sampling_type_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum sampling_type_flag_t
        {
            SAMPLING_TYPE_FLAG_EVENT_BASED = ZE_BIT(0),     ///< Event based sampling
            SAMPLING_TYPE_FLAG_TIME_BASED = ZE_BIT(1),      ///< Time based sampling
            SAMPLING_TYPE_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group calculation type
        enum class calculation_type_t : uint32_t
        {
            METRIC_VALUES = 0,                              ///< Calculated metric values from raw data.
            MAX_METRIC_VALUES = 1,                          ///< Maximum metric values.
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group properties queried using ::zetMetricGroupGetProperties
        struct properties_t
        {
            structure_type_t stype = structure_type_t::METRIC_GROUP_PROPERTIES; ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            char name[ZET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
            char description[ZET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
            sampling_type_flags_t samplingType;             ///< [out] metric group sampling type.
                                                            ///< returns a combination of ::zet_metric_group_sampling_type_flag_t.
            uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                            ///< groups from different domains.
            uint32_t metricCount;                           ///< [out] metric count belonging to this group

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_group_handle_t m_handle = nullptr;       ///< [in] handle of metric group object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricGroup( void ) = delete;
        MetricGroup( 
            metric_group_handle_t handle,                   ///< [in] handle of metric group object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricGroup( void ) = default;

        MetricGroup( MetricGroup const& other ) = delete;
        void operator=( MetricGroup const& other ) = delete;

        MetricGroup( MetricGroup&& other ) = delete;
        void operator=( MetricGroup&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves metric group for a device.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void ZE_APICALL
        Get(
            Device* pDevice,                                ///< [in] pointer to the device
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metric groups available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< metric groups.
                                                            ///< if count is larger than the number of metric groups available, then
                                                            ///< the driver will update the value with the correct number of metric
                                                            ///< groups available.
            MetricGroup** ppMetricGroups = nullptr          ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                            ///< groups
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void ZE_APICALL
        GetProperties(
            properties_t* pProperties                       ///< [in,out] metric group properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Calculates metric values from raw data.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void ZE_APICALL
        CalculateMetricValues(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            calculation_type_t type,                        ///< [in] calculation type to be applied on raw data
            size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
            const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
            uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metric values to be calculated.
                                                            ///< if count is non-zero, then driver will only calculate that number of
                                                            ///< metric values.
                                                            ///< if count is larger than the number available in the raw data buffer,
                                                            ///< then the driver will update the value with the actual number of metric
                                                            ///< values to be calculated.
            typed_value_t* pMetricValues = nullptr          ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                            ///< metrics
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric
    class Metric
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric types
        enum class type_t : uint32_t
        {
            DURATION = 0,                                   ///< Metric type: duration
            EVENT = 1,                                      ///< Metric type: event
            EVENT_WITH_RANGE = 2,                           ///< Metric type: event with range
            THROUGHPUT = 3,                                 ///< Metric type: throughput
            TIMESTAMP = 4,                                  ///< Metric type: timestamp
            FLAG = 5,                                       ///< Metric type: flag
            RATIO = 6,                                      ///< Metric type: ratio
            RAW = 7,                                        ///< Metric type: raw
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric properties queried using ::zetMetricGetProperties
        struct properties_t
        {
            structure_type_t stype = structure_type_t::METRIC_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            char name[ZET_MAX_METRIC_NAME];                 ///< [out] metric name
            char description[ZET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
            char component[ZET_MAX_METRIC_COMPONENT];       ///< [out] metric component
            uint32_t tierNumber;                            ///< [out] number of tier
            type_t metricType;                              ///< [out] metric type
            value_type_t resultType;                        ///< [out] metric result type
            char resultUnits[ZET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_handle_t m_handle;                       ///< [in] handle of metric object
        MetricGroup* m_pMetricGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Metric( void ) = delete;
        Metric( 
            metric_handle_t handle,                         ///< [in] handle of metric object
            MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
            );

        ~Metric( void ) = default;

        Metric( Metric const& other ) = delete;
        void operator=( Metric const& other ) = delete;

        Metric( Metric&& other ) = delete;
        void operator=( Metric&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getMetricgroup( void ) const { return m_pMetricGroup; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves metric from a metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void ZE_APICALL
        Get(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metrics available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                            ///< if count is larger than the number of metrics available, then the
                                                            ///< driver will update the value with the correct number of metrics available.
            Metric** ppMetrics = nullptr                    ///< [in,out][optional][range(0, *pCount)] array of pointer to metrics
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a metric.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void ZE_APICALL
        GetProperties(
            properties_t* pProperties                       ///< [in,out] metric properties
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric streamer
    class MetricStreamer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric streamer descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::METRIC_STREAMER_DESC;///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                            ///< will be signalled
            uint32_t samplingPeriod;                        ///< [in,out] streamer sampling period in nanoseconds

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_streamer_handle_t m_handle;              ///< [in] handle of metric streamer object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric streamer

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricStreamer( void ) = delete;
        MetricStreamer( 
            metric_streamer_handle_t handle,                ///< [in] handle of metric streamer object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric streamer
            );

        ~MetricStreamer( void ) = default;

        MetricStreamer( MetricStreamer const& other ) = delete;
        void operator=( MetricStreamer const& other ) = delete;

        MetricStreamer( MetricStreamer&& other ) = delete;
        void operator=( MetricStreamer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens metric streamer for a device.
        /// 
        /// @details
        ///     - The notification event must have been created from an event pool that
        ///       was created using ::ZE_EVENT_POOL_FLAG_HOST_VISIBLE flag.
        ///     - The notification event must **not** have been created from an event
        ///       pool that was created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP
        ///       flag.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// @returns
        ///     - MetricStreamer*: handle of metric streamer
        /// 
        /// @throws result_t
        static MetricStreamer* ZE_APICALL
        Open(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            desc_t* desc,                                   ///< [in,out] metric streamer descriptor
            ze::Event* pNotificationEvent = nullptr         ///< [in][optional] event used for report availability notification
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes metric streamer.
        /// 
        /// @details
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same metric streamer handle.
        /// @throws result_t
        void ZE_APICALL
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reads data from metric streamer.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void ZE_APICALL
        ReadData(
            uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                            ///< if UINT32_MAX, then function will retrieve all reports available
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
                                                            ///< if size is larger than size needed for all reports, then driver will
                                                            ///< update the value with the actual size needed.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing streamer
                                                            ///< reports in raw format
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query pool
    class MetricQueryPool
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool types
        enum class type_t : uint32_t
        {
            PERFORMANCE = 0,                                ///< Performance metric query pool.
            EXECUTION = 1,                                  ///< Skips workload execution between begin/end calls.
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool description
        struct desc_t
        {
            structure_type_t stype = structure_type_t::METRIC_QUERY_POOL_DESC;  ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            type_t type = type_t::PERFORMANCE;              ///< [in] Query pool type.
            uint32_t count;                                 ///< [in] Internal slots count within query pool object.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_pool_handle_t m_handle;            ///< [in] handle of metric query pool object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric query pool

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQueryPool( void ) = delete;
        MetricQueryPool( 
            metric_query_pool_handle_t handle,              ///< [in] handle of metric query pool object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric query pool
            );

        ~MetricQueryPool( void ) = default;

        MetricQueryPool( MetricQueryPool const& other ) = delete;
        void operator=( MetricQueryPool const& other ) = delete;

        MetricQueryPool( MetricQueryPool&& other ) = delete;
        void operator=( MetricQueryPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool of metric queries on the context.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - MetricQueryPool*: handle of metric query pool
        /// 
        /// @throws result_t
        static MetricQueryPool* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] metric group associated with the query object.
            const desc_t* desc                              ///< [in] metric query pool descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a query pool object.
        /// 
        /// @details
        ///     - The application must destroy all query handles created from the pool
        ///       before destroying the pool itself.
        ///     - The application must ensure the device is not currently referencing
        ///       the any query within the pool before it is deleted.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same query pool handle.
        ///     - The implementation of this function must be thread-safe.
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query
    class MetricQuery
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_handle_t m_handle;                 ///< [in] handle of metric query object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQuery( void ) = delete;
        MetricQuery( 
            metric_query_handle_t handle,                   ///< [in] handle of metric query object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricQuery( void ) = default;

        MetricQuery( MetricQuery const& other ) = delete;
        void operator=( MetricQuery const& other ) = delete;

        MetricQuery( MetricQuery&& other ) = delete;
        void operator=( MetricQuery&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates metric query from the pool.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - MetricQuery*: handle of metric query
        /// 
        /// @throws result_t
        static MetricQuery* ZE_APICALL
        Create(
            MetricQueryPool* pMetricQueryPool,              ///< [in] pointer to the metric query pool
            uint32_t index                                  ///< [in] index of the query within the pool
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a metric query object.
        /// 
        /// @details
        ///     - The application must ensure the device is not currently referencing
        ///       the query before it is deleted.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same query handle.
        ///     - The implementation of this function must be thread-safe.
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            MetricQuery* pMetricQuery                       ///< [in][release] pointer to metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resets a metric query object back to inital state.
        /// 
        /// @details
        ///     - The application must ensure the device is not currently referencing
        ///       the query before it is reset
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same query handle.
        /// @throws result_t
        void ZE_APICALL
        Reset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves raw data for a given metric query.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void ZE_APICALL
        GetData(
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
                                                            ///< if size is larger than size needed for all reports, then driver will
                                                            ///< update the value with the actual size needed.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                            ///< reports in raw format
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type_flags_t to std::string
    std::string to_string( const MetricGroup::sampling_type_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_t to std::string
    std::string to_string( const MetricGroup::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::calculation_type_t to std::string
    std::string to_string( const MetricGroup::calculation_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( const Metric::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_t to std::string
    std::string to_string( const Metric::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricStreamer::desc_t to std::string
    std::string to_string( const MetricStreamer::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::type_t to std::string
    std::string to_string( const MetricQueryPool::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_t to std::string
    std::string to_string( const MetricQueryPool::desc_t val );

} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool APIs for Program Instrumentation (PIN)
#pragma region pin
namespace zet
{
} // namespace zet

namespace zet
{
} // namespace zet
#pragma endregion
// Intel 'oneAPI' Level-Zero Tool Experimental Extension APIs for API Tracing
#pragma region tracing
///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_API_TRACING_EXP_NAME
/// @brief API Tracing Experimental Extension Name
#define ZET_API_TRACING_EXP_NAME  "ZET_experimental_api_tracing"
#endif // ZET_API_TRACING_EXP_NAME

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief API Tracing Experimental Extension Version(s)
    enum class api_tracing_exp_version_t : uint32_t
    {
        _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
        CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version
        FORCE_UINT32 = 0x7fffffff

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for tracer
    class TracerExp
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Alias the existing callbacks definition for 'core' callbacks
        using core_callbacks_t = ze_callbacks_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Tracer descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::TRACER_EXP_DESC; ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            void* pUserData;                                ///< [in] pointer passed to every tracer's callbacks

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        tracer_exp_handle_t m_handle;                   ///< [in] handle of tracer object
        Driver* m_pDriver;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the tracer object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        TracerExp( void ) = delete;
        TracerExp( 
            tracer_exp_handle_t handle,                     ///< [in] handle of tracer object
            Driver* pDriver,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the tracer object
            );

        ~TracerExp( void ) = default;

        TracerExp( TracerExp const& other ) = delete;
        void operator=( TracerExp const& other ) = delete;

        TracerExp( TracerExp&& other ) = delete;
        void operator=( TracerExp&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a tracer on the context.
        /// 
        /// @details
        ///     - The application must only use the tracer for the context which was
        ///       provided during creation.
        ///     - The tracer is created in the disabled state.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - TracerExp*: pointer to handle of tracer object created
        /// 
        /// @throws result_t
        static TracerExp* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            const desc_t* desc                              ///< [in] pointer to tracer descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a tracer.
        /// 
        /// @details
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        ///     - The implementation of this function must be thread-safe.
        ///     - The implementation of this function will stall and wait on any
        ///       outstanding threads executing callbacks before freeing any Host
        ///       allocations associated with this tracer.
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            TracerExp* pTracer                              ///< [in][release] pointer to tracer object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the collection of callbacks to be executed **before** driver
        ///        execution.
        /// 
        /// @details
        ///     - The application only needs to set the function pointers it is
        ///       interested in receiving; all others should be 'nullptr'
        ///     - The application must ensure that no other threads are executing
        ///       functions for which the tracing functions are changing.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void ZE_APICALL
        SetPrologues(
            core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the collection of callbacks to be executed **after** driver
        ///        execution.
        /// 
        /// @details
        ///     - The application only needs to set the function pointers it is
        ///       interested in receiving; all others should be 'nullptr'
        ///     - The application must ensure that no other threads are executing
        ///       functions for which the tracing functions are changing.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void ZE_APICALL
        SetEpilogues(
            core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Enables (or disables) the tracer
        /// 
        /// @details
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void ZE_APICALL
        SetEnabled(
            ze::bool_t enable                               ///< [in] enable the tracer if true; disable if false
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts api_tracing_exp_version_t to std::string
    std::string to_string( const api_tracing_exp_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts TracerExp::desc_t to std::string
    std::string to_string( const TracerExp::desc_t val );

} // namespace zet
#pragma endregion
#endif // defined(__cplusplus)
#endif // _ZET_API_HPP