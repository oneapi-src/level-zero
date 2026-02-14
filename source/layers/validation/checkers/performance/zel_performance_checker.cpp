/*
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_performance_checker.cpp
 *
 */
#include "zel_performance_checker.h"

namespace validation_layer
{
    class performanceChecker performance_checker;

    performanceChecker::performanceChecker() {
        enableperformance = getenv_tobool( "ZEL_ENABLE_PERFORMANCE_CHECKER" );
        if(enableperformance) {
            performanceChecker::ZEperformanceChecker *zeChecker = new performanceChecker::ZEperformanceChecker;
            performanceChecker::ZESperformanceChecker *zesChecker = new performanceChecker::ZESperformanceChecker;
            performanceChecker::ZETperformanceChecker *zetChecker = new performanceChecker::ZETperformanceChecker;
            performance_checker.zeValidation = zeChecker;
            performance_checker.zetValidation = zetChecker;
            performance_checker.zesValidation = zesChecker;
            validation_layer::context.validationHandlers.push_back(&performance_checker);
        }
    }

    performanceChecker::~performanceChecker() {
        if(enableperformance) {
            delete performance_checker.zeValidation;
            delete performance_checker.zetValidation;
            delete performance_checker.zesValidation;
        }
    }
    ze_result_t performanceChecker::ZEperformanceChecker::zeCommandListCreateImmediateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t* descriptor, ze_command_list_handle_t*, ze_result_t result)
    {
        if (result == ZE_RESULT_SUCCESS) {
            if (descriptor->mode & ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS) {
                context.logger->log_performance("Synchronous command queue may cause performance degradation. Consider using asynchronous mode.");
            }
            if (descriptor->flags & ZE_COMMAND_QUEUE_FLAG_IN_ORDER) {
                if (!(descriptor->flags & ZE_COMMAND_QUEUE_FLAG_COPY_OFFLOAD_HINT)) {
                    context.logger->log_performance("In-order command list created without copy offload hint. Consider using copy offload hint for better performance of copy operations.");
                }
            }
            else {
                context.logger->log_performance("Out-of-order command list created. Consider using in-order command lists for better performance.");
            }
        }
        return result;
    }
}