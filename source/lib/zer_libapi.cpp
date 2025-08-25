/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_libapi.cpp
 *
 * @brief C++ static library for zer
 *
 */
#include "ze_lib.h"
#include "error_state.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a string describing the last error code returned by the
///        default driver in the current thread.
/// 
/// @details
///     - String returned is thread local.
///     - String is only updated on calls returning an error, i.e., not on calls
///       returning ::ZE_RESULT_SUCCESS.
///     - String may be empty if driver considers error code is already explicit
///       enough to describe cause.
///     - Memory pointed to by ppString is owned by the default driver.
///     - String returned is null-terminated.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ppString`
ze_result_t ZE_APICALL
zerGetLastErrorDescription(
    const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                    ///< cause of error.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    error_state::getErrorDesc(ppString);
    if (ppString && *ppString && strlen(*ppString) > 0)
    {
        return ZE_RESULT_SUCCESS;
    }
    static const zer_pfnGetLastErrorDescription_t pfnGetLastErrorDescription = [&result] {
        auto pfnGetLastErrorDescription = ze_lib::context->zerDdiTable.load()->Global.pfnGetLastErrorDescription;
        if( nullptr == pfnGetLastErrorDescription ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetLastErrorDescription;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetLastErrorDescription( ppString );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    error_state::getErrorDesc(ppString);
    if (ppString && *ppString && strlen(*ppString) > 0)
    {
        return ZE_RESULT_SUCCESS;
    }
    auto pfnGetLastErrorDescription = ze_lib::context->zerDdiTable.load()->Global.pfnGetLastErrorDescription;
    if( nullptr == pfnGetLastErrorDescription ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLastErrorDescription( ppString );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Translates device handle to integer identifier.
/// 
/// @details
///     - The implementation of this function should be lock-free.
///     - This function does not return error code, to get info about failure
///       user may use ::zerGetLastErrorDescription function.
///     - In case of failure, this function returns UINT32_MAX.
/// 
/// @returns
///     - integer identifier for the device
///     - UINT32_MAX
uint32_t ZE_APICALL
zerTranslateDeviceHandleToIdentifier(
    ze_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    if(ze_lib::destruction) {
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        return UINT32_MAX;
    }
    static const zer_pfnTranslateDeviceHandleToIdentifier_t pfnTranslateDeviceHandleToIdentifier = [] {
        auto pfnTranslateDeviceHandleToIdentifier = ze_lib::context->zerDdiTable.load()->Global.pfnTranslateDeviceHandleToIdentifier;
        return pfnTranslateDeviceHandleToIdentifier;
    }();
    if (nullptr == pfnTranslateDeviceHandleToIdentifier) {
        error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        return UINT32_MAX;
    }    
    return pfnTranslateDeviceHandleToIdentifier( hDevice );
    #else
    if(ze_lib::destruction) {
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        return UINT32_MAX;
    }

    auto pfnTranslateDeviceHandleToIdentifier = ze_lib::context->zerDdiTable.load()->Global.pfnTranslateDeviceHandleToIdentifier;
    if( nullptr == pfnTranslateDeviceHandleToIdentifier ) {
        if(!ze_lib::context->isInitialized)
            error_state::setErrorDesc("ERROR UNINITIALIZED");
        else
            error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        return UINT32_MAX;
    }

    return pfnTranslateDeviceHandleToIdentifier( hDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Translates to integer identifier to a device handle.
/// 
/// @details
///     - The driver must be initialized before calling this function.
///     - The implementation of this function should be lock-free.
///     - This function does not return error code, to get info about failure
///       user may use ::zerGetLastErrorDescription function.
///     - In case of failure, this function returns null.
///     - Details on the error can be retrieved using
///       ::zerGetLastErrorDescription function.
/// 
/// @returns
///     - handle of the device with the given identifier
///     - nullptr
ze_device_handle_t ZE_APICALL
zerTranslateIdentifierToDeviceHandle(
    uint32_t identifier                             ///< [in] integer identifier of the device
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    if(ze_lib::destruction) {
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        return nullptr;
    }
    static const zer_pfnTranslateIdentifierToDeviceHandle_t pfnTranslateIdentifierToDeviceHandle = [] {
        auto pfnTranslateIdentifierToDeviceHandle = ze_lib::context->zerDdiTable.load()->Global.pfnTranslateIdentifierToDeviceHandle;
        return pfnTranslateIdentifierToDeviceHandle;
    }();
    if (nullptr == pfnTranslateIdentifierToDeviceHandle) {
        error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        return nullptr;
    }    
    return pfnTranslateIdentifierToDeviceHandle( identifier );
    #else
    if(ze_lib::destruction) {
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        return nullptr;
    }

    auto pfnTranslateIdentifierToDeviceHandle = ze_lib::context->zerDdiTable.load()->Global.pfnTranslateIdentifierToDeviceHandle;
    if( nullptr == pfnTranslateIdentifierToDeviceHandle ) {
        if(!ze_lib::context->isInitialized)
            error_state::setErrorDesc("ERROR UNINITIALIZED");
        else
            error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        return nullptr;
    }

    return pfnTranslateIdentifierToDeviceHandle( identifier );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves handle to default context from the default driver.
/// 
/// @details
///     - The driver must be initialized before calling this function.
///     - The implementation of this function should be lock-free.
///     - This returned context contains all the devices available in the
///       default driver.
///     - This function does not return error code, to get info about failure
///       user may use ::zerGetLastErrorDescription function.
///     - In case of failure, this function returns null.
///     - Details on the error can be retrieved using
///       ::zerGetLastErrorDescription function.
/// 
/// @returns
///     - handle of the default context
///     - nullptr
ze_context_handle_t ZE_APICALL
zerGetDefaultContext(
    void
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    if(ze_lib::destruction) {
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        return nullptr;
    }
    static const zer_pfnGetDefaultContext_t pfnGetDefaultContext = [] {
        auto pfnGetDefaultContext = ze_lib::context->zerDdiTable.load()->Global.pfnGetDefaultContext;
        return pfnGetDefaultContext;
    }();
    if (nullptr == pfnGetDefaultContext) {
        error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        return nullptr;
    }    
    return pfnGetDefaultContext(  );
    #else
    if(ze_lib::destruction) {
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        return nullptr;
    }

    auto pfnGetDefaultContext = ze_lib::context->zerDdiTable.load()->Global.pfnGetDefaultContext;
    if( nullptr == pfnGetDefaultContext ) {
        if(!ze_lib::context->isInitialized)
            error_state::setErrorDesc("ERROR UNINITIALIZED");
        else
            error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        return nullptr;
    }

    return pfnGetDefaultContext(  );
    #endif
}

} // extern "C"
