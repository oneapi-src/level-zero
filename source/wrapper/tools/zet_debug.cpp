/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_debug.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Program Debug
 *
 */
#include "zet_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    Debug::Debug( 
        debug_session_handle_t handle                   ///< [in] debug session handle
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Attach to a device.
    /// 
    /// @returns
    ///     - Debug*: debug session handle
    /// 
    /// @throws result_t
    Debug* __zecall
    Debug::Attach(
        Device* pDevice,                                ///< [in] device handle
        const config_t* config                          ///< [in] the debug configuration
        )
    {
        zet_debug_session_handle_t hDebug;

        auto result = static_cast<result_t>( ::zetDebugAttach(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const zet_debug_config_t*>( config ),
            &hDebug ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::Attach" );

        Debug* pDebug = nullptr;

        try
        {
            pDebug = new Debug( reinterpret_cast<debug_session_handle_t>( hDebug ) );
        }
        catch( std::bad_alloc& )
        {
            delete pDebug;
            pDebug = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "zet::Debug::Attach" );
        }

        return pDebug;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Close a debug session.
    /// 
    /// @throws result_t
    void __zecall
    Debug::Detach(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetDebugDetach(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::Detach" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query the number of device threads for a debug session.
    /// 
    /// @returns
    ///     - uint64_t: the maximal number of threads
    /// 
    /// @throws result_t
    uint64_t __zecall
    Debug::GetNumThreads(
        void
        )
    {
        uint64_t numThreads;

        auto result = static_cast<result_t>( ::zetDebugGetNumThreads(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            &numThreads ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::GetNumThreads" );

        return numThreads;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read the topmost debug event.
    /// 
    /// @returns
    ///     - ze::bool_t:'0' when ZE::RESULT_NOT_READY
    /// @throws result_t
    ze::bool_t __zecall
    Debug::ReadEvent(
        uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
        size_t size,                                    ///< [in] the size of the buffer in bytes
        void* buffer                                    ///< [in,out] a buffer to hold the event data
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadEvent(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            timeout,
            size,
            buffer ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::ReadEvent" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Interrupt device threads.
    /// 
    /// @throws result_t
    void __zecall
    Debug::Interrupt(
        uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto result = static_cast<result_t>( ::zetDebugInterrupt(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::Interrupt" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Resume device threads.
    /// 
    /// @throws result_t
    void __zecall
    Debug::Resume(
        uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto result = static_cast<result_t>( ::zetDebugResume(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::Resume" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read memory.
    /// 
    /// @throws result_t
    void __zecall
    Debug::ReadMemory(
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to read from
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadMemory(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            memSpace,
            address,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::ReadMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Write memory.
    /// 
    /// @throws result_t
    void __zecall
    Debug::WriteMemory(
        uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
        int memSpace,                                   ///< [in] the (device-specific) memory space
        uint64_t address,                               ///< [in] the virtual address of the memory to write to
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto result = static_cast<result_t>( ::zetDebugWriteMemory(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            memSpace,
            address,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::WriteMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read register state.
    /// 
    /// @throws result_t
    void __zecall
    Debug::ReadState(
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadState(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            offset,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::ReadState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Write register state.
    /// 
    /// @throws result_t
    void __zecall
    Debug::WriteState(
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto result = static_cast<result_t>( ::zetDebugWriteState(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            threadid,
            offset,
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "zet::Debug::WriteState" );
    }

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_flags_t to std::string
    std::string to_string( const Debug::event_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEBUG_EVENT_FLAG_NONE   ";
        
        if( static_cast<uint32_t>(Debug::event_flags_t::DEBUG_EVENT_FLAG_STOPPED) & bits )
            str += "DEBUG_EVENT_FLAG_STOPPED | ";

        return ( str.size() > 3 ) 
            ? "Debug::event_flags_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Debug::event_flags_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_type_t to std::string
    std::string to_string( const Debug::event_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::event_type_t::DEBUG_EVENT_INVALID:
            str = "Debug::event_type_t::DEBUG_EVENT_INVALID";
            break;

        case Debug::event_type_t::DEBUG_EVENT_DETACHED:
            str = "Debug::event_type_t::DEBUG_EVENT_DETACHED";
            break;

        case Debug::event_type_t::DEBUG_EVENT_PROCESS_ENTRY:
            str = "Debug::event_type_t::DEBUG_EVENT_PROCESS_ENTRY";
            break;

        case Debug::event_type_t::DEBUG_EVENT_PROCESS_EXIT:
            str = "Debug::event_type_t::DEBUG_EVENT_PROCESS_EXIT";
            break;

        case Debug::event_type_t::DEBUG_EVENT_MODULE_LOAD:
            str = "Debug::event_type_t::DEBUG_EVENT_MODULE_LOAD";
            break;

        case Debug::event_type_t::DEBUG_EVENT_MODULE_UNLOAD:
            str = "Debug::event_type_t::DEBUG_EVENT_MODULE_UNLOAD";
            break;

        case Debug::event_type_t::DEBUG_EVENT_EXCEPTION:
            str = "Debug::event_type_t::DEBUG_EVENT_EXCEPTION";
            break;

        default:
            str = "Debug::event_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::detach_reason_t to std::string
    std::string to_string( const Debug::detach_reason_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::detach_reason_t::DEBUG_DETACH_INVALID:
            str = "Debug::detach_reason_t::DEBUG_DETACH_INVALID";
            break;

        case Debug::detach_reason_t::DEBUG_DETACH_HOST_EXIT:
            str = "Debug::detach_reason_t::DEBUG_DETACH_HOST_EXIT";
            break;

        default:
            str = "Debug::detach_reason_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_intel_graphics_t to std::string
    std::string to_string( const Debug::memory_space_intel_graphics_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_DEFAULT:
            str = "Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_DEFAULT";
            break;

        case Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_SLM:
            str = "Debug::memory_space_intel_graphics_t::DEBUG_MEMORY_SPACE_GEN_SLM";
            break;

        default:
            str = "Debug::memory_space_intel_graphics_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_intel_graphics_t to std::string
    std::string to_string( const Debug::state_intel_graphics_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_INVALID:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_INVALID";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_GRF:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_GRF";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ACC:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ACC";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ADDR:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_ADDR";
            break;

        case Debug::state_intel_graphics_t::DEBUG_STATE_GEN_FLAG:
            str = "Debug::state_intel_graphics_t::DEBUG_STATE_GEN_FLAG";
            break;

        default:
            str = "Debug::state_intel_graphics_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_v1_t to std::string
    std::string to_string( const Debug::config_v1_t val )
    {
        std::string str;
        
        str += "Debug::config_v1_t::pid : ";
        str += std::to_string(val.pid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_variants_t to std::string
    std::string to_string( const Debug::config_variants_t val )
    {
        std::string str;
        
        str += "Debug::config_variants_t::v1 : ";
        str += to_string(val.v1);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_t to std::string
    std::string to_string( const Debug::config_t val )
    {
        std::string str;
        
        str += "Debug::config_t::version : ";
        str += std::to_string(val.version);
        str += "\n";
        
        str += "Debug::config_t::variant : ";
        str += to_string(val.variant);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_detached_t to std::string
    std::string to_string( const Debug::event_info_detached_t val )
    {
        std::string str;
        
        str += "Debug::event_info_detached_t::reason : ";
        str += std::to_string(val.reason);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_module_t to std::string
    std::string to_string( const Debug::event_info_module_t val )
    {
        std::string str;
        
        str += "Debug::event_info_module_t::moduleBegin : ";
        str += std::to_string(val.moduleBegin);
        str += "\n";
        
        str += "Debug::event_info_module_t::moduleEnd : ";
        str += std::to_string(val.moduleEnd);
        str += "\n";
        
        str += "Debug::event_info_module_t::load : ";
        str += std::to_string(val.load);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_t to std::string
    std::string to_string( const Debug::event_info_t val )
    {
        std::string str;
        
        str += "Debug::event_info_t::detached : ";
        str += to_string(val.detached);
        str += "\n";
        
        str += "Debug::event_info_t::module : ";
        str += to_string(val.module);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_t to std::string
    std::string to_string( const Debug::event_t val )
    {
        std::string str;
        
        str += "Debug::event_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Debug::event_t::thread : ";
        str += std::to_string(val.thread);
        str += "\n";
        
        str += "Debug::event_t::flags : ";
        str += std::to_string(val.flags);
        str += "\n";
        
        str += "Debug::event_t::info : ";
        str += to_string(val.info);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_section_t to std::string
    std::string to_string( const Debug::state_section_t val )
    {
        std::string str;
        
        str += "Debug::state_section_t::type : ";
        str += std::to_string(val.type);
        str += "\n";
        
        str += "Debug::state_section_t::version : ";
        str += std::to_string(val.version);
        str += "\n";
        
        str += "Debug::state_section_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Debug::state_section_t::offset : ";
        str += std::to_string(val.offset);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::state_t to std::string
    std::string to_string( const Debug::state_t val )
    {
        std::string str;
        
        str += "Debug::state_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Debug::state_t::headerSize : ";
        str += std::to_string(val.headerSize);
        str += "\n";
        
        str += "Debug::state_t::secSize : ";
        str += std::to_string(val.secSize);
        str += "\n";
        
        str += "Debug::state_t::numSec : ";
        str += std::to_string(val.numSec);
        str += "\n";

        return str;
    }

} // namespace zet
