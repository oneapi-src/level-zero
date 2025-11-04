/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_ldrddi_driver_ddi.cpp
 *
 */
#include "ze_loader_internal.h"

namespace loader_driver_ddi
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerGetLastErrorDescription
    __zedlllocal ze_result_t ZE_APICALL
    zerGetLastErrorDescription(
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        error_state::getErrorDesc(ppString);
        if (ppString && *ppString && strlen(*ppString) > 0)
        {
            return ZE_RESULT_SUCCESS;
        }

        // Check if the default driver supports DDI Handles
        if (loader::context->defaultZerDriverHandle == nullptr) {
            if (loader::context->zeDrivers.front().zerddiInitResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
                return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto dditable = reinterpret_cast<ze_handle_t*>( loader::context->defaultZerDriverHandle )->pRuntime;
        if (dditable->isValidFlag == 0) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Global == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetLastErrorDescription = dditable->Global->pfnGetLastErrorDescription;
        if( nullptr == pfnGetLastErrorDescription ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetLastErrorDescription( ppString );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerTranslateDeviceHandleToIdentifier
    __zedlllocal uint32_t ZE_APICALL
    zerTranslateDeviceHandleToIdentifier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        uint32_t result {};

        // Check if the default driver supports DDI Handles
        if (loader::context->defaultZerDriverHandle == nullptr) {
            if (loader::context->zeDrivers.front().zerddiInitResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
                error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
                return UINT32_MAX;
            }
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return UINT32_MAX;
        }
        auto dditable = reinterpret_cast<ze_handle_t*>( loader::context->defaultZerDriverHandle )->pRuntime;
        if (dditable->isValidFlag == 0) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return UINT32_MAX;
        }
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            error_state::setErrorDesc("ERROR UNSUPPORTED VERSION");
            return UINT32_MAX;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Global == nullptr) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return UINT32_MAX;
        }
        auto pfnTranslateDeviceHandleToIdentifier = dditable->Global->pfnTranslateDeviceHandleToIdentifier;
        if( nullptr == pfnTranslateDeviceHandleToIdentifier ) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return UINT32_MAX;
        }
        // forward to device-driver
        result = pfnTranslateDeviceHandleToIdentifier( hDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerTranslateIdentifierToDeviceHandle
    __zedlllocal ze_device_handle_t ZE_APICALL
    zerTranslateIdentifierToDeviceHandle(
        uint32_t identifier                             ///< [in] integer identifier of the device
        )
    {
        ze_device_handle_t result {};

        // Check if the default driver supports DDI Handles
        if (loader::context->defaultZerDriverHandle == nullptr) {
            if (loader::context->zeDrivers.front().zerddiInitResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
                error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
                return nullptr;
            }
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        auto dditable = reinterpret_cast<ze_handle_t*>( loader::context->defaultZerDriverHandle )->pRuntime;
        if (dditable->isValidFlag == 0) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            error_state::setErrorDesc("ERROR UNSUPPORTED VERSION");
            return nullptr;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Global == nullptr) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        auto pfnTranslateIdentifierToDeviceHandle = dditable->Global->pfnTranslateIdentifierToDeviceHandle;
        if( nullptr == pfnTranslateIdentifierToDeviceHandle ) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        // forward to device-driver
        result = pfnTranslateIdentifierToDeviceHandle( identifier );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zerGetDefaultContext
    __zedlllocal ze_context_handle_t ZE_APICALL
    zerGetDefaultContext(
        void
        )
    {
        ze_context_handle_t result {};

        // Check if the default driver supports DDI Handles
        if (loader::context->defaultZerDriverHandle == nullptr) {
            if (loader::context->zeDrivers.front().zerddiInitResult == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
                error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
                return nullptr;
            }
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        auto dditable = reinterpret_cast<ze_handle_t*>( loader::context->defaultZerDriverHandle )->pRuntime;
        if (dditable->isValidFlag == 0) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            error_state::setErrorDesc("ERROR UNSUPPORTED VERSION");
            return nullptr;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Global == nullptr) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        auto pfnGetDefaultContext = dditable->Global->pfnGetDefaultContext;
        if( nullptr == pfnGetDefaultContext ) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        // forward to device-driver
        result = pfnGetDefaultContext(  );
        return result;
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief function for removing the ddi driver tables for zer
    __zedlllocal void ZE_APICALL
    zerDestroyDDiDriverTables(zer_dditable_driver_t* pDdiTable)
    {
        // Delete ddi tables
        delete pDdiTable->Global;
        delete pDdiTable;
    }

} // namespace loader_driver_ddi