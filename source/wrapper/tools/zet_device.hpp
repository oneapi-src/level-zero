/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_device.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Device
 *
 */
#ifndef _ZET_DEVICE_HPP
#define _ZET_DEVICE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for driver instance
    class Driver : public ze::Driver
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Driver::Driver;

        ~Driver( void ) = default;

        Driver( Driver const& other ) = delete;
        void operator=( Driver const& other ) = delete;

        Driver( Driver&& other ) = delete;
        void operator=( Driver&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device : public ze::Device
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using ze::Device::Device;

        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Activates metric groups.
        /// 
        /// @details
        ///     - MetricGroup must be active until MetricQueryGetDeta and
        ///       ::zetMetricTracerClose.
        ///     - Conflicting metric groups cannot be activated, in such case tha call
        ///       would fail.
        /// @throws result_t
        void __zecall
        ActivateMetricGroups(
            uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
            MetricGroup** ppMetricGroups = nullptr          ///< [in][optional][range(0, count)] handles of the metric groups to
                                                            ///< activate. NULL to deactivate.
            );

    };

} // namespace zet

namespace zet
{
} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_DEVICE_HPP
