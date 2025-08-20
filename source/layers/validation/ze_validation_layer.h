/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_layer.h
 *
 */
#pragma once
#include "ze_ddi.h"
#include "zet_ddi.h"
#include "zes_ddi.h"
#include "ze_util.h"
#include "loader/ze_loader.h"
#include "handle_lifetime.h"
#include "ze_entry_points.h"
#include "zet_entry_points.h"
#include "zes_entry_points.h"
#include "logging.h"
#include <memory>
#include <vector>

#define VALIDATION_COMP_NAME "validation layer"

namespace validation_layer
{
    ///////////////////////////////////////////////////////////////////////////////

    class validationChecker {
    public:
        ZEValidationEntryPoints *zeValidation;
        ZESValidationEntryPoints *zesValidation;
        ZETValidationEntryPoints *zetValidation;
    };
    class __zedlllocal context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_CURRENT;

        bool enableHandleLifetime = false;
        bool enableThreadingValidation = false;

        ze_dditable_t   zeDdiTable = {};
        zet_dditable_t  zetDdiTable = {};
        zes_dditable_t  zesDdiTable = {};

        std::vector<validationChecker *> validationHandlers;
        std::unique_ptr<HandleLifetimeValidation> handleLifetime;
        
        std::shared_ptr<loader::Logger> logger;

        static context_t& getInstance() {
            static context_t instance;
            return instance;
        }
        context_t();
        ~context_t();
    };

    extern context_t& context;
} // namespace validation_layer
