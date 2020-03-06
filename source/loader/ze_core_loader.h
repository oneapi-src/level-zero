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
    using ze_driver_object_t                  = object_t < ze_driver_handle_t >;
    using ze_driver_factory_t                 = singleton_factory_t < ze_driver_object_t, ze_driver_handle_t >;

    using ze_device_object_t                  = object_t < ze_device_handle_t >;
    using ze_device_factory_t                 = singleton_factory_t < ze_device_object_t, ze_device_handle_t >;

    using ze_command_queue_object_t           = object_t < ze_command_queue_handle_t >;
    using ze_command_queue_factory_t          = singleton_factory_t < ze_command_queue_object_t, ze_command_queue_handle_t >;

    using ze_command_list_object_t            = object_t < ze_command_list_handle_t >;
    using ze_command_list_factory_t           = singleton_factory_t < ze_command_list_object_t, ze_command_list_handle_t >;

    using ze_fence_object_t                   = object_t < ze_fence_handle_t >;
    using ze_fence_factory_t                  = singleton_factory_t < ze_fence_object_t, ze_fence_handle_t >;

    using ze_event_pool_object_t              = object_t < ze_event_pool_handle_t >;
    using ze_event_pool_factory_t             = singleton_factory_t < ze_event_pool_object_t, ze_event_pool_handle_t >;

    using ze_event_object_t                   = object_t < ze_event_handle_t >;
    using ze_event_factory_t                  = singleton_factory_t < ze_event_object_t, ze_event_handle_t >;

    using ze_image_object_t                   = object_t < ze_image_handle_t >;
    using ze_image_factory_t                  = singleton_factory_t < ze_image_object_t, ze_image_handle_t >;

    using ze_module_object_t                  = object_t < ze_module_handle_t >;
    using ze_module_factory_t                 = singleton_factory_t < ze_module_object_t, ze_module_handle_t >;

    using ze_module_build_log_object_t        = object_t < ze_module_build_log_handle_t >;
    using ze_module_build_log_factory_t       = singleton_factory_t < ze_module_build_log_object_t, ze_module_build_log_handle_t >;

    using ze_kernel_object_t                  = object_t < ze_kernel_handle_t >;
    using ze_kernel_factory_t                 = singleton_factory_t < ze_kernel_object_t, ze_kernel_handle_t >;

    using ze_sampler_object_t                 = object_t < ze_sampler_handle_t >;
    using ze_sampler_factory_t                = singleton_factory_t < ze_sampler_object_t, ze_sampler_handle_t >;

}
