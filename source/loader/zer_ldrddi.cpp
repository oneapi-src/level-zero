/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_ldrddi.cpp
 *
 */
#include "ze_loader_internal.h"

using namespace loader_driver_ddi;

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize all DDI tables for a driver by calling *FromDriver functions
    ///
    /// @details This function can fail in the following scenarios:
    ///     - driver->initStatus is already set to a failure code (from a previous
    ///       required DDI initialization failure). Each *FromDriver call first checks
    ///       driver->initStatus and returns it immediately if it's already a failure.
    ///     - A required DDI table's getTable call into the driver returns a failure,
    ///       which updates driver->initStatus and is propagated back
    ///
    ///     Note: If GET_FUNCTION_PTR returns null (function not found in driver),
    ///     it only fails if driver->initStatus was already a failure. Otherwise,
    ///     driver->initStatus is returned (which would be SUCCESS).
    ///
    ///     Note: Optional DDI tables (when namespace != "zer") are ignored if they
    ///     fail, and this function continues to attempt loading remaining tables.
    ///     Only required DDI table failures cause this function to fail and return
    ///     immediately.
    ///
    /// @returns
    ///     - ::ZE_RESULT_SUCCESS if all required DDI tables loaded successfully
    ///     - ::ZE_RESULT_ERROR_* if any required DDI table failed to load
    __zedlllocal ze_result_t ZE_APICALL
    zerloaderInitDriverDDITables(loader::driver_t *driver) {
        ze_result_t result = ZE_RESULT_SUCCESS;
        result = zerGetGlobalProcAddrTableFromDriver(driver);
        if (result != ZE_RESULT_SUCCESS) {
            return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;
        
        error_state::getErrorDesc(ppString);
        if (ppString && *ppString && strlen(*ppString) > 0)
        {
            return ZE_RESULT_SUCCESS;
        }

        auto pfnGetLastErrorDescription = loader::defaultZerDdiTable->Global.pfnGetLastErrorDescription;
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
        
        auto pfnTranslateDeviceHandleToIdentifier = loader::defaultZerDdiTable->Global.pfnTranslateDeviceHandleToIdentifier;
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
        
        auto pfnTranslateIdentifierToDeviceHandle = loader::defaultZerDdiTable->Global.pfnTranslateIdentifierToDeviceHandle;
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
        
        auto pfnGetDefaultContext = loader::defaultZerDdiTable->Global.pfnGetDefaultContext;
        if( nullptr == pfnGetDefaultContext ) {
            error_state::setErrorDesc("ERROR UNINITIALIZED");
            return nullptr;
        }
        // forward to device-driver
        result = pfnGetDefaultContext(  );
        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Global table
__zedlllocal void ZE_APICALL
zerGetGlobalProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pRuntime->Global->pfnGetLastErrorDescription                  = loader::zerGetLastErrorDescription;
    loader::loaderDispatch->pRuntime->Global->pfnTranslateDeviceHandleToIdentifier        = loader::zerTranslateDeviceHandleToIdentifier;
    loader::loaderDispatch->pRuntime->Global->pfnTranslateIdentifierToDeviceHandle        = loader::zerTranslateIdentifierToDeviceHandle;
    loader::loaderDispatch->pRuntime->Global->pfnGetDefaultContext                        = loader::zerGetDefaultContext;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedlllocal ze_result_t ZE_APICALL
zerGetGlobalProcAddrTableFromDriver(loader::driver_t *driver)
{
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(driver->initStatus != ZE_RESULT_SUCCESS)
        return driver->initStatus;
    auto getTable = reinterpret_cast<zer_pfnGetGlobalProcAddrTable_t>(
        GET_FUNCTION_PTR( driver->handle, "zerGetGlobalProcAddrTable") );
    if(!getTable) 
        return driver->initStatus;
    result = getTable( loader::context->ddi_init_version, &driver->dditable.zer.Global);
    return result;
}
///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zerGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zer_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    loader::context->ddi_init_version = version;

    ze_result_t result = ZE_RESULT_SUCCESS;

    auto driverCount = loader::context->zeDrivers.size();
    auto firstDriver = &loader::context->zeDrivers[0];
    if (driverCount == 1 && firstDriver && !loader::context->forceIntercept) {
        result = zerGetGlobalProcAddrTableFromDriver(firstDriver);
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pRuntime->Global = new zer_global_dditable_t;
            if (version >= ZE_API_VERSION_1_14) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetLastErrorDescription                  = loader_driver_ddi::zerGetLastErrorDescription;
            } else {
                pDdiTable->pfnGetLastErrorDescription                  = loader::zerGetLastErrorDescription;
            }
            }
            if (version >= ZE_API_VERSION_1_14) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnTranslateDeviceHandleToIdentifier        = loader_driver_ddi::zerTranslateDeviceHandleToIdentifier;
            } else {
                pDdiTable->pfnTranslateDeviceHandleToIdentifier        = loader::zerTranslateDeviceHandleToIdentifier;
            }
            }
            if (version >= ZE_API_VERSION_1_14) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnTranslateIdentifierToDeviceHandle        = loader_driver_ddi::zerTranslateIdentifierToDeviceHandle;
            } else {
                pDdiTable->pfnTranslateIdentifierToDeviceHandle        = loader::zerTranslateIdentifierToDeviceHandle;
            }
            }
            if (version >= ZE_API_VERSION_1_14) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetDefaultContext                        = loader_driver_ddi::zerGetDefaultContext;
            } else {
                pDdiTable->pfnGetDefaultContext                        = loader::zerGetDefaultContext;
            }
            }
            zerGetGlobalProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zer.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zer_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zerGetGlobalProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<zer_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zerGetGlobalProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        zer_global_dditable_t dditable;
        memcpy(&dditable, pDdiTable, sizeof(zer_global_dditable_t));
        result = getTable( version, &dditable );
        loader::context->tracing_dditable.zer.Global = dditable;
        if ( loader::context->tracingLayerEnabled ) {
            result = getTable( version, pDdiTable );
        }
    }

    return result;
}


#if defined(__cplusplus)
};
#endif