<%!
from templates import helper as th
%><%
    n=namespace
    N=n.upper()
%>/*
 * ***THIS FILE IS GENERATED. ***
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}
 *
 */
#pragma once
#include "../zel_global_certification_state.h"
#include "${n}_entry_points.h"

namespace validation_layer {
class ${N}certificationCheckerGenerated : public ${N}ValidationEntryPoints {
public:
%for obj in th.extract_objs(specs, r"function"):
    virtual ze_result_t ${th.make_func_name(n, tags, obj)}Prologue( \
    %for line in th.make_param_lines(n, tags, obj, format=["type", "name", "delim"]):
${line} \
    %endfor
) override {
        if (GlobalCertificationState::getInstance().certification_version < ${th.get_version(obj)}) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        return ZE_RESULT_SUCCESS;
    }
%endfor
};
} // namespace validation_layer
