/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_cmdlist.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Command List
 *
 */
#ifndef _ZE_CMDLIST_HPP
#define _ZE_CMDLIST_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_command_list_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command list creation flags
        enum class flag_t
        {
            NONE = 0,                                       ///< default behavior
            COPY_ONLY = ZE_BIT(0),                          ///< command list **only** contains copy operations (and synchronization primitives).
                                                            ///< this command list may **only** be submitted to a command queue created
                                                            ///< with ::ZE_COMMAND_QUEUE_FLAG_COPY_ONLY.
            RELAXED_ORDERING = ZE_BIT(1),                   ///< driver may reorder programs and copys between barriers and
                                                            ///< synchronization primitives.
                                                            ///< using this flag may increase Host overhead of ::zeCommandListClose.
                                                            ///< therefore, this flag should **not** be set for low-latency usage-models.
            MAXIMIZE_THROUGHPUT = ZE_BIT(2),                ///< driver may perform additional optimizations that increase dexecution
                                                            ///< throughput. 
                                                            ///< using this flag may increase Host overhead of ::zeCommandListClose and ::zeCommandQueueExecuteCommandLists.
                                                            ///< therefore, this flag should **not** be set for low-latency usage-models.
            EXPLICIT_ONLY = ZE_BIT(3),                      ///< command list should be optimized for submission to a single command
                                                            ///< queue and device engine.
                                                            ///< driver **must** disable any implicit optimizations for distributing
                                                            ///< work across multiple engines.
                                                            ///< this flag should be used when applications want full control over
                                                            ///< multi-engine submission and scheduling.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported memory advice hints
        enum class memory_advice_t
        {
            SET_READ_MOSTLY = 0,                            ///< hint that memory will be read from frequently and written to rarely
            CLEAR_READ_MOSTLY,                              ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_READ_MOSTLY
            SET_PREFERRED_LOCATION,                         ///< hint that the preferred memory location is the specified device
            CLEAR_PREFERRED_LOCATION,                       ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_PREFERRED_LOCATION
            SET_ACCESSED_BY,                                ///< hint that memory will be accessed by the specified device
            CLEAR_ACCESSED_BY,                              ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_ACCESSED_BY
            SET_NON_ATOMIC_MOSTLY,                          ///< hints that memory will mostly be accessed non-atomically
            CLEAR_NON_ATOMIC_MOSTLY,                        ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
            BIAS_CACHED,                                    ///< hints that memory should be cached
            BIAS_UNCACHED,                                  ///< hints that memory should be not be cached

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command List descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_COMMAND_LIST_DESC_VERSION_CURRENT
            flag_t flags = flag_t::NONE;                    ///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel dispatch group count.
        struct group_count_t
        {
            uint32_t groupCountX = 0;                       ///< [in] number of thread groups in X dimension
            uint32_t groupCountY = 0;                       ///< [in] number of thread groups in Y dimension
            uint32_t groupCountZ = 0;                       ///< [in] number of thread groups in Z dimension

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copy region descriptor
        struct copy_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in bytes
            uint32_t originY;                               ///< [in] The origin y offset for region in rows
            uint32_t originZ;                               ///< [in] The origin z offset for region in slices
            uint32_t width;                                 ///< [in] The region width relative to origin in bytes
            uint32_t height;                                ///< [in] The region height relative to origin in rows
            uint32_t depth;                                 ///< [in] The region depth relative to origin in slices. Set this to 0 for
                                                            ///< 2D copy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Region descriptor
        struct image_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in pixels
            uint32_t originY;                               ///< [in] The origin y offset for region in pixels
            uint32_t originZ;                               ///< [in] The origin z offset for region in pixels
            uint32_t width;                                 ///< [in] The region width relative to origin in pixels
            uint32_t height;                                ///< [in] The region height relative to origin in pixels
            uint32_t depth;                                 ///< [in] The region depth relative to origin. For 1D or 2D images, set
                                                            ///< this to 1.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_list_handle_t m_handle;                 ///< [in] handle of command list object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command list object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandList( void ) = delete;
        CommandList( 
            command_list_handle_t handle,                   ///< [in] handle of command list object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command list object
            );

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a command list on the device for submitting commands to any
        ///        command queue.
        /// 
        /// @details
        ///     - The command list can only be used on the device on which it was
        ///       created.
        ///     - The command list is created in the 'open' state.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command list descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a command list on the device with an implicit command queue
        ///        for immediate submission of commands.
        /// 
        /// @details
        ///     - The command list can only be used on the device on which it was
        ///       created.
        ///     - The command list is created in the 'open' state and never needs to be
        ///       closed.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* __zecall
        CreateImmediate(
            Device* pDevice,                                ///< [in] pointer to the device object
            const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a command list.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the command list before it is deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this command list.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __zecall
        Destroy(
            CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes a command list; ready to be executed by a command queue.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset a command list to initial (empty) state; ready for appending
        ///        commands.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the command list before it is reset
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        Reset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends an execution and global memory barrier into a command list.
        /// 
        /// @details
        ///     - If numWaitEvents is zero, then all previous commands are completed
        ///       prior to the execution of the barrier.
        ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
        ///       signaled prior to the execution of the barrier.
        ///     - This command blocks all following commands from beginning until the
        ///       execution of the barrier completes.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **vkCmdPipelineBarrier**
        ///     - clEnqueueBarrierWithWaitList
        /// @throws result_t
        void __zecall
        AppendBarrier(
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing barrier
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends a global memory ranges barrier into a command list.
        /// 
        /// @details
        ///     - If numWaitEvents is zero, then all previous commands are completed
        ///       prior to the execution of the barrier.
        ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
        ///       signaled prior to the execution of the barrier.
        ///     - This command blocks all following commands from beginning until the
        ///       execution of the barrier completes.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendMemoryRangesBarrier(
            uint32_t numRanges,                             ///< [in] number of memory ranges
            const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
            const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing barrier
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch kernel over one or more work groups.
        /// 
        /// @details
        ///     - This may **only** be called for a command list created with command
        ///       queue group ordinal that supports compute.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendLaunchKernel(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch kernel cooperatively over one or more work groups.
        /// 
        /// @details
        ///     - This may **only** be called for a command list created with command
        ///       queue group ordinal that supports compute.
        ///     - This may only be used for a command list that are submitted to command
        ///       queue with cooperative flag set.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        ///     - Use ::zeKernelSuggestMaxCooperativeGroupCount to recommend max group
        ///       count for device for cooperative functions that device supports.
        /// @throws result_t
        void __zecall
        AppendLaunchCooperativeKernel(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch kernel over one or more work groups using indirect arguments.
        /// 
        /// @details
        ///     - The launch arguments need to be device visible.
        ///     - The launch arguments buffer may not be reused until the function has
        ///       completed on the device.
        ///     - This may **only** be called for a command list created with command
        ///       queue group ordinal that supports compute.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendLaunchKernelIndirect(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchArgumentsBuffer,    ///< [in] pointer to device buffer that will contain thread group launch
                                                            ///< arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Launch multiple kernels over one or more work groups using an array of
        ///        indirect arguments.
        /// 
        /// @details
        ///     - The array of launch arguments need to be device visible.
        ///     - The array of launch arguments buffer may not be reused until the
        ///       kernel has completed on the device.
        ///     - This may **only** be called for a command list created with command
        ///       queue group ordinal that supports compute.
        ///     - This function may **not** be called from simultaneous threads with the
        ///       same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendLaunchMultipleKernelsIndirect(
            uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
            Kernel** ppKernels,                             ///< [in][range(0, numKernels)] handles of the kernel objects
            const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                            ///< number of kernels to launch; value must be less-than or equal-to
                                                            ///< numKernels
            const group_count_t* pLaunchArgumentsBuffer,    ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                            ///< a contiguous array of thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends a signal of the event from the device into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clSetUserEventStatus**
        ///     - vkCmdSetEvent
        /// @throws result_t
        void __zecall
        AppendSignalEvent(
            Event* pEvent                                   ///< [in] pointer to the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends wait on event(s) on the device into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendWaitOnEvents(
            uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
            Event** ppEvents                                ///< [in][range(0, numEvents)] pointer to the events to wait on before
                                                            ///< continuing
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reset an event back to not signaled state
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - vkResetEvent
        /// @throws result_t
        void __zecall
        AppendEventReset(
            Event* pEvent                                   ///< [in] pointer to the event
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies host, device, or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by both srcptr and dstptr must be accessible by
        ///       the device on which the command list is created.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clEnqueueCopyBuffer**
        ///     - **clEnqueueReadBuffer**
        ///     - **clEnqueueWriteBuffer**
        ///     - **clEnqueueSVMMemcpy**
        /// @throws result_t
        void __zecall
        AppendMemoryCopy(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            size_t size,                                    ///< [in] size in bytes to copy
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Initializes host, device, or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by dstptr must be accessible by the device on
        ///       which the command list is created.
        ///     - The value to initialize memory to is described by the pattern and the
        ///       pattern size.
        ///     - The pattern size must be a power of two.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clEnqueueFillBuffer**
        ///     - **clEnqueueSVMMemFill**
        /// @throws result_t
        void __zecall
        AppendMemoryFill(
            void* ptr,                                      ///< [in] pointer to memory to initialize
            const void* pattern,                            ///< [in] pointer to value to initialize memory to
            size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
            size_t size,                                    ///< [in] size in bytes to initialize
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies a region from a 2D or 3D array of host, device, or shared
        ///        memory.
        /// 
        /// @details
        ///     - The memory pointed to by both srcptr and dstptr must be accessible by
        ///       the device on which the command list is created.
        ///     - The region width, height, and depth for both src and dst must be same.
        ///       The origins can be different.
        ///     - The src and dst regions cannot be overlapping.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendMemoryCopyRegion(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const copy_region_t* dstRegion,                 ///< [in] pointer to destination region to copy to
            uint32_t dstPitch,                              ///< [in] destination pitch in bytes
            uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                            ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                            ///< ignored.
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            const copy_region_t* srcRegion,                 ///< [in] pointer to source region to copy from
            uint32_t srcPitch,                              ///< [in] source pitch in bytes
            uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                            ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                            ///< ignored.
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies a image.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - **clEnqueueCopyImage**
        /// @throws result_t
        void __zecall
        AppendImageCopy(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies a region of a image to another image.
        /// 
        /// @details
        ///     - The region width and height for both src and dst must be same. The
        ///       origins can be different.
        ///     - The src and dst regions cannot be overlapping.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendImageCopyRegion(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            const image_region_t* pDstRegion = nullptr,     ///< [in][optional] destination region descriptor
            const image_region_t* pSrcRegion = nullptr,     ///< [in][optional] source region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies from a image to device or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by dstptr must be accessible by the device on
        ///       which the command list is created.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clEnqueueReadImage
        /// @throws result_t
        void __zecall
        AppendImageCopyToMemory(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            const image_region_t* pSrcRegion = nullptr,     ///< [in][optional] source region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copies to a image from device or shared memory.
        /// 
        /// @details
        ///     - The memory pointed to by srcptr must be accessible by the device on
        ///       which the command list is created.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clEnqueueWriteImage
        /// @throws result_t
        void __zecall
        AppendImageCopyFromMemory(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            const image_region_t* pDstRegion = nullptr,     ///< [in][optional] destination region descriptor
            Event* pEvent = nullptr                         ///< [in][optional] pointer to the event to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Asynchronously prefetches shared memory to the device associated with
        ///        the specified command list
        /// 
        /// @details
        ///     - This is a hint to improve performance only and is not required for
        ///       correctness.
        ///     - Only prefetching to the device associated with the specified command
        ///       list is supported.
        ///       Prefetching to the host or to a peer device is not supported.
        ///     - Prefetching may not be supported for all allocation types for all devices.
        ///       If memory prefetching is not supported for the specified memory range
        ///       the prefetch hint may be ignored.
        ///     - Prefetching may only be supported at a device-specific granularity,
        ///       such as at a page boundary.
        ///       In this case, the memory range may be expanded such that the start and
        ///       end of the range satisfy granularity requirements.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clEnqueueSVMMigrateMem
        /// @throws result_t
        void __zecall
        AppendMemoryPrefetch(
            const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
            size_t size                                     ///< [in] size in bytes of the memory range to prefetch
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Provides advice about the use of a shared memory range
        /// 
        /// @details
        ///     - Memory advice is a performance hint only and is not required for
        ///       functional correctness.
        ///     - Memory advice can be used to override driver heuristics to explicitly
        ///       control shared memory behavior.
        ///     - Not all memory advice hints may be supported for all allocation types
        ///       for all devices.
        ///       If a memory advice hint is not supported by the device it will be ignored.
        ///     - Memory advice may only be supported at a device-specific granularity,
        ///       such as at a page boundary.
        ///       In this case, the memory range may be expanded such that the start and
        ///       end of the range satisfy granularity requirements.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        AppendMemAdvise(
            Device* pDevice,                                ///< [in] device associated with the memory advice
            const void* ptr,                                ///< [in] Pointer to the start of the memory range
            size_t size,                                    ///< [in] Size in bytes of the memory range
            memory_advice_t advice                          ///< [in] Memory advice for the memory range
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_version_t to std::string
    std::string to_string( const CommandList::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::flag_t to std::string
    std::string to_string( const CommandList::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_t to std::string
    std::string to_string( const CommandList::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::group_count_t to std::string
    std::string to_string( const CommandList::group_count_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::copy_region_t to std::string
    std::string to_string( const CommandList::copy_region_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::image_region_t to std::string
    std::string to_string( const CommandList::image_region_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::memory_advice_t to std::string
    std::string to_string( const CommandList::memory_advice_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_CMDLIST_HPP
