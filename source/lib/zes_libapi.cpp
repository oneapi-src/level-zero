/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_libapi.cpp
 *
 * @brief C++ static library for zes
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize 'oneAPI' System Resource Management (sysman)
/// 
/// @details
///     - The application must call this function or ::zeInit with the
///       ::ZES_ENABLE_SYSMAN environment variable set before calling any other
///       sysman function.
///     - If this function is not called then all other sysman functions will
///       return ::ZE_RESULT_ERROR_UNINITIALIZED.
///     - This function will only initialize sysman. To initialize other
///       functions, call ::zeInit.
///     - There is no requirement to call this function before or after
///       ::zeInit.
///     - Only one instance of sysman will be initialized per process.
///     - The application must call this function after forking new processes.
///       Each forked process must call this function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe for scenarios
///       where multiple libraries may initialize sysman simultaneously.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < flags`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t ZE_APICALL
zesInit(
    zes_init_flags_t flags                          ///< [in] initialization flags.
                                                    ///< currently unused, must be 0 (default).
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    if (!ze_lib::context) {
        ze_lib::context = new ze_lib::context_t;
    }
    #endif
    static ze_result_t result = ZE_RESULT_SUCCESS;
    std::call_once(ze_lib::context->initOnceSysMan, [flags]() {
        result = ze_lib::context->Init(flags, true, nullptr);

    });

    if( ZE_RESULT_SUCCESS != result )
        return result;

    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInit = ze_lib::context->zesDdiTable.load()->Global.pfnInit;
    if( nullptr == pfnInit ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnInit( flags );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves sysman driver instances
/// 
/// @details
///     - A sysman driver represents a collection of physical devices.
///     - Multiple calls to this function will return identical sysman driver
///       handles, in the same order.
///     - The application may pass nullptr for pDrivers when only querying the
///       number of sysman drivers.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
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
zesDriverGet(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sysman driver instances.
                                                    ///< if count is zero, then the loader shall update the value with the
                                                    ///< total number of sysman drivers available.
                                                    ///< if count is greater than the number of sysman drivers available, then
                                                    ///< the loader shall update the value with the correct number of sysman
                                                    ///< drivers available.
    zes_driver_handle_t* phDrivers                  ///< [in,out][optional][range(0, *pCount)] array of sysman driver instance handles.
                                                    ///< if count is less than the number of sysman drivers available, then the
                                                    ///< loader shall only retrieve that number of sysman drivers.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    if (ze_lib::context->zesDdiTable == nullptr) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDriverGet_t pfnGet = [&result] {
        auto pfnGet = ze_lib::context->zesDdiTable.load()->Driver.pfnGet;
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

    if (ze_lib::context->zesDdiTable == nullptr) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zesDdiTable.load()->Driver.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    ze_lib::context->zesInuse = true;

    return pfnGet( pCount, phDrivers );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves extension properties
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDriverGetExtensionProperties(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of extension properties available.
                                                    ///< if count is greater than the number of extension properties available,
                                                    ///< then the driver shall update the value with the correct number of
                                                    ///< extension properties available.
    zes_driver_extension_properties_t* pExtensionProperties ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< extension properties.
                                                    ///< if count is less than the number of extension properties available,
                                                    ///< then driver shall only retrieve that number of extension properties.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDriverGetExtensionProperties_t pfnGetExtensionProperties = [&result] {
        auto pfnGetExtensionProperties = ze_lib::context->zesDdiTable.load()->Driver.pfnGetExtensionProperties;
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

    auto pfnGetExtensionProperties = ze_lib::context->zesDdiTable.load()->Driver.pfnGetExtensionProperties;
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == name`
///         + `nullptr == ppFunctionAddress`
ze_result_t ZE_APICALL
zesDriverGetExtensionFunctionAddress(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
    const char* name,                               ///< [in] extension function name
    void** ppFunctionAddress                        ///< [out] pointer to function pointer
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDriverGetExtensionFunctionAddress_t pfnGetExtensionFunctionAddress = [&result] {
        auto pfnGetExtensionFunctionAddress = ze_lib::context->zesDdiTable.load()->Driver.pfnGetExtensionFunctionAddress;
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

    auto pfnGetExtensionFunctionAddress = ze_lib::context->zesDdiTable.load()->Driver.pfnGetExtensionFunctionAddress;
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
/// @brief Retrieves sysman devices within a sysman driver
/// 
/// @details
///     - Multiple calls to this function will return identical sysman device
///       handles, in the same order.
///     - The number and order of handles returned from this function is NOT
///       affected by the ::ZE_AFFINITY_MASK, ::ZE_ENABLE_PCI_ID_DEVICE_ORDER,
///       or ::ZE_FLAT_DEVICE_HIERARCHY environment variables.
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
zesDeviceGet(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sysman devices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of sysman devices available.
                                                    ///< if count is greater than the number of sysman devices available, then
                                                    ///< the driver shall update the value with the correct number of sysman
                                                    ///< devices available.
    zes_device_handle_t* phDevices                  ///< [in,out][optional][range(0, *pCount)] array of handle of sysman devices.
                                                    ///< if count is less than the number of sysman devices available, then
                                                    ///< driver shall only retrieve that number of sysman devices.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGet_t pfnGet = [&result] {
        auto pfnGet = ze_lib::context->zesDdiTable.load()->Device.pfnGet;
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

    auto pfnGet = ze_lib::context->zesDdiTable.load()->Device.pfnGet;
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
/// @brief Get properties about the device
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
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDeviceGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Device.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hDevice, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Device.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDevice, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about the state of the device - if a reset is
///        required, reasons for the reset and if the device has been repaired
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
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDeviceGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Device.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hDevice, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Device.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hDevice, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @details
///     - Performs a PCI bus reset of the device. This will result in all
///       current device state being lost.
///     - All applications using the device should be stopped before calling
///       this function.
///     - If the force argument is specified, all applications using the device
///       will be forcibly killed.
///     - The function will block until the device has restarted or an
///       implementation defined timeout occurred waiting for the reset to
///       complete.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + Reset cannot be performed because applications are using this device.
///     - ::ZE_RESULT_ERROR_UNKNOWN
///         + There were problems unloading the device driver, performing a bus reset or reloading the device driver.
ze_result_t ZE_APICALL
zesDeviceReset(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                    ///< device will be forcibly killed.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceReset_t pfnReset = [&result] {
        auto pfnReset = ze_lib::context->zesDdiTable.load()->Device.pfnReset;
        if( nullptr == pfnReset ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReset;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReset( hDevice, force );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zesDdiTable.load()->Device.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hDevice, force );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device extension
/// 
/// @details
///     - Performs a PCI bus reset of the device. This will result in all
///       current device state being lost.
///     - Prior to calling this function, user is responsible for closing
///       applications using the device unless force argument is specified.
///     - If the force argument is specified, all applications using the device
///       will be forcibly killed.
///     - The function will block until the device has restarted or a
///       implementation specific timeout occurred waiting for the reset to
///       complete.
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
///         + `nullptr == pProperties`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + Reset cannot be performed because applications are using this device.
///     - ::ZE_RESULT_ERROR_UNKNOWN
///         + There were problems unloading the device driver, performing a bus reset or reloading the device driver.
ze_result_t ZE_APICALL
zesDeviceResetExt(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    zes_reset_properties_t* pProperties             ///< [in] Device reset properties to apply
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceResetExt_t pfnResetExt = [&result] {
        auto pfnResetExt = ze_lib::context->zesDdiTable.load()->Device.pfnResetExt;
        if( nullptr == pfnResetExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnResetExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnResetExt( hDevice, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnResetExt = ze_lib::context->zesDdiTable.load()->Device.pfnResetExt;
    if( nullptr == pfnResetExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnResetExt( hDevice, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about host processes using the device
/// 
/// @details
///     - The number of processes connected to the device is dynamic. This means
///       that between a call to determine the value of pCount and the
///       subsequent call, the number of processes may have increased or
///       decreased. It is recommended that a large array be passed in so as to
///       avoid receiving the error ::ZE_RESULT_ERROR_INVALID_SIZE. Also, always
///       check the returned value in pCount since it may be less than the
///       earlier call to get the required array size.
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
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The provided value of pCount is not big enough to store information about all the processes currently attached to the device.
ze_result_t ZE_APICALL
zesDeviceProcessesGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of processes currently attached to the device.
                                                    ///< if count is greater than the number of processes currently attached to
                                                    ///< the device, then the driver shall update the value with the correct
                                                    ///< number of processes.
    zes_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information.
                                                    ///< if count is less than the number of processes currently attached to
                                                    ///< the device, then the driver shall only retrieve information about that
                                                    ///< number of processes. In this case, the return code will ::ZE_RESULT_ERROR_INVALID_SIZE.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceProcessesGetState_t pfnProcessesGetState = [&result] {
        auto pfnProcessesGetState = ze_lib::context->zesDdiTable.load()->Device.pfnProcessesGetState;
        if( nullptr == pfnProcessesGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnProcessesGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnProcessesGetState( hDevice, pCount, pProcesses );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnProcessesGetState = ze_lib::context->zesDdiTable.load()->Device.pfnProcessesGetState;
    if( nullptr == pfnProcessesGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnProcessesGetState( hDevice, pCount, pProcesses );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
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
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDevicePciGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDevicePciGetProperties_t pfnPciGetProperties = [&result] {
        auto pfnPciGetProperties = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetProperties;
        if( nullptr == pfnPciGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnPciGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnPciGetProperties( hDevice, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetProperties = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetProperties( hDevice, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current PCI state - current speed
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
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDevicePciGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDevicePciGetState_t pfnPciGetState = [&result] {
        auto pfnPciGetState = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetState;
        if( nullptr == pfnPciGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnPciGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnPciGetState( hDevice, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetState = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetState;
    if( nullptr == pfnPciGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetState( hDevice, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about each configured bar
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDevicePciGetBars(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of PCI bars that are setup.
                                                    ///< if count is greater than the number of PCI bars that are setup, then
                                                    ///< the driver shall update the value with the correct number of PCI bars.
    zes_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of information about setup
                                                    ///< PCI bars.
                                                    ///< if count is less than the number of PCI bars that are setup, then the
                                                    ///< driver shall only retrieve information about that number of PCI bars.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDevicePciGetBars_t pfnPciGetBars = [&result] {
        auto pfnPciGetBars = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetBars;
        if( nullptr == pfnPciGetBars ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnPciGetBars;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnPciGetBars( hDevice, pCount, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetBars = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetBars;
    if( nullptr == pfnPciGetBars ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetBars( hDevice, pCount, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats - bandwidth, number of packets, number of replays
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
///         + `nullptr == pStats`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesDevicePciGetStats(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDevicePciGetStats_t pfnPciGetStats = [&result] {
        auto pfnPciGetStats = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetStats;
        if( nullptr == pfnPciGetStats ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnPciGetStats;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnPciGetStats( hDevice, pStats );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetStats = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetStats;
    if( nullptr == pfnPciGetStats ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetStats( hDevice, pStats );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the overclock waiver.The overclock waiver setting is persistent
///        until the next pcode boot
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
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This product does not support overclocking
ze_result_t ZE_APICALL
zesDeviceSetOverclockWaiver(
    zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceSetOverclockWaiver_t pfnSetOverclockWaiver = [&result] {
        auto pfnSetOverclockWaiver = ze_lib::context->zesDdiTable.load()->Device.pfnSetOverclockWaiver;
        if( nullptr == pfnSetOverclockWaiver ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetOverclockWaiver;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetOverclockWaiver( hDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetOverclockWaiver = ze_lib::context->zesDdiTable.load()->Device.pfnSetOverclockWaiver;
    if( nullptr == pfnSetOverclockWaiver ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetOverclockWaiver( hDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the list of supported overclock domains for this device
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
///         + `nullptr == pOverclockDomains`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceGetOverclockDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pOverclockDomains                     ///< [in,out] Returns the overclock domains that are supported (a bit for
                                                    ///< each of enum ::zes_overclock_domain_t). If no bits are set, the device
                                                    ///< doesn't support overclocking.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGetOverclockDomains_t pfnGetOverclockDomains = [&result] {
        auto pfnGetOverclockDomains = ze_lib::context->zesDdiTable.load()->Device.pfnGetOverclockDomains;
        if( nullptr == pfnGetOverclockDomains ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetOverclockDomains;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetOverclockDomains( hDevice, pOverclockDomains );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetOverclockDomains = ze_lib::context->zesDdiTable.load()->Device.pfnGetOverclockDomains;
    if( nullptr == pfnGetOverclockDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetOverclockDomains( hDevice, pOverclockDomains );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the list of supported overclock controls available for one of the
///        supported overclock domains on the device
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
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_DOMAIN_ADM < domainType`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pAvailableControls`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceGetOverclockControls(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_overclock_domain_t domainType,              ///< [in] Domain type.
    uint32_t* pAvailableControls                    ///< [in,out] Returns the overclock controls that are supported for the
                                                    ///< specified overclock domain (a bit for each of enum
                                                    ///< ::zes_overclock_control_t).
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGetOverclockControls_t pfnGetOverclockControls = [&result] {
        auto pfnGetOverclockControls = ze_lib::context->zesDdiTable.load()->Device.pfnGetOverclockControls;
        if( nullptr == pfnGetOverclockControls ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetOverclockControls;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetOverclockControls( hDevice, domainType, pAvailableControls );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetOverclockControls = ze_lib::context->zesDdiTable.load()->Device.pfnGetOverclockControls;
    if( nullptr == pfnGetOverclockControls ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetOverclockControls( hDevice, domainType, pAvailableControls );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset all overclock settings to default values (shipped = 1 or
///        manufacturing =0)
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
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceResetOverclockSettings(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    ze_bool_t onShippedState                        ///< [in] True will reset to shipped state; false will reset to
                                                    ///< manufacturing state
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceResetOverclockSettings_t pfnResetOverclockSettings = [&result] {
        auto pfnResetOverclockSettings = ze_lib::context->zesDdiTable.load()->Device.pfnResetOverclockSettings;
        if( nullptr == pfnResetOverclockSettings ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnResetOverclockSettings;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnResetOverclockSettings( hDevice, onShippedState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnResetOverclockSettings = ze_lib::context->zesDdiTable.load()->Device.pfnResetOverclockSettings;
    if( nullptr == pfnResetOverclockSettings ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnResetOverclockSettings( hDevice, onShippedState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Determine the state of overclocking
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
///         + `nullptr == pOverclockMode`
///         + `nullptr == pWaiverSetting`
///         + `nullptr == pOverclockState`
///         + `nullptr == pPendingAction`
///         + `nullptr == pPendingReset`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceReadOverclockState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_overclock_mode_t* pOverclockMode,           ///< [out] One of overclock mode.
    ze_bool_t* pWaiverSetting,                      ///< [out] Waiver setting: 0 = Waiver not set, 1 = waiver has been set.
    ze_bool_t* pOverclockState,                     ///< [out] Current settings 0 =manufacturing state, 1= shipped state)..
    zes_pending_action_t* pPendingAction,           ///< [out] This enum is returned when the driver attempts to set an
                                                    ///< overclock control or reset overclock settings.
    ze_bool_t* pPendingReset                        ///< [out] Pending reset 0 =manufacturing state, 1= shipped state)..
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceReadOverclockState_t pfnReadOverclockState = [&result] {
        auto pfnReadOverclockState = ze_lib::context->zesDdiTable.load()->Device.pfnReadOverclockState;
        if( nullptr == pfnReadOverclockState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReadOverclockState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadOverclockState = ze_lib::context->zesDdiTable.load()->Device.pfnReadOverclockState;
    if( nullptr == pfnReadOverclockState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of overclock domains
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumOverclockDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_overclock_handle_t* phDomainHandle          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumOverclockDomains_t pfnEnumOverclockDomains = [&result] {
        auto pfnEnumOverclockDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumOverclockDomains;
        if( nullptr == pfnEnumOverclockDomains ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumOverclockDomains;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumOverclockDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumOverclockDomains;
    if( nullptr == pfnEnumOverclockDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get overclock domain control properties
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDomainProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetDomainProperties(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockGetDomainProperties_t pfnGetDomainProperties = [&result] {
        auto pfnGetDomainProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainProperties;
        if( nullptr == pfnGetDomainProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDomainProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDomainProperties( hDomainHandle, pDomainProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDomainProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainProperties;
    if( nullptr == pfnGetDomainProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDomainProperties( hDomainHandle, pDomainProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read overclock VF min,max and step values
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pVFProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetDomainVFProperties(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockGetDomainVFProperties_t pfnGetDomainVFProperties = [&result] {
        auto pfnGetDomainVFProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainVFProperties;
        if( nullptr == pfnGetDomainVFProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDomainVFProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDomainVFProperties( hDomainHandle, pVFProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDomainVFProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainVFProperties;
    if( nullptr == pfnGetDomainVFProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDomainVFProperties( hDomainHandle, pVFProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read overclock control values - min/max/step/default/ref
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pControlProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetDomainControlProperties(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Handle for the component.
    zes_control_property_t* pControlProperties      ///< [in,out] overclock control values.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockGetDomainControlProperties_t pfnGetDomainControlProperties = [&result] {
        auto pfnGetDomainControlProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainControlProperties;
        if( nullptr == pfnGetDomainControlProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDomainControlProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDomainControlProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainControlProperties;
    if( nullptr == pfnGetDomainControlProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the current value for a given overclock control
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pValue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetControlCurrentValue(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component.
    zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
    double* pValue                                  ///< [in,out] Getting overclock control value for the specified control.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockGetControlCurrentValue_t pfnGetControlCurrentValue = [&result] {
        auto pfnGetControlCurrentValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlCurrentValue;
        if( nullptr == pfnGetControlCurrentValue ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetControlCurrentValue;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetControlCurrentValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlCurrentValue;
    if( nullptr == pfnGetControlCurrentValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the the reset pending value for a given overclock control
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pValue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetControlPendingValue(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
    double* pValue                                  ///< [out] Returns the pending value for a given control. The units and
                                                    ///< format of the value depend on the control type.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockGetControlPendingValue_t pfnGetControlPendingValue = [&result] {
        auto pfnGetControlPendingValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlPendingValue;
        if( nullptr == pfnGetControlPendingValue ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetControlPendingValue;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetControlPendingValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlPendingValue;
    if( nullptr == pfnGetControlPendingValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the value for a given overclock control
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pPendingAction`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockSetControlUserValue(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
    double pValue,                                  ///< [in] The new value of the control. The units and format of the value
                                                    ///< depend on the control type.
    zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockSetControlUserValue_t pfnSetControlUserValue = [&result] {
        auto pfnSetControlUserValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnSetControlUserValue;
        if( nullptr == pfnSetControlUserValue ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetControlUserValue;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetControlUserValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnSetControlUserValue;
    if( nullptr == pfnSetControlUserValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Determine the state of an overclock control
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pControlState`
///         + `nullptr == pPendingAction`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetControlState(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
    zes_control_state_t* pControlState,             ///< [out] Current overclock control state.
    zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockGetControlState_t pfnGetControlState = [&result] {
        auto pfnGetControlState = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlState;
        if( nullptr == pfnGetControlState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetControlState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetControlState = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlState;
    if( nullptr == pfnGetControlState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the frequency or voltage of a V-F point from the default or
///        custom V-F curve.
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_VF_TYPE_FREQ < VFType`
///         + `::ZES_VF_ARRAY_TYPE_LIVE_VF_ARRAY < VFArrayType`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == PointValue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetVFPointValues(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
    zes_vf_array_type_t VFArrayType,                ///< [in] User,Default or Live VF array to read from
    uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
    uint32_t* PointValue                            ///< [out] Returns the frequency in 1kHz units or voltage in millivolt
                                                    ///< units from the custom V-F curve at the specified zero-based index 
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockGetVFPointValues_t pfnGetVFPointValues = [&result] {
        auto pfnGetVFPointValues = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetVFPointValues;
        if( nullptr == pfnGetVFPointValues ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFPointValues;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFPointValues = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetVFPointValues;
    if( nullptr == pfnGetVFPointValues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Write the frequency or voltage of a V-F point to custom V-F curve.
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
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_VF_TYPE_FREQ < VFType`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockSetVFPointValues(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
    uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
    uint32_t PointValue                             ///< [in] Writes frequency in 1kHz units or voltage in millivolt units to
                                                    ///< custom V-F curve at the specified zero-based index 
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnOverclockSetVFPointValues_t pfnSetVFPointValues = [&result] {
        auto pfnSetVFPointValues = ze_lib::context->zesDdiTable.load()->Overclock.pfnSetVFPointValues;
        if( nullptr == pfnSetVFPointValues ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetVFPointValues;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetVFPointValues = ze_lib::context->zesDdiTable.load()->Overclock.pfnSetVFPointValues;
    if( nullptr == pfnSetVFPointValues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of diagnostics test suites
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumDiagnosticTestSuites(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_diag_handle_t* phDiagnostics                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumDiagnosticTestSuites_t pfnEnumDiagnosticTestSuites = [&result] {
        auto pfnEnumDiagnosticTestSuites = ze_lib::context->zesDdiTable.load()->Device.pfnEnumDiagnosticTestSuites;
        if( nullptr == pfnEnumDiagnosticTestSuites ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumDiagnosticTestSuites;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumDiagnosticTestSuites = ze_lib::context->zesDdiTable.load()->Device.pfnEnumDiagnosticTestSuites;
    if( nullptr == pfnEnumDiagnosticTestSuites ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a diagnostics test suite
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
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDiagnosticsGetProperties(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                    ///< suite
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDiagnosticsGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hDiagnostics, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDiagnostics, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get individual tests that can be run separately. Not all test suites
///        permit running individual tests, check the `haveTests` member of
///        ::zes_diag_properties_t.
/// 
/// @details
///     - The list of available tests is returned in order of increasing test
///       index (see the `index` member of ::zes_diag_test_t).
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
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDiagnosticsGetTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of tests that are available.
                                                    ///< if count is greater than the number of tests that are available, then
                                                    ///< the driver shall update the value with the correct number of tests.
    zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] array of information about
                                                    ///< individual tests sorted by increasing value of the `index` member of ::zes_diag_test_t.
                                                    ///< if count is less than the number of tests that are available, then the
                                                    ///< driver shall only retrieve that number of tests.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDiagnosticsGetTests_t pfnGetTests = [&result] {
        auto pfnGetTests = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnGetTests;
        if( nullptr == pfnGetTests ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetTests;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetTests( hDiagnostics, pCount, pTests );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetTests = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnGetTests;
    if( nullptr == pfnGetTests ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetTests( hDiagnostics, pCount, pTests );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - WARNING: Running diagnostics may destroy current device state
///       information. Gracefully close any running workloads before initiating.
///     - To run all tests in a test suite, set start =
///       ::ZES_DIAG_FIRST_TEST_INDEX and end = ::ZES_DIAG_LAST_TEST_INDEX.
///     - If the test suite permits running individual tests, the `haveTests`
///       member of ::zes_diag_properties_t will be true. In this case, the
///       function ::zesDiagnosticsGetTests() can be called to get the list of
///       tests and corresponding indices that can be supplied to the arguments
///       start and end in this function.
///     - This function will block until the diagnostics have completed and
///       force reset based on result
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pResult`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform diagnostics.
ze_result_t ZE_APICALL
zesDiagnosticsRunTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t startIndex,                            ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t endIndex,                              ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDiagnosticsRunTests_t pfnRunTests = [&result] {
        auto pfnRunTests = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnRunTests;
        if( nullptr == pfnRunTests ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnRunTests;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnRunTests = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnRunTests;
    if( nullptr == pfnRunTests ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Is ECC functionality available - true or false?
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
///         + `nullptr == pAvailable`
ze_result_t ZE_APICALL
zesDeviceEccAvailable(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEccAvailable_t pfnEccAvailable = [&result] {
        auto pfnEccAvailable = ze_lib::context->zesDdiTable.load()->Device.pfnEccAvailable;
        if( nullptr == pfnEccAvailable ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEccAvailable;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEccAvailable( hDevice, pAvailable );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEccAvailable = ze_lib::context->zesDdiTable.load()->Device.pfnEccAvailable;
    if( nullptr == pfnEccAvailable ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEccAvailable( hDevice, pAvailable );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Is ECC support configurable - true or false?
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
///         + `nullptr == pConfigurable`
ze_result_t ZE_APICALL
zesDeviceEccConfigurable(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEccConfigurable_t pfnEccConfigurable = [&result] {
        auto pfnEccConfigurable = ze_lib::context->zesDdiTable.load()->Device.pfnEccConfigurable;
        if( nullptr == pfnEccConfigurable ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEccConfigurable;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEccConfigurable( hDevice, pConfigurable );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEccConfigurable = ze_lib::context->zesDdiTable.load()->Device.pfnEccConfigurable;
    if( nullptr == pfnEccConfigurable ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEccConfigurable( hDevice, pConfigurable );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current ECC state, pending state, and pending action
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
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDeviceGetEccState(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGetEccState_t pfnGetEccState = [&result] {
        auto pfnGetEccState = ze_lib::context->zesDdiTable.load()->Device.pfnGetEccState;
        if( nullptr == pfnGetEccState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetEccState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetEccState( hDevice, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetEccState = ze_lib::context->zesDdiTable.load()->Device.pfnGetEccState;
    if( nullptr == pfnGetEccState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetEccState( hDevice, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set new ECC state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - ::zesDeviceGetState should be called to determine pending action
///       required to implement state change.
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
///         + `nullptr == newState`
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_DEVICE_ECC_STATE_DISABLED < newState->state`
///     - ::ZE_RESULT_WARNING_ACTION_REQUIRED
///         + User must look at the pendingAction attribute of pState & perform the action required to complete the ECC state change.
ze_result_t ZE_APICALL
zesDeviceSetEccState(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    const zes_device_ecc_desc_t* newState,          ///< [in] Pointer to desired ECC state.
    zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceSetEccState_t pfnSetEccState = [&result] {
        auto pfnSetEccState = ze_lib::context->zesDdiTable.load()->Device.pfnSetEccState;
        if( nullptr == pfnSetEccState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetEccState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetEccState( hDevice, newState, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEccState = ze_lib::context->zesDdiTable.load()->Device.pfnSetEccState;
    if( nullptr == pfnSetEccState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEccState( hDevice, newState, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of engine groups
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumEngineGroups(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_engine_handle_t* phEngine                   ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumEngineGroups_t pfnEnumEngineGroups = [&result] {
        auto pfnEnumEngineGroups = ze_lib::context->zesDdiTable.load()->Device.pfnEnumEngineGroups;
        if( nullptr == pfnEnumEngineGroups ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumEngineGroups;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumEngineGroups( hDevice, pCount, phEngine );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumEngineGroups = ze_lib::context->zesDdiTable.load()->Device.pfnEnumEngineGroups;
    if( nullptr == pfnEnumEngineGroups ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumEngineGroups( hDevice, pCount, phEngine );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine group properties
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
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesEngineGetProperties(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnEngineGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Engine.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hEngine, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Engine.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hEngine, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity stats for an engine group.
/// 
/// @details
///     - This function also returns the engine activity inside a Virtual
///       Machine (VM), in the presence of hardware virtualization (SRIOV)
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
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
ze_result_t ZE_APICALL
zesEngineGetActivity(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                    ///< counters.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnEngineGetActivity_t pfnGetActivity = [&result] {
        auto pfnGetActivity = ze_lib::context->zesDdiTable.load()->Engine.pfnGetActivity;
        if( nullptr == pfnGetActivity ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetActivity;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetActivity( hEngine, pStats );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetActivity = ze_lib::context->zesDdiTable.load()->Engine.pfnGetActivity;
    if( nullptr == pfnGetActivity ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetActivity( hEngine, pStats );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Specify the list of events to listen to for a given device
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
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xffff < events`
ze_result_t ZE_APICALL
zesDeviceEventRegister(
    zes_device_handle_t hDevice,                    ///< [in] The device handle.
    zes_event_type_flags_t events                   ///< [in] List of events to listen to.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEventRegister_t pfnEventRegister = [&result] {
        auto pfnEventRegister = ze_lib::context->zesDdiTable.load()->Device.pfnEventRegister;
        if( nullptr == pfnEventRegister ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEventRegister;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEventRegister( hDevice, events );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEventRegister = ze_lib::context->zesDdiTable.load()->Device.pfnEventRegister;
    if( nullptr == pfnEventRegister ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEventRegister( hDevice, events );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for events to be received from a one or more devices.
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
///         + `nullptr == phDevices`
///         + `nullptr == pNumDeviceEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied device handles belongs to a different driver.
ze_result_t ZE_APICALL
zesDriverEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then will check status and return immediately;
                                                    ///< if `UINT32_MAX`, then function will not return until events arrive.
    uint32_t count,                                 ///< [in] Number of device handles in phDevices.
    zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                    ///< devices from the provided driver handle can be specified in this list.
    uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                    ///< generated events. If non-zero, check pEvents to determine the devices
                                                    ///< and events that were received.
    zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                    ///< device listened in phDevices.
                                                    ///< This array must be at least as big as count.
                                                    ///< For every device handle in phDevices, this will provide the events
                                                    ///< that occurred for that device at the same position in this array. If
                                                    ///< no event was received for a given device, the corresponding array
                                                    ///< entry will be zero.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDriverEventListen_t pfnEventListen = [&result] {
        auto pfnEventListen = ze_lib::context->zesDdiTable.load()->Driver.pfnEventListen;
        if( nullptr == pfnEventListen ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEventListen;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEventListen = ze_lib::context->zesDdiTable.load()->Driver.pfnEventListen;
    if( nullptr == pfnEventListen ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for events to be received from a one or more devices.
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
///         + `nullptr == phDevices`
///         + `nullptr == pNumDeviceEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied device handles belongs to a different driver.
ze_result_t ZE_APICALL
zesDriverEventListenEx(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then will check status and return immediately;
                                                    ///< if `UINT64_MAX`, then function will not return until events arrive.
    uint32_t count,                                 ///< [in] Number of device handles in phDevices.
    zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                    ///< devices from the provided driver handle can be specified in this list.
    uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                    ///< generated events. If non-zero, check pEvents to determine the devices
                                                    ///< and events that were received.
    zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                    ///< device listened in phDevices.
                                                    ///< This array must be at least as big as count.
                                                    ///< For every device handle in phDevices, this will provide the events
                                                    ///< that occurred for that device at the same position in this array. If
                                                    ///< no event was received for a given device, the corresponding array
                                                    ///< entry will be zero.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDriverEventListenEx_t pfnEventListenEx = [&result] {
        auto pfnEventListenEx = ze_lib::context->zesDdiTable.load()->Driver.pfnEventListenEx;
        if( nullptr == pfnEventListenEx ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEventListenEx;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEventListenEx = ze_lib::context->zesDdiTable.load()->Driver.pfnEventListenEx;
    if( nullptr == pfnEventListenEx ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of Fabric ports in a device
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFabricPorts(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_fabric_port_handle_t* phPort                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumFabricPorts_t pfnEnumFabricPorts = [&result] {
        auto pfnEnumFabricPorts = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFabricPorts;
        if( nullptr == pfnEnumFabricPorts ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumFabricPorts;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumFabricPorts( hDevice, pCount, phPort );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFabricPorts = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFabricPorts;
    if( nullptr == pfnEnumFabricPorts ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFabricPorts( hDevice, pCount, phPort );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port properties
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
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFabricPortGetProperties(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hPort, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPort, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port link type
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
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLinkType`
ze_result_t ZE_APICALL
zesFabricPortGetLinkType(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                    ///< port.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortGetLinkType_t pfnGetLinkType = [&result] {
        auto pfnGetLinkType = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetLinkType;
        if( nullptr == pfnGetLinkType ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetLinkType;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetLinkType( hPort, pLinkType );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLinkType = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetLinkType;
    if( nullptr == pfnGetLinkType ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLinkType( hPort, pLinkType );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port configuration
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
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesFabricPortGetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortGetConfig_t pfnGetConfig = [&result] {
        auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetConfig( hPort, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hPort, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set Fabric port configuration
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
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFabricPortSetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortSetConfig_t pfnSetConfig = [&result] {
        auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->FabricPort.pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetConfig( hPort, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->FabricPort.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hPort, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port state - status (health/degraded/failed/disabled),
///        reasons for link degradation or instability, current rx/tx speed
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
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesFabricPortGetState(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hPort, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hPort, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput
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
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThroughput`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesFabricPortGetThroughput(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortGetThroughput_t pfnGetThroughput = [&result] {
        auto pfnGetThroughput = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetThroughput;
        if( nullptr == pfnGetThroughput ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetThroughput;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetThroughput( hPort, pThroughput );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetThroughput = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetThroughput( hPort, pThroughput );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric Port Error Counters
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - The memory backing the arrays for phPorts and ppThroughputs must be
///       allocated in system memory by the user who is also responsible for
///       releasing them when they are no longer needed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pErrors`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesFabricPortGetFabricErrorCounters(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortGetFabricErrorCounters_t pfnGetFabricErrorCounters = [&result] {
        auto pfnGetFabricErrorCounters = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetFabricErrorCounters;
        if( nullptr == pfnGetFabricErrorCounters ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFabricErrorCounters;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFabricErrorCounters( hPort, pErrors );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFabricErrorCounters = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetFabricErrorCounters;
    if( nullptr == pfnGetFabricErrorCounters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFabricErrorCounters( hPort, pErrors );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput from multiple ports in a single call
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
///         + `nullptr == phPort`
///         + `nullptr == pThroughput`
ze_result_t ZE_APICALL
zesFabricPortGetMultiPortThroughput(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t numPorts,                              ///< [in] Number of ports enumerated in function ::zesDeviceEnumFabricPorts
    zes_fabric_port_handle_t* phPort,               ///< [in][range(0, numPorts)] array of fabric port handles provided by user
                                                    ///< to gather throughput values. 
    zes_fabric_port_throughput_t** pThroughput      ///< [out][range(0, numPorts)] array of fabric port throughput counters
                                                    ///< from multiple ports of type ::zes_fabric_port_throughput_t.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFabricPortGetMultiPortThroughput_t pfnGetMultiPortThroughput = [&result] {
        auto pfnGetMultiPortThroughput = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetMultiPortThroughput;
        if( nullptr == pfnGetMultiPortThroughput ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetMultiPortThroughput;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMultiPortThroughput = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetMultiPortThroughput;
    if( nullptr == pfnGetMultiPortThroughput ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of fans
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFans(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_fan_handle_t* phFan                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumFans_t pfnEnumFans = [&result] {
        auto pfnEnumFans = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFans;
        if( nullptr == pfnEnumFans ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumFans;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumFans( hDevice, pCount, phFan );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFans = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFans;
    if( nullptr == pfnEnumFans ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFans( hDevice, pCount, phFan );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties
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
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFanGetProperties(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFanGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Fan.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hFan, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Fan.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hFan, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan configurations and the current fan speed mode (default, fixed,
///        temp-speed table)
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
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesFanGetConfig(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFanGetConfig_t pfnGetConfig = [&result] {
        auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Fan.pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetConfig( hFan, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Fan.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hFan, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to run with hardware factory settings (set mode to
///        ::ZES_FAN_SPEED_MODE_DEFAULT)
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
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFanSetDefaultMode(
    zes_fan_handle_t hFan                           ///< [in] Handle for the component.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFanSetDefaultMode_t pfnSetDefaultMode = [&result] {
        auto pfnSetDefaultMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetDefaultMode;
        if( nullptr == pfnSetDefaultMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetDefaultMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetDefaultMode( hFan );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetDefaultMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetDefaultMode;
    if( nullptr == pfnSetDefaultMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetDefaultMode( hFan );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to rotate at a fixed speed (set mode to
///        ::ZES_FAN_SPEED_MODE_FIXED)
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
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == speed`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Fixing the fan speed not supported by the hardware or the fan speed units are not supported. See the `supportedModes` and `supportedUnits` members of ::zes_fan_properties_t.
ze_result_t ZE_APICALL
zesFanSetFixedSpeedMode(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFanSetFixedSpeedMode_t pfnSetFixedSpeedMode = [&result] {
        auto pfnSetFixedSpeedMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetFixedSpeedMode;
        if( nullptr == pfnSetFixedSpeedMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetFixedSpeedMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetFixedSpeedMode( hFan, speed );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetFixedSpeedMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetFixedSpeedMode;
    if( nullptr == pfnSetFixedSpeedMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetFixedSpeedMode( hFan, speed );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to adjust speed based on a temperature/speed table
///        (set mode to ::ZES_FAN_SPEED_MODE_TABLE)
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
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == speedTable`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The temperature/speed pairs in the array are not sorted on temperature from lowest to highest.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Fan speed table not supported by the hardware or the fan speed units are not supported. See the `supportedModes` and `supportedUnits` members of ::zes_fan_properties_t.
ze_result_t ZE_APICALL
zesFanSetSpeedTableMode(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFanSetSpeedTableMode_t pfnSetSpeedTableMode = [&result] {
        auto pfnSetSpeedTableMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetSpeedTableMode;
        if( nullptr == pfnSetSpeedTableMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetSpeedTableMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetSpeedTableMode( hFan, speedTable );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetSpeedTableMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetSpeedTableMode;
    if( nullptr == pfnSetSpeedTableMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetSpeedTableMode( hFan, speedTable );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a fan - current mode and speed
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
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_FAN_SPEED_UNITS_PERCENT < units`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSpeed`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + The requested fan speed units are not supported. See the `supportedUnits` member of ::zes_fan_properties_t.
ze_result_t ZE_APICALL
zesFanGetState(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                    ///< requested. A value of -1 indicates that the fan speed cannot be
                                                    ///< measured.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFanGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Fan.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hFan, units, pSpeed );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Fan.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hFan, units, pSpeed );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of firmwares
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFirmwares(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_firmware_handle_t* phFirmware               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumFirmwares_t pfnEnumFirmwares = [&result] {
        auto pfnEnumFirmwares = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFirmwares;
        if( nullptr == pfnEnumFirmwares ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumFirmwares;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumFirmwares( hDevice, pCount, phFirmware );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFirmwares = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFirmwares;
    if( nullptr == pfnEnumFirmwares ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFirmwares( hDevice, pCount, phFirmware );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware properties
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
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFirmwareGetProperties(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                    ///< firmware
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFirmwareGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hFirmware, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hFirmware, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Flash a new firmware image
/// 
/// @details
///     - Any running workload must be gracefully closed before invoking this
///       function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This is a non-blocking call. Application may call
///       ::zesFirmwareGetFlashProgress to get completion status.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImage`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t ZE_APICALL
zesFirmwareFlash(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFirmwareFlash_t pfnFlash = [&result] {
        auto pfnFlash = ze_lib::context->zesDdiTable.load()->Firmware.pfnFlash;
        if( nullptr == pfnFlash ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnFlash;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnFlash( hFirmware, pImage, size );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFlash = ze_lib::context->zesDdiTable.load()->Firmware.pfnFlash;
    if( nullptr == pfnFlash ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFlash( hFirmware, pImage, size );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Firmware Flash Progress
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
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCompletionPercent`
ze_result_t ZE_APICALL
zesFirmwareGetFlashProgress(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    uint32_t* pCompletionPercent                    ///< [in,out] Pointer to the Completion Percentage of Firmware Update
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFirmwareGetFlashProgress_t pfnGetFlashProgress = [&result] {
        auto pfnGetFlashProgress = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetFlashProgress;
        if( nullptr == pfnGetFlashProgress ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetFlashProgress;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetFlashProgress( hFirmware, pCompletionPercent );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFlashProgress = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetFlashProgress;
    if( nullptr == pfnGetFlashProgress ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFlashProgress( hFirmware, pCompletionPercent );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Firmware Console Logs
/// 
/// @details
///     - The caller may pass nullptr for pFirmwareLog and set pSize to zero
///       when querying only for size.
///     - The caller must provide memory for Firmware log.
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
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t ZE_APICALL
zesFirmwareGetConsoleLogs(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    size_t* pSize,                                  ///< [in,out] size of firmware log
    char* pFirmwareLog                              ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFirmwareGetConsoleLogs_t pfnGetConsoleLogs = [&result] {
        auto pfnGetConsoleLogs = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetConsoleLogs;
        if( nullptr == pfnGetConsoleLogs ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetConsoleLogs;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetConsoleLogs( hFirmware, pSize, pFirmwareLog );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConsoleLogs = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetConsoleLogs;
    if( nullptr == pfnGetConsoleLogs ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConsoleLogs( hFirmware, pSize, pFirmwareLog );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of frequency domains
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFrequencyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_freq_handle_t* phFrequency                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumFrequencyDomains_t pfnEnumFrequencyDomains = [&result] {
        auto pfnEnumFrequencyDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFrequencyDomains;
        if( nullptr == pfnEnumFrequencyDomains ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumFrequencyDomains;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFrequencyDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFrequencyDomains;
    if( nullptr == pfnEnumFrequencyDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency properties - available frequencies
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
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFrequencyGetProperties(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hFrequency, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hFrequency, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get available non-overclocked hardware clock frequencies for the
///        frequency domain
/// 
/// @details
///     - The list of available frequencies is returned in order of slowest to
///       fastest.
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
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesFrequencyGetAvailableClocks(
    zes_freq_handle_t hFrequency,                   ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of frequencies that are available.
                                                    ///< if count is greater than the number of frequencies that are available,
                                                    ///< then the driver shall update the value with the correct number of frequencies.
    double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                    ///< MHz and sorted from slowest to fastest.
                                                    ///< if count is less than the number of frequencies that are available,
                                                    ///< then the driver shall only retrieve that number of frequencies.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyGetAvailableClocks_t pfnGetAvailableClocks = [&result] {
        auto pfnGetAvailableClocks = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetAvailableClocks;
        if( nullptr == pfnGetAvailableClocks ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetAvailableClocks;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAvailableClocks = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetAvailableClocks;
    if( nullptr == pfnGetAvailableClocks ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency limits
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
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
ze_result_t ZE_APICALL
zesFrequencyGetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyGetRange_t pfnGetRange = [&result] {
        auto pfnGetRange = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetRange;
        if( nullptr == pfnGetRange ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetRange;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetRange( hFrequency, pLimits );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRange = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetRange;
    if( nullptr == pfnGetRange ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRange( hFrequency, pLimits );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency range between which the hardware can operate.
/// 
/// @details
///     - The application may call this function with the frequency range min
///       and max values set to `-1` to request the frequency be (re)set to the
///       default values.
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
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencySetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencySetRange_t pfnSetRange = [&result] {
        auto pfnSetRange = ze_lib::context->zesDdiTable.load()->Frequency.pfnSetRange;
        if( nullptr == pfnSetRange ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetRange;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetRange( hFrequency, pLimits );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetRange = ze_lib::context->zesDdiTable.load()->Frequency.pfnSetRange;
    if( nullptr == pfnSetRange ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetRange( hFrequency, pLimits );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency state - frequency request, actual frequency, TDP
///        limits
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
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesFrequencyGetState(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hFrequency, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hFrequency, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency throttle time
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
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThrottleTime`
ze_result_t ZE_APICALL
zesFrequencyGetThrottleTime(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyGetThrottleTime_t pfnGetThrottleTime = [&result] {
        auto pfnGetThrottleTime = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetThrottleTime;
        if( nullptr == pfnGetThrottleTime ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetThrottleTime;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetThrottleTime( hFrequency, pThrottleTime );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetThrottleTime = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetThrottleTime( hFrequency, pThrottleTime );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking capabilities.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcCapabilities`
ze_result_t ZE_APICALL
zesFrequencyOcGetCapabilities(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcGetCapabilities_t pfnOcGetCapabilities = [&result] {
        auto pfnOcGetCapabilities = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetCapabilities;
        if( nullptr == pfnOcGetCapabilities ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcGetCapabilities;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetCapabilities = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetCapabilities;
    if( nullptr == pfnOcGetCapabilities ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking frequency target, if extended moded is
///        supported, will returned in 1 Mhz granularity.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentOcFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetFrequencyTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                    ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                    ///< cannot be greater than the `maxOcFrequency` member of
                                                    ///< ::zes_oc_capabilities_t.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcGetFrequencyTarget_t pfnOcGetFrequencyTarget = [&result] {
        auto pfnOcGetFrequencyTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetFrequencyTarget;
        if( nullptr == pfnOcGetFrequencyTarget ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcGetFrequencyTarget;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetFrequencyTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetFrequencyTarget;
    if( nullptr == pfnOcGetFrequencyTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking frequency target, if extended moded is
///        supported, can be set in 1 Mhz granularity.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetFrequencyTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                    ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                    ///< cannot be greater than the `maxOcFrequency` member of
                                                    ///< ::zes_oc_capabilities_t.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcSetFrequencyTarget_t pfnOcSetFrequencyTarget = [&result] {
        auto pfnOcSetFrequencyTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetFrequencyTarget;
        if( nullptr == pfnOcSetFrequencyTarget ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcSetFrequencyTarget;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetFrequencyTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetFrequencyTarget;
    if( nullptr == pfnOcSetFrequencyTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking voltage settings.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentVoltageTarget`
///         + `nullptr == pCurrentVoltageOffset`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetVoltageTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than the
                                                    ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
    double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, including the new overclock voltageTarget.
                                                    ///< Valid range is between the `minOcVoltageOffset` and
                                                    ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcGetVoltageTarget_t pfnOcGetVoltageTarget = [&result] {
        auto pfnOcGetVoltageTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetVoltageTarget;
        if( nullptr == pfnOcGetVoltageTarget ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcGetVoltageTarget;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetVoltageTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetVoltageTarget;
    if( nullptr == pfnOcGetVoltageTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking voltage settings.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetVoltageTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than the
                                                    ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
    double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, include the new overclock voltageTarget.
                                                    ///< Valid range is between the `minOcVoltageOffset` and
                                                    ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcSetVoltageTarget_t pfnOcSetVoltageTarget = [&result] {
        auto pfnOcSetVoltageTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetVoltageTarget;
        if( nullptr == pfnOcSetVoltageTarget ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcSetVoltageTarget;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetVoltageTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetVoltageTarget;
    if( nullptr == pfnOcSetVoltageTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking mode.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OC_MODE_FIXED < CurrentOcMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetMode(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcSetMode_t pfnOcSetMode = [&result] {
        auto pfnOcSetMode = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetMode;
        if( nullptr == pfnOcSetMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcSetMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcSetMode( hFrequency, CurrentOcMode );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetMode = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetMode;
    if( nullptr == pfnOcSetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetMode( hFrequency, CurrentOcMode );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking mode.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentOcMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetMode(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcGetMode_t pfnOcGetMode = [&result] {
        auto pfnOcGetMode = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetMode;
        if( nullptr == pfnOcGetMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcGetMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcGetMode( hFrequency, pCurrentOcMode );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetMode = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetMode;
    if( nullptr == pfnOcGetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetMode( hFrequency, pCurrentOcMode );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum current limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcIccMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + Capability the `isIccMaxSupported` member of ::zes_oc_capabilities_t is false for this frequency domain.
ze_result_t ZE_APICALL
zesFrequencyOcGetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                    ///< successful return.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcGetIccMax_t pfnOcGetIccMax = [&result] {
        auto pfnOcGetIccMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetIccMax;
        if( nullptr == pfnOcGetIccMax ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcGetIccMax;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcGetIccMax( hFrequency, pOcIccMax );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetIccMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetIccMax;
    if( nullptr == pfnOcGetIccMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetIccMax( hFrequency, pOcIccMax );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum current limit setting.
/// 
/// @details
///     - Setting ocIccMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The `isIccMaxSupported` member of ::zes_oc_capabilities_t is false for this frequency domain.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified current limit is too low or too high.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcSetIccMax_t pfnOcSetIccMax = [&result] {
        auto pfnOcSetIccMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetIccMax;
        if( nullptr == pfnOcSetIccMax ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcSetIccMax;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcSetIccMax( hFrequency, ocIccMax );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetIccMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetIccMax;
    if( nullptr == pfnOcSetIccMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetIccMax( hFrequency, ocIccMax );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum temperature limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcTjMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
ze_result_t ZE_APICALL
zesFrequencyOcGetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                    ///< on successful return.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcGetTjMax_t pfnOcGetTjMax = [&result] {
        auto pfnOcGetTjMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetTjMax;
        if( nullptr == pfnOcGetTjMax ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcGetTjMax;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcGetTjMax( hFrequency, pOcTjMax );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetTjMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetTjMax;
    if( nullptr == pfnOcGetTjMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetTjMax( hFrequency, pOcTjMax );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum temperature limit setting.
/// 
/// @details
///     - Setting ocTjMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The `isTjMaxSupported` member of ::zes_oc_capabilities_t is false for this frequency domain.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified temperature limit is too high.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFrequencyOcSetTjMax_t pfnOcSetTjMax = [&result] {
        auto pfnOcSetTjMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetTjMax;
        if( nullptr == pfnOcSetTjMax ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOcSetTjMax;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOcSetTjMax( hFrequency, ocTjMax );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetTjMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetTjMax;
    if( nullptr == pfnOcSetTjMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetTjMax( hFrequency, ocTjMax );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of LEDs
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumLeds(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_led_handle_t* phLed                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumLeds_t pfnEnumLeds = [&result] {
        auto pfnEnumLeds = ze_lib::context->zesDdiTable.load()->Device.pfnEnumLeds;
        if( nullptr == pfnEnumLeds ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumLeds;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumLeds( hDevice, pCount, phLed );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumLeds = ze_lib::context->zesDdiTable.load()->Device.pfnEnumLeds;
    if( nullptr == pfnEnumLeds ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumLeds( hDevice, pCount, phLed );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED properties
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
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesLedGetProperties(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnLedGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Led.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hLed, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Led.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hLed, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a LED - on/off, color
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
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesLedGetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnLedGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Led.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hLed, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Led.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hLed, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Turn the LED on/off
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
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesLedSetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnLedSetState_t pfnSetState = [&result] {
        auto pfnSetState = ze_lib::context->zesDdiTable.load()->Led.pfnSetState;
        if( nullptr == pfnSetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetState( hLed, enable );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetState = ze_lib::context->zesDdiTable.load()->Led.pfnSetState;
    if( nullptr == pfnSetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetState( hLed, enable );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the color of the LED
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
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pColor`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This LED doesn't not support color changes. See the `haveRGB` member of ::zes_led_properties_t.
ze_result_t ZE_APICALL
zesLedSetColor(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    const zes_led_color_t* pColor                   ///< [in] New color of the LED.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnLedSetColor_t pfnSetColor = [&result] {
        auto pfnSetColor = ze_lib::context->zesDdiTable.load()->Led.pfnSetColor;
        if( nullptr == pfnSetColor ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetColor;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetColor( hLed, pColor );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetColor = ze_lib::context->zesDdiTable.load()->Led.pfnSetColor;
    if( nullptr == pfnSetColor ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetColor( hLed, pColor );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of memory modules
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumMemoryModules(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_mem_handle_t* phMemory                      ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumMemoryModules_t pfnEnumMemoryModules = [&result] {
        auto pfnEnumMemoryModules = ze_lib::context->zesDdiTable.load()->Device.pfnEnumMemoryModules;
        if( nullptr == pfnEnumMemoryModules ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumMemoryModules;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumMemoryModules( hDevice, pCount, phMemory );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumMemoryModules = ze_lib::context->zesDdiTable.load()->Device.pfnEnumMemoryModules;
    if( nullptr == pfnEnumMemoryModules ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumMemoryModules( hDevice, pCount, phMemory );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory properties
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
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesMemoryGetProperties(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnMemoryGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Memory.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hMemory, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Memory.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hMemory, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory state - health, allocated
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
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesMemoryGetState(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnMemoryGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Memory.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hMemory, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Memory.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hMemory, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory bandwidth
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
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBandwidth`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesMemoryGetBandwidth(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the total number of bytes read from and written
                                                    ///< to memory, as well as the current maximum bandwidth.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnMemoryGetBandwidth_t pfnGetBandwidth = [&result] {
        auto pfnGetBandwidth = ze_lib::context->zesDdiTable.load()->Memory.pfnGetBandwidth;
        if( nullptr == pfnGetBandwidth ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetBandwidth;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetBandwidth( hMemory, pBandwidth );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetBandwidth = ze_lib::context->zesDdiTable.load()->Memory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetBandwidth( hMemory, pBandwidth );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handles to accelerator domains whose performance can be optimized
///        via a Performance Factor
/// 
/// @details
///     - A Performance Factor should be tuned for each workload.
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPerformanceFactorDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_perf_handle_t* phPerf                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumPerformanceFactorDomains_t pfnEnumPerformanceFactorDomains = [&result] {
        auto pfnEnumPerformanceFactorDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPerformanceFactorDomains;
        if( nullptr == pfnEnumPerformanceFactorDomains ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumPerformanceFactorDomains;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumPerformanceFactorDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPerformanceFactorDomains;
    if( nullptr == pfnEnumPerformanceFactorDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about a Performance Factor domain
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
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPerformanceFactorGetProperties(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                    ///< Factor domain.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPerformanceFactorGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hPerf, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPerf, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current Performance Factor for a given domain
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
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFactor`
ze_result_t ZE_APICALL
zesPerformanceFactorGetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                    ///< hardware (may not be the same as the requested Performance Factor).
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPerformanceFactorGetConfig_t pfnGetConfig = [&result] {
        auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetConfig( hPerf, pFactor );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hPerf, pFactor );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the performance factor for a domain
/// 
/// @details
///     - The Performance Factor is a number between 0 and 100.
///     - A Performance Factor is a hint to the hardware. Depending on the
///       hardware, the request may not be granted. Follow up this function with
///       a call to ::zesPerformanceFactorGetConfig() to determine the actual
///       factor being used by the hardware.
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
///         + `nullptr == hPerf`
ze_result_t ZE_APICALL
zesPerformanceFactorSetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double factor                                   ///< [in] The new Performance Factor.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPerformanceFactorSetConfig_t pfnSetConfig = [&result] {
        auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetConfig( hPerf, factor );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hPerf, factor );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power domains
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPowerDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_pwr_handle_t* phPower                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumPowerDomains_t pfnEnumPowerDomains = [&result] {
        auto pfnEnumPowerDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPowerDomains;
        if( nullptr == pfnEnumPowerDomains ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumPowerDomains;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumPowerDomains( hDevice, pCount, phPower );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumPowerDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPowerDomains;
    if( nullptr == pfnEnumPowerDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumPowerDomains( hDevice, pCount, phPower );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of the PCIe card-level power
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
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
///         + `nullptr == phPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + The device does not provide access to card level power controls or telemetry. An invalid power domain handle will be returned in phPower.
ze_result_t ZE_APICALL
zesDeviceGetCardPowerDomain(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGetCardPowerDomain_t pfnGetCardPowerDomain = [&result] {
        auto pfnGetCardPowerDomain = ze_lib::context->zesDdiTable.load()->Device.pfnGetCardPowerDomain;
        if( nullptr == pfnGetCardPowerDomain ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetCardPowerDomain;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetCardPowerDomain( hDevice, phPower );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCardPowerDomain = ze_lib::context->zesDdiTable.load()->Device.pfnGetCardPowerDomain;
    if( nullptr == pfnGetCardPowerDomain ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCardPowerDomain( hDevice, phPower );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a power domain
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
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPowerGetProperties(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Power.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hPower, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Power.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPower, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
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
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEnergy`
ze_result_t ZE_APICALL
zesPowerGetEnergyCounter(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerGetEnergyCounter_t pfnGetEnergyCounter = [&result] {
        auto pfnGetEnergyCounter = ze_lib::context->zesDdiTable.load()->Power.pfnGetEnergyCounter;
        if( nullptr == pfnGetEnergyCounter ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetEnergyCounter;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetEnergyCounter( hPower, pEnergy );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetEnergyCounter = ze_lib::context->zesDdiTable.load()->Power.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetEnergyCounter( hPower, pEnergy );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] Use ::zesPowerGetLimitsExt.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
ze_result_t ZE_APICALL
zesPowerGetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit. If this is null, the
                                                    ///< current sustained power limits will not be returned.
    zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit. If this is null, the current
                                                    ///< peak power limits will not be returned.
    zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                    ///< power limits will not be returned.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerGetLimits_t pfnGetLimits = [&result] {
        auto pfnGetLimits = ze_lib::context->zesDdiTable.load()->Power.pfnGetLimits;
        if( nullptr == pfnGetLimits ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetLimits;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLimits = ze_lib::context->zesDdiTable.load()->Power.pfnGetLimits;
    if( nullptr == pfnGetLimits ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] Use ::zesPowerSetLimitsExt.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t ZE_APICALL
zesPowerSetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit. If this is null, no changes
                                                    ///< will be made to the sustained power limits.
    const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit. If this is null, no changes will
                                                    ///< be made to the burst power limits.
    const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit. If this is null, no changes will
                                                    ///< be made to the peak power limits.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerSetLimits_t pfnSetLimits = [&result] {
        auto pfnSetLimits = ze_lib::context->zesDdiTable.load()->Power.pfnSetLimits;
        if( nullptr == pfnSetLimits ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetLimits;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetLimits = ze_lib::context->zesDdiTable.load()->Power.pfnSetLimits;
    if( nullptr == pfnSetLimits ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy threshold
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
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThreshold`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check the `isEnergyThresholdSupported` member of ::zes_power_properties_t).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t ZE_APICALL
zesPowerGetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerGetEnergyThreshold_t pfnGetEnergyThreshold = [&result] {
        auto pfnGetEnergyThreshold = ze_lib::context->zesDdiTable.load()->Power.pfnGetEnergyThreshold;
        if( nullptr == pfnGetEnergyThreshold ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetEnergyThreshold;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetEnergyThreshold( hPower, pThreshold );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetEnergyThreshold = ze_lib::context->zesDdiTable.load()->Power.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetEnergyThreshold( hPower, pThreshold );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - An event ::ZES_EVENT_TYPE_FLAG_ENERGY_THRESHOLD_CROSSED will be
///       generated when the delta energy consumed starting from this call
///       exceeds the specified threshold. Use the function
///       ::zesDeviceEventRegister() to start receiving the event.
///     - Only one running process can control the energy threshold at a given
///       time. If another process attempts to change the energy threshold, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesPowerGetEnergyThreshold() to determine the process ID currently
///       controlling this setting.
///     - Calling this function will remove any pending energy thresholds and
///       start counting from the time of this call.
///     - Once the energy threshold has been reached and the event generated,
///       the threshold is automatically removed. It is up to the application to
///       request a new threshold.
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
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check the `isEnergyThresholdSupported` member of ::zes_power_properties_t).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process has set the energy threshold.
ze_result_t ZE_APICALL
zesPowerSetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerSetEnergyThreshold_t pfnSetEnergyThreshold = [&result] {
        auto pfnSetEnergyThreshold = ze_lib::context->zesDdiTable.load()->Power.pfnSetEnergyThreshold;
        if( nullptr == pfnSetEnergyThreshold ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetEnergyThreshold;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetEnergyThreshold( hPower, threshold );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEnergyThreshold = ze_lib::context->zesDdiTable.load()->Power.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEnergyThreshold( hPower, threshold );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power supplies
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPsus(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_psu_handle_t* phPsu                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumPsus_t pfnEnumPsus = [&result] {
        auto pfnEnumPsus = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPsus;
        if( nullptr == pfnEnumPsus ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumPsus;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumPsus( hDevice, pCount, phPsu );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumPsus = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPsus;
    if( nullptr == pfnEnumPsus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumPsus( hDevice, pCount, phPsu );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power supply properties
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
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPsuGetProperties(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPsuGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Psu.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hPsu, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Psu.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPsu, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current power supply state
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
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesPsuGetState(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPsuGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Psu.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hPsu, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Psu.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hPsu, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of all RAS error sets on a device
/// 
/// @details
///     - A RAS error set is a collection of RAS error counters of a given type
///       (correctable/uncorrectable) from hardware blocks contained within a
///       sub-device or within the device.
///     - A device without sub-devices will typically return two handles, one
///       for correctable errors sets and one for uncorrectable error sets.
///     - A device with sub-devices will return RAS error sets for each
///       sub-device and possibly RAS error sets for hardware blocks outside the
///       sub-devices.
///     - If the function completes successfully but pCount is set to 0, RAS
///       features are not available/enabled on this device.
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumRasErrorSets(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_ras_handle_t* phRas                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumRasErrorSets_t pfnEnumRasErrorSets = [&result] {
        auto pfnEnumRasErrorSets = ze_lib::context->zesDdiTable.load()->Device.pfnEnumRasErrorSets;
        if( nullptr == pfnEnumRasErrorSets ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumRasErrorSets;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumRasErrorSets( hDevice, pCount, phRas );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumRasErrorSets = ze_lib::context->zesDdiTable.load()->Device.pfnEnumRasErrorSets;
    if( nullptr == pfnEnumRasErrorSets ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumRasErrorSets( hDevice, pCount, phRas );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS properties of a given RAS error set - this enables discovery
///        of the type of RAS error set (correctable/uncorrectable) and if
///        located on a sub-device
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
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesRasGetProperties(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnRasGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Ras.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hRas, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Ras.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hRas, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the configured
///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
///       be triggered.
///     - When a particular RAS uncorrectable error counter exceeds the
///       configured threshold, the event
///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be triggered.
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
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesRasGetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                    ///< thresholds used to trigger events
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnRasGetConfig_t pfnGetConfig = [&result] {
        auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Ras.pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetConfig( hRas, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Ras.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hRas, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the specified
///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
///       be generated.
///     - When a particular RAS uncorrectable error counter exceeds the
///       specified threshold, the event
///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be generated.
///     - Call ::zesRasGetState() and set the clear flag to true to restart
///       event generation once counters have exceeded thresholds.
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
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to set thresholds.
ze_result_t ZE_APICALL
zesRasSetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnRasSetConfig_t pfnSetConfig = [&result] {
        auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->Ras.pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetConfig( hRas, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->Ras.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hRas, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current value of RAS error counters for a particular error set
/// 
/// @details
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
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
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t ZE_APICALL
zesRasGetState(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnRasGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Ras.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hRas, clear, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Ras.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hRas, clear, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns handles to scheduler components.
/// 
/// @details
///     - Each scheduler component manages the distribution of work across one
///       or more accelerator engines.
///     - If an application wishes to change the scheduler behavior for all
///       accelerator engines of a specific type (e.g. compute), it should
///       select all the handles where the `engines` member
///       ::zes_sched_properties_t contains that type.
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumSchedulers(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_sched_handle_t* phScheduler                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumSchedulers_t pfnEnumSchedulers = [&result] {
        auto pfnEnumSchedulers = ze_lib::context->zesDdiTable.load()->Device.pfnEnumSchedulers;
        if( nullptr == pfnEnumSchedulers ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumSchedulers;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumSchedulers( hDevice, pCount, phScheduler );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumSchedulers = ze_lib::context->zesDdiTable.load()->Device.pfnEnumSchedulers;
    if( nullptr == pfnEnumSchedulers ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumSchedulers( hDevice, pCount, phScheduler );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a scheduler component
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
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesSchedulerGetProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
    zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hScheduler, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hScheduler, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduling mode in effect on a scheduler component.
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
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetCurrentMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerGetCurrentMode_t pfnGetCurrentMode = [&result] {
        auto pfnGetCurrentMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetCurrentMode;
        if( nullptr == pfnGetCurrentMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetCurrentMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetCurrentMode( hScheduler, pMode );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCurrentMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetCurrentMode;
    if( nullptr == pfnGetCurrentMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCurrentMode( hScheduler, pMode );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMEOUT
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
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetTimeoutModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerGetTimeoutModeProperties_t pfnGetTimeoutModeProperties = [&result] {
        auto pfnGetTimeoutModeProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetTimeoutModeProperties;
        if( nullptr == pfnGetTimeoutModeProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetTimeoutModeProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetTimeoutModeProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetTimeoutModeProperties;
    if( nullptr == pfnGetTimeoutModeProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMESLICE
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
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetTimesliceModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerGetTimesliceModeProperties_t pfnGetTimesliceModeProperties = [&result] {
        auto pfnGetTimesliceModeProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetTimesliceModeProperties;
        if( nullptr == pfnGetTimesliceModeProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetTimesliceModeProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetTimesliceModeProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetTimesliceModeProperties;
    if( nullptr == pfnGetTimesliceModeProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMEOUT or update scheduler
///        mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized for multiple applications or contexts
///       submitting work to the hardware. When higher priority work arrives,
///       the scheduler attempts to pause the current executing work within some
///       timeout interval, then submits the other work.
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
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetTimeoutMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerSetTimeoutMode_t pfnSetTimeoutMode = [&result] {
        auto pfnSetTimeoutMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetTimeoutMode;
        if( nullptr == pfnSetTimeoutMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetTimeoutMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetTimeoutMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetTimeoutMode;
    if( nullptr == pfnSetTimeoutMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMESLICE or update
///        scheduler mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized to provide fair sharing of hardware execution
///       time between multiple contexts submitting work to the hardware
///       concurrently.
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
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetTimesliceMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerSetTimesliceMode_t pfnSetTimesliceMode = [&result] {
        auto pfnSetTimesliceMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetTimesliceMode;
        if( nullptr == pfnSetTimesliceMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetTimesliceMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetTimesliceMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetTimesliceMode;
    if( nullptr == pfnSetTimesliceMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_EXCLUSIVE
/// 
/// @details
///     - This mode is optimized for single application/context use-cases. It
///       permits a context to run indefinitely on the hardware without being
///       preempted or terminated. All pending work for other contexts must wait
///       until the running context completes with no further submitted work.
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
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetExclusiveMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerSetExclusiveMode_t pfnSetExclusiveMode = [&result] {
        auto pfnSetExclusiveMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetExclusiveMode;
        if( nullptr == pfnSetExclusiveMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetExclusiveMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetExclusiveMode( hScheduler, pNeedReload );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetExclusiveMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetExclusiveMode;
    if( nullptr == pfnSetExclusiveMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetExclusiveMode( hScheduler, pNeedReload );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG
/// 
/// @details
///     - This is a special mode that must ben enabled when debugging an
///       application that uses this device e.g. using the Level0 Debug API.
///     - It ensures that only one command queue can execute work on the
///       hardware at a given time. Work is permitted to run as long as needed
///       without enforcing any scheduler fairness policies.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetComputeUnitDebugMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnSchedulerSetComputeUnitDebugMode_t pfnSetComputeUnitDebugMode = [&result] {
        auto pfnSetComputeUnitDebugMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetComputeUnitDebugMode;
        if( nullptr == pfnSetComputeUnitDebugMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetComputeUnitDebugMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetComputeUnitDebugMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetComputeUnitDebugMode;
    if( nullptr == pfnSetComputeUnitDebugMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of standby controls
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumStandbyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_standby_handle_t* phStandby                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumStandbyDomains_t pfnEnumStandbyDomains = [&result] {
        auto pfnEnumStandbyDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumStandbyDomains;
        if( nullptr == pfnEnumStandbyDomains ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumStandbyDomains;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumStandbyDomains( hDevice, pCount, phStandby );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumStandbyDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumStandbyDomains;
    if( nullptr == pfnEnumStandbyDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumStandbyDomains( hDevice, pCount, phStandby );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get standby hardware component properties
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
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesStandbyGetProperties(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnStandbyGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Standby.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hStandby, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Standby.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hStandby, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current standby promotion mode
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
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
ze_result_t ZE_APICALL
zesStandbyGetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnStandbyGetMode_t pfnGetMode = [&result] {
        auto pfnGetMode = ze_lib::context->zesDdiTable.load()->Standby.pfnGetMode;
        if( nullptr == pfnGetMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetMode( hStandby, pMode );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMode = ze_lib::context->zesDdiTable.load()->Standby.pfnGetMode;
    if( nullptr == pfnGetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMode( hStandby, pMode );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set standby promotion mode
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
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_STANDBY_PROMO_MODE_NEVER < mode`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesStandbySetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnStandbySetMode_t pfnSetMode = [&result] {
        auto pfnSetMode = ze_lib::context->zesDdiTable.load()->Standby.pfnSetMode;
        if( nullptr == pfnSetMode ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetMode;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetMode( hStandby, mode );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetMode = ze_lib::context->zesDdiTable.load()->Standby.pfnSetMode;
    if( nullptr == pfnSetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetMode( hStandby, mode );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of temperature sensors
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumTemperatureSensors(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_temp_handle_t* phTemperature                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumTemperatureSensors_t pfnEnumTemperatureSensors = [&result] {
        auto pfnEnumTemperatureSensors = ze_lib::context->zesDdiTable.load()->Device.pfnEnumTemperatureSensors;
        if( nullptr == pfnEnumTemperatureSensors ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumTemperatureSensors;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumTemperatureSensors = ze_lib::context->zesDdiTable.load()->Device.pfnEnumTemperatureSensors;
    if( nullptr == pfnEnumTemperatureSensors ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor properties
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
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesTemperatureGetProperties(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnTemperatureGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hTemperature, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hTemperature, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature configuration for this sensor - which events are
///        triggered and the trigger conditions
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
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally this is only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL.
///         + One or both of the thresholds is not supported. Check the `isThreshold1Supported` and `isThreshold2Supported` members of ::zes_temp_properties_t.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t ZE_APICALL
zesTemperatureGetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnTemperatureGetConfig_t pfnGetConfig = [&result] {
        auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetConfig( hTemperature, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hTemperature, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature configuration for this sensor - indicates which events
///        are triggered and the trigger conditions
/// 
/// @details
///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL will be triggered when
///       temperature reaches the critical range. Use the function
///       ::zesDeviceEventRegister() to start receiving this event.
///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD1 and
///       ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD2 will be generated when
///       temperature cross the thresholds set using this function. Use the
///       function ::zesDeviceEventRegister() to start receiving these events.
///     - Only one running process can set the temperature configuration at a
///       time. If another process attempts to change the configuration, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesTemperatureGetConfig() will return the process ID currently
///       controlling these settings.
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
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally they are only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL.
///         + Enabling the critical temperature event is not supported. Check the `isCriticalTempSupported` member of ::zes_temp_properties_t.
///         + One or both of the thresholds is not supported. Check the `isThreshold1Supported` and `isThreshold2Supported` members of ::zes_temp_properties_t.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or both the thresholds is above TjMax (see ::zesFrequencyOcGetTjMax()). Temperature thresholds must be below this value.
ze_result_t ZE_APICALL
zesTemperatureSetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    const zes_temp_config_t* pConfig                ///< [in] New configuration.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnTemperatureSetConfig_t pfnSetConfig = [&result] {
        auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->Temperature.pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetConfig;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetConfig( hTemperature, pConfig );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->Temperature.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hTemperature, pConfig );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the temperature from a specified sensor
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
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTemperature`
ze_result_t ZE_APICALL
zesTemperatureGetState(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                    ///< in degrees Celsius.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnTemperatureGetState_t pfnGetState = [&result] {
        auto pfnGetState = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetState;
        if( nullptr == pfnGetState ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetState;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetState( hTemperature, pTemperature );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hTemperature, pTemperature );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This function returns all the power limits associated with the
///       supplied power domain.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesPowerGetLimitsExt(
    zes_pwr_handle_t hPower,                        ///< [in] Power domain handle instance.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of power limit descriptors. If count is
                                                    ///< zero, then the driver shall update the value with the total number of
                                                    ///< components of this type that are available. If count is greater than
                                                    ///< the number of components of this type that are available, then the
                                                    ///< driver shall update the value with the correct number of components.
    zes_power_limit_ext_desc_t* pSustained          ///< [in,out][optional][range(0, *pCount)] Array of query results for power
                                                    ///< limit descriptors. If count is less than the number of components of
                                                    ///< this type that are available, then the driver shall only retrieve that
                                                    ///< number of components.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerGetLimitsExt_t pfnGetLimitsExt = [&result] {
        auto pfnGetLimitsExt = ze_lib::context->zesDdiTable.load()->Power.pfnGetLimitsExt;
        if( nullptr == pfnGetLimitsExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetLimitsExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetLimitsExt( hPower, pCount, pSustained );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLimitsExt = ze_lib::context->zesDdiTable.load()->Power.pfnGetLimitsExt;
    if( nullptr == pfnGetLimitsExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLimitsExt( hPower, pCount, pSustained );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application can only modify unlocked members of the limit
///       descriptors returned by ::zesPowerGetLimitsExt.
///     - Not all the limits returned by ::zesPowerGetLimitsExt need to be
///       supplied to this function.
///     - Limits do not have to be supplied in the same order as returned by
///       ::zesPowerGetLimitsExt.
///     - The same limit can be supplied multiple times. Limits are applied in
///       the order in which they are supplied.
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
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t ZE_APICALL
zesPowerSetLimitsExt(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in] Pointer to the number of power limit descriptors.
    zes_power_limit_ext_desc_t* pSustained          ///< [in][optional][range(0, *pCount)] Array of power limit descriptors.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnPowerSetLimitsExt_t pfnSetLimitsExt = [&result] {
        auto pfnSetLimitsExt = ze_lib::context->zesDdiTable.load()->Power.pfnSetLimitsExt;
        if( nullptr == pfnSetLimitsExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetLimitsExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetLimitsExt( hPower, pCount, pSustained );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetLimitsExt = ze_lib::context->zesDdiTable.load()->Power.pfnSetLimitsExt;
    if( nullptr == pfnSetLimitsExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetLimitsExt( hPower, pCount, pSustained );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get activity stats for Physical Function (PF) and each Virtual
///        Function (VF) associated with engine group.
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
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE - "Engine activity extension is not supported in the environment."
ze_result_t ZE_APICALL
zesEngineGetActivityExt(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of engine stats available.
                                                    ///<  - if count is greater than the total number of engine stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of engine stats available.
                                                    ///<  - The count returned is the sum of number of VF instances currently
                                                    ///< available and the PF instance.
    zes_engine_stats_t* pStats                      ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                    ///<  - if count is less than the total number of engine stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector with engine stat for
                                                    ///< PF at index 0 of the vector followed by user provided pCount-1 number
                                                    ///< of VF engine stats.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnEngineGetActivityExt_t pfnGetActivityExt = [&result] {
        auto pfnGetActivityExt = ze_lib::context->zesDdiTable.load()->Engine.pfnGetActivityExt;
        if( nullptr == pfnGetActivityExt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetActivityExt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetActivityExt( hEngine, pCount, pStats );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetActivityExt = ze_lib::context->zesDdiTable.load()->Engine.pfnGetActivityExt;
    if( nullptr == pfnGetActivityExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetActivityExt( hEngine, pCount, pStats );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Ras Get State
/// 
/// @details
///     - This function retrieves error counters for different RAS error
///       categories.
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
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesRasGetStateExp(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of RAS state structures that can be retrieved.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of error categories for which state can be retrieved.
                                                    ///< if count is greater than the number of RAS states available, then the
                                                    ///< driver shall update the value with the correct number of RAS states available.
    zes_ras_state_exp_t* pState                     ///< [in,out][optional][range(0, *pCount)] array of query results for RAS
                                                    ///< error states for different categories.
                                                    ///< if count is less than the number of RAS states available, then driver
                                                    ///< shall only retrieve that number of RAS states.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnRasGetStateExp_t pfnGetStateExp = [&result] {
        auto pfnGetStateExp = ze_lib::context->zesDdiTable.load()->RasExp.pfnGetStateExp;
        if( nullptr == pfnGetStateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetStateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetStateExp( hRas, pCount, pState );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetStateExp = ze_lib::context->zesDdiTable.load()->RasExp.pfnGetStateExp;
    if( nullptr == pfnGetStateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetStateExp( hRas, pCount, pState );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Ras Clear State
/// 
/// @details
///     - This function clears error counters for a RAS error category.
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
///     - The application should not call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_RAS_ERROR_CATEGORY_EXP_L3FABRIC_ERRORS < category`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t ZE_APICALL
zesRasClearStateExp(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_error_category_exp_t category           ///< [in] category for which error counter is to be cleared.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnRasClearStateExp_t pfnClearStateExp = [&result] {
        auto pfnClearStateExp = ze_lib::context->zesDdiTable.load()->RasExp.pfnClearStateExp;
        if( nullptr == pfnClearStateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnClearStateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnClearStateExp( hRas, category );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnClearStateExp = ze_lib::context->zesDdiTable.load()->RasExp.pfnClearStateExp;
    if( nullptr == pfnClearStateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnClearStateExp( hRas, category );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the firmware security version number of the currently running
///        firmware
/// 
/// @details
///     - The application should create a character array of size
///       ::ZES_STRING_PROPERTY_SIZE and reference it for the `pVersion`
///       parameter.
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
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pVersion`
ze_result_t ZE_APICALL
zesFirmwareGetSecurityVersionExp(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    char* pVersion                                  ///< [in,out] NULL terminated string value. The string "unknown" will be
                                                    ///< returned if this property cannot be determined.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFirmwareGetSecurityVersionExp_t pfnGetSecurityVersionExp = [&result] {
        auto pfnGetSecurityVersionExp = ze_lib::context->zesDdiTable.load()->FirmwareExp.pfnGetSecurityVersionExp;
        if( nullptr == pfnGetSecurityVersionExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetSecurityVersionExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetSecurityVersionExp( hFirmware, pVersion );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSecurityVersionExp = ze_lib::context->zesDdiTable.load()->FirmwareExp.pfnGetSecurityVersionExp;
    if( nullptr == pfnGetSecurityVersionExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSecurityVersionExp( hFirmware, pVersion );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the firmware security version number
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
///         + `nullptr == hFirmware`
ze_result_t ZE_APICALL
zesFirmwareSetSecurityVersionExp(
    zes_firmware_handle_t hFirmware                 ///< [in] Handle for the component.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnFirmwareSetSecurityVersionExp_t pfnSetSecurityVersionExp = [&result] {
        auto pfnSetSecurityVersionExp = ze_lib::context->zesDdiTable.load()->FirmwareExp.pfnSetSecurityVersionExp;
        if( nullptr == pfnSetSecurityVersionExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetSecurityVersionExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetSecurityVersionExp( hFirmware );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetSecurityVersionExp = ze_lib::context->zesDdiTable.load()->FirmwareExp.pfnSetSecurityVersionExp;
    if( nullptr == pfnSetSecurityVersionExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetSecurityVersionExp( hFirmware );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves sub device properties for the given sysman device handle
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceGetSubDevicePropertiesExp(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sub devices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of sub devices currently attached to the device.
                                                    ///< if count is greater than the number of sub devices currently attached
                                                    ///< to the device, then the driver shall update the value with the correct
                                                    ///< number of sub devices.
    zes_subdevice_exp_properties_t* pSubdeviceProps ///< [in,out][optional][range(0, *pCount)] array of sub device property structures.
                                                    ///< if count is less than the number of sysman sub devices available, then
                                                    ///< the driver shall only retrieve that number of sub device property structures.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceGetSubDevicePropertiesExp_t pfnGetSubDevicePropertiesExp = [&result] {
        auto pfnGetSubDevicePropertiesExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnGetSubDevicePropertiesExp;
        if( nullptr == pfnGetSubDevicePropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetSubDevicePropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetSubDevicePropertiesExp( hDevice, pCount, pSubdeviceProps );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSubDevicePropertiesExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnGetSubDevicePropertiesExp;
    if( nullptr == pfnGetSubDevicePropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSubDevicePropertiesExp( hDevice, pCount, pSubdeviceProps );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves sysman device and subdevice index for the given UUID and
///        sysman driver
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
///         + `nullptr == phDevice`
///         + `nullptr == onSubdevice`
///         + `nullptr == subdeviceId`
ze_result_t ZE_APICALL
zesDriverGetDeviceByUuidExp(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
    zes_uuid_t uuid,                                ///< [in] universal unique identifier.
    zes_device_handle_t* phDevice,                  ///< [out] Sysman handle of the device.
    ze_bool_t* onSubdevice,                         ///< [out] True if the UUID belongs to the sub-device; false means that
                                                    ///< UUID belongs to the root device.
    uint32_t* subdeviceId                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDriverGetDeviceByUuidExp_t pfnGetDeviceByUuidExp = [&result] {
        auto pfnGetDeviceByUuidExp = ze_lib::context->zesDdiTable.load()->DriverExp.pfnGetDeviceByUuidExp;
        if( nullptr == pfnGetDeviceByUuidExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDeviceByUuidExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDeviceByUuidExp( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDeviceByUuidExp = ze_lib::context->zesDdiTable.load()->DriverExp.pfnGetDeviceByUuidExp;
    if( nullptr == pfnGetDeviceByUuidExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDeviceByUuidExp( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of virtual function modules
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use ::zesDeviceEnumEnabledVFExp.
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumActiveVFExp(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_vf_handle_t* phVFhandle                     ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumActiveVFExp_t pfnEnumActiveVFExp = [&result] {
        auto pfnEnumActiveVFExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnEnumActiveVFExp;
        if( nullptr == pfnEnumActiveVFExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumActiveVFExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumActiveVFExp( hDevice, pCount, phVFhandle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumActiveVFExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnEnumActiveVFExp;
    if( nullptr == pfnEnumActiveVFExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumActiveVFExp( hDevice, pCount, phVFhandle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get virtual function management properties
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use
///       ::zesVFManagementGetVFCapabilitiesExp.
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
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesVFManagementGetVFPropertiesExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
    zes_vf_exp_properties_t* pProperties            ///< [in,out] Will contain VF properties.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementGetVFPropertiesExp_t pfnGetVFPropertiesExp = [&result] {
        auto pfnGetVFPropertiesExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFPropertiesExp;
        if( nullptr == pfnGetVFPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFPropertiesExp( hVFhandle, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFPropertiesExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFPropertiesExp;
    if( nullptr == pfnGetVFPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFPropertiesExp( hVFhandle, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory activity stats for each available memory types associated
///        with Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use
///       ::zesVFManagementGetVFMemoryUtilizationExp2.
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
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFMemoryUtilizationExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF memory stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of memory stats available.
                                                    ///<  - if count is greater than the total number of memory stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of memory stats available.
                                                    ///<  - The count returned is the sum of number of VF instances currently
                                                    ///< available and the PF instance.
    zes_vf_util_mem_exp_t* pMemUtil                 ///< [in,out][optional][range(0, *pCount)] array of memory group activity counters.
                                                    ///<  - if count is less than the total number of memory stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< memory stats.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementGetVFMemoryUtilizationExp_t pfnGetVFMemoryUtilizationExp = [&result] {
        auto pfnGetVFMemoryUtilizationExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFMemoryUtilizationExp;
        if( nullptr == pfnGetVFMemoryUtilizationExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFMemoryUtilizationExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFMemoryUtilizationExp( hVFhandle, pCount, pMemUtil );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFMemoryUtilizationExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFMemoryUtilizationExp;
    if( nullptr == pfnGetVFMemoryUtilizationExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFMemoryUtilizationExp( hVFhandle, pCount, pMemUtil );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine activity stats for each available engine group associated
///        with Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use
///       ::zesVFManagementGetVFEngineUtilizationExp2.
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
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFEngineUtilizationExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of engine stats available.
                                                    ///<  - if count is greater than the total number of engine stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of engine stats available.
                                                    ///<  - The count returned is the sum of number of VF instances currently
                                                    ///< available and the PF instance.
    zes_vf_util_engine_exp_t* pEngineUtil           ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                    ///<  - if count is less than the total number of engine stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< engine stats.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementGetVFEngineUtilizationExp_t pfnGetVFEngineUtilizationExp = [&result] {
        auto pfnGetVFEngineUtilizationExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFEngineUtilizationExp;
        if( nullptr == pfnGetVFEngineUtilizationExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFEngineUtilizationExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFEngineUtilizationExp( hVFhandle, pCount, pEngineUtil );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFEngineUtilizationExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFEngineUtilizationExp;
    if( nullptr == pfnGetVFEngineUtilizationExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFEngineUtilizationExp( hVFhandle, pCount, pEngineUtil );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure utilization telemetry enabled or disabled associated with
///        Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported.
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
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < flags`
ze_result_t ZE_APICALL
zesVFManagementSetVFTelemetryModeExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    zes_vf_info_util_exp_flags_t flags,             ///< [in] utilization flags to enable or disable. May be 0 or a valid
                                                    ///< combination of ::zes_vf_info_util_exp_flag_t.
    ze_bool_t enable                                ///< [in] Enable utilization telemetry.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementSetVFTelemetryModeExp_t pfnSetVFTelemetryModeExp = [&result] {
        auto pfnSetVFTelemetryModeExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnSetVFTelemetryModeExp;
        if( nullptr == pfnSetVFTelemetryModeExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetVFTelemetryModeExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetVFTelemetryModeExp( hVFhandle, flags, enable );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetVFTelemetryModeExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnSetVFTelemetryModeExp;
    if( nullptr == pfnSetVFTelemetryModeExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetVFTelemetryModeExp( hVFhandle, flags, enable );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set sampling interval to monitor for a particular utilization
///        telemetry associated with Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported.
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
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < flag`
ze_result_t ZE_APICALL
zesVFManagementSetVFTelemetrySamplingIntervalExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    zes_vf_info_util_exp_flags_t flag,              ///< [in] utilization flags to set sampling interval. May be 0 or a valid
                                                    ///< combination of ::zes_vf_info_util_exp_flag_t.
    uint64_t samplingInterval                       ///< [in] Sampling interval value.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementSetVFTelemetrySamplingIntervalExp_t pfnSetVFTelemetrySamplingIntervalExp = [&result] {
        auto pfnSetVFTelemetrySamplingIntervalExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnSetVFTelemetrySamplingIntervalExp;
        if( nullptr == pfnSetVFTelemetrySamplingIntervalExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetVFTelemetrySamplingIntervalExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetVFTelemetrySamplingIntervalExp( hVFhandle, flag, samplingInterval );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetVFTelemetrySamplingIntervalExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnSetVFTelemetrySamplingIntervalExp;
    if( nullptr == pfnSetVFTelemetrySamplingIntervalExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetVFTelemetrySamplingIntervalExp( hVFhandle, flag, samplingInterval );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of virtual function modules
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
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumEnabledVFExp(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_vf_handle_t* phVFhandle                     ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnDeviceEnumEnabledVFExp_t pfnEnumEnabledVFExp = [&result] {
        auto pfnEnumEnabledVFExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnEnumEnabledVFExp;
        if( nullptr == pfnEnumEnabledVFExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnumEnabledVFExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnumEnabledVFExp( hDevice, pCount, phVFhandle );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumEnabledVFExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnEnumEnabledVFExp;
    if( nullptr == pfnEnumEnabledVFExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumEnabledVFExp( hDevice, pCount, phVFhandle );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get virtual function management capabilities
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use
///       ::zesVFManagementGetVFCapabilitiesExp2.
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
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCapability`
ze_result_t ZE_APICALL
zesVFManagementGetVFCapabilitiesExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
    zes_vf_exp_capabilities_t* pCapability          ///< [in,out] Will contain VF capability.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementGetVFCapabilitiesExp_t pfnGetVFCapabilitiesExp = [&result] {
        auto pfnGetVFCapabilitiesExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFCapabilitiesExp;
        if( nullptr == pfnGetVFCapabilitiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFCapabilitiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFCapabilitiesExp( hVFhandle, pCapability );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFCapabilitiesExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFCapabilitiesExp;
    if( nullptr == pfnGetVFCapabilitiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFCapabilitiesExp( hVFhandle, pCapability );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory activity stats for each available memory types associated
///        with Virtual Function (VF)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - If VF is disable/pause/not active, utilization will give zero value.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFMemoryUtilizationExp2(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF memory stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of memory stats available.
                                                    ///<  - if count is greater than the total number of memory stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of memory stats available.
    zes_vf_util_mem_exp2_t* pMemUtil                ///< [in,out][optional][range(0, *pCount)] array of memory group activity counters.
                                                    ///<  - if count is less than the total number of memory stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< memory stats.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementGetVFMemoryUtilizationExp2_t pfnGetVFMemoryUtilizationExp2 = [&result] {
        auto pfnGetVFMemoryUtilizationExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFMemoryUtilizationExp2;
        if( nullptr == pfnGetVFMemoryUtilizationExp2 ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFMemoryUtilizationExp2;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFMemoryUtilizationExp2( hVFhandle, pCount, pMemUtil );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFMemoryUtilizationExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFMemoryUtilizationExp2;
    if( nullptr == pfnGetVFMemoryUtilizationExp2 ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFMemoryUtilizationExp2( hVFhandle, pCount, pMemUtil );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine activity stats for each available engine group associated
///        with Virtual Function (VF)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - If VF is disable/pause/not active, utilization will give zero value.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFEngineUtilizationExp2(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of engine stats available.
                                                    ///<  - if count is greater than the total number of engine stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of engine stats available.
    zes_vf_util_engine_exp2_t* pEngineUtil          ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                    ///<  - if count is less than the total number of engine stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< engine stats.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementGetVFEngineUtilizationExp2_t pfnGetVFEngineUtilizationExp2 = [&result] {
        auto pfnGetVFEngineUtilizationExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFEngineUtilizationExp2;
        if( nullptr == pfnGetVFEngineUtilizationExp2 ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFEngineUtilizationExp2;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFEngineUtilizationExp2( hVFhandle, pCount, pEngineUtil );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFEngineUtilizationExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFEngineUtilizationExp2;
    if( nullptr == pfnGetVFEngineUtilizationExp2 ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFEngineUtilizationExp2( hVFhandle, pCount, pEngineUtil );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get virtual function management capabilities
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
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCapability`
ze_result_t ZE_APICALL
zesVFManagementGetVFCapabilitiesExp2(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
    zes_vf_exp2_capabilities_t* pCapability         ///< [in,out] Will contain VF capability.
    )
{
    #ifdef DYNAMIC_LOAD_LOADER
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zes_pfnVFManagementGetVFCapabilitiesExp2_t pfnGetVFCapabilitiesExp2 = [&result] {
        auto pfnGetVFCapabilitiesExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFCapabilitiesExp2;
        if( nullptr == pfnGetVFCapabilitiesExp2 ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetVFCapabilitiesExp2;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetVFCapabilitiesExp2( hVFhandle, pCapability );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFCapabilitiesExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFCapabilitiesExp2;
    if( nullptr == pfnGetVFCapabilitiesExp2 ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFCapabilitiesExp2( hVFhandle, pCapability );
    #endif
}

} // extern "C"
