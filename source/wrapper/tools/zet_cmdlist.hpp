/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_cmdlist.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Command List
 *
 */
#ifndef _ZET_CMDLIST_HPP
#define _ZET_CMDLIST_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList : public ze::CommandList
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::CommandList::CommandList;

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Append metric tracer marker into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricTracerMarker(
            MetricTracer* pMetricTracer,                    ///< [in] pointer to the metric tracer
            uint32_t value                                  ///< [in] tracer marker value
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query begin into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricQueryBegin(
            MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query end into a command list.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricQueryEnd(
            MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
            ze::Event* pCompletionEvent = nullptr           ///< [in][optional] pointer to the completion event to signal
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Appends metric query commands to flush all caches.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        /// @throws result_t
        void __zecall
        AppendMetricMemoryBarrier(
            void
            );

    };

} // namespace zet

namespace zet
{
} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_CMDLIST_HPP
