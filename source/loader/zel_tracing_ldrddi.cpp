/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_tracing_ldrddi.cpp
 *
 */
#include "ze_loader_internal.h"
#include "layers/zel_tracing_ddi.h"

namespace loader
{

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelGetTracerApiProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zel_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if(( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<zel_pfnGetTracerApiProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zelGetTracerApiProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
} // namespace loader
