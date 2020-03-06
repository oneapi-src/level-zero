/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    using zet_driver_object_t                 = object_t < zet_driver_handle_t >;
    using zet_driver_factory_t                = singleton_factory_t < zet_driver_object_t, zet_driver_handle_t >;

    using zet_device_object_t                 = object_t < zet_device_handle_t >;
    using zet_device_factory_t                = singleton_factory_t < zet_device_object_t, zet_device_handle_t >;

    using zet_command_list_object_t           = object_t < zet_command_list_handle_t >;
    using zet_command_list_factory_t          = singleton_factory_t < zet_command_list_object_t, zet_command_list_handle_t >;

    using zet_module_object_t                 = object_t < zet_module_handle_t >;
    using zet_module_factory_t                = singleton_factory_t < zet_module_object_t, zet_module_handle_t >;

    using zet_kernel_object_t                 = object_t < zet_kernel_handle_t >;
    using zet_kernel_factory_t                = singleton_factory_t < zet_kernel_object_t, zet_kernel_handle_t >;

    using zet_metric_group_object_t           = object_t < zet_metric_group_handle_t >;
    using zet_metric_group_factory_t          = singleton_factory_t < zet_metric_group_object_t, zet_metric_group_handle_t >;

    using zet_metric_object_t                 = object_t < zet_metric_handle_t >;
    using zet_metric_factory_t                = singleton_factory_t < zet_metric_object_t, zet_metric_handle_t >;

    using zet_metric_tracer_object_t          = object_t < zet_metric_tracer_handle_t >;
    using zet_metric_tracer_factory_t         = singleton_factory_t < zet_metric_tracer_object_t, zet_metric_tracer_handle_t >;

    using zet_metric_query_pool_object_t      = object_t < zet_metric_query_pool_handle_t >;
    using zet_metric_query_pool_factory_t     = singleton_factory_t < zet_metric_query_pool_object_t, zet_metric_query_pool_handle_t >;

    using zet_metric_query_object_t           = object_t < zet_metric_query_handle_t >;
    using zet_metric_query_factory_t          = singleton_factory_t < zet_metric_query_object_t, zet_metric_query_handle_t >;

    using zet_tracer_object_t                 = object_t < zet_tracer_handle_t >;
    using zet_tracer_factory_t                = singleton_factory_t < zet_tracer_object_t, zet_tracer_handle_t >;

    using zet_sysman_object_t                 = object_t < zet_sysman_handle_t >;
    using zet_sysman_factory_t                = singleton_factory_t < zet_sysman_object_t, zet_sysman_handle_t >;

    using zet_sysman_pwr_object_t             = object_t < zet_sysman_pwr_handle_t >;
    using zet_sysman_pwr_factory_t            = singleton_factory_t < zet_sysman_pwr_object_t, zet_sysman_pwr_handle_t >;

    using zet_sysman_freq_object_t            = object_t < zet_sysman_freq_handle_t >;
    using zet_sysman_freq_factory_t           = singleton_factory_t < zet_sysman_freq_object_t, zet_sysman_freq_handle_t >;

    using zet_sysman_engine_object_t          = object_t < zet_sysman_engine_handle_t >;
    using zet_sysman_engine_factory_t         = singleton_factory_t < zet_sysman_engine_object_t, zet_sysman_engine_handle_t >;

    using zet_sysman_standby_object_t         = object_t < zet_sysman_standby_handle_t >;
    using zet_sysman_standby_factory_t        = singleton_factory_t < zet_sysman_standby_object_t, zet_sysman_standby_handle_t >;

    using zet_sysman_firmware_object_t        = object_t < zet_sysman_firmware_handle_t >;
    using zet_sysman_firmware_factory_t       = singleton_factory_t < zet_sysman_firmware_object_t, zet_sysman_firmware_handle_t >;

    using zet_sysman_mem_object_t             = object_t < zet_sysman_mem_handle_t >;
    using zet_sysman_mem_factory_t            = singleton_factory_t < zet_sysman_mem_object_t, zet_sysman_mem_handle_t >;

    using zet_sysman_fabric_port_object_t     = object_t < zet_sysman_fabric_port_handle_t >;
    using zet_sysman_fabric_port_factory_t    = singleton_factory_t < zet_sysman_fabric_port_object_t, zet_sysman_fabric_port_handle_t >;

    using zet_sysman_temp_object_t            = object_t < zet_sysman_temp_handle_t >;
    using zet_sysman_temp_factory_t           = singleton_factory_t < zet_sysman_temp_object_t, zet_sysman_temp_handle_t >;

    using zet_sysman_psu_object_t             = object_t < zet_sysman_psu_handle_t >;
    using zet_sysman_psu_factory_t            = singleton_factory_t < zet_sysman_psu_object_t, zet_sysman_psu_handle_t >;

    using zet_sysman_fan_object_t             = object_t < zet_sysman_fan_handle_t >;
    using zet_sysman_fan_factory_t            = singleton_factory_t < zet_sysman_fan_object_t, zet_sysman_fan_handle_t >;

    using zet_sysman_led_object_t             = object_t < zet_sysman_led_handle_t >;
    using zet_sysman_led_factory_t            = singleton_factory_t < zet_sysman_led_object_t, zet_sysman_led_handle_t >;

    using zet_sysman_ras_object_t             = object_t < zet_sysman_ras_handle_t >;
    using zet_sysman_ras_factory_t            = singleton_factory_t < zet_sysman_ras_object_t, zet_sysman_ras_handle_t >;

    using zet_sysman_diag_object_t            = object_t < zet_sysman_diag_handle_t >;
    using zet_sysman_diag_factory_t           = singleton_factory_t < zet_sysman_diag_object_t, zet_sysman_diag_handle_t >;

    using zet_sysman_event_object_t           = object_t < zet_sysman_event_handle_t >;
    using zet_sysman_event_factory_t          = singleton_factory_t < zet_sysman_event_object_t, zet_sysman_event_handle_t >;

    using zet_debug_session_object_t          = object_t < zet_debug_session_handle_t >;
    using zet_debug_session_factory_t         = singleton_factory_t < zet_debug_session_object_t, zet_debug_session_handle_t >;

}
