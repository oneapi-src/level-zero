/*
 * Copyright (C) 2020-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "tracing_imp.h"

#include <tuple>

namespace tracing_layer {

thread_local ze_bool_t tracingInProgress = 0;

struct APITracerContextImp *pGlobalAPITracerContextImp;

APITracer *APITracer::create() {
    APITracerImp *tracer = new APITracerImp;
    tracer->tracingState = disabledState;
    tracer->tracerFunctions = {};
    UNRECOVERABLE_IF(tracer == nullptr);
    return tracer;
}

ze_result_t createAPITracer(const zel_tracer_desc_t *desc,
                            zel_tracer_handle_t *phTracer) {

    if (!pGlobalAPITracerContextImp->isTracingEnabled()) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    APITracerImp *tracer = static_cast<APITracerImp *>(APITracer::create());

    tracer->tracerFunctions.pUserData = desc->pUserData;

    *phTracer = tracer->toHandle();
    return ZE_RESULT_SUCCESS;
}

// This destructor will be called only during at-exit processing,
// Hence, this function is executing in a single threaded environment,
// and requires no mutex.
APITracerContextImp::~APITracerContextImp() {
    std::list<ThreadPrivateTracerData *>::iterator itr =
        threadTracerDataList.begin();
    while (itr != threadTracerDataList.end()) {
        (*itr)->clearThreadTracerDataOnList();
        itr = threadTracerDataList.erase(itr);
    }
}

ze_result_t APITracerImp::destroyTracer(zel_tracer_handle_t phTracer) {

    APITracerImp *tracer = static_cast<APITracerImp *>(phTracer);

    ze_result_t result =
        pGlobalAPITracerContextImp->finalizeDisableImpTracingWait(tracer);
    if (result == ZE_RESULT_SUCCESS) {
        delete tracing_layer::APITracer::fromHandle(phTracer);
    }
    return result;
}

ze_result_t APITracerImp::setPrologues(zel_core_callbacks_t *pCoreCbs) {

    if (this->tracingState != disabledState) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    copyCoreCbsToAllCbs(this->tracerFunctions.corePrologues, *pCoreCbs);

    return ZE_RESULT_SUCCESS;
}

ze_result_t APITracerImp::setEpilogues(zel_core_callbacks_t *pCoreCbs) {

    if (this->tracingState != disabledState) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    copyCoreCbsToAllCbs(this->tracerFunctions.coreEpilogues, *pCoreCbs);

    return ZE_RESULT_SUCCESS;
}

zel_ze_all_callbacks_t& APITracerImp::getZeProEpilogues(zel_tracer_reg_t callback_type, ze_result_t& result) {

    result = ZE_RESULT_SUCCESS;

    if (this->tracingState != disabledState)
        result = ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if (callback_type == ZEL_REGISTER_PROLOGUE)
        return this->tracerFunctions.corePrologues;
    else
        return this->tracerFunctions.coreEpilogues;
}

zel_zer_all_callbacks_t& APITracerImp::getZerProEpilogues(zel_tracer_reg_t callback_type, ze_result_t &result) {

    result = ZE_RESULT_SUCCESS;

    if (this->tracingState != disabledState)
        result = ZE_RESULT_ERROR_INVALID_ARGUMENT;

    if (callback_type == ZEL_REGISTER_PROLOGUE)
        return this->tracerFunctions.runtimePrologues;
    else
        return this->tracerFunctions.runtimeEpilogues;
}

ze_result_t APITracerImp::resetAllCallbacks() {

    if (this->tracingState != disabledState) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    this->tracerFunctions.corePrologues = {};
    this->tracerFunctions.coreEpilogues = {};
    this->tracerFunctions.runtimePrologues = {};
    this->tracerFunctions.runtimeEpilogues = {};
    this->tracerFunctions.extensionCallbacks.clear();

    return ZE_RESULT_SUCCESS;
}

ze_result_t APITracerImp::enableTracer(ze_bool_t enable) {
    return pGlobalAPITracerContextImp->enableTracingImp(this, enable);
}

ze_result_t APITracerImp::registerExtensionCallback(
    ze_driver_handle_t hDriver, const char *functionName,
    zel_tracer_reg_t callback_type,
    zel_pfnDriverExtensionFunctionCb_t pCallback, int *pPrologueDelta,
    int *pEpilogueDelta) {

    if (pPrologueDelta != nullptr)
        *pPrologueDelta = 0;
    if (pEpilogueDelta != nullptr)
        *pEpilogueDelta = 0;

    // Disabled-only, like the per-API register calls, so the active tracer array
    // is never mutated while in use.
    if (this->tracingState != disabledState)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;

    ExtensionFunctionKey key{hDriver, functionName};
    auto &callbacks = this->tracerFunctions.extensionCallbacks;

    // Before/after presence per phase, so the caller can refcount the shared
    // prologue and epilogue driver wrappers independently.
    auto it = callbacks.find(key);
    const bool hadPrologue = it != callbacks.end() && it->second.prologue != nullptr;
    const bool hadEpilogue = it != callbacks.end() && it->second.epilogue != nullptr;

    auto &entry = callbacks[key];
    if (callback_type == ZEL_REGISTER_PROLOGUE)
        entry.prologue = pCallback;
    else
        entry.epilogue = pCallback;

    const bool hasPrologue = entry.prologue != nullptr;
    const bool hasEpilogue = entry.epilogue != nullptr;

    // Drop fully-cleared entries so the fan-out never carries dead keys.
    if (!hasPrologue && !hasEpilogue)
        callbacks.erase(key);

    if (pPrologueDelta != nullptr)
        *pPrologueDelta = static_cast<int>(hasPrologue) - static_cast<int>(hadPrologue);
    if (pEpilogueDelta != nullptr)
        *pEpilogueDelta = static_cast<int>(hasEpilogue) - static_cast<int>(hadEpilogue);

    return ZE_RESULT_SUCCESS;
}

std::vector<TracerExtensionRegistration>
APITracerImp::snapshotExtensionRegistrations() {
    std::vector<TracerExtensionRegistration> out;
    auto &callbacks = this->tracerFunctions.extensionCallbacks;
    out.reserve(callbacks.size());
    for (auto &kv : callbacks) {
        TracerExtensionRegistration reg;
        reg.hDriver = kv.first.hDriver;
        reg.functionName = kv.first.functionName;
        reg.hasPrologue = kv.second.prologue != nullptr;
        reg.hasEpilogue = kv.second.epilogue != nullptr;
        out.push_back(std::move(reg));
    }
    return out;
}

void APITracerImp::copyCoreCbsToAllCbs(zel_ze_all_callbacks_t& allCbs, zel_core_callbacks_t& cbs) {

    allCbs.Global.pfnInitCb = cbs.Global.pfnInitCb;
    allCbs.Driver.pfnGetCb = cbs.Driver.pfnGetCb;
    allCbs.Driver.pfnGetApiVersionCb = cbs.Driver.pfnGetApiVersionCb;
    allCbs.Driver.pfnGetPropertiesCb = cbs.Driver.pfnGetPropertiesCb;
    allCbs.Driver.pfnGetIpcPropertiesCb = cbs.Driver.pfnGetIpcPropertiesCb;
    allCbs.Driver.pfnGetExtensionPropertiesCb = cbs.Driver.pfnGetExtensionPropertiesCb;
    allCbs.Device.pfnGetCb = cbs.Device.pfnGetCb;
    allCbs.Device.pfnGetSubDevicesCb = cbs.Device.pfnGetSubDevicesCb;
    allCbs.Device.pfnGetPropertiesCb = cbs.Device.pfnGetPropertiesCb;
    allCbs.Device.pfnGetComputePropertiesCb = cbs.Device.pfnGetComputePropertiesCb;
    allCbs.Device.pfnGetModulePropertiesCb = cbs.Device.pfnGetModulePropertiesCb;
    allCbs.Device.pfnGetCommandQueueGroupPropertiesCb = cbs.Device.pfnGetCommandQueueGroupPropertiesCb;
    allCbs.Device.pfnGetMemoryPropertiesCb = cbs.Device.pfnGetMemoryPropertiesCb;
    allCbs.Device.pfnGetMemoryAccessPropertiesCb = cbs.Device.pfnGetMemoryAccessPropertiesCb;
    allCbs.Device.pfnGetCachePropertiesCb = cbs.Device.pfnGetCachePropertiesCb;
    allCbs.Device.pfnGetImagePropertiesCb = cbs.Device.pfnGetImagePropertiesCb;
    allCbs.Device.pfnGetExternalMemoryPropertiesCb = cbs.Device.pfnGetExternalMemoryPropertiesCb;
    allCbs.Device.pfnGetP2PPropertiesCb = cbs.Device.pfnGetP2PPropertiesCb;
    allCbs.Device.pfnCanAccessPeerCb = cbs.Device.pfnCanAccessPeerCb;
    allCbs.Device.pfnGetStatusCb = cbs.Device.pfnGetStatusCb;
    allCbs.Context.pfnCreateCb = cbs.Context.pfnCreateCb;
    allCbs.Context.pfnDestroyCb = cbs.Context.pfnDestroyCb;
    allCbs.Context.pfnGetStatusCb = cbs.Context.pfnGetStatusCb;
    allCbs.Context.pfnSystemBarrierCb = cbs.Context.pfnSystemBarrierCb;
    allCbs.Context.pfnMakeMemoryResidentCb = cbs.Context.pfnMakeMemoryResidentCb;
    allCbs.Context.pfnEvictMemoryCb = cbs.Context.pfnEvictMemoryCb;
    allCbs.Context.pfnMakeImageResidentCb = cbs.Context.pfnMakeImageResidentCb;
    allCbs.Context.pfnEvictImageCb = cbs.Context.pfnEvictImageCb;
    allCbs.CommandQueue.pfnCreateCb = cbs.CommandQueue.pfnCreateCb;
    allCbs.CommandQueue.pfnDestroyCb = cbs.CommandQueue.pfnDestroyCb;
    allCbs.CommandQueue.pfnExecuteCommandListsCb = cbs.CommandQueue.pfnExecuteCommandListsCb;
    allCbs.CommandQueue.pfnSynchronizeCb = cbs.CommandQueue.pfnSynchronizeCb;
    allCbs.CommandList.pfnCreateCb = cbs.CommandList.pfnCreateCb;
    allCbs.CommandList.pfnCreateImmediateCb = cbs.CommandList.pfnCreateImmediateCb;
    allCbs.CommandList.pfnDestroyCb = cbs.CommandList.pfnDestroyCb;
    allCbs.CommandList.pfnCloseCb = cbs.CommandList.pfnCloseCb;
    allCbs.CommandList.pfnResetCb = cbs.CommandList.pfnResetCb;
    allCbs.CommandList.pfnAppendWriteGlobalTimestampCb = cbs.CommandList.pfnAppendWriteGlobalTimestampCb;
    allCbs.CommandList.pfnAppendBarrierCb = cbs.CommandList.pfnAppendBarrierCb;
    allCbs.CommandList.pfnAppendMemoryRangesBarrierCb = cbs.CommandList.pfnAppendMemoryRangesBarrierCb;
    allCbs.CommandList.pfnAppendMemoryCopyCb = cbs.CommandList.pfnAppendMemoryCopyCb;
    allCbs.CommandList.pfnAppendMemoryFillCb = cbs.CommandList.pfnAppendMemoryFillCb;
    allCbs.CommandList.pfnAppendMemoryCopyRegionCb = cbs.CommandList.pfnAppendMemoryCopyRegionCb;
    allCbs.CommandList.pfnAppendMemoryCopyFromContextCb = cbs.CommandList.pfnAppendMemoryCopyFromContextCb;
    allCbs.CommandList.pfnAppendImageCopyCb = cbs.CommandList.pfnAppendImageCopyCb;
    allCbs.CommandList.pfnAppendImageCopyRegionCb = cbs.CommandList.pfnAppendImageCopyRegionCb;
    allCbs.CommandList.pfnAppendImageCopyToMemoryCb = cbs.CommandList.pfnAppendImageCopyToMemoryCb;
    allCbs.CommandList.pfnAppendImageCopyFromMemoryCb = cbs.CommandList.pfnAppendImageCopyFromMemoryCb;
    allCbs.CommandList.pfnAppendMemoryPrefetchCb = cbs.CommandList.pfnAppendMemoryPrefetchCb;
    allCbs.CommandList.pfnAppendMemAdviseCb = cbs.CommandList.pfnAppendMemAdviseCb;
    allCbs.CommandList.pfnAppendSignalEventCb = cbs.CommandList.pfnAppendSignalEventCb;
    allCbs.CommandList.pfnAppendWaitOnEventsCb = cbs.CommandList.pfnAppendWaitOnEventsCb;
    allCbs.CommandList.pfnAppendEventResetCb = cbs.CommandList.pfnAppendEventResetCb;
    allCbs.CommandList.pfnAppendQueryKernelTimestampsCb = cbs.CommandList.pfnAppendQueryKernelTimestampsCb;
    allCbs.CommandList.pfnAppendLaunchKernelCb = cbs.CommandList.pfnAppendLaunchKernelCb;
    allCbs.CommandList.pfnAppendLaunchCooperativeKernelCb = cbs.CommandList.pfnAppendLaunchCooperativeKernelCb;
    allCbs.CommandList.pfnAppendLaunchKernelIndirectCb = cbs.CommandList.pfnAppendLaunchKernelIndirectCb;
    allCbs.CommandList.pfnAppendLaunchMultipleKernelsIndirectCb = cbs.CommandList.pfnAppendLaunchMultipleKernelsIndirectCb;
    allCbs.Fence.pfnCreateCb = cbs.Fence.pfnCreateCb;
    allCbs.Fence.pfnDestroyCb = cbs.Fence.pfnDestroyCb;
    allCbs.Fence.pfnHostSynchronizeCb = cbs.Fence.pfnHostSynchronizeCb;
    allCbs.Fence.pfnQueryStatusCb = cbs.Fence.pfnQueryStatusCb;
    allCbs.Fence.pfnResetCb = cbs.Fence.pfnResetCb;
    allCbs.EventPool.pfnCreateCb = cbs.EventPool.pfnCreateCb;
    allCbs.EventPool.pfnDestroyCb = cbs.EventPool.pfnDestroyCb;
    allCbs.EventPool.pfnGetIpcHandleCb = cbs.EventPool.pfnGetIpcHandleCb;
    allCbs.EventPool.pfnOpenIpcHandleCb = cbs.EventPool.pfnOpenIpcHandleCb;
    allCbs.EventPool.pfnCloseIpcHandleCb = cbs.EventPool.pfnCloseIpcHandleCb;
    allCbs.Event.pfnCreateCb = cbs.Event.pfnCreateCb;
    allCbs.Event.pfnDestroyCb = cbs.Event.pfnDestroyCb;
    allCbs.Event.pfnHostSignalCb = cbs.Event.pfnHostSignalCb;
    allCbs.Event.pfnHostSynchronizeCb = cbs.Event.pfnHostSynchronizeCb;
    allCbs.Event.pfnQueryStatusCb = cbs.Event.pfnQueryStatusCb;
    allCbs.Event.pfnHostResetCb = cbs.Event.pfnHostResetCb;
    allCbs.Event.pfnQueryKernelTimestampCb = cbs.Event.pfnQueryKernelTimestampCb;
    allCbs.Image.pfnGetPropertiesCb = cbs.Image.pfnGetPropertiesCb;
    allCbs.Image.pfnCreateCb = cbs.Image.pfnCreateCb;
    allCbs.Image.pfnDestroyCb = cbs.Image.pfnDestroyCb;
    allCbs.Module.pfnCreateCb = cbs.Module.pfnCreateCb;
    allCbs.Module.pfnDestroyCb = cbs.Module.pfnDestroyCb;
    allCbs.Module.pfnDynamicLinkCb = cbs.Module.pfnDynamicLinkCb;
    allCbs.Module.pfnGetNativeBinaryCb = cbs.Module.pfnGetNativeBinaryCb;
    allCbs.Module.pfnGetGlobalPointerCb = cbs.Module.pfnGetGlobalPointerCb;
    allCbs.Module.pfnGetKernelNamesCb = cbs.Module.pfnGetKernelNamesCb;
    allCbs.Module.pfnGetPropertiesCb = cbs.Module.pfnGetPropertiesCb;
    allCbs.Module.pfnGetFunctionPointerCb = cbs.Module.pfnGetFunctionPointerCb;
    allCbs.ModuleBuildLog.pfnDestroyCb = cbs.ModuleBuildLog.pfnDestroyCb;
    allCbs.ModuleBuildLog.pfnGetStringCb = cbs.ModuleBuildLog.pfnGetStringCb;
    allCbs.Kernel.pfnCreateCb = cbs.Kernel.pfnCreateCb;
    allCbs.Kernel.pfnDestroyCb = cbs.Kernel.pfnDestroyCb;
    allCbs.Kernel.pfnSetCacheConfigCb = cbs.Kernel.pfnSetCacheConfigCb;
    allCbs.Kernel.pfnSetGroupSizeCb = cbs.Kernel.pfnSetGroupSizeCb;
    allCbs.Kernel.pfnSuggestGroupSizeCb = cbs.Kernel.pfnSuggestGroupSizeCb;
    allCbs.Kernel.pfnSuggestMaxCooperativeGroupCountCb = cbs.Kernel.pfnSuggestMaxCooperativeGroupCountCb;
    allCbs.Kernel.pfnSetArgumentValueCb = cbs.Kernel.pfnSetArgumentValueCb;
    allCbs.Kernel.pfnSetIndirectAccessCb = cbs.Kernel.pfnSetIndirectAccessCb;
    allCbs.Kernel.pfnGetIndirectAccessCb = cbs.Kernel.pfnGetIndirectAccessCb;
    allCbs.Kernel.pfnGetSourceAttributesCb = cbs.Kernel.pfnGetSourceAttributesCb;
    allCbs.Kernel.pfnGetPropertiesCb = cbs.Kernel.pfnGetPropertiesCb;
    allCbs.Kernel.pfnGetNameCb = cbs.Kernel.pfnGetNameCb;
    allCbs.Sampler.pfnCreateCb = cbs.Sampler.pfnCreateCb;
    allCbs.Sampler.pfnDestroyCb = cbs.Sampler.pfnDestroyCb;
    allCbs.PhysicalMem.pfnCreateCb = cbs.PhysicalMem.pfnCreateCb;
    allCbs.PhysicalMem.pfnDestroyCb = cbs.PhysicalMem.pfnDestroyCb;
    allCbs.Mem.pfnAllocSharedCb = cbs.Mem.pfnAllocSharedCb;
    allCbs.Mem.pfnAllocDeviceCb = cbs.Mem.pfnAllocDeviceCb;
    allCbs.Mem.pfnAllocHostCb = cbs.Mem.pfnAllocHostCb;
    allCbs.Mem.pfnFreeCb = cbs.Mem.pfnFreeCb;
    allCbs.Mem.pfnGetAllocPropertiesCb = cbs.Mem.pfnGetAllocPropertiesCb;
    allCbs.Mem.pfnGetAddressRangeCb = cbs.Mem.pfnGetAddressRangeCb;
    allCbs.Mem.pfnGetIpcHandleCb = cbs.Mem.pfnGetIpcHandleCb;
    allCbs.Mem.pfnOpenIpcHandleCb = cbs.Mem.pfnOpenIpcHandleCb;
    allCbs.Mem.pfnCloseIpcHandleCb = cbs.Mem.pfnCloseIpcHandleCb;
    allCbs.VirtualMem.pfnReserveCb = cbs.VirtualMem.pfnReserveCb;
    allCbs.VirtualMem.pfnFreeCb = cbs.VirtualMem.pfnFreeCb;
    allCbs.VirtualMem.pfnQueryPageSizeCb = cbs.VirtualMem.pfnQueryPageSizeCb;
    allCbs.VirtualMem.pfnMapCb = cbs.VirtualMem.pfnMapCb;
    allCbs.VirtualMem.pfnUnmapCb = cbs.VirtualMem.pfnUnmapCb;
    allCbs.VirtualMem.pfnSetAccessAttributeCb = cbs.VirtualMem.pfnSetAccessAttributeCb;
    allCbs.VirtualMem.pfnGetAccessAttributeCb = cbs.VirtualMem.pfnGetAccessAttributeCb;

}
    
void APITracerContextImp::addThreadTracerDataToList(
    ThreadPrivateTracerData *threadDataP) {
    std::lock_guard<std::mutex> lock(threadTracerDataListMutex);
    threadTracerDataList.push_back(threadDataP);
}

void APITracerContextImp::removeThreadTracerDataFromList(
    ThreadPrivateTracerData *threadDataP) {
    std::lock_guard<std::mutex> lock(threadTracerDataListMutex);
    if (threadTracerDataList.empty())
        return;
    threadTracerDataList.remove(threadDataP);
}

thread_local ThreadPrivateTracerData myThreadPrivateTracerData;

ThreadPrivateTracerData::ThreadPrivateTracerData() {
    isInitialized = false;
    onList = false;
    tracerArrayPointer.store(nullptr, std::memory_order_relaxed);
}

ThreadPrivateTracerData::~ThreadPrivateTracerData() {
    if (onList) {
        pGlobalAPITracerContextImp->removeThreadTracerDataFromList(this);
        onList = false;
    }
    tracerArrayPointer.store(nullptr, std::memory_order_relaxed);
}

void ThreadPrivateTracerData::removeThreadTracerDataFromList(void) {
    if (onList) {
        pGlobalAPITracerContextImp->removeThreadTracerDataFromList(this);
        onList = false;
    }
    tracerArrayPointer.store(nullptr, std::memory_order_relaxed);
}

bool ThreadPrivateTracerData::testAndSetThreadTracerDataInitializedAndOnList(
    void) {
    if (!isInitialized) {
        isInitialized = true;
        onList = true;
        pGlobalAPITracerContextImp->addThreadTracerDataToList(
            &myThreadPrivateTracerData);
    }
    return onList;
}

// bool APITracerContextImp::isTracingEnabled() { return
// driver_ddiTable.enableTracing; }
bool APITracerContextImp::isTracingEnabled() { return true; }

//
// Walk the list of per-thread private data structures, testing
// whether any of them reference this array.
//
// Return 1 if a reference is found.  Otherwise return 0.
//
ze_bool_t
APITracerContextImp::testForTracerArrayReferences(tracer_array_t *tracerArray) {
    std::lock_guard<std::mutex> lock(threadTracerDataListMutex);
    std::list<ThreadPrivateTracerData *>::iterator itr;
    for (itr = threadTracerDataList.begin(); itr != threadTracerDataList.end();
         itr++) {
        if ((*itr)->tracerArrayPointer.load(std::memory_order_relaxed) ==
            tracerArray)
            return 1;
    }
    return 0;
}

//
// Walk the retiring_tracer_array_list, checking each member of the list for
// references by per thread tracer array pointer. Delete and free
// each tracer array that has no per-thread references.
//
// Return the number of entries on the retiring tracer array list.
//
size_t APITracerContextImp::testAndFreeRetiredTracers() {
    std::list<tracer_array_t *>::iterator itr =
        this->retiringTracerArrayList.begin();
    while (itr != this->retiringTracerArrayList.end()) {
        tracer_array_t *retiringTracerArray = *itr;
        itr++;
        if (testForTracerArrayReferences(retiringTracerArray))
            continue;
        this->retiringTracerArrayList.remove(retiringTracerArray);
        delete[] retiringTracerArray->tracerArrayEntries;
        delete retiringTracerArray;
    }
    return this->retiringTracerArrayList.size();
}

size_t APITracerContextImp::updateTracerArrays() {
    tracer_array_t *newTracerArray;
    size_t newTracerArrayCount = this->enabledTracerImpList.size();

    if (newTracerArrayCount != 0) {

        newTracerArray = new tracer_array_t;

        newTracerArray->tracerArrayCount = newTracerArrayCount;
        newTracerArray->tracerArrayEntries =
            new tracer_array_entry_t[newTracerArrayCount];
        //
        // iterate over the list of enabled tracers, copying their entries into the
        // new tracer array
        //
        size_t i = 0;
        std::list<struct APITracerImp *>::iterator itr;
        for (itr = enabledTracerImpList.begin(); itr != enabledTracerImpList.end();
             itr++) {
            newTracerArray->tracerArrayEntries[i] = (*itr)->tracerFunctions;
            i++;
        }

    } else {
        newTracerArray = &emptyTracerArray;
    }
    //
    // active_tracer_array.load can use memory_order_relaxed here because
    // there is logically no transfer of other memory context between
    // threads in this case.
    //
    tracer_array_t *active_tracer_array_shadow =
        activeTracerArray.load(std::memory_order_relaxed);
    if (active_tracer_array_shadow != &emptyTracerArray) {
        retiringTracerArrayList.push_back(active_tracer_array_shadow);
    }
    //
    // This active_tracer_array.store must use memory_order_release.
    // This store DOES signal a logical transfer of tracer state information
    // from this thread to the tracing threads.
    //
    activeTracerArray.store(newTracerArray, std::memory_order_release);
    return testAndFreeRetiredTracers();
}

ze_result_t
APITracerContextImp::enableTracingImp(struct APITracerImp *tracerImp,
                                      ze_bool_t enable) {
    std::lock_guard<std::mutex> lock(traceTableMutex);
    ze_result_t result;
    switch (tracerImp->tracingState) {
    case disabledState:
        if (enable) {
            enabledTracerImpList.push_back(tracerImp);
            tracerImp->tracingState = enabledState;
            updateTracerArrays();
        }
        result = ZE_RESULT_SUCCESS;
        break;

    case enabledState:
        if (!enable) {
            enabledTracerImpList.remove(tracerImp);
            tracerImp->tracingState = disabledWaitingState;
            if (updateTracerArrays() == 0)
                tracerImp->tracingState = disabledState;
        }
        result = ZE_RESULT_SUCCESS;
        break;

    case disabledWaitingState:
        result = ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
        break;

    default:
        result = ZE_RESULT_ERROR_UNINITIALIZED;
        UNRECOVERABLE_IF(true);
        break;
    }
    return result;
}

// This is called by the destroy tracer method.
//
// This routine will return ZE_RESULT_SUCCESS
// state if either it has never been enabled,
// or if it has been enabled and then disabled.
//
// On ZE_RESULT_SUCESS, the destroy tracer method
// can free the tracer's memory.
//
// ZE_RESULT_ERROR_UNINITIALIZED is returned
// if the tracer has been enabled but not
// disabled.  The destroy tracer method
// should NOT free this tracer's memory.
//
ze_result_t APITracerContextImp::finalizeDisableImpTracingWait(
    struct APITracerImp *tracerImp) {
    std::lock_guard<std::mutex> lock(traceTableMutex);
    ze_result_t result;
    switch (tracerImp->tracingState) {
    case disabledState:
        result = ZE_RESULT_SUCCESS;
        break;

    case enabledState:
        result = ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
        break;

    case disabledWaitingState:
        while (testAndFreeRetiredTracers() != 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        tracerImp->tracingState = disabledState;
        result = ZE_RESULT_SUCCESS;
        break;

    default:
        result = ZE_RESULT_ERROR_UNINITIALIZED;
        UNRECOVERABLE_IF(true);
        break;
    }

    return result;
}

void *APITracerContextImp::getActiveTracersList() {
    tracer_array_t *stableTracerArray = nullptr;

    if (!myThreadPrivateTracerData
             .testAndSetThreadTracerDataInitializedAndOnList()) {
        return nullptr;
    }

    do {
        stableTracerArray = pGlobalAPITracerContextImp->activeTracerArray.load(
            std::memory_order_acquire);
        myThreadPrivateTracerData.tracerArrayPointer.store(
            stableTracerArray, std::memory_order_relaxed);
    } while (stableTracerArray !=
             pGlobalAPITracerContextImp->activeTracerArray.load(
                 std::memory_order_relaxed));
    return (void *)stableTracerArray;
}

void APITracerContextImp::releaseActivetracersList() {
    if (myThreadPrivateTracerData
            .testAndSetThreadTracerDataInitializedAndOnList())
        myThreadPrivateTracerData.tracerArrayPointer.store(
            nullptr, std::memory_order_relaxed);
}

namespace {
// Registry of loader contexts, one per (hDriver, functionName). Entries are
// never erased: the ctx pointer is handed to the driver and must stay valid for
// process life (std::map keeps node addresses stable). Refcounts gate the
// prologue/epilogue driver-wrapper install.
struct LoaderExtensionRegistryEntry {
    LoaderExtensionContext ctx;
    uint32_t prologueRefCount = 0;
    uint32_t epilogueRefCount = 0;
    LoaderExtensionRegistryEntry(ze_driver_handle_t hDriver,
                                 const char *functionName)
        : ctx(hDriver, functionName) {}
};
std::mutex loaderExtensionContextMutex;
std::map<ExtensionFunctionKey, LoaderExtensionRegistryEntry> loaderExtensionContexts;

// Caller must hold loaderExtensionContextMutex.
LoaderExtensionRegistryEntry &
getOrCreateRegistryEntryLocked(const ExtensionFunctionKey &key,
                               ze_driver_handle_t hDriver,
                               const char *functionName) {
    auto it = loaderExtensionContexts.find(key);
    if (it == loaderExtensionContexts.end()) {
        it = loaderExtensionContexts
                 .emplace(std::piecewise_construct,
                          std::forward_as_tuple(key),
                          std::forward_as_tuple(hDriver, functionName))
                 .first;
    }
    return it->second;
}

// Applies a signed delta to an unsigned refcount, clamping at zero.
uint32_t applyRefDelta(uint32_t count, int delta) {
    if (delta > 0)
        return count + static_cast<uint32_t>(delta);
    if (delta < 0) {
        uint32_t dec = static_cast<uint32_t>(-delta);
        return dec > count ? 0u : count - dec;
    }
    return count;
}

// Prologue->epilogue scratch (via the driver's ppTracerInstanceUserData slot):
// a snapshot of each tracer's epilogue + instance data, so the epilogue never
// touches the (possibly retired) active tracer array.
struct ExtensionCallFrame {
    std::vector<APITracerCallbackStateImp<zel_pfnDriverExtensionFunctionCb_t>>
        epilogCallbacks;
    std::vector<void *> instanceUserData;
};
} // namespace

LoaderExtensionContext *
getOrCreateLoaderExtensionContext(ze_driver_handle_t hDriver,
                                  const char *functionName) {
    ExtensionFunctionKey key{hDriver, functionName};
    std::lock_guard<std::mutex> lock(loaderExtensionContextMutex);
    return &getOrCreateRegistryEntryLocked(key, hDriver, functionName).ctx;
}

LoaderExtensionInstallState
updateLoaderExtensionInstall(ze_driver_handle_t hDriver,
                             const char *functionName, int prologueDelta,
                             int epilogueDelta) {
    ExtensionFunctionKey key{hDriver, functionName};
    std::lock_guard<std::mutex> lock(loaderExtensionContextMutex);
    auto &entry = getOrCreateRegistryEntryLocked(key, hDriver, functionName);

    const bool hadPrologue = entry.prologueRefCount > 0;
    const bool hadEpilogue = entry.epilogueRefCount > 0;
    entry.prologueRefCount = applyRefDelta(entry.prologueRefCount, prologueDelta);
    entry.epilogueRefCount = applyRefDelta(entry.epilogueRefCount, epilogueDelta);

    LoaderExtensionInstallState state;
    state.wantPrologue = entry.prologueRefCount > 0;
    state.wantEpilogue = entry.epilogueRefCount > 0;
    state.prologueInstallChanged = state.wantPrologue != hadPrologue;
    state.epilogueInstallChanged = state.wantEpilogue != hadEpilogue;
    state.ctx = &entry.ctx;
    return state;
}

// Runs one phase (prologue or epilogue) inline over the active tracer snapshot
// with a throwaway instance slot. Shared by the prologue-only and epilogue-only
// fast paths (no cross-phase instance data). Acquires/releases the tracer array.
static void runInlineExtensionPhase(
    const ExtensionFunctionKey &key, void *pParams, ze_result_t result,
    zel_pfnDriverExtensionFunctionCb_t ExtensionFunctionCallbacks::*phase) {
    tracer_array_t *currentTracerArray =
        (tracer_array_t *)pGlobalAPITracerContextImp->getActiveTracersList();
    if (currentTracerArray && currentTracerArray->tracerArrayCount) {
        for (size_t i = 0; i < currentTracerArray->tracerArrayCount; i++) {
            auto &tracerEntry = currentTracerArray->tracerArrayEntries[i];
            if (tracerEntry.extensionCallbacks.empty())
                continue;
            auto cbIt = tracerEntry.extensionCallbacks.find(key);
            if (cbIt == tracerEntry.extensionCallbacks.end() ||
                cbIt->second.*phase == nullptr)
                continue;
            void *instanceUserData = nullptr;
            (cbIt->second.*phase)(pParams, result, tracerEntry.pUserData,
                                  &instanceUserData);
        }
    }
    pGlobalAPITracerContextImp->releaseActivetracersList();
}

void ZE_APICALL loaderExtensionPrologue(void *pParams, ze_result_t result,
                                        void *pLoaderContext,
                                        void **ppTracerInstanceUserData) {
    if (ppTracerInstanceUserData != nullptr)
        *ppTracerInstanceUserData = nullptr;
    if (pLoaderContext == nullptr || ppTracerInstanceUserData == nullptr)
        return;

    // Recursion guard, cleared before the driver body runs so the body's own
    // core-API calls stay traceable; the epilogue re-establishes it.
    if (tracingInProgress)
        return;
    tracingInProgress = 1;

    auto *ctx = static_cast<LoaderExtensionContext *>(pLoaderContext);
    const ExtensionFunctionKey &key = ctx->key;

    // Fast path: no epilogue installed, so no instance data to thread -> run
    // prologues inline with no frame allocation.
    if (!ctx->epilogueInstalled.load(std::memory_order_relaxed)) {
        runInlineExtensionPhase(key, pParams, result,
                                &ExtensionFunctionCallbacks::prologue);
        tracingInProgress = 0;
        return;
    }

    // Epilogue installed: build a frame of epilogue snapshots + instance slots
    // for the epilogue wrapper to consume.
    auto *frame = new ExtensionCallFrame();

    tracer_array_t *currentTracerArray =
        (tracer_array_t *)pGlobalAPITracerContextImp->getActiveTracersList();
    if (currentTracerArray && currentTracerArray->tracerArrayCount) {
        const size_t count = currentTracerArray->tracerArrayCount;
        // Reserve so push_back never reallocates: the &instanceUserData.back()
        // slot handed to each prologue must stay valid through the loop.
        frame->epilogCallbacks.reserve(count);
        frame->instanceUserData.reserve(count);
        for (size_t i = 0; i < count; i++) {
            auto &tracerEntry = currentTracerArray->tracerArrayEntries[i];
            if (tracerEntry.extensionCallbacks.empty())
                continue;
            auto cbIt = tracerEntry.extensionCallbacks.find(key);
            if (cbIt == tracerEntry.extensionCallbacks.end())
                continue;
            // Snapshot epilogue + a shared instance slot, then run the prologue
            // into that slot so its value reaches the matching epilogue.
            APITracerCallbackStateImp<zel_pfnDriverExtensionFunctionCb_t> epilog;
            epilog.current_api_callback = cbIt->second.epilogue;
            epilog.pUserData = tracerEntry.pUserData;
            frame->epilogCallbacks.push_back(epilog);
            frame->instanceUserData.push_back(nullptr);
            if (cbIt->second.prologue != nullptr)
                cbIt->second.prologue(pParams, result, tracerEntry.pUserData,
                                      &frame->instanceUserData.back());
        }
    }
    pGlobalAPITracerContextImp->releaseActivetracersList();

    // No participating tracer: drop the frame; a null instance handle no-ops the epilogue.
    if (frame->epilogCallbacks.empty()) {
        delete frame;
        tracingInProgress = 0;
        return;
    }

    *ppTracerInstanceUserData = frame;
    tracingInProgress = 0;
}

void ZE_APICALL loaderExtensionEpilogue(void *pParams, ze_result_t result,
                                        void *pLoaderContext,
                                        void **ppTracerInstanceUserData) {
    if (ppTracerInstanceUserData == nullptr)
        return;

    // Non-null handle: a frame the prologue built -> run its epilogue snapshots
    // and free it.
    auto *frame =
        static_cast<ExtensionCallFrame *>(*ppTracerInstanceUserData);
    if (frame != nullptr) {
        tracingInProgress = 1;
        for (size_t i = 0; i < frame->epilogCallbacks.size(); i++) {
            if (frame->epilogCallbacks[i].current_api_callback != nullptr)
                frame->epilogCallbacks[i].current_api_callback(
                    pParams, result, frame->epilogCallbacks[i].pUserData,
                    &frame->instanceUserData[i]);
        }
        tracingInProgress = 0;

        delete frame;
        *ppTracerInstanceUserData = nullptr;
        return;
    }

    // No frame (epilogue-only, or no participants): self-gather epilogues with a
    // fresh instance slot.
    if (pLoaderContext == nullptr)
        return;
    if (tracingInProgress)
        return;
    tracingInProgress = 1;

    auto *ctx = static_cast<LoaderExtensionContext *>(pLoaderContext);
    runInlineExtensionPhase(ctx->key, pParams, result,
                            &ExtensionFunctionCallbacks::epilogue);
    tracingInProgress = 0;
}

} // namespace tracing_layer
