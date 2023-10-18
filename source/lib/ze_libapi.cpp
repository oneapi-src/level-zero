/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
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
///     - The application must call this function before calling any other
///       function.
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
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < flags`
ze_result_t ZE_APICALL
zeInit(
    ze_init_flags_t flags                           ///< [in] initialization flags.
                                                    ///< must be 0 (default) or a combination of ::ze_init_flag_t.
    )
{
    static ze_result_t result = ZE_RESULT_SUCCESS;
    std::call_once(ze_lib::context->initOnce, [flags]() {
        result = ze_lib::context->Init(flags, false);

        if( ZE_RESULT_SUCCESS != result )
            return result;

        if(ze_lib::context->inTeardown) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        auto pfnInit = ze_lib::context->zeDdiTable.Global.pfnInit;
        if( nullptr == pfnInit ) {
            if(!ze_lib::context->isInitialized)
                return ZE_RESULT_ERROR_UNINITIALIZED;
            else
                return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }

        result = pfnInit( flags );
        return result;
    });

    if(ze_lib::context->inTeardown) {
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves driver instances
/// 
/// @details
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zeDdiTable.Driver.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( pCount, phDrivers );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the specified driver
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetApiVersion = ze_lib::context->zeDdiTable.Driver.pfnGetApiVersion;
    if( nullptr == pfnGetApiVersion ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetApiVersion( hDriver, version );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.Driver.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDriver, pDriverProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcProperties = ze_lib::context->zeDdiTable.Driver.pfnGetIpcProperties;
    if( nullptr == pfnGetIpcProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcProperties( hDriver, pIpcProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExtensionProperties = ze_lib::context->zeDdiTable.Driver.pfnGetExtensionProperties;
    if( nullptr == pfnGetExtensionProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExtensionFunctionAddress = ze_lib::context->zeDdiTable.Driver.pfnGetExtensionFunctionAddress;
    if( nullptr == pfnGetExtensionFunctionAddress ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLastErrorDescription = ze_lib::context->zeDdiTable.Driver.pfnGetLastErrorDescription;
    if( nullptr == pfnGetLastErrorDescription ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLastErrorDescription( hDriver, ppString );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves devices within a driver
/// 
/// @details
///     - Multiple calls to this function will return identical device handles,
///       in the same order.
///     - The number and order of handles returned from this function is
///       affected by the ::ZE_AFFINITY_MASK and ::ZE_ENABLE_PCI_ID_DEVICE_ORDER
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zeDdiTable.Device.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( hDriver, pCount, phDevices );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRootDevice = ze_lib::context->zeDdiTable.Device.pfnGetRootDevice;
    if( nullptr == pfnGetRootDevice ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRootDevice( hDevice, phRootDevice );
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
///       ::ZE_AFFINITY_MASK environment variable.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSubDevices = ze_lib::context->zeDdiTable.Device.pfnGetSubDevices;
    if( nullptr == pfnGetSubDevices ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSubDevices( hDevice, pCount, phSubdevices );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.Device.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDevice, pDeviceProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetComputeProperties = ze_lib::context->zeDdiTable.Device.pfnGetComputeProperties;
    if( nullptr == pfnGetComputeProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetComputeProperties( hDevice, pComputeProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetModuleProperties = ze_lib::context->zeDdiTable.Device.pfnGetModuleProperties;
    if( nullptr == pfnGetModuleProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetModuleProperties( hDevice, pModuleProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves command queue group properties of the device.
/// 
/// @details
///     - Properties are reported for each physical command queue type supported
///       by the device.
///     - Multiple calls to this function will return properties in the same
///       order.
///     - The order in which the properties are returned defines the command
///       queue group's ordinal.
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zeDeviceGetCommandQueueGroupProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of command queue group properties available.
                                                    ///< if count is greater than the number of command queue group properties
                                                    ///< available, then the driver shall update the value with the correct
                                                    ///< number of command queue group properties available.
    ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< command queue group properties.
                                                    ///< if count is less than the number of command queue group properties
                                                    ///< available, then driver shall only retrieve that number of command
                                                    ///< queue group properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCommandQueueGroupProperties = ze_lib::context->zeDdiTable.Device.pfnGetCommandQueueGroupProperties;
    if( nullptr == pfnGetCommandQueueGroupProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMemoryProperties = ze_lib::context->zeDdiTable.Device.pfnGetMemoryProperties;
    if( nullptr == pfnGetMemoryProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMemoryAccessProperties = ze_lib::context->zeDdiTable.Device.pfnGetMemoryAccessProperties;
    if( nullptr == pfnGetMemoryAccessProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCacheProperties = ze_lib::context->zeDdiTable.Device.pfnGetCacheProperties;
    if( nullptr == pfnGetCacheProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCacheProperties( hDevice, pCount, pCacheProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetImageProperties = ze_lib::context->zeDdiTable.Device.pfnGetImageProperties;
    if( nullptr == pfnGetImageProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetImageProperties( hDevice, pImageProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExternalMemoryProperties = ze_lib::context->zeDdiTable.Device.pfnGetExternalMemoryProperties;
    if( nullptr == pfnGetExternalMemoryProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetP2PProperties = ze_lib::context->zeDdiTable.Device.pfnGetP2PProperties;
    if( nullptr == pfnGetP2PProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCanAccessPeer = ze_lib::context->zeDdiTable.Device.pfnCanAccessPeer;
    if( nullptr == pfnCanAccessPeer ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCanAccessPeer( hDevice, hPeerDevice, value );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetStatus = ze_lib::context->zeDdiTable.Device.pfnGetStatus;
    if( nullptr == pfnGetStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetStatus( hDevice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns synchronized Host and device global timestamps.
/// 
/// @details
///     - The application may call this function from simultaneous threads with
///       the same device handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == hostTimestamp`
///         + `nullptr == deviceTimestamp`
ze_result_t ZE_APICALL
zeDeviceGetGlobalTimestamps(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                    ///< Device's global timestamp value
    uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                    ///< Host's global timestamp value
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetGlobalTimestamps = ze_lib::context->zeDdiTable.Device.pfnGetGlobalTimestamps;
    if( nullptr == pfnGetGlobalTimestamps ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phContext`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < desc->flags`
ze_result_t ZE_APICALL
zeContextCreate(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
    const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
    ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.Context.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hDriver, desc, phContext );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phContext`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < desc->flags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateEx = ze_lib::context->zeDdiTable.Context.pfnCreateEx;
    if( nullptr == pfnCreateEx ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateEx( hDriver, desc, numDevices, phDevices, phContext );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeContextDestroy(
    ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.Context.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hContext );
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
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetStatus = ze_lib::context->zeDdiTable.Context.pfnGetStatus;
    if( nullptr == pfnGetStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetStatus( hContext );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///         + `::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS < desc->mode`
///         + `::ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_HIGH < desc->priority`
ze_result_t ZE_APICALL
zeCommandQueueCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.CommandQueue.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phCommandQueue );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeCommandQueueDestroy(
    ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.CommandQueue.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hCommandQueue );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnExecuteCommandLists = ze_lib::context->zeDdiTable.CommandQueue.pfnExecuteCommandLists;
    if( nullptr == pfnExecuteCommandLists ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSynchronize = ze_lib::context->zeDdiTable.CommandQueue.pfnSynchronize;
    if( nullptr == pfnSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSynchronize( hCommandQueue, timeout );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < desc->flags`
ze_result_t ZE_APICALL
zeCommandListCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.CommandList.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phCommandList );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == altdesc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < altdesc->flags`
///         + `::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS < altdesc->mode`
///         + `::ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_HIGH < altdesc->priority`
ze_result_t ZE_APICALL
zeCommandListCreateImmediate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateImmediate = ze_lib::context->zeDdiTable.CommandList.pfnCreateImmediate;
    if( nullptr == pfnCreateImmediate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeCommandListDestroy(
    ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.CommandList.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hCommandList );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zeCommandListClose(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnClose = ze_lib::context->zeDdiTable.CommandList.pfnClose;
    if( nullptr == pfnClose ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnClose( hCommandList );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zeCommandListReset(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zeDdiTable.CommandList.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hCommandList );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendWriteGlobalTimestamp = ze_lib::context->zeDdiTable.CommandList.pfnAppendWriteGlobalTimestamp;
    if( nullptr == pfnAppendWriteGlobalTimestamp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSynchronize = ze_lib::context->zeDdiTable.CommandList.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSynchronize( hCommandList, timeout );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendBarrier = ze_lib::context->zeDdiTable.CommandList.pfnAppendBarrier;
    if( nullptr == pfnAppendBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryRangesBarrier = ze_lib::context->zeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;
    if( nullptr == pfnAppendMemoryRangesBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
ze_result_t ZE_APICALL
zeContextSystemBarrier(
    ze_context_handle_t hContext,                   ///< [in] handle of context object
    ze_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSystemBarrier = ze_lib::context->zeDdiTable.Context.pfnSystemBarrier;
    if( nullptr == pfnSystemBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSystemBarrier( hContext, hDevice );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryCopy = ze_lib::context->zeDdiTable.CommandList.pfnAppendMemoryCopy;
    if( nullptr == pfnAppendMemoryCopy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Initializes host, device, or shared memory.
/// 
/// @details
///     - The application must ensure the memory pointed to by dstptr is
///       accessible by the device on which the command list was created.
///     - The implementation must not access the memory pointed to by dstptr as
///       it is free to be modified by either the Host or device up until
///       execution.
///     - The value to initialize memory to is described by the pattern and the
///       pattern size.
///     - The pattern size must be a power-of-two and less than or equal to the
///       `maxMemoryFillPatternSize` member of
///       ::ze_command_queue_group_properties_t.
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pattern`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryFill = ze_lib::context->zeDdiTable.CommandList.pfnAppendMemoryFill;
    if( nullptr == pfnAppendMemoryFill ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryCopyRegion = ze_lib::context->zeDdiTable.CommandList.pfnAppendMemoryCopyRegion;
    if( nullptr == pfnAppendMemoryCopyRegion ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryCopyFromContext = ze_lib::context->zeDdiTable.CommandList.pfnAppendMemoryCopyFromContext;
    if( nullptr == pfnAppendMemoryCopyFromContext ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopy = ze_lib::context->zeDdiTable.CommandList.pfnAppendImageCopy;
    if( nullptr == pfnAppendImageCopy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyRegion = ze_lib::context->zeDdiTable.CommandList.pfnAppendImageCopyRegion;
    if( nullptr == pfnAppendImageCopyRegion ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyToMemory = ze_lib::context->zeDdiTable.CommandList.pfnAppendImageCopyToMemory;
    if( nullptr == pfnAppendImageCopyToMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyFromMemory = ze_lib::context->zeDdiTable.CommandList.pfnAppendImageCopyFromMemory;
    if( nullptr == pfnAppendImageCopyFromMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemoryPrefetch = ze_lib::context->zeDdiTable.CommandList.pfnAppendMemoryPrefetch;
    if( nullptr == pfnAppendMemoryPrefetch ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemoryPrefetch( hCommandList, ptr, size );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MEMORY_ADVICE_CLEAR_SYSTEM_MEMORY_PREFERRED_LOCATION < advice`
ze_result_t ZE_APICALL
zeCommandListAppendMemAdvise(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
    ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMemAdvise = ze_lib::context->zeDdiTable.CommandList.pfnAppendMemAdvise;
    if( nullptr == pfnAppendMemAdvise ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < desc->flags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.EventPool.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeEventPoolDestroy(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.EventPool.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hEventPool );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phEvent`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < desc->signal`
///         + `0x7 < desc->wait`
ze_result_t ZE_APICALL
zeEventCreate(
    ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.Event.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hEventPool, desc, phEvent );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeEventDestroy(
    ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.Event.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hEvent );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcHandle = ze_lib::context->zeDdiTable.EventPool.pfnGetIpcHandle;
    if( nullptr == pfnGetIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcHandle( hEventPool, phIpc );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
ze_result_t ZE_APICALL
zeEventPoolPutIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                    ///< handle
    ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPutIpcHandle = ze_lib::context->zeDdiTable.EventPool.pfnPutIpcHandle;
    if( nullptr == pfnPutIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPutIpcHandle( hContext, hIpc );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOpenIpcHandle = ze_lib::context->zeDdiTable.EventPool.pfnOpenIpcHandle;
    if( nullptr == pfnOpenIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOpenIpcHandle( hContext, hIpc, phEventPool );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEventPool`
ze_result_t ZE_APICALL
zeEventPoolCloseIpcHandle(
    ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCloseIpcHandle = ze_lib::context->zeDdiTable.EventPool.pfnCloseIpcHandle;
    if( nullptr == pfnCloseIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCloseIpcHandle( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a signal of the event from the device into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendSignalEvent = ze_lib::context->zeDdiTable.CommandList.pfnAppendSignalEvent;
    if( nullptr == pfnAppendSignalEvent ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendSignalEvent( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends wait on event(s) on the device into a command list.
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
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendWaitOnEvents = ze_lib::context->zeDdiTable.CommandList.pfnAppendWaitOnEvents;
    if( nullptr == pfnAppendWaitOnEvents ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeEventHostSignal(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSignal = ze_lib::context->zeDdiTable.Event.pfnHostSignal;
    if( nullptr == pfnHostSignal ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSignal( hEvent );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSynchronize = ze_lib::context->zeDdiTable.Event.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSynchronize( hEvent, timeout );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryStatus = ze_lib::context->zeDdiTable.Event.pfnQueryStatus;
    if( nullptr == pfnQueryStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryStatus( hEvent );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendEventReset = ze_lib::context->zeDdiTable.CommandList.pfnAppendEventReset;
    if( nullptr == pfnAppendEventReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendEventReset( hCommandList, hEvent );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEvent`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zeEventHostReset(
    ze_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostReset = ze_lib::context->zeDdiTable.Event.pfnHostReset;
    if( nullptr == pfnHostReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostReset( hEvent );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryKernelTimestamp = ze_lib::context->zeDdiTable.Event.pfnQueryKernelTimestamp;
    if( nullptr == pfnQueryKernelTimestamp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryKernelTimestamp( hEvent, dstptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends a query of an events' timestamp value(s) into a command list.
/// 
/// @details
///     - The application must ensure the events are accessible by the device on
///       which the command list was created.
///     - The application must ensure the events were created from an event pool
///       that was created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendQueryKernelTimestamps = ze_lib::context->zeDdiTable.CommandList.pfnAppendQueryKernelTimestamps;
    if( nullptr == pfnAppendQueryKernelTimestamps ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phFence`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < desc->flags`
ze_result_t ZE_APICALL
zeFenceCreate(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.Fence.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hCommandQueue, desc, phFence );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeFenceDestroy(
    ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.Fence.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hFence );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnHostSynchronize = ze_lib::context->zeDdiTable.Fence.pfnHostSynchronize;
    if( nullptr == pfnHostSynchronize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnHostSynchronize( hFence, timeout );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryStatus = ze_lib::context->zeDdiTable.Fence.pfnQueryStatus;
    if( nullptr == pfnQueryStatus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryStatus( hFence );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFence`
ze_result_t ZE_APICALL
zeFenceReset(
    ze_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zeDdiTable.Fence.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hFence );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == pImageProperties`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///         + `::ZE_IMAGE_TYPE_BUFFER < desc->type`
ze_result_t ZE_APICALL
zeImageGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.Image.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDevice, desc, pImageProperties );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phImage`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///         + `::ZE_IMAGE_TYPE_BUFFER < desc->type`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT
ze_result_t ZE_APICALL
zeImageCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.Image.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phImage );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hImage`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeImageDestroy(
    ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.Image.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hImage );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < device_desc->flags`
///         + `0xf < host_desc->flags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAllocShared = ze_lib::context->zeDdiTable.Mem.pfnAllocShared;
    if( nullptr == pfnAllocShared ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < device_desc->flags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAllocDevice = ze_lib::context->zeDdiTable.Mem.pfnAllocDevice;
    if( nullptr == pfnAllocDevice ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < host_desc->flags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAllocHost = ze_lib::context->zeDdiTable.Mem.pfnAllocHost;
    if( nullptr == pfnAllocHost ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAllocHost( hContext, host_desc, size, alignment, pptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory on the
///        context.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the memory before it is freed
///     - The implementation of this function may immediately free all Host and
///       Device allocations associated with this memory
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFree = ze_lib::context->zeDdiTable.Mem.pfnFree;
    if( nullptr == pfnFree ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFree( hContext, ptr );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAllocProperties = ze_lib::context->zeDdiTable.Mem.pfnGetAllocProperties;
    if( nullptr == pfnGetAllocProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
ze_result_t ZE_APICALL
zeMemGetAddressRange(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAddressRange = ze_lib::context->zeDdiTable.Mem.pfnGetAddressRange;
    if( nullptr == pfnGetAddressRange ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAddressRange( hContext, ptr, pBase, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle for the specified allocation
/// 
/// @details
///     - Takes a pointer to a device memory allocation and creates an IPC
///       memory handle for exporting it for use in another process.
///     - The pointer must be base pointer of a device or host memory
///       allocation; i.e. the value returned from ::zeMemAllocDevice or from
///       ::zeMemAllocHost, respectively.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcHandle = ze_lib::context->zeDdiTable.Mem.pfnGetIpcHandle;
    if( nullptr == pfnGetIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcHandle( hContext, ptr, pIpcHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle out of a file descriptor
/// 
/// @details
///     - Handle passed must be a valid file descriptor obtained with
///       ::ze_external_memory_export_fd_t via ::zeMemGetAllocProperties.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIpcHandleFromFileDescriptorExp = ze_lib::context->zeDdiTable.MemExp.pfnGetIpcHandleFromFileDescriptorExp;
    if( nullptr == pfnGetIpcHandleFromFileDescriptorExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFileDescriptorFromIpcHandleExp = ze_lib::context->zeDdiTable.MemExp.pfnGetFileDescriptorFromIpcHandleExp;
    if( nullptr == pfnGetFileDescriptorFromIpcHandleExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns an IPC memory handle to the driver
/// 
/// @details
///     - This call may be used for IPC handles previously obtained with either
///       ::zeMemGetIpcHandle or with ::ze_external_memory_export_fd_t via ::zeMemGetAllocProperties.
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
ze_result_t ZE_APICALL
zeMemPutIpcHandle(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPutIpcHandle = ze_lib::context->zeDdiTable.Mem.pfnPutIpcHandle;
    if( nullptr == pfnPutIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPutIpcHandle( hContext, handle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer on the
///        context.
/// 
/// @details
///     - Takes an IPC memory handle from a remote process and associates it
///       with a device pointer usable in this process.
///     - The device pointer in this process should not be freed with
///       ::zeMemFree, but rather with ::zeMemCloseIpcHandle.
///     - Multiple calls to this function with the same IPC handle will return
///       unique pointers.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < flags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOpenIpcHandle = ze_lib::context->zeDdiTable.Mem.pfnOpenIpcHandle;
    if( nullptr == pfnOpenIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCloseIpcHandle = ze_lib::context->zeDdiTable.Mem.pfnCloseIpcHandle;
    if( nullptr == pfnCloseIpcHandle ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCloseIpcHandle( hContext, ptr );
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
///       ::ZE_RESULT_INVALID_ARGUMENT is returned.
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7f < attr`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetAtomicAccessAttributeExp = ze_lib::context->zeDdiTable.MemExp.pfnSetAtomicAccessAttributeExp;
    if( nullptr == pfnSetAtomicAccessAttributeExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAtomicAccessAttributeExp = ze_lib::context->zeDdiTable.MemExp.pfnGetAtomicAccessAttributeExp;
    if( nullptr == pfnGetAtomicAccessAttributeExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pInputModule`
///         + `nullptr == phModule`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MODULE_FORMAT_NATIVE < desc->format`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.Module.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeModuleDestroy(
    ze_module_handle_t hModule                      ///< [in][release] handle of the module
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.Module.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hModule );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDynamicLink = ze_lib::context->zeDdiTable.Module.pfnDynamicLink;
    if( nullptr == pfnDynamicLink ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDynamicLink( numModules, phModules, phLinkLog );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModuleBuildLog`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeModuleBuildLogDestroy(
    ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.ModuleBuildLog.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hModuleBuildLog );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetString = ze_lib::context->zeDdiTable.ModuleBuildLog.pfnGetString;
    if( nullptr == pfnGetString ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetNativeBinary = ze_lib::context->zeDdiTable.Module.pfnGetNativeBinary;
    if( nullptr == pfnGetNativeBinary ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve global variable pointer from Module.
/// 
/// @details
///     - The application may query global pointer from any module that either
///       exports or imports it.
///     - The application must dynamically link a module that imports a global
///       before the global pointer can be queried from it.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetGlobalPointer = ze_lib::context->zeDdiTable.Module.pfnGetGlobalPointer;
    if( nullptr == pfnGetGlobalPointer ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetKernelNames = ze_lib::context->zeDdiTable.Module.pfnGetKernelNames;
    if( nullptr == pfnGetKernelNames ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetKernelNames( hModule, pCount, pNames );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.Module.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hModule, pModuleProperties );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pKernelName`
///         + `nullptr == phKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < desc->flags`
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_NAME
///     - ::ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED
ze_result_t ZE_APICALL
zeKernelCreate(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
    ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.Kernel.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hModule, desc, phKernel );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeKernelDestroy(
    ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.Kernel.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hKernel );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFunctionPointer = ze_lib::context->zeDdiTable.Module.pfnGetFunctionPointer;
    if( nullptr == pfnGetFunctionPointer ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetGroupSize = ze_lib::context->zeDdiTable.Kernel.pfnSetGroupSize;
    if( nullptr == pfnSetGroupSize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSuggestGroupSize = ze_lib::context->zeDdiTable.Kernel.pfnSuggestGroupSize;
    if( nullptr == pfnSuggestGroupSize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested max group count for a cooperative kernel.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSuggestMaxCooperativeGroupCount = ze_lib::context->zeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;
    if( nullptr == pfnSuggestMaxCooperativeGroupCount ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX
///     - ::ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE
ze_result_t ZE_APICALL
zeKernelSetArgumentValue(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetArgumentValue = ze_lib::context->zeDdiTable.Kernel.pfnSetArgumentValue;
    if( nullptr == pfnSetArgumentValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < flags`
ze_result_t ZE_APICALL
zeKernelSetIndirectAccess(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetIndirectAccess = ze_lib::context->zeDdiTable.Kernel.pfnSetIndirectAccess;
    if( nullptr == pfnSetIndirectAccess ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetIndirectAccess( hKernel, flags );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetIndirectAccess = ze_lib::context->zeDdiTable.Kernel.pfnGetIndirectAccess;
    if( nullptr == pfnGetIndirectAccess ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetIndirectAccess( hKernel, pFlags );
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
                                                    ///< a null-terminating character, is returned in pSize.
                                                    ///< Otherwise, pString must point to valid application memory that is
                                                    ///< greater than or equal to *pSize bytes in length, and on return the
                                                    ///< pointed-to string will contain a space-separated list of kernel source attributes.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSourceAttributes = ze_lib::context->zeDdiTable.Kernel.pfnGetSourceAttributes;
    if( nullptr == pfnGetSourceAttributes ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSourceAttributes( hKernel, pSize, pString );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
ze_result_t ZE_APICALL
zeKernelSetCacheConfig(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                    ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetCacheConfig = ze_lib::context->zeDdiTable.Kernel.pfnSetCacheConfig;
    if( nullptr == pfnSetCacheConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetCacheConfig( hKernel, flags );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zeDdiTable.Kernel.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hKernel, pKernelProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetName = ze_lib::context->zeDdiTable.Kernel.pfnGetName;
    if( nullptr == pfnGetName ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetName( hKernel, pSize, pName );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchKernel = ze_lib::context->zeDdiTable.CommandList.pfnAppendLaunchKernel;
    if( nullptr == pfnAppendLaunchKernel ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchCooperativeKernel = ze_lib::context->zeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel;
    if( nullptr == pfnAppendLaunchCooperativeKernel ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchKernelIndirect = ze_lib::context->zeDdiTable.CommandList.pfnAppendLaunchKernelIndirect;
    if( nullptr == pfnAppendLaunchKernelIndirect ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendLaunchMultipleKernelsIndirect = ze_lib::context->zeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;
    if( nullptr == pfnAppendLaunchMultipleKernelsIndirect ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
ze_result_t ZE_APICALL
zeContextMakeMemoryResident(
    ze_context_handle_t hContext,                   ///< [in] handle of context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnMakeMemoryResident = ze_lib::context->zeDdiTable.Context.pfnMakeMemoryResident;
    if( nullptr == pfnMakeMemoryResident ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnMakeMemoryResident( hContext, hDevice, ptr, size );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEvictMemory = ze_lib::context->zeDdiTable.Context.pfnEvictMemory;
    if( nullptr == pfnEvictMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEvictMemory( hContext, hDevice, ptr, size );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnMakeImageResident = ze_lib::context->zeDdiTable.Context.pfnMakeImageResident;
    if( nullptr == pfnMakeImageResident ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnMakeImageResident( hContext, hDevice, hImage );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEvictImage = ze_lib::context->zeDdiTable.Context.pfnEvictImage;
    if( nullptr == pfnEvictImage ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEvictImage( hContext, hDevice, hImage );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phSampler`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_SAMPLER_ADDRESS_MODE_MIRROR < desc->addressMode`
///         + `::ZE_SAMPLER_FILTER_MODE_LINEAR < desc->filterMode`
ze_result_t ZE_APICALL
zeSamplerCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
    ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.Sampler.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phSampler );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSampler`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeSamplerDestroy(
    ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.Sampler.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hSampler );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReserve = ze_lib::context->zeDdiTable.VirtualMem.pfnReserve;
    if( nullptr == pfnReserve ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReserve( hContext, pStart, size, pptr );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFree = ze_lib::context->zeDdiTable.VirtualMem.pfnFree;
    if( nullptr == pfnFree ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFree( hContext, ptr, size );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryPageSize = ze_lib::context->zeDdiTable.VirtualMem.pfnQueryPageSize;
    if( nullptr == pfnQueryPageSize ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryPageSize( hContext, hDevice, size, pagesize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a physical memory object for the context.
/// 
/// @details
///     - The application must only use the physical memory object on the
///       context for which it was created.
///     - The size must be page aligned. See ::zeVirtualMemQueryPageSize.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phPhysicalMemory`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < desc->flags`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///         + `0 == desc->size`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
ze_result_t ZE_APICALL
zePhysicalMemCreate(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
    ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zeDdiTable.PhysicalMem.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, desc, phPhysicalMemory );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zeDdiTable.PhysicalMem.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hContext, hPhysicalMemory );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hPhysicalMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MEMORY_ACCESS_ATTRIBUTE_READONLY < access`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnMap = ze_lib::context->zeDdiTable.VirtualMem.pfnMap;
    if( nullptr == pfnMap ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnUnmap = ze_lib::context->zeDdiTable.VirtualMem.pfnUnmap;
    if( nullptr == pfnUnmap ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnUnmap( hContext, ptr, size );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_MEMORY_ACCESS_ATTRIBUTE_READONLY < access`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetAccessAttribute = ze_lib::context->zeDdiTable.VirtualMem.pfnSetAccessAttribute;
    if( nullptr == pfnSetAccessAttribute ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetAccessAttribute( hContext, ptr, size, access );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAccessAttribute = ze_lib::context->zeDdiTable.VirtualMem.pfnGetAccessAttribute;
    if( nullptr == pfnGetAccessAttribute ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAccessAttribute( hContext, ptr, size, access, outSize );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetGlobalOffsetExp = ze_lib::context->zeDdiTable.KernelExp.pfnSetGlobalOffsetExp;
    if( nullptr == pfnSetGlobalOffsetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReserveCacheExt = ze_lib::context->zeDdiTable.Device.pfnReserveCacheExt;
    if( nullptr == pfnReserveCacheExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_CACHE_EXT_REGION_NON_RESERVED < cacheRegion`
ze_result_t ZE_APICALL
zeDeviceSetCacheAdviceExt(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    void* ptr,                                      ///< [in] memory pointer to query
    size_t regionSize,                              ///< [in] region size, in pages
    ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetCacheAdviceExt = ze_lib::context->zeDdiTable.Device.pfnSetCacheAdviceExt;
    if( nullptr == pfnSetCacheAdviceExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query event timestamps for a device or sub-device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support
///       ::ZE_experimental_event_query_timestamps.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryTimestampsExp = ze_lib::context->zeDdiTable.EventExp.pfnQueryTimestampsExp;
    if( nullptr == pfnQueryTimestampsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query image memory properties.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support
///       ::ZE_experimental_image_memory_properties extension.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMemoryPropertiesExp = ze_lib::context->zeDdiTable.ImageExp.pfnGetMemoryPropertiesExp;
    if( nullptr == pfnGetMemoryPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMemoryPropertiesExp( hImage, pMemoryProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create image view on the context.
/// 
/// @details
///     - The application must only use the image view for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_extension_image_view extension.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnViewCreateExt = ze_lib::context->zeDdiTable.Image.pfnViewCreateExt;
    if( nullptr == pfnViewCreateExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create image view on the context.
/// 
/// @details
///     - The application must only use the image view for the device, or its
///       sub-devices, which was provided during creation.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_experimental_image_view
///       extension.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnViewCreateExp = ze_lib::context->zeDdiTable.ImageExp.pfnViewCreateExp;
    if( nullptr == pfnViewCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pHint`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < pHint->flags`
ze_result_t ZE_APICALL
zeKernelSchedulingHintExp(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSchedulingHintExp = ze_lib::context->zeDdiTable.KernelExp.pfnSchedulingHintExp;
    if( nullptr == pfnSchedulingHintExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSchedulingHintExp( hKernel, pHint );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetPropertiesExt = ze_lib::context->zeDdiTable.Device.pfnPciGetPropertiesExt;
    if( nullptr == pfnPciGetPropertiesExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetPropertiesExt( hDevice, pPciProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyToMemoryExt = ze_lib::context->zeDdiTable.CommandList.pfnAppendImageCopyToMemoryExt;
    if( nullptr == pfnAppendImageCopyToMemoryExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendImageCopyFromMemoryExt = ze_lib::context->zeDdiTable.CommandList.pfnAppendImageCopyFromMemoryExt;
    if( nullptr == pfnAppendImageCopyFromMemoryExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAllocPropertiesExt = ze_lib::context->zeDdiTable.Image.pfnGetAllocPropertiesExt;
    if( nullptr == pfnGetAllocPropertiesExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pInspectDesc`
///         + `nullptr == phModules`
///         + `nullptr == phLog`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < pInspectDesc->flags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInspectLinkageExt = ze_lib::context->zeDdiTable.Module.pfnInspectLinkageExt;
    if( nullptr == pfnInspectLinkageExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory using the
///        specified free policy.
/// 
/// @details
///     - The memory free policy is specified by the memory free descriptor.
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemFreeDesc`
///         + `nullptr == ptr`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x3 < pMemFreeDesc->freePolicy`
ze_result_t ZE_APICALL
zeMemFreeExt(
    ze_context_handle_t hContext,                   ///< [in] handle of the context object
    const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
    void* ptr                                       ///< [in][release] pointer to memory to free
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFreeExt = ze_lib::context->zeDdiTable.Mem.pfnFreeExt;
    if( nullptr == pfnFreeExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFreeExt( hContext, pMemFreeDesc, ptr );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExp = ze_lib::context->zeDdiTable.FabricVertexExp.pfnGetExp;
    if( nullptr == pfnGetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExp( hDriver, pCount, phVertices );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves a fabric sub-vertex from a fabric vertex
/// 
/// @details
///     - Multiple calls to this function will return identical fabric vertex
///       handles, in the same order.
///     - The number of handles returned from this function is affected by the
///       ::ZE_AFFINITY_MASK environment variable.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSubVerticesExp = ze_lib::context->zeDdiTable.FabricVertexExp.pfnGetSubVerticesExp;
    if( nullptr == pfnGetSubVerticesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.FabricVertexExp.pfnGetPropertiesExp;
    if( nullptr == pfnGetPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExp( hVertex, pVertexProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDeviceExp = ze_lib::context->zeDdiTable.FabricVertexExp.pfnGetDeviceExp;
    if( nullptr == pfnGetDeviceExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDeviceExp( hVertex, phDevice );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFabricVertexExp = ze_lib::context->zeDdiTable.DeviceExp.pfnGetFabricVertexExp;
    if( nullptr == pfnGetFabricVertexExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFabricVertexExp( hDevice, phVertex );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExp = ze_lib::context->zeDdiTable.FabricEdgeExp.pfnGetExp;
    if( nullptr == pfnGetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExp( hVertexA, hVertexB, pCount, phEdges );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVerticesExp = ze_lib::context->zeDdiTable.FabricEdgeExp.pfnGetVerticesExp;
    if( nullptr == pfnGetVerticesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVerticesExp( hEdge, phVertexA, phVertexB );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.FabricEdgeExp.pfnGetPropertiesExp;
    if( nullptr == pfnGetPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExp( hEdge, pEdgeProperties );
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
///       ::ZE_extension_event_query_kernel_timestamps.
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnQueryKernelTimestampsExt = ze_lib::context->zeDdiTable.Event.pfnQueryKernelTimestampsExt;
    if( nullptr == pfnQueryKernelTimestampsExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a ray tracing acceleration structure builder object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_experimental_rtas_builder
///       extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDescriptor`
///         + `nullptr == phBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_BUILDER_EXP_VERSION_CURRENT < pDescriptor->builderVersion`
ze_result_t ZE_APICALL
zeRTASBuilderCreateExp(
    ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
    const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
    ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExp = ze_lib::context->zeDdiTable.RTASBuilderExp.pfnCreateExp;
    if( nullptr == pfnCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExp( hDriver, pDescriptor, phBuilder );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBuildOpDescriptor`
///         + `nullptr == pProperties`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXP_INVALID < pBuildOpDescriptor->rtasFormat`
///         + `::ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_HIGH < pBuildOpDescriptor->buildQuality`
///         + `0x3 < pBuildOpDescriptor->buildFlags`
ze_result_t ZE_APICALL
zeRTASBuilderGetBuildPropertiesExp(
    ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
    const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
    ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetBuildPropertiesExp = ze_lib::context->zeDdiTable.RTASBuilderExp.pfnGetBuildPropertiesExp;
    if( nullptr == pfnGetBuildPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Checks ray tracing acceleration structure format compatibility
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXP_INVALID < rtasFormatA`
///         + `::ZE_RTAS_FORMAT_EXP_INVALID < rtasFormatB`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnRTASFormatCompatibilityCheckExp = ze_lib::context->zeDdiTable.DriverExp.pfnRTASFormatCompatibilityCheckExp;
    if( nullptr == pfnRTASFormatCompatibilityCheckExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBuildOpDescriptor`
///         + `nullptr == pScratchBuffer`
///         + `nullptr == pRtasBuffer`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZE_RTAS_FORMAT_EXP_INVALID < pBuildOpDescriptor->rtasFormat`
///         + `::ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_HIGH < pBuildOpDescriptor->buildQuality`
///         + `0x3 < pBuildOpDescriptor->buildFlags`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnBuildExp = ze_lib::context->zeDdiTable.RTASBuilderExp.pfnBuildExp;
    if( nullptr == pfnBuildExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hBuilder`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zeRTASBuilderDestroyExp(
    ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zeDdiTable.RTASBuilderExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( hBuilder );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a ray tracing acceleration structure builder parallel
///        operation object
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
///     - The implementation must support ::ZE_experimental_rtas_builder
///       extension.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExp = ze_lib::context->zeDdiTable.RTASParallelOperationExp.pfnCreateExp;
    if( nullptr == pfnCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExp( hDriver, phParallelOperation );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExp = ze_lib::context->zeDdiTable.RTASParallelOperationExp.pfnGetPropertiesExp;
    if( nullptr == pfnGetPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExp( hParallelOperation, pProperties );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationJoinExp(
    ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnJoinExp = ze_lib::context->zeDdiTable.RTASParallelOperationExp.pfnJoinExp;
    if( nullptr == pfnJoinExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnJoinExp( hParallelOperation );
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hParallelOperation`
ze_result_t ZE_APICALL
zeRTASParallelOperationDestroyExp(
    ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zeDdiTable.RTASParallelOperationExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( hParallelOperation );
}

} // extern "C"
