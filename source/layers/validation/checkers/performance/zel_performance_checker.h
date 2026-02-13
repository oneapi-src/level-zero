/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_performance_checker.h
 *
 */

#pragma once 

#include <string>
#include "ze_api.h"
#include "ze_validation_layer.h"

namespace validation_layer
{
    class __zedlllocal performanceChecker : public validationChecker{
        public:
            performanceChecker();
            ~performanceChecker();

            class ZEperformanceChecker : public ZEValidationEntryPoints {
                ze_result_t zeCommandListCreateImmediateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t*, ze_command_list_handle_t*, ze_result_t result) override;
            };
            class ZESperformanceChecker : public ZESValidationEntryPoints {};
            class ZETperformanceChecker : public ZETValidationEntryPoints {};

 
        bool enableperformance = false;
    };
    extern class performanceChecker performance_checker;
}