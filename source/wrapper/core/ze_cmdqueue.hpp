/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_cmdqueue.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Command Queue
 *
 */
#ifndef _ZE_CMDQUEUE_HPP
#define _ZE_CMDQUEUE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command queue
    class CommandQueue
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_command_queue_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = ZE_BIT(0),                          ///< command queue only supports enqueuing copy-only command lists
            LOGICAL_ONLY = ZE_BIT(1),                       ///< command queue is not tied to a physical command queue; driver may
                                                            ///< dynamically assign based on usage
            SINGLE_SLICE_ONLY = ZE_BIT(2),                  ///< command queue reserves and cannot consume more than a single slice.
                                                            ///< 'slice' size is device-specific.  cannot be combined with COPY_ONLY.
            SUPPORTS_COOPERATIVE_KERNELS = ZE_BIT(3),       ///< command queue supports command list with cooperative kernels. See
                                                            ///< ::zeCommandListAppendLaunchCooperativeKernel for more details. cannot
                                                            ///< be combined with COPY_ONLY.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue modes
        enum class mode_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            SYNCHRONOUS,                                    ///< Device execution always completes immediately on execute;
                                                            ///< Host thread is blocked using wait on implicit synchronization object
            ASYNCHRONOUS,                                   ///< Device execution is scheduled and will complete in future;
                                                            ///< explicit synchronization object must be used to determine completeness

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue priorities
        enum class priority_t
        {
            NORMAL = 0,                                     ///< [default] normal priority
            LOW,                                            ///< lower priority than normal
            HIGH,                                           ///< higher priority than normal

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command Queue descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags
            mode_t mode = mode_t::DEFAULT;                  ///< [in] operation mode
            priority_t priority = priority_t::NORMAL;       ///< [in] priority
            uint32_t ordinal = 0;                           ///< [in] if logical-only flag is set, then will be ignored;
                                                            ///< if supports-cooperative-kernels is set, then may be ignored;
                                                            ///< else-if copy-only flag is set, then must be less than ::ze_device_properties_t.numAsyncCopyEngines;
                                                            ///< otherwise must be less than
                                                            ///< ::ze_device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                            ///< the ::ze_device_properties_t.numAsyncComputeEngines must be queried
                                                            ///< from the sub-device being used.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_queue_handle_t m_handle;                ///< [in] handle of command queue object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command queue object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandQueue( void ) = delete;
        CommandQueue( 
            command_queue_handle_t handle,                  ///< [in] handle of command queue object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command queue object
            );

        ~CommandQueue( void ) = default;

        CommandQueue( CommandQueue const& other ) = delete;
        void operator=( CommandQueue const& other ) = delete;

        CommandQueue( CommandQueue&& other ) = delete;
        void operator=( CommandQueue&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - CommandQueue*: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        static CommandQueue* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command queue descriptor
            );

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
        /// @throws result_t
        static void __zecall
        Destroy(
            CommandQueue* pCommandQueue                     ///< [in][release] pointer to command queue object to destroy
            );

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
        /// @throws result_t
        void __zecall
        ExecuteCommandLists(
            uint32_t numCommandLists,                       ///< [in] number of command lists to execute
            CommandList** ppCommandLists,                   ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                            ///< to execute
            Fence* pFence = nullptr                         ///< [in][optional] pointer to the fence to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Synchronizes a command queue by waiting on the host.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        Synchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                            ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                            ///< if UINT32_MAX, then function will not return until complete or device
                                                            ///< is lost.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_version_t to std::string
    std::string to_string( const CommandQueue::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flag_t to std::string
    std::string to_string( const CommandQueue::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( const CommandQueue::mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( const CommandQueue::priority_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_t to std::string
    std::string to_string( const CommandQueue::desc_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_CMDQUEUE_HPP
