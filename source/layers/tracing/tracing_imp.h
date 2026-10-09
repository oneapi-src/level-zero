/*
 * Copyright (C) 2020-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "tracing.h"
#include "ze_api.h"
#include "ze_tracing_cb_structs.h"
#include "loader/ze_loader.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#define UNRECOVERABLE_IF(expression)                             \
                                                                 \
    if (expression) {                                            \
        std::cout << "Abort was called at " << __LINE__          \
                  << " line in file: " << __FILE__ << std::endl; \
        std::abort();                                            \
    }

namespace tracing_layer {

extern thread_local ze_bool_t tracingInProgress;
extern struct APITracerContextImp *pGlobalAPITracerContextImp;

// Keys registration and per-call fan-out by (hDriver, functionName) so a callback
// for one driver never fires for another driver's same-named function.
struct ExtensionFunctionKey {
    ze_driver_handle_t hDriver;
    std::string functionName;
    bool operator<(const ExtensionFunctionKey &rhs) const {
        if (hDriver != rhs.hDriver)
            return hDriver < rhs.hDriver;
        return functionName < rhs.functionName;
    }
};

// A single tracer's prologue/epilogue for one extension function.
struct ExtensionFunctionCallbacks {
    zel_pfnDriverExtensionFunctionCb_t prologue = nullptr;
    zel_pfnDriverExtensionFunctionCb_t epilogue = nullptr;
};

// Loader-owned context echoed back by the driver to the wrapper functions so the
// wrapper can recover which (hDriver, functionName) fired. Lives for process life
// in a tracing-layer registry (addresses must stay stable).
struct LoaderExtensionContext {
    ze_driver_handle_t hDriver;
    std::string functionName;
    // Precomputed here to avoid rebuilding the key (a heap alloc) on every call.
    ExtensionFunctionKey key;
    // True while the driver has the epilogue trampoline. Read lock-free by the
    // prologue wrapper to decide whether to build a per-call instance frame;
    // written under the registry mutex, ordered in ze_tracing.cpp so a concurrent
    // call never builds a frame the driver won't hand back to an epilogue.
    std::atomic<bool> epilogueInstalled{false};
    LoaderExtensionContext(ze_driver_handle_t driver, const char *name)
        : hDriver(driver), functionName(name), key{driver, name} {}
};

typedef struct tracer_array_entry {
    zel_ze_all_callbacks_t corePrologues;
    zel_ze_all_callbacks_t coreEpilogues;
    zel_zer_all_callbacks_t runtimePrologues;
    zel_zer_all_callbacks_t runtimeEpilogues;
    void *pUserData;
    // Per-tracer extension-function callbacks, copied by value into the active
    // tracer array so the lock-free fan-out can walk them.
    std::map<ExtensionFunctionKey, ExtensionFunctionCallbacks> extensionCallbacks;
} tracer_array_entry_t;

typedef struct tracerArray {
    size_t tracerArrayCount;
    tracer_array_entry_t *tracerArrayEntries;
} tracer_array_t;

typedef enum tracingState {
    disabledState,        // tracing has never been enabled
    enabledState,         // tracing is enabled.
    disabledWaitingState, // tracing has been disabled, but not waited for
} tracingState_t;

struct APITracerImp : APITracer {
    ze_result_t destroyTracer(zel_tracer_handle_t phTracer) override;
    ze_result_t setPrologues(zel_core_callbacks_t *pCoreCbs) override;
    ze_result_t setEpilogues(zel_core_callbacks_t *pCoreCbs) override;
    zel_ze_all_callbacks_t& getZeProEpilogues(zel_tracer_reg_t callback_type, ze_result_t& result) override;
    zel_zer_all_callbacks_t &getZerProEpilogues(zel_tracer_reg_t callback_type, ze_result_t &result) override;
    ze_result_t resetAllCallbacks() override;
    ze_result_t enableTracer(ze_bool_t enable) override;

    // Registers/clears one extension-function prologue or epilogue slot for
    // (hDriver, functionName). Only valid while the tracer is disabled.
    ze_result_t registerExtensionCallback(ze_driver_handle_t hDriver,
                                          const char *functionName,
                                          zel_tracer_reg_t callback_type,
                                          zel_pfnDriverExtensionFunctionCb_t pCallback,
                                          int *pPrologueDelta = nullptr,
                                          int *pEpilogueDelta = nullptr) override;

    std::vector<TracerExtensionRegistration>
    snapshotExtensionRegistrations() override;

    tracer_array_entry_t tracerFunctions;
    tracingState_t tracingState;

  private:

    void copyCoreCbsToAllCbs(zel_ze_all_callbacks_t& allCbs, zel_core_callbacks_t& Cbs);
};

class ThreadPrivateTracerData {
  public:
    void clearThreadTracerDataOnList(void) { onList = false; }
    void removeThreadTracerDataFromList(void);
    bool testAndSetThreadTracerDataInitializedAndOnList(void);
    bool onList;
    bool isInitialized;
    ThreadPrivateTracerData();
    ~ThreadPrivateTracerData();

    std::atomic<tracer_array_t *> tracerArrayPointer;

  private:
    ThreadPrivateTracerData(const ThreadPrivateTracerData &);
    ThreadPrivateTracerData &operator=(const ThreadPrivateTracerData &);
};

struct APITracerContextImp : APITracerContext {
  public:
    APITracerContextImp() {
        activeTracerArray.store(&emptyTracerArray, std::memory_order_relaxed);
    };

    ~APITracerContextImp() override;

    static void apiTracingEnable(ze_init_flag_t flag);

    void *getActiveTracersList() override;
    void releaseActivetracersList() override;

    ze_result_t enableTracingImp(struct APITracerImp *newTracer,
                                 ze_bool_t enable);
    ze_result_t finalizeDisableImpTracingWait(struct APITracerImp *oldTracer);

    bool isTracingEnabled();

    void addThreadTracerDataToList(ThreadPrivateTracerData *threadDataP);
    void removeThreadTracerDataFromList(ThreadPrivateTracerData *threadDataP);

  private:
    std::mutex traceTableMutex;
    tracer_array_t emptyTracerArray = {0, NULL};
    std::atomic<tracer_array_t *> activeTracerArray;

    //
    // a list of tracer arrays that were once active, but
    // have been replaced by a new active array.  These
    // once-active tracer arrays may continue for some time
    // to have references to them among the per-thread
    // tracer array pointers.
    //
    std::list<tracer_array_t *> retiringTracerArrayList;

    std::list<struct APITracerImp *> enabledTracerImpList;

    ze_bool_t testForTracerArrayReferences(tracer_array_t *tracerArray);
    size_t testAndFreeRetiredTracers();
    size_t updateTracerArrays();

    std::list<ThreadPrivateTracerData *> threadTracerDataList;
    std::mutex threadTracerDataListMutex;
};

extern thread_local ThreadPrivateTracerData myThreadPrivateTracerData;

template <class T>
class APITracerCallbackStateImp {
  public:
    T current_api_callback;
    void *pUserData;
};

template <class T>
class APITracerCallbackDataImp {
  public:
    T apiOrdinal = nullptr;
    std::vector<tracing_layer::APITracerCallbackStateImp<T>> prologCallbacks;
    std::vector<tracing_layer::APITracerCallbackStateImp<T>> epilogCallbacks;
};

#define ZE_HANDLE_TRACER_RECURSION(ze_api_ptr, ...) \
    do {                                            \
        if (tracing_layer::tracingInProgress) {     \
            return ze_api_ptr(__VA_ARGS__);         \
        }                                           \
        tracing_layer::tracingInProgress = 1;       \
    } while (0)

#define ZE_GEN_TRACER_ARRAY_ENTRY(callbackPtr, tracerArray, tracerArrayIndex, \
                                  callbackType, callbackCategory,             \
                                  callbackFunction)                           \
    do {                                                                      \
        callbackPtr = tracerArray->tracerArrayEntries[tracerArrayIndex]       \
                          .callbackType.callbackCategory.callbackFunction;    \
    } while (0)

#define ZE_GEN_PER_API_CALLBACK_STATE(perApiCallbackData, tracerType,               \
                                      callbackCategory, callbackFunctionType)       \
    tracing_layer::tracer_array_t *currentTracerArray;                              \
    currentTracerArray =                                                            \
        (tracing_layer::tracer_array_t *)                                           \
            tracing_layer::pGlobalAPITracerContextImp->getActiveTracersList();      \
    if (currentTracerArray && currentTracerArray->tracerArrayCount) {           \
        for (size_t i = 0; i < currentTracerArray->tracerArrayCount; i++) {         \
            tracerType prologueCallbackPtr;                                         \
            tracerType epilogue_callback_ptr;                                       \
            ZE_GEN_TRACER_ARRAY_ENTRY(prologueCallbackPtr, currentTracerArray, i,   \
                                      corePrologues, callbackCategory,              \
                                      callbackFunctionType);                        \
            ZE_GEN_TRACER_ARRAY_ENTRY(epilogue_callback_ptr, currentTracerArray, i, \
                                      coreEpilogues, callbackCategory,              \
                                      callbackFunctionType);                        \
                                                                                    \
            tracing_layer::APITracerCallbackStateImp<tracerType> prologCallback;    \
            prologCallback.current_api_callback = prologueCallbackPtr;              \
            prologCallback.pUserData =                                              \
                currentTracerArray->tracerArrayEntries[i].pUserData;                \
            perApiCallbackData.prologCallbacks.push_back(prologCallback);           \
                                                                                    \
            tracing_layer::APITracerCallbackStateImp<tracerType> epilogCallback;    \
            epilogCallback.current_api_callback = epilogue_callback_ptr;            \
            epilogCallback.pUserData =                                              \
                currentTracerArray->tracerArrayEntries[i].pUserData;                \
            perApiCallbackData.epilogCallbacks.push_back(epilogCallback);           \
        }                                                                           \
    }

#define ZER_GEN_PER_API_CALLBACK_STATE(perApiCallbackData, tracerType,               \
                                       callbackCategory, callbackFunctionType)       \
    tracing_layer::tracer_array_t *currentTracerArray;                               \
    currentTracerArray =                                                             \
        (tracing_layer::tracer_array_t *)                                            \
            tracing_layer::pGlobalAPITracerContextImp->getActiveTracersList();       \
    if (currentTracerArray && currentTracerArray->tracerArrayCount) {            \
        for (size_t i = 0; i < currentTracerArray->tracerArrayCount; i++){           \
            tracerType prologueCallbackPtr;                                          \
            tracerType epilogue_callback_ptr;                                        \
            ZE_GEN_TRACER_ARRAY_ENTRY(prologueCallbackPtr, currentTracerArray, i,    \
                                       runtimePrologues, callbackCategory,           \
                                       callbackFunctionType);                        \
            ZE_GEN_TRACER_ARRAY_ENTRY(epilogue_callback_ptr, currentTracerArray, i,  \
                                       runtimeEpilogues, callbackCategory,           \
                                       callbackFunctionType);                        \
                                                                                     \
            tracing_layer::APITracerCallbackStateImp<tracerType> prologCallback;     \
            prologCallback.current_api_callback = prologueCallbackPtr;               \
            prologCallback.pUserData =                                               \
                currentTracerArray->tracerArrayEntries[i].pUserData;                 \
            perApiCallbackData.prologCallbacks.push_back(prologCallback);            \
                                                                                     \
            tracing_layer::APITracerCallbackStateImp<tracerType> epilogCallback;     \
            epilogCallback.current_api_callback = epilogue_callback_ptr;             \
            epilogCallback.pUserData =                                               \
                currentTracerArray->tracerArrayEntries[i].pUserData;                 \
            perApiCallbackData.epilogCallbacks.push_back(epilogCallback);            \
        }                                                                            \
    }

template <typename TRet, typename TFunction_pointer, typename TParams, typename TTracer,
          typename TTracerPrologCallbacks, typename TTracerEpilogCallbacks,
          typename... Args>
TRet
APITracerWrapperImp(TFunction_pointer zeApiPtr, TParams paramsStruct,
                    TTracer apiOrdinal, TTracerPrologCallbacks prologCallbacks,
                    TTracerEpilogCallbacks epilogCallbacks, Args &&...args)
{
    TRet ret {};
    std::vector<APITracerCallbackStateImp<TTracer>> *callbacks_prologs =
        &prologCallbacks;
    std::vector<APITracerCallbackStateImp<TTracer>> *callbacksEpilogs =
        &epilogCallbacks;
    // Fast path: if no callbacks are registered, directly call the API
    if (callbacks_prologs->empty() && callbacksEpilogs->empty()) {
        ret = zeApiPtr(args...);
        tracing_layer::tracingInProgress = 0;
        tracing_layer::pGlobalAPITracerContextImp->releaseActivetracersList();
        return ret;
    }

    std::vector<void *> ppTracerInstanceUserData;
    ppTracerInstanceUserData.resize(callbacks_prologs->size());

    for (size_t i = 0; i < callbacks_prologs->size(); i++) {
        if (callbacks_prologs->at(i).current_api_callback != nullptr)
            callbacks_prologs->at(i).current_api_callback(
                paramsStruct, ret, callbacks_prologs->at(i).pUserData,
                &ppTracerInstanceUserData[i]);
    }
    ret = zeApiPtr(args...);
    for (size_t i = 0; i < callbacksEpilogs->size(); i++) {
        if (callbacksEpilogs->at(i).current_api_callback != nullptr)
            callbacksEpilogs->at(i).current_api_callback(
                paramsStruct, ret, callbacksEpilogs->at(i).pUserData,
                &ppTracerInstanceUserData[i]);
    }
    tracing_layer::tracingInProgress = 0;
    tracing_layer::pGlobalAPITracerContextImp->releaseActivetracersList();
    return ret;
}

// Returns the stable, process-lifetime loader context for (hDriver,
// functionName), creating it on first use. The returned pointer is handed to the
// driver and echoed back to the wrapper functions below.
LoaderExtensionContext *getOrCreateLoaderExtensionContext(ze_driver_handle_t hDriver,
                                                          const char *functionName);

// Result of applying per-phase reference deltas to a (hDriver, functionName)
// install entry: the desired install state for each phase, whether each phase
// just crossed its 0<->1 boundary (so the caller must re-issue the driver setter),
// and the stable loader context to hand the driver.
struct LoaderExtensionInstallState {
    bool wantPrologue;
    bool wantEpilogue;
    bool prologueInstallChanged;
    bool epilogueInstallChanged;
    LoaderExtensionContext *ctx;
};

// Applies prologue/epilogue reference deltas to the install refcounts for
// (hDriver, functionName), counting how many tracers currently hold a live
// callback of each phase. The single shared driver-side wrapper installs a phase
// trampoline on that phase's 0->1 edge and removes it on 1->0. The registry entry
// is never erased, so any in-flight driver call keeps a valid ctx.
LoaderExtensionInstallState updateLoaderExtensionInstall(ze_driver_handle_t hDriver,
                                                         const char *functionName,
                                                         int prologueDelta,
                                                         int epilogueDelta);

// Loader-owned wrappers registered with the driver. The driver calls these from
// the body of the intercepted extension function; pLoaderContext is the
// LoaderExtensionContext* returned by getOrCreateLoaderExtensionContext.
void ZE_APICALL loaderExtensionPrologue(void *pParams, ze_result_t result,
                                        void *pLoaderContext,
                                        void **ppTracerInstanceUserData);
void ZE_APICALL loaderExtensionEpilogue(void *pParams, ze_result_t result,
                                        void *pLoaderContext,
                                        void **ppTracerInstanceUserData);

} // namespace tracing_layer
