/*
 *
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_tracing_register_cb_libapi.cpp
 *
 */

#include "ze_lib.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "layers/zel_tracing_register_cb.h"
#include "ze_api.h"

extern "C" { 

/// APIs to register callbacks for each core API

ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerInitRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnInitCb_t pfnInitCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnInitCb_t pfnInitCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerInitRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnInitCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetCb_t pfnGetCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverGetCb_t pfnGetCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverGetRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetApiVersionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetApiVersionCb_t pfnGetApiVersionCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverGetApiVersionCb_t pfnGetApiVersionCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverGetApiVersionRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetApiVersionCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetPropertiesCb_t pfnGetPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverGetPropertiesCb_t pfnGetPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverGetPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetIpcPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetIpcPropertiesCb_t pfnGetIpcPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverGetIpcPropertiesCb_t pfnGetIpcPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverGetIpcPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetIpcPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetExtensionPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetExtensionPropertiesCb_t pfnGetExtensionPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverGetExtensionPropertiesCb_t pfnGetExtensionPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverGetExtensionPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetExtensionPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetExtensionFunctionAddressRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetExtensionFunctionAddressCb_t pfnGetExtensionFunctionAddressCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverGetExtensionFunctionAddressCb_t pfnGetExtensionFunctionAddressCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverGetExtensionFunctionAddressRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetExtensionFunctionAddressCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverGetLastErrorDescriptionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverGetLastErrorDescriptionCb_t pfnGetLastErrorDescriptionCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverGetLastErrorDescriptionCb_t pfnGetLastErrorDescriptionCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverGetLastErrorDescriptionRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetLastErrorDescriptionCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetCb_t pfnGetCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetCb_t pfnGetCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetRootDeviceRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetRootDeviceCb_t pfnGetRootDeviceCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetRootDeviceCb_t pfnGetRootDeviceCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetRootDeviceRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetRootDeviceCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetSubDevicesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetSubDevicesCb_t pfnGetSubDevicesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetSubDevicesCb_t pfnGetSubDevicesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetSubDevicesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetSubDevicesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetPropertiesCb_t pfnGetPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetPropertiesCb_t pfnGetPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetComputePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetComputePropertiesCb_t pfnGetComputePropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetComputePropertiesCb_t pfnGetComputePropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetComputePropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetComputePropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetModulePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetModulePropertiesCb_t pfnGetModulePropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetModulePropertiesCb_t pfnGetModulePropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetModulePropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetModulePropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetCommandQueueGroupPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t pfnGetCommandQueueGroupPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t pfnGetCommandQueueGroupPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetCommandQueueGroupPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetCommandQueueGroupPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetMemoryPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetMemoryPropertiesCb_t pfnGetMemoryPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetMemoryPropertiesCb_t pfnGetMemoryPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetMemoryPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetMemoryPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetMemoryAccessPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetMemoryAccessPropertiesCb_t pfnGetMemoryAccessPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetMemoryAccessPropertiesCb_t pfnGetMemoryAccessPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetMemoryAccessPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetMemoryAccessPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetCachePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetCachePropertiesCb_t pfnGetCachePropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetCachePropertiesCb_t pfnGetCachePropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetCachePropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetCachePropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetImagePropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetImagePropertiesCb_t pfnGetImagePropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetImagePropertiesCb_t pfnGetImagePropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetImagePropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetImagePropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetExternalMemoryPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetExternalMemoryPropertiesCb_t pfnGetExternalMemoryPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetExternalMemoryPropertiesCb_t pfnGetExternalMemoryPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetExternalMemoryPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetExternalMemoryPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetP2PPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetP2PPropertiesCb_t pfnGetP2PPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetP2PPropertiesCb_t pfnGetP2PPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetP2PPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetP2PPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceCanAccessPeerRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceCanAccessPeerCb_t pfnCanAccessPeerCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceCanAccessPeerCb_t pfnCanAccessPeerCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceCanAccessPeerRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCanAccessPeerCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetStatusCb_t pfnGetStatusCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetStatusCb_t pfnGetStatusCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetStatusRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetStatusCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetGlobalTimestampsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetGlobalTimestampsCb_t pfnGetGlobalTimestampsCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetGlobalTimestampsCb_t pfnGetGlobalTimestampsCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetGlobalTimestampsRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetGlobalTimestampsCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextCreateExRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextCreateExCb_t pfnCreateExCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextCreateExCb_t pfnCreateExCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextCreateExRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateExCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextGetStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextGetStatusCb_t pfnGetStatusCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextGetStatusCb_t pfnGetStatusCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextGetStatusRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetStatusCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandQueueCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandQueueCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandQueueDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandQueueDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueExecuteCommandListsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueExecuteCommandListsCb_t pfnExecuteCommandListsCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandQueueExecuteCommandListsCb_t pfnExecuteCommandListsCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandQueueExecuteCommandListsRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnExecuteCommandListsCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandQueueSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandQueueSynchronizeCb_t pfnSynchronizeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandQueueSynchronizeCb_t pfnSynchronizeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandQueueSynchronizeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSynchronizeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListCreateImmediateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListCreateImmediateCb_t pfnCreateImmediateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListCreateImmediateCb_t pfnCreateImmediateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListCreateImmediateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateImmediateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListCloseRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListCloseCb_t pfnCloseCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListCloseCb_t pfnCloseCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListCloseRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCloseCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListResetCb_t pfnResetCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListResetCb_t pfnResetCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListResetRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnResetCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendWriteGlobalTimestampRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendWriteGlobalTimestampCb_t pfnAppendWriteGlobalTimestampCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendWriteGlobalTimestampCb_t pfnAppendWriteGlobalTimestampCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendWriteGlobalTimestampRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendWriteGlobalTimestampCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListHostSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListHostSynchronizeCb_t pfnHostSynchronizeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListHostSynchronizeCb_t pfnHostSynchronizeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListHostSynchronizeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnHostSynchronizeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendBarrierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendBarrierCb_t pfnAppendBarrierCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendBarrierCb_t pfnAppendBarrierCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendBarrierRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendBarrierCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryRangesBarrierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryRangesBarrierCb_t pfnAppendMemoryRangesBarrierCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendMemoryRangesBarrierCb_t pfnAppendMemoryRangesBarrierCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendMemoryRangesBarrierRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendMemoryRangesBarrierCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextSystemBarrierRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextSystemBarrierCb_t pfnSystemBarrierCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextSystemBarrierCb_t pfnSystemBarrierCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextSystemBarrierRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSystemBarrierCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryCopyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryCopyCb_t pfnAppendMemoryCopyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendMemoryCopyCb_t pfnAppendMemoryCopyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendMemoryCopyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendMemoryCopyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryFillRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryFillCb_t pfnAppendMemoryFillCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendMemoryFillCb_t pfnAppendMemoryFillCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendMemoryFillRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendMemoryFillCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryCopyRegionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryCopyRegionCb_t pfnAppendMemoryCopyRegionCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendMemoryCopyRegionCb_t pfnAppendMemoryCopyRegionCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendMemoryCopyRegionRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendMemoryCopyRegionCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryCopyFromContextRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryCopyFromContextCb_t pfnAppendMemoryCopyFromContextCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendMemoryCopyFromContextCb_t pfnAppendMemoryCopyFromContextCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendMemoryCopyFromContextRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendMemoryCopyFromContextCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyCb_t pfnAppendImageCopyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendImageCopyCb_t pfnAppendImageCopyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendImageCopyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendImageCopyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyRegionRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyRegionCb_t pfnAppendImageCopyRegionCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendImageCopyRegionCb_t pfnAppendImageCopyRegionCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendImageCopyRegionRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendImageCopyRegionCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyToMemoryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyToMemoryCb_t pfnAppendImageCopyToMemoryCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendImageCopyToMemoryCb_t pfnAppendImageCopyToMemoryCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendImageCopyToMemoryRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendImageCopyToMemoryCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyFromMemoryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyFromMemoryCb_t pfnAppendImageCopyFromMemoryCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendImageCopyFromMemoryCb_t pfnAppendImageCopyFromMemoryCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendImageCopyFromMemoryRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendImageCopyFromMemoryCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemoryPrefetchRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemoryPrefetchCb_t pfnAppendMemoryPrefetchCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendMemoryPrefetchCb_t pfnAppendMemoryPrefetchCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendMemoryPrefetchRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendMemoryPrefetchCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendMemAdviseRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendMemAdviseCb_t pfnAppendMemAdviseCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendMemAdviseCb_t pfnAppendMemAdviseCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendMemAdviseRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendMemAdviseCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventPoolCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventPoolCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventPoolDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventPoolDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolGetIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolGetIpcHandleCb_t pfnGetIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventPoolGetIpcHandleCb_t pfnGetIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventPoolGetIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolPutIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolPutIpcHandleCb_t pfnPutIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventPoolPutIpcHandleCb_t pfnPutIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventPoolPutIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnPutIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolOpenIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolOpenIpcHandleCb_t pfnOpenIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventPoolOpenIpcHandleCb_t pfnOpenIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventPoolOpenIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnOpenIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventPoolCloseIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventPoolCloseIpcHandleCb_t pfnCloseIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventPoolCloseIpcHandleCb_t pfnCloseIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventPoolCloseIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCloseIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendSignalEventRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendSignalEventCb_t pfnAppendSignalEventCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendSignalEventCb_t pfnAppendSignalEventCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendSignalEventRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendSignalEventCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendWaitOnEventsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendWaitOnEventsCb_t pfnAppendWaitOnEventsCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendWaitOnEventsCb_t pfnAppendWaitOnEventsCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendWaitOnEventsRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendWaitOnEventsCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventHostSignalRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventHostSignalCb_t pfnHostSignalCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventHostSignalCb_t pfnHostSignalCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventHostSignalRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnHostSignalCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventHostSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventHostSynchronizeCb_t pfnHostSynchronizeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventHostSynchronizeCb_t pfnHostSynchronizeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventHostSynchronizeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnHostSynchronizeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryStatusCb_t pfnQueryStatusCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventQueryStatusCb_t pfnQueryStatusCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventQueryStatusRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnQueryStatusCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendEventResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendEventResetCb_t pfnAppendEventResetCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendEventResetCb_t pfnAppendEventResetCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendEventResetRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendEventResetCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventHostResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventHostResetCb_t pfnHostResetCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventHostResetCb_t pfnHostResetCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventHostResetRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnHostResetCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryKernelTimestampRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryKernelTimestampCb_t pfnQueryKernelTimestampCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventQueryKernelTimestampCb_t pfnQueryKernelTimestampCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventQueryKernelTimestampRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnQueryKernelTimestampCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendQueryKernelTimestampsRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendQueryKernelTimestampsCb_t pfnAppendQueryKernelTimestampsCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendQueryKernelTimestampsCb_t pfnAppendQueryKernelTimestampsCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendQueryKernelTimestampsRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendQueryKernelTimestampsCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFenceCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFenceCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFenceDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFenceDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceHostSynchronizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceHostSynchronizeCb_t pfnHostSynchronizeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFenceHostSynchronizeCb_t pfnHostSynchronizeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFenceHostSynchronizeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnHostSynchronizeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceQueryStatusRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceQueryStatusCb_t pfnQueryStatusCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFenceQueryStatusCb_t pfnQueryStatusCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFenceQueryStatusRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnQueryStatusCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFenceResetRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFenceResetCb_t pfnResetCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFenceResetCb_t pfnResetCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFenceResetRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnResetCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageGetPropertiesCb_t pfnGetPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnImageGetPropertiesCb_t pfnGetPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerImageGetPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnImageCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerImageCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnImageDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerImageDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemAllocSharedRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemAllocSharedCb_t pfnAllocSharedCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemAllocSharedCb_t pfnAllocSharedCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemAllocSharedRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAllocSharedCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemAllocDeviceRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemAllocDeviceCb_t pfnAllocDeviceCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemAllocDeviceCb_t pfnAllocDeviceCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemAllocDeviceRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAllocDeviceCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemAllocHostRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemAllocHostCb_t pfnAllocHostCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemAllocHostCb_t pfnAllocHostCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemAllocHostRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAllocHostCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemFreeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemFreeCb_t pfnFreeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemFreeCb_t pfnFreeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemFreeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnFreeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetAllocPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetAllocPropertiesCb_t pfnGetAllocPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemGetAllocPropertiesCb_t pfnGetAllocPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemGetAllocPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetAllocPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetAddressRangeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetAddressRangeCb_t pfnGetAddressRangeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemGetAddressRangeCb_t pfnGetAddressRangeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemGetAddressRangeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetAddressRangeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetIpcHandleCb_t pfnGetIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemGetIpcHandleCb_t pfnGetIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemGetIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetIpcHandleFromFileDescriptorExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetIpcHandleFromFileDescriptorExpCb_t pfnGetIpcHandleFromFileDescriptorExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemGetIpcHandleFromFileDescriptorExpCb_t pfnGetIpcHandleFromFileDescriptorExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemGetIpcHandleFromFileDescriptorExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetIpcHandleFromFileDescriptorExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetFileDescriptorFromIpcHandleExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetFileDescriptorFromIpcHandleExpCb_t pfnGetFileDescriptorFromIpcHandleExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemGetFileDescriptorFromIpcHandleExpCb_t pfnGetFileDescriptorFromIpcHandleExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemGetFileDescriptorFromIpcHandleExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetFileDescriptorFromIpcHandleExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemPutIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemPutIpcHandleCb_t pfnPutIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemPutIpcHandleCb_t pfnPutIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemPutIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnPutIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemOpenIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemOpenIpcHandleCb_t pfnOpenIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemOpenIpcHandleCb_t pfnOpenIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemOpenIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnOpenIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemCloseIpcHandleRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemCloseIpcHandleCb_t pfnCloseIpcHandleCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemCloseIpcHandleCb_t pfnCloseIpcHandleCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemCloseIpcHandleRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCloseIpcHandleCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemSetAtomicAccessAttributeExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemSetAtomicAccessAttributeExpCb_t pfnSetAtomicAccessAttributeExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemSetAtomicAccessAttributeExpCb_t pfnSetAtomicAccessAttributeExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemSetAtomicAccessAttributeExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetAtomicAccessAttributeExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemGetAtomicAccessAttributeExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemGetAtomicAccessAttributeExpCb_t pfnGetAtomicAccessAttributeExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemGetAtomicAccessAttributeExpCb_t pfnGetAtomicAccessAttributeExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemGetAtomicAccessAttributeExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetAtomicAccessAttributeExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleDynamicLinkRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleDynamicLinkCb_t pfnDynamicLinkCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleDynamicLinkCb_t pfnDynamicLinkCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleDynamicLinkRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDynamicLinkCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleBuildLogDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleBuildLogDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleBuildLogDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleBuildLogDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleBuildLogGetStringRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleBuildLogGetStringCb_t pfnGetStringCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleBuildLogGetStringCb_t pfnGetStringCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleBuildLogGetStringRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetStringCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetNativeBinaryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetNativeBinaryCb_t pfnGetNativeBinaryCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleGetNativeBinaryCb_t pfnGetNativeBinaryCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleGetNativeBinaryRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetNativeBinaryCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetGlobalPointerRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetGlobalPointerCb_t pfnGetGlobalPointerCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleGetGlobalPointerCb_t pfnGetGlobalPointerCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleGetGlobalPointerRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetGlobalPointerCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetKernelNamesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetKernelNamesCb_t pfnGetKernelNamesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleGetKernelNamesCb_t pfnGetKernelNamesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleGetKernelNamesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetKernelNamesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetPropertiesCb_t pfnGetPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleGetPropertiesCb_t pfnGetPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleGetPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleGetFunctionPointerRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleGetFunctionPointerCb_t pfnGetFunctionPointerCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleGetFunctionPointerCb_t pfnGetFunctionPointerCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleGetFunctionPointerRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetFunctionPointerCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetGroupSizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetGroupSizeCb_t pfnSetGroupSizeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSetGroupSizeCb_t pfnSetGroupSizeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSetGroupSizeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetGroupSizeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSuggestGroupSizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSuggestGroupSizeCb_t pfnSuggestGroupSizeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSuggestGroupSizeCb_t pfnSuggestGroupSizeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSuggestGroupSizeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSuggestGroupSizeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSuggestMaxCooperativeGroupCountRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t pfnSuggestMaxCooperativeGroupCountCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t pfnSuggestMaxCooperativeGroupCountCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSuggestMaxCooperativeGroupCountRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSuggestMaxCooperativeGroupCountCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetArgumentValueRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetArgumentValueCb_t pfnSetArgumentValueCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSetArgumentValueCb_t pfnSetArgumentValueCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSetArgumentValueRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetArgumentValueCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetIndirectAccessRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetIndirectAccessCb_t pfnSetIndirectAccessCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSetIndirectAccessCb_t pfnSetIndirectAccessCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSetIndirectAccessRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetIndirectAccessCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetIndirectAccessRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetIndirectAccessCb_t pfnGetIndirectAccessCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelGetIndirectAccessCb_t pfnGetIndirectAccessCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelGetIndirectAccessRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetIndirectAccessCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetSourceAttributesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetSourceAttributesCb_t pfnGetSourceAttributesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelGetSourceAttributesCb_t pfnGetSourceAttributesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelGetSourceAttributesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetSourceAttributesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetCacheConfigRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetCacheConfigCb_t pfnSetCacheConfigCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSetCacheConfigCb_t pfnSetCacheConfigCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSetCacheConfigRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetCacheConfigCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetPropertiesRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetPropertiesCb_t pfnGetPropertiesCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelGetPropertiesCb_t pfnGetPropertiesCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelGetPropertiesRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelGetNameRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelGetNameCb_t pfnGetNameCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelGetNameCb_t pfnGetNameCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelGetNameRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetNameCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchKernelRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchKernelCb_t pfnAppendLaunchKernelCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendLaunchKernelCb_t pfnAppendLaunchKernelCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendLaunchKernelRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendLaunchKernelCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchCooperativeKernelRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchCooperativeKernelCb_t pfnAppendLaunchCooperativeKernelCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendLaunchCooperativeKernelCb_t pfnAppendLaunchCooperativeKernelCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendLaunchCooperativeKernelRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendLaunchCooperativeKernelCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchKernelIndirectRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchKernelIndirectCb_t pfnAppendLaunchKernelIndirectCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendLaunchKernelIndirectCb_t pfnAppendLaunchKernelIndirectCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendLaunchKernelIndirectRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendLaunchKernelIndirectCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendLaunchMultipleKernelsIndirectRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t pfnAppendLaunchMultipleKernelsIndirectCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t pfnAppendLaunchMultipleKernelsIndirectCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendLaunchMultipleKernelsIndirectRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendLaunchMultipleKernelsIndirectCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextMakeMemoryResidentRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextMakeMemoryResidentCb_t pfnMakeMemoryResidentCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextMakeMemoryResidentCb_t pfnMakeMemoryResidentCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextMakeMemoryResidentRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnMakeMemoryResidentCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextEvictMemoryRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextEvictMemoryCb_t pfnEvictMemoryCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextEvictMemoryCb_t pfnEvictMemoryCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextEvictMemoryRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnEvictMemoryCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextMakeImageResidentRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextMakeImageResidentCb_t pfnMakeImageResidentCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextMakeImageResidentCb_t pfnMakeImageResidentCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextMakeImageResidentRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnMakeImageResidentCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerContextEvictImageRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnContextEvictImageCb_t pfnEvictImageCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnContextEvictImageCb_t pfnEvictImageCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerContextEvictImageRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnEvictImageCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerSamplerCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnSamplerCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnSamplerCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerSamplerCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerSamplerDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnSamplerDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnSamplerDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerSamplerDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemReserveRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemReserveCb_t pfnReserveCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnVirtualMemReserveCb_t pfnReserveCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerVirtualMemReserveRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnReserveCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemFreeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemFreeCb_t pfnFreeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnVirtualMemFreeCb_t pfnFreeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerVirtualMemFreeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnFreeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemQueryPageSizeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemQueryPageSizeCb_t pfnQueryPageSizeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnVirtualMemQueryPageSizeCb_t pfnQueryPageSizeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerVirtualMemQueryPageSizeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnQueryPageSizeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerPhysicalMemCreateRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnPhysicalMemCreateCb_t pfnCreateCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnPhysicalMemCreateCb_t pfnCreateCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerPhysicalMemCreateRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerPhysicalMemDestroyRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnPhysicalMemDestroyCb_t pfnDestroyCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnPhysicalMemDestroyCb_t pfnDestroyCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerPhysicalMemDestroyRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemMapRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemMapCb_t pfnMapCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnVirtualMemMapCb_t pfnMapCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerVirtualMemMapRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnMapCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemUnmapRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemUnmapCb_t pfnUnmapCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnVirtualMemUnmapCb_t pfnUnmapCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerVirtualMemUnmapRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnUnmapCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemSetAccessAttributeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemSetAccessAttributeCb_t pfnSetAccessAttributeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnVirtualMemSetAccessAttributeCb_t pfnSetAccessAttributeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerVirtualMemSetAccessAttributeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetAccessAttributeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerVirtualMemGetAccessAttributeRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnVirtualMemGetAccessAttributeCb_t pfnGetAccessAttributeCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnVirtualMemGetAccessAttributeCb_t pfnGetAccessAttributeCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerVirtualMemGetAccessAttributeRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetAccessAttributeCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSetGlobalOffsetExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSetGlobalOffsetExpCb_t pfnSetGlobalOffsetExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSetGlobalOffsetExpCb_t pfnSetGlobalOffsetExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSetGlobalOffsetExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetGlobalOffsetExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceReserveCacheExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceReserveCacheExtCb_t pfnReserveCacheExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceReserveCacheExtCb_t pfnReserveCacheExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceReserveCacheExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnReserveCacheExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceSetCacheAdviceExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceSetCacheAdviceExtCb_t pfnSetCacheAdviceExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceSetCacheAdviceExtCb_t pfnSetCacheAdviceExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceSetCacheAdviceExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSetCacheAdviceExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryTimestampsExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryTimestampsExpCb_t pfnQueryTimestampsExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventQueryTimestampsExpCb_t pfnQueryTimestampsExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventQueryTimestampsExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnQueryTimestampsExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageGetMemoryPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageGetMemoryPropertiesExpCb_t pfnGetMemoryPropertiesExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnImageGetMemoryPropertiesExpCb_t pfnGetMemoryPropertiesExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerImageGetMemoryPropertiesExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetMemoryPropertiesExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageViewCreateExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageViewCreateExtCb_t pfnViewCreateExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnImageViewCreateExtCb_t pfnViewCreateExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerImageViewCreateExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnViewCreateExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageViewCreateExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageViewCreateExpCb_t pfnViewCreateExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnImageViewCreateExpCb_t pfnViewCreateExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerImageViewCreateExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnViewCreateExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerKernelSchedulingHintExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnKernelSchedulingHintExpCb_t pfnSchedulingHintExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnKernelSchedulingHintExpCb_t pfnSchedulingHintExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerKernelSchedulingHintExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnSchedulingHintExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDevicePciGetPropertiesExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDevicePciGetPropertiesExtCb_t pfnPciGetPropertiesExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDevicePciGetPropertiesExtCb_t pfnPciGetPropertiesExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDevicePciGetPropertiesExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnPciGetPropertiesExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyToMemoryExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyToMemoryExtCb_t pfnAppendImageCopyToMemoryExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendImageCopyToMemoryExtCb_t pfnAppendImageCopyToMemoryExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendImageCopyToMemoryExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendImageCopyToMemoryExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCommandListAppendImageCopyFromMemoryExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnCommandListAppendImageCopyFromMemoryExtCb_t pfnAppendImageCopyFromMemoryExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnCommandListAppendImageCopyFromMemoryExtCb_t pfnAppendImageCopyFromMemoryExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerCommandListAppendImageCopyFromMemoryExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnAppendImageCopyFromMemoryExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerImageGetAllocPropertiesExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnImageGetAllocPropertiesExtCb_t pfnGetAllocPropertiesExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnImageGetAllocPropertiesExtCb_t pfnGetAllocPropertiesExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerImageGetAllocPropertiesExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetAllocPropertiesExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerModuleInspectLinkageExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnModuleInspectLinkageExtCb_t pfnInspectLinkageExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnModuleInspectLinkageExtCb_t pfnInspectLinkageExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerModuleInspectLinkageExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnInspectLinkageExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerMemFreeExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnMemFreeExtCb_t pfnFreeExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnMemFreeExtCb_t pfnFreeExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerMemFreeExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnFreeExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetExpCb_t pfnGetExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFabricVertexGetExpCb_t pfnGetExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFabricVertexGetExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetSubVerticesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetSubVerticesExpCb_t pfnGetSubVerticesExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFabricVertexGetSubVerticesExpCb_t pfnGetSubVerticesExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFabricVertexGetSubVerticesExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetSubVerticesExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetPropertiesExpCb_t pfnGetPropertiesExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFabricVertexGetPropertiesExpCb_t pfnGetPropertiesExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFabricVertexGetPropertiesExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricVertexGetDeviceExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricVertexGetDeviceExpCb_t pfnGetDeviceExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFabricVertexGetDeviceExpCb_t pfnGetDeviceExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFabricVertexGetDeviceExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetDeviceExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDeviceGetFabricVertexExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDeviceGetFabricVertexExpCb_t pfnGetFabricVertexExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDeviceGetFabricVertexExpCb_t pfnGetFabricVertexExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDeviceGetFabricVertexExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetFabricVertexExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricEdgeGetExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricEdgeGetExpCb_t pfnGetExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFabricEdgeGetExpCb_t pfnGetExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFabricEdgeGetExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricEdgeGetVerticesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricEdgeGetVerticesExpCb_t pfnGetVerticesExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFabricEdgeGetVerticesExpCb_t pfnGetVerticesExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFabricEdgeGetVerticesExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetVerticesExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerFabricEdgeGetPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnFabricEdgeGetPropertiesExpCb_t pfnGetPropertiesExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnFabricEdgeGetPropertiesExpCb_t pfnGetPropertiesExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerFabricEdgeGetPropertiesExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerEventQueryKernelTimestampsExtRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnEventQueryKernelTimestampsExtCb_t pfnQueryKernelTimestampsExtCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnEventQueryKernelTimestampsExtCb_t pfnQueryKernelTimestampsExtCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerEventQueryKernelTimestampsExtRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnQueryKernelTimestampsExtCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderCreateExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderCreateExpCb_t pfnCreateExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASBuilderCreateExpCb_t pfnCreateExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASBuilderCreateExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderGetBuildPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderGetBuildPropertiesExpCb_t pfnGetBuildPropertiesExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASBuilderGetBuildPropertiesExpCb_t pfnGetBuildPropertiesExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASBuilderGetBuildPropertiesExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetBuildPropertiesExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDriverRTASFormatCompatibilityCheckExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnDriverRTASFormatCompatibilityCheckExpCb_t pfnRTASFormatCompatibilityCheckExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnDriverRTASFormatCompatibilityCheckExpCb_t pfnRTASFormatCompatibilityCheckExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerDriverRTASFormatCompatibilityCheckExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnRTASFormatCompatibilityCheckExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderBuildExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderBuildExpCb_t pfnBuildExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASBuilderBuildExpCb_t pfnBuildExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASBuilderBuildExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnBuildExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASBuilderDestroyExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASBuilderDestroyExpCb_t pfnDestroyExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASBuilderDestroyExpCb_t pfnDestroyExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASBuilderDestroyExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationCreateExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationCreateExpCb_t pfnCreateExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASParallelOperationCreateExpCb_t pfnCreateExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASParallelOperationCreateExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnCreateExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationGetPropertiesExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationGetPropertiesExpCb_t pfnGetPropertiesExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASParallelOperationGetPropertiesExpCb_t pfnGetPropertiesExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASParallelOperationGetPropertiesExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnGetPropertiesExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationJoinExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationJoinExpCb_t pfnJoinExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASParallelOperationJoinExpCb_t pfnJoinExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASParallelOperationJoinExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnJoinExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerRTASParallelOperationDestroyExpRegisterCallback(
    zel_tracer_handle_t hTracer,
    zel_tracer_reg_t callback_type,
    ze_pfnRTASParallelOperationDestroyExpCb_t pfnDestroyExpCb
    ) {

    if(!ze_lib::context->tracing_lib)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *ze_pfnSetCallback_t)(
        zel_tracer_handle_t hTracer,
        zel_tracer_reg_t callback_type,
        ze_pfnRTASParallelOperationDestroyExpCb_t pfnDestroyExpCb
    );

    auto func = reinterpret_cast<ze_pfnSetCallback_t>(
        GET_FUNCTION_PTR(ze_lib::context->tracing_lib, "zelTracerRTASParallelOperationDestroyExpRegisterCallback") );

    if(func)
        return func(hTracer, callback_type, pfnDestroyExpCb);

    return ZE_RESULT_ERROR_UNINITIALIZED;    
}


} //Extern C