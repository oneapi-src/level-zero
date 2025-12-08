/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_system_resource_tracker_checker.h
 *
 */

#pragma once 

#include <string>
#include "ze_api.h"
#include "ze_validation_layer.h"

namespace validation_layer
{
    class __zedlllocal system_resource_trackerChecker : public validationChecker {
        public:
            system_resource_trackerChecker();
            ~system_resource_trackerChecker();
            system_resource_trackerChecker(const system_resource_trackerChecker&) = delete;
            system_resource_trackerChecker& operator=(const system_resource_trackerChecker&) = delete;

            class ZEsystem_resource_trackerChecker : public ZEValidationEntryPoints {
            public:
                // Create/Destroy operations with Prologue/Epilogue pairs for exact memory delta tracking
                ze_result_t zeContextCreatePrologue(ze_driver_handle_t, const ze_context_desc_t *, ze_context_handle_t*) override;
                ze_result_t zeContextCreateEpilogue(ze_driver_handle_t, const ze_context_desc_t *, ze_context_handle_t*, ze_result_t result) override;
                ze_result_t zeContextDestroyPrologue(ze_context_handle_t) override;
                ze_result_t zeContextDestroyEpilogue(ze_context_handle_t, ze_result_t result) override;
                ze_result_t zeCommandQueueCreatePrologue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t *, ze_command_queue_handle_t *) override;
                ze_result_t zeCommandQueueCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t *, ze_command_queue_handle_t *, ze_result_t result) override;
                ze_result_t zeCommandQueueDestroyPrologue(ze_command_queue_handle_t) override;
                ze_result_t zeCommandQueueDestroyEpilogue(ze_command_queue_handle_t, ze_result_t result) override;
                ze_result_t zeModuleCreatePrologue(ze_context_handle_t, ze_device_handle_t, const ze_module_desc_t*, ze_module_handle_t*, ze_module_build_log_handle_t*) override;
                ze_result_t zeModuleCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_module_desc_t*, ze_module_handle_t*, ze_module_build_log_handle_t*, ze_result_t result) override;
                ze_result_t zeModuleDestroyPrologue(ze_module_handle_t) override;
                ze_result_t zeModuleDestroyEpilogue(ze_module_handle_t, ze_result_t result) override;
                ze_result_t zeKernelCreatePrologue(ze_module_handle_t, const ze_kernel_desc_t*, ze_kernel_handle_t*) override;
                ze_result_t zeKernelCreateEpilogue(ze_module_handle_t, const ze_kernel_desc_t*, ze_kernel_handle_t*, ze_result_t result) override;
                ze_result_t zeKernelDestroyPrologue(ze_kernel_handle_t) override;
                ze_result_t zeKernelDestroyEpilogue(ze_kernel_handle_t, ze_result_t result) override;
                ze_result_t zeEventPoolCreatePrologue(ze_context_handle_t, const ze_event_pool_desc_t*, uint32_t, ze_device_handle_t*, ze_event_pool_handle_t*) override;
                ze_result_t zeEventPoolCreateEpilogue(ze_context_handle_t, const ze_event_pool_desc_t*, uint32_t, ze_device_handle_t*, ze_event_pool_handle_t*, ze_result_t result) override;
                ze_result_t zeEventPoolDestroyPrologue(ze_event_pool_handle_t) override;
                ze_result_t zeEventPoolDestroyEpilogue(ze_event_pool_handle_t, ze_result_t result) override;
                ze_result_t zeCommandListCreateImmediatePrologue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t*, ze_command_list_handle_t*) override;
                ze_result_t zeCommandListCreateImmediateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_queue_desc_t*, ze_command_list_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListCreatePrologue(ze_context_handle_t, ze_device_handle_t, const ze_command_list_desc_t*, ze_command_list_handle_t*) override;
                ze_result_t zeCommandListCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_command_list_desc_t*, ze_command_list_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListDestroyPrologue(ze_command_list_handle_t) override;
                ze_result_t zeCommandListDestroyEpilogue(ze_command_list_handle_t, ze_result_t result) override;
                ze_result_t zeEventCreatePrologue(ze_event_pool_handle_t, const ze_event_desc_t *, ze_event_handle_t *) override;
                ze_result_t zeEventCreateEpilogue(ze_event_pool_handle_t, const ze_event_desc_t *, ze_event_handle_t *, ze_result_t result) override;
                ze_result_t zeEventDestroyPrologue(ze_event_handle_t) override;
                ze_result_t zeEventDestroyEpilogue(ze_event_handle_t, ze_result_t result) override;
                ze_result_t zeFenceCreatePrologue(ze_command_queue_handle_t, const ze_fence_desc_t *, ze_fence_handle_t*) override;
                ze_result_t zeFenceCreateEpilogue(ze_command_queue_handle_t, const ze_fence_desc_t *, ze_fence_handle_t*, ze_result_t result) override;
                ze_result_t zeFenceDestroyPrologue(ze_fence_handle_t) override;
                ze_result_t zeFenceDestroyEpilogue(ze_fence_handle_t, ze_result_t result) override;
                ze_result_t zeImageCreatePrologue(ze_context_handle_t, ze_device_handle_t, const ze_image_desc_t*, ze_image_handle_t*) override;
                ze_result_t zeImageCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_image_desc_t*, ze_image_handle_t*, ze_result_t result) override;
                ze_result_t zeImageViewCreateExtPrologue(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView) override;
                ze_result_t zeImageViewCreateExtEpilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t hImage, ze_image_handle_t* phImageView , ze_result_t result) override;
                ze_result_t zeImageDestroyPrologue(ze_image_handle_t) override;
                ze_result_t zeImageDestroyEpilogue(ze_image_handle_t, ze_result_t result) override;
                ze_result_t zeSamplerCreatePrologue(ze_context_handle_t, ze_device_handle_t, const ze_sampler_desc_t*, ze_sampler_handle_t*) override;
                ze_result_t zeSamplerCreateEpilogue(ze_context_handle_t, ze_device_handle_t, const ze_sampler_desc_t*, ze_sampler_handle_t*, ze_result_t result) override;
                ze_result_t zeSamplerDestroyPrologue(ze_sampler_handle_t) override;
                ze_result_t zeSamplerDestroyEpilogue(ze_sampler_handle_t, ze_result_t result) override;
                ze_result_t zeMemAllocDevicePrologue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **) override;
                ze_result_t zeMemAllocDeviceEpilogue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **, ze_result_t result) override;
                ze_result_t zeMemAllocHostPrologue(ze_context_handle_t, const ze_host_mem_alloc_desc_t *, size_t, size_t, void **) override;
                ze_result_t zeMemAllocHostEpilogue(ze_context_handle_t, const ze_host_mem_alloc_desc_t *, size_t, size_t, void **, ze_result_t result) override;
                ze_result_t zeMemAllocSharedPrologue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, const ze_host_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **) override;
                ze_result_t zeMemAllocSharedEpilogue(ze_context_handle_t, const ze_device_mem_alloc_desc_t *, const ze_host_mem_alloc_desc_t *, size_t, size_t, ze_device_handle_t, void **, ze_result_t result) override;
                ze_result_t zeMemFreePrologue(ze_context_handle_t, void *) override;
                ze_result_t zeMemFreeEpilogue(ze_context_handle_t, void *, ze_result_t result) override;
                ze_result_t zeMemFreeExtPrologue(ze_context_handle_t, const ze_memory_free_ext_desc_t*, void *) override;
                ze_result_t zeMemFreeExtEpilogue(ze_context_handle_t, const ze_memory_free_ext_desc_t*, void *, ze_result_t result) override;
                
                // CommandList Append operations - Prologue/Epilogue pairs for memory tracking
                ze_result_t zeCommandListAppendBarrierPrologue(ze_command_list_handle_t, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendBarrierEpilogue(ze_command_list_handle_t, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendMemoryRangesBarrierPrologue(ze_command_list_handle_t, uint32_t, const size_t*, const void**, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendMemoryRangesBarrierEpilogue(ze_command_list_handle_t, uint32_t, const size_t*, const void**, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendMemoryCopyPrologue(ze_command_list_handle_t, void*, const void*, size_t, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendMemoryCopyEpilogue(ze_command_list_handle_t, void*, const void*, size_t, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendMemoryFillPrologue(ze_command_list_handle_t, void*, const void*, size_t, size_t, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendMemoryFillEpilogue(ze_command_list_handle_t, void*, const void*, size_t, size_t, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendMemoryCopyRegionPrologue(ze_command_list_handle_t, void*, const ze_copy_region_t*, uint32_t, uint32_t, const void*, const ze_copy_region_t*, uint32_t, uint32_t, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendMemoryCopyRegionEpilogue(ze_command_list_handle_t, void*, const ze_copy_region_t*, uint32_t, uint32_t, const void*, const ze_copy_region_t*, uint32_t, uint32_t, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendMemoryCopyFromContextPrologue(ze_command_list_handle_t, void*, ze_context_handle_t, const void*, size_t, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendMemoryCopyFromContextEpilogue(ze_command_list_handle_t, void*, ze_context_handle_t, const void*, size_t, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendImageCopyPrologue(ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendImageCopyEpilogue(ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendImageCopyRegionPrologue(ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, const ze_image_region_t*, const ze_image_region_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendImageCopyRegionEpilogue(ze_command_list_handle_t, ze_image_handle_t, ze_image_handle_t, const ze_image_region_t*, const ze_image_region_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendImageCopyToMemoryPrologue(ze_command_list_handle_t, void*, ze_image_handle_t, const ze_image_region_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendImageCopyToMemoryEpilogue(ze_command_list_handle_t, void*, ze_image_handle_t, const ze_image_region_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendImageCopyFromMemoryPrologue(ze_command_list_handle_t, ze_image_handle_t, const void*, const ze_image_region_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendImageCopyFromMemoryEpilogue(ze_command_list_handle_t, ze_image_handle_t, const void*, const ze_image_region_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendMemoryPrefetchPrologue(ze_command_list_handle_t, const void*, size_t) override;
                ze_result_t zeCommandListAppendMemoryPrefetchEpilogue(ze_command_list_handle_t, const void*, size_t, ze_result_t result) override;
                ze_result_t zeCommandListAppendMemAdvisePrologue(ze_command_list_handle_t, ze_device_handle_t, const void*, size_t, ze_memory_advice_t) override;
                ze_result_t zeCommandListAppendMemAdviseEpilogue(ze_command_list_handle_t, ze_device_handle_t, const void*, size_t, ze_memory_advice_t, ze_result_t result) override;
                ze_result_t zeCommandListAppendSignalEventPrologue(ze_command_list_handle_t, ze_event_handle_t) override;
                ze_result_t zeCommandListAppendSignalEventEpilogue(ze_command_list_handle_t, ze_event_handle_t, ze_result_t result) override;
                ze_result_t zeCommandListAppendWaitOnEventsPrologue(ze_command_list_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendWaitOnEventsEpilogue(ze_command_list_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendEventResetPrologue(ze_command_list_handle_t, ze_event_handle_t) override;
                ze_result_t zeCommandListAppendEventResetEpilogue(ze_command_list_handle_t, ze_event_handle_t, ze_result_t result) override;
                ze_result_t zeCommandListAppendQueryKernelTimestampsPrologue(ze_command_list_handle_t, uint32_t, ze_event_handle_t*, void*, const size_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendQueryKernelTimestampsEpilogue(ze_command_list_handle_t, uint32_t, ze_event_handle_t*, void*, const size_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendLaunchKernelPrologue(ze_command_list_handle_t, ze_kernel_handle_t, const ze_group_count_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendLaunchKernelEpilogue(ze_command_list_handle_t, ze_kernel_handle_t, const ze_group_count_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendLaunchCooperativeKernelPrologue(ze_command_list_handle_t, ze_kernel_handle_t, const ze_group_count_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendLaunchCooperativeKernelEpilogue(ze_command_list_handle_t, ze_kernel_handle_t, const ze_group_count_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendLaunchKernelIndirectPrologue(ze_command_list_handle_t, ze_kernel_handle_t, const ze_group_count_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendLaunchKernelIndirectEpilogue(ze_command_list_handle_t, ze_kernel_handle_t, const ze_group_count_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
                ze_result_t zeCommandListAppendWriteGlobalTimestampPrologue(ze_command_list_handle_t, uint64_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*) override;
                ze_result_t zeCommandListAppendWriteGlobalTimestampEpilogue(ze_command_list_handle_t, uint64_t*, ze_event_handle_t, uint32_t, ze_event_handle_t*, ze_result_t result) override;
            };
            class ZESsystem_resource_trackerChecker : public ZESValidationEntryPoints {};
            class ZETsystem_resource_trackerChecker : public ZETValidationEntryPoints {};
        bool enablesystem_resource_tracker = false;
    };
    extern class system_resource_trackerChecker system_resource_tracker_checker;
}