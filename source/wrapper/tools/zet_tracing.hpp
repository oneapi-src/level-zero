/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_tracing.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for API Tracing
 *
 */
#ifndef _ZET_TRACING_HPP
#define _ZET_TRACING_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "ze_callbacks.h"

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for tracer
    class Tracer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Alias the existing callbacks definition for 'core' callbacks
        using core_callbacks_t = ze_callbacks_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_tracer_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Tracer descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZET_TRACER_DESC_VERSION_CURRENT
            void* pUserData;                                ///< [in] pointer passed to every tracer's callbacks

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        tracer_handle_t m_handle;                       ///< [in] handle of tracer object
        Driver* m_pDriver;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the tracer object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Tracer( void ) = delete;
        Tracer( 
            tracer_handle_t handle,                         ///< [in] handle of tracer object
            Driver* pDriver,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the tracer object
            );

        ~Tracer( void ) = default;

        Tracer( Tracer const& other ) = delete;
        void operator=( Tracer const& other ) = delete;

        Tracer( Tracer&& other ) = delete;
        void operator=( Tracer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a tracer for the specified driver.
        /// 
        /// @details
        ///     - The tracer can only be used on the driver on which it was created.
        ///     - The tracer is created in the disabled state.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Tracer*: pointer to handle of tracer object created
        /// 
        /// @throws result_t
        static Tracer* __zecall
        Create(
            Driver* pDriver,                                ///< [in] pointer to the driver
            const desc_t* desc                              ///< [in] pointer to tracer descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a tracer.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        ///     - The implementation of this function will stall and wait on any
        ///       outstanding threads executing callbacks before freeing any Host
        ///       allocations associated with this tracer.
        /// @throws result_t
        static void __zecall
        Destroy(
            Tracer* pTracer                                 ///< [in][release] pointer to tracer object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the collection of callbacks to be executed **before** driver
        ///        execution.
        /// 
        /// @details
        ///     - The application only needs to set the function pointers it is
        ///       interested in receiving; all others should be 'nullptr'
        ///     - The application must ensure that no other threads are executing
        ///       functions for which the tracing functions are changing.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void __zecall
        SetPrologues(
            core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the collection of callbacks to be executed **after** driver
        ///        execution.
        /// 
        /// @details
        ///     - The application only needs to set the function pointers it is
        ///       interested in receiving; all others should be 'nullptr'
        ///     - The application must ensure that no other threads are executing
        ///       functions for which the tracing functions are changing.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void __zecall
        SetEpilogues(
            core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Enables (or disables) the tracer
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void __zecall
        SetEnabled(
            ze::bool_t enable                               ///< [in] enable the tracer if true; disable if false
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_version_t to std::string
    std::string to_string( const Tracer::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_t to std::string
    std::string to_string( const Tracer::desc_t val );

} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_TRACING_HPP
