/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once
#include <vector>
#include <map>
#include <atomic>

#include "ze_ddi.h"
#include "zet_ddi.h"
#include "zes_ddi.h"

#include "ze_util.h"
#include "ze_object.h"

#include "ze_ldrddi.h"
#include "zet_ldrddi.h"
#include "zes_ldrddi.h"

#include "loader/ze_loader.h"
#include "logging.h"
#include "spdlog/spdlog.h"
namespace loader
{
    //////////////////////////////////////////////////////////////////////////
    struct driver_t
    {
        HMODULE handle = NULL;
        ze_result_t initStatus = ZE_RESULT_SUCCESS;
        ze_result_t initDriversStatus = ZE_RESULT_SUCCESS;
        dditable_t dditable = {};
        std::string name;
        bool driverInuse = false;
    };

    using driver_vector_t = std::vector< driver_t >;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        ze_driver_factory_t                 ze_driver_factory;
        ze_device_factory_t                 ze_device_factory;
        ze_context_factory_t                ze_context_factory;
        ze_command_queue_factory_t          ze_command_queue_factory;
        ze_command_list_factory_t           ze_command_list_factory;
        ze_fence_factory_t                  ze_fence_factory;
        ze_event_pool_factory_t             ze_event_pool_factory;
        ze_event_factory_t                  ze_event_factory;
        ze_image_factory_t                  ze_image_factory;
        ze_module_factory_t                 ze_module_factory;
        ze_module_build_log_factory_t       ze_module_build_log_factory;
        ze_kernel_factory_t                 ze_kernel_factory;
        ze_sampler_factory_t                ze_sampler_factory;
        ze_physical_mem_factory_t           ze_physical_mem_factory;
        ze_fabric_vertex_factory_t          ze_fabric_vertex_factory;
        ze_fabric_edge_factory_t            ze_fabric_edge_factory;
        ze_external_semaphore_ext_factory_t ze_external_semaphore_ext_factory;
        ze_rtas_builder_exp_factory_t       ze_rtas_builder_exp_factory;
        ze_rtas_parallel_operation_exp_factory_t    ze_rtas_parallel_operation_exp_factory;
        ///////////////////////////////////////////////////////////////////////////////
        zes_driver_factory_t                zes_driver_factory;
        zes_device_factory_t                zes_device_factory;
        zes_sched_factory_t                 zes_sched_factory;
        zes_perf_factory_t                  zes_perf_factory;
        zes_pwr_factory_t                   zes_pwr_factory;
        zes_freq_factory_t                  zes_freq_factory;
        zes_engine_factory_t                zes_engine_factory;
        zes_standby_factory_t               zes_standby_factory;
        zes_firmware_factory_t              zes_firmware_factory;
        zes_mem_factory_t                   zes_mem_factory;
        zes_fabric_port_factory_t           zes_fabric_port_factory;
        zes_temp_factory_t                  zes_temp_factory;
        zes_psu_factory_t                   zes_psu_factory;
        zes_fan_factory_t                   zes_fan_factory;
        zes_led_factory_t                   zes_led_factory;
        zes_ras_factory_t                   zes_ras_factory;
        zes_diag_factory_t                  zes_diag_factory;
        zes_overclock_factory_t             zes_overclock_factory;
        zes_vf_factory_t                    zes_vf_factory;
        ///////////////////////////////////////////////////////////////////////////////
        zet_driver_factory_t                zet_driver_factory;
        zet_device_factory_t                zet_device_factory;
        zet_context_factory_t               zet_context_factory;
        zet_command_list_factory_t          zet_command_list_factory;
        zet_module_factory_t                zet_module_factory;
        zet_kernel_factory_t                zet_kernel_factory;
        zet_metric_group_factory_t          zet_metric_group_factory;
        zet_metric_factory_t                zet_metric_factory;
        zet_metric_streamer_factory_t       zet_metric_streamer_factory;
        zet_metric_query_pool_factory_t     zet_metric_query_pool_factory;
        zet_metric_query_factory_t          zet_metric_query_factory;
        zet_tracer_exp_factory_t            zet_tracer_exp_factory;
        zet_debug_session_factory_t         zet_debug_session_factory;
        zet_metric_programmable_exp_factory_t   zet_metric_programmable_exp_factory;
        zet_metric_tracer_exp_factory_t     zet_metric_tracer_exp_factory;
        zet_metric_decoder_exp_factory_t    zet_metric_decoder_exp_factory;
        ///////////////////////////////////////////////////////////////////////////////
        std::mutex image_handle_map_lock;
        std::mutex sampler_handle_map_lock;
        std::unordered_map<ze_image_object_t *, ze_image_handle_t>            image_handle_map;
        std::unordered_map<ze_sampler_object_t *, ze_sampler_handle_t>        sampler_handle_map;
        ze_api_version_t version = ZE_API_VERSION_CURRENT;

        driver_vector_t allDrivers;
        driver_vector_t zeDrivers;
        driver_vector_t zesDrivers;
        driver_vector_t *sysmanInstanceDrivers;

        HMODULE validationLayer = nullptr;
        HMODULE tracingLayer = nullptr;
        bool driverEnvironmentQueried = false;

        bool forceIntercept = false;
        bool initDriversSupport = false;
        std::vector<zel_component_version_t> compVersions;
        const char *LOADER_COMP_NAME = "loader";

        ze_result_t check_drivers(ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly);
        void debug_trace_message(std::string errorMessage, std::string errorValue);
        ze_result_t init();
        ze_result_t init_driver(driver_t &driver, ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool sysmanOnly);
        void add_loader_version();
        ~context_t();
        bool intercept_enabled = false;
        bool debugTraceEnabled = false;
        bool tracingLayerEnabled = false;
        dditable_t tracing_dditable = {};
        std::shared_ptr<Logger> zel_logger;
    };

    extern context_t *context;
}
