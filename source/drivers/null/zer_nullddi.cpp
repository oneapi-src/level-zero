/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_nullddi.cpp
 *
 */
#include "ze_null.h"
#include <cstring>

namespace driver
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLastErrorDescription = context.zerDdiTable.Global.pfnGetLastErrorDescription;
        if( nullptr != pfnGetLastErrorDescription )
        {
            result = pfnGetLastErrorDescription( ppString );
        }
        else
        {
            // generic implementation
        }
        
        char *env_str = context.setenv_var_with_driver_id("zerGetLastErrorDescription", ZEL_NULL_DRIVER_ID);
        context.env_vars.push_back(env_str);

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnTranslateDeviceHandleToIdentifier = context.zerDdiTable.Global.pfnTranslateDeviceHandleToIdentifier;
        if( nullptr != pfnTranslateDeviceHandleToIdentifier )
        {
            result = pfnTranslateDeviceHandleToIdentifier( hDevice );
        }
        else
        {
            // generic implementation
        }
        
        char *env_str = context.setenv_var_with_driver_id("zerTranslateDeviceHandleToIdentifier", ZEL_NULL_DRIVER_ID);
        context.env_vars.push_back(env_str);

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnTranslateIdentifierToDeviceHandle = context.zerDdiTable.Global.pfnTranslateIdentifierToDeviceHandle;
        if( nullptr != pfnTranslateIdentifierToDeviceHandle )
        {
            result = pfnTranslateIdentifierToDeviceHandle( identifier );
        }
        else
        {
            // generic implementation
        }
        
        char *env_str = context.setenv_var_with_driver_id("zerTranslateIdentifierToDeviceHandle", ZEL_NULL_DRIVER_ID);
        context.env_vars.push_back(env_str);

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDefaultContext = context.zerDdiTable.Global.pfnGetDefaultContext;
        if( nullptr != pfnGetDefaultContext )
        {
            result = pfnGetDefaultContext(  );
        }
        else
        {
            // generic implementation
        }
        
        char *env_str = context.setenv_var_with_driver_id("zerGetDefaultContext", ZEL_NULL_DRIVER_ID);
        context.env_vars.push_back(env_str);

        return result;
    }

} // namespace driver

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
    auto zer_api_disable = getenv_string( "ZEL_TEST_NULL_DRIVER_DISABLE_ZER_API" );
    #ifndef ZEL_NULL_DRIVER_ID
    #define ZEL_NULL_DRIVER_ID 1
    #endif
    std::string null_driver_id_str = std::to_string(ZEL_NULL_DRIVER_ID);
    auto zer_api_unsupported = (zer_api_disable == null_driver_id_str);
    if(zer_api_unsupported)
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetLastErrorDescription                = driver::zerGetLastErrorDescription;

    pDdiTable->pfnTranslateDeviceHandleToIdentifier      = driver::zerTranslateDeviceHandleToIdentifier;

    pDdiTable->pfnTranslateIdentifierToDeviceHandle      = driver::zerTranslateIdentifierToDeviceHandle;

    pDdiTable->pfnGetDefaultContext                      = driver::zerGetDefaultContext;

    return result;
}

#if defined(__cplusplus)
};
#endif
