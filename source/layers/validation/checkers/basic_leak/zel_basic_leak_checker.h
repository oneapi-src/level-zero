/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_basic_leak_checker.h
 *
 */

#pragma once

#include <atomic>
#include <string>
#include <unordered_map>

#include "ze_api.h"
#include "ze_validation_layer.h"

namespace validation_layer
{
    // Counts the number of calls to each function and reports (in the dtor)
    // the difference between the number of calls to create and destroy functions
    // if there is a mismatch.
    //
    // The functions to track are passed in the constructor.
    //
    // A sample output is this:
    // ------------------------------------------------------------------------
    //                zeContextCreate = 1     \--->        zeContextDestroy = 1
    //           zeCommandQueueCreate = 1     \--->   zeCommandQueueDestroy = 1
    //                 zeModuleCreate = 1     \--->         zeModuleDestroy = 1
    //                 zeKernelCreate = 1     \--->         zeKernelDestroy = 1
    //              zeEventPoolCreate = 1     \--->      zeEventPoolDestroy = 1
    //   zeCommandListCreateImmediate = 1     |
    //            zeCommandListCreate = 1     \--->    zeCommandListDestroy = 1  ---> LEAK = 1
    //                  zeEventCreate = 2     \--->          zeEventDestroy = 2
    //                  zeFenceCreate = 1     \--->          zeFenceDestroy = 1
    //                  zeImageCreate = 0     \--->          zeImageDestroy = 0
    //                zeSamplerCreate = 0     \--->        zeSamplerDestroy = 0
    //               zeMemAllocDevice = 0     |
    //                 zeMemAllocHost = 1     |
    //               zeMemAllocShared = 0     \--->               zeMemFree = 1
    //                                        \--->            zeMemFreeExt = 0
    //
    class __zedlllocal basic_leakChecker : public validationChecker{
        public:
            basic_leakChecker();
            ~basic_leakChecker();

            class ZEbasic_leakChecker : public ZEValidationEntryPoints {
            public:
                ZEbasic_leakChecker();
                ~ZEbasic_leakChecker();

                ze_result_t zeContextCreateEpilogue(ze_driver_handle_t, const ze_context_desc_t *, ze_context_handle_t*, ze_result_t result) override;
                ze_result_t zeContextDestroyEpilogue(ze_context_handle_t, ze_result_t result) override;
                ze_result_t zeCommandQueueCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t *, ze_command_queue_handle_t *, ze_result_t result) override;
                ze_result_t zeCommandQueueDestroyEpilogue(ze_command_queue_handle_t, ze_result_t result) override;
                ze_result_t zeModuleCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_module_desc_t*, ze_module_handle_t*, ze_module_build_log_handle_t*, ze_result_t result) override;
                ze_result_t zeModuleDestroyEpilogue(ze_module_handle_t, ze_result_t result) override;
                ze_result_t zeKernelCreateEpilogue(ze_module_handle_t, const ze_kernel_desc_t*, ze_kernel_handle_t*, ze_result_t result) override;
                ze_result_t zeKernelDestroyEpilogue(ze_kernel_handle_t, ze_result_t result) override;
                ze_result_t zeEventPoolCreateEpilogue(ze_context_handle_t, const ze_event_pool_desc_t*, uint32_t, ze_device_handle_t*, ze_event_pool_handle_t*, ze_result_t result) override;
                ze_result_t zeEventPoolDestroyEpilogue(ze_event_pool_handle_t, ze_result_t result) override;
                ze_result_t zeCommandListCreateImmediateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t*, ze_command_list_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_list_desc_t*, ze_command_list_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListDestroyEpilogue(ze_command_list_handle_t, ze_result_t result) override;
                ze_result_t zeEventCreateEpilogue(ze_event_pool_handle_t, const ze_event_desc_t *, ze_event_handle_t *, ze_result_t result) override;
                ze_result_t zeEventDestroyEpilogue(ze_event_handle_t, ze_result_t result) override;
                ze_result_t zeFenceCreateEpilogue(ze_command_queue_handle_t, const ze_fence_desc_t *, ze_fence_handle_t*, ze_result_t result) override;
                ze_result_t zeFenceDestroyEpilogue(ze_fence_handle_t, ze_result_t result) override;
                ze_result_t zeImageCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_image_desc_t*, ze_image_handle_t*, ze_result_t result) override;
                ze_result_t zeImageViewCreateExtEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView , ze_result_t result) override;
                ze_result_t zeImageDestroyEpilogue(ze_image_handle_t, ze_result_t result) override;
                ze_result_t zeSamplerCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_sampler_desc_t*, ze_sampler_handle_t*, ze_result_t result) override;
                ze_result_t zeSamplerDestroyEpilogue(ze_sampler_handle_t, ze_result_t result) override;
                ze_result_t zeMemAllocDeviceEpilogue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **, ze_result_t result) override;
                ze_result_t zeMemAllocHostEpilogue(ze_context_handle_t, const ze_host_mem_alloc_desc_t *, size_t, size_t, void **, ze_result_t result) override;
                ze_result_t zeMemAllocSharedEpilogue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, const ze_host_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **, ze_result_t result) override;
                ze_result_t zeMemFreeEpilogue(ze_context_handle_t, void *, ze_result_t result) override;
                ze_result_t zeMemFreeExtEpilogue(ze_context_handle_t, const ze_memory_free_ext_desc_t*, void *, ze_result_t result) override;
            private:
                void countFunctionCall(const std::string &functionName);
                std::unordered_map<std::string, std::atomic<int64_t>> counts;
            };

            class ZESbasic_leakChecker : public ZESValidationEntryPoints {};
            class ZETbasic_leakChecker : public ZETValidationEntryPoints {};
            bool enablebasic_leak = false;
    };
    extern class basic_leakChecker basic_leak_checker;
}