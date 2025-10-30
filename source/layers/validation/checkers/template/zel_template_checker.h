/*
 *
 * Copyright (C) 2024-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_template_checker.h
 *
 */

#pragma once 

#include <string>
#include "ze_api.h"
#include "ze_validation_layer.h"

namespace validation_layer
{
    class __zedlllocal validationCheckerTemplate : public validationChecker{
        public:
            validationCheckerTemplate();
            ~validationCheckerTemplate();

            class ZEvalidationCheckerTemplate : public ZEValidationEntryPoints {
            public:
                ze_result_t zeInitPrologue( ze_init_flags_t flags ) override;
            };
            class ZESvalidationCheckerTemplate : public ZESValidationEntryPoints {
            public:
                ze_result_t zesInitPrologue( zes_init_flags_t flags ) override;
            };
            class ZETvalidationCheckerTemplate : public ZETValidationEntryPoints {
            public:
                ze_result_t zetModuleGetDebugInfoPrologue( zet_module_handle_t hModule, zet_module_debug_info_format_t format, size_t* pSize, uint8_t* pDebugInfo ) override;
            };
            class ZERvalidationCheckerTemplate : public ZERValidationEntryPoints {
            public:
            };
        bool enableValidationCheckerTemplate = false;
    };
    extern class validationCheckerTemplate templateChecker;
}