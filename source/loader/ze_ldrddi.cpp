/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_ldrddi.cpp
 *
 */
#include "ze_loader_internal.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    ze_driver_factory_t                 ze_driver_factory;
    ze_device_factory_t                 ze_device_factory;
    ze_context_factory_t                ze_context_factory;
    ze_command_queue_factory_t          ze_command_queue_factory;
    ze_command_list_factory_t           ze_command_list_factory;
    ze_fence_factory_t                  ze_fence_factory;
    ze_event_pool_factory_t             ze_event_pool_factory;
    ze_event_factory_t                  ze_event_factory;
    ze_image_factory_t                  ze_image_factory;
    ze_module_factory_t                 ze_module_factory;
    ze_module_build_log_factory_t       ze_module_build_log_factory;
    ze_kernel_factory_t                 ze_kernel_factory;
    ze_sampler_factory_t                ze_sampler_factory;
    ze_physical_mem_factory_t           ze_physical_mem_factory;
    ze_fabric_vertex_factory_t          ze_fabric_vertex_factory;
    ze_fabric_edge_factory_t            ze_fabric_edge_factory;
    ze_rtas_builder_exp_factory_t       ze_rtas_builder_exp_factory;
    ze_rtas_parallel_operation_exp_factory_t    ze_rtas_parallel_operation_exp_factory;
    ///////////////////////////////////////////////////////////////////////////////
    std::unordered_map<ze_image_object_t *, ze_image_handle_t>            image_handle_map;
    std::unordered_map<ze_sampler_object_t *, ze_sampler_handle_t>        sampler_handle_map;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    __zedlllocal ze_result_t ZE_APICALL
    zeInit(
        ze_init_flags_t flags                           ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        bool atLeastOneDriverValid = false;
        for( auto& drv : context->drivers )
        {
            if(drv.initStatus != ZE_RESULT_SUCCESS)
                continue;
            drv.initStatus = drv.dditable.ze.Global.pfnInit( flags );
            if(drv.initStatus == ZE_RESULT_SUCCESS)
                atLeastOneDriverValid = true;
        }

        if(!atLeastOneDriverValid)
            result=ZE_RESULT_ERROR_UNINITIALIZED;

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGet
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        uint32_t total_driver_handle_count = 0;

        for( auto& drv : context->drivers )
        {
            if(drv.initStatus != ZE_RESULT_SUCCESS)
                continue;

            if( ( 0 < *pCount ) && ( *pCount == total_driver_handle_count))
                break;

            uint32_t library_driver_handle_count = 0;

            result = drv.dditable.ze.Driver.pfnGet( &library_driver_handle_count, nullptr );
            if( ZE_RESULT_SUCCESS != result ) break;

            if( nullptr != phDrivers && *pCount !=0)
            {
                if( total_driver_handle_count + library_driver_handle_count > *pCount) {
                    library_driver_handle_count = *pCount - total_driver_handle_count;
                }
                result = drv.dditable.ze.Driver.pfnGet( &library_driver_handle_count, &phDrivers[ total_driver_handle_count ] );
                if( ZE_RESULT_SUCCESS != result ) break;

                try
                {
                    for( uint32_t i = 0; i < library_driver_handle_count; ++i ) {
                        uint32_t driver_index = total_driver_handle_count + i;
                        phDrivers[ driver_index ] = reinterpret_cast<ze_driver_handle_t>(
                            ze_driver_factory.getInstance( phDrivers[ driver_index ], &drv.dditable ) );
                    }
                }
                catch( std::bad_alloc& )
                {
                    result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
                }
            }

            total_driver_handle_count += library_driver_handle_count;
        }

        if( ZE_RESULT_SUCCESS == result )
            *pCount = total_driver_handle_count;

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetApiVersion
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetApiVersion = dditable->ze.Driver.pfnGetApiVersion;
        if( nullptr == pfnGetApiVersion )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetProperties = dditable->ze.Driver.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetIpcProperties = dditable->ze.Driver.pfnGetIpcProperties;
        if( nullptr == pfnGetIpcProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetExtensionProperties = dditable->ze.Driver.pfnGetExtensionProperties;
        if( nullptr == pfnGetExtensionProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetExtensionFunctionAddress = dditable->ze.Driver.pfnGetExtensionFunctionAddress;
        if( nullptr == pfnGetExtensionFunctionAddress )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetLastErrorDescription = dditable->ze.Driver.pfnGetLastErrorDescription;
        if( nullptr == pfnGetLastErrorDescription )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetLastErrorDescription( hDriver, ppString );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGet = dditable->ze.Device.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGet( hDriver, pCount, phDevices );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDevices ) && ( i < *pCount ); ++i )
                phDevices[ i ] = reinterpret_cast<ze_device_handle_t>(
                    ze_device_factory.getInstance( phDevices[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetRootDevice = dditable->ze.Device.pfnGetRootDevice;
        if( nullptr == pfnGetRootDevice )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetRootDevice( hDevice, phRootDevice );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phRootDevice = reinterpret_cast<ze_device_handle_t>(
                ze_device_factory.getInstance( *phRootDevice, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetSubDevices = dditable->ze.Device.pfnGetSubDevices;
        if( nullptr == pfnGetSubDevices )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetSubDevices( hDevice, pCount, phSubdevices );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phSubdevices ) && ( i < *pCount ); ++i )
                phSubdevices[ i ] = reinterpret_cast<ze_device_handle_t>(
                    ze_device_factory.getInstance( phSubdevices[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetProperties = dditable->ze.Device.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetComputeProperties = dditable->ze.Device.pfnGetComputeProperties;
        if( nullptr == pfnGetComputeProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetModuleProperties = dditable->ze.Device.pfnGetModuleProperties;
        if( nullptr == pfnGetModuleProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetCommandQueueGroupProperties = dditable->ze.Device.pfnGetCommandQueueGroupProperties;
        if( nullptr == pfnGetCommandQueueGroupProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetMemoryProperties = dditable->ze.Device.pfnGetMemoryProperties;
        if( nullptr == pfnGetMemoryProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetMemoryAccessProperties = dditable->ze.Device.pfnGetMemoryAccessProperties;
        if( nullptr == pfnGetMemoryAccessProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetCacheProperties = dditable->ze.Device.pfnGetCacheProperties;
        if( nullptr == pfnGetCacheProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetImageProperties = dditable->ze.Device.pfnGetImageProperties;
        if( nullptr == pfnGetImageProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetExternalMemoryProperties = dditable->ze.Device.pfnGetExternalMemoryProperties;
        if( nullptr == pfnGetExternalMemoryProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetP2PProperties = dditable->ze.Device.pfnGetP2PProperties;
        if( nullptr == pfnGetP2PProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hPeerDevice = reinterpret_cast<ze_device_object_t*>( hPeerDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCanAccessPeer = dditable->ze.Device.pfnCanAccessPeer;
        if( nullptr == pfnCanAccessPeer )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hPeerDevice = reinterpret_cast<ze_device_object_t*>( hPeerDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetStatus = dditable->ze.Device.pfnGetStatus;
        if( nullptr == pfnGetStatus )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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
                                                        ///< Device's global timestamp value
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetGlobalTimestamps = dditable->ze.Device.pfnGetGlobalTimestamps;
        if( nullptr == pfnGetGlobalTimestamps )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnCreate = dditable->ze.Context.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnCreate( hDriver, desc, phContext );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phContext = reinterpret_cast<ze_context_handle_t>(
                ze_context_factory.getInstance( *phContext, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnCreateEx = dditable->ze.Context.pfnCreateEx;
        if( nullptr == pfnCreateEx )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handles to driver handles
        auto phDevicesLocal = new ze_device_handle_t [numDevices];
        for( size_t i = 0; ( nullptr != phDevices ) && ( i < numDevices ); ++i )
            phDevicesLocal[ i ] = reinterpret_cast<ze_device_object_t*>( phDevices[ i ] )->handle;

        // forward to device-driver
        result = pfnCreateEx( hDriver, desc, numDevices, phDevicesLocal, phContext );
        delete []phDevicesLocal;

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phContext = reinterpret_cast<ze_context_handle_t>(
                ze_context_factory.getInstance( *phContext, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnDestroy = dditable->ze.Context.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // forward to device-driver
        result = pfnDestroy( hContext );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_context_factory.release( hContext );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetStatus = dditable->ze.Context.pfnGetStatus;
        if( nullptr == pfnGetStatus )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->ze.CommandQueue.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phCommandQueue );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phCommandQueue = reinterpret_cast<ze_command_queue_handle_t>(
                ze_command_queue_factory.getInstance( *phCommandQueue, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnDestroy = dditable->ze.CommandQueue.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandQueue );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_command_queue_factory.release( hCommandQueue );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnExecuteCommandLists = dditable->ze.CommandQueue.pfnExecuteCommandLists;
        if( nullptr == pfnExecuteCommandLists )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // convert loader handles to driver handles
        auto phCommandListsLocal = new ze_command_list_handle_t [numCommandLists];
        for( size_t i = 0; ( nullptr != phCommandLists ) && ( i < numCommandLists ); ++i )
            phCommandListsLocal[ i ] = reinterpret_cast<ze_command_list_object_t*>( phCommandLists[ i ] )->handle;

        // convert loader handle to driver handle
        hFence = ( hFence ) ? reinterpret_cast<ze_fence_object_t*>( hFence )->handle : nullptr;

        // forward to device-driver
        result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandListsLocal, hFence );
        delete []phCommandListsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnSynchronize = dditable->ze.CommandQueue.pfnSynchronize;
        if( nullptr == pfnSynchronize )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnSynchronize( hCommandQueue, timeout );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->ze.CommandList.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phCommandList );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phCommandList = reinterpret_cast<ze_command_list_handle_t>(
                ze_command_list_factory.getInstance( *phCommandList, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreateImmediate = dditable->ze.CommandList.pfnCreateImmediate;
        if( nullptr == pfnCreateImmediate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phCommandList = reinterpret_cast<ze_command_list_handle_t>(
                ze_command_list_factory.getInstance( *phCommandList, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnDestroy = dditable->ze.CommandList.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandList );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_command_list_factory.release( hCommandList );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnClose = dditable->ze.CommandList.pfnClose;
        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnReset = dditable->ze.CommandList.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendWriteGlobalTimestamp = dditable->ze.CommandList.pfnAppendWriteGlobalTimestamp;
        if( nullptr == pfnAppendWriteGlobalTimestamp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnHostSynchronize = dditable->ze.CommandList.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnHostSynchronize( hCommandList, timeout );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendBarrier = dditable->ze.CommandList.pfnAppendBarrier;
        if( nullptr == pfnAppendBarrier )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryRangesBarrier = dditable->ze.CommandList.pfnAppendMemoryRangesBarrier;
        if( nullptr == pfnAppendMemoryRangesBarrier )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnSystemBarrier = dditable->ze.Context.pfnSystemBarrier;
        if( nullptr == pfnSystemBarrier )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryCopy = dditable->ze.CommandList.pfnAppendMemoryCopy;
        if( nullptr == pfnAppendMemoryCopy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryFill = dditable->ze.CommandList.pfnAppendMemoryFill;
        if( nullptr == pfnAppendMemoryFill )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryCopyRegion = dditable->ze.CommandList.pfnAppendMemoryCopyRegion;
        if( nullptr == pfnAppendMemoryCopyRegion )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryCopyFromContext = dditable->ze.CommandList.pfnAppendMemoryCopyFromContext;
        if( nullptr == pfnAppendMemoryCopyFromContext )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hContextSrc = reinterpret_cast<ze_context_object_t*>( hContextSrc )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopy = dditable->ze.CommandList.pfnAppendImageCopy;
        if( nullptr == pfnAppendImageCopy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<ze_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<ze_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyRegion = dditable->ze.CommandList.pfnAppendImageCopyRegion;
        if( nullptr == pfnAppendImageCopyRegion )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<ze_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<ze_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyToMemory = dditable->ze.CommandList.pfnAppendImageCopyToMemory;
        if( nullptr == pfnAppendImageCopyToMemory )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<ze_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyFromMemory = dditable->ze.CommandList.pfnAppendImageCopyFromMemory;
        if( nullptr == pfnAppendImageCopyFromMemory )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<ze_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryPrefetch = dditable->ze.CommandList.pfnAppendMemoryPrefetch;
        if( nullptr == pfnAppendMemoryPrefetch )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemAdvise = dditable->ze.CommandList.pfnAppendMemAdvise;
        if( nullptr == pfnAppendMemAdvise )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->ze.EventPool.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handles to driver handles
        auto phDevicesLocal = new ze_device_handle_t [numDevices];
        for( size_t i = 0; ( nullptr != phDevices ) && ( i < numDevices ); ++i )
            phDevicesLocal[ i ] = reinterpret_cast<ze_device_object_t*>( phDevices[ i ] )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, desc, numDevices, phDevicesLocal, phEventPool );
        delete []phDevicesLocal;

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phEventPool = reinterpret_cast<ze_event_pool_handle_t>(
                ze_event_pool_factory.getInstance( *phEventPool, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnDestroy = dditable->ze.EventPool.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnDestroy( hEventPool );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_event_pool_factory.release( hEventPool );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnCreate = dditable->ze.Event.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnCreate( hEventPool, desc, phEvent );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phEvent = reinterpret_cast<ze_event_handle_t>(
                ze_event_factory.getInstance( *phEvent, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnDestroy = dditable->ze.Event.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnDestroy( hEvent );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_event_factory.release( hEvent );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnGetIpcHandle = dditable->ze.EventPool.pfnGetIpcHandle;
        if( nullptr == pfnGetIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnPutIpcHandle = dditable->ze.EventPool.pfnPutIpcHandle;
        if( nullptr == pfnPutIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnOpenIpcHandle = dditable->ze.EventPool.pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // forward to device-driver
        result = pfnOpenIpcHandle( hContext, hIpc, phEventPool );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phEventPool = reinterpret_cast<ze_event_pool_handle_t>(
                ze_event_pool_factory.getInstance( *phEventPool, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnCloseIpcHandle = dditable->ze.EventPool.pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnCloseIpcHandle( hEventPool );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_event_pool_factory.release( hEventPool );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendSignalEvent = dditable->ze.CommandList.pfnAppendSignalEvent;
        if( nullptr == pfnAppendSignalEvent )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendWaitOnEvents = dditable->ze.CommandList.pfnAppendWaitOnEvents;
        if( nullptr == pfnAppendWaitOnEvents )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handles to driver handles
        auto phEventsLocal = new ze_event_handle_t [numEvents];
        for( size_t i = 0; ( nullptr != phEvents ) && ( i < numEvents ); ++i )
            phEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEventsLocal );
        delete []phEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnHostSignal = dditable->ze.Event.pfnHostSignal;
        if( nullptr == pfnHostSignal )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnHostSynchronize = dditable->ze.Event.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnQueryStatus = dditable->ze.Event.pfnQueryStatus;
        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendEventReset = dditable->ze.CommandList.pfnAppendEventReset;
        if( nullptr == pfnAppendEventReset )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnHostReset = dditable->ze.Event.pfnHostReset;
        if( nullptr == pfnHostReset )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnQueryKernelTimestamp = dditable->ze.Event.pfnQueryKernelTimestamp;
        if( nullptr == pfnQueryKernelTimestamp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendQueryKernelTimestamps = dditable->ze.CommandList.pfnAppendQueryKernelTimestamps;
        if( nullptr == pfnAppendQueryKernelTimestamps )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handles to driver handles
        auto phEventsLocal = new ze_event_handle_t [numEvents];
        for( size_t i = 0; ( nullptr != phEvents ) && ( i < numEvents ); ++i )
            phEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phEvents[ i ] )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEventsLocal, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phEventsLocal;
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnCreate = dditable->ze.Fence.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnCreate( hCommandQueue, desc, phFence );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phFence = reinterpret_cast<ze_fence_handle_t>(
                ze_fence_factory.getInstance( *phFence, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnDestroy = dditable->ze.Fence.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnDestroy( hFence );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_fence_factory.release( hFence );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnHostSynchronize = dditable->ze.Fence.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnQueryStatus = dditable->ze.Fence.pfnQueryStatus;
        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnReset = dditable->ze.Fence.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetProperties = dditable->ze.Image.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->ze.Image.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phImage );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            ze_image_handle_t internalHandlePtr = *phImage;
            *phImage = reinterpret_cast<ze_image_handle_t>(
                ze_image_factory.getInstance( *phImage, dditable ) );
            // convert loader handle to driver handle and store in map
            image_handle_map.insert({ze_image_factory.getInstance( internalHandlePtr, dditable ), internalHandlePtr});
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_image_object_t*>( hImage )->dditable;
        auto pfnDestroy = dditable->ze.Image.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // remove the handle from the kernel arugment map
        image_handle_map.erase(reinterpret_cast<ze_image_object_t*>(hImage));
        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnDestroy( hImage );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_image_factory.release( hImage );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnAllocShared = dditable->ze.Mem.pfnAllocShared;
        if( nullptr == pfnAllocShared )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = ( hDevice ) ? reinterpret_cast<ze_device_object_t*>( hDevice )->handle : nullptr;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnAllocDevice = dditable->ze.Mem.pfnAllocDevice;
        if( nullptr == pfnAllocDevice )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnAllocHost = dditable->ze.Mem.pfnAllocHost;
        if( nullptr == pfnAllocHost )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnFree = dditable->ze.Mem.pfnFree;
        if( nullptr == pfnFree )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetAllocProperties = dditable->ze.Mem.pfnGetAllocProperties;
        if( nullptr == pfnGetAllocProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // forward to device-driver
        result = pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            if( nullptr != phDevice )
                *phDevice = reinterpret_cast<ze_device_handle_t>(
                    ze_device_factory.getInstance( *phDevice, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetAddressRange = dditable->ze.Mem.pfnGetAddressRange;
        if( nullptr == pfnGetAddressRange )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetIpcHandle = dditable->ze.Mem.pfnGetIpcHandle;
        if( nullptr == pfnGetIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetIpcHandleFromFileDescriptorExp = dditable->ze.MemExp.pfnGetIpcHandleFromFileDescriptorExp;
        if( nullptr == pfnGetIpcHandleFromFileDescriptorExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetFileDescriptorFromIpcHandleExp = dditable->ze.MemExp.pfnGetFileDescriptorFromIpcHandleExp;
        if( nullptr == pfnGetFileDescriptorFromIpcHandleExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnPutIpcHandle = dditable->ze.Mem.pfnPutIpcHandle;
        if( nullptr == pfnPutIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnOpenIpcHandle = dditable->ze.Mem.pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCloseIpcHandle = dditable->ze.Mem.pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnSetAtomicAccessAttributeExp = dditable->ze.MemExp.pfnSetAtomicAccessAttributeExp;
        if( nullptr == pfnSetAtomicAccessAttributeExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetAtomicAccessAttributeExp = dditable->ze.MemExp.pfnGetAtomicAccessAttributeExp;
        if( nullptr == pfnGetAtomicAccessAttributeExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->ze.Module.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );

        try
        {
            // convert driver handle to loader handle
            *phModule = reinterpret_cast<ze_module_handle_t>(
                ze_module_factory.getInstance( *phModule, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            if( nullptr != phBuildLog )
                *phBuildLog = reinterpret_cast<ze_module_build_log_handle_t>(
                    ze_module_build_log_factory.getInstance( *phBuildLog, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnDestroy = dditable->ze.Module.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnDestroy( hModule );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_module_factory.release( hModule );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( phModules[ 0 ] )->dditable;
        auto pfnDynamicLink = dditable->ze.Module.pfnDynamicLink;
        if( nullptr == pfnDynamicLink )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handles to driver handles
        auto phModulesLocal = new ze_module_handle_t [numModules];
        for( size_t i = 0; ( nullptr != phModules ) && ( i < numModules ); ++i )
            phModulesLocal[ i ] = reinterpret_cast<ze_module_object_t*>( phModules[ i ] )->handle;

        // forward to device-driver
        result = pfnDynamicLink( numModules, phModulesLocal, phLinkLog );
        delete []phModulesLocal;

        try
        {
            // convert driver handle to loader handle
            if( nullptr != phLinkLog )
                *phLinkLog = reinterpret_cast<ze_module_build_log_handle_t>(
                    ze_module_build_log_factory.getInstance( *phLinkLog, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        if( ZE_RESULT_SUCCESS != result )
            return result;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_build_log_object_t*>( hModuleBuildLog )->dditable;
        auto pfnDestroy = dditable->ze.ModuleBuildLog.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModuleBuildLog = reinterpret_cast<ze_module_build_log_object_t*>( hModuleBuildLog )->handle;

        // forward to device-driver
        result = pfnDestroy( hModuleBuildLog );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_module_build_log_factory.release( hModuleBuildLog );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_build_log_object_t*>( hModuleBuildLog )->dditable;
        auto pfnGetString = dditable->ze.ModuleBuildLog.pfnGetString;
        if( nullptr == pfnGetString )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModuleBuildLog = reinterpret_cast<ze_module_build_log_object_t*>( hModuleBuildLog )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnGetNativeBinary = dditable->ze.Module.pfnGetNativeBinary;
        if( nullptr == pfnGetNativeBinary )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnGetGlobalPointer = dditable->ze.Module.pfnGetGlobalPointer;
        if( nullptr == pfnGetGlobalPointer )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnGetKernelNames = dditable->ze.Module.pfnGetKernelNames;
        if( nullptr == pfnGetKernelNames )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnGetProperties = dditable->ze.Module.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnCreate = dditable->ze.Kernel.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnCreate( hModule, desc, phKernel );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phKernel = reinterpret_cast<ze_kernel_handle_t>(
                ze_kernel_factory.getInstance( *phKernel, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnDestroy = dditable->ze.Kernel.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnDestroy( hKernel );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_kernel_factory.release( hKernel );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnGetFunctionPointer = dditable->ze.Module.pfnGetFunctionPointer;
        if( nullptr == pfnGetFunctionPointer )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSetGroupSize = dditable->ze.Kernel.pfnSetGroupSize;
        if( nullptr == pfnSetGroupSize )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSuggestGroupSize = dditable->ze.Kernel.pfnSuggestGroupSize;
        if( nullptr == pfnSuggestGroupSize )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSuggestMaxCooperativeGroupCount = dditable->ze.Kernel.pfnSuggestMaxCooperativeGroupCount;
        if( nullptr == pfnSuggestMaxCooperativeGroupCount )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSetArgumentValue = dditable->ze.Kernel.pfnSetArgumentValue;
        if( nullptr == pfnSetArgumentValue )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // convert pArgValue to correct handle if applicable
        void *internalArgValue = const_cast<void *>(pArgValue);
        if (pArgValue) {
            // check if the arg value is a translated handle
            ze_image_object_t **imageHandle = static_cast<ze_image_object_t **>(internalArgValue);
            ze_sampler_object_t **samplerHandle = static_cast<ze_sampler_object_t **>(internalArgValue);
            if( image_handle_map.find(*imageHandle) != image_handle_map.end() ) {
                internalArgValue = &image_handle_map[*imageHandle];
            } else if( sampler_handle_map.find(*samplerHandle) != sampler_handle_map.end() ) {
                internalArgValue = &sampler_handle_map[*samplerHandle];
            }
        }
        // forward to device-driver
        result = pfnSetArgumentValue( hKernel, argIndex, argSize, const_cast<const void *>(internalArgValue) );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSetIndirectAccess = dditable->ze.Kernel.pfnSetIndirectAccess;
        if( nullptr == pfnSetIndirectAccess )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnGetIndirectAccess = dditable->ze.Kernel.pfnGetIndirectAccess;
        if( nullptr == pfnGetIndirectAccess )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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
                                                        ///< a null-terminating character, is returned in pSize.
                                                        ///< Otherwise, pString must point to valid application memory that is
                                                        ///< greater than or equal to *pSize bytes in length, and on return the
                                                        ///< pointed-to string will contain a space-separated list of kernel source attributes.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnGetSourceAttributes = dditable->ze.Kernel.pfnGetSourceAttributes;
        if( nullptr == pfnGetSourceAttributes )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSetCacheConfig = dditable->ze.Kernel.pfnSetCacheConfig;
        if( nullptr == pfnSetCacheConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnGetProperties = dditable->ze.Kernel.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnGetName = dditable->ze.Kernel.pfnGetName;
        if( nullptr == pfnGetName )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchKernel = dditable->ze.CommandList.pfnAppendLaunchKernel;
        if( nullptr == pfnAppendLaunchKernel )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchCooperativeKernel = dditable->ze.CommandList.pfnAppendLaunchCooperativeKernel;
        if( nullptr == pfnAppendLaunchCooperativeKernel )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchKernelIndirect = dditable->ze.CommandList.pfnAppendLaunchKernelIndirect;
        if( nullptr == pfnAppendLaunchKernelIndirect )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchMultipleKernelsIndirect = dditable->ze.CommandList.pfnAppendLaunchMultipleKernelsIndirect;
        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handles to driver handles
        auto phKernelsLocal = new ze_kernel_handle_t [numKernels];
        for( size_t i = 0; ( nullptr != phKernels ) && ( i < numKernels ); ++i )
            phKernelsLocal[ i ] = reinterpret_cast<ze_kernel_object_t*>( phKernels[ i ] )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernelsLocal, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phKernelsLocal;
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnMakeMemoryResident = dditable->ze.Context.pfnMakeMemoryResident;
        if( nullptr == pfnMakeMemoryResident )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnEvictMemory = dditable->ze.Context.pfnEvictMemory;
        if( nullptr == pfnEvictMemory )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnMakeImageResident = dditable->ze.Context.pfnMakeImageResident;
        if( nullptr == pfnMakeImageResident )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnEvictImage = dditable->ze.Context.pfnEvictImage;
        if( nullptr == pfnEvictImage )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->ze.Sampler.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phSampler );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            ze_sampler_handle_t internalHandlePtr = *phSampler;
            *phSampler = reinterpret_cast<ze_sampler_handle_t>(
                ze_sampler_factory.getInstance( *phSampler, dditable ) );
            // convert loader handle to driver handle and store in map
            sampler_handle_map.insert({ze_sampler_factory.getInstance( internalHandlePtr, dditable ), internalHandlePtr});
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_sampler_object_t*>( hSampler )->dditable;
        auto pfnDestroy = dditable->ze.Sampler.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // remove the handle from the kernel arugment map
        sampler_handle_map.erase(reinterpret_cast<ze_sampler_object_t*>(hSampler));
        // convert loader handle to driver handle
        hSampler = reinterpret_cast<ze_sampler_object_t*>( hSampler )->handle;

        // forward to device-driver
        result = pfnDestroy( hSampler );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_sampler_factory.release( hSampler );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnReserve = dditable->ze.VirtualMem.pfnReserve;
        if( nullptr == pfnReserve )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnFree = dditable->ze.VirtualMem.pfnFree;
        if( nullptr == pfnFree )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnQueryPageSize = dditable->ze.VirtualMem.pfnQueryPageSize;
        if( nullptr == pfnQueryPageSize )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnQueryPageSize( hContext, hDevice, size, pagesize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemCreate
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->ze.PhysicalMem.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, hDevice, desc, phPhysicalMemory );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phPhysicalMemory = reinterpret_cast<ze_physical_mem_handle_t>(
                ze_physical_mem_factory.getInstance( *phPhysicalMemory, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnDestroy = dditable->ze.PhysicalMem.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hPhysicalMemory = reinterpret_cast<ze_physical_mem_object_t*>( hPhysicalMemory )->handle;

        // forward to device-driver
        result = pfnDestroy( hContext, hPhysicalMemory );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_physical_mem_factory.release( hPhysicalMemory );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnMap = dditable->ze.VirtualMem.pfnMap;
        if( nullptr == pfnMap )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hPhysicalMemory = reinterpret_cast<ze_physical_mem_object_t*>( hPhysicalMemory )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnUnmap = dditable->ze.VirtualMem.pfnUnmap;
        if( nullptr == pfnUnmap )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnSetAccessAttribute = dditable->ze.VirtualMem.pfnSetAccessAttribute;
        if( nullptr == pfnSetAccessAttribute )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetAccessAttribute = dditable->ze.VirtualMem.pfnGetAccessAttribute;
        if( nullptr == pfnGetAccessAttribute )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSetGlobalOffsetExp = dditable->ze.KernelExp.pfnSetGlobalOffsetExp;
        if( nullptr == pfnSetGlobalOffsetExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnReserveCacheExt = dditable->ze.Device.pfnReserveCacheExt;
        if( nullptr == pfnReserveCacheExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnSetCacheAdviceExt = dditable->ze.Device.pfnSetCacheAdviceExt;
        if( nullptr == pfnSetCacheAdviceExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnQueryTimestampsExp = dditable->ze.EventExp.pfnQueryTimestampsExp;
        if( nullptr == pfnQueryTimestampsExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_image_object_t*>( hImage )->dditable;
        auto pfnGetMemoryPropertiesExp = dditable->ze.ImageExp.pfnGetMemoryPropertiesExp;
        if( nullptr == pfnGetMemoryPropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnViewCreateExt = dditable->ze.Image.pfnViewCreateExt;
        if( nullptr == pfnViewCreateExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phImageView = reinterpret_cast<ze_image_handle_t>(
                ze_image_factory.getInstance( *phImageView, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnViewCreateExp = dditable->ze.ImageExp.pfnViewCreateExp;
        if( nullptr == pfnViewCreateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            ze_image_handle_t internalHandlePtr = *phImageView;
            *phImageView = reinterpret_cast<ze_image_handle_t>(
                ze_image_factory.getInstance( *phImageView, dditable ) );
            // convert loader handle to driver handle and store in map
            image_handle_map.insert({ze_image_factory.getInstance( internalHandlePtr, dditable ), internalHandlePtr});
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSchedulingHintExp = dditable->ze.KernelExp.pfnSchedulingHintExp;
        if( nullptr == pfnSchedulingHintExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetPropertiesExt = dditable->ze.Device.pfnPciGetPropertiesExt;
        if( nullptr == pfnPciGetPropertiesExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyToMemoryExt = dditable->ze.CommandList.pfnAppendImageCopyToMemoryExt;
        if( nullptr == pfnAppendImageCopyToMemoryExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<ze_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyFromMemoryExt = dditable->ze.CommandList.pfnAppendImageCopyFromMemoryExt;
        if( nullptr == pfnAppendImageCopyFromMemoryExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<ze_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnGetAllocPropertiesExt = dditable->ze.Image.pfnGetAllocPropertiesExt;
        if( nullptr == pfnGetAllocPropertiesExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( phModules[ 0 ] )->dditable;
        auto pfnInspectLinkageExt = dditable->ze.Module.pfnInspectLinkageExt;
        if( nullptr == pfnInspectLinkageExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handles to driver handles
        auto phModulesLocal = new ze_module_handle_t [numModules];
        for( size_t i = 0; ( nullptr != phModules ) && ( i < numModules ); ++i )
            phModulesLocal[ i ] = reinterpret_cast<ze_module_object_t*>( phModules[ i ] )->handle;

        // forward to device-driver
        result = pfnInspectLinkageExt( pInspectDesc, numModules, phModulesLocal, phLog );
        delete []phModulesLocal;

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phLog = reinterpret_cast<ze_module_build_log_handle_t>(
                ze_module_build_log_factory.getInstance( *phLog, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_context_object_t*>( hContext )->dditable;
        auto pfnFreeExt = dditable->ze.Mem.pfnFreeExt;
        if( nullptr == pfnFreeExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<ze_context_object_t*>( hContext )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetExp = dditable->ze.FabricVertexExp.pfnGetExp;
        if( nullptr == pfnGetExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetExp( hDriver, pCount, phVertices );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phVertices ) && ( i < *pCount ); ++i )
                phVertices[ i ] = reinterpret_cast<ze_fabric_vertex_handle_t>(
                    ze_fabric_vertex_factory.getInstance( phVertices[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertex )->dditable;
        auto pfnGetSubVerticesExp = dditable->ze.FabricVertexExp.pfnGetSubVerticesExp;
        if( nullptr == pfnGetSubVerticesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVertex = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertex )->handle;

        // forward to device-driver
        result = pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phSubvertices ) && ( i < *pCount ); ++i )
                phSubvertices[ i ] = reinterpret_cast<ze_fabric_vertex_handle_t>(
                    ze_fabric_vertex_factory.getInstance( phSubvertices[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertex )->dditable;
        auto pfnGetPropertiesExp = dditable->ze.FabricVertexExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVertex = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertex )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertex )->dditable;
        auto pfnGetDeviceExp = dditable->ze.FabricVertexExp.pfnGetDeviceExp;
        if( nullptr == pfnGetDeviceExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVertex = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertex )->handle;

        // forward to device-driver
        result = pfnGetDeviceExp( hVertex, phDevice );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phDevice = reinterpret_cast<ze_device_handle_t>(
                ze_device_factory.getInstance( *phDevice, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetFabricVertexExp = dditable->ze.DeviceExp.pfnGetFabricVertexExp;
        if( nullptr == pfnGetFabricVertexExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetFabricVertexExp( hDevice, phVertex );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phVertex = reinterpret_cast<ze_fabric_vertex_handle_t>(
                ze_fabric_vertex_factory.getInstance( *phVertex, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertexA )->dditable;
        auto pfnGetExp = dditable->ze.FabricEdgeExp.pfnGetExp;
        if( nullptr == pfnGetExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVertexA = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertexA )->handle;

        // convert loader handle to driver handle
        hVertexB = reinterpret_cast<ze_fabric_vertex_object_t*>( hVertexB )->handle;

        // forward to device-driver
        result = pfnGetExp( hVertexA, hVertexB, pCount, phEdges );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phEdges ) && ( i < *pCount ); ++i )
                phEdges[ i ] = reinterpret_cast<ze_fabric_edge_handle_t>(
                    ze_fabric_edge_factory.getInstance( phEdges[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fabric_edge_object_t*>( hEdge )->dditable;
        auto pfnGetVerticesExp = dditable->ze.FabricEdgeExp.pfnGetVerticesExp;
        if( nullptr == pfnGetVerticesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEdge = reinterpret_cast<ze_fabric_edge_object_t*>( hEdge )->handle;

        // forward to device-driver
        result = pfnGetVerticesExp( hEdge, phVertexA, phVertexB );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phVertexA = reinterpret_cast<ze_fabric_vertex_handle_t>(
                ze_fabric_vertex_factory.getInstance( *phVertexA, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        try
        {
            // convert driver handle to loader handle
            *phVertexB = reinterpret_cast<ze_fabric_vertex_handle_t>(
                ze_fabric_vertex_factory.getInstance( *phVertexB, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fabric_edge_object_t*>( hEdge )->dditable;
        auto pfnGetPropertiesExp = dditable->ze.FabricEdgeExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEdge = reinterpret_cast<ze_fabric_edge_object_t*>( hEdge )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnQueryKernelTimestampsExt = dditable->ze.Event.pfnQueryKernelTimestampsExt;
        if( nullptr == pfnQueryKernelTimestampsExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnCreateExp = dditable->ze.RTASBuilderExp.pfnCreateExp;
        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnCreateExp( hDriver, pDescriptor, phBuilder );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phBuilder = reinterpret_cast<ze_rtas_builder_exp_handle_t>(
                ze_rtas_builder_exp_factory.getInstance( *phBuilder, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_rtas_builder_exp_object_t*>( hBuilder )->dditable;
        auto pfnGetBuildPropertiesExp = dditable->ze.RTASBuilderExp.pfnGetBuildPropertiesExp;
        if( nullptr == pfnGetBuildPropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hBuilder = reinterpret_cast<ze_rtas_builder_exp_object_t*>( hBuilder )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnRTASFormatCompatibilityCheckExp = dditable->ze.DriverExp.pfnRTASFormatCompatibilityCheckExp;
        if( nullptr == pfnRTASFormatCompatibilityCheckExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_rtas_builder_exp_object_t*>( hBuilder )->dditable;
        auto pfnBuildExp = dditable->ze.RTASBuilderExp.pfnBuildExp;
        if( nullptr == pfnBuildExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hBuilder = reinterpret_cast<ze_rtas_builder_exp_object_t*>( hBuilder )->handle;

        // convert loader handle to driver handle
        hParallelOperation = ( hParallelOperation ) ? reinterpret_cast<ze_rtas_parallel_operation_exp_object_t*>( hParallelOperation )->handle : nullptr;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_rtas_builder_exp_object_t*>( hBuilder )->dditable;
        auto pfnDestroyExp = dditable->ze.RTASBuilderExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hBuilder = reinterpret_cast<ze_rtas_builder_exp_object_t*>( hBuilder )->handle;

        // forward to device-driver
        result = pfnDestroyExp( hBuilder );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_rtas_builder_exp_factory.release( hBuilder );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnCreateExp = dditable->ze.RTASParallelOperationExp.pfnCreateExp;
        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnCreateExp( hDriver, phParallelOperation );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phParallelOperation = reinterpret_cast<ze_rtas_parallel_operation_exp_handle_t>(
                ze_rtas_parallel_operation_exp_factory.getInstance( *phParallelOperation, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_rtas_parallel_operation_exp_object_t*>( hParallelOperation )->dditable;
        auto pfnGetPropertiesExp = dditable->ze.RTASParallelOperationExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hParallelOperation = reinterpret_cast<ze_rtas_parallel_operation_exp_object_t*>( hParallelOperation )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_rtas_parallel_operation_exp_object_t*>( hParallelOperation )->dditable;
        auto pfnJoinExp = dditable->ze.RTASParallelOperationExp.pfnJoinExp;
        if( nullptr == pfnJoinExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hParallelOperation = reinterpret_cast<ze_rtas_parallel_operation_exp_object_t*>( hParallelOperation )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_rtas_parallel_operation_exp_object_t*>( hParallelOperation )->dditable;
        auto pfnDestroyExp = dditable->ze.RTASParallelOperationExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hParallelOperation = reinterpret_cast<ze_rtas_parallel_operation_exp_object_t*>( hParallelOperation )->handle;

        // forward to device-driver
        result = pfnDestroyExp( hParallelOperation );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        ze_rtas_parallel_operation_exp_factory.release( hParallelOperation );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

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
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetGlobalProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Global);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnInit                                     = loader::zeInit;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetGlobalProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetGlobalProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASBuilderExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASBuilderExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_builder_exp_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetRTASBuilderExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetRTASBuilderExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.RTASBuilderExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreateExp                                = loader::zeRTASBuilderCreateExp;
            pDdiTable->pfnGetBuildPropertiesExp                    = loader::zeRTASBuilderGetBuildPropertiesExp;
            pDdiTable->pfnBuildExp                                 = loader::zeRTASBuilderBuildExp;
            pDdiTable->pfnDestroyExp                               = loader::zeRTASBuilderDestroyExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.RTASBuilderExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetRTASBuilderExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetRTASBuilderExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetRTASBuilderExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetRTASBuilderExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASParallelOperationExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASParallelOperationExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_parallel_operation_exp_dditable_t* pDdiTable///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetRTASParallelOperationExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetRTASParallelOperationExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.RTASParallelOperationExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreateExp                                = loader::zeRTASParallelOperationCreateExp;
            pDdiTable->pfnGetPropertiesExp                         = loader::zeRTASParallelOperationGetPropertiesExp;
            pDdiTable->pfnJoinExp                                  = loader::zeRTASParallelOperationJoinExp;
            pDdiTable->pfnDestroyExp                               = loader::zeRTASParallelOperationDestroyExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.RTASParallelOperationExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetRTASParallelOperationExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetRTASParallelOperationExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetRTASParallelOperationExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetRTASParallelOperationExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDriverProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Driver);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zeDriverGet;
            pDdiTable->pfnGetApiVersion                            = loader::zeDriverGetApiVersion;
            pDdiTable->pfnGetProperties                            = loader::zeDriverGetProperties;
            pDdiTable->pfnGetIpcProperties                         = loader::zeDriverGetIpcProperties;
            pDdiTable->pfnGetExtensionProperties                   = loader::zeDriverGetExtensionProperties;
            pDdiTable->pfnGetExtensionFunctionAddress              = loader::zeDriverGetExtensionFunctionAddress;
            pDdiTable->pfnGetLastErrorDescription                  = loader::zeDriverGetLastErrorDescription;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Driver;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetDriverProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetDriverProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DriverExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDriverExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetDriverExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDriverExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.DriverExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnRTASFormatCompatibilityCheckExp          = loader::zeDriverRTASFormatCompatibilityCheckExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.DriverExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDriverExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetDriverExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDriverExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetDriverExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDeviceProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Device);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zeDeviceGet;
            pDdiTable->pfnGetSubDevices                            = loader::zeDeviceGetSubDevices;
            pDdiTable->pfnGetProperties                            = loader::zeDeviceGetProperties;
            pDdiTable->pfnGetComputeProperties                     = loader::zeDeviceGetComputeProperties;
            pDdiTable->pfnGetModuleProperties                      = loader::zeDeviceGetModuleProperties;
            pDdiTable->pfnGetCommandQueueGroupProperties           = loader::zeDeviceGetCommandQueueGroupProperties;
            pDdiTable->pfnGetMemoryProperties                      = loader::zeDeviceGetMemoryProperties;
            pDdiTable->pfnGetMemoryAccessProperties                = loader::zeDeviceGetMemoryAccessProperties;
            pDdiTable->pfnGetCacheProperties                       = loader::zeDeviceGetCacheProperties;
            pDdiTable->pfnGetImageProperties                       = loader::zeDeviceGetImageProperties;
            pDdiTable->pfnGetExternalMemoryProperties              = loader::zeDeviceGetExternalMemoryProperties;
            pDdiTable->pfnGetP2PProperties                         = loader::zeDeviceGetP2PProperties;
            pDdiTable->pfnCanAccessPeer                            = loader::zeDeviceCanAccessPeer;
            pDdiTable->pfnGetStatus                                = loader::zeDeviceGetStatus;
            pDdiTable->pfnGetGlobalTimestamps                      = loader::zeDeviceGetGlobalTimestamps;
            pDdiTable->pfnReserveCacheExt                          = loader::zeDeviceReserveCacheExt;
            pDdiTable->pfnSetCacheAdviceExt                        = loader::zeDeviceSetCacheAdviceExt;
            pDdiTable->pfnPciGetPropertiesExt                      = loader::zeDevicePciGetPropertiesExt;
            pDdiTable->pfnGetRootDevice                            = loader::zeDeviceGetRootDevice;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetDeviceProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetDeviceProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetDeviceExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.DeviceExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetFabricVertexExp                       = loader::zeDeviceGetFabricVertexExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.DeviceExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetDeviceExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetDeviceExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_context_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetContextProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Context);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeContextCreate;
            pDdiTable->pfnDestroy                                  = loader::zeContextDestroy;
            pDdiTable->pfnGetStatus                                = loader::zeContextGetStatus;
            pDdiTable->pfnSystemBarrier                            = loader::zeContextSystemBarrier;
            pDdiTable->pfnMakeMemoryResident                       = loader::zeContextMakeMemoryResident;
            pDdiTable->pfnEvictMemory                              = loader::zeContextEvictMemory;
            pDdiTable->pfnMakeImageResident                        = loader::zeContextMakeImageResident;
            pDdiTable->pfnEvictImage                               = loader::zeContextEvictImage;
            pDdiTable->pfnCreateEx                                 = loader::zeContextCreateEx;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Context;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetContextProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetContextProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetCommandQueueProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.CommandQueue);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeCommandQueueCreate;
            pDdiTable->pfnDestroy                                  = loader::zeCommandQueueDestroy;
            pDdiTable->pfnExecuteCommandLists                      = loader::zeCommandQueueExecuteCommandLists;
            pDdiTable->pfnSynchronize                              = loader::zeCommandQueueSynchronize;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.CommandQueue;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetCommandQueueProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetCommandQueueProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetCommandListProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.CommandList);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeCommandListCreate;
            pDdiTable->pfnCreateImmediate                          = loader::zeCommandListCreateImmediate;
            pDdiTable->pfnDestroy                                  = loader::zeCommandListDestroy;
            pDdiTable->pfnClose                                    = loader::zeCommandListClose;
            pDdiTable->pfnReset                                    = loader::zeCommandListReset;
            pDdiTable->pfnAppendWriteGlobalTimestamp               = loader::zeCommandListAppendWriteGlobalTimestamp;
            pDdiTable->pfnAppendBarrier                            = loader::zeCommandListAppendBarrier;
            pDdiTable->pfnAppendMemoryRangesBarrier                = loader::zeCommandListAppendMemoryRangesBarrier;
            pDdiTable->pfnAppendMemoryCopy                         = loader::zeCommandListAppendMemoryCopy;
            pDdiTable->pfnAppendMemoryFill                         = loader::zeCommandListAppendMemoryFill;
            pDdiTable->pfnAppendMemoryCopyRegion                   = loader::zeCommandListAppendMemoryCopyRegion;
            pDdiTable->pfnAppendMemoryCopyFromContext              = loader::zeCommandListAppendMemoryCopyFromContext;
            pDdiTable->pfnAppendImageCopy                          = loader::zeCommandListAppendImageCopy;
            pDdiTable->pfnAppendImageCopyRegion                    = loader::zeCommandListAppendImageCopyRegion;
            pDdiTable->pfnAppendImageCopyToMemory                  = loader::zeCommandListAppendImageCopyToMemory;
            pDdiTable->pfnAppendImageCopyFromMemory                = loader::zeCommandListAppendImageCopyFromMemory;
            pDdiTable->pfnAppendMemoryPrefetch                     = loader::zeCommandListAppendMemoryPrefetch;
            pDdiTable->pfnAppendMemAdvise                          = loader::zeCommandListAppendMemAdvise;
            pDdiTable->pfnAppendSignalEvent                        = loader::zeCommandListAppendSignalEvent;
            pDdiTable->pfnAppendWaitOnEvents                       = loader::zeCommandListAppendWaitOnEvents;
            pDdiTable->pfnAppendEventReset                         = loader::zeCommandListAppendEventReset;
            pDdiTable->pfnAppendQueryKernelTimestamps              = loader::zeCommandListAppendQueryKernelTimestamps;
            pDdiTable->pfnAppendLaunchKernel                       = loader::zeCommandListAppendLaunchKernel;
            pDdiTable->pfnAppendLaunchCooperativeKernel            = loader::zeCommandListAppendLaunchCooperativeKernel;
            pDdiTable->pfnAppendLaunchKernelIndirect               = loader::zeCommandListAppendLaunchKernelIndirect;
            pDdiTable->pfnAppendLaunchMultipleKernelsIndirect      = loader::zeCommandListAppendLaunchMultipleKernelsIndirect;
            pDdiTable->pfnAppendImageCopyToMemoryExt               = loader::zeCommandListAppendImageCopyToMemoryExt;
            pDdiTable->pfnAppendImageCopyFromMemoryExt             = loader::zeCommandListAppendImageCopyFromMemoryExt;
            pDdiTable->pfnHostSynchronize                          = loader::zeCommandListHostSynchronize;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetCommandListProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetCommandListProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetEventProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Event);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeEventCreate;
            pDdiTable->pfnDestroy                                  = loader::zeEventDestroy;
            pDdiTable->pfnHostSignal                               = loader::zeEventHostSignal;
            pDdiTable->pfnHostSynchronize                          = loader::zeEventHostSynchronize;
            pDdiTable->pfnQueryStatus                              = loader::zeEventQueryStatus;
            pDdiTable->pfnHostReset                                = loader::zeEventHostReset;
            pDdiTable->pfnQueryKernelTimestamp                     = loader::zeEventQueryKernelTimestamp;
            pDdiTable->pfnQueryKernelTimestampsExt                 = loader::zeEventQueryKernelTimestampsExt;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Event;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetEventProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetEventProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_exp_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetEventExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetEventExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.EventExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnQueryTimestampsExp                       = loader::zeEventQueryTimestampsExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.EventExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetEventExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetEventExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetEventPoolProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.EventPool);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeEventPoolCreate;
            pDdiTable->pfnDestroy                                  = loader::zeEventPoolDestroy;
            pDdiTable->pfnGetIpcHandle                             = loader::zeEventPoolGetIpcHandle;
            pDdiTable->pfnOpenIpcHandle                            = loader::zeEventPoolOpenIpcHandle;
            pDdiTable->pfnCloseIpcHandle                           = loader::zeEventPoolCloseIpcHandle;
            pDdiTable->pfnPutIpcHandle                             = loader::zeEventPoolPutIpcHandle;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.EventPool;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetEventPoolProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetEventPoolProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetFenceProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Fence);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeFenceCreate;
            pDdiTable->pfnDestroy                                  = loader::zeFenceDestroy;
            pDdiTable->pfnHostSynchronize                          = loader::zeFenceHostSynchronize;
            pDdiTable->pfnQueryStatus                              = loader::zeFenceQueryStatus;
            pDdiTable->pfnReset                                    = loader::zeFenceReset;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Fence;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetFenceProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetFenceProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetImageProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Image);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zeImageGetProperties;
            pDdiTable->pfnCreate                                   = loader::zeImageCreate;
            pDdiTable->pfnDestroy                                  = loader::zeImageDestroy;
            pDdiTable->pfnGetAllocPropertiesExt                    = loader::zeImageGetAllocPropertiesExt;
            pDdiTable->pfnViewCreateExt                            = loader::zeImageViewCreateExt;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Image;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetImageProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetImageProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ImageExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetImageExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_exp_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetImageExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetImageExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.ImageExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetMemoryPropertiesExp                   = loader::zeImageGetMemoryPropertiesExp;
            pDdiTable->pfnViewCreateExp                            = loader::zeImageViewCreateExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.ImageExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetImageExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetImageExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetImageExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetImageExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetKernelProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Kernel);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeKernelCreate;
            pDdiTable->pfnDestroy                                  = loader::zeKernelDestroy;
            pDdiTable->pfnSetCacheConfig                           = loader::zeKernelSetCacheConfig;
            pDdiTable->pfnSetGroupSize                             = loader::zeKernelSetGroupSize;
            pDdiTable->pfnSuggestGroupSize                         = loader::zeKernelSuggestGroupSize;
            pDdiTable->pfnSuggestMaxCooperativeGroupCount          = loader::zeKernelSuggestMaxCooperativeGroupCount;
            pDdiTable->pfnSetArgumentValue                         = loader::zeKernelSetArgumentValue;
            pDdiTable->pfnSetIndirectAccess                        = loader::zeKernelSetIndirectAccess;
            pDdiTable->pfnGetIndirectAccess                        = loader::zeKernelGetIndirectAccess;
            pDdiTable->pfnGetSourceAttributes                      = loader::zeKernelGetSourceAttributes;
            pDdiTable->pfnGetProperties                            = loader::zeKernelGetProperties;
            pDdiTable->pfnGetName                                  = loader::zeKernelGetName;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Kernel;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetKernelProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetKernelProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's KernelExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetKernelExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetKernelExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetKernelExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.KernelExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnSetGlobalOffsetExp                       = loader::zeKernelSetGlobalOffsetExp;
            pDdiTable->pfnSchedulingHintExp                        = loader::zeKernelSchedulingHintExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.KernelExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetKernelExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetKernelExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetKernelExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetKernelExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Mem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_mem_dditable_t* pDdiTable                    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetMemProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Mem);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnAllocShared                              = loader::zeMemAllocShared;
            pDdiTable->pfnAllocDevice                              = loader::zeMemAllocDevice;
            pDdiTable->pfnAllocHost                                = loader::zeMemAllocHost;
            pDdiTable->pfnFree                                     = loader::zeMemFree;
            pDdiTable->pfnGetAllocProperties                       = loader::zeMemGetAllocProperties;
            pDdiTable->pfnGetAddressRange                          = loader::zeMemGetAddressRange;
            pDdiTable->pfnGetIpcHandle                             = loader::zeMemGetIpcHandle;
            pDdiTable->pfnOpenIpcHandle                            = loader::zeMemOpenIpcHandle;
            pDdiTable->pfnCloseIpcHandle                           = loader::zeMemCloseIpcHandle;
            pDdiTable->pfnFreeExt                                  = loader::zeMemFreeExt;
            pDdiTable->pfnPutIpcHandle                             = loader::zeMemPutIpcHandle;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Mem;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetMemProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetMemProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MemExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_mem_exp_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetMemExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetMemExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.MemExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetIpcHandleFromFileDescriptorExp        = loader::zeMemGetIpcHandleFromFileDescriptorExp;
            pDdiTable->pfnGetFileDescriptorFromIpcHandleExp        = loader::zeMemGetFileDescriptorFromIpcHandleExp;
            pDdiTable->pfnSetAtomicAccessAttributeExp              = loader::zeMemSetAtomicAccessAttributeExp;
            pDdiTable->pfnGetAtomicAccessAttributeExp              = loader::zeMemGetAtomicAccessAttributeExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.MemExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetMemExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetMemExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetMemExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetMemExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetModuleProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Module);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeModuleCreate;
            pDdiTable->pfnDestroy                                  = loader::zeModuleDestroy;
            pDdiTable->pfnDynamicLink                              = loader::zeModuleDynamicLink;
            pDdiTable->pfnGetNativeBinary                          = loader::zeModuleGetNativeBinary;
            pDdiTable->pfnGetGlobalPointer                         = loader::zeModuleGetGlobalPointer;
            pDdiTable->pfnGetKernelNames                           = loader::zeModuleGetKernelNames;
            pDdiTable->pfnGetProperties                            = loader::zeModuleGetProperties;
            pDdiTable->pfnGetFunctionPointer                       = loader::zeModuleGetFunctionPointer;
            pDdiTable->pfnInspectLinkageExt                        = loader::zeModuleInspectLinkageExt;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Module;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetModuleProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetModuleProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetModuleBuildLogProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.ModuleBuildLog);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnDestroy                                  = loader::zeModuleBuildLogDestroy;
            pDdiTable->pfnGetString                                = loader::zeModuleBuildLogGetString;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.ModuleBuildLog;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetModuleBuildLogProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetModuleBuildLogProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PhysicalMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetPhysicalMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_physical_mem_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetPhysicalMemProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.PhysicalMem);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zePhysicalMemCreate;
            pDdiTable->pfnDestroy                                  = loader::zePhysicalMemDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.PhysicalMem;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetPhysicalMemProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetPhysicalMemProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetSamplerProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.Sampler);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeSamplerCreate;
            pDdiTable->pfnDestroy                                  = loader::zeSamplerDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.Sampler;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetSamplerProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetSamplerProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's VirtualMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetVirtualMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_virtual_mem_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetVirtualMemProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.ze.VirtualMem);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnReserve                                  = loader::zeVirtualMemReserve;
            pDdiTable->pfnFree                                     = loader::zeVirtualMemFree;
            pDdiTable->pfnQueryPageSize                            = loader::zeVirtualMemQueryPageSize;
            pDdiTable->pfnMap                                      = loader::zeVirtualMemMap;
            pDdiTable->pfnUnmap                                    = loader::zeVirtualMemUnmap;
            pDdiTable->pfnSetAccessAttribute                       = loader::zeVirtualMemSetAccessAttribute;
            pDdiTable->pfnGetAccessAttribute                       = loader::zeVirtualMemGetAccessAttribute;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.VirtualMem;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetVirtualMemProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetVirtualMemProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricEdgeExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricEdgeExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fabric_edge_exp_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetFabricEdgeExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetFabricEdgeExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.FabricEdgeExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetExp                                   = loader::zeFabricEdgeGetExp;
            pDdiTable->pfnGetVerticesExp                           = loader::zeFabricEdgeGetVerticesExp;
            pDdiTable->pfnGetPropertiesExp                         = loader::zeFabricEdgeGetPropertiesExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.FabricEdgeExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetFabricEdgeExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetFabricEdgeExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetFabricEdgeExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetFabricEdgeExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricVertexExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricVertexExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fabric_vertex_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<ze_pfnGetFabricVertexExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zeGetFabricVertexExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.ze.FabricVertexExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetExp                                   = loader::zeFabricVertexGetExp;
            pDdiTable->pfnGetSubVerticesExp                        = loader::zeFabricVertexGetSubVerticesExp;
            pDdiTable->pfnGetPropertiesExp                         = loader::zeFabricVertexGetPropertiesExp;
            pDdiTable->pfnGetDeviceExp                             = loader::zeFabricVertexGetDeviceExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.ze.FabricVertexExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetFabricVertexExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zeGetFabricVertexExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    // If the API tracing layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->tracingLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetFabricVertexExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->tracingLayer, "zeGetFabricVertexExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
