/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_residency.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Memory Residency
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes memory resident for the device.
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::MakeMemoryResident(
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceMakeMemoryResident(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::MakeMemoryResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows memory to be evicted from the device.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the memory before it is evicted
    ///     - Memory is always implicitly evicted if it is resident when freed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::EvictMemory(
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceEvictMemory(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::EvictMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes image resident for the device.
    /// 
    /// @details
    ///     - If the application does not properly manage residency then the device
    ///       may experience unrecoverable page-faults.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::MakeImageResident(
        Image* pImage                                   ///< [in] pointer to image to make resident
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceMakeImageResident(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::MakeImageResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows image to be evicted from the device.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the memory before it is evicted
    ///     - An image is always implicitly evicted if it is resident when
    ///       destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Device::EvictImage(
        Image* pImage                                   ///< [in] pointer to image to make evict
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceEvictImage(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Device::EvictImage" );
    }

} // namespace ze

namespace ze
{
} // namespace ze
