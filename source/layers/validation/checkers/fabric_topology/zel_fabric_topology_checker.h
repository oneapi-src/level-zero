/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_fabric_topology_checker.h
 *
 */

#pragma once

#include <string>
#include "ze_api.h"
#include "ze_validation_layer.h"

namespace validation_layer
{
    // Fabric Topology checker.
    //
    // Records, per process, a JSON Lines event stream describing:
    //   - the device / sub-device / fabric topology visible to the process
    //     (fabric vertices + edges, P2P access matrix, PCI addresses),
    //   - the data movement the workload issues through Level Zero copy/fill
    //     commands, attributed to (executing device, source location,
    //     destination location),
    //   - IPC memory export/import events with join keys so that streams
    //     from several processes can be stitched together to show which
    //     processes / devices communicate.
    //
    // The streams are merged and visualized with scripts/fabric_topology_viewer.py.
    class __zedlllocal fabricTopologyChecker : public validationChecker {
    public:
        fabricTopologyChecker();
        ~fabricTopologyChecker();
        fabricTopologyChecker(const fabricTopologyChecker &) = delete;
        fabricTopologyChecker &operator=(const fabricTopologyChecker &) = delete;

        class ZEfabricTopologyChecker : public ZEValidationEntryPoints {
        public:
            // Topology discovery: populated once the loader completes zeInitDrivers / zeDriverGet
            ze_result_t zeInitDriversEpilogue(uint32_t *pCount, ze_driver_handle_t *phDrivers, ze_init_driver_type_desc_t *desc, ze_result_t result) override;
            ze_result_t zeDriverGetEpilogue(uint32_t *pCount, ze_driver_handle_t *phDrivers, ze_result_t result) override;
            ze_result_t zeDeviceGetEpilogue(ze_driver_handle_t hDriver, uint32_t *pCount, ze_device_handle_t *phDevices, ze_result_t result) override;

            // Memory ownership tracking
            ze_result_t zeMemAllocDeviceEpilogue(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t *device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void **pptr, ze_result_t result) override;
            ze_result_t zeMemAllocHostEpilogue(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, void **pptr, ze_result_t result) override;
            ze_result_t zeMemAllocSharedEpilogue(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t *device_desc, const ze_host_mem_alloc_desc_t *host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void **pptr, ze_result_t result) override;
            ze_result_t zeMemFreeEpilogue(ze_context_handle_t hContext, void *ptr, ze_result_t result) override;
            ze_result_t zeMemFreeExtEpilogue(ze_context_handle_t hContext, const ze_memory_free_ext_desc_t *pMemFreeDesc, void *ptr, ze_result_t result) override;

            // IPC (cross-process) memory sharing
            ze_result_t zeMemGetIpcHandleEpilogue(ze_context_handle_t hContext, const void *ptr, ze_ipc_mem_handle_t *pIpcHandle, ze_result_t result) override;
            ze_result_t zeMemGetIpcHandleWithPropertiesEpilogue(ze_context_handle_t hContext, const void *ptr, void *pNext, ze_ipc_mem_handle_t *pIpcHandle, ze_result_t result) override;
            ze_result_t zeMemOpenIpcHandleEpilogue(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void **pptr, ze_result_t result) override;
            ze_result_t zeMemCloseIpcHandleEpilogue(ze_context_handle_t hContext, const void *ptr, ze_result_t result) override;

            // Command list bookkeeping
            ze_result_t zeCommandListCreateEpilogue(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t *desc, ze_command_list_handle_t *phCommandList, ze_result_t result) override;
            ze_result_t zeCommandListCreateImmediateEpilogue(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t *altdesc, ze_command_list_handle_t *phCommandList, ze_result_t result) override;
            ze_result_t zeCommandListCreateCloneExpEpilogue(ze_command_list_handle_t hCommandList, ze_command_list_handle_t *phClonedCommandList, ze_result_t result) override;
            ze_result_t zeCommandListDestroyEpilogue(ze_command_list_handle_t hCommandList, ze_result_t result) override;
            ze_result_t zeCommandListResetEpilogue(ze_command_list_handle_t hCommandList, ze_result_t result) override;

            // Data movement
            ze_result_t zeCommandListAppendMemoryCopyEpilogue(ze_command_list_handle_t hCommandList, void *dstptr, const void *srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents, ze_result_t result) override;
            ze_result_t zeCommandListAppendMemoryCopyRegionEpilogue(ze_command_list_handle_t hCommandList, void *dstptr, const ze_copy_region_t *dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void *srcptr, const ze_copy_region_t *srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents, ze_result_t result) override;
            ze_result_t zeCommandListAppendMemoryCopyFromContextEpilogue(ze_command_list_handle_t hCommandList, void *dstptr, ze_context_handle_t hContextSrc, const void *srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents, ze_result_t result) override;
            ze_result_t zeCommandListAppendMemoryFillEpilogue(ze_command_list_handle_t hCommandList, void *ptr, const void *pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents, ze_result_t result) override;

            // Submission of regular command lists
            ze_result_t zeCommandQueueExecuteCommandListsEpilogue(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_fence_handle_t hFence, ze_result_t result) override;
            ze_result_t zeCommandListImmediateAppendCommandListsExpEpilogue(ze_command_list_handle_t hCommandListImmediate, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents, ze_result_t result) override;
        };
        class ZESfabricTopologyChecker : public ZESValidationEntryPoints {};
        class ZETfabricTopologyChecker : public ZETValidationEntryPoints {};
        class ZERfabricTopologyChecker : public ZERValidationEntryPoints {};

        bool enableFabricTopology = false;
    };
    extern class fabricTopologyChecker fabric_topology_checker;
} // namespace validation_layer
