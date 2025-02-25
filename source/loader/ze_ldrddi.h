/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_ldrddi.h
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

    using ze_context_object_t                 = object_t < ze_context_handle_t >;
    using ze_context_factory_t                = singleton_factory_t < ze_context_object_t, ze_context_handle_t >;

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

    using ze_physical_mem_object_t            = object_t < ze_physical_mem_handle_t >;
    using ze_physical_mem_factory_t           = singleton_factory_t < ze_physical_mem_object_t, ze_physical_mem_handle_t >;

    using ze_fabric_vertex_object_t           = object_t < ze_fabric_vertex_handle_t >;
    using ze_fabric_vertex_factory_t          = singleton_factory_t < ze_fabric_vertex_object_t, ze_fabric_vertex_handle_t >;

    using ze_fabric_edge_object_t             = object_t < ze_fabric_edge_handle_t >;
    using ze_fabric_edge_factory_t            = singleton_factory_t < ze_fabric_edge_object_t, ze_fabric_edge_handle_t >;

    using ze_external_semaphore_ext_object_t  = object_t < ze_external_semaphore_ext_handle_t >;
    using ze_external_semaphore_ext_factory_t = singleton_factory_t < ze_external_semaphore_ext_object_t, ze_external_semaphore_ext_handle_t >;

    using ze_rtas_builder_exp_object_t        = object_t < ze_rtas_builder_exp_handle_t >;
    using ze_rtas_builder_exp_factory_t       = singleton_factory_t < ze_rtas_builder_exp_object_t, ze_rtas_builder_exp_handle_t >;

    using ze_rtas_parallel_operation_exp_object_t = object_t < ze_rtas_parallel_operation_exp_handle_t >;
    using ze_rtas_parallel_operation_exp_factory_t    = singleton_factory_t < ze_rtas_parallel_operation_exp_object_t, ze_rtas_parallel_operation_exp_handle_t >;

    __zedlllocal void ZE_APICALL
    zeDestroyDDiDriverTables(ze_dditable_driver_t* pDdiTable);
}

#if defined(__cplusplus)
extern "C" {
#endif

__zedlllocal void ZE_APICALL
zeGetGlobalProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetRTASBuilderExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetRTASParallelOperationExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDriverProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDriverExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDeviceProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetDeviceExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetContextProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetCommandQueueProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetCommandListProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetCommandListExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetEventProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetEventExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetEventPoolProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetFenceProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetImageProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetImageExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetKernelProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetKernelExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetMemProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetMemExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetModuleProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetModuleBuildLogProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetPhysicalMemProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetSamplerProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetVirtualMemProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetFabricEdgeExpProcAddrTableLegacy();
__zedlllocal void ZE_APICALL
zeGetFabricVertexExpProcAddrTableLegacy();

#if defined(__cplusplus)
};
#endif
