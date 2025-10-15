/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_ldrddi_driver_ddi.cpp
 *
 */
#include "ze_loader_internal.h"

namespace loader_driver_ddi
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetApiVersion
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetApiVersion = dditable->Driver->pfnGetApiVersion;
        if( nullptr == pfnGetApiVersion ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetApiVersion( hDriver, version );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Driver->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hDriver, pDriverProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIpcProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetIpcProperties = dditable->Driver->pfnGetIpcProperties;
        if( nullptr == pfnGetIpcProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetIpcProperties( hDriver, pIpcProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionProperties
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetExtensionProperties = dditable->Driver->pfnGetExtensionProperties;
        if( nullptr == pfnGetExtensionProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionFunctionAddress
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_1) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetExtensionFunctionAddress = dditable->Driver->pfnGetExtensionFunctionAddress;
        if( nullptr == pfnGetExtensionFunctionAddress ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetLastErrorDescription
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetLastErrorDescription(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_6) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetLastErrorDescription = dditable->Driver->pfnGetLastErrorDescription;
        if( nullptr == pfnGetLastErrorDescription ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetLastErrorDescription( hDriver, ppString );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetDefaultContext
    __zedlllocal ze_context_handle_t ZE_APICALL
    zeDriverGetDefaultContext(
        ze_driver_handle_t hDriver                      ///< [in] handle of the driver instance
        )
    {
        ze_context_handle_t result {};

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return nullptr;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            return nullptr;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return nullptr;
        }
        auto pfnGetDefaultContext = dditable->Driver->pfnGetDefaultContext;
        if( nullptr == pfnGetDefaultContext ) {
            return nullptr;
        }
        // forward to device-driver
        result = pfnGetDefaultContext( hDriver );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGet = dditable->Device->pfnGet;
        if( nullptr == pfnGet ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGet( hDriver, pCount, phDevices );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetRootDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetRootDevice(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetRootDevice = dditable->Device->pfnGetRootDevice;
        if( nullptr == pfnGetRootDevice ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetRootDevice( hDevice, phRootDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetSubDevices
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetSubDevices = dditable->Device->pfnGetSubDevices;
        if( nullptr == pfnGetSubDevices ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetSubDevices( hDevice, pCount, phSubdevices );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Device->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hDevice, pDeviceProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetComputeProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetComputeProperties = dditable->Device->pfnGetComputeProperties;
        if( nullptr == pfnGetComputeProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetComputeProperties( hDevice, pComputeProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetModuleProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetModuleProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetModuleProperties = dditable->Device->pfnGetModuleProperties;
        if( nullptr == pfnGetModuleProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetModuleProperties( hDevice, pModuleProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCommandQueueGroupProperties
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetCommandQueueGroupProperties = dditable->Device->pfnGetCommandQueueGroupProperties;
        if( nullptr == pfnGetCommandQueueGroupProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetMemoryProperties = dditable->Device->pfnGetMemoryProperties;
        if( nullptr == pfnGetMemoryProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetMemoryAccessProperties = dditable->Device->pfnGetMemoryAccessProperties;
        if( nullptr == pfnGetMemoryAccessProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetCacheProperties = dditable->Device->pfnGetCacheProperties;
        if( nullptr == pfnGetCacheProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetCacheProperties( hDevice, pCount, pCacheProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetImageProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetImageProperties = dditable->Device->pfnGetImageProperties;
        if( nullptr == pfnGetImageProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetImageProperties( hDevice, pImageProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetExternalMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetExternalMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetExternalMemoryProperties = dditable->Device->pfnGetExternalMemoryProperties;
        if( nullptr == pfnGetExternalMemoryProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetP2PProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetP2PProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetP2PProperties = dditable->Device->pfnGetP2PProperties;
        if( nullptr == pfnGetP2PProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceCanAccessPeer
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceCanAccessPeer(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCanAccessPeer = dditable->Device->pfnCanAccessPeer;
        if( nullptr == pfnCanAccessPeer ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCanAccessPeer( hDevice, hPeerDevice, value );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetStatus(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetStatus = dditable->Device->pfnGetStatus;
        if( nullptr == pfnGetStatus ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetStatus( hDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetGlobalTimestamps
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetGlobalTimestamps(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                        ///< Device's global timestamp value.
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_1) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetGlobalTimestamps = dditable->Device->pfnGetGlobalTimestamps;
        if( nullptr == pfnGetGlobalTimestamps ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceSynchronize(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSynchronize = dditable->Device->pfnSynchronize;
        if( nullptr == pfnSynchronize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSynchronize( hDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeContextCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->Context->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hDriver, desc, phContext );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextCreateEx
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_1) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreateEx = dditable->Context->pfnCreateEx;
        if( nullptr == pfnCreateEx ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreateEx( hDriver, desc, numDevices, phDevices, phContext );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeContextDestroy(
        ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->Context->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hContext );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeContextGetStatus(
        ze_context_handle_t hContext                    ///< [in] handle of context object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetStatus = dditable->Context->pfnGetStatus;
        if( nullptr == pfnGetStatus ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetStatus( hContext );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandQueue == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->CommandQueue->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phCommandQueue );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandQueue )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandQueue == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->CommandQueue->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hCommandQueue );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueExecuteCommandLists
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueExecuteCommandLists(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandQueue )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandQueue == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnExecuteCommandLists = dditable->CommandQueue->pfnExecuteCommandLists;
        if( nullptr == pfnExecuteCommandLists ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueSynchronize
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandQueue )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandQueue == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSynchronize = dditable->CommandQueue->pfnSynchronize;
        if( nullptr == pfnSynchronize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSynchronize( hCommandQueue, timeout );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueGetOrdinal
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetOrdinal(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandQueue )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandQueue == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetOrdinal = dditable->CommandQueue->pfnGetOrdinal;
        if( nullptr == pfnGetOrdinal ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetOrdinal( hCommandQueue, pOrdinal );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueGetIndex
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetIndex(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pIndex                                ///< [out] command queue index within the group
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandQueue )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandQueue == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetIndex = dditable->CommandQueue->pfnGetIndex;
        if( nullptr == pfnGetIndex ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetIndex( hCommandQueue, pIndex );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->CommandList->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateImmediate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateImmediate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreateImmediate = dditable->CommandList->pfnCreateImmediate;
        if( nullptr == pfnCreateImmediate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->CommandList->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListClose
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnClose = dditable->CommandList->pfnClose;
        if( nullptr == pfnClose ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnClose( hCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnReset = dditable->CommandList->pfnReset;
        if( nullptr == pfnReset ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnReset( hCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWriteGlobalTimestamp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendWriteGlobalTimestamp = dditable->CommandList->pfnAppendWriteGlobalTimestamp;
        if( nullptr == pfnAppendWriteGlobalTimestamp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_6) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnHostSynchronize = dditable->CommandList->pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnHostSynchronize( hCommandList, timeout );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetDeviceHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetDeviceHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_device_handle_t* phDevice                    ///< [out] handle of the device on which the command list was created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetDeviceHandle = dditable->CommandList->pfnGetDeviceHandle;
        if( nullptr == pfnGetDeviceHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetDeviceHandle( hCommandList, phDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetContextHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetContextHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the command list was created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetContextHandle = dditable->CommandList->pfnGetContextHandle;
        if( nullptr == pfnGetContextHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetContextHandle( hCommandList, phContext );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetOrdinal
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetOrdinal(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal to which command list is submitted
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetOrdinal = dditable->CommandList->pfnGetOrdinal;
        if( nullptr == pfnGetOrdinal ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetOrdinal( hCommandList, pOrdinal );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListImmediateGetIndex
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListImmediateGetIndex(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t* pIndex                                ///< [out] command queue index within the group to which the immediate
                                                        ///< command list is submitted
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandListImmediate )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnImmediateGetIndex = dditable->CommandList->pfnImmediateGetIndex;
        if( nullptr == pfnImmediateGetIndex ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnImmediateGetIndex( hCommandListImmediate, pIndex );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListIsImmediate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListIsImmediate(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_bool_t* pIsImmediate                         ///< [out] Boolean indicating whether the command list is an immediate
                                                        ///< command list (true) or not (false)
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnIsImmediate = dditable->CommandList->pfnIsImmediate;
        if( nullptr == pfnIsImmediate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnIsImmediate( hCommandList, pIsImmediate );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendBarrier = dditable->CommandList->pfnAppendBarrier;
        if( nullptr == pfnAppendBarrier ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryRangesBarrier
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendMemoryRangesBarrier = dditable->CommandList->pfnAppendMemoryRangesBarrier;
        if( nullptr == pfnAppendMemoryRangesBarrier ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextSystemBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeContextSystemBarrier(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSystemBarrier = dditable->Context->pfnSystemBarrier;
        if( nullptr == pfnSystemBarrier ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSystemBarrier( hContext, hDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopy
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendMemoryCopy = dditable->CommandList->pfnAppendMemoryCopy;
        if( nullptr == pfnAppendMemoryCopy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryFill
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendMemoryFill = dditable->CommandList->pfnAppendMemoryFill;
        if( nullptr == pfnAppendMemoryFill ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyRegion
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendMemoryCopyRegion = dditable->CommandList->pfnAppendMemoryCopyRegion;
        if( nullptr == pfnAppendMemoryCopyRegion ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyFromContext
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendMemoryCopyFromContext = dditable->CommandList->pfnAppendMemoryCopyFromContext;
        if( nullptr == pfnAppendMemoryCopyFromContext ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopy
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendImageCopy = dditable->CommandList->pfnAppendImageCopy;
        if( nullptr == pfnAppendImageCopy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyRegion
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendImageCopyRegion = dditable->CommandList->pfnAppendImageCopyRegion;
        if( nullptr == pfnAppendImageCopyRegion ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemory
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendImageCopyToMemory = dditable->CommandList->pfnAppendImageCopyToMemory;
        if( nullptr == pfnAppendImageCopyToMemory ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemory
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendImageCopyFromMemory = dditable->CommandList->pfnAppendImageCopyFromMemory;
        if( nullptr == pfnAppendImageCopyFromMemory ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryPrefetch
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryPrefetch(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendMemoryPrefetch = dditable->CommandList->pfnAppendMemoryPrefetch;
        if( nullptr == pfnAppendMemoryPrefetch ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemAdvise
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemAdvise(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendMemAdvise = dditable->CommandList->pfnAppendMemAdvise;
        if( nullptr == pfnAppendMemAdvise ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCreate
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->EventPool->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEventPool )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->EventPool->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hEventPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeEventCreate(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEventPool )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->Event->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hEventPool, desc, phEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->Event->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEventPool )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetIpcHandle = dditable->EventPool->pfnGetIpcHandle;
        if( nullptr == pfnGetIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetIpcHandle( hEventPool, phIpc );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolPutIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_6) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnPutIpcHandle = dditable->EventPool->pfnPutIpcHandle;
        if( nullptr == pfnPutIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnPutIpcHandle( hContext, hIpc );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolOpenIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event pool handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOpenIpcHandle = dditable->EventPool->pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOpenIpcHandle( hContext, hIpc, phEventPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEventPool )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCloseIpcHandle = dditable->EventPool->pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCloseIpcHandle( hEventPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendSignalEvent = dditable->CommandList->pfnAppendSignalEvent;
        if( nullptr == pfnAppendSignalEvent ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendSignalEvent( hCommandList, hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWaitOnEvents
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                        ///< continuing
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendWaitOnEvents = dditable->CommandList->pfnAppendWaitOnEvents;
        if( nullptr == pfnAppendWaitOnEvents ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSignal
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnHostSignal = dditable->Event->pfnHostSignal;
        if( nullptr == pfnHostSignal ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnHostSignal( hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnHostSynchronize = dditable->Event->pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnHostSynchronize( hEvent, timeout );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnQueryStatus = dditable->Event->pfnQueryStatus;
        if( nullptr == pfnQueryStatus ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnQueryStatus( hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendEventReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendEventReset = dditable->CommandList->pfnAppendEventReset;
        if( nullptr == pfnAppendEventReset ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendEventReset( hCommandList, hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostReset
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnHostReset = dditable->Event->pfnHostReset;
        if( nullptr == pfnHostReset ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnHostReset( hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryKernelTimestamp
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestamp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnQueryKernelTimestamp = dditable->Event->pfnQueryKernelTimestamp;
        if( nullptr == pfnQueryKernelTimestamp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnQueryKernelTimestamp( hEvent, dstptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendQueryKernelTimestamps
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendQueryKernelTimestamps = dditable->CommandList->pfnAppendQueryKernelTimestamps;
        if( nullptr == pfnAppendQueryKernelTimestamps ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetEventPool
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetEventPool(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_pool_handle_t* phEventPool             ///< [out] handle of the event pool for the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetEventPool = dditable->Event->pfnGetEventPool;
        if( nullptr == pfnGetEventPool ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetEventPool( hEvent, phEventPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetSignalScope
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetSignalScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pSignalScope            ///< [out] signal event scope. This is the scope of relevant cache
                                                        ///< hierarchies that are flushed on a signal action before the event is
                                                        ///< triggered. May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetSignalScope = dditable->Event->pfnGetSignalScope;
        if( nullptr == pfnGetSignalScope ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetSignalScope( hEvent, pSignalScope );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetWaitScope
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetWaitScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pWaitScope              ///< [out] wait event scope. This is the scope of relevant cache
                                                        ///< hierarchies invalidated on a wait action after the event is complete.
                                                        ///< May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetWaitScope = dditable->Event->pfnGetWaitScope;
        if( nullptr == pfnGetWaitScope ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetWaitScope( hEvent, pWaitScope );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetContextHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetContextHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the event pool was created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEventPool )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetContextHandle = dditable->EventPool->pfnGetContextHandle;
        if( nullptr == pfnGetContextHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetContextHandle( hEventPool, phContext );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetFlags
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetFlags(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_event_pool_flags_t* pFlags                   ///< [out] creation flags used to create the event pool; may be 0 or a
                                                        ///< valid combination of ::ze_event_pool_flag_t
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEventPool )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventPool == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetFlags = dditable->EventPool->pfnGetFlags;
        if( nullptr == pfnGetFlags ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetFlags( hEventPool, pFlags );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceCreate(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandQueue )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fence == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->Fence->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hCommandQueue, desc, phFence );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFence )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fence == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->Fence->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hFence );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFence )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fence == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnHostSynchronize = dditable->Fence->pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnHostSynchronize( hFence, timeout );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFence )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fence == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnQueryStatus = dditable->Fence->pfnQueryStatus;
        if( nullptr == pfnQueryStatus ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnQueryStatus( hFence );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceReset
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFence )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fence == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnReset = dditable->Fence->pfnReset;
        if( nullptr == pfnReset ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnReset( hFence );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Image == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Image->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hDevice, desc, pImageProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeImageCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Image == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->Image->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phImage );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hImage )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Image == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->Image->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hImage );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocShared
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAllocShared = dditable->Mem->pfnAllocShared;
        if( nullptr == pfnAllocShared ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocDevice
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAllocDevice = dditable->Mem->pfnAllocDevice;
        if( nullptr == pfnAllocDevice ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocHost
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAllocHost = dditable->Mem->pfnAllocHost;
        if( nullptr == pfnAllocHost ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAllocHost( hContext, host_desc, size, alignment, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemFree
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnFree = dditable->Mem->pfnFree;
        if( nullptr == pfnFree ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnFree( hContext, ptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAllocProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAllocProperties(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetAllocProperties = dditable->Mem->pfnGetAllocProperties;
        if( nullptr == pfnGetAllocProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAddressRange
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAddressRange(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetAddressRange = dditable->Mem->pfnGetAddressRange;
        if( nullptr == pfnGetAddressRange ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetAddressRange( hContext, ptr, pBase, pSize );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetIpcHandle = dditable->Mem->pfnGetIpcHandle;
        if( nullptr == pfnGetIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetIpcHandle( hContext, ptr, pIpcHandle );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetIpcHandleFromFileDescriptorExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandleFromFileDescriptorExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        uint64_t handle,                                ///< [in] file descriptor
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_6) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->MemExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetIpcHandleFromFileDescriptorExp = dditable->MemExp->pfnGetIpcHandleFromFileDescriptorExp;
        if( nullptr == pfnGetIpcHandleFromFileDescriptorExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetFileDescriptorFromIpcHandleExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetFileDescriptorFromIpcHandleExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t ipcHandle,                  ///< [in] IPC memory handle
        uint64_t* pHandle                               ///< [out] Returned file descriptor
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_6) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->MemExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetFileDescriptorFromIpcHandleExp = dditable->MemExp->pfnGetFileDescriptorFromIpcHandleExp;
        if( nullptr == pfnGetFileDescriptorFromIpcHandleExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemPutIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_6) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnPutIpcHandle = dditable->Mem->pfnPutIpcHandle;
        if( nullptr == pfnPutIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnPutIpcHandle( hContext, handle );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemOpenIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation.
                                                        ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOpenIpcHandle = dditable->Mem->pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemCloseIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCloseIpcHandle = dditable->Mem->pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCloseIpcHandle( hContext, ptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemSetAtomicAccessAttributeExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemSetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t attr          ///< [in] Atomic access attributes to set for the specified range.
                                                        ///< Must be 0 (default) or a valid combination of ::ze_memory_atomic_attr_exp_flag_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->MemExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetAtomicAccessAttributeExp = dditable->MemExp->pfnSetAtomicAccessAttributeExp;
        if( nullptr == pfnSetAtomicAccessAttributeExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAtomicAccessAttributeExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t* pAttr        ///< [out] Atomic access attributes for the specified range
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->MemExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetAtomicAccessAttributeExp = dditable->MemExp->pfnGetAtomicAccessAttributeExp;
        if( nullptr == pfnGetAtomicAccessAttributeExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->Module->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModule )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->Module->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hModule );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDynamicLink
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDynamicLink(
        uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to
                                                        ///< dynamically link together.
        ze_module_build_log_handle_t* phLinkLog         ///< [out][optional] pointer to handle of dynamic link log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( phModules[ 0 ] )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDynamicLink = dditable->Module->pfnDynamicLink;
        if( nullptr == pfnDynamicLink ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDynamicLink( numModules, phModules, phLinkLog );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModuleBuildLog )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->ModuleBuildLog == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->ModuleBuildLog->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hModuleBuildLog );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogGetString
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogGetString(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModuleBuildLog )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->ModuleBuildLog == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetString = dditable->ModuleBuildLog->pfnGetString;
        if( nullptr == pfnGetString ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetNativeBinary
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetNativeBinary(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModule )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetNativeBinary = dditable->Module->pfnGetNativeBinary;
        if( nullptr == pfnGetNativeBinary ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetGlobalPointer
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pGlobalName,                        ///< [in] name of global variable in module
        size_t* pSize,                                  ///< [in,out][optional] size of global variable
        void** pptr                                     ///< [in,out][optional] device visible pointer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModule )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetGlobalPointer = dditable->Module->pfnGetGlobalPointer;
        if( nullptr == pfnGetGlobalPointer ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetKernelNames
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModule )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetKernelNames = dditable->Module->pfnGetKernelNames;
        if( nullptr == pfnGetKernelNames ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetKernelNames( hModule, pCount, pNames );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetProperties(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModule )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Module->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hModule, pModuleProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelCreate(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModule )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->Kernel->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hModule, desc, phKernel );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->Kernel->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hKernel );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetFunctionPointer
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetFunctionPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hModule )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetFunctionPointer = dditable->Module->pfnGetFunctionPointer;
        if( nullptr == pfnGetFunctionPointer ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGroupSize
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetGroupSize = dditable->Kernel->pfnSetGroupSize;
        if( nullptr == pfnSetGroupSize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestGroupSize
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSuggestGroupSize = dditable->Kernel->pfnSuggestGroupSize;
        if( nullptr == pfnSuggestGroupSize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSuggestMaxCooperativeGroupCount = dditable->Kernel->pfnSuggestMaxCooperativeGroupCount;
        if( nullptr == pfnSuggestMaxCooperativeGroupCount ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetArgumentValue
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetArgumentValue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetArgumentValue = dditable->Kernel->pfnSetArgumentValue;
        if( nullptr == pfnSetArgumentValue ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetIndirectAccess = dditable->Kernel->pfnSetIndirectAccess;
        if( nullptr == pfnSetIndirectAccess ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetIndirectAccess( hKernel, flags );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetIndirectAccess = dditable->Kernel->pfnGetIndirectAccess;
        if( nullptr == pfnGetIndirectAccess ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetIndirectAccess( hKernel, pFlags );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetSourceAttributes
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetSourceAttributes = dditable->Kernel->pfnGetSourceAttributes;
        if( nullptr == pfnGetSourceAttributes ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetSourceAttributes( hKernel, pSize, pString );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetCacheConfig
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                        ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetCacheConfig = dditable->Kernel->pfnSetCacheConfig;
        if( nullptr == pfnSetCacheConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetCacheConfig( hKernel, flags );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Kernel->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hKernel, pKernelProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetName
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetName(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                        ///< bytes.
        char* pName                                     ///< [in,out][optional] char pointer to kernel name.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Kernel == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetName = dditable->Kernel->pfnGetName;
        if( nullptr == pfnGetName ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetName( hKernel, pSize, pName );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernel
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendLaunchKernel = dditable->CommandList->pfnAppendLaunchKernel;
        if( nullptr == pfnAppendLaunchKernel ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelWithParameters
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendLaunchKernelWithParameters = dditable->CommandList->pfnAppendLaunchKernelWithParameters;
        if( nullptr == pfnAppendLaunchKernelWithParameters ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendLaunchKernelWithParameters( hCommandList, hKernel, pGroupCounts, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelWithArguments
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendLaunchKernelWithArguments = dditable->CommandList->pfnAppendLaunchKernelWithArguments;
        if( nullptr == pfnAppendLaunchKernelWithArguments ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendLaunchKernelWithArguments( hCommandList, hKernel, groupCounts, groupSizes, pArguments, pNext, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchCooperativeKernel
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendLaunchCooperativeKernel = dditable->CommandList->pfnAppendLaunchCooperativeKernel;
        if( nullptr == pfnAppendLaunchCooperativeKernel ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelIndirect
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendLaunchKernelIndirect = dditable->CommandList->pfnAppendLaunchKernelIndirect;
        if( nullptr == pfnAppendLaunchKernelIndirect ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchMultipleKernelsIndirect
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendLaunchMultipleKernelsIndirect = dditable->CommandList->pfnAppendLaunchMultipleKernelsIndirect;
        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextMakeMemoryResident
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeMemoryResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnMakeMemoryResident = dditable->Context->pfnMakeMemoryResident;
        if( nullptr == pfnMakeMemoryResident ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnMakeMemoryResident( hContext, hDevice, ptr, size );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextEvictMemory
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictMemory(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEvictMemory = dditable->Context->pfnEvictMemory;
        if( nullptr == pfnEvictMemory ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEvictMemory( hContext, hDevice, ptr, size );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextMakeImageResident
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeImageResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnMakeImageResident = dditable->Context->pfnMakeImageResident;
        if( nullptr == pfnMakeImageResident ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnMakeImageResident( hContext, hDevice, hImage );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextEvictImage
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictImage(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Context == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEvictImage = dditable->Context->pfnEvictImage;
        if( nullptr == pfnEvictImage ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEvictImage( hContext, hDevice, hImage );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Sampler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->Sampler->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phSampler );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hSampler )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Sampler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->Sampler->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hSampler );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemReserve
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemReserve(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in][optional] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VirtualMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnReserve = dditable->VirtualMem->pfnReserve;
        if( nullptr == pfnReserve ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnReserve( hContext, pStart, size, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemFree
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to free.
        size_t size                                     ///< [in] size in bytes to free; must be page aligned.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VirtualMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnFree = dditable->VirtualMem->pfnFree;
        if( nullptr == pfnFree ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnFree( hContext, ptr, size );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemQueryPageSize
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemQueryPageSize(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t size,                                    ///< [in] unaligned allocation size in bytes
        size_t* pagesize                                ///< [out] pointer to page size to use for start address and size
                                                        ///< alignments.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VirtualMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnQueryPageSize = dditable->VirtualMem->pfnQueryPageSize;
        if( nullptr == pfnQueryPageSize ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnQueryPageSize( hContext, hDevice, size, pagesize );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemCreate
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object, can be `nullptr` if creating
                                                        ///< physical host memory.
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->PhysicalMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreate = dditable->PhysicalMem->pfnCreate;
        if( nullptr == pfnCreate ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phPhysicalMemory );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemDestroy(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->PhysicalMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroy = dditable->PhysicalMem->pfnDestroy;
        if( nullptr == pfnDestroy ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroy( hContext, hPhysicalMemory );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemMap
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VirtualMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnMap = dditable->VirtualMem->pfnMap;
        if( nullptr == pfnMap ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemUnmap
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemUnmap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to unmap.
        size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VirtualMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnUnmap = dditable->VirtualMem->pfnUnmap;
        if( nullptr == pfnUnmap ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnUnmap( hContext, ptr, size );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemSetAccessAttribute
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemSetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VirtualMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetAccessAttribute = dditable->VirtualMem->pfnSetAccessAttribute;
        if( nullptr == pfnSetAccessAttribute ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetAccessAttribute( hContext, ptr, size, access );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemGetAccessAttribute
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemGetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t* access,           ///< [out] query result for page access attribute.
        size_t* outSize                                 ///< [out] query result for size of virtual address range, starting at ptr,
                                                        ///< that shares same access attribute.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VirtualMem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetAccessAttribute = dditable->VirtualMem->pfnGetAccessAttribute;
        if( nullptr == pfnGetAccessAttribute ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetAccessAttribute( hContext, ptr, size, access, outSize );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGlobalOffsetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGlobalOffsetExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t offsetX,                               ///< [in] global offset for X dimension to use for this kernel
        uint32_t offsetY,                               ///< [in] global offset for Y dimension to use for this kernel
        uint32_t offsetZ                                ///< [in] global offset for Z dimension to use for this kernel
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_1) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->KernelExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetGlobalOffsetExp = dditable->KernelExp->pfnSetGlobalOffsetExp;
        if( nullptr == pfnSetGlobalOffsetExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetBinaryExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetBinaryExp(
        ze_kernel_handle_t hKernel,                     ///< [in] Kernel handle.
        size_t* pSize,                                  ///< [in,out] pointer to variable with size of GEN ISA binary.
        uint8_t* pKernelBinary                          ///< [in,out] pointer to storage area for GEN ISA binary function.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_11) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->KernelExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetBinaryExp = dditable->KernelExp->pfnGetBinaryExp;
        if( nullptr == pfnGetBinaryExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetBinaryExp( hKernel, pSize, pKernelBinary );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceImportExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceImportExternalSemaphoreExt(
        ze_device_handle_t hDevice,                     ///< [in] The device handle.
        const ze_external_semaphore_ext_desc_t* desc,   ///< [in] The pointer to external semaphore descriptor.
        ze_external_semaphore_ext_handle_t* phSemaphore ///< [out] The handle of the external semaphore imported.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_12) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnImportExternalSemaphoreExt = dditable->Device->pfnImportExternalSemaphoreExt;
        if( nullptr == pfnImportExternalSemaphoreExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnImportExternalSemaphoreExt( hDevice, desc, phSemaphore );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceReleaseExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceReleaseExternalSemaphoreExt(
        ze_external_semaphore_ext_handle_t hSemaphore   ///< [in] The handle of the external semaphore.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hSemaphore )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_12) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnReleaseExternalSemaphoreExt = dditable->Device->pfnReleaseExternalSemaphoreExt;
        if( nullptr == pfnReleaseExternalSemaphoreExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnReleaseExternalSemaphoreExt( hSemaphore );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalExternalSemaphoreExt(
        ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
        uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
        ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in][range(0, numSemaphores)] The vector of external semaphore handles
                                                        ///< to be appended into command list.
        ze_external_semaphore_signal_params_ext_t* signalParams,///< [in] Signal parameters.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_12) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendSignalExternalSemaphoreExt = dditable->CommandList->pfnAppendSignalExternalSemaphoreExt;
        if( nullptr == pfnAppendSignalExternalSemaphoreExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendSignalExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, signalParams, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWaitExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWaitExternalSemaphoreExt(
        ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
        uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
        ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in] [range(0,numSemaphores)] The vector of external semaphore handles
                                                        ///< to append into command list.
        ze_external_semaphore_wait_params_ext_t* waitParams,///< [in] Wait parameters.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_12) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendWaitExternalSemaphoreExt = dditable->CommandList->pfnAppendWaitExternalSemaphoreExt;
        if( nullptr == pfnAppendWaitExternalSemaphoreExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendWaitExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, waitParams, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderCreateExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCreateExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_ext_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_ext_handle_t* phBuilder         ///< [out] handle of builder object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilder == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreateExt = dditable->RTASBuilder->pfnCreateExt;
        if( nullptr == pfnCreateExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreateExt( hDriver, pDescriptor, phBuilder );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderGetBuildPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderGetBuildPropertiesExt(
        ze_rtas_builder_ext_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_ext_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_ext_properties_t* pProperties   ///< [in,out] query result for builder properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hBuilder )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilder == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetBuildPropertiesExt = dditable->RTASBuilder->pfnGetBuildPropertiesExt;
        if( nullptr == pfnGetBuildPropertiesExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetBuildPropertiesExt( hBuilder, pBuildOpDescriptor, pProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverRTASFormatCompatibilityCheckExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverRTASFormatCompatibilityCheckExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_ext_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_ext_t rtasFormatB                ///< [in] operand B
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnRTASFormatCompatibilityCheckExt = dditable->Driver->pfnRTASFormatCompatibilityCheckExt;
        if( nullptr == pfnRTASFormatCompatibilityCheckExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnRTASFormatCompatibilityCheckExt( hDriver, rtasFormatA, rtasFormatB );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderBuildExt
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hBuilder )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilder == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnBuildExt = dditable->RTASBuilder->pfnBuildExt;
        if( nullptr == pfnBuildExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnBuildExt( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderCommandListAppendCopyExt
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilder == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCommandListAppendCopyExt = dditable->RTASBuilder->pfnCommandListAppendCopyExt;
        if( nullptr == pfnCommandListAppendCopyExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCommandListAppendCopyExt( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderDestroyExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExt(
        ze_rtas_builder_ext_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hBuilder )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilder == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroyExt = dditable->RTASBuilder->pfnDestroyExt;
        if( nullptr == pfnDestroyExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroyExt( hBuilder );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationCreateExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_ext_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperation == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreateExt = dditable->RTASParallelOperation->pfnCreateExt;
        if( nullptr == pfnCreateExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreateExt( hDriver, phParallelOperation );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationGetPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_ext_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hParallelOperation )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperation == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetPropertiesExt = dditable->RTASParallelOperation->pfnGetPropertiesExt;
        if( nullptr == pfnGetPropertiesExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetPropertiesExt( hParallelOperation, pProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationJoinExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hParallelOperation )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperation == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnJoinExt = dditable->RTASParallelOperation->pfnJoinExt;
        if( nullptr == pfnJoinExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnJoinExt( hParallelOperation );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationDestroyExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hParallelOperation )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperation == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroyExt = dditable->RTASParallelOperation->pfnDestroyExt;
        if( nullptr == pfnDestroyExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroyExt( hParallelOperation );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetVectorWidthPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_13) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVectorWidthPropertiesExt = dditable->Device->pfnGetVectorWidthPropertiesExt;
        if( nullptr == pfnGetVectorWidthPropertiesExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVectorWidthPropertiesExt( hDevice, pCount, pVectorWidthProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetAllocationPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->KernelExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetAllocationPropertiesExp = dditable->KernelExp->pfnGetAllocationPropertiesExp;
        if( nullptr == pfnGetAllocationPropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetAllocationPropertiesExp( hKernel, pCount, pAllocationProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceReserveCacheExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceReserveCacheExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t cacheLevel,                              ///< [in] cache level where application want to reserve. If zero, then the
                                                        ///< driver shall default to last level of cache and attempt to reserve in
                                                        ///< that cache.
        size_t cacheReservationSize                     ///< [in] value for reserving size, in bytes. If zero, then the driver
                                                        ///< shall remove prior reservation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_2) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnReserveCacheExt = dditable->Device->pfnReserveCacheExt;
        if( nullptr == pfnReserveCacheExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSetCacheAdviceExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceSetCacheAdviceExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        void* ptr,                                      ///< [in] memory pointer to query
        size_t regionSize,                              ///< [in] region size, in pages
        ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_2) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetCacheAdviceExt = dditable->Device->pfnSetCacheAdviceExt;
        if( nullptr == pfnSetCacheAdviceExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryTimestampsExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_2) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->EventExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnQueryTimestampsExp = dditable->EventExp->pfnQueryTimestampsExp;
        if( nullptr == pfnQueryTimestampsExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetMemoryPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetMemoryPropertiesExp(
        ze_image_handle_t hImage,                       ///< [in] handle of image object
        ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hImage )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_2) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->ImageExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetMemoryPropertiesExp = dditable->ImageExp->pfnGetMemoryPropertiesExp;
        if( nullptr == pfnGetMemoryPropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetMemoryPropertiesExp( hImage, pMemoryProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageViewCreateExt
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Image == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnViewCreateExt = dditable->Image->pfnViewCreateExt;
        if( nullptr == pfnViewCreateExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageViewCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_2) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->ImageExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnViewCreateExp = dditable->ImageExp->pfnViewCreateExp;
        if( nullptr == pfnViewCreateExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSchedulingHintExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSchedulingHintExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hKernel )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_2) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->KernelExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSchedulingHintExp = dditable->KernelExp->pfnSchedulingHintExp;
        if( nullptr == pfnSchedulingHintExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSchedulingHintExp( hKernel, pHint );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDevicePciGetPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDevicePciGetPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
        ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_3) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnPciGetPropertiesExt = dditable->Device->pfnPciGetPropertiesExt;
        if( nullptr == pfnPciGetPropertiesExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnPciGetPropertiesExt( hDevice, pPciProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemoryExt
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_3) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendImageCopyToMemoryExt = dditable->CommandList->pfnAppendImageCopyToMemoryExt;
        if( nullptr == pfnAppendImageCopyToMemoryExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemoryExt
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_3) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandList == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnAppendImageCopyFromMemoryExt = dditable->CommandList->pfnAppendImageCopyFromMemoryExt;
        if( nullptr == pfnAppendImageCopyFromMemoryExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetAllocPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetAllocPropertiesExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_image_handle_t hImage,                       ///< [in] handle of image object to query
        ze_image_allocation_ext_properties_t* pImageAllocProperties ///< [in,out] query result for image allocation properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_3) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Image == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetAllocPropertiesExt = dditable->Image->pfnGetAllocPropertiesExt;
        if( nullptr == pfnGetAllocPropertiesExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleInspectLinkageExt
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleInspectLinkageExt(
        ze_linkage_inspection_ext_desc_t* pInspectDesc, ///< [in] pointer to linkage inspection descriptor structure.
        uint32_t numModules,                            ///< [in] number of modules to be inspected pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to be
                                                        ///< inspected for import dependencies.
        ze_module_build_log_handle_t* phLog             ///< [out] pointer to handle of linkage inspection log. Log object will
                                                        ///< contain separate lists of imports, un-resolvable imports, and exports.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( phModules[ 0 ] )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_3) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Module == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnInspectLinkageExt = dditable->Module->pfnInspectLinkageExt;
        if( nullptr == pfnInspectLinkageExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemFreeExt
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFreeExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_3) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnFreeExt = dditable->Mem->pfnFreeExt;
        if( nullptr == pfnFreeExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnFreeExt( hContext, pMemFreeDesc, ptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricVertexExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetExp = dditable->FabricVertexExp->pfnGetExp;
        if( nullptr == pfnGetExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetExp( hDriver, pCount, phVertices );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetSubVerticesExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVertex )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricVertexExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetSubVerticesExp = dditable->FabricVertexExp->pfnGetSubVerticesExp;
        if( nullptr == pfnGetSubVerticesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetPropertiesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVertex )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricVertexExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetPropertiesExp = dditable->FabricVertexExp->pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetPropertiesExp( hVertex, pVertexProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetDeviceExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetDeviceExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVertex )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricVertexExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetDeviceExp = dditable->FabricVertexExp->pfnGetDeviceExp;
        if( nullptr == pfnGetDeviceExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetDeviceExp( hVertex, phDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetFabricVertexExp
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetFabricVertexExp(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->DeviceExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetFabricVertexExp = dditable->DeviceExp->pfnGetFabricVertexExp;
        if( nullptr == pfnGetFabricVertexExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetFabricVertexExp( hDevice, phVertex );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVertexA )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricEdgeExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetExp = dditable->FabricEdgeExp->pfnGetExp;
        if( nullptr == pfnGetExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetExp( hVertexA, hVertexB, pCount, phEdges );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetVerticesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetVerticesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge instance
        ze_fabric_vertex_handle_t* phVertexA,           ///< [out] fabric vertex connected to one end of the given fabric edge.
        ze_fabric_vertex_handle_t* phVertexB            ///< [out] fabric vertex connected to other end of the given fabric edge.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEdge )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricEdgeExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVerticesExp = dditable->FabricEdgeExp->pfnGetVerticesExp;
        if( nullptr == pfnGetVerticesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVerticesExp( hEdge, phVertexA, phVertexB );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetPropertiesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
        ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEdge )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricEdgeExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetPropertiesExp = dditable->FabricEdgeExp->pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetPropertiesExp( hEdge, pEdgeProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryKernelTimestampsExt
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEvent )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_6) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Event == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnQueryKernelTimestampsExt = dditable->Event->pfnQueryKernelTimestampsExt;
        if( nullptr == pfnQueryKernelTimestampsExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilderExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreateExp = dditable->RTASBuilderExp->pfnCreateExp;
        if( nullptr == pfnCreateExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreateExp( hDriver, pDescriptor, phBuilder );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderGetBuildPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderGetBuildPropertiesExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hBuilder )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilderExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetBuildPropertiesExp = dditable->RTASBuilderExp->pfnGetBuildPropertiesExp;
        if( nullptr == pfnGetBuildPropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverRTASFormatCompatibilityCheckExp
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverRTASFormatCompatibilityCheckExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_exp_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_exp_t rtasFormatB                ///< [in] operand B
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->DriverExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnRTASFormatCompatibilityCheckExp = dditable->DriverExp->pfnRTASFormatCompatibilityCheckExp;
        if( nullptr == pfnRTASFormatCompatibilityCheckExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderBuildExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hBuilder )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilderExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnBuildExp = dditable->RTASBuilderExp->pfnBuildExp;
        if( nullptr == pfnBuildExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExp(
        ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hBuilder )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASBuilderExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroyExp = dditable->RTASBuilderExp->pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroyExp( hBuilder );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperationExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreateExp = dditable->RTASParallelOperationExp->pfnCreateExp;
        if( nullptr == pfnCreateExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreateExp( hDriver, phParallelOperation );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hParallelOperation )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperationExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetPropertiesExp = dditable->RTASParallelOperationExp->pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetPropertiesExp( hParallelOperation, pProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationJoinExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hParallelOperation )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperationExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnJoinExp = dditable->RTASParallelOperationExp->pfnJoinExp;
        if( nullptr == pfnJoinExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnJoinExp( hParallelOperation );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hParallelOperation )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RTASParallelOperationExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnDestroyExp = dditable->RTASParallelOperationExp->pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnDestroyExp( hParallelOperation );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetPitchFor2dImage
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetPitchFor2dImage(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        size_t imageWidth,                              ///< [in] imageWidth
        size_t imageHeight,                             ///< [in] imageHeight
        unsigned int elementSizeInBytes,                ///< [in] Element size in bytes
        size_t * rowPitch                               ///< [out] rowPitch
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hContext )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Mem == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetPitchFor2dImage = dditable->Mem->pfnGetPitchFor2dImage;
        if( nullptr == pfnGetPitchFor2dImage ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetPitchFor2dImage( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetDeviceOffsetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetDeviceOffsetExp(
        ze_image_handle_t hImage,                       ///< [in] handle of the image
        uint64_t* pDeviceOffset                         ///< [out] bindless device offset for image
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hImage )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->ImageExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetDeviceOffsetExp = dditable->ImageExp->pfnGetDeviceOffsetExp;
        if( nullptr == pfnGetDeviceOffsetExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetDeviceOffsetExp( hImage, pDeviceOffset );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateCloneExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateCloneExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle to source command list (the command list to clone)
        ze_command_list_handle_t* phClonedCommandList   ///< [out] pointer to handle of the cloned command list
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnCreateCloneExp = dditable->CommandListExp->pfnCreateCloneExp;
        if( nullptr == pfnCreateCloneExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnCreateCloneExp( hCommandList, phClonedCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListImmediateAppendCommandListsExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandListImmediate )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnImmediateAppendCommandListsExp = dditable->CommandListExp->pfnImmediateAppendCommandListsExp;
        if( nullptr == pfnImmediateAppendCommandListsExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnImmediateAppendCommandListsExp( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetNextCommandIdExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetNextCommandIdExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_command_id_exp_desc_t* desc,   ///< [in] pointer to mutable command identifier descriptor
        uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetNextCommandIdExp = dditable->CommandListExp->pfnGetNextCommandIdExp;
        if( nullptr == pfnGetNextCommandIdExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetNextCommandIdExp( hCommandList, desc, pCommandId );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetNextCommandIdWithKernelsExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_10) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetNextCommandIdWithKernelsExp = dditable->CommandListExp->pfnGetNextCommandIdWithKernelsExp;
        if( nullptr == pfnGetNextCommandIdWithKernelsExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetNextCommandIdWithKernelsExp( hCommandList, desc, numKernels, phKernels, pCommandId );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_commands_exp_desc_t* desc      ///< [in] pointer to mutable commands descriptor; multiple descriptors may
                                                        ///< be chained via `pNext` member
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnUpdateMutableCommandsExp = dditable->CommandListExp->pfnUpdateMutableCommandsExp;
        if( nullptr == pfnUpdateMutableCommandsExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnUpdateMutableCommandsExp( hCommandList, desc );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandSignalEventExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandSignalEventExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        ze_event_handle_t hSignalEvent                  ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnUpdateMutableCommandSignalEventExp = dditable->CommandListExp->pfnUpdateMutableCommandSignalEventExp;
        if( nullptr == pfnUpdateMutableCommandSignalEventExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnUpdateMutableCommandSignalEventExp( hCommandList, commandId, hSignalEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandWaitEventsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandWaitEventsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        uint32_t numWaitEvents,                         ///< [in][optional] the number of wait events
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnUpdateMutableCommandWaitEventsExp = dditable->CommandListExp->pfnUpdateMutableCommandWaitEventsExp;
        if( nullptr == pfnUpdateMutableCommandWaitEventsExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnUpdateMutableCommandWaitEventsExp( hCommandList, commandId, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandKernelsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandKernelsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] the number of kernels to update
        uint64_t* pCommandId,                           ///< [in][range(0, numKernels)] command identifier
        ze_kernel_handle_t* phKernels                   ///< [in][range(0, numKernels)] handle of the kernel for a command
                                                        ///< identifier to switch to
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hCommandList )->pCore;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_10) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->CommandListExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnUpdateMutableCommandKernelsExp = dditable->CommandListExp->pfnUpdateMutableCommandKernelsExp;
        if( nullptr == pfnUpdateMutableCommandKernelsExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnUpdateMutableCommandKernelsExp( hCommandList, numKernels, pCommandId, phKernels );
        return result;
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief function for removing the ddi driver tables for ze
    __zedlllocal void ZE_APICALL
    zeDestroyDDiDriverTables(ze_dditable_driver_t* pDdiTable)
    {
        // Delete ddi tables
        delete pDdiTable->Global;
        delete pDdiTable->RTASBuilder;
        delete pDdiTable->RTASBuilderExp;
        delete pDdiTable->RTASParallelOperation;
        delete pDdiTable->RTASParallelOperationExp;
        delete pDdiTable->Driver;
        delete pDdiTable->DriverExp;
        delete pDdiTable->Device;
        delete pDdiTable->DeviceExp;
        delete pDdiTable->Context;
        delete pDdiTable->CommandQueue;
        delete pDdiTable->CommandList;
        delete pDdiTable->CommandListExp;
        delete pDdiTable->Event;
        delete pDdiTable->EventExp;
        delete pDdiTable->EventPool;
        delete pDdiTable->Fence;
        delete pDdiTable->Image;
        delete pDdiTable->ImageExp;
        delete pDdiTable->Kernel;
        delete pDdiTable->KernelExp;
        delete pDdiTable->Mem;
        delete pDdiTable->MemExp;
        delete pDdiTable->Module;
        delete pDdiTable->ModuleBuildLog;
        delete pDdiTable->PhysicalMem;
        delete pDdiTable->Sampler;
        delete pDdiTable->VirtualMem;
        delete pDdiTable->FabricEdgeExp;
        delete pDdiTable->FabricVertexExp;
        delete pDdiTable;
    }

} // namespace loader_driver_ddi