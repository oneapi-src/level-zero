/*
 *
 * Copyright (C) 2021-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_tracing_register_cb.h
 *
 */

#include "tracing.h"
#include "ze_tracing_layer.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "layers/zel_tracing_register_cb.h"
#include "zer_api.h"

extern "C" { 

/// APIs to register callbacks for each zer API

ZE_DLLEXPORT ze_result_t ZE_APICALL
zelTracerGetLastErrorDescriptionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnGetLastErrorDescriptionCb_t pfnGetLastErrorDescriptionCb
    ) {

    ze_result_t result;
    auto& cbs = tracing_layer::APITracer::fromHandle(hTracer)->getZerProEpilogues(callback_type, result);
    if (result == ZE_RESULT_SUCCESS)
        cbs.Global.pfnGetLastErrorDescriptionCb = pfnGetLastErrorDescriptionCb;

    return result;
}


ZE_DLLEXPORT ze_result_t ZE_APICALL
zelTracerTranslateDeviceHandleToIdentifierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnTranslateDeviceHandleToIdentifierCb_t pfnTranslateDeviceHandleToIdentifierCb
    ) {

    ze_result_t result;
    auto& cbs = tracing_layer::APITracer::fromHandle(hTracer)->getZerProEpilogues(callback_type, result);
    if (result == ZE_RESULT_SUCCESS)
        cbs.Global.pfnTranslateDeviceHandleToIdentifierCb = pfnTranslateDeviceHandleToIdentifierCb;

    return result;
}


ZE_DLLEXPORT ze_result_t ZE_APICALL
zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnTranslateIdentifierToDeviceHandleCb_t pfnTranslateIdentifierToDeviceHandleCb
    ) {

    ze_result_t result;
    auto& cbs = tracing_layer::APITracer::fromHandle(hTracer)->getZerProEpilogues(callback_type, result);
    if (result == ZE_RESULT_SUCCESS)
        cbs.Global.pfnTranslateIdentifierToDeviceHandleCb = pfnTranslateIdentifierToDeviceHandleCb;

    return result;
}


ZE_DLLEXPORT ze_result_t ZE_APICALL
zelTracerGetDefaultContextRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnGetDefaultContextCb_t pfnGetDefaultContextCb
    ) {

    ze_result_t result;
    auto& cbs = tracing_layer::APITracer::fromHandle(hTracer)->getZerProEpilogues(callback_type, result);
    if (result == ZE_RESULT_SUCCESS)
        cbs.Global.pfnGetDefaultContextCb = pfnGetDefaultContextCb;

    return result;
}



} //extern C