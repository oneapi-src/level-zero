/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_cmdqueue.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Command Queue
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    CommandQueue::CommandQueue( 
        command_queue_handle_t handle,                  ///< [in] handle of command queue object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command queue object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command queue on the device.
    /// 
    /// @details
    ///     - The command queue can only be used on the device on which it was
    ///       created.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateCommandQueue**
    /// 
    /// @returns
    ///     - CommandQueue*: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* __zecall
    CommandQueue::Create(
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command queue descriptor
        )
    {
        ze_command_queue_handle_t hCommandQueue;

        auto result = static_cast<result_t>( ::zeCommandQueueCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_queue_desc_t*>( desc ),
            &hCommandQueue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandQueue::Create" );

        CommandQueue* pCommandQueue = nullptr;

        try
        {
            pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandQueue;
            pCommandQueue = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::CommandQueue::Create" );
        }

        return pCommandQueue;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command queue.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the command queue before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this command queue
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command queue handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseCommandQueue**
    /// 
    /// @throws result_t
    void __zecall
    CommandQueue::Destroy(
        CommandQueue* pCommandQueue                     ///< [in][release] pointer to command queue object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeCommandQueueDestroy(
            reinterpret_cast<ze_command_queue_handle_t>( pCommandQueue->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandQueue::Destroy" );

        delete pCommandQueue;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Executes a command list in a command queue.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkQueueSubmit
    /// 
    /// @throws result_t
    void __zecall
    CommandQueue::ExecuteCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        CommandList** ppCommandLists,                   ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        Fence* pFence                                   ///< [in][optional] pointer to the fence to signal on completion
        )
    {
        thread_local std::vector<ze_command_list_handle_t> hCommandLists;
        hCommandLists.resize( 0 );
        hCommandLists.reserve( numCommandLists );
        for( uint32_t i = 0; i < numCommandLists; ++i )
            hCommandLists.emplace_back( reinterpret_cast<ze_command_list_handle_t>( ppCommandLists[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zeCommandQueueExecuteCommandLists(
            reinterpret_cast<ze_command_queue_handle_t>( getHandle() ),
            numCommandLists,
            hCommandLists.data(),
            ( pFence ) ? reinterpret_cast<ze_fence_handle_t>( pFence->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandQueue::ExecuteCommandLists" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Synchronizes a command queue by waiting on the host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    CommandQueue::Synchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::zeCommandQueueSynchronize(
            reinterpret_cast<ze_command_queue_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandQueue::Synchronize" );
        return 1; // true
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_version_t to std::string
    std::string to_string( const CommandQueue::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::desc_version_t::CURRENT:
            str = "CommandQueue::desc_version_t::CURRENT";
            break;

        default:
            str = "CommandQueue::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flag_t to std::string
    std::string to_string( const CommandQueue::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::COPY_ONLY) & bits )
            str += "COPY_ONLY | ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::LOGICAL_ONLY) & bits )
            str += "LOGICAL_ONLY | ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::SINGLE_SLICE_ONLY) & bits )
            str += "SINGLE_SLICE_ONLY | ";
        
        if( static_cast<uint32_t>(CommandQueue::flag_t::SUPPORTS_COOPERATIVE_KERNELS) & bits )
            str += "SUPPORTS_COOPERATIVE_KERNELS | ";

        return ( str.size() > 3 ) 
            ? "CommandQueue::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "CommandQueue::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( const CommandQueue::mode_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::mode_t::DEFAULT:
            str = "CommandQueue::mode_t::DEFAULT";
            break;

        case CommandQueue::mode_t::SYNCHRONOUS:
            str = "CommandQueue::mode_t::SYNCHRONOUS";
            break;

        case CommandQueue::mode_t::ASYNCHRONOUS:
            str = "CommandQueue::mode_t::ASYNCHRONOUS";
            break;

        default:
            str = "CommandQueue::mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( const CommandQueue::priority_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::priority_t::NORMAL:
            str = "CommandQueue::priority_t::NORMAL";
            break;

        case CommandQueue::priority_t::LOW:
            str = "CommandQueue::priority_t::LOW";
            break;

        case CommandQueue::priority_t::HIGH:
            str = "CommandQueue::priority_t::HIGH";
            break;

        default:
            str = "CommandQueue::priority_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_t to std::string
    std::string to_string( const CommandQueue::desc_t val )
    {
        std::string str;
        
        str += "CommandQueue::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "CommandQueue::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "CommandQueue::desc_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "CommandQueue::desc_t::priority : ";
        str += to_string(val.priority);
        str += "\n";
        
        str += "CommandQueue::desc_t::ordinal : ";
        str += std::to_string(val.ordinal);
        str += "\n";

        return str;
    }

} // namespace ze
