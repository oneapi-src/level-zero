/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_fence.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Fence
 *
 */
#ifndef _ZE_FENCE_HPP
#define _ZE_FENCE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for fence
    class Fence
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_fence_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported fence creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fence descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_FENCE_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        fence_handle_t m_handle;                        ///< [in] handle of fence object
        CommandQueue* m_pCommandQueue;                  ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the fence object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Fence( void ) = delete;
        Fence( 
            fence_handle_t handle,                          ///< [in] handle of fence object
            CommandQueue* pCommandQueue,                    ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the fence object
            );

        ~Fence( void ) = default;

        Fence( Fence const& other ) = delete;
        void operator=( Fence const& other ) = delete;

        Fence( Fence&& other ) = delete;
        void operator=( Fence&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getCommandqueue( void ) const { return m_pCommandQueue; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Fence*: pointer to handle of fence object created
        /// 
        /// @throws result_t
        static Fence* __zecall
        Create(
            CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
            const desc_t* desc                              ///< [in] pointer to fence descriptor
            );

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
        /// @throws result_t
        static void __zecall
        Destroy(
            Fence* pFence                                   ///< [in][release] pointer to fence object to destroy
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        HostSynchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                            ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                            ///< if UINT32_MAX, then function will not return until complete or device
                                                            ///< is lost.
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        QueryStatus(
            void
            );

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
        /// @throws result_t
        void __zecall
        Reset(
            void
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_version_t to std::string
    std::string to_string( const Fence::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::flag_t to std::string
    std::string to_string( const Fence::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_t to std::string
    std::string to_string( const Fence::desc_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_FENCE_HPP
