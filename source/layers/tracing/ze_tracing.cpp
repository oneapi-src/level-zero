/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "tracing.h"
#include "ze_tracing_layer.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "loader/ze_loader.h"

namespace tracing {
ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerCreate(
    const zel_tracer_desc_t *desc,
    zel_tracer_handle_t *phTracer) {
    return tracing_layer::createAPITracer(desc, phTracer);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerDestroy(
    zel_tracer_handle_t hTracer) {
    return tracing_layer::APITracer::fromHandle(hTracer)->destroyTracer(hTracer);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerSetPrologues(
    zel_tracer_handle_t hTracer,
    zel_core_callbacks_t *pCoreCbs) {
    return tracing_layer::APITracer::fromHandle(hTracer)->setPrologues(pCoreCbs);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerSetEpilogues(
    zel_tracer_handle_t hTracer,
    zel_core_callbacks_t *pCoreCbs) {
    return tracing_layer::APITracer::fromHandle(hTracer)->setEpilogues(pCoreCbs);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zelTracerSetEnabled(
    zel_tracer_handle_t hTracer,
    ze_bool_t enable) {
    return tracing_layer::APITracer::fromHandle(hTracer)->enableTracer(enable);
}

}
#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's TracerExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelGetTracerApiProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zel_tracer_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( tracing_layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = tracing::zelTracerCreate;

    pDdiTable->pfnDestroy                                = tracing::zelTracerDestroy;

    pDdiTable->pfnSetPrologues                           = tracing::zelTracerSetPrologues;

    pDdiTable->pfnSetEpilogues                           = tracing::zelTracerSetEpilogues;

    pDdiTable->pfnSetEnabled                             = tracing::zelTracerSetEnabled;

    return result;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderGetVersion(zel_component_version_t *version)    
{
    if(version == nullptr)
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    string_copy_s(version->component_name, TRACING_COMP_NAME, ZEL_COMPONENT_STRING_SIZE);
    version->spec_version = ZE_API_VERSION_CURRENT;
    version->component_lib_version.major = LOADER_VERSION_MAJOR;
    version->component_lib_version.minor = LOADER_VERSION_MINOR;
    version->component_lib_version.patch = LOADER_VERSION_PATCH;

    return ZE_RESULT_SUCCESS;
}


#if defined(__cplusplus)
};
#endif
