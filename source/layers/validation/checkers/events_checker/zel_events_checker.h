/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_events_checker.h
 *
 */

#pragma once

#include "xla/graphcycles.h"
#include "ze_api.h"
#include "ze_validation_layer.h"

#include <limits>
#include <string>

namespace validation_layer {

constexpr uint32_t invalidDagID = (std::numeric_limits<uint32_t>::max)();
constexpr ze_event_handle_t invalidEventAddress = (std::numeric_limits<ze_event_handle_t>::max)();
using actionAndSignalEvent = std::pair<std::string, ze_event_handle_t>;

class __zedlllocal eventsChecker : public validationChecker {
  public:
    eventsChecker();
    ~eventsChecker();

    class ZEeventsChecker : public ZEValidationEntryPoints {
      public:
        ze_result_t zeEventCreateEpilogue(ze_event_pool_handle_t hEventPool, const ze_event_desc_t *desc, ze_event_handle_t *phEvent) override;
        ze_result_t zeEventDestroyEpilogue(ze_event_handle_t hEvent) override;
        ze_result_t zeCommandListAppendMemoryCopyPrologue(ze_command_list_handle_t hCommandList, void *dstptr, const void *srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendWriteGlobalTimestampPrologue(ze_command_list_handle_t hCommandList, uint64_t *dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendBarrierPrologue(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendMemoryRangesBarrierPrologue(ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t *pRangeSizes, const void **pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendMemoryFillPrologue(ze_command_list_handle_t hCommandList, void *ptr, const void *pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendMemoryCopyRegionPrologue(ze_command_list_handle_t hCommandList, void *dstptr, const ze_copy_region_t *dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void *srcptr, const ze_copy_region_t *srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendMemoryCopyFromContextPrologue(ze_command_list_handle_t hCommandList, void *dstptr, ze_context_handle_t hContextSrc, const void *srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendImageCopyPrologue(ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendImageCopyRegionPrologue(ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, ze_image_handle_t hSrcImage, const ze_image_region_t *pDstRegion, const ze_image_region_t *pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendImageCopyToMemoryPrologue(ze_command_list_handle_t hCommandList, void *dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t *pSrcRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendImageCopyFromMemoryPrologue(ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void *srcptr, const ze_image_region_t *pDstRegion, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendSignalEventPrologue(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) override;
        ze_result_t zeCommandListAppendWaitOnEventsPrologue(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t *phEvents) override;
        ze_result_t zeEventHostSignalPrologue(ze_event_handle_t hEvent) override;
        ze_result_t zeCommandListAppendEventResetPrologue(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) override;
        ze_result_t zeEventHostResetPrologue(ze_event_handle_t hEvent) override;
        ze_result_t zeCommandListAppendQueryKernelTimestampsPrologue(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t *phEvents, void *dstptr, const size_t *pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendLaunchKernelPrologue(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t *pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendLaunchCooperativeKernelPrologue(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t *pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendLaunchKernelIndirectPrologue(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t *pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirectPrologue(ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t *phKernels, const uint32_t *pCountBuffer, const ze_group_count_t *pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListUpdateMutableCommandSignalEventExpPrologue(ze_command_list_handle_t hCommandList, uint64_t commandId, ze_event_handle_t hSignalEvent) override;
        ze_result_t zeCommandListUpdateMutableCommandWaitEventsExpPrologue(ze_command_list_handle_t hCommandList, uint64_t commandId, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendImageCopyToMemoryExtPrologue(ze_command_list_handle_t hCommandList, void *dstptr, ze_image_handle_t hSrcImage, const ze_image_region_t *pSrcRegion, uint32_t destRowPitch, uint32_t destSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListAppendImageCopyFromMemoryExtPrologue(ze_command_list_handle_t hCommandList, ze_image_handle_t hDstImage, const void *srcptr, const ze_image_region_t *pDstRegion, uint32_t srcRowPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;
        ze_result_t zeCommandListImmediateAppendCommandListsExpPrologue(ze_command_list_handle_t hCommandListImmediate, uint32_t numCommandLists, ze_command_list_handle_t *phCommandLists, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t *phWaitEvents) override;

      private:
        // Add node in the DAG and get its ID.
        int addNodeInDag() { return dag.NewNode(); }

        // Add edge in the DAG.
        bool addEdgeInDag(uint32_t x, uint32_t y) { return dag.InsertEdge(x, y); }

        // In case the user uses a single hSignalEvent twice or more, which is an ill usage.
        void validateSignalEventOwnership(const std::string &zeCallDisc, const ze_event_handle_t hSignalEvent);

        // Inserts new actions and events in the DAG based on the ze<API CALLS>.
        void checkForDeadlock(const std::string &zeCallDisc, const ze_event_handle_t hSignalEvent, const uint32_t numWaitEvents, const ze_event_handle_t *phWaitEvents);

        // Reset the event to have an invalid DAG ID such that it can be reused.
        // Useful for zeCalls such as zeCommandListAppendEventReset and zeEventHostReset.
        void resetEventInEventToDagID(const std::string &zeCallDisc, ze_event_handle_t hEvent);

        // The DAG structure.
        xla::GraphCycles dag;

        // events point from/out to a DAG node. This map stores the DAG ID for each event (if there is one).
        std::unordered_map<ze_event_handle_t, uint32_t> eventToDagID;

        // This map acts as a bi-directional map to eventToDagID. It maps DAG ID to a pair containing action description and signal event.
        std::unordered_map<uint32_t, actionAndSignalEvent> dagIDToAction;
    };
    class ZESeventsChecker : public ZESValidationEntryPoints {};
    class ZETeventsChecker : public ZETValidationEntryPoints {};

    bool enableEventsDeadlock = false;
};
extern class eventsChecker eventsDeadlock_checker;
} // namespace validation_layer