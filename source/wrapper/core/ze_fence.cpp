/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_fence.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Fence
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    Fence::Fence( 
        fence_handle_t handle,                          ///< [in] handle of fence object
        CommandQueue* pCommandQueue,                    ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the fence object
        ) :
        m_handle( handle ),
        m_pCommandQueue( pCommandQueue ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a fence object on the device's command queue.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkCreateFence**
    /// 
    /// @returns
    ///     - Fence*: pointer to handle of fence object created
    /// 
    /// @throws result_t
    Fence* __zecall
    Fence::Create(
        CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
        const desc_t* desc                              ///< [in] pointer to fence descriptor
        )
    {
        ze_fence_handle_t hFence;

        auto result = static_cast<result_t>( ::zeFenceCreate(
            reinterpret_cast<ze_command_queue_handle_t>( pCommandQueue->getHandle() ),
            reinterpret_cast<const ze_fence_desc_t*>( desc ),
            &hFence ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Fence::Create" );

        Fence* pFence = nullptr;

        try
        {
            pFence = new Fence( reinterpret_cast<fence_handle_t>( hFence ), pCommandQueue, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pFence;
            pFence = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Fence::Create" );
        }

        return pFence;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a fence object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the fence before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this fence
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same fence handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkDestroyFence**
    /// 
    /// @throws result_t
    void __zecall
    Fence::Destroy(
        Fence* pFence                                   ///< [in][release] pointer to fence object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeFenceDestroy(
            reinterpret_cast<ze_fence_handle_t>( pFence->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Fence::Destroy" );

        delete pFence;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The current host thread waits on a fence to be signaled.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkWaitForFences**
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    Fence::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::zeFenceHostSynchronize(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Fence::HostSynchronize" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries a fence object's status.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkGetFenceStatus**
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t __zecall
    Fence::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeFenceQueryStatus(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Fence::QueryStatus" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset a fence back to the not signaled state.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkResetFences**
    /// 
    /// @throws result_t
    void __zecall
    Fence::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeFenceReset(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Fence::Reset" );
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_version_t to std::string
    std::string to_string( const Fence::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Fence::desc_version_t::CURRENT:
            str = "Fence::desc_version_t::CURRENT";
            break;

        default:
            str = "Fence::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::flag_t to std::string
    std::string to_string( const Fence::flag_t val )
    {
        std::string str;

        switch( val )
        {
        case Fence::flag_t::NONE:
            str = "Fence::flag_t::NONE";
            break;

        default:
            str = "Fence::flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_t to std::string
    std::string to_string( const Fence::desc_t val )
    {
        std::string str;
        
        str += "Fence::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Fence::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

} // namespace ze
