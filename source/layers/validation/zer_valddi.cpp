/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_valddi.cpp
 *
 */
#include "ze_validation_layer.h"

namespace validation_layer
{
    static ze_result_t logAndPropagateResult(const char* fname, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS) {
            context.logger->log_trace("Error (" + loader::to_string(result) + ") in " + std::string(fname));
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerGetLastErrorDescription
    __zedlllocal ze_result_t ZE_APICALL
    zerGetLastErrorDescription(
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        context.logger->log_trace("zerGetLastErrorDescription(ppString)");

        auto pfnGetLastErrorDescription = context.zerDdiTable.Global.pfnGetLastErrorDescription;

        if( nullptr == pfnGetLastErrorDescription )
            return logAndPropagateResult("zerGetLastErrorDescription", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerGetLastErrorDescriptionPrologue( ppString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zerGetLastErrorDescription", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zerHandleLifetime.zerGetLastErrorDescriptionPrologue( ppString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zerGetLastErrorDescription", result);
        }

        auto driver_result = pfnGetLastErrorDescription( ppString );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerGetLastErrorDescriptionEpilogue( ppString ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zerGetLastErrorDescription", result);
        }

        return logAndPropagateResult("zerGetLastErrorDescription", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerTranslateDeviceHandleToIdentifier
    __zedlllocal uint32_t ZE_APICALL
    zerTranslateDeviceHandleToIdentifier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        context.logger->log_trace("zerTranslateDeviceHandleToIdentifier(hDevice)");

        auto pfnTranslateDeviceHandleToIdentifier = context.zerDdiTable.Global.pfnTranslateDeviceHandleToIdentifier;

        if( nullptr == pfnTranslateDeviceHandleToIdentifier )
            return UINT32_MAX;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerTranslateDeviceHandleToIdentifierPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return UINT32_MAX;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zerHandleLifetime.zerTranslateDeviceHandleToIdentifierPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return UINT32_MAX;
        }

        auto driver_result = pfnTranslateDeviceHandleToIdentifier( hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerTranslateDeviceHandleToIdentifierEpilogue( hDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return UINT32_MAX;
        }

        return driver_result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerTranslateIdentifierToDeviceHandle
    __zedlllocal ze_device_handle_t ZE_APICALL
    zerTranslateIdentifierToDeviceHandle(
        uint32_t identifier                             ///< [in] integer identifier of the device
        )
    {
        context.logger->log_trace("zerTranslateIdentifierToDeviceHandle(identifier)");

        auto pfnTranslateIdentifierToDeviceHandle = context.zerDdiTable.Global.pfnTranslateIdentifierToDeviceHandle;

        if( nullptr == pfnTranslateIdentifierToDeviceHandle )
            return nullptr;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerTranslateIdentifierToDeviceHandlePrologue( identifier );
            if(result!=ZE_RESULT_SUCCESS) return nullptr;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zerHandleLifetime.zerTranslateIdentifierToDeviceHandlePrologue( identifier );
            if(result!=ZE_RESULT_SUCCESS) return nullptr;
        }

        auto driver_result = pfnTranslateIdentifierToDeviceHandle( identifier );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerTranslateIdentifierToDeviceHandleEpilogue( identifier ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return nullptr;
        }

        return driver_result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerGetDefaultContext
    __zedlllocal ze_context_handle_t ZE_APICALL
    zerGetDefaultContext(
        void
        )
    {
        context.logger->log_trace("zerGetDefaultContext()");

        auto pfnGetDefaultContext = context.zerDdiTable.Global.pfnGetDefaultContext;

        if( nullptr == pfnGetDefaultContext )
            return nullptr;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerGetDefaultContextPrologue( );
            if(result!=ZE_RESULT_SUCCESS) return nullptr;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zerHandleLifetime.zerGetDefaultContextPrologue( );
            if(result!=ZE_RESULT_SUCCESS) return nullptr;
        }

        auto driver_result = pfnGetDefaultContext(  );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zerValidation->zerGetDefaultContextEpilogue( driver_result );
            if(result!=ZE_RESULT_SUCCESS) return nullptr;
        }

        return driver_result;
    }

} // namespace validation_layer

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
    auto& dditable = validation_layer::context.zerDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnGetLastErrorDescription                  = pDdiTable->pfnGetLastErrorDescription;
        pDdiTable->pfnGetLastErrorDescription                = validation_layer::zerGetLastErrorDescription;
    }
    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnTranslateDeviceHandleToIdentifier        = pDdiTable->pfnTranslateDeviceHandleToIdentifier;
        pDdiTable->pfnTranslateDeviceHandleToIdentifier      = validation_layer::zerTranslateDeviceHandleToIdentifier;
    }
    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnTranslateIdentifierToDeviceHandle        = pDdiTable->pfnTranslateIdentifierToDeviceHandle;
        pDdiTable->pfnTranslateIdentifierToDeviceHandle      = validation_layer::zerTranslateIdentifierToDeviceHandle;
    }
    if (version >= ZE_API_VERSION_1_14) {
        dditable.pfnGetDefaultContext                        = pDdiTable->pfnGetDefaultContext;
        pDdiTable->pfnGetDefaultContext                      = validation_layer::zerGetDefaultContext;
    }
    return result;
}

#if defined(__cplusplus)
};
#endif
