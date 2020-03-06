/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_debug.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Program Debug
 *
 */
#ifndef _ZET_DEBUG_HPP
#define _ZET_DEBUG_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_API_VERSION
/// @brief The API version.
#define ZET_DEBUG_API_VERSION  1
#endif // ZET_DEBUG_API_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_TIMEOUT_INFINITE
/// @brief An infinite timeout.
#define ZET_DEBUG_TIMEOUT_INFINITE  0xffffffffffffffffull
#endif // ZET_DEBUG_TIMEOUT_INFINITE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_NONE
/// @brief No thread on the device.
#define ZET_DEBUG_THREAD_NONE  0xffffffffffffffffull
#endif // ZET_DEBUG_THREAD_NONE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_ALL
/// @brief All threads on the device.
#define ZET_DEBUG_THREAD_ALL  0xfffffffffffffffeull
#endif // ZET_DEBUG_THREAD_ALL

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Debug session handle
    class Debug;
    struct _debug_session_handle_t;
    using debug_session_handle_t = _debug_session_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for Debug API
    class Debug
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug event flags.
        enum class event_flags_t
        {
            DEBUG_EVENT_FLAG_NONE = 0,                      ///< No event flags
            DEBUG_EVENT_FLAG_STOPPED = ZE_BIT(0),           ///< The reporting thread stopped

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug event types.
        enum class event_type_t
        {
            DEBUG_EVENT_INVALID = 0,                        ///< The event is invalid
            DEBUG_EVENT_DETACHED,                           ///< The tool was detached
            DEBUG_EVENT_PROCESS_ENTRY,                      ///< The debuggee process created command queues on the device
            DEBUG_EVENT_PROCESS_EXIT,                       ///< The debuggee process destroyed all command queues on the device
            DEBUG_EVENT_MODULE_LOAD,                        ///< An in-memory module was loaded onto the device
            DEBUG_EVENT_MODULE_UNLOAD,                      ///< An in-memory module is about to get unloaded from the device
            DEBUG_EVENT_EXCEPTION,                          ///< The thread stopped due to a device exception

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug detach reason.
        enum class detach_reason_t
        {
            DEBUG_DETACH_INVALID = 0,                       ///< The detach reason is not valid
            DEBUG_DETACH_HOST_EXIT,                         ///< The host process exited

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory spaces for Intel Graphics devices.
        enum class memory_space_intel_graphics_t
        {
            DEBUG_MEMORY_SPACE_GEN_DEFAULT = 0,             ///< default memory space (attribute may be omitted)
            DEBUG_MEMORY_SPACE_GEN_SLM,                     ///< shared local memory space

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Register file types for Intel Graphics devices.
        enum class state_intel_graphics_t
        {
            DEBUG_STATE_GEN_INVALID = 0,                    ///< An invalid register file
            DEBUG_STATE_GEN_GRF,                            ///< The general register file
            DEBUG_STATE_GEN_ACC,                            ///< The accumulator register file
            DEBUG_STATE_GEN_ADDR,                           ///< The address register file
            DEBUG_STATE_GEN_FLAG,                           ///< The flags register file

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug configuration: version 1
        struct config_v1_t
        {
            int pid;                                        ///< The host process identifier

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug configuration: version-dependent fields
        union config_variants_t
        {
            config_v1_t v1;                                 ///< Version 1

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Debug configuration
        struct config_t
        {
            uint16_t version;                               ///< The requested program debug API version
            config_variants_t variant;                      ///< Version-specific fields

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event information for ::ZET_DEBUG_EVENT_DETACHED
        struct event_info_detached_t
        {
            uint8_t reason;                                 ///< The detach reason

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event information for ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD
        struct event_info_module_t
        {
            uint64_t moduleBegin;                           ///< The begin address of the in-memory module
            uint64_t moduleEnd;                             ///< The end address of the in-memory module
            uint64_t load;                                  ///< The load address of the module on the device

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event type specific information
        union event_info_t
        {
            event_info_detached_t detached;                 ///< type == ::ZET_DEBUG_EVENT_DETACHED
            event_info_module_t module;                     ///< type == ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief A debug event on the device.
        struct event_t
        {
            uint8_t type;                                   ///< The event type
            uint64_t thread;                                ///< The thread reporting the event
            uint64_t flags;                                 ///< A bit-vector of ::zet_debug_event_flags_t
            event_info_t info;                              ///< Event type specific information

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief A register file descriptor.
        struct state_section_t
        {
            uint16_t type;                                  ///< The register file type type
            uint16_t version;                               ///< The register file version
            uint32_t size;                                  ///< The size of the register file in bytes
            uint64_t offset;                                ///< The offset into the register state area

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief A register state descriptor.
        struct state_t
        {
            uint32_t size;                                  ///< The size of the register state object in bytes
            uint8_t headerSize;                             ///< The size of the register state descriptor in bytes
            uint8_t secSize;                                ///< The size of the register file descriptors in bytes
            uint16_t numSec;                                ///< The number of register file descriptors

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
        /// @returns
        ///     - Debug*: debug session handle
        /// 
        /// @throws result_t
        static Debug* __zecall
        Attach(
            Device* pDevice,                                ///< [in] device handle
            const config_t* config                          ///< [in] the debug configuration
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Close a debug session.
        /// @throws result_t
        void __zecall
        Detach(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query the number of device threads for a debug session.
        /// @returns
        ///     - uint64_t: the maximal number of threads
        /// 
        /// @throws result_t
        uint64_t __zecall
        GetNumThreads(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read the topmost debug event.
        /// @returns
        ///     - ze::bool_t:'0' when ZE::RESULT_NOT_READY
        /// @throws result_t
        ze::bool_t __zecall
        ReadEvent(
            uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
            size_t size,                                    ///< [in] the size of the buffer in bytes
            void* buffer                                    ///< [in,out] a buffer to hold the event data
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Interrupt device threads.
        /// @throws result_t
        void __zecall
        Interrupt(
            uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resume device threads.
        /// @throws result_t
        void __zecall
        Resume(
            uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read memory.
        /// @throws result_t
        void __zecall
        ReadMemory(
            uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
            int memSpace,                                   ///< [in] the (device-specific) memory space
            uint64_t address,                               ///< [in] the virtual address of the memory to read from
            size_t size,                                    ///< [in] the number of bytes to read
            void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Write memory.
        /// @throws result_t
        void __zecall
        WriteMemory(
            uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
            int memSpace,                                   ///< [in] the (device-specific) memory space
            uint64_t address,                               ///< [in] the virtual address of the memory to write to
            size_t size,                                    ///< [in] the number of bytes to write
            const void* buffer                              ///< [in] a buffer holding the pattern to write
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Read register state.
        /// @throws result_t
        void __zecall
        ReadState(
            uint64_t threadid,                              ///< [in] the thread context
            uint64_t offset,                                ///< [in] the offset into the register state area
            size_t size,                                    ///< [in] the number of bytes to read
            void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Write register state.
        /// @throws result_t
        void __zecall
        WriteState(
            uint64_t threadid,                              ///< [in] the thread context
            uint64_t offset,                                ///< [in] the offset into the register state area
            size_t size,                                    ///< [in] the number of bytes to write
            const void* buffer                              ///< [in] a buffer holding the pattern to write
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_v1_t to std::string
    std::string to_string( const Debug::config_v1_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_variants_t to std::string
    std::string to_string( const Debug::config_variants_t val );

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
    /// @brief Converts Debug::event_info_t to std::string
    std::string to_string( const Debug::event_info_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_t to std::string
    std::string to_string( const Debug::event_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_intel_graphics_t to std::string
    std::string to_string( const Debug::memory_space_intel_graphics_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_intel_graphics_t to std::string
    std::string to_string( const Debug::state_intel_graphics_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_section_t to std::string
    std::string to_string( const Debug::state_section_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_t to std::string
    std::string to_string( const Debug::state_t val );

} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_DEBUG_HPP
