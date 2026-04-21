/*
 *
 * Copyright (C) 2019-2026 Intel Corporation
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
#include "zer_ddi.h"
#include "ze_util.h"
#include "loader/ze_loader.h"
#include "handle_lifetime.h"
#include "ze_entry_points.h"
#include "zet_entry_points.h"
#include "zes_entry_points.h"
#include "zer_entry_points.h"
#include "ze_logger.h"
#include "ze_to_string.h"
#include "zes_to_string.h"
#include "zet_to_string.h"
#include "zer_to_string.h"
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
        ZERValidationEntryPoints *zerValidation;
    };
    class __zedlllocal context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_CURRENT;

        bool enableHandleLifetime = false;
        bool enableThreadingValidation = false;
        bool verboseLogging = false;

        ze_dditable_t   zeDdiTable = {};
        zet_dditable_t  zetDdiTable = {};
        zes_dditable_t  zesDdiTable = {};
        zer_dditable_t  zerDdiTable = {};

        std::vector<validationChecker *> validationHandlers;
        std::unique_ptr<HandleLifetimeValidation> handleLifetime;
        
        // Raw pointer — the loader owns the ZeLogger and guarantees it outlives
        // the validation layer during normal operation (dlclose happens before
        // zel_logger is destroyed in context_t::~context_t()).  Using a raw pointer
        // (rather than shared_ptr) avoids _Sp_counted_base::_M_release() being
        // called during _dl_call_fini after the control block has been freed.
        loader::ZeLogger *logger;

        static context_t& getInstance() {
            static context_t instance;
            return instance;
        }
        context_t();
        ~context_t();
    };

    extern context_t& context;
} // namespace validation_layer
