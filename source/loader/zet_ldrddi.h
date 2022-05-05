/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_ldrddi.h
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

    using zet_context_object_t                = object_t < zet_context_handle_t >;
    using zet_context_factory_t               = singleton_factory_t < zet_context_object_t, zet_context_handle_t >;

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

    using zet_metric_streamer_object_t        = object_t < zet_metric_streamer_handle_t >;
    using zet_metric_streamer_factory_t       = singleton_factory_t < zet_metric_streamer_object_t, zet_metric_streamer_handle_t >;

    using zet_metric_query_pool_object_t      = object_t < zet_metric_query_pool_handle_t >;
    using zet_metric_query_pool_factory_t     = singleton_factory_t < zet_metric_query_pool_object_t, zet_metric_query_pool_handle_t >;

    using zet_metric_query_object_t           = object_t < zet_metric_query_handle_t >;
    using zet_metric_query_factory_t          = singleton_factory_t < zet_metric_query_object_t, zet_metric_query_handle_t >;

    using zet_tracer_exp_object_t             = object_t < zet_tracer_exp_handle_t >;
    using zet_tracer_exp_factory_t            = singleton_factory_t < zet_tracer_exp_object_t, zet_tracer_exp_handle_t >;

    using zet_debug_session_object_t          = object_t < zet_debug_session_handle_t >;
    using zet_debug_session_factory_t         = singleton_factory_t < zet_debug_session_object_t, zet_debug_session_handle_t >;

}
