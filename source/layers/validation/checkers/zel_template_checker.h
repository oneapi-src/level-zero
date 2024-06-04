/*
 *
 * Copyright (C) 2024 Intel Corporation
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
                ze_result_t zeInit ( ze_init_flags_t flags ) override;
            };
            class ZESvalidationCheckerTemplate : public ZESValidationEntryPoints {
            public:
                ze_result_t zesInit ( zes_init_flags_t flags ) override;
            };
            class ZETvalidationCheckerTemplate : public ZETValidationEntryPoints {
            public:
                ze_result_t zetModuleGetDebugInfo ( zet_module_handle_t hModule, zet_module_debug_info_format_t format, size_t* pSize, uint8_t* pDebugInfo ) override;
            };
        bool enableValidationCheckerTemplate = false;
    };
    extern class validationCheckerTemplate templateChecker;
}