/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_libapi.cpp
 *
 * @brief C++ static library for ze
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the 'oneAPI' driver(s)
/// 
/// @details
///     - @deprecated since 1.10. Please use zeInitDrivers()
///     - The application must call this function or zeInitDrivers before
///       calling any other function.
///     - If this function is not called then all other functions will return
///       ::ZE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of each driver will be initialized per process.
///     - The application may call this function multiple times with different
///       flags or environment variables enabled.
///     - The application must call this function after forking new processes.
///       Each forked process must call this function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe for scenarios
///       where multiple libraries may initialize the driver(s) simultaneously.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeInit(
    ze_init_flags_t flags                           ///< [in] initialization flags.
                                                    ///< must be 0 (default) or a combination of ::ze_init_flag_t.
    )
{
    static ze_result_t result = ZE_RESULT_SUCCESS;
    #ifdef L0_STATIC_LOADER_BUILD
    if (!ze_lib::context) {
        ze_lib::context = new ze_lib::context_t;
    }
    #endif
    std::call_once(ze_lib::context->initOnce, [flags]() {
        result = ze_lib::context->Init(flags, false, nullptr);

        if( ZE_RESULT_SUCCESS != result )
            return result;

        if(ze_lib::destruction) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        auto pfnInit = ze_lib::context->zeDdiTable.load()->Global.pfnInit;
        if( nullptr == pfnInit ) {
            if(!ze_lib::context->isInitialized)
                return ZE_RESULT_ERROR_UNINITIALIZED;
            else
                return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }

        result = pfnInit( flags );
        return result;
    });

    if(ze_lib::destruction) {
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves driver instances
/// 
/// @details
///     - @deprecated since 1.10. Please use zeInitDrivers()
///     - Usage of zeInitDrivers and zeDriverGet is mutually exclusive and
///       should not be used together. Usage of them together will result in
///       undefined behavior.
///     - A driver represents a collection of physical devices.
///     - Multiple calls to this function will return identical driver handles,
///       in the same order.
///     - The application may pass nullptr for pDrivers when only querying the
///       number of drivers.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetPlatformIDs
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDriverGet(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                    ///< if count is zero, then the loader shall update the value with the
                                                    ///< total number of drivers available.
                                                    ///< if count is greater than the number of drivers available, then the
                                                    ///< loader shall update the value with the correct number of drivers available.
    ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles.
                                                    ///< if count is less than the number of drivers available, then the loader
                                                    ///< shall only retrieve that number of drivers.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    if (!ze_lib::context || ze_lib::context->zeDdiTable == nullptr) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverGet_t pfnGet = [&result] {
        auto pfnGet = ze_lib::context->zeDdiTable.load()->Driver.pfnGet;
        if( nullptr == pfnGet ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGet;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGet( pCount, phDrivers );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if (ze_lib::context->zeDdiTable == nullptr) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zeDdiTable.load()->Driver.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    ze_lib::context->zeInuse = true;

    return pfnGet( pCount, phDrivers );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the 'oneAPI' driver(s) based on the driver types requested
///        and retrieve the driver handles.
/// 
/// @details
///     - The application must call this function or zeInit before calling any
///       other function. (zeInit is [Deprecated] and is replaced by
///       zeInitDrivers)
///     - Calls to zeInit[Deprecated] or InitDrivers will not alter the drivers
///       retrieved through either api.
///     - Drivers init through zeInit[Deprecated] or InitDrivers will not be
///       reInitialized once init in an application. The Loader will determine
///       if the already init driver needs to be delivered to the user through
///       the init type flags.
///     - Already init Drivers will not be uninitialized if the call to
///       InitDrivers does not include that driver's type. Those init drivers
///       which don't match the init flags will not have their driver handles
///       returned to the user in that InitDrivers call.
///     - If this function or zeInit[Deprecated] is not called, then all other
///       functions will return ::ZE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of each driver will be initialized per process.
///     - A driver represents a collection of physical devices.
///     - Multiple calls to this function will return identical driver handles,
///       in the same order.
///     - The drivers returned to the caller will be based on the init types
///       which state the drivers to be included.
///     - The application may pass nullptr for pDrivers when only querying the
///       number of drivers.
///     - The application may call this function multiple times with different
///       flags or environment variables enabled.
///     - The application must call this function after forking new processes.
///       Each forked process must call this function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe for scenarios
///       where multiple libraries may initialize the driver(s) simultaneously.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///         + `nullptr == desc`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x0 == desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeInitDrivers(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                    ///< if count is zero, then the loader shall update the value with the
                                                    ///< total number of drivers available.
                                                    ///< if count is greater than the number of drivers available, then the
                                                    ///< loader shall update the value with the correct number of drivers available.
    ze_driver_handle_t* phDrivers,                  ///< [in,out][optional][range(0, *pCount)] array of driver instance handles.
                                                    ///< if count is less than the number of drivers available, then the loader
                                                    ///< shall only retrieve that number of drivers.
    ze_init_driver_type_desc_t* desc                ///< [in] descriptor containing the driver type initialization details
                                                    ///< including ::ze_init_driver_type_flag_t combinations.
    )
{
    ze_result_t result = ZE_RESULT_SUCCESS;
    #ifdef L0_STATIC_LOADER_BUILD
    if (!ze_lib::context) {
        ze_lib::context = new ze_lib::context_t;
    }
    #endif
    std::call_once(ze_lib::context->initOnceDrivers, [desc,&result]() {
        result = ze_lib::context->Init(0, false, desc);
        return result;
    });

    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if (ze_lib::context->zeDdiTable.load() == nullptr) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInitDrivers = ze_lib::context->zeDdiTable.load()->Global.pfnInitDrivers;
    if( nullptr == pfnInitDrivers ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    result = pfnInitDrivers( pCount, phDrivers, desc );

    if (result == ZE_RESULT_SUCCESS) {
        if (phDrivers) {
            ze_lib::context->zeInuse = true;
        }
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the specified driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - Starting from API version 1.17, any driver reporting version 1.17 or
///       later is assumed to support the ::ZE_DRIVER_DDI_HANDLES_EXT_NAME
///       extension; see ::ze_driver_ddi_handles_ext_properties_t for details.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == version`
ze_result_t ZE_APICALL
zeDriverGetApiVersion(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_api_version_t* version                       ///< [out] api version
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverGetApiVersion_t pfnGetApiVersion = [&result] {
        auto pfnGetApiVersion = ze_lib::context->zeDdiTable.load()->Driver.pfnGetApiVersion;
        if( nullptr == pfnGetApiVersion ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetApiVersion;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetApiVersion( hDriver, version );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetApiVersion = ze_lib::context->zeDdiTable.load()->Driver.pfnGetApiVersion;
    if( nullptr == pfnGetApiVersion ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetApiVersion( hDriver, version );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the driver.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetPlatformInfo**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDriverProperties`
ze_result_t ZE_APICALL
zeDriverGetProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Driver.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hDriver, pDriverProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Driver.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDriver, pDriverProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves IPC attributes of the driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIpcProperties`
ze_result_t ZE_APICALL
zeDriverGetIpcProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverGetIpcProperties_t pfnGetIpcProperties = [&result] {
        auto pfnGetIpcProperties = ze_lib::context->zeDdiTable.load()->Driver.pfnGetIpcProperties;
        if( nullptr == pfnGetIpcProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetIpcProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetIpcProperties( hDriver, pIpcProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcProperties = ze_lib::context->zeDdiTable.load()->Driver.pfnGetIpcProperties;
    if( nullptr == pfnGetIpcProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcProperties( hDriver, pIpcProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves extension properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkEnumerateInstanceExtensionProperties**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDriverGetExtensionProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of extension properties available.
                                                    ///< if count is greater than the number of extension properties available,
                                                    ///< then the driver shall update the value with the correct number of
                                                    ///< extension properties available.
    ze_driver_extension_properties_t* pExtensionProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< extension properties.
                                                    ///< if count is less than the number of extension properties available,
                                                    ///< then driver shall only retrieve that number of extension properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverGetExtensionProperties_t pfnGetExtensionProperties = [&result] {
        auto pfnGetExtensionProperties = ze_lib::context->zeDdiTable.load()->Driver.pfnGetExtensionProperties;
        if( nullptr == pfnGetExtensionProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetExtensionProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExtensionProperties = ze_lib::context->zeDdiTable.load()->Driver.pfnGetExtensionProperties;
    if( nullptr == pfnGetExtensionProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves function pointer for vendor-specific or experimental
///        extensions
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == name`
///         + `nullptr == ppFunctionAddress`
ze_result_t ZE_APICALL
zeDriverGetExtensionFunctionAddress(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const char* name,                               ///< [in] extension function name
    void** ppFunctionAddress                        ///< [out] pointer to function pointer
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverGetExtensionFunctionAddress_t pfnGetExtensionFunctionAddress = [&result] {
        auto pfnGetExtensionFunctionAddress = ze_lib::context->zeDdiTable.load()->Driver.pfnGetExtensionFunctionAddress;
        if( nullptr == pfnGetExtensionFunctionAddress ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetExtensionFunctionAddress;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExtensionFunctionAddress = ze_lib::context->zeDdiTable.load()->Driver.pfnGetExtensionFunctionAddress;
    if( nullptr == pfnGetExtensionFunctionAddress ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a string describing the last error code returned by the
///        driver in the current thread.
/// 
/// @details
///     - String returned is thread local.
///     - String is only updated on calls returning an error, i.e., not on calls
///       returning ::ZE_RESULT_SUCCESS.
///     - String may be empty if driver considers error code is already explicit
///       enough to describe cause.
///     - Memory pointed to by ppString is owned by the driver.
///     - String returned is null-terminated.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ppString`
ze_result_t ZE_APICALL
zeDriverGetLastErrorDescription(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                    ///< cause of error.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverGetLastErrorDescription_t pfnGetLastErrorDescription = [&result] {
        auto pfnGetLastErrorDescription = ze_lib::context->zeDdiTable.load()->Driver.pfnGetLastErrorDescription;
        if( nullptr == pfnGetLastErrorDescription ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetLastErrorDescription;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetLastErrorDescription( hDriver, ppString );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLastErrorDescription = ze_lib::context->zeDdiTable.load()->Driver.pfnGetLastErrorDescription;
    if( nullptr == pfnGetLastErrorDescription ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLastErrorDescription( hDriver, ppString );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves handle to default context from the driver.
/// 
/// @details
///     - The implementation of this function should be lock-free.
///     - This returned context contains all the devices available in the
///       driver.
///     - This function does not return error code, to get info about failure
///       user may use ::zeDriverGetLastErrorDescription function.
///     - In case of failure, this function returns null.
///     - Details on the error can be retrieved using
///       ::zeDriverGetLastErrorDescription function.
/// 
/// @returns
///     - handle of the default context
///     - nullptr
ze_context_handle_t ZE_APICALL
zeDriverGetDefaultContext(
    ze_driver_handle_t hDriver                      ///< [in] handle of the driver instance
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    if(ze_lib::destruction) {
        return nullptr;
    }
    static const ze_pfnDriverGetDefaultContext_t pfnGetDefaultContext = [] {
        auto pfnGetDefaultContext = ze_lib::context->zeDdiTable.load()->Driver.pfnGetDefaultContext;
        return pfnGetDefaultContext;
    }();
    if (nullptr == pfnGetDefaultContext) {
        return nullptr;
    }    
    return pfnGetDefaultContext( hDriver );
    #else
    if(ze_lib::destruction) {
        return nullptr;
    }

    auto pfnGetDefaultContext = ze_lib::context->zeDdiTable.load()->Driver.pfnGetDefaultContext;
    if( nullptr == pfnGetDefaultContext ) {
        return nullptr;
    }

    return pfnGetDefaultContext( hDriver );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves devices within a driver
/// 
/// @details
///     - Multiple calls to this function will return identical device handles,
///       in the same order.
///     - The number and order of handles returned from this function is
///       affected by the `ZE_AFFINITY_MASK` and `ZE_ENABLE_PCI_ID_DEVICE_ORDER`
///       environment variables.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDeviceGet(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of devices available.
                                                    ///< if count is greater than the number of devices available, then the
                                                    ///< driver shall update the value with the correct number of devices available.
    ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices.
                                                    ///< if count is less than the number of devices available, then driver
                                                    ///< shall only retrieve that number of devices.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGet_t pfnGet = [&result] {
        auto pfnGet = ze_lib::context->zeDdiTable.load()->Device.pfnGet;
        if( nullptr == pfnGet ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGet;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGet( hDriver, pCount, phDevices );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zeDdiTable.load()->Device.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( hDriver, pCount, phDevices );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the root-device of a device handle
/// 
/// @details
///     - When the device handle passed does not belong to any root-device,
///       nullptr is returned.
///     - Multiple calls to this function will return the same device handle.
///     - The root-device handle returned by this function does not have access
///       automatically to the resources
///       created with the associated sub-device, unless those resources have
///       been created with a context
///       explicitly containing both handles.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phRootDevice`
ze_result_t ZE_APICALL
zeDeviceGetRootDevice(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetRootDevice_t pfnGetRootDevice = [&result] {
        auto pfnGetRootDevice = ze_lib::context->zeDdiTable.load()->Device.pfnGetRootDevice;
        if( nullptr == pfnGetRootDevice ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetRootDevice;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetRootDevice( hDevice, phRootDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRootDevice = ze_lib::context->zeDdiTable.load()->Device.pfnGetRootDevice;
    if( nullptr == pfnGetRootDevice ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRootDevice( hDevice, phRootDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a sub-device from a device
/// 
/// @details
///     - When the device handle passed does not contain any sub-device, a
///       pCount of 0 is returned.
///     - Multiple calls to this function will return identical device handles,
///       in the same order.
///     - The number of handles returned from this function is affected by the
///       `ZE_AFFINITY_MASK` environment variable.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clCreateSubDevices
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDeviceGetSubDevices(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of sub-devices available.
                                                    ///< if count is greater than the number of sub-devices available, then the
                                                    ///< driver shall update the value with the correct number of sub-devices available.
    ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices.
                                                    ///< if count is less than the number of sub-devices available, then driver
                                                    ///< shall only retrieve that number of sub-devices.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetSubDevices_t pfnGetSubDevices = [&result] {
        auto pfnGetSubDevices = ze_lib::context->zeDdiTable.load()->Device.pfnGetSubDevices;
        if( nullptr == pfnGetSubDevices ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetSubDevices;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetSubDevices( hDevice, pCount, phSubdevices );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSubDevices = ze_lib::context->zeDdiTable.load()->Device.pfnGetSubDevices;
    if( nullptr == pfnGetSubDevices ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSubDevices( hDevice, pCount, phSubdevices );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDeviceProperties`
ze_result_t ZE_APICALL
zeDeviceGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hDevice, pDeviceProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDevice, pDeviceProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves compute properties of the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pComputeProperties`
ze_result_t ZE_APICALL
zeDeviceGetComputeProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetComputeProperties_t pfnGetComputeProperties = [&result] {
        auto pfnGetComputeProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetComputeProperties;
        if( nullptr == pfnGetComputeProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetComputeProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetComputeProperties( hDevice, pComputeProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetComputeProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetComputeProperties;
    if( nullptr == pfnGetComputeProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetComputeProperties( hDevice, pComputeProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves module properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pModuleProperties`
ze_result_t ZE_APICALL
zeDeviceGetModuleProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetModuleProperties_t pfnGetModuleProperties = [&result] {
        auto pfnGetModuleProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetModuleProperties;
        if( nullptr == pfnGetModuleProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetModuleProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetModuleProperties( hDevice, pModuleProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetModuleProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetModuleProperties;
    if( nullptr == pfnGetModuleProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetModuleProperties( hDevice, pModuleProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves command queue group properties of the device.
/// 
/// @details
///     - Properties are reported for each physical command queue group
///       available on the device.
///     - Multiple calls to this function will return properties in the same
///       order.
///     - The order in which the properties are returned is defined by the
///       command queue group's ordinal.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkGetPhysicalDeviceQueueFamilyProperties**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDeviceGetCommandQueueGroupProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of available command queue groups.
                                                    ///< If count is zero, then the driver shall update the value with the
                                                    ///< total number of command queue groups available.
                                                    ///< If count is less than the number of command queue groups available,
                                                    ///< then the driver shall only retrieve command queue group properties for
                                                    ///< the given number of command queue groups.
                                                    ///< If count is greater than or equal to the number of command queue
                                                    ///< groups available, then the driver shall retrieve command queue group
                                                    ///< properties for all available command queue groups.
    ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< command queue group properties.
                                                    ///< If count is less than the number of command queue groups available,
                                                    ///< then the driver shall only retrieve that number of command queue group properties.
                                                    ///< The order of properties in the array corresponds to the command queue
                                                    ///< group ordinal.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetCommandQueueGroupProperties_t pfnGetCommandQueueGroupProperties = [&result] {
        auto pfnGetCommandQueueGroupProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetCommandQueueGroupProperties;
        if( nullptr == pfnGetCommandQueueGroupProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetCommandQueueGroupProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCommandQueueGroupProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetCommandQueueGroupProperties;
    if( nullptr == pfnGetCommandQueueGroupProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves local memory properties of the device.
/// 
/// @details
///     - Properties are reported for each physical memory type supported by the
///       device.
///     - Multiple calls to this function will return properties in the same
///       order.
///     - The order in which the properties are returned defines the device's
///       local memory ordinal.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDeviceGetMemoryProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of memory properties available.
                                                    ///< if count is greater than the number of memory properties available,
                                                    ///< then the driver shall update the value with the correct number of
                                                    ///< memory properties available.
    ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< memory properties.
                                                    ///< if count is less than the number of memory properties available, then
                                                    ///< driver shall only retrieve that number of memory properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetMemoryProperties_t pfnGetMemoryProperties = [&result] {
        auto pfnGetMemoryProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetMemoryProperties;
        if( nullptr == pfnGetMemoryProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetMemoryProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMemoryProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetMemoryProperties;
    if( nullptr == pfnGetMemoryProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory access properties of the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemAccessProperties`
ze_result_t ZE_APICALL
zeDeviceGetMemoryAccessProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetMemoryAccessProperties_t pfnGetMemoryAccessProperties = [&result] {
        auto pfnGetMemoryAccessProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetMemoryAccessProperties;
        if( nullptr == pfnGetMemoryAccessProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetMemoryAccessProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMemoryAccessProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetMemoryAccessProperties;
    if( nullptr == pfnGetMemoryAccessProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves cache properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetDeviceInfo
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDeviceGetCacheProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of cache properties available.
                                                    ///< if count is greater than the number of cache properties available,
                                                    ///< then the driver shall update the value with the correct number of
                                                    ///< cache properties available.
    ze_device_cache_properties_t* pCacheProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for cache properties.
                                                    ///< if count is less than the number of cache properties available, then
                                                    ///< driver shall only retrieve that number of cache properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetCacheProperties_t pfnGetCacheProperties = [&result] {
        auto pfnGetCacheProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetCacheProperties;
        if( nullptr == pfnGetCacheProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetCacheProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetCacheProperties( hDevice, pCount, pCacheProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCacheProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetCacheProperties;
    if( nullptr == pfnGetCacheProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCacheProperties( hDevice, pCount, pCacheProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves image properties of the device
/// 
/// @details
///     - See ::zeImageGetProperties for format-specific capabilities.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImageProperties`
ze_result_t ZE_APICALL
zeDeviceGetImageProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetImageProperties_t pfnGetImageProperties = [&result] {
        auto pfnGetImageProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetImageProperties;
        if( nullptr == pfnGetImageProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetImageProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetImageProperties( hDevice, pImageProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetImageProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetImageProperties;
    if( nullptr == pfnGetImageProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetImageProperties( hDevice, pImageProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves external memory import and export of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pExternalMemoryProperties`
ze_result_t ZE_APICALL
zeDeviceGetExternalMemoryProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetExternalMemoryProperties_t pfnGetExternalMemoryProperties = [&result] {
        auto pfnGetExternalMemoryProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetExternalMemoryProperties;
        if( nullptr == pfnGetExternalMemoryProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetExternalMemoryProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExternalMemoryProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetExternalMemoryProperties;
    if( nullptr == pfnGetExternalMemoryProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves peer-to-peer properties between one device and a peer
///        devices
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pP2PProperties`
ze_result_t ZE_APICALL
zeDeviceGetP2PProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetP2PProperties_t pfnGetP2PProperties = [&result] {
        auto pfnGetP2PProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetP2PProperties;
        if( nullptr == pfnGetP2PProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetP2PProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetP2PProperties = ze_lib::context->zeDdiTable.load()->Device.pfnGetP2PProperties;
    if( nullptr == pfnGetP2PProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries if one device can directly access peer device allocations
/// 
/// @details
///     - Any device can access any other device within a node through a
///       scale-up fabric.
///     - The following are conditions for CanAccessPeer query.
///         + If both device and peer device are the same then return true.
///         + If both sub-device and peer sub-device are the same then return
///           true.
///         + If both are sub-devices and share the same parent device then
///           return true.
///         + If both device and remote device are connected by a direct or
///           indirect scale-up fabric or over PCIe (same root complex or shared
///           PCIe switch) then true.
///         + If both sub-device and remote parent device (and vice-versa) are
///           connected by a direct or indirect scale-up fabric or over PCIe
///           (same root complex or shared PCIe switch) then true.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == value`
ze_result_t ZE_APICALL
zeDeviceCanAccessPeer(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_bool_t* value                                ///< [out] returned access capability
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceCanAccessPeer_t pfnCanAccessPeer = [&result] {
        auto pfnCanAccessPeer = ze_lib::context->zeDdiTable.load()->Device.pfnCanAccessPeer;
        if( nullptr == pfnCanAccessPeer ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCanAccessPeer;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCanAccessPeer( hDevice, hPeerDevice, value );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCanAccessPeer = ze_lib::context->zeDdiTable.load()->Device.pfnCanAccessPeer;
    if( nullptr == pfnCanAccessPeer ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCanAccessPeer( hDevice, hPeerDevice, value );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns current status of the device.
/// 
/// @details
///     - Once a device is reset, this call will update the OS handle attached
///       to the device handle.
///     - The application may call this function from simultaneous threads with
///       the same device handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_SUCCESS
///         + Device is available for use.
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///         + Device is lost; must be reset for use.
ze_result_t ZE_APICALL
zeDeviceGetStatus(
    ze_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetStatus_t pfnGetStatus = [&result] {
        auto pfnGetStatus = ze_lib::context->zeDdiTable.load()->Device.pfnGetStatus;
        if( nullptr == pfnGetStatus ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetStatus;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetStatus( hDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetStatus = ze_lib::context->zeDdiTable.load()->Device.pfnGetStatus;
    if( nullptr == pfnGetStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetStatus( hDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns synchronized Host and device global timestamps.
/// 
/// @details
///     - The application may call this function from simultaneous threads with
///       the same device handle.
///     - The implementation of this function must be thread-safe.
///     - The hostTimestamp value needs to return a sample from a
///       RAW_MONOTONIC_CLOCK source that is not affected by system time changes
///       or by software adjustments to the clock.
///     - The hostTimestamp and deviceTimestamp values should be coordinated to
///       be sampled at the same time/close together
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == hostTimestamp`
///         + `nullptr == deviceTimestamp`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + The feature is not supported by the underlying platform.
ze_result_t ZE_APICALL
zeDeviceGetGlobalTimestamps(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp in nanoseconds at the time
                                                    ///< of invoking the function.
    uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp in tick counts at the
                                                    ///< time of invoking the function.
                                                    ///< To get the devicetime stamp in nanoseconds, resolve the tick counts
                                                    ///< using the timestampValidBits as mask together with timerResolution
                                                    ///< members of the ::ze_device_properties_t structure.
                                                    ///< For example: deviceTimestampinNS = (deviceTimestamp &
                                                    ///< timestampValidBits) * 1/timerResolution.(when timer resolution is in cycle/sec)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetGlobalTimestamps_t pfnGetGlobalTimestamps = [&result] {
        auto pfnGetGlobalTimestamps = ze_lib::context->zeDdiTable.load()->Device.pfnGetGlobalTimestamps;
        if( nullptr == pfnGetGlobalTimestamps ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetGlobalTimestamps;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetGlobalTimestamps = ze_lib::context->zeDdiTable.load()->Device.pfnGetGlobalTimestamps;
    if( nullptr == pfnGetGlobalTimestamps ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes all command queues related to the device.
/// 
/// @details
///     - The application may call this function from simultaneous threads with
///       the same device handle.
///     - The implementation of this function should be thread-safe.
///     - This function blocks until all preceding submissions to all queues on
///       the device are completed.
///     - This function returns an error if device execution fails.
///     - This function hangs indefinitely if the device is blocked on a
///       non-signaled event.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
ze_result_t ZE_APICALL
zeDeviceSynchronize(
    ze_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceSynchronize_t pfnSynchronize = [&result] {
        auto pfnSynchronize = ze_lib::context->zeDdiTable.load()->Device.pfnSynchronize;
        if( nullptr == pfnSynchronize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSynchronize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSynchronize( hDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSynchronize = ze_lib::context->zeDdiTable.load()->Device.pfnSynchronize;
    if( nullptr == pfnSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSynchronize( hDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns unified increment value that can be used for Counter Based
///        Events created with
///        ::ze_event_counter_based_external_aggregate_storage_desc_t
/// 
/// @details
///     - Value is applicable only to this specific device
///     - It may be used, when user is not able define number of internal driver
///       operations during given append call, for example dividing copy into
///       multiple engines. More details can be found in programming guide.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == incrementValue`
ze_result_t ZE_APICALL
zeDeviceGetAggregatedCopyOffloadIncrementValue(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* incrementValue                        ///< [out] increment value that can be used for Event creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetAggregatedCopyOffloadIncrementValue_t pfnGetAggregatedCopyOffloadIncrementValue = [&result] {
        auto pfnGetAggregatedCopyOffloadIncrementValue = ze_lib::context->zeDdiTable.load()->Device.pfnGetAggregatedCopyOffloadIncrementValue;
        if( nullptr == pfnGetAggregatedCopyOffloadIncrementValue ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAggregatedCopyOffloadIncrementValue;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAggregatedCopyOffloadIncrementValue( hDevice, incrementValue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAggregatedCopyOffloadIncrementValue = ze_lib::context->zeDdiTable.load()->Device.pfnGetAggregatedCopyOffloadIncrementValue;
    if( nullptr == pfnGetAggregatedCopyOffloadIncrementValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAggregatedCopyOffloadIncrementValue( hDevice, incrementValue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns maximum value supported by the driver for Counter Based Events
///        created with externally managed counter storage (see
///        ::ze_event_counter_based_external_sync_allocation_desc_t and
///        ::ze_event_counter_based_external_aggregate_storage_desc_t).
/// 
/// @details
///     - Value is applicable only to this specific device.
///     - User must query this value before creating a Counter Based Event with
///       externally managed counter storage and ensure that `completionValue`
///       provided in the descriptor does not exceed it.
///     - User must also ensure that any value written by the application to
///       `deviceAddress` or `hostAddress` of an externally managed counter
///       storage (including values aggregated under `deviceAddress` of
///       ::ze_event_counter_based_external_aggregate_storage_desc_t) does not
///       exceed this maximum at any point in time.
///     - Driver does not validate values written by the user to externally
///       managed memory; exceeding this maximum results in undefined behavior.
///     - ::zeEventCounterBasedCreate returns ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///       if the descriptor specifies a value greater than the value returned by
///       this query.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == maxValue`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + Provided invalid hDevice or maxValue pointer
ze_result_t ZE_APICALL
zeDeviceGetCounterBasedEventMaxValue(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint64_t* maxValue                              ///< [out] maximum value that may appear under externally managed counter
                                                    ///< storage and that may be passed as `completionValue` when creating a
                                                    ///< Counter Based Event
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetCounterBasedEventMaxValue_t pfnGetCounterBasedEventMaxValue = [&result] {
        auto pfnGetCounterBasedEventMaxValue = ze_lib::context->zeDdiTable.load()->Device.pfnGetCounterBasedEventMaxValue;
        if( nullptr == pfnGetCounterBasedEventMaxValue ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetCounterBasedEventMaxValue;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetCounterBasedEventMaxValue( hDevice, maxValue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCounterBasedEventMaxValue = ze_lib::context->zeDdiTable.load()->Device.pfnGetCounterBasedEventMaxValue;
    if( nullptr == pfnGetCounterBasedEventMaxValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCounterBasedEventMaxValue( hDevice, maxValue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gathers null-terminated plain text representation of runtime
///        requirements for provided object.
/// 
/// @details
///     - To gather requirements for a given object (e.g. an L0 module or
///       graph), pObjDesc must point to a structure (e.g.
///       ::ze_runtime_requirements_module_desc_t or
///       ::ze_runtime_requirements_graph_desc_t) describing object for which
///       the requirements are being retrieved.
///     - Requirements are copied to user-provided memory pointed to by
///       pRequirements and pSize is set to represent the actual written length
///       of the requirements string in bytes.
///     - The caller can pass nullptr for pRequirements when querying only for
///       size.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pObjDesc`
///         + `nullptr == pSize`
///         + (nullptr != pRequirements) && (nullptr == pSize).
///         + (nullptr != pRequirements) && (*pSize < requiredSize).
///     - ::ZE_RESULT_SUCCESS
///         + Successfully gathered requirements for provided source (e.g. module).
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + Provided hDevice handle is invalid
///         + pObjDesc doesn't point to a structure that describes a supported object for which the requirements can be gathered.
ze_result_t ZE_APICALL
zeDeviceGetRuntimeRequirements(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const void* pObjDesc,                           ///< [in] describes the object for which the requirements are to be
                                                    ///< gathered
    size_t* pSize,                                  ///< [in,out] size of requirements string in bytes.
    char* pRequirements                             ///< [in,out][optional] holds results of the query.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetRuntimeRequirements_t pfnGetRuntimeRequirements = [&result] {
        auto pfnGetRuntimeRequirements = ze_lib::context->zeDdiTable.load()->Device.pfnGetRuntimeRequirements;
        if( nullptr == pfnGetRuntimeRequirements ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetRuntimeRequirements;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetRuntimeRequirements( hDevice, pObjDesc, pSize, pRequirements );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRuntimeRequirements = ze_lib::context->zeDdiTable.load()->Device.pfnGetRuntimeRequirements;
    if( nullptr == pfnGetRuntimeRequirements ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRuntimeRequirements( hDevice, pObjDesc, pSize, pRequirements );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves requirements producer key.
/// 
/// @details
///     - Retrieves null-terminated plain text that represents the producer of
///       requirements (Example string: 'INTEL.L0.GPU').
///     - Useful for bookkeeping of the requirements on user side.
/// 
/// @returns
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pKey`
///         + (nullptr == pKey).
///     - ::ZE_RESULT_SUCCESS
///         + Successfully retrieved the key.
ze_result_t ZE_APICALL
zeDeviceGetRuntimeRequirementsKey(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const char** pKey                               ///< [out] returned key
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetRuntimeRequirementsKey_t pfnGetRuntimeRequirementsKey = [&result] {
        auto pfnGetRuntimeRequirementsKey = ze_lib::context->zeDdiTable.load()->Device.pfnGetRuntimeRequirementsKey;
        if( nullptr == pfnGetRuntimeRequirementsKey ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetRuntimeRequirementsKey;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetRuntimeRequirementsKey( hDevice, pKey );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRuntimeRequirementsKey = ze_lib::context->zeDdiTable.load()->Device.pfnGetRuntimeRequirementsKey;
    if( nullptr == pfnGetRuntimeRequirementsKey ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRuntimeRequirementsKey( hDevice, pKey );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Validates runtime requirements.
/// 
/// @details
///     - To validate existing requirements (e.g. cached from previous runs),
///       requirements string should be passed as pRequirements.
/// 
/// @returns
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRequirements`
///         + `nullptr == pOut`
///         + (nullptr == pRequirements).
///         + (nullptr == pOut).
///     - ::ZE_RESULT_SUCCESS
///         + Validation call succeeded and result of the validation is available in pOut.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + Provided hDevice handle is invalid
ze_result_t ZE_APICALL
zeDeviceValidateRuntimeRequirements(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const char* pRequirements,                      ///< [in] requirements to be validated. Requirements should be
                                                    ///< null-terminated plain text representation of runtime requirements
                                                    ///< previously retrieved from the device.
    ze_validate_runtime_requirements_output_t* pOut ///< [in][out] Output of the validation call.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceValidateRuntimeRequirements_t pfnValidateRuntimeRequirements = [&result] {
        auto pfnValidateRuntimeRequirements = ze_lib::context->zeDdiTable.load()->Device.pfnValidateRuntimeRequirements;
        if( nullptr == pfnValidateRuntimeRequirements ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnValidateRuntimeRequirements;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnValidateRuntimeRequirements( hDevice, pRequirements, pOut );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnValidateRuntimeRequirements = ze_lib::context->zeDdiTable.load()->Device.pfnValidateRuntimeRequirements;
    if( nullptr == pfnValidateRuntimeRequirements ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnValidateRuntimeRequirements( hDevice, pRequirements, pOut );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a context for the driver.
/// 
/// @details
///     - The application must only use the context for the driver which was
///       provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phContext`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeContextCreate(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
    const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
    ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->Context.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hDriver, desc, phContext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->Context.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hDriver, desc, phContext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a context for the driver.
/// 
/// @details
///     - The application must only use the context for the driver which was
///       provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phContext`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phDevices) && (0 < numDevices)`
ze_result_t ZE_APICALL
zeContextCreateEx(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
    const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
    uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                    ///< phDevices`
    ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                    ///< context has visibility.
                                                    ///< if nullptr, then all devices and any sub-devices supported by the
                                                    ///< driver instance are
                                                    ///< visible to the context.
                                                    ///< otherwise, the context only has visibility to the devices and any
                                                    ///< sub-devices of the
                                                    ///< devices in this array.
    ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextCreateEx_t pfnCreateEx = [&result] {
        auto pfnCreateEx = ze_lib::context->zeDdiTable.load()->Context.pfnCreateEx;
        if( nullptr == pfnCreateEx ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateEx;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateEx( hDriver, desc, numDevices, phDevices, phContext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateEx = ze_lib::context->zeDdiTable.load()->Context.pfnCreateEx;
    if( nullptr == pfnCreateEx ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateEx( hDriver, desc, numDevices, phDevices, phContext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a context.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the context before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this context.
///     - The application must **not** call this function from simultaneous
///       threads with the same context handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeContextDestroy(
    ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Context.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hContext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Context.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hContext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns current status of the context.
/// 
/// @details
///     - The application may call this function from simultaneous threads with
///       the same context handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_SUCCESS
///         + Context is available for use.
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///         + Context is invalid; due to device lost or reset.
ze_result_t ZE_APICALL
zeContextGetStatus(
    ze_context_handle_t hContext                    ///< [in] handle of context object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextGetStatus_t pfnGetStatus = [&result] {
        auto pfnGetStatus = ze_lib::context->zeDdiTable.load()->Context.pfnGetStatus;
        if( nullptr == pfnGetStatus ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetStatus;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetStatus( hContext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetStatus = ze_lib::context->zeDdiTable.load()->Context.pfnGetStatus;
    if( nullptr == pfnGetStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetStatus( hContext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on the context.
/// 
/// @details
///     - A command queue represents a logical input stream to the device, tied
///       to a physical input stream.
///     - The application must only use the command queue for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateCommandQueue**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < desc->flags`
///         + `::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS < desc->mode`
///         + `::ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_HIGH < desc->priority`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeCommandQueueCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, hDevice, desc, phCommandQueue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phCommandQueue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue.
/// 
/// @details
///     - The application must destroy all fence handles created from the
///       command queue before destroying the command queue itself
///     - The application must ensure the device is not currently referencing
///       the command queue before it is deleted
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this command queue
///     - The application must **not** call this function from simultaneous
///       threads with the same command queue handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseCommandQueue**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeCommandQueueDestroy(
    ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hCommandQueue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hCommandQueue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Executes a command list in a command queue.
/// 
/// @details
///     - The command lists are submitted to the device in the order they are
///       received, whether from multiple calls (on the same or different
///       threads) or a single call with multiple command lists.
///     - The application must ensure the command lists are accessible by the
///       device on which the command queue was created.
///     - The application must ensure the device is not currently referencing
///       the command list since the implementation is allowed to modify the
///       contents of the command list for submission.
///     - The application must only execute command lists created with an
///       identical command queue group ordinal to the command queue.
///     - The application must use a fence created using the same command queue.
///     - The application must ensure the command queue, command list and fence
///       were created on the same context.
///     - The application must ensure the command lists being executed are not
///       immediate command lists.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkQueueSubmit
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phCommandLists`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `0 == numCommandLists`
///     - ::ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeCommandQueueExecuteCommandLists(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                    ///< to execute
    ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueExecuteCommandLists_t pfnExecuteCommandLists = [&result] {
        auto pfnExecuteCommandLists = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnExecuteCommandLists;
        if( nullptr == pfnExecuteCommandLists ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnExecuteCommandLists;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnExecuteCommandLists = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnExecuteCommandLists;
    if( nullptr == pfnExecuteCommandLists ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue by waiting on the host.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
ze_result_t ZE_APICALL
zeCommandQueueSynchronize(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then immediately returns the status of the command queue;
                                                    ///< if `UINT64_MAX`, then function will not return until complete or
                                                    ///< device is lost.
                                                    ///< Due to external dependencies, timeout may be rounded to the closest
                                                    ///< value allowed by the accuracy of those dependencies.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueSynchronize_t pfnSynchronize = [&result] {
        auto pfnSynchronize = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnSynchronize;
        if( nullptr == pfnSynchronize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSynchronize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSynchronize( hCommandQueue, timeout );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSynchronize = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnSynchronize;
    if( nullptr == pfnSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSynchronize( hCommandQueue, timeout );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the command queue group ordinal.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOrdinal`
ze_result_t ZE_APICALL
zeCommandQueueGetOrdinal(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t* pOrdinal                              ///< [out] command queue group ordinal
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueGetOrdinal_t pfnGetOrdinal = [&result] {
        auto pfnGetOrdinal = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetOrdinal;
        if( nullptr == pfnGetOrdinal ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetOrdinal;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetOrdinal( hCommandQueue, pOrdinal );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetOrdinal = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetOrdinal;
    if( nullptr == pfnGetOrdinal ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetOrdinal( hCommandQueue, pOrdinal );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the command queue index within the group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIndex`
ze_result_t ZE_APICALL
zeCommandQueueGetIndex(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t* pIndex                                ///< [out] command queue index within the group
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueGetIndex_t pfnGetIndex = [&result] {
        auto pfnGetIndex = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetIndex;
        if( nullptr == pfnGetIndex ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetIndex;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetIndex( hCommandQueue, pIndex );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIndex = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetIndex;
    if( nullptr == pfnGetIndex ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIndex( hCommandQueue, pIndex );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets command queue creation flags.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCmdQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFlags`
ze_result_t ZE_APICALL
zeCommandQueueGetFlags(
    ze_command_queue_handle_t hCmdQueue,            ///< [in] handle of the command queue
    ze_command_queue_flags_t* pFlags                ///< [out] pointer to flags used during command queue creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueGetFlags_t pfnGetFlags = [&result] {
        auto pfnGetFlags = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetFlags;
        if( nullptr == pfnGetFlags ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFlags;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFlags( hCmdQueue, pFlags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFlags = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetFlags;
    if( nullptr == pfnGetFlags ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFlags( hCmdQueue, pFlags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets command queue operation mode.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCmdQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
ze_result_t ZE_APICALL
zeCommandQueueGetMode(
    ze_command_queue_handle_t hCmdQueue,            ///< [in] handle of the command queue
    ze_command_queue_mode_t* pMode                  ///< [out] pointer to mode used during command queue creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueGetMode_t pfnGetMode = [&result] {
        auto pfnGetMode = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetMode;
        if( nullptr == pfnGetMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetMode( hCmdQueue, pMode );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMode = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetMode;
    if( nullptr == pfnGetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMode( hCmdQueue, pMode );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets command queue priority.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCmdQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pPriority`
ze_result_t ZE_APICALL
zeCommandQueueGetPriority(
    ze_command_queue_handle_t hCmdQueue,            ///< [in] handle of the command queue
    ze_command_queue_priority_t* pPriority          ///< [out] pointer to priority used during command queue creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandQueueGetPriority_t pfnGetPriority = [&result] {
        auto pfnGetPriority = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetPriority;
        if( nullptr == pfnGetPriority ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPriority;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPriority( hCmdQueue, pPriority );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPriority = ze_lib::context->zeDdiTable.load()->CommandQueue.pfnGetPriority;
    if( nullptr == pfnGetPriority ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPriority( hCmdQueue, pPriority );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the context.
/// 
/// @details
///     - A command list represents a sequence of commands for execution on a
///       command queue.
///     - The command list is created in the 'open' state.
///     - The application must only use the command list for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3f < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeCommandListCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->CommandList.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, hDevice, desc, phCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->CommandList.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an immediate command list on the context.
/// 
/// @details
///     - An immediate command list is used for low-latency submission of
///       commands.
///     - An immediate command list creates an implicit command queue.
///     - Immediate command lists must not be passed to
///       ::zeCommandQueueExecuteCommandLists.
///     - Commands appended into an immediate command list may execute
///       synchronously, by blocking until the command is complete.
///     - The command list is created in the 'open' state and never needs to be
///       closed.
///     - The application must only use the command list for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == altdesc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < altdesc->flags`
///         + `::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS < altdesc->mode`
///         + `::ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_HIGH < altdesc->priority`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeCommandListCreateImmediate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListCreateImmediate_t pfnCreateImmediate = [&result] {
        auto pfnCreateImmediate = ze_lib::context->zeDdiTable.load()->CommandList.pfnCreateImmediate;
        if( nullptr == pfnCreateImmediate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateImmediate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateImmediate = ze_lib::context->zeDdiTable.load()->CommandList.pfnCreateImmediate;
    if( nullptr == pfnCreateImmediate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the command list before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this command list.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeCommandListDestroy(
    ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->CommandList.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->CommandList.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command list; ready to be executed by a command queue.
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zeCommandListClose(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListClose_t pfnClose = [&result] {
        auto pfnClose = ze_lib::context->zeDdiTable.load()->CommandList.pfnClose;
        if( nullptr == pfnClose ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnClose;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnClose( hCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnClose = ze_lib::context->zeDdiTable.load()->CommandList.pfnClose;
    if( nullptr == pfnClose ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnClose( hCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state; ready for appending
///        commands.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the command list before it is reset
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zeCommandListReset(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListReset_t pfnReset = [&result] {
        auto pfnReset = ze_lib::context->zeDdiTable.load()->CommandList.pfnReset;
        if( nullptr == pfnReset ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReset;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReset( hCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zeDdiTable.load()->CommandList.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a memory write of the device's global timestamp value into a
///        command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The timestamp frequency can be queried from the `timerResolution`
///       member of ::ze_device_properties_t.
///     - The number of valid bits in the timestamp value can be queried from
///       the `timestampValidBits` member of ::ze_device_properties_t.
///     - The application must ensure the memory pointed to by dstptr is
///       accessible by the device on which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendWriteGlobalTimestamp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint64_t* dstptr,                               ///< [in,out] pointer to memory where timestamp value will be written; must
                                                    ///< be 8byte-aligned.
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                    ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing query
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendWriteGlobalTimestamp_t pfnAppendWriteGlobalTimestamp = [&result] {
        auto pfnAppendWriteGlobalTimestamp = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendWriteGlobalTimestamp;
        if( nullptr == pfnAppendWriteGlobalTimestamp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendWriteGlobalTimestamp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendWriteGlobalTimestamp = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendWriteGlobalTimestamp;
    if( nullptr == pfnAppendWriteGlobalTimestamp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes an immediate command list by waiting on the host for the
///        completion of all commands previously submitted to it.
/// 
/// @details
///     - The application must call this function only with command lists
///       created with ::zeCommandListCreateImmediate.
///     - Waiting on one immediate command list shall not block the concurrent
///       execution of commands appended to other
///       immediate command lists created with either a different ordinal or
///       different index.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + handle does not correspond to an immediate command list
ze_result_t ZE_APICALL
zeCommandListHostSynchronize(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the immediate command list
    uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then immediately returns the status of the immediate command list;
                                                    ///< if `UINT64_MAX`, then function will not return until complete or
                                                    ///< device is lost.
                                                    ///< Due to external dependencies, timeout may be rounded to the closest
                                                    ///< value allowed by the accuracy of those dependencies.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListHostSynchronize_t pfnHostSynchronize = [&result] {
        auto pfnHostSynchronize = ze_lib::context->zeDdiTable.load()->CommandList.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnHostSynchronize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnHostSynchronize( hCommandList, timeout );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSynchronize = ze_lib::context->zeDdiTable.load()->CommandList.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSynchronize( hCommandList, timeout );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the handle of the device on which the command list was created.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phDevice`
ze_result_t ZE_APICALL
zeCommandListGetDeviceHandle(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_device_handle_t* phDevice                    ///< [out] handle of the device on which the command list was created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListGetDeviceHandle_t pfnGetDeviceHandle = [&result] {
        auto pfnGetDeviceHandle = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetDeviceHandle;
        if( nullptr == pfnGetDeviceHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDeviceHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDeviceHandle( hCommandList, phDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDeviceHandle = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetDeviceHandle;
    if( nullptr == pfnGetDeviceHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDeviceHandle( hCommandList, phDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the handle of the context on which the command list was created.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phContext`
ze_result_t ZE_APICALL
zeCommandListGetContextHandle(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_context_handle_t* phContext                  ///< [out] handle of the context on which the command list was created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListGetContextHandle_t pfnGetContextHandle = [&result] {
        auto pfnGetContextHandle = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetContextHandle;
        if( nullptr == pfnGetContextHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetContextHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetContextHandle( hCommandList, phContext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetContextHandle = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetContextHandle;
    if( nullptr == pfnGetContextHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetContextHandle( hCommandList, phContext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the command queue group ordinal to which the command list is
///        submitted.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOrdinal`
ze_result_t ZE_APICALL
zeCommandListGetOrdinal(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t* pOrdinal                              ///< [out] command queue group ordinal to which command list is submitted
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListGetOrdinal_t pfnGetOrdinal = [&result] {
        auto pfnGetOrdinal = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetOrdinal;
        if( nullptr == pfnGetOrdinal ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetOrdinal;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetOrdinal( hCommandList, pOrdinal );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetOrdinal = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetOrdinal;
    if( nullptr == pfnGetOrdinal ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetOrdinal( hCommandList, pOrdinal );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the command queue index within the group to which the immediate
///        command list is submitted.
/// 
/// @details
///     - The application must call this function only with command lists
///       created with ::zeCommandListCreateImmediate.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandListImmediate`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIndex`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + handle does not correspond to an immediate command list
ze_result_t ZE_APICALL
zeCommandListImmediateGetIndex(
    ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
    uint32_t* pIndex                                ///< [out] command queue index within the group to which the immediate
                                                    ///< command list is submitted
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListImmediateGetIndex_t pfnImmediateGetIndex = [&result] {
        auto pfnImmediateGetIndex = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetIndex;
        if( nullptr == pfnImmediateGetIndex ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnImmediateGetIndex;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnImmediateGetIndex( hCommandListImmediate, pIndex );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnImmediateGetIndex = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetIndex;
    if( nullptr == pfnImmediateGetIndex ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnImmediateGetIndex( hCommandListImmediate, pIndex );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query whether a command list is an immediate command list.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIsImmediate`
ze_result_t ZE_APICALL
zeCommandListIsImmediate(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_bool_t* pIsImmediate                         ///< [out] Boolean indicating whether the command list is an immediate
                                                    ///< command list (true) or not (false)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListIsImmediate_t pfnIsImmediate = [&result] {
        auto pfnIsImmediate = ze_lib::context->zeDdiTable.load()->CommandList.pfnIsImmediate;
        if( nullptr == pfnIsImmediate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnIsImmediate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnIsImmediate( hCommandList, pIsImmediate );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnIsImmediate = ze_lib::context->zeDdiTable.load()->CommandList.pfnIsImmediate;
    if( nullptr == pfnIsImmediate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnIsImmediate( hCommandList, pIsImmediate );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets command list creation flags.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFlags`
ze_result_t ZE_APICALL
zeCommandListGetFlags(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_command_list_flags_t* pFlags                 ///< [out] pointer to flags used during command list creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListGetFlags_t pfnGetFlags = [&result] {
        auto pfnGetFlags = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetFlags;
        if( nullptr == pfnGetFlags ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFlags;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFlags( hCommandList, pFlags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFlags = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetFlags;
    if( nullptr == pfnGetFlags ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFlags( hCommandList, pFlags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets immediate command list command queue flags.
/// 
/// @details
///     - The application must call this function only with command lists
///       created with ::zeCommandListCreateImmediate.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFlags`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + handle does not correspond to an immediate command list
ze_result_t ZE_APICALL
zeCommandListImmediateGetFlags(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_command_queue_flags_t* pFlags                ///< [out] pointer to flags used during command list creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListImmediateGetFlags_t pfnImmediateGetFlags = [&result] {
        auto pfnImmediateGetFlags = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetFlags;
        if( nullptr == pfnImmediateGetFlags ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnImmediateGetFlags;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnImmediateGetFlags( hCommandList, pFlags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnImmediateGetFlags = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetFlags;
    if( nullptr == pfnImmediateGetFlags ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnImmediateGetFlags( hCommandList, pFlags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets immediate command list command queue mode.
/// 
/// @details
///     - The application must call this function only with command lists
///       created with ::zeCommandListCreateImmediate.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + handle does not correspond to an immediate command list
ze_result_t ZE_APICALL
zeCommandListImmediateGetMode(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_command_queue_mode_t* pMode                  ///< [out] pointer to mode used during command list creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListImmediateGetMode_t pfnImmediateGetMode = [&result] {
        auto pfnImmediateGetMode = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetMode;
        if( nullptr == pfnImmediateGetMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnImmediateGetMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnImmediateGetMode( hCommandList, pMode );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnImmediateGetMode = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetMode;
    if( nullptr == pfnImmediateGetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnImmediateGetMode( hCommandList, pMode );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets immediate command list command queue priority.
/// 
/// @details
///     - The application must call this function only with command lists
///       created with ::zeCommandListCreateImmediate.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pPriority`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + handle does not correspond to an immediate command list
ze_result_t ZE_APICALL
zeCommandListImmediateGetPriority(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_command_queue_priority_t* pPriority          ///< [out] pointer to priority used during command list creation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListImmediateGetPriority_t pfnImmediateGetPriority = [&result] {
        auto pfnImmediateGetPriority = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetPriority;
        if( nullptr == pfnImmediateGetPriority ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnImmediateGetPriority;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnImmediateGetPriority( hCommandList, pPriority );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnImmediateGetPriority = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateGetPriority;
    if( nullptr == pfnImmediateGetPriority ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnImmediateGetPriority( hCommandList, pPriority );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends an execution and global memory barrier into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - If numWaitEvents is zero, then all previous commands, enqueued on same
///       command queue, must complete prior to the execution of the barrier.
///       This is not the case when numWaitEvents is non-zero.
///     - If numWaitEvents is non-zero, then only all phWaitEvents must be
///       signaled prior to the execution of the barrier.
///     - This command blocks all following commands from beginning until the
///       execution of the barrier completes.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkCmdPipelineBarrier**
///     - clEnqueueBarrierWithWaitList
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendBarrier(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                    ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendBarrier_t pfnAppendBarrier = [&result] {
        auto pfnAppendBarrier = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendBarrier;
        if( nullptr == pfnAppendBarrier ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendBarrier;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendBarrier = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendBarrier;
    if( nullptr == pfnAppendBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a global memory ranges barrier into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - If numWaitEvents is zero, then all previous commands are completed
///       prior to the execution of the barrier.
///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
///       signaled prior to the execution of the barrier.
///     - This command blocks all following commands from beginning until the
///       execution of the barrier completes.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRangeSizes`
///         + `nullptr == pRanges`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendMemoryRangesBarrier(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numRanges,                             ///< [in] number of memory ranges
    const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
    const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                    ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryRangesBarrier_t pfnAppendMemoryRangesBarrier = [&result] {
        auto pfnAppendMemoryRangesBarrier = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryRangesBarrier;
        if( nullptr == pfnAppendMemoryRangesBarrier ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryRangesBarrier;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryRangesBarrier = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryRangesBarrier;
    if( nullptr == pfnAppendMemoryRangesBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Ensures in-bound writes to the device are globally observable.
/// 
/// @details
///     - This is a special-case system level barrier that can be used to ensure
///       global observability of writes; 
///       typically needed after a producer (e.g., NIC) performs direct writes
///       to the device's memory (e.g., Direct RDMA writes).
///       This is typically required when the memory corresponding to the writes
///       is subsequently accessed from a remote device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
ze_result_t ZE_APICALL
zeContextSystemBarrier(
    ze_context_handle_t hContext,                   ///< [in] handle of context object
    ze_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextSystemBarrier_t pfnSystemBarrier = [&result] {
        auto pfnSystemBarrier = ze_lib::context->zeDdiTable.load()->Context.pfnSystemBarrier;
        if( nullptr == pfnSystemBarrier ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSystemBarrier;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSystemBarrier( hContext, hDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSystemBarrier = ze_lib::context->zeDdiTable.load()->Context.pfnSystemBarrier;
    if( nullptr == pfnSystemBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSystemBarrier( hContext, hDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies host, device, or shared memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by dstptr and srcptr
///       is accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr and
///       srcptr as they are free to be modified by either the Host or device up
///       until execution.
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyBuffer**
///     - **clEnqueueReadBuffer**
///     - **clEnqueueWriteBuffer**
///     - **clEnqueueSVMMemcpy**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendMemoryCopy(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryCopy_t pfnAppendMemoryCopy = [&result] {
        auto pfnAppendMemoryCopy = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopy;
        if( nullptr == pfnAppendMemoryCopy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryCopy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryCopy = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopy;
    if( nullptr == pfnAppendMemoryCopy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies host, device, or shared memory with additional parameters.
/// 
/// @details
///     - The application must ensure the memory pointed to by dstptr and srcptr
///       is accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr and
///       srcptr as they are free to be modified by either the Host or device up
///       until execution.
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyBuffer**
///     - **clEnqueueReadBuffer**
///     - **clEnqueueWriteBuffer**
///     - **clEnqueueSVMMemcpy**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + an extension passed via pNext is not supported
ze_result_t ZE_APICALL
zeCommandListAppendMemoryCopyWithParameters(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    const void* pNext,                              ///< [in][optional] additional extensions passed to the function
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryCopyWithParameters_t pfnAppendMemoryCopyWithParameters = [&result] {
        auto pfnAppendMemoryCopyWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopyWithParameters;
        if( nullptr == pfnAppendMemoryCopyWithParameters ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryCopyWithParameters;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryCopyWithParameters( hCommandList, dstptr, srcptr, size, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryCopyWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopyWithParameters;
    if( nullptr == pfnAppendMemoryCopyWithParameters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryCopyWithParameters( hCommandList, dstptr, srcptr, size, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Initializes host, device, or shared memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by ptr is accessible
///       by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by ptr as it
///       is free to be modified by either the Host or device up until
///       execution.
///     - The ptr must be aligned to pattern_size
///     - The value to initialize memory to is described by the pattern and the
///       pattern size.
///     - The pattern size must be a power-of-two and less than or equal to the
///       `maxMemoryFillPatternSize` member of
///       ::ze_command_queue_group_properties_t.
///     - The size must be a multiple of pattern size.
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueFillBuffer**
///     - **clEnqueueSVMMemFill**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pattern`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///         + `size % pattern_size != 0`
ze_result_t ZE_APICALL
zeCommandListAppendMemoryFill(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    const void* pattern,                            ///< [in] pointer to value to initialize memory to
    size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initialize
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryFill_t pfnAppendMemoryFill = [&result] {
        auto pfnAppendMemoryFill = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryFill;
        if( nullptr == pfnAppendMemoryFill ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryFill;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryFill = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryFill;
    if( nullptr == pfnAppendMemoryFill ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Initializes host, device, or shared memory with additional parameters.
/// 
/// @details
///     - The application must ensure the memory pointed to by ptr is accessible
///       by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by ptr as it
///       is free to be modified by either the Host or device up until
///       execution.
///     - The ptr must be aligned to pattern_size.
///     - The value to initialize memory to is described by the pattern and the
///       pattern size.
///     - The pattern size must be a power-of-two and less than or equal to the
///       `maxMemoryFillPatternSize` member of
///       ::ze_command_queue_group_properties_t.
///     - The size must be a multiple of pattern size.
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueFillBuffer**
///     - **clEnqueueSVMMemFill**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pattern`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///         + `size % pattern_size != 0`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + an extension passed via pNext is not supported
ze_result_t ZE_APICALL
zeCommandListAppendMemoryFillWithParameters(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    const void* pattern,                            ///< [in] pointer to value to initialize memory to
    size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initialize
    const void* pNext,                              ///< [in][optional] additional extensions passed to the function
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryFillWithParameters_t pfnAppendMemoryFillWithParameters = [&result] {
        auto pfnAppendMemoryFillWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryFillWithParameters;
        if( nullptr == pfnAppendMemoryFillWithParameters ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryFillWithParameters;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryFillWithParameters( hCommandList, ptr, pattern, pattern_size, size, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryFillWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryFillWithParameters;
    if( nullptr == pfnAppendMemoryFillWithParameters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryFillWithParameters( hCommandList, ptr, pattern, pattern_size, size, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region from a 2D or 3D array of host, device, or shared
///        memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by dstptr and srcptr
///       is accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr and
///       srcptr as they are free to be modified by either the Host or device up
///       until execution.
///     - The region width, height, and depth for both src and dst must be same.
///       The origins can be different.
///     - The src and dst regions cannot be overlapping.
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///         + `nullptr == dstRegion`
///         + `nullptr == srcptr`
///         + `nullptr == srcRegion`
///     - ::ZE_RESULT_ERROR_OVERLAPPING_REGIONS
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendMemoryCopyRegion(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                              ///< [in] destination pitch in bytes
    uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                    ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                    ///< otherwise it's ignored.
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                              ///< [in] source pitch in bytes
    uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                    ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                    ///< otherwise it's ignored.
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryCopyRegion_t pfnAppendMemoryCopyRegion = [&result] {
        auto pfnAppendMemoryCopyRegion = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopyRegion;
        if( nullptr == pfnAppendMemoryCopyRegion ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryCopyRegion;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryCopyRegion = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopyRegion;
    if( nullptr == pfnAppendMemoryCopyRegion ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies host, device, or shared memory from another context.
/// 
/// @details
///     - The current active and source context must be from the same driver.
///     - The application must ensure the memory pointed to by dstptr and srcptr
///       is accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr and
///       srcptr as they are free to be modified by either the Host or device up
///       until execution.
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hContextSrc`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendMemoryCopyFromContext(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    ze_context_handle_t hContextSrc,                ///< [in] handle of source context object
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryCopyFromContext_t pfnAppendMemoryCopyFromContext = [&result] {
        auto pfnAppendMemoryCopyFromContext = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopyFromContext;
        if( nullptr == pfnAppendMemoryCopyFromContext ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryCopyFromContext;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryCopyFromContext = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryCopyFromContext;
    if( nullptr == pfnAppendMemoryCopyFromContext ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies an image.
/// 
/// @details
///     - The application must ensure the image and events are accessible by the
///       device on which the command list was created.
///     - The application must ensure the image format descriptors for both
///       source and destination images are the same.
///     - The application must ensure the command list, images and events were
///       created on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clEnqueueCopyImage**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDstImage`
///         + `nullptr == hSrcImage`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendImageCopy(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendImageCopy_t pfnAppendImageCopy = [&result] {
        auto pfnAppendImageCopy = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopy;
        if( nullptr == pfnAppendImageCopy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendImageCopy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopy = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopy;
    if( nullptr == pfnAppendImageCopy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a region of an image to another image.
/// 
/// @details
///     - The application must ensure the image and events are accessible by the
///       device on which the command list was created.
///     - The region width and height for both src and dst must be same. The
///       origins can be different.
///     - The src and dst regions cannot be overlapping.
///     - The application must ensure the image format descriptors for both
///       source and destination images are the same.
///     - The application must ensure the command list, images and events were
///       created, and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDstImage`
///         + `nullptr == hSrcImage`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_OVERLAPPING_REGIONS
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendImageCopyRegion(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendImageCopyRegion_t pfnAppendImageCopyRegion = [&result] {
        auto pfnAppendImageCopyRegion = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyRegion;
        if( nullptr == pfnAppendImageCopyRegion ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendImageCopyRegion;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyRegion = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyRegion;
    if( nullptr == pfnAppendImageCopyRegion ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies from an image to device or shared memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by dstptr is
///       accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr as
///       it is free to be modified by either the Host or device up until
///       execution.
///     - The application must ensure the image and events are accessible by the
///       device on which the command list was created.
///     - The application must ensure the image format descriptor for the source
///       image is a single-planar format.
///     - The application must ensure the command list, image and events were
///       created, and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueReadImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hSrcImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendImageCopyToMemory(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendImageCopyToMemory_t pfnAppendImageCopyToMemory = [&result] {
        auto pfnAppendImageCopyToMemory = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyToMemory;
        if( nullptr == pfnAppendImageCopyToMemory ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendImageCopyToMemory;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyToMemory = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyToMemory;
    if( nullptr == pfnAppendImageCopyToMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies to an image from device or shared memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by srcptr is
///       accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by srcptr as
///       it is free to be modified by either the Host or device up until
///       execution.
///     - The application must ensure the image and events are accessible by the
///       device on which the command list was created.
///     - The application must ensure the image format descriptor for the
///       destination image is a single-planar format.
///     - The application must ensure the command list, image and events were
///       created, and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueWriteImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDstImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendImageCopyFromMemory(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendImageCopyFromMemory_t pfnAppendImageCopyFromMemory = [&result] {
        auto pfnAppendImageCopyFromMemory = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyFromMemory;
        if( nullptr == pfnAppendImageCopyFromMemory ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendImageCopyFromMemory;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyFromMemory = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyFromMemory;
    if( nullptr == pfnAppendImageCopyFromMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Asynchronously prefetches shared memory to the device associated with
///        the specified command list
/// 
/// @details
///     - This is a hint to improve performance only and is not required for
///       correctness.
///     - Only prefetching to the device associated with the specified command
///       list is supported.
///       Prefetching to the host or to a peer device is not supported.
///     - Prefetching may not be supported for all allocation types for all devices.
///       If memory prefetching is not supported for the specified memory range
///       the prefetch hint may be ignored.
///     - Prefetching may only be supported at a device-specific granularity,
///       such as at a page boundary.
///       In this case, the memory range may be expanded such that the start and
///       end of the range satisfy granularity requirements.
///     - The application must ensure the memory pointed to by ptr is accessible
///       by the device on which the command list was created.
///     - The application must ensure the command list was created, and the
///       memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueSVMMigrateMem
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
ze_result_t ZE_APICALL
zeCommandListAppendMemoryPrefetch(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t size                                     ///< [in] size in bytes of the memory range to prefetch
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemoryPrefetch_t pfnAppendMemoryPrefetch = [&result] {
        auto pfnAppendMemoryPrefetch = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryPrefetch;
        if( nullptr == pfnAppendMemoryPrefetch ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemoryPrefetch;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemoryPrefetch( hCommandList, ptr, size );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryPrefetch = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemoryPrefetch;
    if( nullptr == pfnAppendMemoryPrefetch ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryPrefetch( hCommandList, ptr, size );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Provides advice about the use of a shared memory range
/// 
/// @details
///     - Memory advice is a performance hint only and is not required for
///       functional correctness.
///     - Memory advice can be used to override driver heuristics to explicitly
///       control shared memory behavior.
///     - Not all memory advice hints may be supported for all allocation types
///       for all devices.
///       If a memory advice hint is not supported by the device it will be ignored.
///     - Memory advice may only be supported at a device-specific granularity,
///       such as at a page boundary.
///       In this case, the memory range may be expanded such that the start and
///       end of the range satisfy granularity requirements.
///     - The application must ensure the memory pointed to by ptr is accessible
///       by the device on which the command list was created.
///     - The application must ensure the command list was created, and memory
///       was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle, and the memory was
///       allocated.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MEMORY_ADVICE_CLEAR_SYSTEM_MEMORY_PREFERRED_LOCATION < advice`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeCommandListAppendMemAdvise(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendMemAdvise_t pfnAppendMemAdvise = [&result] {
        auto pfnAppendMemAdvise = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemAdvise;
        if( nullptr == pfnAppendMemAdvise ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMemAdvise;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemAdvise = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendMemAdvise;
    if( nullptr == pfnAppendMemAdvise ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool of events on the context.
/// 
/// @details
///     - The application must only use events within the pool for the
///       device(s), or their sub-devices, which were provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `0 == desc->count`
///         + `(nullptr == phDevices) && (0 < numDevices)`
ze_result_t ZE_APICALL
zeEventPoolCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                    ///< phDevices`
    ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                    ///< have visibility to the event pool.
                                                    ///< if nullptr, then event pool is visible to all devices supported by the
                                                    ///< driver instance.
    ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->EventPool.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->EventPool.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event pool object.
/// 
/// @details
///     - The application must destroy all event handles created from the pool
///       before destroying the pool itself.
///     - The application must ensure the device is not currently referencing
///       the any event within the pool before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this event pool.
///     - The application must **not** call this function from simultaneous
///       threads with the same event pool handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeEventPoolDestroy(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->EventPool.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hEventPool );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->EventPool.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hEventPool );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an event from the pool.
/// 
/// @details
///     - An event is used to communicate fine-grain host-to-device,
///       device-to-host or device-to-device dependencies have completed.
///     - The application must ensure the location in the pool is not being used
///       by another event.
///     - The application must **not** call this function from simultaneous
///       threads with the same event pool handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateUserEvent**
///     - vkCreateEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phEvent`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < desc->signal`
///         + `0x7 < desc->wait`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeEventCreate(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->Event.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hEventPool, desc, phEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->Event.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hEventPool, desc, phEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates Counter Based Event
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phEvent`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7f < desc->flags`
///         + `0x7 < desc->signal`
///         + `0x7 < desc->wait`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + `completionValue` provided in `pNext` ::ze_event_counter_based_external_sync_allocation_desc_t or ::ze_event_counter_based_external_aggregate_storage_desc_t exceeds the value returned by ::zeDeviceGetCounterBasedEventMaxValue
ze_result_t ZE_APICALL
zeEventCounterBasedCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_event_counter_based_desc_t* desc,      ///< [in] pointer to counter based event descriptor
    ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventCounterBasedCreate_t pfnCounterBasedCreate = [&result] {
        auto pfnCounterBasedCreate = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedCreate;
        if( nullptr == pfnCounterBasedCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCounterBasedCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCounterBasedCreate( hContext, hDevice, desc, phEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCounterBasedCreate = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedCreate;
    if( nullptr == pfnCounterBasedCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCounterBasedCreate( hContext, hDevice, desc, phEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an event object.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the event before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this event.
///     - The application must **not** call this function from simultaneous
///       threads with the same event handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseEvent**
///     - vkDestroyEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeEventDestroy(
    ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Event.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Event.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets an IPC event pool handle for the specified event handle that can
///        be shared with another process.
/// 
/// @details
///     - Event pool must have been created with ::ZE_EVENT_POOL_FLAG_IPC.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phIpc`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeEventPoolGetIpcHandle(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolGetIpcHandle_t pfnGetIpcHandle = [&result] {
        auto pfnGetIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnGetIpcHandle;
        if( nullptr == pfnGetIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetIpcHandle( hEventPool, phIpc );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnGetIpcHandle;
    if( nullptr == pfnGetIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcHandle( hEventPool, phIpc );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns an IPC event pool handle to the driver
/// 
/// @details
///     - This call must be used for IPC handles previously obtained with
///       ::zeEventPoolGetIpcHandle.
///     - Upon call, driver may release any underlying resources associated with
///       the IPC handle.
///       For instance, it may close the file descriptor contained in the IPC
///       handle, if such type of handle is being used by the driver.
///     - This call does not destroy the original event pool for which the IPC
///       handle was created.
///     - This function may **not** be called from simultaneous threads with the
///       same IPC handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
ze_result_t ZE_APICALL
zeEventPoolPutIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                    ///< handle
    ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolPutIpcHandle_t pfnPutIpcHandle = [&result] {
        auto pfnPutIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnPutIpcHandle;
        if( nullptr == pfnPutIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnPutIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnPutIpcHandle( hContext, hIpc );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPutIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnPutIpcHandle;
    if( nullptr == pfnPutIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPutIpcHandle( hContext, hIpc );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC event pool handle to retrieve an event pool handle from
///        another process.
/// 
/// @details
///     - Multiple calls to this function with the same IPC handle will return
///       unique event pool handles.
///     - The event handle in this process should not be freed with
///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
///     - If the original event pool has been created for a device containing a
///       number of sub-devices, then the event pool
///       returned by this call may be used on a device containing the same
///       number of sub-devices, or on any of
///       those sub-devices.
///     - However, if the original event pool has been created for a sub-device,
///       then the event pool returned by this call
///       cannot be used on a device containing any number of sub-devices, and
///       must be used only in a sub-device. This ensures
///       functional correctness for any implementation or optimizations the
///       underlying Level Zero driver may do on
///       event pools and events.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEventPool`
ze_result_t ZE_APICALL
zeEventPoolOpenIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event pool
                                                    ///< handle
    ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event pool handle
    ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolOpenIpcHandle_t pfnOpenIpcHandle = [&result] {
        auto pfnOpenIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOpenIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOpenIpcHandle( hContext, hIpc, phEventPool );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOpenIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnOpenIpcHandle;
    if( nullptr == pfnOpenIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOpenIpcHandle( hContext, hIpc, phEventPool );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC event handle in the current process.
/// 
/// @details
///     - Closes an IPC event handle by destroying events that were opened in
///       this process using ::zeEventPoolOpenIpcHandle.
///     - The application must **not** call this function from simultaneous
///       threads with the same event pool handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
ze_result_t ZE_APICALL
zeEventPoolCloseIpcHandle(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolCloseIpcHandle_t pfnCloseIpcHandle = [&result] {
        auto pfnCloseIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCloseIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCloseIpcHandle( hEventPool );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCloseIpcHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnCloseIpcHandle;
    if( nullptr == pfnCloseIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCloseIpcHandle( hEventPool );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets an IPC counter based event handle that can be shared with another
///        process.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phIpc`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
ze_result_t ZE_APICALL
zeEventCounterBasedGetIpcHandle(
    ze_event_handle_t hEvent,                       ///< [in] handle of event object
    ze_ipc_event_counter_based_handle_t* phIpc      ///< [out] Returned IPC event handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventCounterBasedGetIpcHandle_t pfnCounterBasedGetIpcHandle = [&result] {
        auto pfnCounterBasedGetIpcHandle = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedGetIpcHandle;
        if( nullptr == pfnCounterBasedGetIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCounterBasedGetIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCounterBasedGetIpcHandle( hEvent, phIpc );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCounterBasedGetIpcHandle = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedGetIpcHandle;
    if( nullptr == pfnCounterBasedGetIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCounterBasedGetIpcHandle( hEvent, phIpc );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC event handle to retrieve from another process.
/// 
/// @details
///     - The `hContext` parameter has no requirement to match the context that
///       was used to create the event in the exporting process. Any context of
///       the importing process may be used, including the driver's default
///       context.
///     - Device association of the opened event depends on its current state at
///       the time of the call: if the event has not yet been enqueued for
///       signaling, no device is yet associated with it; if the event has been
///       enqueued for signaling, it is associated with the device performing
///       that signal operation.
///     - Any device of the importing process may signal the opened event.
///       Enqueuing a signal operation overwrites the previous tracking point.
///     - A device may wait on the opened event only if it has P2P access to the
///       device associated with the current tracking point. The set of devices
///       that may wait therefore depends on the P2P capabilities relative to
///       the signaling device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvent`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
ze_result_t ZE_APICALL
zeEventCounterBasedOpenIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event
                                                    ///< handle
    ze_ipc_event_counter_based_handle_t hIpc,       ///< [in] IPC event handle
    ze_event_handle_t* phEvent                      ///< [out] pointer handle of event object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventCounterBasedOpenIpcHandle_t pfnCounterBasedOpenIpcHandle = [&result] {
        auto pfnCounterBasedOpenIpcHandle = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedOpenIpcHandle;
        if( nullptr == pfnCounterBasedOpenIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCounterBasedOpenIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCounterBasedOpenIpcHandle( hContext, hIpc, phEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCounterBasedOpenIpcHandle = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedOpenIpcHandle;
    if( nullptr == pfnCounterBasedOpenIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCounterBasedOpenIpcHandle( hContext, hIpc, phEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC event handle in the current process.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeEventCounterBasedCloseIpcHandle(
    ze_event_handle_t hEvent                        ///< [in][release] handle of event object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventCounterBasedCloseIpcHandle_t pfnCounterBasedCloseIpcHandle = [&result] {
        auto pfnCounterBasedCloseIpcHandle = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedCloseIpcHandle;
        if( nullptr == pfnCounterBasedCloseIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCounterBasedCloseIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCounterBasedCloseIpcHandle( hEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCounterBasedCloseIpcHandle = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedCloseIpcHandle;
    if( nullptr == pfnCounterBasedCloseIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCounterBasedCloseIpcHandle( hEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns Counter Based Event completion value (counter) and its device
///        address
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == completionValue`
///         + `nullptr == deviceAddress`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
ze_result_t ZE_APICALL
zeEventCounterBasedGetDeviceAddress(
    ze_event_handle_t hEvent,                       ///< [in] handle of event object
    uint64_t* completionValue,                      ///< [in][out] completion value
    uint64_t* deviceAddress                         ///< [in][out] counter device address
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventCounterBasedGetDeviceAddress_t pfnCounterBasedGetDeviceAddress = [&result] {
        auto pfnCounterBasedGetDeviceAddress = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedGetDeviceAddress;
        if( nullptr == pfnCounterBasedGetDeviceAddress ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCounterBasedGetDeviceAddress;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCounterBasedGetDeviceAddress( hEvent, completionValue, deviceAddress );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCounterBasedGetDeviceAddress = ze_lib::context->zeDdiTable.load()->Event.pfnCounterBasedGetDeviceAddress;
    if( nullptr == pfnCounterBasedGetDeviceAddress ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCounterBasedGetDeviceAddress( hEvent, completionValue, deviceAddress );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a signal of the event from the device into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created. This requirement does not apply to
///       counter-based events.
///     - For counter-based events, the event may be signaled on any device,
///       regardless of the device used to create the event. When a
///       counter-based event is passed for signaling, it drops its previous
///       tracking point and re-associates with the device on which the command
///       list was created, tracking the new signaling point. No peer-to-peer
///       access between the previously associated device and the new signaling
///       device is required.
///     - The duration of an event created from an event pool that was created
///       using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP or
///       ::ZE_EVENT_POOL_FLAG_KERNEL_MAPPED_TIMESTAMP flags is undefined.
///       However, for consistency and orthogonality the event will report
///       correctly as signaled when used by other event API functionality.
///     - The application must ensure the command list and events were created
///       on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetUserEventStatus**
///     - vkCmdSetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeCommandListAppendSignalEvent(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendSignalEvent_t pfnAppendSignalEvent = [&result] {
        auto pfnAppendSignalEvent = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendSignalEvent;
        if( nullptr == pfnAppendSignalEvent ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendSignalEvent;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendSignalEvent( hCommandList, hEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendSignalEvent = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendSignalEvent;
    if( nullptr == pfnAppendSignalEvent ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendSignalEvent( hCommandList, hEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends wait on event(s) on the device into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - For counter-based events, the device on which the command list was
///       created must have peer-to-peer access to the device that last signaled
///       the event. Unlike signaling, waiting on a counter-based event does not
///       re-associate it with another device.
///     - The application must ensure the command list and events were created
///       on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvents`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeCommandListAppendWaitOnEvents(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                    ///< continuing
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendWaitOnEvents_t pfnAppendWaitOnEvents = [&result] {
        auto pfnAppendWaitOnEvents = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendWaitOnEvents;
        if( nullptr == pfnAppendWaitOnEvents ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendWaitOnEvents;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendWaitOnEvents = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendWaitOnEvents;
    if( nullptr == pfnAppendWaitOnEvents ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Signals a event from host.
/// 
/// @details
///     - The duration of an event created from an event pool that was created
///       using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP or
///       ::ZE_EVENT_POOL_FLAG_KERNEL_MAPPED_TIMESTAMP flags is undefined.
///       However, for consistency and orthogonality the event will report
///       correctly as signaled when used by other event API functionality.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clSetUserEventStatus
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeEventHostSignal(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventHostSignal_t pfnHostSignal = [&result] {
        auto pfnHostSignal = ze_lib::context->zeDdiTable.load()->Event.pfnHostSignal;
        if( nullptr == pfnHostSignal ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnHostSignal;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnHostSignal( hEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSignal = ze_lib::context->zeDdiTable.load()->Event.pfnHostSignal;
    if( nullptr == pfnHostSignal ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSignal( hEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on an event to be signaled.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clWaitForEvents
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
ze_result_t ZE_APICALL
zeEventHostSynchronize(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                    ///< if `UINT64_MAX`, then function will not return until complete or
                                                    ///< device is lost.
                                                    ///< Due to external dependencies, timeout may be rounded to the closest
                                                    ///< value allowed by the accuracy of those dependencies.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventHostSynchronize_t pfnHostSynchronize = [&result] {
        auto pfnHostSynchronize = ze_lib::context->zeDdiTable.load()->Event.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnHostSynchronize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnHostSynchronize( hEvent, timeout );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSynchronize = ze_lib::context->zeDdiTable.load()->Event.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSynchronize( hEvent, timeout );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an event object's status on the host.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetEventInfo**
///     - vkGetEventStatus
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + not signaled
ze_result_t ZE_APICALL
zeEventQueryStatus(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventQueryStatus_t pfnQueryStatus = [&result] {
        auto pfnQueryStatus = ze_lib::context->zeDdiTable.load()->Event.pfnQueryStatus;
        if( nullptr == pfnQueryStatus ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnQueryStatus;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnQueryStatus( hEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryStatus = ze_lib::context->zeDdiTable.load()->Event.pfnQueryStatus;
    if( nullptr == pfnQueryStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryStatus( hEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a reset of an event back to not signaled state into a command
///        list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created
///       on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkResetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeCommandListAppendEventReset(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendEventReset_t pfnAppendEventReset = [&result] {
        auto pfnAppendEventReset = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendEventReset;
        if( nullptr == pfnAppendEventReset ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendEventReset;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendEventReset( hCommandList, hEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendEventReset = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendEventReset;
    if( nullptr == pfnAppendEventReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendEventReset( hCommandList, hEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread resets an event back to not signaled state.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkResetEvent
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeEventHostReset(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventHostReset_t pfnHostReset = [&result] {
        auto pfnHostReset = ze_lib::context->zeDdiTable.load()->Event.pfnHostReset;
        if( nullptr == pfnHostReset ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnHostReset;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnHostReset( hEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostReset = ze_lib::context->zeDdiTable.load()->Event.pfnHostReset;
    if( nullptr == pfnHostReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostReset( hEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries an event's timestamp value on the host.
/// 
/// @details
///     - The application must ensure the event was created from an event pool
///       that was created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP or
///       ::ZE_EVENT_POOL_FLAG_KERNEL_MAPPED_TIMESTAMP flag.
///     - The destination memory will be unmodified if the event has not been
///       signaled.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + not signaled
ze_result_t ZE_APICALL
zeEventQueryKernelTimestamp(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventQueryKernelTimestamp_t pfnQueryKernelTimestamp = [&result] {
        auto pfnQueryKernelTimestamp = ze_lib::context->zeDdiTable.load()->Event.pfnQueryKernelTimestamp;
        if( nullptr == pfnQueryKernelTimestamp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnQueryKernelTimestamp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnQueryKernelTimestamp( hEvent, dstptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryKernelTimestamp = ze_lib::context->zeDdiTable.load()->Event.pfnQueryKernelTimestamp;
    if( nullptr == pfnQueryKernelTimestamp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryKernelTimestamp( hEvent, dstptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a query of an events' timestamp value(s) into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the events were created from an event pool
///       that was created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP or
///       ::ZE_EVENT_POOL_FLAG_KERNEL_MAPPED_TIMESTAMP flag.
///     - The application must ensure the memory pointed to by both dstptr and
///       pOffsets is accessible by the device on which the command list was
///       created.
///     - The value(s) written to the destination buffer are undefined if any
///       timestamp event has not been signaled.
///     - If pOffsets is nullptr, then multiple results will be appended
///       sequentially into memory in the same order as phEvents.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEvents`
///         + `nullptr == dstptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendQueryKernelTimestamps(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] the number of timestamp events to query
    ze_event_handle_t* phEvents,                    ///< [in][range(0, numEvents)] handles of timestamp events to query
    void* dstptr,                                   ///< [in,out] pointer to memory where ::ze_kernel_timestamp_result_t will
                                                    ///< be written; must be size-aligned.
    const size_t* pOffsets,                         ///< [in][optional][range(0, numEvents)] offset, in bytes, to write
                                                    ///< results; address must be 4byte-aligned and offsets must be
                                                    ///< size-aligned.
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                    ///< must be 0 if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing query
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendQueryKernelTimestamps_t pfnAppendQueryKernelTimestamps = [&result] {
        auto pfnAppendQueryKernelTimestamps = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendQueryKernelTimestamps;
        if( nullptr == pfnAppendQueryKernelTimestamps ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendQueryKernelTimestamps;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendQueryKernelTimestamps = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendQueryKernelTimestamps;
    if( nullptr == pfnAppendQueryKernelTimestamps ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the handle of the event pool for the event.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phEventPool`
ze_result_t ZE_APICALL
zeEventGetEventPool(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_event_pool_handle_t* phEventPool             ///< [out] handle of the event pool for the event
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventGetEventPool_t pfnGetEventPool = [&result] {
        auto pfnGetEventPool = ze_lib::context->zeDdiTable.load()->Event.pfnGetEventPool;
        if( nullptr == pfnGetEventPool ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetEventPool;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetEventPool( hEvent, phEventPool );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetEventPool = ze_lib::context->zeDdiTable.load()->Event.pfnGetEventPool;
    if( nullptr == pfnGetEventPool ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetEventPool( hEvent, phEventPool );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the signal event scope.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSignalScope`
ze_result_t ZE_APICALL
zeEventGetSignalScope(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_event_scope_flags_t* pSignalScope            ///< [out] signal event scope. This is the scope of relevant cache
                                                    ///< hierarchies that are flushed on a signal action before the event is
                                                    ///< triggered. May be 0 or a valid combination of ::ze_event_scope_flag_t.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventGetSignalScope_t pfnGetSignalScope = [&result] {
        auto pfnGetSignalScope = ze_lib::context->zeDdiTable.load()->Event.pfnGetSignalScope;
        if( nullptr == pfnGetSignalScope ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetSignalScope;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetSignalScope( hEvent, pSignalScope );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSignalScope = ze_lib::context->zeDdiTable.load()->Event.pfnGetSignalScope;
    if( nullptr == pfnGetSignalScope ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSignalScope( hEvent, pSignalScope );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the wait event scope.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pWaitScope`
ze_result_t ZE_APICALL
zeEventGetWaitScope(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_event_scope_flags_t* pWaitScope              ///< [out] wait event scope. This is the scope of relevant cache
                                                    ///< hierarchies invalidated on a wait action after the event is complete.
                                                    ///< May be 0 or a valid combination of ::ze_event_scope_flag_t.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventGetWaitScope_t pfnGetWaitScope = [&result] {
        auto pfnGetWaitScope = ze_lib::context->zeDdiTable.load()->Event.pfnGetWaitScope;
        if( nullptr == pfnGetWaitScope ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetWaitScope;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetWaitScope( hEvent, pWaitScope );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetWaitScope = ze_lib::context->zeDdiTable.load()->Event.pfnGetWaitScope;
    if( nullptr == pfnGetWaitScope ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetWaitScope( hEvent, pWaitScope );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the handle of the context on which the event pool was created.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phContext`
ze_result_t ZE_APICALL
zeEventPoolGetContextHandle(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    ze_context_handle_t* phContext                  ///< [out] handle of the context on which the event pool was created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolGetContextHandle_t pfnGetContextHandle = [&result] {
        auto pfnGetContextHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnGetContextHandle;
        if( nullptr == pfnGetContextHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetContextHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetContextHandle( hEventPool, phContext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetContextHandle = ze_lib::context->zeDdiTable.load()->EventPool.pfnGetContextHandle;
    if( nullptr == pfnGetContextHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetContextHandle( hEventPool, phContext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the creation flags used to create the event pool.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFlags`
ze_result_t ZE_APICALL
zeEventPoolGetFlags(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    ze_event_pool_flags_t* pFlags                   ///< [out] creation flags used to create the event pool; may be 0 or a
                                                    ///< valid combination of ::ze_event_pool_flag_t
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventPoolGetFlags_t pfnGetFlags = [&result] {
        auto pfnGetFlags = ze_lib::context->zeDdiTable.load()->EventPool.pfnGetFlags;
        if( nullptr == pfnGetFlags ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFlags;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFlags( hEventPool, pFlags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFlags = ze_lib::context->zeDdiTable.load()->EventPool.pfnGetFlags;
    if( nullptr == pfnGetFlags ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFlags( hEventPool, pFlags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets counter based flags of an event.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - Returns 0 for regular events created with ::zeEventCreate, and a valid
///       combination of ::ze_event_counter_based_flag_t for counter based
///       events created with ::zeEventCounterBasedCreate.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFlags`
ze_result_t ZE_APICALL
zeEventGetCounterBasedFlags(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_event_counter_based_flags_t* pFlags          ///< [out] flags used during creation of a counter based event; may be 0 or
                                                    ///< a valid combination of ::ze_event_counter_based_flag_t
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventGetCounterBasedFlags_t pfnGetCounterBasedFlags = [&result] {
        auto pfnGetCounterBasedFlags = ze_lib::context->zeDdiTable.load()->Event.pfnGetCounterBasedFlags;
        if( nullptr == pfnGetCounterBasedFlags ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetCounterBasedFlags;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetCounterBasedFlags( hEvent, pFlags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCounterBasedFlags = ze_lib::context->zeDdiTable.load()->Event.pfnGetCounterBasedFlags;
    if( nullptr == pfnGetCounterBasedFlags ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCounterBasedFlags( hEvent, pFlags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a fence for the command queue.
/// 
/// @details
///     - A fence is a heavyweight synchronization primitive used to communicate
///       to the host that command list execution has completed.
///     - The application must only use the fence for the command queue which
///       was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @remarks
///   _Analogues_
///     - **vkCreateFence**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phFence`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeFenceCreate(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFenceCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->Fence.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hCommandQueue, desc, phFence );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->Fence.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hCommandQueue, desc, phFence );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a fence object.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the fence before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this fence.
///     - The application must **not** call this function from simultaneous
///       threads with the same fence handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @remarks
///   _Analogues_
///     - **vkDestroyFence**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeFenceDestroy(
    ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFenceDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Fence.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hFence );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Fence.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hFence );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief The current host thread waits on a fence to be signaled.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkWaitForFences**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
ze_result_t ZE_APICALL
zeFenceHostSynchronize(
    ze_fence_handle_t hFence,                       ///< [in] handle of the fence
    uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                    ///< if `UINT64_MAX`, then function will not return until complete or
                                                    ///< device is lost.
                                                    ///< Due to external dependencies, timeout may be rounded to the closest
                                                    ///< value allowed by the accuracy of those dependencies.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFenceHostSynchronize_t pfnHostSynchronize = [&result] {
        auto pfnHostSynchronize = ze_lib::context->zeDdiTable.load()->Fence.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnHostSynchronize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnHostSynchronize( hFence, timeout );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSynchronize = ze_lib::context->zeDdiTable.load()->Fence.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSynchronize( hFence, timeout );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries a fence object's status.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkGetFenceStatus**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_NOT_READY
///         + not signaled
ze_result_t ZE_APICALL
zeFenceQueryStatus(
    ze_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFenceQueryStatus_t pfnQueryStatus = [&result] {
        auto pfnQueryStatus = ze_lib::context->zeDdiTable.load()->Fence.pfnQueryStatus;
        if( nullptr == pfnQueryStatus ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnQueryStatus;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnQueryStatus( hFence );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryStatus = ze_lib::context->zeDdiTable.load()->Fence.pfnQueryStatus;
    if( nullptr == pfnQueryStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryStatus( hFence );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a fence back to the not signaled state.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **vkResetFences**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
ze_result_t ZE_APICALL
zeFenceReset(
    ze_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFenceReset_t pfnReset = [&result] {
        auto pfnReset = ze_lib::context->zeDdiTable.load()->Fence.pfnReset;
        if( nullptr == pfnReset ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReset;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReset( hFence );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zeDdiTable.load()->Fence.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hFence );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves supported properties of an image.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == pImageProperties`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///         + `::ZE_IMAGE_TYPE_BUFFER < desc->type`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeImageGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Image.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hDevice, desc, pImageProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Image.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDevice, desc, pImageProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an image on the context.
/// 
/// @details
///     - The application must only use the image for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @remarks
///   _Analogues_
///     - clCreateImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phImage`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///         + `::ZE_IMAGE_TYPE_BUFFER < desc->type`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT
ze_result_t ZE_APICALL
zeImageCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->Image.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, hDevice, desc, phImage );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->Image.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phImage );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes an image object.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the image before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this image.
///     - The application must **not** call this function from simultaneous
///       threads with the same image handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeImageDestroy(
    ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Image.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hImage );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Image.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hImage );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates shared memory on the context.
/// 
/// @details
///     - Shared allocations share ownership between the host and one or more
///       devices.
///     - Shared allocations may optionally be associated with a device by
///       passing a handle to the device.
///     - Devices supporting only single-device shared access capabilities may
///       access shared memory associated with the device.
///       For these devices, ownership of the allocation is shared between the
///       host and the associated device only.
///     - Passing nullptr as the device handle does not associate the shared
///       allocation with any device.
///       For allocations with no associated device, ownership of the allocation
///       is shared between the host and all devices supporting cross-device
///       shared access capabilities.
///     - The application must only use the memory allocation for the context
///       and device, or its sub-devices, which was provided during allocation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < device_desc->flags`
///         + `0x1f < host_desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///         + Must be zero or a power-of-two
///         + `0 != (alignment & (alignment - 1))`
ze_result_t ZE_APICALL
zeMemAllocShared(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
    const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
    size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                    ///< `maxMemAllocSize` member of ::ze_device_properties_t
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                    ///< two
    ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
    void** pptr                                     ///< [out] pointer to shared allocation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemAllocShared_t pfnAllocShared = [&result] {
        auto pfnAllocShared = ze_lib::context->zeDdiTable.load()->Mem.pfnAllocShared;
        if( nullptr == pfnAllocShared ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAllocShared;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAllocShared = ze_lib::context->zeDdiTable.load()->Mem.pfnAllocShared;
    if( nullptr == pfnAllocShared ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates device memory on the context.
/// 
/// @details
///     - Device allocations are owned by a specific device.
///     - In general, a device allocation may only be accessed by the device
///       that owns it.
///     - The application must only use the memory allocation for the context
///       and device, or its sub-devices, which was provided during allocation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < device_desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///         + Must be zero or a power-of-two
///         + `0 != (alignment & (alignment - 1))`
ze_result_t ZE_APICALL
zeMemAllocDevice(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
    size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                    ///< `maxMemAllocSize` member of ::ze_device_properties_t
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                    ///< two
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void** pptr                                     ///< [out] pointer to device allocation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemAllocDevice_t pfnAllocDevice = [&result] {
        auto pfnAllocDevice = ze_lib::context->zeDdiTable.load()->Mem.pfnAllocDevice;
        if( nullptr == pfnAllocDevice ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAllocDevice;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAllocDevice = ze_lib::context->zeDdiTable.load()->Mem.pfnAllocDevice;
    if( nullptr == pfnAllocDevice ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory on the context.
/// 
/// @details
///     - Host allocations are owned by the host process.
///     - Host allocations are accessible by the host and all devices within the
///       driver's context.
///     - Host allocations are frequently used as staging areas to transfer data
///       to or from devices.
///     - The application must only use the memory allocation for the context
///       which was provided during allocation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1f < host_desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///         + Must be zero or a power-of-two
///         + `0 != (alignment & (alignment - 1))`
ze_result_t ZE_APICALL
zeMemAllocHost(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
    size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                    ///< `maxMemAllocSize` member of ::ze_device_properties_t
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                    ///< two
    void** pptr                                     ///< [out] pointer to host allocation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemAllocHost_t pfnAllocHost = [&result] {
        auto pfnAllocHost = ze_lib::context->zeDdiTable.load()->Mem.pfnAllocHost;
        if( nullptr == pfnAllocHost ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAllocHost;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAllocHost( hContext, host_desc, size, alignment, pptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAllocHost = ze_lib::context->zeDdiTable.load()->Mem.pfnAllocHost;
    if( nullptr == pfnAllocHost ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAllocHost( hContext, host_desc, size, alignment, pptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory on the
///        context.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the memory before it is freed
///     - The implementation will use the default and immediate policy to
///       schedule all Host and Device allocations associated with this memory
///       to be freed, without any safety checking. Actual freeing of memory is
///       specific to user mode driver and kernel mode driver implementation and
///       may be done asynchronously.
///     - The application must **not** call this function from simultaneous
///       threads with the same pointer.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
ze_result_t ZE_APICALL
zeMemFree(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    void* ptr                                       ///< [in][release] pointer to memory to free
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemFree_t pfnFree = [&result] {
        auto pfnFree = ze_lib::context->zeDdiTable.load()->Mem.pfnFree;
        if( nullptr == pfnFree ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnFree;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnFree( hContext, ptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFree = ze_lib::context->zeDdiTable.load()->Mem.pfnFree;
    if( nullptr == pfnFree ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFree( hContext, ptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a memory allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The application may query attributes of a memory allocation unrelated
///       to the context.
///       When this occurs, the returned allocation type will be
///       ::ZE_MEMORY_TYPE_UNKNOWN, and the returned identifier and associated
///       device is unspecified.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pMemAllocProperties`
ze_result_t ZE_APICALL
zeMemGetAllocProperties(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] memory pointer to query
    ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
    ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetAllocProperties_t pfnGetAllocProperties = [&result] {
        auto pfnGetAllocProperties = ze_lib::context->zeDdiTable.load()->Mem.pfnGetAllocProperties;
        if( nullptr == pfnGetAllocProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAllocProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAllocProperties = ze_lib::context->zeDdiTable.load()->Mem.pfnGetAllocProperties;
    if( nullptr == pfnGetAllocProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the base address and/or size of an allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_ADDRESS_NOT_FOUND
ze_result_t ZE_APICALL
zeMemGetAddressRange(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetAddressRange_t pfnGetAddressRange = [&result] {
        auto pfnGetAddressRange = ze_lib::context->zeDdiTable.load()->Mem.pfnGetAddressRange;
        if( nullptr == pfnGetAddressRange ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAddressRange;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAddressRange( hContext, ptr, pBase, pSize );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAddressRange = ze_lib::context->zeDdiTable.load()->Mem.pfnGetAddressRange;
    if( nullptr == pfnGetAddressRange ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAddressRange( hContext, ptr, pBase, pSize );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle for the specified allocation
/// 
/// @details
///     - Takes a pointer to a device memory allocation and creates an IPC
///       memory handle for exporting it for use in another process.
///     - The pointer may also be a physical memory handle cast to ``void*``
///       (i.e. ``(void*)hPhysicalMem``); in that case, the IPC handle
///       represents the physical memory object directly and no virtual address
///       mapping is required in the sending process.
///     - Only one physical memory object may be associated with a single IPC
///       handle at a time; the virtual address range passed must map to exactly
///       one physical memory object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pIpcHandle`
ze_result_t ZE_APICALL
zeMemGetIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetIpcHandle_t pfnGetIpcHandle = [&result] {
        auto pfnGetIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnGetIpcHandle;
        if( nullptr == pfnGetIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetIpcHandle( hContext, ptr, pIpcHandle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnGetIpcHandle;
    if( nullptr == pfnGetIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcHandle( hContext, ptr, pIpcHandle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle out of a file descriptor
/// 
/// @details
///     - Handle passed must be a valid file descriptor obtained with
///       ::ze_external_memory_export_fd_t via ::zeMemGetAllocProperties or
///       ::zePhysicalMemGetProperties.
///     - Returned IPC handle may contain metadata in addition to the file
///       descriptor.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIpcHandle`
ze_result_t ZE_APICALL
zeMemGetIpcHandleFromFileDescriptorExp(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    uint64_t handle,                                ///< [in] file descriptor
    ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetIpcHandleFromFileDescriptorExp_t pfnGetIpcHandleFromFileDescriptorExp = [&result] {
        auto pfnGetIpcHandleFromFileDescriptorExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnGetIpcHandleFromFileDescriptorExp;
        if( nullptr == pfnGetIpcHandleFromFileDescriptorExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetIpcHandleFromFileDescriptorExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcHandleFromFileDescriptorExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnGetIpcHandleFromFileDescriptorExp;
    if( nullptr == pfnGetIpcHandleFromFileDescriptorExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets the file descriptor contained in an IPC memory handle
/// 
/// @details
///     - IPC memory handle must be a valid handle obtained with
///       ::zeMemGetIpcHandle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pHandle`
ze_result_t ZE_APICALL
zeMemGetFileDescriptorFromIpcHandleExp(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_ipc_mem_handle_t ipcHandle,                  ///< [in] IPC memory handle
    uint64_t* pHandle                               ///< [out] Returned file descriptor
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetFileDescriptorFromIpcHandleExp_t pfnGetFileDescriptorFromIpcHandleExp = [&result] {
        auto pfnGetFileDescriptorFromIpcHandleExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnGetFileDescriptorFromIpcHandleExp;
        if( nullptr == pfnGetFileDescriptorFromIpcHandleExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFileDescriptorFromIpcHandleExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFileDescriptorFromIpcHandleExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnGetFileDescriptorFromIpcHandleExp;
    if( nullptr == pfnGetFileDescriptorFromIpcHandleExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns an IPC memory handle to the driver
/// 
/// @details
///     - This call may be used for IPC handles previously obtained with either
///       ::zeMemGetIpcHandle or with ::ze_external_memory_export_fd_t via
///       ::zeMemGetAllocProperties or ::zePhysicalMemGetProperties.
///     - Upon call, driver may release any underlying resources associated with
///       the IPC handle.
///       For instance, it may close the file descriptor contained in the IPC
///       handle, if such type of handle is being used by the driver.
///     - This call does not free the original allocation for which the IPC
///       handle was created.
///     - This function may **not** be called from simultaneous threads with the
///       same IPC handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
ze_result_t ZE_APICALL
zeMemPutIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemPutIpcHandle_t pfnPutIpcHandle = [&result] {
        auto pfnPutIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnPutIpcHandle;
        if( nullptr == pfnPutIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnPutIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnPutIpcHandle( hContext, handle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPutIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnPutIpcHandle;
    if( nullptr == pfnPutIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPutIpcHandle( hContext, handle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer on the
///        context.
/// 
/// @details
///     - Takes an IPC memory handle from a remote process and associates it
///       with a device pointer usable in this process.
///     - The 'hDevice' parameter identifies the device into which the
///       allocation is imported. If this device differs from the one where the
///       memory was originally allocated, it must have P2P access to the
///       exporting device. P2P accessibility can be verified using
///       ::zeDeviceGetP2PProperties or ::zeDeviceCanAccessPeer.
///     - The `hContext` parameter has no requirement to match the context used
///       during the original allocation in the exporting process. Any context
///       of the importing process may be used.
///     - After the handle is successfully opened, the returned pointer may be
///       accessed by `hDevice` and by any other device of the importing process
///       that has P2P connectivity to the exporting device.
///     - When the IPC handle was originally created from a physical memory
///       object (directly via a mapped virtual address), opening the handle
///       assigns a new virtual address in the importing process that maps to
///       the underlying physical memory; no prior ::zeVirtualMemReserve or
///       ::zeVirtualMemMap call is required in the importing process.
///     - The device pointer in this process should not be freed with
///       ::zeMemFree, but rather with ::zeMemCloseIpcHandle.
///     - Multiple calls to this function with the same IPC handle will return
///       unique pointers.
///     - The driver must not release the underlying physical memory until all
///       IPC handles referencing it have been closed via ::zeMemCloseIpcHandle
///       or returned via ::zeMemPutIpcHandle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pptr`
ze_result_t ZE_APICALL
zeMemOpenIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    ze_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation.
                                                    ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
    void** pptr                                     ///< [out] pointer to device allocation in this process
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemOpenIpcHandle_t pfnOpenIpcHandle = [&result] {
        auto pfnOpenIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOpenIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOpenIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnOpenIpcHandle;
    if( nullptr == pfnOpenIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::zeMemOpenIpcHandle.
///     - The application must **not** call this function from simultaneous
///       threads with the same pointer.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
ze_result_t ZE_APICALL
zeMemCloseIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr                                 ///< [in][release] pointer to device allocation in this process
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemCloseIpcHandle_t pfnCloseIpcHandle = [&result] {
        auto pfnCloseIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCloseIpcHandle;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCloseIpcHandle( hContext, ptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCloseIpcHandle = ze_lib::context->zeDdiTable.load()->Mem.pfnCloseIpcHandle;
    if( nullptr == pfnCloseIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCloseIpcHandle( hContext, ptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets atomic access attributes for a shared allocation
/// 
/// @details
///     - If the shared-allocation is owned by multiple devices (i.e. nullptr
///       was passed to ::zeMemAllocShared when creating it), then hDevice may be
///       passed to set the attributes in that specific device. If nullptr is
///       passed in hDevice, then the atomic attributes are set in all devices
///       associated with the allocation.
///     - If the atomic access attribute select is not supported by the driver,
///       ::ZE_RESULT_ERROR_INVALID_ARGUMENT is returned.
///     - The atomic access attribute may be only supported at a device-specific
///       granularity, such as at a page boundary. In this case, the memory range
///       may be expanded such that the start and end of the range satisfy granularity
///       requirements.
///     - When calling this function multiple times with different flags, only the
///       attributes from last call are honored.
///     - The application must not call this function for shared-allocations currently
///       being used by the device.
///     - The application must **not** call this function from simultaneous threads
///       with the same pointer.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7f < attr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeMemSetAtomicAccessAttributeExp(
    ze_context_handle_t hContext,                   ///< [in] handle of context
    ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    ze_memory_atomic_attr_exp_flags_t attr          ///< [in] Atomic access attributes to set for the specified range.
                                                    ///< Must be 0 (default) or a valid combination of ::ze_memory_atomic_attr_exp_flag_t.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemSetAtomicAccessAttributeExp_t pfnSetAtomicAccessAttributeExp = [&result] {
        auto pfnSetAtomicAccessAttributeExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnSetAtomicAccessAttributeExp;
        if( nullptr == pfnSetAtomicAccessAttributeExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetAtomicAccessAttributeExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetAtomicAccessAttributeExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnSetAtomicAccessAttributeExp;
    if( nullptr == pfnSetAtomicAccessAttributeExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the atomic access attributes previously set for a shared
///        allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads
///       with the same pointer.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pAttr`
ze_result_t ZE_APICALL
zeMemGetAtomicAccessAttributeExp(
    ze_context_handle_t hContext,                   ///< [in] handle of context
    ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    ze_memory_atomic_attr_exp_flags_t* pAttr        ///< [out] Atomic access attributes for the specified range
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetAtomicAccessAttributeExp_t pfnGetAtomicAccessAttributeExp = [&result] {
        auto pfnGetAtomicAccessAttributeExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnGetAtomicAccessAttributeExp;
        if( nullptr == pfnGetAtomicAccessAttributeExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAtomicAccessAttributeExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAtomicAccessAttributeExp = ze_lib::context->zeDdiTable.load()->MemExp.pfnGetAtomicAccessAttributeExp;
    if( nullptr == pfnGetAtomicAccessAttributeExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a module on the context.
/// 
/// @details
///     - Compiles the module for execution on the device.
///     - The application must only use the module for the device, or its
///       sub-devices, which was provided during creation.
///     - The module can be copied to other devices and contexts within the same
///       driver instance by using ::zeModuleGetNativeBinary.
///     - A build log can optionally be returned to the caller. The caller is
///       responsible for destroying build log using ::zeModuleBuildLogDestroy.
///     - The module descriptor constants are only supported for SPIR-V
///       specialization constants.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pInputModule`
///         + `nullptr == phModule`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MODULE_FORMAT_NATIVE < desc->format`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_NATIVE_BINARY
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `0 == desc->inputSize`
///     - ::ZE_RESULT_ERROR_MODULE_BUILD_FAILURE
ze_result_t ZE_APICALL
zeModuleCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
    ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->Module.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->Module.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module
/// 
/// @details
///     - The application must destroy all kernel handles created from the
///       module before destroying the module itself.
///     - The application must ensure the device is not currently referencing
///       the module before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this module.
///     - The application must **not** call this function from simultaneous
///       threads with the same module handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeModuleDestroy(
    ze_module_handle_t hModule                      ///< [in][release] handle of the module
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Module.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hModule );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Module.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hModule );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Dynamically link modules together that share import/export linkage
///        dependencies.
/// 
/// @details
///     - Modules support SPIR-V import and export linkage types for functions
///       and global variables. See the SPIR-V specification for linkage
///       details.
///     - Modules can have both import and export linkage.
///     - Modules that do not have any imports or exports do not need to be
///       linked.
///     - All module import requirements must be satisfied via linking before
///       kernel objects can be created from them.
///     - Modules cannot be partially linked. Unsatisfiable import dependencies
///       in the set of modules passed to ::zeModuleDynamicLink will result in 
///       ::ZE_RESULT_ERROR_MODULE_LINK_FAILURE being returned.
///     - Modules will only be linked once. A module can be used in multiple
///       link calls if it has exports but its imports will not be re-linked.
///     - Ambiguous dependencies, where multiple modules satisfy the same import
///       dependencies for a module, are not allowed.
///     - The application must ensure the modules being linked were created on
///       the same context.
///     - The application may call this function from simultaneous threads as
///       long as the import modules being linked are not the same.
///     - ModuleGetNativeBinary can be called on any module regardless of
///       whether it is linked or not.
///     - A link log can optionally be returned to the caller. The caller is
///       responsible for destroying the link log using
///       ::zeModuleBuildLogDestroy.
///     - The link log may contain a list of the unresolved import dependencies
///       if present.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phModules`
///     - ::ZE_RESULT_ERROR_MODULE_LINK_FAILURE
ze_result_t ZE_APICALL
zeModuleDynamicLink(
    uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
    ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to
                                                    ///< dynamically link together.
    ze_module_build_log_handle_t* phLinkLog         ///< [out][optional] pointer to handle of dynamic link log.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleDynamicLink_t pfnDynamicLink = [&result] {
        auto pfnDynamicLink = ze_lib::context->zeDdiTable.load()->Module.pfnDynamicLink;
        if( nullptr == pfnDynamicLink ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDynamicLink;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDynamicLink( numModules, phModules, phLinkLog );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDynamicLink = ze_lib::context->zeDdiTable.load()->Module.pfnDynamicLink;
    if( nullptr == pfnDynamicLink ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDynamicLink( numModules, phModules, phLinkLog );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module build log object
/// 
/// @details
///     - The implementation of this function may immediately free all Host
///       allocations associated with this object.
///     - The application must **not** call this function from simultaneous
///       threads with the same build log handle.
///     - The implementation of this function should be lock-free.
///     - This function can be called before or after ::zeModuleDestroy for the
///       associated module.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModuleBuildLog`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeModuleBuildLogDestroy(
    ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleBuildLogDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->ModuleBuildLog.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hModuleBuildLog );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->ModuleBuildLog.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hModuleBuildLog );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves text string for build log.
/// 
/// @details
///     - The caller can pass nullptr for pBuildLog when querying only for size.
///     - The caller must provide memory for build log.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModuleBuildLog`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t ZE_APICALL
zeModuleBuildLogGetString(
    ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleBuildLogGetString_t pfnGetString = [&result] {
        auto pfnGetString = ze_lib::context->zeDdiTable.load()->ModuleBuildLog.pfnGetString;
        if( nullptr == pfnGetString ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetString;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetString = ze_lib::context->zeDdiTable.load()->ModuleBuildLog.pfnGetString;
    if( nullptr == pfnGetString ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve native binary from Module.
/// 
/// @details
///     - The native binary output can be cached to disk and new modules can be
///       later constructed from the cached copy.
///     - The native binary will retain debugging information that is associated
///       with a module.
///     - The caller can pass nullptr for pModuleNativeBinary when querying only
///       for size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t ZE_APICALL
zeModuleGetNativeBinary(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleGetNativeBinary_t pfnGetNativeBinary = [&result] {
        auto pfnGetNativeBinary = ze_lib::context->zeDdiTable.load()->Module.pfnGetNativeBinary;
        if( nullptr == pfnGetNativeBinary ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetNativeBinary;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetNativeBinary = ze_lib::context->zeDdiTable.load()->Module.pfnGetNativeBinary;
    if( nullptr == pfnGetNativeBinary ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve global variable pointer from Module.
/// 
/// @details
///     - For modules created from SPIR-V the interpretation of `pGlobalName` is
///       described in the SPIR-V programming guide.
///     - For native modules not created from SPIR-V the interpretation of
///       `pGlobalName` is implementation defined.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pGlobalName`
///     - ::ZE_RESULT_ERROR_INVALID_GLOBAL_NAME
ze_result_t ZE_APICALL
zeModuleGetGlobalPointer(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pGlobalName,                        ///< [in] name of global variable in module
    size_t* pSize,                                  ///< [in,out][optional] size of global variable
    void** pptr                                     ///< [in,out][optional] device visible pointer
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleGetGlobalPointer_t pfnGetGlobalPointer = [&result] {
        auto pfnGetGlobalPointer = ze_lib::context->zeDdiTable.load()->Module.pfnGetGlobalPointer;
        if( nullptr == pfnGetGlobalPointer ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetGlobalPointer;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetGlobalPointer = ze_lib::context->zeDdiTable.load()->Module.pfnGetGlobalPointer;
    if( nullptr == pfnGetGlobalPointer ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve all kernel names in the module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeModuleGetKernelNames(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of names available.
                                                    ///< if count is greater than the number of names available, then the
                                                    ///< driver shall update the value with the correct number of names available.
    const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions.
                                                    ///< if count is less than the number of names available, then driver shall
                                                    ///< only retrieve that number of names.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleGetKernelNames_t pfnGetKernelNames = [&result] {
        auto pfnGetKernelNames = ze_lib::context->zeDdiTable.load()->Module.pfnGetKernelNames;
        if( nullptr == pfnGetKernelNames ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetKernelNames;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetKernelNames( hModule, pCount, pNames );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetKernelNames = ze_lib::context->zeDdiTable.load()->Module.pfnGetKernelNames;
    if( nullptr == pfnGetKernelNames ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetKernelNames( hModule, pCount, pNames );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve module properties.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pModuleProperties`
ze_result_t ZE_APICALL
zeModuleGetProperties(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Module.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hModule, pModuleProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Module.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hModule, pModuleProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create a kernel from the module.
/// 
/// @details
///     - Modules that have unresolved imports need to be dynamically linked
///       before a kernel can be created from them. (See ::zeModuleDynamicLink)
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pKernelName`
///         + `nullptr == phKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_NAME
///     - ::ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED
ze_result_t ZE_APICALL
zeKernelCreate(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
    ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->Kernel.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hModule, desc, phKernel );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->Kernel.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hModule, desc, phKernel );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a kernel object
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the kernel before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this kernel.
///     - The application must **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeKernelDestroy(
    ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Kernel.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hKernel );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Kernel.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hKernel );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve a function pointer from a module by name
/// 
/// @details
///     - The function pointer is unique for the device on which the module was
///       created.
///     - The function pointer is no longer valid if module is destroyed.
///     - The function name should only refer to callable functions within the
///       module.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFunctionName`
///         + `nullptr == pfnFunction`
///     - ::ZE_RESULT_ERROR_INVALID_FUNCTION_NAME
ze_result_t ZE_APICALL
zeModuleGetFunctionPointer(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleGetFunctionPointer_t pfnGetFunctionPointer = [&result] {
        auto pfnGetFunctionPointer = ze_lib::context->zeDdiTable.load()->Module.pfnGetFunctionPointer;
        if( nullptr == pfnGetFunctionPointer ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFunctionPointer;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFunctionPointer = ze_lib::context->zeDdiTable.load()->Module.pfnGetFunctionPointer;
    if( nullptr == pfnGetFunctionPointer ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set group size for a kernel.
/// 
/// @details
///     - The group size will be used when a ::zeCommandListAppendLaunchKernel
///       variant is called.
///     - The application must **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION
ze_result_t ZE_APICALL
zeKernelSetGroupSize(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSetGroupSize_t pfnSetGroupSize = [&result] {
        auto pfnSetGroupSize = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetGroupSize;
        if( nullptr == pfnSetGroupSize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetGroupSize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetGroupSize = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetGroupSize;
    if( nullptr == pfnSetGroupSize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested group size for a kernel given a global size for each
///        dimension.
/// 
/// @details
///     - This function ignores the group size that is set using
///       ::zeKernelSetGroupSize.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == groupSizeX`
///         + `nullptr == groupSizeY`
///         + `nullptr == groupSizeZ`
///     - ::ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION
ze_result_t ZE_APICALL
zeKernelSuggestGroupSize(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSuggestGroupSize_t pfnSuggestGroupSize = [&result] {
        auto pfnSuggestGroupSize = ze_lib::context->zeDdiTable.load()->Kernel.pfnSuggestGroupSize;
        if( nullptr == pfnSuggestGroupSize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSuggestGroupSize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSuggestGroupSize = ze_lib::context->zeDdiTable.load()->Kernel.pfnSuggestGroupSize;
    if( nullptr == pfnSuggestGroupSize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested max group count for a cooperative kernel.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - Applications are recommended to use ::zeKernelSuggestGroupSize and
///       ::zeKernelSetGroupSize first before calling this function and
///       launching cooperative kernels. Otherwise, implementation may return
///       ::ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == totalGroupCount`
ze_result_t ZE_APICALL
zeKernelSuggestMaxCooperativeGroupCount(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t* totalGroupCount                       ///< [out] recommended total group count.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSuggestMaxCooperativeGroupCount_t pfnSuggestMaxCooperativeGroupCount = [&result] {
        auto pfnSuggestMaxCooperativeGroupCount = ze_lib::context->zeDdiTable.load()->Kernel.pfnSuggestMaxCooperativeGroupCount;
        if( nullptr == pfnSuggestMaxCooperativeGroupCount ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSuggestMaxCooperativeGroupCount;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSuggestMaxCooperativeGroupCount = ze_lib::context->zeDdiTable.load()->Kernel.pfnSuggestMaxCooperativeGroupCount;
    if( nullptr == pfnSuggestMaxCooperativeGroupCount ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set kernel argument for a kernel.
/// 
/// @details
///     - The argument values will be used when a
///       ::zeCommandListAppendLaunchKernel variant is called.
///     - The application must **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
///     - If argument is SLM (size), then SLM size in bytes for this resource is
///       provided as argument size and argument value is null
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT
ze_result_t ZE_APICALL
zeKernelSetArgumentValue(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSetArgumentValue_t pfnSetArgumentValue = [&result] {
        auto pfnSetArgumentValue = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetArgumentValue;
        if( nullptr == pfnSetArgumentValue ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetArgumentValue;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetArgumentValue = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetArgumentValue;
    if( nullptr == pfnSetArgumentValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets kernel indirect access flags.
/// 
/// @details
///     - The application should specify which allocations will be indirectly
///       accessed by the kernel to allow driver to optimize which allocations
///       are made resident
///     - This function may **not** be called from simultaneous threads with the
///       same Kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeKernelSetIndirectAccess(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSetIndirectAccess_t pfnSetIndirectAccess = [&result] {
        auto pfnSetIndirectAccess = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetIndirectAccess;
        if( nullptr == pfnSetIndirectAccess ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetIndirectAccess;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetIndirectAccess( hKernel, flags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetIndirectAccess = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetIndirectAccess;
    if( nullptr == pfnSetIndirectAccess ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetIndirectAccess( hKernel, flags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve kernel indirect access flags.
/// 
/// @details
///     - This function may be called from simultaneous threads with the same
///       Kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFlags`
ze_result_t ZE_APICALL
zeKernelGetIndirectAccess(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelGetIndirectAccess_t pfnGetIndirectAccess = [&result] {
        auto pfnGetIndirectAccess = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetIndirectAccess;
        if( nullptr == pfnGetIndirectAccess ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetIndirectAccess;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetIndirectAccess( hKernel, pFlags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIndirectAccess = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetIndirectAccess;
    if( nullptr == pfnGetIndirectAccess ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIndirectAccess( hKernel, pFlags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve all declared kernel attributes (i.e. can be specified with
///        __attribute__ in runtime language).
/// 
/// @details
///     - This function may be called from simultaneous threads with the same
///       Kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t ZE_APICALL
zeKernelGetSourceAttributes(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes, including
                                                    ///< null-terminating character.
    char** pString                                  ///< [in,out][optional] pointer to application-managed character array
                                                    ///< (string data).
                                                    ///< If NULL, the string length of the kernel source attributes, including
                                                    ///< a null-terminating character, is returned in pSize. Otherwise, pString
                                                    ///< must point to valid application memory that is greater than or equal
                                                    ///< to *pSize bytes in length, and on return the pointed-to string will
                                                    ///< contain a space-separated list of kernel source attributes. Note: This
                                                    ///< API was originally intended to ship with a char *pString, however this
                                                    ///< typo was introduced. Thus the API has to stay this way for backwards
                                                    ///< compatible reasons. It can be corrected in v2.0. Suggestion is to
                                                    ///< create your own char *pString and then pass to this API with &pString.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelGetSourceAttributes_t pfnGetSourceAttributes = [&result] {
        auto pfnGetSourceAttributes = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetSourceAttributes;
        if( nullptr == pfnGetSourceAttributes ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetSourceAttributes;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetSourceAttributes( hKernel, pSize, pString );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSourceAttributes = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetSourceAttributes;
    if( nullptr == pfnGetSourceAttributes ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSourceAttributes( hKernel, pSize, pString );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred cache configuration.
/// 
/// @details
///     - The cache configuration will be used when a
///       ::zeCommandListAppendLaunchKernel variant is called.
///     - The application must **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
ze_result_t ZE_APICALL
zeKernelSetCacheConfig(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                    ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSetCacheConfig_t pfnSetCacheConfig = [&result] {
        auto pfnSetCacheConfig = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetCacheConfig;
        if( nullptr == pfnSetCacheConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetCacheConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetCacheConfig( hKernel, flags );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetCacheConfig = ze_lib::context->zeDdiTable.load()->Kernel.pfnSetCacheConfig;
    if( nullptr == pfnSetCacheConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetCacheConfig( hKernel, flags );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve kernel properties.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pKernelProperties`
ze_result_t ZE_APICALL
zeKernelGetProperties(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hKernel, pKernelProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hKernel, pKernelProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve kernel name from Kernel.
/// 
/// @details
///     - The caller can pass nullptr for pName when querying only for size.
///     - The implementation will copy the kernel name into a buffer supplied by
///       the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t ZE_APICALL
zeKernelGetName(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                    ///< bytes.
    char* pName                                     ///< [in,out][optional] char pointer to kernel name.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelGetName_t pfnGetName = [&result] {
        auto pfnGetName = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetName;
        if( nullptr == pfnGetName ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetName;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetName( hKernel, pSize, pName );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetName = ze_lib::context->zeDdiTable.load()->Kernel.pfnGetName;
    if( nullptr == pfnGetName ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetName( hKernel, pSize, pName );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups.
/// 
/// @details
///     - The application must ensure the kernel and events are accessible by
///       the device on which the command list was created.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - The application must ensure the command list, kernel and events were
///       created on the same context.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLaunchFuncArgs`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendLaunchKernel(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendLaunchKernel_t pfnAppendLaunchKernel = [&result] {
        auto pfnAppendLaunchKernel = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernel;
        if( nullptr == pfnAppendLaunchKernel ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendLaunchKernel;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchKernel = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernel;
    if( nullptr == pfnAppendLaunchKernel ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups and allow to pass
///        additional parameters.
/// 
/// @details
///     - The application must ensure the kernel and events are accessible by
///       the device on which the command list was created.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - The application must ensure the command list, kernel and events were
///       created on the same context.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
///     - This function allows to pass additional parameters in the form of
///       `${x}_base_desc_t`
///     - This function can replace ::zeCommandListAppendLaunchCooperativeKernel
///       with additional parameter
///       `${x}_command_list_append_launch_kernel_param_cooperative_desc_t`
///     - This function supports both immediate and regular command lists.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pGroupCounts`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + when passed additional parameters are invalid or incompatible with the device or command list
ze_result_t ZE_APICALL
zeCommandListAppendLaunchKernelWithParameters(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t* pGroupCounts,           ///< [in] thread group launch arguments
    const void * pNext,                             ///< [in][optional] additional parameters passed to the function
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendLaunchKernelWithParameters_t pfnAppendLaunchKernelWithParameters = [&result] {
        auto pfnAppendLaunchKernelWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernelWithParameters;
        if( nullptr == pfnAppendLaunchKernelWithParameters ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendLaunchKernelWithParameters;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendLaunchKernelWithParameters( hCommandList, hKernel, pGroupCounts, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchKernelWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernelWithParameters;
    if( nullptr == pfnAppendLaunchKernelWithParameters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchKernelWithParameters( hCommandList, hKernel, pGroupCounts, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups with specifying work group
///        size and all kernel arguments and allow to pass additional extensions.
/// 
/// @details
///     - The application must ensure the kernel and events are accessible by
///       the device on which the command list was created.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - The application must ensure the command list, kernel and events were
///       created on the same context.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
///     - This function supports both immediate and regular command lists.
///     - This function changes kernel state as if separate
///       ${x}KernelSetGroupSize and ${x}KernelSetArgumentValue functions were
///       called.
///     - This function allows to pass additional extensions in the form of
///       `${x}_base_desc_t`
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + when passed additional extensions are invalid or incompatible with the device or command list
///     - ::ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION - "as per ${x}KernelSetGroupSize"
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT - "as per ${x}KernelSetArgumentValue"
ze_result_t ZE_APICALL
zeCommandListAppendLaunchKernelWithArguments(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t groupCounts,             ///< [in] thread group counts
    const ze_group_size_t groupSizes,               ///< [in] thread group sizes
    void ** pArguments,                             ///< [in]pointer to an array of pointers
    const void * pNext,                             ///< [in][optional] additional extensions passed to the function
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendLaunchKernelWithArguments_t pfnAppendLaunchKernelWithArguments = [&result] {
        auto pfnAppendLaunchKernelWithArguments = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernelWithArguments;
        if( nullptr == pfnAppendLaunchKernelWithArguments ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendLaunchKernelWithArguments;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendLaunchKernelWithArguments( hCommandList, hKernel, groupCounts, groupSizes, pArguments, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchKernelWithArguments = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernelWithArguments;
    if( nullptr == pfnAppendLaunchKernelWithArguments ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchKernelWithArguments( hCommandList, hKernel, groupCounts, groupSizes, pArguments, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel cooperatively over one or more work groups.
/// 
/// @details
///     - The application must ensure the kernel and events are accessible by
///       the device on which the command list was created.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - This may only be used for a command list that are submitted to command
///       queue with cooperative flag set.
///     - The application must ensure the command list, kernel and events were
///       created on the same context.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
///     - Use ::zeKernelSuggestMaxCooperativeGroupCount to recommend max group
///       count for device for cooperative functions that device supports.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLaunchFuncArgs`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendLaunchCooperativeKernel(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendLaunchCooperativeKernel_t pfnAppendLaunchCooperativeKernel = [&result] {
        auto pfnAppendLaunchCooperativeKernel = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchCooperativeKernel;
        if( nullptr == pfnAppendLaunchCooperativeKernel ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendLaunchCooperativeKernel;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchCooperativeKernel = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchCooperativeKernel;
    if( nullptr == pfnAppendLaunchCooperativeKernel ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups using indirect arguments.
/// 
/// @details
///     - The application must ensure the kernel and events are accessible by
///       the device on which the command list was created.
///     - The application must ensure the launch arguments are visible to the
///       device on which the command list was created.
///     - The implementation must not access the contents of the launch
///       arguments as they are free to be modified by either the Host or device
///       up until execution.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - The application must ensure the command list, kernel and events were
///       created, and the memory was allocated, on the same context.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLaunchArgumentsBuffer`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendLaunchKernelIndirect(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                    ///< arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendLaunchKernelIndirect_t pfnAppendLaunchKernelIndirect = [&result] {
        auto pfnAppendLaunchKernelIndirect = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernelIndirect;
        if( nullptr == pfnAppendLaunchKernelIndirect ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendLaunchKernelIndirect;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchKernelIndirect = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchKernelIndirect;
    if( nullptr == pfnAppendLaunchKernelIndirect ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch multiple kernels over one or more work groups using an array of
///        indirect arguments.
/// 
/// @details
///     - The application must ensure the kernel and events are accessible by
///       the device on which the command list was created.
///     - The application must ensure the array of launch arguments and count
///       buffer are visible to the device on which the command list was
///       created.
///     - The implementation must not access the contents of the array of launch
///       arguments or count buffer as they are free to be modified by either
///       the Host or device up until execution.
///     - This may **only** be called for a command list created with command
///       queue group ordinal that supports compute.
///     - The application must enusre the command list, kernel and events were
///       created, and the memory was allocated, on the same context.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phKernels`
///         + `nullptr == pCountBuffer`
///         + `nullptr == pLaunchArgumentsBuffer`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendLaunchMultipleKernelsIndirect(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
    ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
    const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of kernels to launch; value must be less than or equal to
                                                    ///< numKernels
    const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                    ///< a contiguous array of thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendLaunchMultipleKernelsIndirect_t pfnAppendLaunchMultipleKernelsIndirect = [&result] {
        auto pfnAppendLaunchMultipleKernelsIndirect = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchMultipleKernelsIndirect;
        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendLaunchMultipleKernelsIndirect;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchMultipleKernelsIndirect = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendLaunchMultipleKernelsIndirect;
    if( nullptr == pfnAppendLaunchMultipleKernelsIndirect ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Makes memory resident for the device.
/// 
/// @details
///     - The application must ensure the memory is resident before being
///       referenced by the device
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + ptr is not recognized by the implementation
ze_result_t ZE_APICALL
zeContextMakeMemoryResident(
    ze_context_handle_t hContext,                   ///< [in] handle of context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextMakeMemoryResident_t pfnMakeMemoryResident = [&result] {
        auto pfnMakeMemoryResident = ze_lib::context->zeDdiTable.load()->Context.pfnMakeMemoryResident;
        if( nullptr == pfnMakeMemoryResident ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnMakeMemoryResident;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnMakeMemoryResident( hContext, hDevice, ptr, size );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnMakeMemoryResident = ze_lib::context->zeDdiTable.load()->Context.pfnMakeMemoryResident;
    if( nullptr == pfnMakeMemoryResident ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnMakeMemoryResident( hContext, hDevice, ptr, size );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows memory to be evicted from the device.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the memory before it is evicted
///     - The application may free the memory without evicting; the memory is
///       implicitly evicted when freed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
ze_result_t ZE_APICALL
zeContextEvictMemory(
    ze_context_handle_t hContext,                   ///< [in] handle of context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextEvictMemory_t pfnEvictMemory = [&result] {
        auto pfnEvictMemory = ze_lib::context->zeDdiTable.load()->Context.pfnEvictMemory;
        if( nullptr == pfnEvictMemory ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEvictMemory;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEvictMemory( hContext, hDevice, ptr, size );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEvictMemory = ze_lib::context->zeDdiTable.load()->Context.pfnEvictMemory;
    if( nullptr == pfnEvictMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEvictMemory( hContext, hDevice, ptr, size );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Makes image resident for the device.
/// 
/// @details
///     - The application must ensure the image is resident before being
///       referenced by the device
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///         + `nullptr == hImage`
ze_result_t ZE_APICALL
zeContextMakeImageResident(
    ze_context_handle_t hContext,                   ///< [in] handle of context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextMakeImageResident_t pfnMakeImageResident = [&result] {
        auto pfnMakeImageResident = ze_lib::context->zeDdiTable.load()->Context.pfnMakeImageResident;
        if( nullptr == pfnMakeImageResident ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnMakeImageResident;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnMakeImageResident( hContext, hDevice, hImage );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnMakeImageResident = ze_lib::context->zeDdiTable.load()->Context.pfnMakeImageResident;
    if( nullptr == pfnMakeImageResident ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnMakeImageResident( hContext, hDevice, hImage );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Allows image to be evicted from the device.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the image before it is evicted
///     - The application may destroy the image without evicting; the image is
///       implicitly evicted when destroyed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///         + `nullptr == hImage`
ze_result_t ZE_APICALL
zeContextEvictImage(
    ze_context_handle_t hContext,                   ///< [in] handle of context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnContextEvictImage_t pfnEvictImage = [&result] {
        auto pfnEvictImage = ze_lib::context->zeDdiTable.load()->Context.pfnEvictImage;
        if( nullptr == pfnEvictImage ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEvictImage;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEvictImage( hContext, hDevice, hImage );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEvictImage = ze_lib::context->zeDdiTable.load()->Context.pfnEvictImage;
    if( nullptr == pfnEvictImage ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEvictImage( hContext, hDevice, hImage );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates sampler on the context.
/// 
/// @details
///     - The application must only use the sampler for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phSampler`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_SAMPLER_ADDRESS_MODE_MIRROR < desc->addressMode`
///         + `::ZE_SAMPLER_FILTER_MODE_LINEAR < desc->filterMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeSamplerCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
    ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnSamplerCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->Sampler.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, hDevice, desc, phSampler );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->Sampler.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phSampler );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys sampler object
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the sampler before it is deleted.
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this sampler.
///     - The application must **not** call this function from simultaneous
///       threads with the same sampler handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSampler`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeSamplerDestroy(
    ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnSamplerDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Sampler.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hSampler );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->Sampler.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hSampler );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reserves pages in virtual address space.
/// 
/// @details
///     - The application must only use the memory allocation on the context for
///       which it was created.
///     - The starting address and size must be page aligned. See
///       ::zeVirtualMemQueryPageSize.
///     - If pStart is not null then implementation will attempt to reserve
///       starting from that address. If not available then will find another
///       suitable starting address.
///     - The application may call this function from simultaneous threads.
///     - The access attributes will default to none to indicate reservation is
///       inaccessible.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
ze_result_t ZE_APICALL
zeVirtualMemReserve(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* pStart,                             ///< [in][optional] pointer to start of region to reserve. If nullptr then
                                                    ///< implementation will choose a start address.
    size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
    void** pptr                                     ///< [out] pointer to virtual reservation.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnVirtualMemReserve_t pfnReserve = [&result] {
        auto pfnReserve = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnReserve;
        if( nullptr == pfnReserve ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReserve;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReserve( hContext, pStart, size, pptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReserve = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnReserve;
    if( nullptr == pfnReserve ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReserve( hContext, pStart, size, pptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Free pages in a reserved virtual address range.
/// 
/// @details
///     - Any existing virtual mappings for the range will be unmapped.
///     - Physical allocations objects that were mapped to this range will not
///       be destroyed. These need to be destroyed explicitly.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
ze_result_t ZE_APICALL
zeVirtualMemFree(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] pointer to start of region to free.
    size_t size                                     ///< [in] size in bytes to free; must be page aligned.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnVirtualMemFree_t pfnFree = [&result] {
        auto pfnFree = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnFree;
        if( nullptr == pfnFree ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnFree;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnFree( hContext, ptr, size );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFree = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnFree;
    if( nullptr == pfnFree ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFree( hContext, ptr, size );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries page size to use for aligning virtual memory reservations and
///        physical memory allocations.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pagesize`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
ze_result_t ZE_APICALL
zeVirtualMemQueryPageSize(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    size_t size,                                    ///< [in] unaligned allocation size in bytes
    size_t* pagesize                                ///< [out] pointer to page size to use for start address and size
                                                    ///< alignments.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnVirtualMemQueryPageSize_t pfnQueryPageSize = [&result] {
        auto pfnQueryPageSize = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnQueryPageSize;
        if( nullptr == pfnQueryPageSize ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnQueryPageSize;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnQueryPageSize( hContext, hDevice, size, pagesize );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryPageSize = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnQueryPageSize;
    if( nullptr == pfnQueryPageSize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryPageSize( hContext, hDevice, size, pagesize );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves memory properties of the physical memory object.
/// 
/// @details
///     - The application must only use the physical memory object on the
///       context for which it was created.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hPhysicalMem`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemProperties`
ze_result_t ZE_APICALL
zePhysicalMemGetProperties(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_physical_mem_handle_t hPhysicalMem,          ///< [in] handle of the physical memory object
    ze_physical_mem_properties_t* pMemProperties    ///< [in,out] pointer to physical memory properties structure.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnPhysicalMemGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->PhysicalMem.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hContext, hPhysicalMem, pMemProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.load()->PhysicalMem.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hContext, hPhysicalMem, pMemProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a physical memory object for the context.
/// 
/// @details
///     - The application must only use the physical memory object on the
///       context for which it was created.
///     - The size must be page aligned. For host memory, the operating system
///       page size should be used. For device memory, see
///       ::zeVirtualMemQueryPageSize.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phPhysicalMemory`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == desc->size`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
ze_result_t ZE_APICALL
zePhysicalMemCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object, can be `nullptr` if creating
                                                    ///< physical host memory.
    ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
    ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnPhysicalMemCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zeDdiTable.load()->PhysicalMem.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, hDevice, desc, phPhysicalMemory );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.load()->PhysicalMem.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phPhysicalMemory );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a physical memory object.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the physical memory object before it is deleted
///     - The application must **not** call this function from simultaneous
///       threads with the same physical memory handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hPhysicalMemory`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zePhysicalMemDestroy(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnPhysicalMemDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zeDdiTable.load()->PhysicalMem.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hContext, hPhysicalMemory );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.load()->PhysicalMem.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hContext, hPhysicalMemory );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Maps pages in virtual address space to pages from physical memory
///        object.
/// 
/// @details
///     - The virtual address range must have been reserved using
///       ::zeVirtualMemReserve.
///     - The application must only use the mapped memory allocation on the
///       context for which it was created.
///     - The virtual start address and size must be page aligned. See
///       ::zeVirtualMemQueryPageSize.
///     - The application should use, for the starting address and size, the
///       same size alignment used for the physical allocation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hPhysicalMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MEMORY_ACCESS_ATTRIBUTE_READONLY < access`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
ze_result_t ZE_APICALL
zeVirtualMemMap(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] pointer to start of virtual address range to map.
    size_t size,                                    ///< [in] size in bytes of virtual address range to map; must be page
                                                    ///< aligned.
    ze_physical_mem_handle_t hPhysicalMemory,       ///< [in] handle to physical memory object.
    size_t offset,                                  ///< [in] offset into physical memory allocation object; must be page
                                                    ///< aligned.
    ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                    ///< range.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnVirtualMemMap_t pfnMap = [&result] {
        auto pfnMap = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnMap;
        if( nullptr == pfnMap ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnMap;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnMap = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnMap;
    if( nullptr == pfnMap ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Unmaps pages in virtual address space from pages from a physical
///        memory object.
/// 
/// @details
///     - The page access attributes for virtual address range will revert back
///       to none.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///         + Address must be page aligned
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///         + Size must be page aligned
ze_result_t ZE_APICALL
zeVirtualMemUnmap(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] pointer to start of region to unmap.
    size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnVirtualMemUnmap_t pfnUnmap = [&result] {
        auto pfnUnmap = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnUnmap;
        if( nullptr == pfnUnmap ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnUnmap;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnUnmap( hContext, ptr, size );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnUnmap = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnUnmap;
    if( nullptr == pfnUnmap ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnUnmap( hContext, ptr, size );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set memory access attributes for a virtual address range.
/// 
/// @details
///     - This function may be called from simultaneous threads with the same
///       function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MEMORY_ACCESS_ATTRIBUTE_READONLY < access`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///         + Address must be page aligned
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///         + Size must be page aligned
ze_result_t ZE_APICALL
zeVirtualMemSetAccessAttribute(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
    size_t size,                                    ///< [in] size in bytes; must be page aligned.
    ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                    ///< range.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnVirtualMemSetAccessAttribute_t pfnSetAccessAttribute = [&result] {
        auto pfnSetAccessAttribute = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnSetAccessAttribute;
        if( nullptr == pfnSetAccessAttribute ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetAccessAttribute;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetAccessAttribute( hContext, ptr, size, access );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetAccessAttribute = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnSetAccessAttribute;
    if( nullptr == pfnSetAccessAttribute ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetAccessAttribute( hContext, ptr, size, access );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory access attribute for a virtual address range.
/// 
/// @details
///     - If size and outSize are equal then the pages in the specified virtual
///       address range have the same access attributes.
///     - This function may be called from simultaneous threads with the same
///       function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == access`
///         + `nullptr == outSize`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///         + Address must be page aligned
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == size`
///         + Size must be page aligned
ze_result_t ZE_APICALL
zeVirtualMemGetAccessAttribute(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
    size_t size,                                    ///< [in] size in bytes; must be page aligned.
    ze_memory_access_attribute_t* access,           ///< [out] query result for page access attribute.
    size_t* outSize                                 ///< [out] query result for size of virtual address range, starting at ptr,
                                                    ///< that shares same access attribute.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnVirtualMemGetAccessAttribute_t pfnGetAccessAttribute = [&result] {
        auto pfnGetAccessAttribute = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnGetAccessAttribute;
        if( nullptr == pfnGetAccessAttribute ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAccessAttribute;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAccessAttribute( hContext, ptr, size, access, outSize );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAccessAttribute = ze_lib::context->zeDdiTable.load()->VirtualMem.pfnGetAccessAttribute;
    if( nullptr == pfnGetAccessAttribute ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAccessAttribute( hContext, ptr, size, access, outSize );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set global work offset for a kernel.
/// 
/// @details
///     - The global work offset will be used when a
///       ::zeCommandListAppendLaunchKernel() variant is called.
///     - The application must **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
ze_result_t ZE_APICALL
zeKernelSetGlobalOffsetExp(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t offsetX,                               ///< [in] global offset for X dimension to use for this kernel
    uint32_t offsetY,                               ///< [in] global offset for Y dimension to use for this kernel
    uint32_t offsetZ                                ///< [in] global offset for Z dimension to use for this kernel
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSetGlobalOffsetExp_t pfnSetGlobalOffsetExp = [&result] {
        auto pfnSetGlobalOffsetExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnSetGlobalOffsetExp;
        if( nullptr == pfnSetGlobalOffsetExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetGlobalOffsetExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetGlobalOffsetExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnSetGlobalOffsetExp;
    if( nullptr == pfnSetGlobalOffsetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves kernel binary program data (ISA GEN format).
/// 
/// @details
///     - A valid kernel handle must be created with ::zeKernelCreate.
///     - Returns Intel Graphics Assembly (GEN ISA) format binary program data
///       for kernel handle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
///         + `nullptr == pKernelBinary`
ze_result_t ZE_APICALL
zeKernelGetBinaryExp(
    ze_kernel_handle_t hKernel,                     ///< [in] Kernel handle.
    size_t* pSize,                                  ///< [in,out] pointer to variable with size of GEN ISA binary.
    uint8_t* pKernelBinary                          ///< [in,out] pointer to storage area for GEN ISA binary function.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelGetBinaryExp_t pfnGetBinaryExp = [&result] {
        auto pfnGetBinaryExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnGetBinaryExp;
        if( nullptr == pfnGetBinaryExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetBinaryExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetBinaryExp( hKernel, pSize, pKernelBinary );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetBinaryExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnGetBinaryExp;
    if( nullptr == pfnGetBinaryExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetBinaryExp( hKernel, pSize, pKernelBinary );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Import an external semaphore
/// 
/// @details
///     - Imports an external semaphore.
///     - This function may be called from simultaneous threads with the same
///       device handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phSemaphore`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1ff < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeDeviceImportExternalSemaphoreExt(
    ze_device_handle_t hDevice,                     ///< [in] The device handle.
    const ze_external_semaphore_ext_desc_t* desc,   ///< [in] The pointer to external semaphore descriptor.
    ze_external_semaphore_ext_handle_t* phSemaphore ///< [out] The handle of the external semaphore imported.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceImportExternalSemaphoreExt_t pfnImportExternalSemaphoreExt = [&result] {
        auto pfnImportExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->Device.pfnImportExternalSemaphoreExt;
        if( nullptr == pfnImportExternalSemaphoreExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnImportExternalSemaphoreExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnImportExternalSemaphoreExt( hDevice, desc, phSemaphore );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnImportExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->Device.pfnImportExternalSemaphoreExt;
    if( nullptr == pfnImportExternalSemaphoreExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnImportExternalSemaphoreExt( hDevice, desc, phSemaphore );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Release an external semaphore
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the semaphore before it is released.
///     - The application must **not** call this function from simultaneous
///       threads with the same semaphore handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSemaphore`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeDeviceReleaseExternalSemaphoreExt(
    ze_external_semaphore_ext_handle_t hSemaphore   ///< [in] The handle of the external semaphore.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceReleaseExternalSemaphoreExt_t pfnReleaseExternalSemaphoreExt = [&result] {
        auto pfnReleaseExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->Device.pfnReleaseExternalSemaphoreExt;
        if( nullptr == pfnReleaseExternalSemaphoreExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReleaseExternalSemaphoreExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReleaseExternalSemaphoreExt( hSemaphore );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReleaseExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->Device.pfnReleaseExternalSemaphoreExt;
    if( nullptr == pfnReleaseExternalSemaphoreExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReleaseExternalSemaphoreExt( hSemaphore );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Signal an external semaphore
/// 
/// @details
///     - Signals an external semaphore.
///     - This function must only be used with an immediate command list.
///     - This function may be called from simultaneous threads with the same
///       command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phSemaphores`
///         + `nullptr == signalParams`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///         + `(nullptr == phSemaphores) && (0 < numSemaphores)`
///         + `(nullptr == signalParams) && (0 < numSemaphores)`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + Commandlist handle does not correspond to an immediate command list
ze_result_t ZE_APICALL
zeCommandListAppendSignalExternalSemaphoreExt(
    ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
    uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
    ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in][range(0, numSemaphores)] The array of pointers to external
                                                    ///< semaphore handles to be appended into command list.
    ze_external_semaphore_signal_params_ext_t* signalParams,///< [in][range(0, numSemaphores)] The array of pointers to external
                                                    ///< semaphore signal parameters.
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendSignalExternalSemaphoreExt_t pfnAppendSignalExternalSemaphoreExt = [&result] {
        auto pfnAppendSignalExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendSignalExternalSemaphoreExt;
        if( nullptr == pfnAppendSignalExternalSemaphoreExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendSignalExternalSemaphoreExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendSignalExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, signalParams, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendSignalExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendSignalExternalSemaphoreExt;
    if( nullptr == pfnAppendSignalExternalSemaphoreExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendSignalExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, signalParams, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait on external semaphores
/// 
/// @details
///     - Waits on external semaphores.
///     - This function must only be used with an immediate command list.
///     - This function may be called from simultaneous threads with the same
///       command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phSemaphores`
///         + `nullptr == waitParams`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///         + `(nullptr == phSemaphores) && (0 < numSemaphores)`
///         + `(nullptr == waitParams) && (0 < numSemaphores)`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + Commandlist handle does not correspond to an immediate command list
ze_result_t ZE_APICALL
zeCommandListAppendWaitExternalSemaphoreExt(
    ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
    uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
    ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in][range(0,numSemaphores)] The array of pointers to external
                                                    ///< semaphore handles to append into command list.
    ze_external_semaphore_wait_params_ext_t* waitParams,///< [in][range(0,numSemaphores)] The array of pointers to external
                                                    ///< semaphore wait parameters.
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendWaitExternalSemaphoreExt_t pfnAppendWaitExternalSemaphoreExt = [&result] {
        auto pfnAppendWaitExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendWaitExternalSemaphoreExt;
        if( nullptr == pfnAppendWaitExternalSemaphoreExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendWaitExternalSemaphoreExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendWaitExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, waitParams, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendWaitExternalSemaphoreExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendWaitExternalSemaphoreExt;
    if( nullptr == pfnAppendWaitExternalSemaphoreExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendWaitExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, waitParams, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a ray tracing acceleration structure builder object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_RTAS_EXT_NAME extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDescriptor`
///         + `nullptr == phBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_BUILDER_EXT_VERSION_CURRENT < pDescriptor->builderVersion`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeRTASBuilderCreateExt(
    ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
    const ze_rtas_builder_ext_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
    ze_rtas_builder_ext_handle_t* phBuilder         ///< [out] handle of builder object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderCreateExt_t pfnCreateExt = [&result] {
        auto pfnCreateExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnCreateExt;
        if( nullptr == pfnCreateExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExt( hDriver, pDescriptor, phBuilder );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnCreateExt;
    if( nullptr == pfnCreateExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExt( hDriver, pDescriptor, phBuilder );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves ray tracing acceleration structure builder properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBuildOpDescriptor`
///         + `nullptr == pProperties`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXT_MAX < pBuildOpDescriptor->rtasFormat`
///         + `::ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXT_HIGH < pBuildOpDescriptor->buildQuality`
///         + `0x3 < pBuildOpDescriptor->buildFlags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeRTASBuilderGetBuildPropertiesExt(
    ze_rtas_builder_ext_handle_t hBuilder,          ///< [in] handle of builder object
    const ze_rtas_builder_build_op_ext_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
    ze_rtas_builder_ext_properties_t* pProperties   ///< [in,out] query result for builder properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderGetBuildPropertiesExt_t pfnGetBuildPropertiesExt = [&result] {
        auto pfnGetBuildPropertiesExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnGetBuildPropertiesExt;
        if( nullptr == pfnGetBuildPropertiesExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetBuildPropertiesExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetBuildPropertiesExt( hBuilder, pBuildOpDescriptor, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetBuildPropertiesExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnGetBuildPropertiesExt;
    if( nullptr == pfnGetBuildPropertiesExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetBuildPropertiesExt( hBuilder, pBuildOpDescriptor, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Checks ray tracing acceleration structure format compatibility
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXT_MAX < rtasFormatA`
///         + `::ZE_RTAS_FORMAT_EXT_MAX < rtasFormatB`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_SUCCESS
///         + An acceleration structure built with `rtasFormatA` is compatible with devices that report `rtasFormatB`.
///     - ::ZE_RESULT_EXT_ERROR_OPERANDS_INCOMPATIBLE
///         + An acceleration structure built with `rtasFormatA` is **not** compatible with devices that report `rtasFormatB`.
ze_result_t ZE_APICALL
zeDriverRTASFormatCompatibilityCheckExt(
    ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
    ze_rtas_format_ext_t rtasFormatA,               ///< [in] operand A
    ze_rtas_format_ext_t rtasFormatB                ///< [in] operand B
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverRTASFormatCompatibilityCheckExt_t pfnRTASFormatCompatibilityCheckExt = [&result] {
        auto pfnRTASFormatCompatibilityCheckExt = ze_lib::context->zeDdiTable.load()->Driver.pfnRTASFormatCompatibilityCheckExt;
        if( nullptr == pfnRTASFormatCompatibilityCheckExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnRTASFormatCompatibilityCheckExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnRTASFormatCompatibilityCheckExt( hDriver, rtasFormatA, rtasFormatB );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnRTASFormatCompatibilityCheckExt = ze_lib::context->zeDdiTable.load()->Driver.pfnRTASFormatCompatibilityCheckExt;
    if( nullptr == pfnRTASFormatCompatibilityCheckExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnRTASFormatCompatibilityCheckExt( hDriver, rtasFormatA, rtasFormatB );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Build ray tracing acceleration structure
/// 
/// @details
///     - This function builds an acceleration structure of the scene consisting
///       of the specified geometry information and writes the acceleration
///       structure to the provided destination buffer. All types of geometries
///       can get freely mixed inside a scene.
///     - Before an acceleration structure can be built, the user must allocate
///       the memory for the acceleration structure buffer and scratch buffer
///       using sizes queried with the ::zeRTASBuilderGetBuildPropertiesExt function.
///     - When using the "worst-case" size for the acceleration structure
///       buffer, the acceleration structure construction will never fail with ::ZE_RESULT_EXT_RTAS_BUILD_RETRY.
///     - When using the "expected" size for the acceleration structure buffer,
///       the acceleration structure construction may fail with
///       ::ZE_RESULT_EXT_RTAS_BUILD_RETRY. If this happens, the user may resize
///       their acceleration structure buffer using the returned
///       `*pRtasBufferSizeBytes` value, which will be updated with an improved
///       size estimate that will likely result in a successful build.
///     - The acceleration structure construction is run on the host and is
///       synchronous, thus after the function returns with a successful result,
///       the acceleration structure may be used.
///     - All provided data buffers must be host-accessible. The referenced
///       scene data (index- and vertex- buffers) have to be accessible from the
///       host, and will **not** be referenced by the build acceleration structure.
///     - The acceleration structure buffer is typicall a host allocation that
///       is later manually copied to a device allocation. Alternatively one can
///       also use a shared USM allocation as acceration structure buffer and
///       skip the copy.
///     - A successfully constructed acceleration structure is entirely
///       self-contained. There is no requirement for input data to persist
///       beyond build completion.
///     - A successfully constructed acceleration structure is non-copyable.
///     - Acceleration structure construction may be parallelized by passing a
///       valid handle to a parallel operation object and joining that parallel
///       operation using ::zeRTASParallelOperationJoinExt with user-provided
///       worker threads.
///     - A successfully constructed acceleration structure is generally
///       non-copyable. It can only get copied from host to device using the
///       special ::zeRTASBuilderCommandListAppendCopyExt function.
///     - **Additional Notes**
///        - "The geometry infos array, geometry infos, and scratch buffer must
///       all be standard host memory allocations."
///        - "A pointer to a geometry info can be a null pointer, in which case
///       the geometry is treated as empty."
///        - "If no parallel operation handle is provided, the build is run
///       sequentially on the current thread."
///        - "A parallel operation object may only be associated with a single
///       acceleration structure build at a time."
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBuildOpDescriptor`
///         + `nullptr == pScratchBuffer`
///         + `nullptr == pRtasBuffer`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXT_MAX < pBuildOpDescriptor->rtasFormat`
///         + `::ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXT_HIGH < pBuildOpDescriptor->buildQuality`
///         + `0x3 < pBuildOpDescriptor->buildFlags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_EXT_RTAS_BUILD_DEFERRED
///         + Acceleration structure build completion is deferred to parallel operation join.
///     - ::ZE_RESULT_EXT_RTAS_BUILD_RETRY
///         + Acceleration structure build failed due to insufficient resources, retry the build operation with a larger acceleration structure buffer allocation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + Acceleration structure build failed due to parallel operation object participation in another build operation.
ze_result_t ZE_APICALL
zeRTASBuilderBuildExt(
    ze_rtas_builder_ext_handle_t hBuilder,          ///< [in] handle of builder object
    const ze_rtas_builder_build_op_ext_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
    void* pScratchBuffer,                           ///< [in][range(0, `scratchBufferSizeBytes`)] scratch buffer to be used
                                                    ///< during acceleration structure construction
    size_t scratchBufferSizeBytes,                  ///< [in] size of scratch buffer, in bytes
    void* pRtasBuffer,                              ///< [in] pointer to destination buffer
    size_t rtasBufferSizeBytes,                     ///< [in] destination buffer size, in bytes
    ze_rtas_parallel_operation_ext_handle_t hParallelOperation, ///< [in][optional] handle to parallel operation object
    void* pBuildUserPtr,                            ///< [in][optional] pointer passed to callbacks
    ze_rtas_aabb_ext_t* pBounds,                    ///< [in,out][optional] pointer to destination address for acceleration
                                                    ///< structure bounds
    size_t* pRtasBufferSizeBytes                    ///< [out][optional] updated acceleration structure size requirement, in
                                                    ///< bytes
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderBuildExt_t pfnBuildExt = [&result] {
        auto pfnBuildExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnBuildExt;
        if( nullptr == pfnBuildExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnBuildExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnBuildExt( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnBuildExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnBuildExt;
    if( nullptr == pfnBuildExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnBuildExt( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies a ray tracing acceleration structure (RTAS) from host to device
///        memory.
/// 
/// @details
///     - The memory pointed to by srcptr must be host memory containing a valid
///       ray tracing acceleration structure.
///     - The number of bytes to copy must be larger or equal to the size of the
///       ray tracing acceleration structure.
///     - The application must ensure the memory pointed to by dstptr and srcptr
///       is accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr and
///       srcptr as they are free to be modified by either the Host or device up
///       until execution.
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the command list and events were created,
///       and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeRTASBuilderCommandListAppendCopyExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination in device memory to copy the ray tracing
                                                    ///< acceleration structure to
    const void* srcptr,                             ///< [in] pointer to a valid source ray tracing acceleration structure in
                                                    ///< host memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderCommandListAppendCopyExt_t pfnCommandListAppendCopyExt = [&result] {
        auto pfnCommandListAppendCopyExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnCommandListAppendCopyExt;
        if( nullptr == pfnCommandListAppendCopyExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCommandListAppendCopyExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCommandListAppendCopyExt( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCommandListAppendCopyExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnCommandListAppendCopyExt;
    if( nullptr == pfnCommandListAppendCopyExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCommandListAppendCopyExt( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a ray tracing acceleration structure builder object
/// 
/// @details
///     - The implementation of this function may immediately release any
///       internal Host and Device resources associated with this builder.
///     - The application must **not** call this function from simultaneous
///       threads with the same builder handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeRTASBuilderDestroyExt(
    ze_rtas_builder_ext_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderDestroyExt_t pfnDestroyExt = [&result] {
        auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnDestroyExt;
        if( nullptr == pfnDestroyExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExt( hBuilder );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->RTASBuilder.pfnDestroyExt;
    if( nullptr == pfnDestroyExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExt( hBuilder );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a ray tracing acceleration structure builder parallel
///        operation object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_RTAS_EXT_NAME extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationCreateExt(
    ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
    ze_rtas_parallel_operation_ext_handle_t* phParallelOperation///< [out] handle of parallel operation object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationCreateExt_t pfnCreateExt = [&result] {
        auto pfnCreateExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnCreateExt;
        if( nullptr == pfnCreateExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExt( hDriver, phParallelOperation );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnCreateExt;
    if( nullptr == pfnCreateExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExt( hDriver, phParallelOperation );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves ray tracing acceleration structure builder parallel
///        operation properties
/// 
/// @details
///     - The application must first bind the parallel operation object to a
///       build operation before it may query the parallel operation properties.
///       In other words, the application must first call
///       ::zeRTASBuilderBuildExt with **hParallelOperation** before calling
///       this function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zeRTASParallelOperationGetPropertiesExt(
    ze_rtas_parallel_operation_ext_handle_t hParallelOperation, ///< [in] handle of parallel operation object
    ze_rtas_parallel_operation_ext_properties_t* pProperties///< [in,out] query result for parallel operation properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationGetPropertiesExt_t pfnGetPropertiesExt = [&result] {
        auto pfnGetPropertiesExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnGetPropertiesExt;
        if( nullptr == pfnGetPropertiesExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPropertiesExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPropertiesExt( hParallelOperation, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnGetPropertiesExt;
    if( nullptr == pfnGetPropertiesExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExt( hParallelOperation, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Joins a parallel build operation
/// 
/// @details
///     - All worker threads return the same error code for the parallel build
///       operation upon build completion
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationJoinExt(
    ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in] handle of parallel operation object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationJoinExt_t pfnJoinExt = [&result] {
        auto pfnJoinExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnJoinExt;
        if( nullptr == pfnJoinExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnJoinExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnJoinExt( hParallelOperation );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnJoinExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnJoinExt;
    if( nullptr == pfnJoinExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnJoinExt( hParallelOperation );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a ray tracing acceleration structure builder parallel
///        operation object
/// 
/// @details
///     - The implementation of this function may immediately release any
///       internal Host and Device resources associated with this parallel
///       operation.
///     - The application must **not** call this function from simultaneous
///       threads with the same parallel operation handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationDestroyExt(
    ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationDestroyExt_t pfnDestroyExt = [&result] {
        auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnDestroyExt;
        if( nullptr == pfnDestroyExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExt( hParallelOperation );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->RTASParallelOperation.pfnDestroyExt;
    if( nullptr == pfnDestroyExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExt( hParallelOperation );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves the vector width properties of the device.
/// 
/// @details
///     - Properties are reported for each vector width supported by the device.
///     - Multiple calls to this function will return properties in the same
///       order.
///     - The number of vector width properties is reported thru the pCount
///       parameter which is updated by the driver given pCount == 0.
///     - The application may provide a buffer that is larger than the number of
///       properties, but the application must set pCount to the number of
///       properties to retrieve.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDeviceGetVectorWidthPropertiesExt(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of vector width properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of vector width properties available.
                                                    ///< if count is greater than the number of vector width properties
                                                    ///< available, then the driver shall update the value with the correct
                                                    ///< number of vector width properties available.
    ze_device_vector_width_properties_ext_t* pVectorWidthProperties ///< [in,out][optional][range(0, *pCount)] array of vector width properties.
                                                    ///< if count is less than the number of properties available, then the
                                                    ///< driver will return only the number requested.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetVectorWidthPropertiesExt_t pfnGetVectorWidthPropertiesExt = [&result] {
        auto pfnGetVectorWidthPropertiesExt = ze_lib::context->zeDdiTable.load()->Device.pfnGetVectorWidthPropertiesExt;
        if( nullptr == pfnGetVectorWidthPropertiesExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVectorWidthPropertiesExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVectorWidthPropertiesExt( hDevice, pCount, pVectorWidthProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVectorWidthPropertiesExt = ze_lib::context->zeDdiTable.load()->Device.pfnGetVectorWidthPropertiesExt;
    if( nullptr == pfnGetVectorWidthPropertiesExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVectorWidthPropertiesExt( hDevice, pCount, pVectorWidthProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves kernel allocation properties.
/// 
/// @details
///     - A valid kernel handle must be created with ::zeKernelCreate.
///     - Returns array of kernel allocation properties for kernel handle.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeKernelGetAllocationPropertiesExp(
    ze_kernel_handle_t hKernel,                     ///< [in] Kernel handle.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of kernel allocation properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of kernel allocation properties available.
                                                    ///< if count is greater than the number of kernel allocation properties
                                                    ///< available, then the driver shall update the value with the correct
                                                    ///< number of kernel allocation properties.
    ze_kernel_allocation_exp_properties_t* pAllocationProperties///< [in,out][optional][range(0, *pCount)] array of kernel allocation properties.
                                                    ///< if count is less than the number of kernel allocation properties
                                                    ///< available, then driver shall only retrieve that number of kernel
                                                    ///< allocation properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelGetAllocationPropertiesExp_t pfnGetAllocationPropertiesExp = [&result] {
        auto pfnGetAllocationPropertiesExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnGetAllocationPropertiesExp;
        if( nullptr == pfnGetAllocationPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAllocationPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAllocationPropertiesExp( hKernel, pCount, pAllocationProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAllocationPropertiesExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnGetAllocationPropertiesExp;
    if( nullptr == pfnGetAllocationPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAllocationPropertiesExp( hKernel, pCount, pAllocationProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle for the specified allocation with
///        properties for the requested handle.
/// 
/// @details
///     - Takes a pointer to a device or host memory allocation and creates an
///       IPC memory handle for exporting it for use in another process.
///     - The pointer must be the base pointer of a device or host memory
///       allocation; i.e. the value returned from ::zeMemAllocDevice or from
///       ::zeMemAllocHost, respectively or allocated from
///       ::zePhysicalMemCreate.
///     - The pointer may also be a virtual address that was mapped to a
///       physical memory object via ::zeVirtualMemMap; in that case, the IPC
///       handle represents the underlying physical memory object.
///     - Only one physical memory object may be associated with a single IPC
///       handle at a time; the virtual address range passed must map to exactly
///       one physical memory object.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pIpcHandle`
ze_result_t ZE_APICALL
zeMemGetIpcHandleWithProperties(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    void* pNext,                                    ///< [in][optional] Pointer to extension-specific structure.
    ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetIpcHandleWithProperties_t pfnGetIpcHandleWithProperties = [&result] {
        auto pfnGetIpcHandleWithProperties = ze_lib::context->zeDdiTable.load()->Mem.pfnGetIpcHandleWithProperties;
        if( nullptr == pfnGetIpcHandleWithProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetIpcHandleWithProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetIpcHandleWithProperties( hContext, ptr, pNext, pIpcHandle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcHandleWithProperties = ze_lib::context->zeDdiTable.load()->Mem.pfnGetIpcHandleWithProperties;
    if( nullptr == pfnGetIpcHandleWithProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcHandleWithProperties( hContext, ptr, pNext, pIpcHandle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a new graph object.
/// 
/// @details
///     - A newly created graph is an empty container for captured operations.
///     - The application may instantiate executable graph objects from a
///       recorded graph using ::zeGraphInstantiateExt.
///     - The application may begin capturing into an empty graph using
///       ::zeCommandListBeginCaptureIntoGraphExt.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phGraph`
ze_result_t ZE_APICALL
zeGraphCreateExt(
    ze_context_handle_t hContext,                   ///< [in] handle of the context
    const void* pNext,                              ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    ze_graph_handle_t* phGraph                      ///< [out] pointer to handle of the graph object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnGraphCreateExt_t pfnCreateExt = [&result] {
        auto pfnCreateExt = ze_lib::context->zeDdiTable.load()->Graph.pfnCreateExt;
        if( nullptr == pfnCreateExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExt( hContext, pNext, phGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExt = ze_lib::context->zeDdiTable.load()->Graph.pfnCreateExt;
    if( nullptr == pfnCreateExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExt( hContext, pNext, phGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Begins recording asynchronous append operations into a new graph
///        associated with an immediate command list.
/// 
/// @details
///     - Graph capture is intended for asynchronous append operations only;
///       synchronous operations are not supported while capture is active and
///       return ::ZE_RESULT_ERROR_GRAPH_CAPTURE_UNSUPPORTED.
///     - The application must call this function only with an immediate command
///       list.
///     - The application must not call this function with a synchronous
///       immediate command list.
///     - After this call succeeds, append operations issued to the command list
///       are recorded into a graph and are not submitted to the device. Events
///       used by these operations are not signaled until capture ends and the
///       graph is instantiated and executed.
///     - If the device does not support
///       ::ZE_RECORD_REPLAY_GRAPH_EXT_FLAG_APPEND_COMMANDLIST, then while
///       capture is active, calling
///       ::zeCommandListImmediateAppendCommandListsExp on the capturing command
///       list returns an error (::ZE_RESULT_ERROR_GRAPH_CAPTURE_UNSUPPORTED).
///     - If the device does not support
///       ::ZE_RECORD_REPLAY_GRAPH_EXT_FLAG_SUBGRAPHS, then while capture is
///       active, calling ::zeCommandListAppendGraphExt on the capturing command
///       list returns an error (::ZE_RESULT_ERROR_GRAPH_CAPTURE_UNSUPPORTED).
///     - While capture is active, host-side synchronization operations on
///       recorded work, such as ::zeCommandListHostSynchronize or
///       ::zeEventHostSynchronize, return
///       ::ZE_RESULT_ERROR_GRAPH_CAPTURE_UNSUPPORTED.
///     - While capture is active, internal counter-based events (i.e. without
///       ZEX_COUNTER_BASED_EVENT_FLAG_GRAPH_EXTERNAL) captured in the graph
///       cannot be used outside the graph; such use returns an error
///       (::ZE_RESULT_ERROR_GRAPH_INTERNAL_EVENT).
///     - The command list on which capture starts is called the primary command
///       list for a given capture session.
///     - If an event signaled by a captured command list is used in the wait
///       list of another immediate command list, that command list also enters
///       graph capture mode. This creates a fork. The command list from which
///       the fork originated is called the parent, and the forked command list
///       is called the child. A child command list may itself be used to create
///       additional forks, resulting in a tree of command lists participating
///       in the same graph capture.
///     - Subsequent signals from the parent command list to a child command
///       list are allowed and do not create additional forks or capture
///       sessions; the child command list remains in the same capture session
///       as the parent command list.
///     - Each fork must be joined by signaling on the child command list and by
///       waiting on the parent command list.
///     - A child command list may signal multiple times back to the parent
///       command list, but only the last signal on the child command list may
///       become part of the join operation.
///     - Child command lists continue recording as long as the primary command
///       list is in capture mode.
///     - Commands that append work (for example, compute kernels or data
///       transfers) to a recording child command list after the intended join
///       operation are treated as unjoined work, and the graph is considered
///       invalid. Commands that do not append work (for example, event signal
///       and wait operations) are allowed after the join operation and do not
///       invalidate the graph.
///     - All restrictions described for ::zeCommandListBeginGraphCaptureExt
///       apply to recording child command lists as well.
///     - It is invalid to merge two separate graph capture sessions (i.e. with
///       different primary command lists) by waiting on an event associated
///       with a different graph (operation will return
///       ::ZE_RESULT_ERROR_GRAPH_CAPTURE_MERGE_ATTEMPT).
///     - If the device does not support
///       ::ZE_RECORD_REPLAY_GRAPH_EXT_FLAG_CB_EXTERNAL_IPC, then using an event
///       that was created with both ZEX_COUNTER_BASED_EVENT_FLAG_IPC and
///       ZEX_COUNTER_BASED_EVENT_FLAG_GRAPH_EXTERNAL returns an error
///       (::ZE_RESULT_ERROR_GRAPH_CAPTURE_UNSUPPORTED) during append
///       operations.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zeCommandListBeginGraphCaptureExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list to start capture on
    const void* pNext                               ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListBeginGraphCaptureExt_t pfnBeginGraphCaptureExt = [&result] {
        auto pfnBeginGraphCaptureExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnBeginGraphCaptureExt;
        if( nullptr == pfnBeginGraphCaptureExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnBeginGraphCaptureExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnBeginGraphCaptureExt( hCommandList, pNext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnBeginGraphCaptureExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnBeginGraphCaptureExt;
    if( nullptr == pfnBeginGraphCaptureExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnBeginGraphCaptureExt( hCommandList, pNext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Begins recording asynchronous append operations into an existing
///        graph.
/// 
/// @details
///     - The graph must be created with ::zeGraphCreateExt before calling this
///       function.
///     - The graph must be empty when capture begins.
///     - After this call succeeds, the command list enters graph capture mode
///       and all restrictions described for ::zeCommandListBeginGraphCaptureExt
///       apply.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hGraph`
ze_result_t ZE_APICALL
zeCommandListBeginCaptureIntoGraphExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list to start capture on
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph to capture into
    const void* pNext                               ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListBeginCaptureIntoGraphExt_t pfnBeginCaptureIntoGraphExt = [&result] {
        auto pfnBeginCaptureIntoGraphExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnBeginCaptureIntoGraphExt;
        if( nullptr == pfnBeginCaptureIntoGraphExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnBeginCaptureIntoGraphExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnBeginCaptureIntoGraphExt( hCommandList, hGraph, pNext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnBeginCaptureIntoGraphExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnBeginCaptureIntoGraphExt;
    if( nullptr == pfnBeginCaptureIntoGraphExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnBeginCaptureIntoGraphExt( hCommandList, hGraph, pNext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries whether a command list is in graph capture mode.
/// 
/// @details
///     - The function returns `ZE_RESULT_QUERY_TRUE` when the command list is
///       in graph capture mode.
///     - The function returns `ZE_RESULT_QUERY_FALSE` when the command list is
///       not in graph capture mode.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zeCommandListIsGraphCaptureEnabledExt(
    ze_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListIsGraphCaptureEnabledExt_t pfnIsGraphCaptureEnabledExt = [&result] {
        auto pfnIsGraphCaptureEnabledExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnIsGraphCaptureEnabledExt;
        if( nullptr == pfnIsGraphCaptureEnabledExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnIsGraphCaptureEnabledExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnIsGraphCaptureEnabledExt( hCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnIsGraphCaptureEnabledExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnIsGraphCaptureEnabledExt;
    if( nullptr == pfnIsGraphCaptureEnabledExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnIsGraphCaptureEnabledExt( hCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Ends graph capture on the primary command list and returns the
///        recorded graph.
/// 
/// @details
///     - This function may only be called on the primary command list used with
///       ::zeCommandListBeginGraphCaptureExt or
///       ::zeCommandListBeginCaptureIntoGraphExt.
///     - If capture was started with ::zeCommandListBeginCaptureIntoGraphExt,
///       the returned graph handle is the same graph handle that was provided
///       when capture began.
///     - The returned graph must be instantiated before execution.
///     - This call ends graph capture mode on all command lists participating
///       in the same graph capture (including forks).
///     - After this call succeeds, subsequent append operations submit work to
///       the device normally.
///     - If capture mode is not active on the command list, an error is
///       returned.
///     - After this call succeeds, events signaled by previously captured
///       commands do not create new forks.
///     - After this call succeeds, internal counter-based events (i.e. without
///       ZEX_COUNTER_BASED_EVENT_FLAG_GRAPH_EXTERNAL) can be reused by the
///       application and don't interfere with recorded state.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phGraph`
///     - $ZE_RESULT_ERROR_GRAPH_UNJOINED_FORKS
///         + if graph contains unjoined forks
///     - $ZE_RESULT_ERROR_COMMAND_LIST_NOT_CAPTURING
///         + if command list is not in graph capture mode
ze_result_t ZE_APICALL
zeCommandListEndGraphCaptureExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list to end capture on
    const void* pNext,                              ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    ze_graph_handle_t* phGraph                      ///< [out] pointer to the captured graph handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListEndGraphCaptureExt_t pfnEndGraphCaptureExt = [&result] {
        auto pfnEndGraphCaptureExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnEndGraphCaptureExt;
        if( nullptr == pfnEndGraphCaptureExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEndGraphCaptureExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEndGraphCaptureExt( hCommandList, pNext, phGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEndGraphCaptureExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnEndGraphCaptureExt;
    if( nullptr == pfnEndGraphCaptureExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEndGraphCaptureExt( hCommandList, pNext, phGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the graph associated with a command list that is in graph
///        capture mode.
/// 
/// @details
///     - This function may only be called while the command list is in graph
///       capture mode.
///     - The returned graph handle cannot be instantiated until capture is
///       ended by ::zeCommandListEndGraphCaptureExt.
///     - This function does not transfer ownership of the graph handle.
///     - If the command list is not in graph capture mode, an error is returned
///       and `*phGraph` is set to null.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phGraph`
///     - $ZE_RESULT_ERROR_COMMAND_LIST_NOT_CAPTURING
///         + if command list is not in graph capture mode
ze_result_t ZE_APICALL
zeCommandListGetGraphExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list that is in capture mode
    ze_graph_handle_t* phGraph                      ///< [out] pointer to the graph handle associated with the command list
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListGetGraphExt_t pfnGetGraphExt = [&result] {
        auto pfnGetGraphExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetGraphExt;
        if( nullptr == pfnGetGraphExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetGraphExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetGraphExt( hCommandList, phGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetGraphExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnGetGraphExt;
    if( nullptr == pfnGetGraphExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetGraphExt( hCommandList, phGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the primary command list associated with a graph capture
///        session.
/// 
/// @details
///     - The returned command list is the command list that initiated capture
///       for the graph during its recording stage.
///     - This function can be called while the graph is being recorded and
///       after capture has ended.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phCommandList`
ze_result_t ZE_APICALL
zeGraphGetPrimaryCommandListExt(
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to the primary command list handle associated with the
                                                    ///< graph
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnGraphGetPrimaryCommandListExt_t pfnGetPrimaryCommandListExt = [&result] {
        auto pfnGetPrimaryCommandListExt = ze_lib::context->zeDdiTable.load()->Graph.pfnGetPrimaryCommandListExt;
        if( nullptr == pfnGetPrimaryCommandListExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPrimaryCommandListExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPrimaryCommandListExt( hGraph, phCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPrimaryCommandListExt = ze_lib::context->zeDdiTable.load()->Graph.pfnGetPrimaryCommandListExt;
    if( nullptr == pfnGetPrimaryCommandListExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPrimaryCommandListExt( hGraph, phCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Registers a host callback that is invoked when a graph is destroyed.
/// 
/// @details
///     - Callbacks may be registered while a graph is being recorded or after
///       executable graph instances have been created from it.
///     - Multiple callbacks may be registered for the same graph.
///     - All registered callbacks are invoked when the graph is destroyed.
///     - The callback must not call Level Zero APIs that use the graph being
///       destroyed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
ze_result_t ZE_APICALL
zeGraphSetDestructionCallbackExt(
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph
    zex_mem_graph_free_callback_fn_t pfnCallback,   ///< [in] callback function to invoke when the graph is destroyed
    void* pUserData,                                ///< [in][optional] user data to pass to the callback
    const void* pNext                               ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnGraphSetDestructionCallbackExt_t pfnSetDestructionCallbackExt = [&result] {
        auto pfnSetDestructionCallbackExt = ze_lib::context->zeDdiTable.load()->Graph.pfnSetDestructionCallbackExt;
        if( nullptr == pfnSetDestructionCallbackExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetDestructionCallbackExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetDestructionCallbackExt( hGraph, pfnCallback, pUserData, pNext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetDestructionCallbackExt = ze_lib::context->zeDdiTable.load()->Graph.pfnSetDestructionCallbackExt;
    if( nullptr == pfnSetDestructionCallbackExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetDestructionCallbackExt( hGraph, pfnCallback, pUserData, pNext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an executable graph object from a recorded graph.
/// 
/// @details
///     - Multiple executable graph objects may be created from a single
///       recorded graph.
///     - Recorded regular events (not counter-based) are shared between
///       executable graph instances; the application is responsible for
///       avoiding data races during concurrent execution of multiple graph
///       instances.
///     - Recorded internal counter-based events (i.e. without
///       ZEX_COUNTER_BASED_EVENT_FLAG_GRAPH_EXTERNAL) may be used only for
///       synchronization within the graph. Their state is tied to the
///       underlying execution queue and is not shared between executable graph
///       instances.
///     - Recorded external counter-based events (i.e. with
///       ZEX_COUNTER_BASED_EVENT_FLAG_GRAPH_EXTERNAL) may be used to
///       synchronize the graph with device commands submitted outside the graph
///       (for example, before or after ::zeCommandListAppendGraphExt) and with
///       the host. External counter-based events may incur additional overhead
///       compared to internal counter-based events.
///     - Resources used in captured commands (e.g. buffers passed to kernels as
///       arguments) are shared between instances; the application is
///       responsible for avoiding data races during concurrent execution.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phExecutableGraph`
ze_result_t ZE_APICALL
zeGraphInstantiateExt(
    ze_graph_handle_t hGraph,                       ///< [in] handle of the recorded graph
    const void* pNext,                              ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    ze_executable_graph_handle_t* phExecutableGraph ///< [out] pointer to handle of the executable graph
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnGraphInstantiateExt_t pfnInstantiateExt = [&result] {
        auto pfnInstantiateExt = ze_lib::context->zeDdiTable.load()->Graph.pfnInstantiateExt;
        if( nullptr == pfnInstantiateExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnInstantiateExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnInstantiateExt( hGraph, pNext, phExecutableGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInstantiateExt = ze_lib::context->zeDdiTable.load()->Graph.pfnInstantiateExt;
    if( nullptr == pfnInstantiateExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnInstantiateExt( hGraph, pNext, phExecutableGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends execution of an executable graph to a command list.
/// 
/// @details
///     - The destination command list must match the type and execution
///       characteristics of the command list used to initiate recording,
///       including the queue group ordinal and immediate mode configuration.
///     - Only one execution of the same executable graph object may run at a
///       time; concurrent graph execution requires multiple executable graph
///       instances.
///     - If this function is called while the executable graph is already
///       running, the new execution is scheduled after the current execution
///       completes.
///     - Graph execution obeys the implicit in-order dependency semantics of
///       the destination command list.
///     - If `hSignalEvent` is provided, it is signaled after all recorded
///       append operations on all recorded queues complete.
///     - If wait events are provided, graph execution does not begin until all
///       wait events are satisfied.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hGraph`
ze_result_t ZE_APICALL
zeCommandListAppendGraphExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list to execute the graph on
    ze_executable_graph_handle_t hGraph,            ///< [in] handle of the executable graph
    const void* pNext,                              ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendGraphExt_t pfnAppendGraphExt = [&result] {
        auto pfnAppendGraphExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendGraphExt;
        if( nullptr == pfnAppendGraphExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendGraphExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendGraphExt( hCommandList, hGraph, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendGraphExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendGraphExt;
    if( nullptr == pfnAppendGraphExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendGraphExt( hCommandList, hGraph, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the recorded graph used to instantiate an executable graph.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phSourceGraph`
ze_result_t ZE_APICALL
zeExecutableGraphGetSourceGraphExt(
    ze_executable_graph_handle_t hGraph,            ///< [in] handle of the executable graph
    ze_graph_handle_t* phSourceGraph                ///< [out] pointer to the source recorded graph handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnExecutableGraphGetSourceGraphExt_t pfnGetSourceGraphExt = [&result] {
        auto pfnGetSourceGraphExt = ze_lib::context->zeDdiTable.load()->ExecutableGraph.pfnGetSourceGraphExt;
        if( nullptr == pfnGetSourceGraphExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetSourceGraphExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetSourceGraphExt( hGraph, phSourceGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSourceGraphExt = ze_lib::context->zeDdiTable.load()->ExecutableGraph.pfnGetSourceGraphExt;
    if( nullptr == pfnGetSourceGraphExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSourceGraphExt( hGraph, phSourceGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Queries whether a graph is empty.
/// 
/// @details
///     - The function returns `ZE_RESULT_QUERY_TRUE` when the graph contains no
///       operations.
///     - The function returns `ZE_RESULT_QUERY_FALSE` when the graph contains
///       recorded operations.
///     - The function returns `ZE_RESULT_ERROR_INVALID_GRAPH` when the recorded
///       graph is invalid.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
ze_result_t ZE_APICALL
zeGraphIsEmptyExt(
    ze_graph_handle_t hGraph                        ///< [in] handle of the graph
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnGraphIsEmptyExt_t pfnIsEmptyExt = [&result] {
        auto pfnIsEmptyExt = ze_lib::context->zeDdiTable.load()->Graph.pfnIsEmptyExt;
        if( nullptr == pfnIsEmptyExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnIsEmptyExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnIsEmptyExt( hGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnIsEmptyExt = ze_lib::context->zeDdiTable.load()->Graph.pfnIsEmptyExt;
    if( nullptr == pfnIsEmptyExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnIsEmptyExt( hGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Writes a DOT description of a recorded graph to disk.
/// 
/// @details
///     - The generated DOT output captures the graph structure and recorded
///       append operations.
///     - Kernel node output includes kernel names, argument lists, and argument
///       types and values.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == filePath`
ze_result_t ZE_APICALL
zeGraphDumpContentsExt(
    ze_graph_handle_t hGraph,                       ///< [in] handle of the graph
    const char* filePath,                           ///< [in] path where the DOT file is written
    const void* pNext                               ///< [in][optional] must be null or a pointer to an extension-specific
                                                    ///< structure (i.e. contains stype and pNext)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnGraphDumpContentsExt_t pfnDumpContentsExt = [&result] {
        auto pfnDumpContentsExt = ze_lib::context->zeDdiTable.load()->Graph.pfnDumpContentsExt;
        if( nullptr == pfnDumpContentsExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDumpContentsExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDumpContentsExt( hGraph, filePath, pNext );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDumpContentsExt = ze_lib::context->zeDdiTable.load()->Graph.pfnDumpContentsExt;
    if( nullptr == pfnDumpContentsExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDumpContentsExt( hGraph, filePath, pNext );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys an executable graph object.
/// 
/// @details
///     - The executable graph must not be in use or executing on any command
///       list when it is destroyed.
///     - After destruction, the handle becomes invalid and must not be used in
///       further API calls.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
ze_result_t ZE_APICALL
zeExecutableGraphDestroyExt(
    ze_executable_graph_handle_t hGraph             ///< [in][release] handle of the executable graph to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnExecutableGraphDestroyExt_t pfnDestroyExt = [&result] {
        auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->ExecutableGraph.pfnDestroyExt;
        if( nullptr == pfnDestroyExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExt( hGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->ExecutableGraph.pfnDestroyExt;
    if( nullptr == pfnDestroyExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExt( hGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a recorded graph object.
/// 
/// @details
///     - All executable graph instances created from the recorded graph must be
///       destroyed before this function is called.
///     - After destruction, the handle becomes invalid and must not be used in
///       further API calls.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hGraph`
ze_result_t ZE_APICALL
zeGraphDestroyExt(
    ze_graph_handle_t hGraph                        ///< [in][release] handle of the graph to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnGraphDestroyExt_t pfnDestroyExt = [&result] {
        auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->Graph.pfnDestroyExt;
        if( nullptr == pfnDestroyExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExt( hGraph );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExt = ze_lib::context->zeDdiTable.load()->Graph.pfnDestroyExt;
    if( nullptr == pfnDestroyExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExt( hGraph );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a host function call into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The host function will be executed on the host when the command list
///       reaches this point during execution.
///     - The host function callback must be of type
///       ::ze_host_function_callback_t.
///     - The host function must **not** call any Level Zero API functions.
///     - The host function may access USM shared and USM host allocations.
///     - The runtime invokes the host function asynchronously to API calls.
///     - Device may wait for preceding commands to finish before invoking the
///       callback (i.e. callbacks may introduce implicit synchronization point
///       on the device).
///     - Device will wait for all phWaitEvents to be signaled before executing
///       the host function.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + an extension passed via pNext is not supported
ze_result_t ZE_APICALL
zeCommandListAppendHostFunction(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_host_function_callback_t pfnHostFunction,    ///< [in] host function to call, expected to be lightweight and
                                                    ///< non-blocking
    void* pUserData,                                ///< [in][optional] user specific data that would be passed to function;
                                                    ///< neither the runtime nor the device will dereference it
    const void* pNext,                              ///< [in][optional] additional extensions passed to the function
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] count of phWaitEvents; must be 0 if `nullptr ==
                                                    ///< phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendHostFunction_t pfnAppendHostFunction = [&result] {
        auto pfnAppendHostFunction = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendHostFunction;
        if( nullptr == pfnAppendHostFunction ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendHostFunction;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendHostFunction( hCommandList, pfnHostFunction, pUserData, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendHostFunction = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendHostFunction;
    if( nullptr == pfnAppendHostFunction ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendHostFunction( hCommandList, pfnHostFunction, pUserData, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reserve Cache on Device
/// 
/// @details
///     - The application may call this function but may not be successful as
///       some other application may have reserve prior
/// 
/// @remarks
///   _Analogues_
///     - None
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
ze_result_t ZE_APICALL
zeDeviceReserveCacheExt(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    size_t cacheLevel,                              ///< [in] cache level where application want to reserve. If zero, then the
                                                    ///< driver shall default to last level of cache and attempt to reserve in
                                                    ///< that cache.
    size_t cacheReservationSize                     ///< [in] value for reserving size, in bytes. If zero, then the driver
                                                    ///< shall remove prior reservation
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceReserveCacheExt_t pfnReserveCacheExt = [&result] {
        auto pfnReserveCacheExt = ze_lib::context->zeDdiTable.load()->Device.pfnReserveCacheExt;
        if( nullptr == pfnReserveCacheExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReserveCacheExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReserveCacheExt = ze_lib::context->zeDdiTable.load()->Device.pfnReserveCacheExt;
    if( nullptr == pfnReserveCacheExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Assign VA section to use reserved section
/// 
/// @details
///     - The application may call this function to assign VA to particular
///       reservartion region
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_CACHE_EXT_REGION_NON_RESERVED < cacheRegion`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeDeviceSetCacheAdviceExt(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    void* ptr,                                      ///< [in] memory pointer to query
    size_t regionSize,                              ///< [in] region size, in pages
    ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceSetCacheAdviceExt_t pfnSetCacheAdviceExt = [&result] {
        auto pfnSetCacheAdviceExt = ze_lib::context->zeDdiTable.load()->Device.pfnSetCacheAdviceExt;
        if( nullptr == pfnSetCacheAdviceExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetCacheAdviceExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetCacheAdviceExt = ze_lib::context->zeDdiTable.load()->Device.pfnSetCacheAdviceExt;
    if( nullptr == pfnSetCacheAdviceExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query event timestamps for a device or sub-device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_EVENT_QUERY_TIMESTAMPS_EXP_NAME
///       extension.
///     - The implementation must return all timestamps for the specified event
///       and device pair.
///     - The implementation must return all timestamps for all sub-devices when
///       device handle is parent device.
///     - The implementation may return all timestamps for sub-devices when
///       device handle is sub-device or may return 0 for count.
/// 
/// @remarks
///   _Analogues_
///     - None
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeEventQueryTimestampsExp(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
    uint32_t* pCount,                               ///< [in,out] pointer to the number of timestamp results.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of timestamps available.
                                                    ///< if count is greater than the number of timestamps available, then the
                                                    ///< driver shall update the value with the correct number of timestamps available.
    ze_kernel_timestamp_result_t* pTimestamps       ///< [in,out][optional][range(0, *pCount)] array of timestamp results.
                                                    ///< if count is less than the number of timestamps available, then driver
                                                    ///< shall only retrieve that number of timestamps.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventQueryTimestampsExp_t pfnQueryTimestampsExp = [&result] {
        auto pfnQueryTimestampsExp = ze_lib::context->zeDdiTable.load()->EventExp.pfnQueryTimestampsExp;
        if( nullptr == pfnQueryTimestampsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnQueryTimestampsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryTimestampsExp = ze_lib::context->zeDdiTable.load()->EventExp.pfnQueryTimestampsExp;
    if( nullptr == pfnQueryTimestampsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query image memory properties.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_IMAGE_MEMORY_PROPERTIES_EXP_NAME
///       extension.
/// 
/// @remarks
///   _Analogues_
///     - None
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemoryProperties`
ze_result_t ZE_APICALL
zeImageGetMemoryPropertiesExp(
    ze_image_handle_t hImage,                       ///< [in] handle of image object
    ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageGetMemoryPropertiesExp_t pfnGetMemoryPropertiesExp = [&result] {
        auto pfnGetMemoryPropertiesExp = ze_lib::context->zeDdiTable.load()->ImageExp.pfnGetMemoryPropertiesExp;
        if( nullptr == pfnGetMemoryPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetMemoryPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetMemoryPropertiesExp( hImage, pMemoryProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMemoryPropertiesExp = ze_lib::context->zeDdiTable.load()->ImageExp.pfnGetMemoryPropertiesExp;
    if( nullptr == pfnGetMemoryPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMemoryPropertiesExp( hImage, pMemoryProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create image view on the context.
/// 
/// @details
///     - The application must only use the image view for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_IMAGE_VIEW_EXT_NAME extension.
///     - Image views are treated as images from the API.
///     - Image views provide a mechanism to redescribe how an image is
///       interpreted (e.g. different format).
///     - Image views become disabled when their corresponding image resource is
///       destroyed.
///     - Use ::zeImageDestroy to destroy image view objects.
/// 
/// @remarks
///   _Analogues_
///     - None
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phImageView`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///         + `::ZE_IMAGE_TYPE_BUFFER < desc->type`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT
ze_result_t ZE_APICALL
zeImageViewCreateExt(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
    ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageViewCreateExt_t pfnViewCreateExt = [&result] {
        auto pfnViewCreateExt = ze_lib::context->zeDdiTable.load()->Image.pfnViewCreateExt;
        if( nullptr == pfnViewCreateExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnViewCreateExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnViewCreateExt = ze_lib::context->zeDdiTable.load()->Image.pfnViewCreateExt;
    if( nullptr == pfnViewCreateExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create image view on the context.
/// 
/// @details
///     - The application must only use the image view for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_IMAGE_VIEW_EXP_NAME extension.
///     - Image views are treated as images from the API.
///     - Image views provide a mechanism to redescribe how an image is
///       interpreted (e.g. different format).
///     - Image views become disabled when their corresponding image resource is
///       destroyed.
///     - Use ::zeImageDestroy to destroy image view objects.
///     - Note: This function is deprecated and replaced by
///       ::zeImageViewCreateExt.
/// 
/// @remarks
///   _Analogues_
///     - None
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phImageView`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///         + `::ZE_IMAGE_TYPE_BUFFER < desc->type`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT
ze_result_t ZE_APICALL
zeImageViewCreateExp(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
    ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageViewCreateExp_t pfnViewCreateExp = [&result] {
        auto pfnViewCreateExp = ze_lib::context->zeDdiTable.load()->ImageExp.pfnViewCreateExp;
        if( nullptr == pfnViewCreateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnViewCreateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnViewCreateExp = ze_lib::context->zeDdiTable.load()->ImageExp.pfnViewCreateExp;
    if( nullptr == pfnViewCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Provide kernel scheduling hints that may improve performance
/// 
/// @details
///     - The scheduling hints may improve performance only and are not required
///       for correctness.
///     - If a specified scheduling hint is unsupported it will be silently
///       ignored.
///     - If two conflicting scheduling hints are specified there is no defined behavior;
///       the hints may be ignored or one hint may be chosen arbitrarily.
///     - The application must not call this function from simultaneous threads
///       with the same kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pHint`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < pHint->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeKernelSchedulingHintExp(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnKernelSchedulingHintExp_t pfnSchedulingHintExp = [&result] {
        auto pfnSchedulingHintExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnSchedulingHintExp;
        if( nullptr == pfnSchedulingHintExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSchedulingHintExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSchedulingHintExp( hKernel, pHint );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSchedulingHintExp = ze_lib::context->zeDdiTable.load()->KernelExp.pfnSchedulingHintExp;
    if( nullptr == pfnSchedulingHintExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSchedulingHintExp( hKernel, pHint );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - None
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pPciProperties`
ze_result_t ZE_APICALL
zeDevicePciGetPropertiesExt(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
    ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDevicePciGetPropertiesExt_t pfnPciGetPropertiesExt = [&result] {
        auto pfnPciGetPropertiesExt = ze_lib::context->zeDdiTable.load()->Device.pfnPciGetPropertiesExt;
        if( nullptr == pfnPciGetPropertiesExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnPciGetPropertiesExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnPciGetPropertiesExt( hDevice, pPciProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetPropertiesExt = ze_lib::context->zeDdiTable.load()->Device.pfnPciGetPropertiesExt;
    if( nullptr == pfnPciGetPropertiesExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetPropertiesExt( hDevice, pPciProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies from an image to device or shared memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by dstptr is
///       accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr as
///       it is free to be modified by either the Host or device up until
///       execution.
///     - The application must ensure the image and events are accessible by the
///       device on which the command list was created.
///     - The application must ensure the image format descriptor for the source
///       image is a single-planar format.
///     - The application must ensure that the rowPitch is set to 0 if image is
///       a 1D image. Otherwise the rowPitch must be greater than or equal to
///       the element size in bytes x width.
///     - If rowPitch is set to 0, the appropriate row pitch is calculated based
///       on the size of each element in bytes multiplied by width
///     - The application must ensure that the slicePitch is set to 0 if image
///       is a 1D or 2D image. Otherwise this value must be greater than or
///       equal to rowPitch x height.
///     - If slicePitch is set to 0, the appropriate slice pitch is calculated
///       based on the rowPitch x height.
///     - The application must ensure the command list, image and events were
///       created, and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueReadImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hSrcImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == dstptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendImageCopyToMemoryExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
    uint32_t destRowPitch,                          ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                    ///< image or each image of a 1D or 2D image array being written
    uint32_t destSlicePitch,                        ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                    ///< each image of a 1D or 2D image array being written
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendImageCopyToMemoryExt_t pfnAppendImageCopyToMemoryExt = [&result] {
        auto pfnAppendImageCopyToMemoryExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyToMemoryExt;
        if( nullptr == pfnAppendImageCopyToMemoryExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendImageCopyToMemoryExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyToMemoryExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyToMemoryExt;
    if( nullptr == pfnAppendImageCopyToMemoryExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Copies to an image from device or shared memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by srcptr is
///       accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by srcptr as
///       it is free to be modified by either the Host or device up until
///       execution.
///     - The application must ensure the image and events are accessible by the
///       device on which the command list was created.
///     - The application must ensure the image format descriptor for the
///       destination image is a single-planar format.
///     - The application must ensure that the rowPitch is set to 0 if image is
///       a 1D image. Otherwise the rowPitch must be greater than or equal to
///       the element size in bytes x width.
///     - If rowPitch is set to 0, the appropriate row pitch is calculated based
///       on the size of each element in bytes multiplied by width
///     - The application must ensure that the slicePitch is set to 0 if image
///       is a 1D or 2D image. Otherwise this value must be greater than or
///       equal to rowPitch x height.
///     - If slicePitch is set to 0, the appropriate slice pitch is calculated
///       based on the rowPitch x height.
///     - The application must ensure the command list, image and events were
///       created, and the memory was allocated, on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clEnqueueWriteImage
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDstImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == srcptr`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zeCommandListAppendImageCopyFromMemoryExt(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
    uint32_t srcRowPitch,                           ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                    ///< image or each image of a 1D or 2D image array being read
    uint32_t srcSlicePitch,                         ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                    ///< each image of a 1D or 2D image array being read
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                    ///< if `nullptr == phWaitEvents`
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListAppendImageCopyFromMemoryExt_t pfnAppendImageCopyFromMemoryExt = [&result] {
        auto pfnAppendImageCopyFromMemoryExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyFromMemoryExt;
        if( nullptr == pfnAppendImageCopyFromMemoryExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendImageCopyFromMemoryExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyFromMemoryExt = ze_lib::context->zeDdiTable.load()->CommandList.pfnAppendImageCopyFromMemoryExt;
    if( nullptr == pfnAppendImageCopyFromMemoryExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of an image allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImageAllocProperties`
ze_result_t ZE_APICALL
zeImageGetAllocPropertiesExt(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_image_handle_t hImage,                       ///< [in] handle of image object to query
    ze_image_allocation_ext_properties_t* pImageAllocProperties ///< [in,out] query result for image allocation properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageGetAllocPropertiesExt_t pfnGetAllocPropertiesExt = [&result] {
        auto pfnGetAllocPropertiesExt = ze_lib::context->zeDdiTable.load()->Image.pfnGetAllocPropertiesExt;
        if( nullptr == pfnGetAllocPropertiesExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAllocPropertiesExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAllocPropertiesExt = ze_lib::context->zeDdiTable.load()->Image.pfnGetAllocPropertiesExt;
    if( nullptr == pfnGetAllocPropertiesExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief List Imports & Exports
/// 
/// @details
///     - List all the import & unresolveable import dependencies & exports of a
///       set of modules
/// 
/// @remarks
///   _Analogues_
///     - None
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pInspectDesc`
///         + `nullptr == phModules`
///         + `nullptr == phLog`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < pInspectDesc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeModuleInspectLinkageExt(
    ze_linkage_inspection_ext_desc_t* pInspectDesc, ///< [in] pointer to linkage inspection descriptor structure.
    uint32_t numModules,                            ///< [in] number of modules to be inspected pointed to by phModules.
    ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to be
                                                    ///< inspected for import dependencies.
    ze_module_build_log_handle_t* phLog             ///< [out] pointer to handle of linkage inspection log. Log object will
                                                    ///< contain separate lists of imports, un-resolvable imports, and exports.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnModuleInspectLinkageExt_t pfnInspectLinkageExt = [&result] {
        auto pfnInspectLinkageExt = ze_lib::context->zeDdiTable.load()->Module.pfnInspectLinkageExt;
        if( nullptr == pfnInspectLinkageExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnInspectLinkageExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInspectLinkageExt = ze_lib::context->zeDdiTable.load()->Module.pfnInspectLinkageExt;
    if( nullptr == pfnInspectLinkageExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory on the
///        context using the specified free policy.
/// 
/// @details
///     - Similar to zeMemFree, with added parameter to choose the free policy.
///     - Does not gaurantee memory is freed upon return. See free policy
///       descriptions for details.
///     - The application must **not** call this function from simultaneous
///       threads with the same pointer.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemFreeDesc`
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < pMemFreeDesc->freePolicy`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeMemFreeExt(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
    void* ptr                                       ///< [in][release] pointer to memory to free
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemFreeExt_t pfnFreeExt = [&result] {
        auto pfnFreeExt = ze_lib::context->zeDdiTable.load()->Mem.pfnFreeExt;
        if( nullptr == pfnFreeExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnFreeExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnFreeExt( hContext, pMemFreeDesc, ptr );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFreeExt = ze_lib::context->zeDdiTable.load()->Mem.pfnFreeExt;
    if( nullptr == pfnFreeExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFreeExt( hContext, pMemFreeDesc, ptr );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves fabric vertices within a driver
/// 
/// @details
///     - A fabric vertex represents either a device or a switch connected to
///       other fabric vertices.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeFabricVertexGetExp(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric vertices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of fabric vertices available.
                                                    ///< if count is greater than the number of fabric vertices available, then
                                                    ///< the driver shall update the value with the correct number of fabric
                                                    ///< vertices available.
    ze_fabric_vertex_handle_t* phVertices           ///< [in,out][optional][range(0, *pCount)] array of handle of fabric vertices.
                                                    ///< if count is less than the number of fabric vertices available, then
                                                    ///< driver shall only retrieve that number of fabric vertices.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFabricVertexGetExp_t pfnGetExp = [&result] {
        auto pfnGetExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetExp;
        if( nullptr == pfnGetExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetExp( hDriver, pCount, phVertices );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetExp;
    if( nullptr == pfnGetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExp( hDriver, pCount, phVertices );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a fabric sub-vertex from a fabric vertex
/// 
/// @details
///     - Multiple calls to this function will return identical fabric vertex
///       handles, in the same order.
///     - The number of handles returned from this function is affected by the
///       `ZE_AFFINITY_MASK` environment variable.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVertex`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeFabricVertexGetSubVerticesExp(
    ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-vertices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of sub-vertices available.
                                                    ///< if count is greater than the number of sub-vertices available, then
                                                    ///< the driver shall update the value with the correct number of
                                                    ///< sub-vertices available.
    ze_fabric_vertex_handle_t* phSubvertices        ///< [in,out][optional][range(0, *pCount)] array of handle of sub-vertices.
                                                    ///< if count is less than the number of sub-vertices available, then
                                                    ///< driver shall only retrieve that number of sub-vertices.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFabricVertexGetSubVerticesExp_t pfnGetSubVerticesExp = [&result] {
        auto pfnGetSubVerticesExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetSubVerticesExp;
        if( nullptr == pfnGetSubVerticesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetSubVerticesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSubVerticesExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetSubVerticesExp;
    if( nullptr == pfnGetSubVerticesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the fabric vertex.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVertex`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pVertexProperties`
ze_result_t ZE_APICALL
zeFabricVertexGetPropertiesExp(
    ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
    ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFabricVertexGetPropertiesExp_t pfnGetPropertiesExp = [&result] {
        auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPropertiesExp( hVertex, pVertexProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetPropertiesExp;
    if( nullptr == pfnGetPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExp( hVertex, pVertexProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns device handle from fabric vertex handle.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVertex`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phDevice`
///     - ::ZE_RESULT_EXP_ERROR_VERTEX_IS_NOT_DEVICE
///         + Provided fabric vertex handle does not correspond to a device or subdevice.
///     - ::ZE_RESULT_EXP_ERROR_REMOTE_DEVICE
///         + Provided fabric vertex handle corresponds to remote device or subdevice.
ze_result_t ZE_APICALL
zeFabricVertexGetDeviceExp(
    ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
    ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFabricVertexGetDeviceExp_t pfnGetDeviceExp = [&result] {
        auto pfnGetDeviceExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetDeviceExp;
        if( nullptr == pfnGetDeviceExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDeviceExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDeviceExp( hVertex, phDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDeviceExp = ze_lib::context->zeDdiTable.load()->FabricVertexExp.pfnGetDeviceExp;
    if( nullptr == pfnGetDeviceExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDeviceExp( hVertex, phDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns fabric vertex handle from device handle.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phVertex`
///     - ::ZE_RESULT_EXP_ERROR_DEVICE_IS_NOT_VERTEX
///         + Provided device handle does not correspond to a fabric vertex.
ze_result_t ZE_APICALL
zeDeviceGetFabricVertexExp(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDeviceGetFabricVertexExp_t pfnGetFabricVertexExp = [&result] {
        auto pfnGetFabricVertexExp = ze_lib::context->zeDdiTable.load()->DeviceExp.pfnGetFabricVertexExp;
        if( nullptr == pfnGetFabricVertexExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFabricVertexExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFabricVertexExp( hDevice, phVertex );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFabricVertexExp = ze_lib::context->zeDdiTable.load()->DeviceExp.pfnGetFabricVertexExp;
    if( nullptr == pfnGetFabricVertexExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFabricVertexExp( hDevice, phVertex );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves all fabric edges between provided pair of fabric vertices
/// 
/// @details
///     - A fabric edge represents one or more physical links between two fabric
///       vertices.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVertexA`
///         + `nullptr == hVertexB`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeFabricEdgeGetExp(
    ze_fabric_vertex_handle_t hVertexA,             ///< [in] handle of first fabric vertex instance
    ze_fabric_vertex_handle_t hVertexB,             ///< [in] handle of second fabric vertex instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric edges.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of fabric edges available.
                                                    ///< if count is greater than the number of fabric edges available, then
                                                    ///< the driver shall update the value with the correct number of fabric
                                                    ///< edges available.
    ze_fabric_edge_handle_t* phEdges                ///< [in,out][optional][range(0, *pCount)] array of handle of fabric edges.
                                                    ///< if count is less than the number of fabric edges available, then
                                                    ///< driver shall only retrieve that number of fabric edges.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFabricEdgeGetExp_t pfnGetExp = [&result] {
        auto pfnGetExp = ze_lib::context->zeDdiTable.load()->FabricEdgeExp.pfnGetExp;
        if( nullptr == pfnGetExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetExp( hVertexA, hVertexB, pCount, phEdges );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExp = ze_lib::context->zeDdiTable.load()->FabricEdgeExp.pfnGetExp;
    if( nullptr == pfnGetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExp( hVertexA, hVertexB, pCount, phEdges );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves fabric vertices connected by a fabric edge
/// 
/// @details
///     - A fabric vertex represents either a device or a switch connected to
///       other fabric vertices via a fabric edge.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEdge`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phVertexA`
///         + `nullptr == phVertexB`
ze_result_t ZE_APICALL
zeFabricEdgeGetVerticesExp(
    ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge instance
    ze_fabric_vertex_handle_t* phVertexA,           ///< [out] fabric vertex connected to one end of the given fabric edge.
    ze_fabric_vertex_handle_t* phVertexB            ///< [out] fabric vertex connected to other end of the given fabric edge.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFabricEdgeGetVerticesExp_t pfnGetVerticesExp = [&result] {
        auto pfnGetVerticesExp = ze_lib::context->zeDdiTable.load()->FabricEdgeExp.pfnGetVerticesExp;
        if( nullptr == pfnGetVerticesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVerticesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVerticesExp( hEdge, phVertexA, phVertexB );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVerticesExp = ze_lib::context->zeDdiTable.load()->FabricEdgeExp.pfnGetVerticesExp;
    if( nullptr == pfnGetVerticesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVerticesExp( hEdge, phVertexA, phVertexB );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the fabric edge.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEdge`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEdgeProperties`
ze_result_t ZE_APICALL
zeFabricEdgeGetPropertiesExp(
    ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
    ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnFabricEdgeGetPropertiesExp_t pfnGetPropertiesExp = [&result] {
        auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.load()->FabricEdgeExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPropertiesExp( hEdge, pEdgeProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.load()->FabricEdgeExp.pfnGetPropertiesExp;
    if( nullptr == pfnGetPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExp( hEdge, pEdgeProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query an event's timestamp value on the host, with domain preference.
/// 
/// @details
///     - For collecting *only* kernel timestamps, the application must ensure
///       the event was created from an event pool that was created using
///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
///     - For collecting synchronized timestamps, the application must ensure
///       the event was created from an event pool that was created using
///       ::ZE_EVENT_POOL_FLAG_KERNEL_MAPPED_TIMESTAMP flag. Kernel timestamps
///       are also available from this type of event pool, but there is a
///       performance cost.
///     - The destination memory will be unmodified if the event has not been
///       signaled.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support
///       ::ZE_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_NAME extension.
///     - The implementation must return all timestamps for the specified event
///       and device pair.
///     - The implementation must return all timestamps for all sub-devices when
///       device handle is parent device.
///     - The implementation may return all timestamps for sub-devices when
///       device handle is sub-device or may return 0 for count.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeEventQueryKernelTimestampsExt(
    ze_event_handle_t hEvent,                       ///< [in] handle of the event
    ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
    uint32_t* pCount,                               ///< [in,out] pointer to the number of event packets available.
                                                    ///<    - This value is implementation specific.
                                                    ///<    - if `*pCount` is zero, then the driver shall update the value with
                                                    ///< the total number of event packets available.
                                                    ///<    - if `*pCount` is greater than the number of event packets
                                                    ///< available, the driver shall update the value with the correct value.
                                                    ///<    - Buffer(s) for query results must be sized by the application to
                                                    ///< accommodate a minimum of `*pCount` elements.
    ze_event_query_kernel_timestamps_results_ext_properties_t* pResults ///< [in,out][optional][range(0, *pCount)] pointer to event query
                                                    ///< properties structure(s).
                                                    ///<    - This parameter may be null when `*pCount` is zero.
                                                    ///<    - if `*pCount` is less than the number of event packets available,
                                                    ///< the driver may only update `*pCount` elements, starting at element zero.
                                                    ///<    - if `*pCount` is greater than the number of event packets
                                                    ///< available, the driver may only update the valid elements.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnEventQueryKernelTimestampsExt_t pfnQueryKernelTimestampsExt = [&result] {
        auto pfnQueryKernelTimestampsExt = ze_lib::context->zeDdiTable.load()->Event.pfnQueryKernelTimestampsExt;
        if( nullptr == pfnQueryKernelTimestampsExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnQueryKernelTimestampsExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryKernelTimestampsExt = ze_lib::context->zeDdiTable.load()->Event.pfnQueryKernelTimestampsExt;
    if( nullptr == pfnQueryKernelTimestampsExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a ray tracing acceleration structure builder object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_RTAS_BUILDER_EXP_NAME extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDescriptor`
///         + `nullptr == phBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_BUILDER_EXP_VERSION_CURRENT < pDescriptor->builderVersion`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeRTASBuilderCreateExp(
    ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
    const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
    ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderCreateExp_t pfnCreateExp = [&result] {
        auto pfnCreateExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnCreateExp;
        if( nullptr == pfnCreateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExp( hDriver, pDescriptor, phBuilder );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnCreateExp;
    if( nullptr == pfnCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExp( hDriver, pDescriptor, phBuilder );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves ray tracing acceleration structure builder properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBuildOpDescriptor`
///         + `nullptr == pProperties`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXP_MAX < pBuildOpDescriptor->rtasFormat`
///         + `::ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_HIGH < pBuildOpDescriptor->buildQuality`
///         + `0x3 < pBuildOpDescriptor->buildFlags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeRTASBuilderGetBuildPropertiesExp(
    ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
    const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
    ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderGetBuildPropertiesExp_t pfnGetBuildPropertiesExp = [&result] {
        auto pfnGetBuildPropertiesExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnGetBuildPropertiesExp;
        if( nullptr == pfnGetBuildPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetBuildPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetBuildPropertiesExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnGetBuildPropertiesExp;
    if( nullptr == pfnGetBuildPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Checks ray tracing acceleration structure format compatibility
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXP_MAX < rtasFormatA`
///         + `::ZE_RTAS_FORMAT_EXP_MAX < rtasFormatB`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_SUCCESS
///         + An acceleration structure built with `rtasFormatA` is compatible with devices that report `rtasFormatB`.
///     - ::ZE_RESULT_EXP_ERROR_OPERANDS_INCOMPATIBLE
///         + An acceleration structure built with `rtasFormatA` is **not** compatible with devices that report `rtasFormatB`.
ze_result_t ZE_APICALL
zeDriverRTASFormatCompatibilityCheckExp(
    ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
    ze_rtas_format_exp_t rtasFormatA,               ///< [in] operand A
    ze_rtas_format_exp_t rtasFormatB                ///< [in] operand B
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnDriverRTASFormatCompatibilityCheckExp_t pfnRTASFormatCompatibilityCheckExp = [&result] {
        auto pfnRTASFormatCompatibilityCheckExp = ze_lib::context->zeDdiTable.load()->DriverExp.pfnRTASFormatCompatibilityCheckExp;
        if( nullptr == pfnRTASFormatCompatibilityCheckExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnRTASFormatCompatibilityCheckExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnRTASFormatCompatibilityCheckExp = ze_lib::context->zeDdiTable.load()->DriverExp.pfnRTASFormatCompatibilityCheckExp;
    if( nullptr == pfnRTASFormatCompatibilityCheckExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Build ray tracing acceleration structure
/// 
/// @details
///     - This function builds an acceleration structure of the scene consisting
///       of the specified geometry information and writes the acceleration
///       structure to the provided destination buffer. All types of geometries
///       can get freely mixed inside a scene.
///     - It is the user's responsibility to manage the acceleration structure
///       buffer allocation, de-allocation, and potential prefetching to the
///       device memory. The required size of the acceleration structure buffer
///       can be queried with the ::zeRTASBuilderGetBuildPropertiesExp function.
///       The acceleration structure buffer must be a shared USM allocation and
///       should be present on the host at build time. The referenced scene data
///       (index- and vertex- buffers) can be standard host allocations, and
///       will not be referenced into by the build acceleration structure.
///     - Before an acceleration structure can be built, the user must allocate
///       the memory for the acceleration structure buffer and scratch buffer
///       using sizes based on a query for the estimated size properties.
///     - When using the "worst-case" size for the acceleration structure
///       buffer, the acceleration structure construction will never fail with ::ZE_RESULT_EXP_RTAS_BUILD_RETRY.
///     - When using the "expected" size for the acceleration structure buffer,
///       the acceleration structure construction may fail with
///       ::ZE_RESULT_EXP_RTAS_BUILD_RETRY. If this happens, the user may resize
///       their acceleration structure buffer using the returned
///       `*pRtasBufferSizeBytes` value, which will be updated with an improved
///       size estimate that will likely result in a successful build.
///     - The acceleration structure construction is run on the host and is
///       synchronous, thus after the function returns with a successful result,
///       the acceleration structure may be used.
///     - All provided data buffers must be host-accessible.
///     - The acceleration structure buffer must be a USM allocation.
///     - A successfully constructed acceleration structure is entirely
///       self-contained. There is no requirement for input data to persist
///       beyond build completion.
///     - A successfully constructed acceleration structure is non-copyable.
///     - Acceleration structure construction may be parallelized by passing a
///       valid handle to a parallel operation object and joining that parallel
///       operation using ::zeRTASParallelOperationJoinExp with user-provided
///       worker threads.
///     - **Additional Notes**
///        - "The geometry infos array, geometry infos, and scratch buffer must
///       all be standard host memory allocations."
///        - "A pointer to a geometry info can be a null pointer, in which case
///       the geometry is treated as empty."
///        - "If no parallel operation handle is provided, the build is run
///       sequentially on the current thread."
///        - "A parallel operation object may only be associated with a single
///       acceleration structure build at a time."
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBuildOpDescriptor`
///         + `nullptr == pScratchBuffer`
///         + `nullptr == pRtasBuffer`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXP_MAX < pBuildOpDescriptor->rtasFormat`
///         + `::ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_HIGH < pBuildOpDescriptor->buildQuality`
///         + `0x3 < pBuildOpDescriptor->buildFlags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
///     - ::ZE_RESULT_EXP_RTAS_BUILD_DEFERRED
///         + Acceleration structure build completion is deferred to parallel operation join.
///     - ::ZE_RESULT_EXP_RTAS_BUILD_RETRY
///         + Acceleration structure build failed due to insufficient resources, retry the build operation with a larger acceleration structure buffer allocation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + Acceleration structure build failed due to parallel operation object participation in another build operation.
ze_result_t ZE_APICALL
zeRTASBuilderBuildExp(
    ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
    const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
    void* pScratchBuffer,                           ///< [in][range(0, `scratchBufferSizeBytes`)] scratch buffer to be used
                                                    ///< during acceleration structure construction
    size_t scratchBufferSizeBytes,                  ///< [in] size of scratch buffer, in bytes
    void* pRtasBuffer,                              ///< [in] pointer to destination buffer
    size_t rtasBufferSizeBytes,                     ///< [in] destination buffer size, in bytes
    ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in][optional] handle to parallel operation object
    void* pBuildUserPtr,                            ///< [in][optional] pointer passed to callbacks
    ze_rtas_aabb_exp_t* pBounds,                    ///< [in,out][optional] pointer to destination address for acceleration
                                                    ///< structure bounds
    size_t* pRtasBufferSizeBytes                    ///< [out][optional] updated acceleration structure size requirement, in
                                                    ///< bytes
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderBuildExp_t pfnBuildExp = [&result] {
        auto pfnBuildExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnBuildExp;
        if( nullptr == pfnBuildExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnBuildExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnBuildExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnBuildExp;
    if( nullptr == pfnBuildExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a ray tracing acceleration structure builder object
/// 
/// @details
///     - The implementation of this function may immediately release any
///       internal Host and Device resources associated with this builder.
///     - The application must **not** call this function from simultaneous
///       threads with the same builder handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeRTASBuilderDestroyExp(
    ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASBuilderDestroyExp_t pfnDestroyExp = [&result] {
        auto pfnDestroyExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExp( hBuilder );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zeDdiTable.load()->RTASBuilderExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( hBuilder );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a ray tracing acceleration structure builder parallel
///        operation object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_RTAS_BUILDER_EXP_NAME extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationCreateExp(
    ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
    ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationCreateExp_t pfnCreateExp = [&result] {
        auto pfnCreateExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnCreateExp;
        if( nullptr == pfnCreateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExp( hDriver, phParallelOperation );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnCreateExp;
    if( nullptr == pfnCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExp( hDriver, phParallelOperation );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves ray tracing acceleration structure builder parallel
///        operation properties
/// 
/// @details
///     - The application must first bind the parallel operation object to a
///       build operation before it may query the parallel operation properties.
///       In other words, the application must first call
///       ::zeRTASBuilderBuildExp with **hParallelOperation** before calling
///       this function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zeRTASParallelOperationGetPropertiesExp(
    ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
    ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationGetPropertiesExp_t pfnGetPropertiesExp = [&result] {
        auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPropertiesExp( hParallelOperation, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnGetPropertiesExp;
    if( nullptr == pfnGetPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExp( hParallelOperation, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Joins a parallel build operation
/// 
/// @details
///     - All worker threads return the same error code for the parallel build
///       operation upon build completion
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationJoinExp(
    ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationJoinExp_t pfnJoinExp = [&result] {
        auto pfnJoinExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnJoinExp;
        if( nullptr == pfnJoinExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnJoinExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnJoinExp( hParallelOperation );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnJoinExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnJoinExp;
    if( nullptr == pfnJoinExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnJoinExp( hParallelOperation );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a ray tracing acceleration structure builder parallel
///        operation object
/// 
/// @details
///     - The implementation of this function may immediately release any
///       internal Host and Device resources associated with this parallel
///       operation.
///     - The application must **not** call this function from simultaneous
///       threads with the same parallel operation handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationDestroyExp(
    ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnRTASParallelOperationDestroyExp_t pfnDestroyExp = [&result] {
        auto pfnDestroyExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExp( hParallelOperation );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zeDdiTable.load()->RTASParallelOperationExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( hParallelOperation );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves pitch information that can be used to allocate USM memory
///        for a given image.
/// 
/// @details
///     - Retrieves pitch for 2D image given the width, height and size in bytes
///     - The memory is then allocated using ::zeMemAllocDevice by providing
///       input size calculated as the returned pitch value multiplied by image height
///     - The application may call this function from simultaneous threads
///     - The implementation of this function must be thread-safe.
///     - The implementation of this function should be lock-free.
///     - The implementation must support ::ZE_BINDLESS_IMAGE_EXP_NAME extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
ze_result_t ZE_APICALL
zeMemGetPitchFor2dImage(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    size_t imageWidth,                              ///< [in] imageWidth
    size_t imageHeight,                             ///< [in] imageHeight
    unsigned int elementSizeInBytes,                ///< [in] Element size in bytes
    size_t * rowPitch                               ///< [out] rowPitch
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnMemGetPitchFor2dImage_t pfnGetPitchFor2dImage = [&result] {
        auto pfnGetPitchFor2dImage = ze_lib::context->zeDdiTable.load()->Mem.pfnGetPitchFor2dImage;
        if( nullptr == pfnGetPitchFor2dImage ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPitchFor2dImage;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPitchFor2dImage( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPitchFor2dImage = ze_lib::context->zeDdiTable.load()->Mem.pfnGetPitchFor2dImage;
    if( nullptr == pfnGetPitchFor2dImage ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPitchFor2dImage( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get bindless device offset for image
/// 
/// @details
///     - The application may call this function from simultaneous threads
///     - The implementation of this function must be thread-safe.
///     - The implementation of this function should be lock-free.
///     - The implementation must support ::ZE_BINDLESS_IMAGE_EXP_NAME
///       extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDeviceOffset`
ze_result_t ZE_APICALL
zeImageGetDeviceOffsetExp(
    ze_image_handle_t hImage,                       ///< [in] handle of the image
    uint64_t* pDeviceOffset                         ///< [out] bindless device offset for image
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnImageGetDeviceOffsetExp_t pfnGetDeviceOffsetExp = [&result] {
        auto pfnGetDeviceOffsetExp = ze_lib::context->zeDdiTable.load()->ImageExp.pfnGetDeviceOffsetExp;
        if( nullptr == pfnGetDeviceOffsetExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDeviceOffsetExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDeviceOffsetExp( hImage, pDeviceOffset );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDeviceOffsetExp = ze_lib::context->zeDdiTable.load()->ImageExp.pfnGetDeviceOffsetExp;
    if( nullptr == pfnGetDeviceOffsetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDeviceOffsetExp( hImage, pDeviceOffset );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list as the clone of another command list.
/// 
/// @details
///     - @deprecated since 1.17
///     - The source command list must be created with the
///       ::ZE_COMMAND_LIST_FLAG_EXP_CLONEABLE flag.
///     - The source command list must be closed prior to cloning.
///     - The source command list may be cloned while it is running on the
///       device.
///     - The cloned command list inherits all properties of the source command
///       list.
///     - The cloned command list must be destroyed prior to the source command
///       list.
///     - The application must only use the command list for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phClonedCommandList`
ze_result_t ZE_APICALL
zeCommandListCreateCloneExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle to source command list (the command list to clone)
    ze_command_list_handle_t* phClonedCommandList   ///< [out] pointer to handle of the cloned command list
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListCreateCloneExp_t pfnCreateCloneExp = [&result] {
        auto pfnCreateCloneExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnCreateCloneExp;
        if( nullptr == pfnCreateCloneExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateCloneExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateCloneExp( hCommandList, phClonedCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateCloneExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnCreateCloneExp;
    if( nullptr == pfnCreateCloneExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateCloneExp( hCommandList, phClonedCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends command lists to dispatch from an immediate command list.
/// 
/// @details
///     - @deprecated since 1.16. Please use
///       ::zeCommandListImmediateAppendCommandListsWithParameters.
///     - The application must call this function only with command lists
///       created with ::zeCommandListCreateImmediate.
///     - The command lists passed to this function in the `phCommandLists`
///       argument must be regular command lists (i.e. not immediate command
///       lists).
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandListImmediate`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phCommandLists`
ze_result_t ZE_APICALL
zeCommandListImmediateAppendCommandListsExp(
    ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
    uint32_t numCommandLists,                       ///< [in] number of command lists
    ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] handles of command lists
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
                                                    ///<    - if not null, this event is signaled after the completion of all
                                                    ///< appended command lists
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing appended
                                                    ///< command lists; must be 0 if nullptr == phWaitEvents
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing appended command lists.
                                                    ///<    - if not null, all wait events must be satisfied prior to the start
                                                    ///< of any appended command list(s)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListImmediateAppendCommandListsExp_t pfnImmediateAppendCommandListsExp = [&result] {
        auto pfnImmediateAppendCommandListsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnImmediateAppendCommandListsExp;
        if( nullptr == pfnImmediateAppendCommandListsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnImmediateAppendCommandListsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnImmediateAppendCommandListsExp( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnImmediateAppendCommandListsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnImmediateAppendCommandListsExp;
    if( nullptr == pfnImmediateAppendCommandListsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnImmediateAppendCommandListsExp( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends command lists to dispatch from an immediate command list with
///        additional parameters.
/// 
/// @details
///     - The application must call this function only with command lists
///       created with ::zeCommandListCreateImmediate.
///     - The command lists passed to this function in the `phCommandLists`
///       argument must be regular command lists (i.e. not immediate command
///       lists).
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandListImmediate`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phCommandLists`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + an extension passed via pNext is not supported
ze_result_t ZE_APICALL
zeCommandListImmediateAppendCommandListsWithParameters(
    ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
    uint32_t numCommandLists,                       ///< [in] number of command lists
    ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] handles of command lists
    const void* pNext,                              ///< [in][optional] additional extensions passed to the function
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
                                                    ///<    - if not null, this event is signaled after the completion of all
                                                    ///< appended command lists
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing appended
                                                    ///< command lists; must be 0 if nullptr == phWaitEvents
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing appended command lists.
                                                    ///<    - if not null, all wait events must be satisfied prior to the start
                                                    ///< of any appended command list(s)
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListImmediateAppendCommandListsWithParameters_t pfnImmediateAppendCommandListsWithParameters = [&result] {
        auto pfnImmediateAppendCommandListsWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateAppendCommandListsWithParameters;
        if( nullptr == pfnImmediateAppendCommandListsWithParameters ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnImmediateAppendCommandListsWithParameters;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnImmediateAppendCommandListsWithParameters( hCommandListImmediate, numCommandLists, phCommandLists, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnImmediateAppendCommandListsWithParameters = ze_lib::context->zeDdiTable.load()->CommandList.pfnImmediateAppendCommandListsWithParameters;
    if( nullptr == pfnImmediateAppendCommandListsWithParameters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnImmediateAppendCommandListsWithParameters( hCommandListImmediate, numCommandLists, phCommandLists, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a unique command identifier for the next command to be
///        appended to a command list.
/// 
/// @details
///     - This function may only be called for a mutable command list.
///     - This function may not be called on a closed command list.
///     - This function may be called from simultaneous threads with the same
///       command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == pCommandId`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xff < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeCommandListGetNextCommandIdExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    const ze_mutable_command_id_exp_desc_t* desc,   ///< [in] pointer to mutable command identifier descriptor
    uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListGetNextCommandIdExp_t pfnGetNextCommandIdExp = [&result] {
        auto pfnGetNextCommandIdExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnGetNextCommandIdExp;
        if( nullptr == pfnGetNextCommandIdExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetNextCommandIdExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetNextCommandIdExp( hCommandList, desc, pCommandId );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetNextCommandIdExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnGetNextCommandIdExp;
    if( nullptr == pfnGetNextCommandIdExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetNextCommandIdExp( hCommandList, desc, pCommandId );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns a unique command identifier for the next command to be
///        appended to a command list. Provides possible kernel handles for
///        kernel mutation when ::ZE_MUTABLE_COMMAND_EXP_FLAG_KERNEL_INSTRUCTION
///        flag is present.
/// 
/// @details
///     - This function may only be called for a mutable command list.
///     - This function may not be called on a closed command list.
///     - This function may be called from simultaneous threads with the same
///       command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == pCommandId`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xff < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION
ze_result_t ZE_APICALL
zeCommandListGetNextCommandIdWithKernelsExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    const ze_mutable_command_id_exp_desc_t* desc,   ///< [in][out] pointer to mutable command identifier descriptor
    uint32_t numKernels,                            ///< [in][optional] number of entries on phKernels list
    ze_kernel_handle_t* phKernels,                  ///< [in][optional][range(0, numKernels)] list of kernels that user can
                                                    ///< switch between using ::zeCommandListUpdateMutableCommandKernelsExp
                                                    ///< call
    uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListGetNextCommandIdWithKernelsExp_t pfnGetNextCommandIdWithKernelsExp = [&result] {
        auto pfnGetNextCommandIdWithKernelsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnGetNextCommandIdWithKernelsExp;
        if( nullptr == pfnGetNextCommandIdWithKernelsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetNextCommandIdWithKernelsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetNextCommandIdWithKernelsExp( hCommandList, desc, numKernels, phKernels, pCommandId );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetNextCommandIdWithKernelsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnGetNextCommandIdWithKernelsExp;
    if( nullptr == pfnGetNextCommandIdWithKernelsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetNextCommandIdWithKernelsExp( hCommandList, desc, numKernels, phKernels, pCommandId );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Updates mutable commands.
/// 
/// @details
///     - This function may only be called for a mutable command list.
///     - The application must synchronize mutable command list execution before
///       calling this function.
///     - The application must close a mutable command list after completing all
///       updates.
///     - This function must not be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + Invalid kernel argument or not matching update descriptor provided
ze_result_t ZE_APICALL
zeCommandListUpdateMutableCommandsExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    const ze_mutable_commands_exp_desc_t* desc      ///< [in] pointer to mutable commands descriptor; multiple descriptors may
                                                    ///< be chained via `pNext` member
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListUpdateMutableCommandsExp_t pfnUpdateMutableCommandsExp = [&result] {
        auto pfnUpdateMutableCommandsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandsExp;
        if( nullptr == pfnUpdateMutableCommandsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnUpdateMutableCommandsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnUpdateMutableCommandsExp( hCommandList, desc );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnUpdateMutableCommandsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandsExp;
    if( nullptr == pfnUpdateMutableCommandsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnUpdateMutableCommandsExp( hCommandList, desc );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query whether a command list was created with the mutable command list
///        extension.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIsMutable`
ze_result_t ZE_APICALL
zeCommandListIsMutableExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_bool_t* pIsMutable                           ///< [out] pointer bool determining whether command list was created with
                                                    ///< mutable extension
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListIsMutableExp_t pfnIsMutableExp = [&result] {
        auto pfnIsMutableExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnIsMutableExp;
        if( nullptr == pfnIsMutableExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnIsMutableExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnIsMutableExp( hCommandList, pIsMutable );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnIsMutableExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnIsMutableExp;
    if( nullptr == pfnIsMutableExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnIsMutableExp( hCommandList, pIsMutable );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Updates the signal event for a mutable command in a mutable command
///        list.
/// 
/// @details
///     - This function may only be called for a mutable command list.
///     - The type, scope and flags of the signal event must match those of the
///       source command.
///     - The application must synchronize mutable command list execution before
///       calling this function.
///     - The application must close a mutable command list after completing all
///       updates.
///     - This function must not be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zeCommandListUpdateMutableCommandSignalEventExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint64_t commandId,                             ///< [in] command identifier
    ze_event_handle_t hSignalEvent                  ///< [in][optional] handle of the event to signal on completion
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListUpdateMutableCommandSignalEventExp_t pfnUpdateMutableCommandSignalEventExp = [&result] {
        auto pfnUpdateMutableCommandSignalEventExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandSignalEventExp;
        if( nullptr == pfnUpdateMutableCommandSignalEventExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnUpdateMutableCommandSignalEventExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnUpdateMutableCommandSignalEventExp( hCommandList, commandId, hSignalEvent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnUpdateMutableCommandSignalEventExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandSignalEventExp;
    if( nullptr == pfnUpdateMutableCommandSignalEventExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnUpdateMutableCommandSignalEventExp( hCommandList, commandId, hSignalEvent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Updates the wait events for a mutable command in a mutable command
///        list.
/// 
/// @details
///     - This function may only be called for a mutable command list.
///     - The number of wait events must match that of the source command.
///     - The type, scope and flags of the wait events must match those of the
///       source command.
///     - Passing `nullptr` as the wait events will update the command to not
///       wait on any events prior to dispatch.
///     - Passing `nullptr` as an event on event wait list will remove event
///       dependency from this wait list slot.
///     - The application must synchronize mutable command list execution before
///       calling this function.
///     - The application must close a mutable command list after completing all
///       updates.
///     - This function must not be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The `numWaitEvents` parameter does not match that of the original command.
ze_result_t ZE_APICALL
zeCommandListUpdateMutableCommandWaitEventsExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint64_t commandId,                             ///< [in] command identifier
    uint32_t numWaitEvents,                         ///< [in][optional] the number of wait events
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListUpdateMutableCommandWaitEventsExp_t pfnUpdateMutableCommandWaitEventsExp = [&result] {
        auto pfnUpdateMutableCommandWaitEventsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandWaitEventsExp;
        if( nullptr == pfnUpdateMutableCommandWaitEventsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnUpdateMutableCommandWaitEventsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnUpdateMutableCommandWaitEventsExp( hCommandList, commandId, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnUpdateMutableCommandWaitEventsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandWaitEventsExp;
    if( nullptr == pfnUpdateMutableCommandWaitEventsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnUpdateMutableCommandWaitEventsExp( hCommandList, commandId, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Updates the kernel for a mutable command in a mutable command list.
/// 
/// @details
///     - This function may only be called for a mutable command list.
///     - The kernel handle must be from the provided list for given command id.
///     - The application must synchronize mutable command list execution before
///       calling this function.
///     - The application must close a mutable command list after completing all
///       updates.
///     - This function must not be called from simultaneous threads with the
///       same command list handle.
///     - This function must be called before updating kernel arguments and
///       dispatch parameters, when kernel is mutated.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///     - ::ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET
///     - ::ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE
///     - ::ZE_RESULT_ERROR_UNKNOWN
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCommandId`
///         + `nullptr == phKernels`
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_HANDLE
///         + Invalid kernel handle provided for the mutation kernel instruction operation.
ze_result_t ZE_APICALL
zeCommandListUpdateMutableCommandKernelsExp(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numKernels,                            ///< [in] the number of kernels to update
    uint64_t* pCommandId,                           ///< [in][range(0, numKernels)] command identifier
    ze_kernel_handle_t* phKernels                   ///< [in][range(0, numKernels)] handle of the kernel for a command
                                                    ///< identifier to switch to
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const ze_pfnCommandListUpdateMutableCommandKernelsExp_t pfnUpdateMutableCommandKernelsExp = [&result] {
        auto pfnUpdateMutableCommandKernelsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandKernelsExp;
        if( nullptr == pfnUpdateMutableCommandKernelsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnUpdateMutableCommandKernelsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnUpdateMutableCommandKernelsExp( hCommandList, numKernels, pCommandId, phKernels );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnUpdateMutableCommandKernelsExp = ze_lib::context->zeDdiTable.load()->CommandListExp.pfnUpdateMutableCommandKernelsExp;
    if( nullptr == pfnUpdateMutableCommandKernelsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnUpdateMutableCommandKernelsExp( hCommandList, numKernels, pCommandId, phKernels );
    #endif
}

} // extern "C"
