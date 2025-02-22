/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
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

    using zet_metric_tracer_exp_object_t      = object_t < zet_metric_tracer_exp_handle_t >;
    using zet_metric_tracer_exp_factory_t     = singleton_factory_t < zet_metric_tracer_exp_object_t, zet_metric_tracer_exp_handle_t >;

    using zet_metric_decoder_exp_object_t     = object_t < zet_metric_decoder_exp_handle_t >;
    using zet_metric_decoder_exp_factory_t    = singleton_factory_t < zet_metric_decoder_exp_object_t, zet_metric_decoder_exp_handle_t >;

    using zet_metric_programmable_exp_object_t    = object_t < zet_metric_programmable_exp_handle_t >;
    using zet_metric_programmable_exp_factory_t   = singleton_factory_t < zet_metric_programmable_exp_object_t, zet_metric_programmable_exp_handle_t >;

}

#if defined(__cplusplus)
extern "C" {
#endif

__zedlllocal void ZE_APICALL
zetGetMetricDecoderExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricProgrammableExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricTracerExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetDeviceProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetDeviceExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetContextProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetCommandListProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetKernelProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetModuleProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetDebugProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricGroupProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricGroupExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricQueryProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricQueryPoolProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetMetricStreamerProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zetGetTracerExpProcAddrTableLegacy();

#if defined(__cplusplus)
};
#endif
