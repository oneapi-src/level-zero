/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_copy.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Copies
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            srcptr,
            size,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryCopy" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryFill(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryFill(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            pattern,
            pattern_size,
            size,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryFill" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryCopyRegion(
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
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<const ze_copy_region_t*>( dstRegion ),
            dstPitch,
            dstSlicePitch,
            srcptr,
            reinterpret_cast<const ze_copy_region_t*>( srcRegion ),
            srcPitch,
            srcSlicePitch,
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryCopyRegion" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopy(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopy" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopyRegion(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopyRegion" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyToMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopyToMemory" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendImageCopyFromMemory(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        Event* pEvent                                   ///< [in][optional] pointer to the event to signal on completion
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyFromMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            srcptr,
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            ( pEvent ) ? reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendImageCopyFromMemory" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryPrefetch(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemoryPrefetch" );
    }

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
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendMemAdvise(
        Device* pDevice,                                ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemAdvise(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            ptr,
            size,
            static_cast<ze_memory_advice_t>( advice ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendMemAdvise" );
    }

} // namespace ze

namespace ze
{
} // namespace ze
