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

#include "ze_ddi.h"
#include "zet_ddi.h"
#include "zes_ddi.h"

#include "ze_util.h"
#include "ze_object.h"

#include "ze_ldrddi.h"
#include "zet_ldrddi.h"
#include "zes_ldrddi.h"

#include "loader/ze_loader.h"

namespace loader
{
    //////////////////////////////////////////////////////////////////////////
    struct driver_t
    {
        HMODULE handle = NULL;
        ze_result_t initStatus = ZE_RESULT_SUCCESS;
        dditable_t dditable = {};
        std::string name;
    };

    using driver_vector_t = std::vector< driver_t >;

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_CURRENT;

        driver_vector_t drivers;

        HMODULE validationLayer = nullptr;
        HMODULE tracingLayer = nullptr;

        bool forceIntercept = false;
        std::vector<zel_component_version_t> compVersions;
        const char *LOADER_COMP_NAME = "loader";

        ze_result_t check_drivers(ze_init_flags_t flags);
        void debug_trace_message(std::string errorMessage, std::string errorValue);
        ze_result_t init();
        ze_result_t init_driver(driver_t driver, ze_init_flags_t flags);
        void add_loader_version();
        ~context_t();
        bool intercept_enabled = false;
        bool debugTraceEnabled = false;
    };

    extern context_t *context;
    extern ze_event_factory_t ze_event_factory;
}
