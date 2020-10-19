/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "ze_api.h"
#include "layers/zel_tracing_api.h"

struct _zel_tracer_handle_t {};

namespace tracing_layer {

struct APITracer : _zel_tracer_handle_t {
    static APITracer *create();
    virtual ~APITracer() = default;
    static APITracer *fromHandle(zel_tracer_handle_t handle) { return static_cast<APITracer *>(handle); }
    inline zel_tracer_handle_t toHandle() { return this; }
    virtual ze_result_t destroyTracer(zel_tracer_handle_t phTracer) = 0;
    virtual ze_result_t setPrologues(zel_core_callbacks_t *pCoreCbs) = 0;
    virtual ze_result_t setEpilogues(zel_core_callbacks_t *pCoreCbs) = 0;
    virtual ze_result_t enableTracer(ze_bool_t enable) = 0;
};

ze_result_t createAPITracer(const zel_tracer_desc_t *desc, zel_tracer_handle_t *phTracer);

struct APITracerContext {
    virtual ~APITracerContext() = default;
    virtual void *getActiveTracersList() = 0;
    virtual void releaseActivetracersList() = 0;
};

} // namespace tracing_layer
