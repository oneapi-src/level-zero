<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()
%>/*
 * ***THIS FILE IS GENERATED. ***
 * See timing.h.mako for modifications
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#pragma once
#include "../zel_global_timing_state.h"
#include "${n}_entry_points.h"

namespace validation_layer {
class ${N}timingCheckerGenerated : public ${N}ValidationEntryPoints {
public:
    %for obj in th.extract_objs(specs, r"function"):
    <%
    param_lines = [line for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"])]
    is_void_params = len(param_lines) == 1 and "void" in param_lines[0]
    func_name = th.make_func_name(n, tags, obj)
    %>virtual ze_result_t ${func_name}Prologue( \
%for line in param_lines:
${line} \
%endfor
) override {
        GlobalTimingState::getInstance().recordStart();
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t ${func_name}Epilogue( \
%if not is_void_params:
%for line in param_lines:
${line} \
%endfor
, ${obj['return_type']} result) override {
%else:
${obj['return_type']} result ) override {
%endif
        GlobalTimingState::getInstance().recordEnd("${func_name}");
        return ZE_RESULT_SUCCESS;
    }
    %endfor
%if n == 'ze':
    // Experimental Intel extension for counter-based events
    virtual ze_result_t zexCounterBasedEventCreate2Prologue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* desc, ze_event_handle_t* phEvent ) override {
        GlobalTimingState::getInstance().recordStart();
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zexCounterBasedEventCreate2Epilogue( ze_context_handle_t hContext, ze_device_handle_t hDevice, const void* desc, ze_event_handle_t* phEvent , ze_result_t result) override {
        GlobalTimingState::getInstance().recordEnd("zexCounterBasedEventCreate2");
        return ZE_RESULT_SUCCESS;
    }
%endif
};
} // namespace validation_layer
