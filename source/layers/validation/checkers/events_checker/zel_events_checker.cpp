/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_events_checker.cpp
 *
 */
#include "zel_events_checker.h"

#include <iostream>
#include <sstream>

namespace validation_layer {
class eventsChecker events_checker;

eventsChecker::eventsChecker() {

    enableEvents = getenv_tobool("ZEL_ENABLE_EVENTS_CHECKER");
    if (enableEvents) {
        eventsChecker::ZEeventsChecker *zeChecker = new eventsChecker::ZEeventsChecker;
        eventsChecker::ZESeventsChecker *zesChecker = new eventsChecker::ZESeventsChecker;
        eventsChecker::ZETeventsChecker *zetChecker = new eventsChecker::ZETeventsChecker;
        events_checker.zeValidation = zeChecker;
        events_checker.zesValidation = zesChecker;
        events_checker.zetValidation = zetChecker;

        validation_layer::context.validationHandlers.push_back(&events_checker);
    }
}

eventsChecker::~eventsChecker() {
    if (enableEvents) {
        delete events_checker.zeValidation;
        delete events_checker.zesValidation;
        delete events_checker.zetValidation;
    }
}

ze_result_t eventsChecker::ZEeventsChecker::zeEventCreateEpilogue(
    ze_event_pool_handle_t hEventPool,  ///< [in] handle of the event pool
    const ze_event_desc_t *desc,        ///< [in] pointer to event descriptor
    ze_event_handle_t *phEvent,         ///< [out] pointer to handle of event object created
    ze_result_t result
) {
    if(result != ZE_RESULT_SUCCESS) {
        return ZE_RESULT_SUCCESS;
    }
    eventToDagID[*phEvent] = invalidDagID;

    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeEventDestroyEpilogue(
    ze_event_handle_t hEvent, ///< [in][release] handle of event object to destroy
    ze_result_t result
) {
    if(result != ZE_RESULT_SUCCESS) {
        return ZE_RESULT_SUCCESS;
    }

    if (eventToDagID.find(hEvent) != eventToDagID.end()) {
        // Delete event from eventToDagID but not from the dagIDToAction map as it may be needed for printing the discription of the action when printing path in the DAG.
        eventToDagID.erase(hEvent);
    }

    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendMemoryCopyPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    void *dstptr,                          ///< [in] pointer to destination memory to copy to
    const void *srcptr,                    ///< [in] pointer to source memory to copy from
    size_t size,                           ///< [in] size in bytes to copy
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendMemoryCopy", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendWriteGlobalTimestampPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    uint64_t *dstptr,                      ///< [in,out] pointer to memory where timestamp value will be written; must
                                           ///< be 8byte-aligned.
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before executing query;
                                           ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before executing query
) {
    checkForDeadlock("zeCommandListAppendWriteGlobalTimestamp", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendBarrierPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before executing barrier;
                                           ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before executing barrier
) {
    checkForDeadlock("zeCommandListAppendBarrier", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendMemoryRangesBarrierPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    uint32_t numRanges,                    ///< [in] number of memory ranges
    const size_t *pRangeSizes,             ///< [in][range(0, numRanges)] array of sizes of memory range
    const void **pRanges,                  ///< [in][range(0, numRanges)] array of memory ranges
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before executing barrier;
                                           ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before executing barrier
) {
    checkForDeadlock("zeCommandListAppendMemoryRangesBarrier", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendMemoryFillPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    void *ptr,                             ///< [in] pointer to memory to initialize
    const void *pattern,                   ///< [in] pointer to value to initialize memory to
    size_t pattern_size,                   ///< [in] size in bytes of the value to initialize memory to
    size_t size,                           ///< [in] size in bytes to initialize
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendMemoryFill", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendMemoryCopyRegionPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    void *dstptr,                          ///< [in] pointer to destination memory to copy to
    const ze_copy_region_t *dstRegion,     ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                     ///< [in] destination pitch in bytes
    uint32_t dstSlicePitch,                ///< [in] destination slice pitch in bytes. This is required for 3D region
                                           ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                           ///< otherwise it's ignored.
    const void *srcptr,                    ///< [in] pointer to source memory to copy from
    const ze_copy_region_t *srcRegion,     ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                     ///< [in] source pitch in bytes
    uint32_t srcSlicePitch,                ///< [in] source slice pitch in bytes. This is required for 3D region
                                           ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                           ///< otherwise it's ignored.
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendMemoryCopyRegion", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendMemoryCopyFromContextPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    void *dstptr,                          ///< [in] pointer to destination memory to copy to
    ze_context_handle_t hContextSrc,       ///< [in] handle of source context object
    const void *srcptr,                    ///< [in] pointer to source memory to copy from
    size_t size,                           ///< [in] size in bytes to copy
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendMemoryCopyFromContext", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendImageCopyPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    ze_image_handle_t hDstImage,           ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,           ///< [in] handle of source image to copy from
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendImageCopy", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendImageCopyRegionPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    ze_image_handle_t hDstImage,           ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,           ///< [in] handle of source image to copy from
    const ze_image_region_t *pDstRegion,   ///< [in][optional] destination region descriptor
    const ze_image_region_t *pSrcRegion,   ///< [in][optional] source region descriptor
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendImageCopyRegion", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendImageCopyToMemoryPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    void *dstptr,                          ///< [in] pointer to destination memory to copy to
    ze_image_handle_t hSrcImage,           ///< [in] handle of source image to copy from
    const ze_image_region_t *pSrcRegion,   ///< [in][optional] source region descriptor
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendImageCopyToMemory", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendImageCopyFromMemoryPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    ze_image_handle_t hDstImage,           ///< [in] handle of destination image to copy to
    const void *srcptr,                    ///< [in] pointer to source memory to copy from
    const ze_image_region_t *pDstRegion,   ///< [in][optional] destination region descriptor
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendImageCopyFromMemory", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendSignalEventPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    ze_event_handle_t hEvent               ///< [in] handle of the event
) {
    checkForDeadlock("zeCommandListAppendSignalEvent", hEvent, 0, nullptr);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendWaitOnEventsPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    uint32_t numEvents,                    ///< [in] number of events to wait on before continuing
    ze_event_handle_t *phEvents            ///< [in][range(0, numEvents)] handles of the events to wait on before
                                           ///< continuing
) {
    checkForDeadlock("zeCommandListAppendWaitOnEvents", nullptr, numEvents, phEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeEventHostSignalPrologue(
    ze_event_handle_t hEvent ///< [in] handle of the event
) {
    checkForDeadlock("zeEventHostSignal", hEvent, 0, nullptr);
    return ZE_RESULT_SUCCESS;
}

void eventsChecker::ZEeventsChecker::resetEventInEventToDagID(
    const std::string &zeCallDisc, /// action discription
    const ze_event_handle_t hEvent ///< [in] handle of the event
) {
    auto it = eventToDagID.find(hEvent);
    // Check if user is using invalid events, hint if it doesn't exist in eventToDagID.
    if (it == eventToDagID.end()) {
        std::cerr << "Warning: hSignalEvent {" << hEvent << "} might be an invalid event in call to " << zeCallDisc << std::endl;
        return;
    }

    if (it->second != invalidDagID) {

        auto action = dagIDToAction.find(it->second);
        if (action != dagIDToAction.end()) {
            action->second.second = invalidEventAddress; // Reset
        }

        it->second = invalidDagID; // Reset
    }
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendEventResetPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    ze_event_handle_t hEvent               ///< [in] handle of the event
) {
    resetEventInEventToDagID("zeCommandListAppendEventReset", hEvent);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeEventHostResetPrologue(
    ze_event_handle_t hEvent ///< [in] handle of the event
) {
    resetEventInEventToDagID("zeEventHostReset", hEvent);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendQueryKernelTimestampsPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    uint32_t numEvents,                    ///< [in] the number of timestamp events to query
    ze_event_handle_t *phEvents,           ///< [in][range(0, numEvents)] handles of timestamp events to query
    void *dstptr,                          ///< [in,out] pointer to memory where ::ze_kernel_timestamp_result_t will
                                           ///< be written; must be size-aligned.
    const size_t *pOffsets,                ///< [in][optional][range(0, numEvents)] offset, in bytes, to write
                                           ///< results; address must be 4byte-aligned and offsets must be
                                           ///< size-aligned.
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before executing query;
                                           ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before executing query
) {
    checkForDeadlock("zeCommandListAppendQueryKernelTimestamps", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendLaunchKernelPrologue(
    ze_command_list_handle_t hCommandList,   ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,              ///< [in] handle of the kernel object
    const ze_group_count_t *pLaunchFuncArgs, ///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,          ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                  ///< [in][optional] number of events to wait on before launching; must be 0
                                             ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents          ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                             ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendLaunchKernel", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendLaunchCooperativeKernelPrologue(
    ze_command_list_handle_t hCommandList,   ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,              ///< [in] handle of the kernel object
    const ze_group_count_t *pLaunchFuncArgs, ///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,          ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                  ///< [in][optional] number of events to wait on before launching; must be 0
                                             ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents          ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                             ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendLaunchCooperativeKernel", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendLaunchKernelIndirectPrologue(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t *pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                    ///< arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendLaunchKernelIndirect", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendLaunchMultipleKernelsIndirectPrologue(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
    ze_kernel_handle_t *phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
    const uint32_t *pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of kernels to launch; value must be less than or equal to
                                                    ///< numKernels
    const ze_group_count_t *pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                    ///< a contiguous array of thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendLaunchMultipleKernelsIndirect", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListUpdateMutableCommandSignalEventExpPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    uint64_t commandId,                    ///< [in] command identifier
    ze_event_handle_t hSignalEvent         ///< [in][optional] handle of the event to signal on completion
) {
    checkForDeadlock("zeCommandListUpdateMutableCommandSignalEventExp", hSignalEvent, 0, nullptr);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListUpdateMutableCommandWaitEventsExpPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of the command list
    uint64_t commandId,                    ///< [in] command identifier
    uint32_t numWaitEvents,                ///< [in][optional] the number of wait events
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListUpdateMutableCommandWaitEventsExp", nullptr, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendImageCopyToMemoryExtPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    void *dstptr,                          ///< [in] pointer to destination memory to copy to
    ze_image_handle_t hSrcImage,           ///< [in] handle of source image to copy from
    const ze_image_region_t *pSrcRegion,   ///< [in][optional] source region descriptor
    uint32_t destRowPitch,                 ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                           ///< image or each image of a 1D or 2D image array being written
    uint32_t destSlicePitch,               ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                           ///< each image of a 1D or 2D image array being written
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendImageCopyToMemoryExt", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListAppendImageCopyFromMemoryExtPrologue(
    ze_command_list_handle_t hCommandList, ///< [in] handle of command list
    ze_image_handle_t hDstImage,           ///< [in] handle of destination image to copy to
    const void *srcptr,                    ///< [in] pointer to source memory to copy from
    const ze_image_region_t *pDstRegion,   ///< [in][optional] destination region descriptor
    uint32_t srcRowPitch,                  ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                           ///< image or each image of a 1D or 2D image array being read
    uint32_t srcSlicePitch,                ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                           ///< each image of a 1D or 2D image array being read
    ze_event_handle_t hSignalEvent,        ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                ///< [in][optional] number of events to wait on before launching; must be 0
                                           ///< if `nullptr == phWaitEvents`
    ze_event_handle_t *phWaitEvents        ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                           ///< on before launching
) {
    checkForDeadlock("zeCommandListAppendImageCopyFromMemoryExt", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

ze_result_t
eventsChecker::ZEeventsChecker::zeCommandListImmediateAppendCommandListsExpPrologue(
    ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
    uint32_t numCommandLists,                       ///< [in] number of command lists
    ze_command_list_handle_t *phCommandLists,       ///< [in][range(0, numCommandLists)] handles of command lists
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
                                                    ///<    - if not null, this event is signaled after the completion of all
                                                    ///< appended command lists
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing appended
                                                    ///< command lists; must be 0 if nullptr == phWaitEvents
    ze_event_handle_t *phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing appended command lists.
                                                    ///<    - if not null, all wait events must be satisfied prior to the start
                                                    ///< of any appended command list(s)
) {
    checkForDeadlock("zeCommandListImmediateAppendCommandListsExp", hSignalEvent, numWaitEvents, phWaitEvents);
    return ZE_RESULT_SUCCESS;
}

void eventsChecker::ZEeventsChecker::validateSignalEventOwnership(const std::string &zeCallDisc,
                                                                  const ze_event_handle_t hSignalEvent) {
    const auto it = eventToDagID.find(hSignalEvent);
    if (it != eventToDagID.end() && it->second != invalidDagID) {
        const auto actionIt = dagIDToAction.find(it->second);
        if (actionIt != dagIDToAction.end()) {
            const std::string previousActionOwner = actionIt->second.first;
            std::cerr << "Warning: " << zeCallDisc << " is using the same ze_event_handle_t for signal {" << hSignalEvent << "} which has been previously used by: " << previousActionOwner << std::endl;
        }
    }
}

void eventsChecker::ZEeventsChecker::checkForDeadlock(
    const std::string &zeCallDisc,        /// action discription
    const ze_event_handle_t hSignalEvent, ///< [in][optional] handle of the event to forming the outgoing edge in the DAG
    const uint32_t numWaitEvents,         ///< [in][optional] number of events that point to this action.
    const ze_event_handle_t *phWaitEvents ///< [in][optional][range(0, numWaitEvents)] handle of the events that point to this action.
) {

    uint32_t this_action_new_node_id = invalidDagID;

    if (hSignalEvent != nullptr) {

        auto it = eventToDagID.find(hSignalEvent);
        // Check if user is using invalid events, hint if it doesn't exist in eventToDagID.
        if (it == eventToDagID.end()) {
            std::cerr << "Warning: hSignalEvent {" << hSignalEvent << "} might be an invalid event in call to " << zeCallDisc << std::endl;
            return;
        }

        // A passive check to see if the user is using the same event for multiple actions.
        // It only print warnings and does not stop the event deadlock checker.
        validateSignalEventOwnership(zeCallDisc, hSignalEvent);

        if (it->second != invalidDagID) {
            // This event already exists in the DAG. Get the DAG node ID.
            // For example when there is indeed a deadlock it would have already been created.
            this_action_new_node_id = it->second;
        }
    }

    for (uint32_t i = 0; i < numWaitEvents; i++) {
        if (eventToDagID.find(phWaitEvents[i]) == eventToDagID.end()) {
            std::cerr << "Warning: phWaitEvents {" << hSignalEvent << "} might be an invalid event in call to " << zeCallDisc << std::endl;
            return;
        }
    }

    if (this_action_new_node_id == invalidDagID) {
        // Create node in DAG
        this_action_new_node_id = addNodeInDag();

        // Now we know where the hSignalEvent points from/out in the DAG. Update the eventToDagID map.
        eventToDagID[hSignalEvent] = this_action_new_node_id;
    }

    // Add this action to the actionToDagID map.
    std::ostringstream oss;
    oss << zeCallDisc << ": (hSignalEvent{" << hSignalEvent << "}, phWaitEvents{";

    for (uint32_t i = 0; i < numWaitEvents; i++) {
        oss << phWaitEvents[i];
        if (i < numWaitEvents - 1) {
            oss << ", ";
        }
    }
    oss << "})";

    std::string action = oss.str(); // Convert the stream to a string.
    dagIDToAction[this_action_new_node_id] = actionAndSignalEvent(action, hSignalEvent);

    // Form the dependency in the DAG
    for (uint32_t i = 0; i < numWaitEvents; i++) {
        auto it = eventToDagID.find(phWaitEvents[i]);
        if (it == eventToDagID.end()) {
            std::cerr << "Warning: phWaitEvents {" << phWaitEvents[i] << "} might be an invalid event in call to " << zeCallDisc << std::endl;
            return;
        }
        uint32_t dagID = it->second;
        if (dagID == invalidDagID) {
            // Create a new node in the DAG for this wait event. That action will be created some time in the future.
            dagID = addNodeInDag();
            it->second = dagID;
        }

        auto getActionDetails = [&](int dagID) -> std::string {
            auto actionIt = dagIDToAction.find(dagID);
            return (actionIt != dagIDToAction.end()) ? actionIt->second.first : "PLACEHOLDER";
        };

        if (!addEdgeInDag(dagID, this_action_new_node_id)) {
            std::string fromAction = getActionDetails(dagID);
            std::string toAction = getActionDetails(this_action_new_node_id);

            std::cerr << "Warning: There may be a potential event deadlock!\n";
            std::cerr << "Adding the following dependency would create a cycle in the DAG:\n\tFrom: " << fromAction << "\n\tTo: " << toAction << "\n";
            std::cerr << "There is already a path:\n";

            constexpr uint32_t maxPathLength = 15;
            auto path = dag.PathDagIDs(this_action_new_node_id, dagID, maxPathLength);
            auto dagIDsInPath = path.first;
            std::cerr << getActionDetails(dagIDsInPath[0]) << "\n";
            std::string spacePrefix = "";
            for (uint32_t j = 1; j < dagIDsInPath.size(); j++) {
                std::cerr << spacePrefix << "|\n"
                          << spacePrefix << "-> " << getActionDetails(dagIDsInPath[j]) << "\n";
                spacePrefix += "   ";
            }
            if (path.second) {
                std::cerr << spacePrefix << "|\n"
                          << spacePrefix << "-> ...\n";
            }
        }
    }
}

} // namespace validation_layer
