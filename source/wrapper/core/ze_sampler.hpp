/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_sampler.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Sampler
 *
 */
#ifndef _ZE_SAMPLER_HPP
#define _ZE_SAMPLER_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief c++ wrapper for sampler
    class Sampler
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_sampler_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler addressing modes
        enum class address_mode_t
        {
            NONE = 0,                                       ///< No coordinate modifications for out-of-bounds image access.
            REPEAT,                                         ///< Out-of-bounds coordinates are wrapped back around.
            CLAMP,                                          ///< Out-of-bounds coordinates are clamped to edge.
            CLAMP_TO_BORDER,                                ///< Out-of-bounds coordinates are clamped to border color which is (0.0f,
                                                            ///< 0.0f, 0.0f, 0.0f) if image format swizzle contains alpha, otherwise
                                                            ///< (0.0f, 0.0f, 0.0f, 1.0f).
            MIRROR,                                         ///< Out-of-bounds coordinates are mirrored starting from edge.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler filtering modes
        enum class filter_mode_t
        {
            NEAREST = 0,                                    ///< No coordinate modifications for out of bounds image access.
            LINEAR,                                         ///< Out-of-bounds coordinates are wrapped back around.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_SAMPLER_DESC_VERSION_CURRENT
            address_mode_t addressMode = address_mode_t::NONE;  ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                            ///< coordinates are handled.
            filter_mode_t filterMode = filter_mode_t::NEAREST;  ///< [in] Sampler filter mode to determine how samples are filtered.
            bool_t isNormalized = true;                     ///< [in] Are coordinates normalized [0, 1] or not.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sampler_handle_t m_handle;                      ///< [in] handle of the sample object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] sampler descriptor

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sampler( void ) = delete;
        Sampler( 
            sampler_handle_t handle,                        ///< [in] handle of the sample object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] sampler descriptor
            );

        ~Sampler( void ) = default;

        Sampler( Sampler const& other ) = delete;
        void operator=( Sampler const& other ) = delete;

        Sampler( Sampler&& other ) = delete;
        void operator=( Sampler&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates sampler object.
        /// 
        /// @details
        ///     - The sampler can only be used on the device on which it was created.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Sampler*: handle of the sampler
        /// 
        /// @throws result_t
        static Sampler* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to sampler descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys sampler object
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the sampler before it is deleted
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this module
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same sampler handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __zecall
        Destroy(
            Sampler* pSampler                               ///< [in][release] pointer to the sampler
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_version_t to std::string
    std::string to_string( const Sampler::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::address_mode_t to std::string
    std::string to_string( const Sampler::address_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::filter_mode_t to std::string
    std::string to_string( const Sampler::filter_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_t to std::string
    std::string to_string( const Sampler::desc_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_SAMPLER_HPP
