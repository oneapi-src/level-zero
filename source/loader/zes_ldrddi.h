/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_ldrddi.h
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using zes_driver_object_t                 = object_t < zes_driver_handle_t >;
    using zes_driver_factory_t                = singleton_factory_t < zes_driver_object_t, zes_driver_handle_t >;

    using zes_device_object_t                 = object_t < zes_device_handle_t >;
    using zes_device_factory_t                = singleton_factory_t < zes_device_object_t, zes_device_handle_t >;

    using zes_sched_object_t                  = object_t < zes_sched_handle_t >;
    using zes_sched_factory_t                 = singleton_factory_t < zes_sched_object_t, zes_sched_handle_t >;

    using zes_perf_object_t                   = object_t < zes_perf_handle_t >;
    using zes_perf_factory_t                  = singleton_factory_t < zes_perf_object_t, zes_perf_handle_t >;

    using zes_pwr_object_t                    = object_t < zes_pwr_handle_t >;
    using zes_pwr_factory_t                   = singleton_factory_t < zes_pwr_object_t, zes_pwr_handle_t >;

    using zes_freq_object_t                   = object_t < zes_freq_handle_t >;
    using zes_freq_factory_t                  = singleton_factory_t < zes_freq_object_t, zes_freq_handle_t >;

    using zes_engine_object_t                 = object_t < zes_engine_handle_t >;
    using zes_engine_factory_t                = singleton_factory_t < zes_engine_object_t, zes_engine_handle_t >;

    using zes_standby_object_t                = object_t < zes_standby_handle_t >;
    using zes_standby_factory_t               = singleton_factory_t < zes_standby_object_t, zes_standby_handle_t >;

    using zes_firmware_object_t               = object_t < zes_firmware_handle_t >;
    using zes_firmware_factory_t              = singleton_factory_t < zes_firmware_object_t, zes_firmware_handle_t >;

    using zes_mem_object_t                    = object_t < zes_mem_handle_t >;
    using zes_mem_factory_t                   = singleton_factory_t < zes_mem_object_t, zes_mem_handle_t >;

    using zes_fabric_port_object_t            = object_t < zes_fabric_port_handle_t >;
    using zes_fabric_port_factory_t           = singleton_factory_t < zes_fabric_port_object_t, zes_fabric_port_handle_t >;

    using zes_temp_object_t                   = object_t < zes_temp_handle_t >;
    using zes_temp_factory_t                  = singleton_factory_t < zes_temp_object_t, zes_temp_handle_t >;

    using zes_psu_object_t                    = object_t < zes_psu_handle_t >;
    using zes_psu_factory_t                   = singleton_factory_t < zes_psu_object_t, zes_psu_handle_t >;

    using zes_fan_object_t                    = object_t < zes_fan_handle_t >;
    using zes_fan_factory_t                   = singleton_factory_t < zes_fan_object_t, zes_fan_handle_t >;

    using zes_led_object_t                    = object_t < zes_led_handle_t >;
    using zes_led_factory_t                   = singleton_factory_t < zes_led_object_t, zes_led_handle_t >;

    using zes_ras_object_t                    = object_t < zes_ras_handle_t >;
    using zes_ras_factory_t                   = singleton_factory_t < zes_ras_object_t, zes_ras_handle_t >;

    using zes_diag_object_t                   = object_t < zes_diag_handle_t >;
    using zes_diag_factory_t                  = singleton_factory_t < zes_diag_object_t, zes_diag_handle_t >;

    using zes_overclock_object_t              = object_t < zes_overclock_handle_t >;
    using zes_overclock_factory_t             = singleton_factory_t < zes_overclock_object_t, zes_overclock_handle_t >;

}
