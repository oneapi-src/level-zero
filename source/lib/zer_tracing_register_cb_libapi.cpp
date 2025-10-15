/*
 *
 * Copyright (C) 2021-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_tracing_register_cb_libapi.cpp
 *
 */

#include "ze_lib.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "layers/zel_tracing_register_cb.h"
#include "zer_api.h"

extern "C" { 

/// APIs to register callbacks for each zer API

ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerGetLastErrorDescriptionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnGetLastErrorDescriptionCb_t pfnGetLastErrorDescriptionCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        zer_pfnGetLastErrorDescriptionCb_t pfnGetLastErrorDescriptionCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerGetLastErrorDescriptionRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetLastErrorDescriptionCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerTranslateDeviceHandleToIdentifierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnTranslateDeviceHandleToIdentifierCb_t pfnTranslateDeviceHandleToIdentifierCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        zer_pfnTranslateDeviceHandleToIdentifierCb_t pfnTranslateDeviceHandleToIdentifierCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerTranslateDeviceHandleToIdentifierRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnTranslateDeviceHandleToIdentifierCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerTranslateIdentifierToDeviceHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnTranslateIdentifierToDeviceHandleCb_t pfnTranslateIdentifierToDeviceHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        zer_pfnTranslateIdentifierToDeviceHandleCb_t pfnTranslateIdentifierToDeviceHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerTranslateIdentifierToDeviceHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnTranslateIdentifierToDeviceHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerGetDefaultContextRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    zer_pfnGetDefaultContextCb_t pfnGetDefaultContextCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        zer_pfnGetDefaultContextCb_t pfnGetDefaultContextCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerGetDefaultContextRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetDefaultContextCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


} //Extern C