<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_loader_internal.h generated from ze_loader_internal.h.mako
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
#include "../utils/logging.h"
#include "spdlog/spdlog.h"
namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Driver Type Enumerations
    /// @details The ordering of the drivers reported to the user is based on the order of the enumerations provided.
    /// When additional driver types are added, they should be added to the end of the list to avoid reporting new device types
    /// before known device types.
    typedef enum _zel_driver_type_t
    {
        ZEL_DRIVER_TYPE_DISCRETE_GPU= 0,          ///< The driver has Discrete GPUs only
        ZEL_DRIVER_TYPE_GPU = 1,                  ///< The driver has Heterogenous GPU types
        ZEL_DRIVER_TYPE_INTEGRATED_GPU = 2,       ///< The driver has Integrated GPUs only
        ZEL_DRIVER_TYPE_MIXED = 3,                ///< The driver has Heterogenous driver types not limited to GPU or NPU.
        ZEL_DRIVER_TYPE_OTHER = 4,                ///< The driver has No GPU Devices and has other device types only
        ZEL_DRIVER_TYPE_FORCE_UINT32 = 0x7fffffff

    } zel_driver_type_t;
    //////////////////////////////////////////////////////////////////////////
    struct driver_t
    {
        HMODULE handle = NULL;
        ze_result_t initStatus = ZE_RESULT_SUCCESS;
        ze_result_t initSysManStatus = ZE_RESULT_SUCCESS;
        ze_result_t initDriversStatus = ZE_RESULT_SUCCESS;
        dditable_t dditable = {};
        std::string name;
        bool driverInuse = false;
        zel_driver_type_t driverType = ZEL_DRIVER_TYPE_FORCE_UINT32;
        ze_driver_properties_t properties;
        bool pciOrderingRequested = false;
    };

    using driver_vector_t = std::vector< driver_t >;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        /// factories
        ///////////////////////////////////////////////////////////////////////////////
        %for obj in th.extract_objs(specs, r"handle"):
        %if 'class' in obj:
        <%
        
            _handle_t = th.subt(n, tags, obj['name'])
            _factory_t = re.sub(r"(\w+)_handle_t", r"\1_factory_t", _handle_t)
            _factory = re.sub(r"(\w+)_handle_t", r"\1_factory", _handle_t)
        %>${th.append_ws(_factory_t, 35)} ${_factory};
        %endif
        %endfor
        ///////////////////////////////////////////////////////////////////////////////
        /// end factories
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
        bool driverSorting(driver_vector_t *drivers, ze_init_driver_type_desc_t* desc, bool sysmanOnly);
        ~context_t();
        bool intercept_enabled = false;
        bool debugTraceEnabled = false;
        bool tracingLayerEnabled = false;
        std::once_flag coreDriverSortOnce;
        std::once_flag sysmanDriverSortOnce;
        std::atomic<bool> sortingInProgress = {false};
        bool instrumentationEnabled = false;
        dditable_t tracing_dditable = {};
        std::shared_ptr<Logger> zel_logger;
    };

    extern context_t *context;
}
