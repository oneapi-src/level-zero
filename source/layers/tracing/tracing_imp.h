/*
 * Copyright (C) 2020-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "tracing.h"
#include "ze_api.h"
#include "ze_tracing_cb_structs.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <list>
#include <mutex>
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

typedef struct tracer_array_entry {
    zel_all_core_callbacks_t corePrologues;
    zel_all_core_callbacks_t coreEpilogues;
    void *pUserData;
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
    zel_all_core_callbacks_t& getProEpilogues(zel_tracer_reg_t callback_type, ze_result_t& result) override;
    ze_result_t resetAllCallbacks() override;
    ze_result_t enableTracer(ze_bool_t enable) override;

    tracer_array_entry_t tracerFunctions;
    tracingState_t tracingState;

  private:

    void copyCoreCbsToAllCbs(zel_all_core_callbacks_t& allCbs, zel_core_callbacks_t& Cbs);
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
    if (currentTracerArray) {                                                       \
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

template <typename TFunction_pointer, typename TParams, typename TTracer,
          typename TTracerPrologCallbacks, typename TTracerEpilogCallbacks,
          typename... Args>
ze_result_t
APITracerWrapperImp(TFunction_pointer zeApiPtr, TParams paramsStruct,
                    TTracer apiOrdinal, TTracerPrologCallbacks prologCallbacks,
                    TTracerEpilogCallbacks epilogCallbacks, Args &&... args) {
    ze_result_t ret = ZE_RESULT_SUCCESS;
    std::vector<APITracerCallbackStateImp<TTracer>> *callbacks_prologs =
        &prologCallbacks;

    std::vector<void *> ppTracerInstanceUserData;
    ppTracerInstanceUserData.resize(callbacks_prologs->size());

    for (size_t i = 0; i < callbacks_prologs->size(); i++) {
        if (callbacks_prologs->at(i).current_api_callback != nullptr)
            callbacks_prologs->at(i).current_api_callback(
                paramsStruct, ret, callbacks_prologs->at(i).pUserData,
                &ppTracerInstanceUserData[i]);
    }
    ret = zeApiPtr(args...);
    std::vector<APITracerCallbackStateImp<TTracer>> *callbacksEpilogs =
        &epilogCallbacks;
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

} // namespace tracing_layer
