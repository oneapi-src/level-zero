/*
 *
 * Copyright (C) 2020-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_trcddi.cpp
 *
 */

#include <iostream>
#include "ze_tracing_layer.h"

namespace tracing_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerGetLastErrorDescription
    __zedlllocal ze_result_t ZE_APICALL
    zerGetLastErrorDescription(
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        auto pfnGetLastErrorDescription = context.zerDdiTable.Global.pfnGetLastErrorDescription;

        if( nullptr == pfnGetLastErrorDescription)
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        ZE_HANDLE_TRACER_RECURSION(context.zerDdiTable.Global.pfnGetLastErrorDescription, ppString);

        // capture parameters
        zer_get_last_error_description_params_t tracerParams = {
            &ppString
        };

        tracing_layer::APITracerCallbackDataImp<zer_pfnGetLastErrorDescriptionCb_t> apiCallbackData;

        ZER_GEN_PER_API_CALLBACK_STATE(apiCallbackData, zer_pfnGetLastErrorDescriptionCb_t, Global, pfnGetLastErrorDescriptionCb);


        return tracing_layer::APITracerWrapperImp<ze_result_t>(context.zerDdiTable.Global.pfnGetLastErrorDescription,
                                                  &tracerParams,
                                                  apiCallbackData.apiOrdinal,
                                                  apiCallbackData.prologCallbacks,
                                                  apiCallbackData.epilogCallbacks,
                                                  *tracerParams.pppString);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerTranslateDeviceHandleToIdentifier
    __zedlllocal uint32_t ZE_APICALL
    zerTranslateDeviceHandleToIdentifier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        auto pfnTranslateDeviceHandleToIdentifier = context.zerDdiTable.Global.pfnTranslateDeviceHandleToIdentifier;

        if( nullptr == pfnTranslateDeviceHandleToIdentifier)
            return UINT32_MAX;

        ZE_HANDLE_TRACER_RECURSION(context.zerDdiTable.Global.pfnTranslateDeviceHandleToIdentifier, hDevice);

        // capture parameters
        zer_translate_device_handle_to_identifier_params_t tracerParams = {
            &hDevice
        };

        tracing_layer::APITracerCallbackDataImp<zer_pfnTranslateDeviceHandleToIdentifierCb_t> apiCallbackData;

        ZER_GEN_PER_API_CALLBACK_STATE(apiCallbackData, zer_pfnTranslateDeviceHandleToIdentifierCb_t, Global, pfnTranslateDeviceHandleToIdentifierCb);


        return tracing_layer::APITracerWrapperImp<uint32_t>(context.zerDdiTable.Global.pfnTranslateDeviceHandleToIdentifier,
                                                  &tracerParams,
                                                  apiCallbackData.apiOrdinal,
                                                  apiCallbackData.prologCallbacks,
                                                  apiCallbackData.epilogCallbacks,
                                                  *tracerParams.phDevice);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerTranslateIdentifierToDeviceHandle
    __zedlllocal ze_device_handle_t ZE_APICALL
    zerTranslateIdentifierToDeviceHandle(
        uint32_t identifier                             ///< [in] integer identifier of the device
        )
    {
        auto pfnTranslateIdentifierToDeviceHandle = context.zerDdiTable.Global.pfnTranslateIdentifierToDeviceHandle;

        if( nullptr == pfnTranslateIdentifierToDeviceHandle)
            return nullptr;

        ZE_HANDLE_TRACER_RECURSION(context.zerDdiTable.Global.pfnTranslateIdentifierToDeviceHandle, identifier);

        // capture parameters
        zer_translate_identifier_to_device_handle_params_t tracerParams = {
            &identifier
        };

        tracing_layer::APITracerCallbackDataImp<zer_pfnTranslateIdentifierToDeviceHandleCb_t> apiCallbackData;

        ZER_GEN_PER_API_CALLBACK_STATE(apiCallbackData, zer_pfnTranslateIdentifierToDeviceHandleCb_t, Global, pfnTranslateIdentifierToDeviceHandleCb);


        return tracing_layer::APITracerWrapperImp<ze_device_handle_t>(context.zerDdiTable.Global.pfnTranslateIdentifierToDeviceHandle,
                                                  &tracerParams,
                                                  apiCallbackData.apiOrdinal,
                                                  apiCallbackData.prologCallbacks,
                                                  apiCallbackData.epilogCallbacks,
                                                  *tracerParams.pidentifier);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerGetDefaultContext
    __zedlllocal ze_context_handle_t ZE_APICALL
    zerGetDefaultContext(
        void
        )
    {
        auto pfnGetDefaultContext = context.zerDdiTable.Global.pfnGetDefaultContext;

        if( nullptr == pfnGetDefaultContext)
            return nullptr;

        ZE_HANDLE_TRACER_RECURSION(context.zerDdiTable.Global.pfnGetDefaultContext);

        // capture parameters
        zer_get_default_context_params_t tracerParams = {
        };

        tracing_layer::APITracerCallbackDataImp<zer_pfnGetDefaultContextCb_t> apiCallbackData;

        ZER_GEN_PER_API_CALLBACK_STATE(apiCallbackData, zer_pfnGetDefaultContextCb_t, Global, pfnGetDefaultContextCb);


        return tracing_layer::APITracerWrapperImp<ze_context_handle_t>(context.zerDdiTable.Global.pfnGetDefaultContext,
                                                  &tracerParams,
                                                  apiCallbackData.apiOrdinal,
                                                  apiCallbackData.prologCallbacks,
                                                  apiCallbackData.epilogCallbacks);
    }

} // namespace tracing_layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zerGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zer_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = tracing_layer::context.zerDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (tracing_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnGetLastErrorDescription                  = pDdiTable->pfnGetLastErrorDescription;
        pDdiTable->pfnGetLastErrorDescription                = tracing_layer::zerGetLastErrorDescription;
    }
    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnTranslateDeviceHandleToIdentifier        = pDdiTable->pfnTranslateDeviceHandleToIdentifier;
        pDdiTable->pfnTranslateDeviceHandleToIdentifier      = tracing_layer::zerTranslateDeviceHandleToIdentifier;
    }
    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnTranslateIdentifierToDeviceHandle        = pDdiTable->pfnTranslateIdentifierToDeviceHandle;
        pDdiTable->pfnTranslateIdentifierToDeviceHandle      = tracing_layer::zerTranslateIdentifierToDeviceHandle;
    }
    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnGetDefaultContext                        = pDdiTable->pfnGetDefaultContext;
        pDdiTable->pfnGetDefaultContext                      = tracing_layer::zerGetDefaultContext;
    }
    return result;
}

#if defined(__cplusplus)
};
#endif
