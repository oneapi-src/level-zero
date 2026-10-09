/*
 * Copyright (C) 2020-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "ze_api.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_register_cb.h"
#include "loader/ze_loader.h"
#include "ze_tracing_cb_structs.h"
#include "zer_tracing_cb_structs.h"

#include <string>
#include <vector>

struct _zel_tracer_handle_t {};

#define TRACING_COMP_NAME "tracing layer"
namespace tracing_layer {

// An extension registration a tracer still holds, used to release its share of
// the driver-side install refcounts on destroy.
struct TracerExtensionRegistration {
    ze_driver_handle_t hDriver;
    std::string functionName;
    bool hasPrologue;
    bool hasEpilogue;
};

struct APITracer : _zel_tracer_handle_t {
    static APITracer *create();
    virtual ~APITracer() = default;
    static APITracer *fromHandle(zel_tracer_handle_t handle) { return static_cast<APITracer *>(handle); }
    inline zel_tracer_handle_t toHandle() { return this; }
    virtual ze_result_t destroyTracer(zel_tracer_handle_t phTracer) = 0;
    virtual ze_result_t setPrologues(zel_core_callbacks_t *pCoreCbs) = 0;
    virtual ze_result_t setEpilogues(zel_core_callbacks_t *pCoreCbs) = 0;
    virtual zel_ze_all_callbacks_t& getZeProEpilogues(zel_tracer_reg_t callback_type, ze_result_t& result) = 0;
    virtual zel_zer_all_callbacks_t& getZerProEpilogues(zel_tracer_reg_t callback_type, ze_result_t& result) = 0;
    virtual ze_result_t resetAllCallbacks() = 0;
    virtual ze_result_t enableTracer(ze_bool_t enable) = 0;
    // Records/clears one prologue or epilogue slot for (hDriver, functionName).
    // pPrologueDelta/pEpilogueDelta (optional) report this tracer's +1/-1/0
    // transition for that slot, for refcounting the driver wrapper.
    virtual ze_result_t registerExtensionCallback(ze_driver_handle_t hDriver,
                                                  const char *functionName,
                                                  zel_tracer_reg_t callback_type,
                                                  zel_pfnDriverExtensionFunctionCb_t pCallback,
                                                  int *pPrologueDelta = nullptr,
                                                  int *pEpilogueDelta = nullptr) = 0;
    // Copy of every extension registration this tracer holds, for releasing its
    // driver-side install refcounts on destroy.
    virtual std::vector<TracerExtensionRegistration>
    snapshotExtensionRegistrations() = 0;
};

ze_result_t createAPITracer(const zel_tracer_desc_t *desc, zel_tracer_handle_t *phTracer);

struct APITracerContext {
    virtual ~APITracerContext() = default;
    virtual void *getActiveTracersList() = 0;
    virtual void releaseActivetracersList() = 0;
};

} // namespace tracing_layer
