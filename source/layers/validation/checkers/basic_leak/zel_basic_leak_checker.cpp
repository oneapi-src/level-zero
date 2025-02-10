/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_basic_leak_checker.cpp
 *
 */
#include "zel_basic_leak_checker.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace validation_layer
{
    class basic_leakChecker basic_leak_checker;

    basic_leakChecker::basic_leakChecker() {
        enablebasic_leak = getenv_tobool( "ZEL_ENABLE_BASIC_LEAK_CHECKER" );
        if(enablebasic_leak) {
            basic_leakChecker::ZEbasic_leakChecker *zeChecker = new basic_leakChecker::ZEbasic_leakChecker;
            basic_leakChecker::ZESbasic_leakChecker *zesChecker = new basic_leakChecker::ZESbasic_leakChecker;
            basic_leakChecker::ZETbasic_leakChecker *zetChecker = new basic_leakChecker::ZETbasic_leakChecker;
            basic_leak_checker.zeValidation = zeChecker;
            basic_leak_checker.zetValidation = zetChecker;
            basic_leak_checker.zesValidation = zesChecker;
            validation_layer::context.validationHandlers.push_back(&basic_leak_checker);
        }
    }

    basic_leakChecker::~basic_leakChecker() {
        if(enablebasic_leak) {
            delete basic_leak_checker.zeValidation;
            delete basic_leak_checker.zetValidation;
            delete basic_leak_checker.zesValidation;
        }
    }

    struct ctorsAndDtors {
        std::vector<std::string> ctors;
        std::vector<std::string> dtors;
    };

    static std::vector<ctorsAndDtors> createDestroySet() {
        return {
            {{"zeContextCreate"}, {"zeContextDestroy"}},
            {{"zeCommandQueueCreate"}, {"zeCommandQueueDestroy"}},
            {{"zeModuleCreate"}, {"zeModuleDestroy"}},
            {{"zeKernelCreate"}, {"zeKernelDestroy"}},
            {{"zeEventPoolCreate"}, {"zeEventPoolDestroy"}},
            {{"zeCommandListCreateImmediate", "zeCommandListCreate"}, {"zeCommandListDestroy"}},
            {{"zeEventCreate"}, {"zeEventDestroy"}},
            {{"zeFenceCreate"}, {"zeFenceDestroy"}},
            {{"zeImageCreate", "zeImageViewCreateExt"}, {"zeImageDestroy"}},
            {{"zeSamplerCreate"}, {"zeSamplerDestroy"}},
            {{"zeMemAllocDevice", "zeMemAllocHost", "zeMemAllocShared"}, {"zeMemFree", "zeMemFreeExt"}}
        };
    }

    basic_leakChecker::ZEbasic_leakChecker::ZEbasic_leakChecker() {
        // initialize counts for all functions that should be tracked
        auto set = createDestroySet();
        for (const auto &s : set) {
            for (auto &name : s.ctors) {
                counts[name] = 0;
            }
            for (auto &name : s.dtors) {
                counts[name] = 0;
            }
        }
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeContextCreateEpilogue(ze_driver_handle_t, const ze_context_desc_t *, ze_context_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeContextCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeContextDestroyEpilogue(ze_context_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeContextDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeCommandQueueCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t *, ze_command_queue_handle_t *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeCommandQueueCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeCommandQueueDestroyEpilogue(ze_command_queue_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeCommandQueueDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeModuleCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_module_desc_t*, ze_module_handle_t*, ze_module_build_log_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeModuleCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeModuleDestroyEpilogue(ze_module_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeModuleDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeKernelCreateEpilogue(ze_module_handle_t, const ze_kernel_desc_t*, ze_kernel_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeKernelCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeKernelDestroyEpilogue(ze_kernel_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeKernelDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeEventPoolCreateEpilogue(ze_context_handle_t, const ze_event_pool_desc_t*, uint32_t, ze_device_handle_t*, ze_event_pool_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeEventPoolCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeEventPoolDestroyEpilogue(ze_event_pool_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeEventPoolDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeCommandListCreateImmediateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t*, ze_command_list_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeCommandListCreateImmediate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeCommandListCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_list_desc_t*, ze_command_list_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeCommandListCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeCommandListDestroyEpilogue(ze_command_list_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeCommandListDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeEventCreateEpilogue(ze_event_pool_handle_t, const ze_event_desc_t *, ze_event_handle_t *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeEventCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeEventDestroyEpilogue(ze_event_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeEventDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeFenceCreateEpilogue(ze_command_queue_handle_t, const ze_fence_desc_t *, ze_fence_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeFenceCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeFenceDestroyEpilogue(ze_fence_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeFenceDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeImageCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_image_desc_t*, ze_image_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeImageCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeImageViewCreateExtEpilogue(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView , ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeImageViewCreateExt");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeImageDestroyEpilogue(ze_image_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeImageDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeSamplerCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_sampler_desc_t*, ze_sampler_handle_t*, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeSamplerCreate");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeSamplerDestroyEpilogue(ze_sampler_handle_t, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeSamplerDestroy");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeMemAllocDeviceEpilogue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeMemAllocDevice");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeMemAllocHostEpilogue(ze_context_handle_t, const ze_host_mem_alloc_desc_t *, size_t, size_t, void **, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeMemAllocHost");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeMemAllocSharedEpilogue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, const ze_host_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeMemAllocShared");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeMemFreeEpilogue(ze_context_handle_t, void *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeMemFree");
        }
        return result;
    }

    ze_result_t basic_leakChecker::ZEbasic_leakChecker::zeMemFreeExtEpilogue(ze_context_handle_t, const ze_memory_free_ext_desc_t*, void *, ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            countFunctionCall("zeMemFreeExt");
        }
        return result;
    }

    void basic_leakChecker::ZEbasic_leakChecker::countFunctionCall(const std::string &functionName)
    {
        auto it = counts.find(functionName);

        // make sure there is no insertion happening during program exeuction
        // as inserting to the map is not thread safe
        if (it == counts.end()) {
            return;
        }

        it->second.fetch_add(1, std::memory_order_relaxed);
    }

    basic_leakChecker::ZEbasic_leakChecker::~ZEbasic_leakChecker() {
        std::cerr << "Check balance of create/destroy calls\n";
        std::cerr << "----------------------------------------------------------\n";
        auto set = createDestroySet();
        for (const auto &s : set) {
            auto &ctors = s.ctors;
            auto &dtors = s.dtors;
            int64_t diff = 0;
            for (size_t i = 0; i < ctors.size(); i++) {
                auto name = ctors[i];
                auto zeCount = counts[name].load();
                diff += zeCount;

                if (i > 0) {
                    std::cerr << " |\n";
                }

                std::cerr << std::setw(30) << std::right << name;
                std::cerr << " = ";
                std::cerr << std::setw(5) << std::left << zeCount;
            }

            std::cerr << " \\--->";

            for (size_t i = 0; i < dtors.size(); i++) {
                auto name = dtors[i];
                auto zeCount = counts[name].load();
                diff -= zeCount;

                if (i > 0) {
                    std::cerr << "\n";
                    std::cerr << std::setw(44) << std::right << "\\--->";
                }

                std::cerr << std::setw(30) << std::right << name;
                std::cerr << " = ";
                std::cerr << std::setw(5) << std::left << zeCount;
            }

            if (diff) {
                std::cerr << " ---> LEAK = " << diff;
            }

            std::cerr << std::endl;
        }
    }
}
