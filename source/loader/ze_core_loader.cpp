/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    ze_driver_factory_t                 ze_driver_factory;
    ze_device_factory_t                 ze_device_factory;
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

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    ze_result_t __zecall
    zeInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        for( auto& drv : context.drivers )
        {
            if( ZE_RESULT_SUCCESS == result )
            {
                result = drv.dditable.ze.Global.pfnInit( flags );
            }
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGet
    ze_result_t __zecall
    zeDriverGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader will update the value with the total
                                                        ///< number of drivers available.
                                                        ///< if count is non-zero, then the loader will only retrieve that number
                                                        ///< of drivers.
                                                        ///< if count is larger than the number of drivers available, then the
                                                        ///< loader will update the value with the correct number of drivers available.
        ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        uint32_t total_count = 0;

        for( auto& drv : context.drivers )
        {
            uint32_t count = 0;

            result = drv.dditable.ze.Driver.pfnGet( &count, nullptr );
            if( ZE_RESULT_SUCCESS != result ) break;

            if( ( 0 < *pCount ) && ( *pCount > total_count + count ) )
                break;

            if( nullptr != phDrivers )
            {
                result = drv.dditable.ze.Driver.pfnGet( &count, &phDrivers[ total_count ] );
                if( ZE_RESULT_SUCCESS != result ) break;

                try
                {
                    for( uint32_t i = total_count; i < count; ++i )
                        phDrivers[ i ] = reinterpret_cast<ze_driver_handle_t>( 
                            ze_driver_factory.getInstance( phDrivers[ i ], &drv.dditable ) );
                }
                catch( std::bad_alloc& )
                {
                    result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
                }
            }

            total_count += count;
        }

        if( ZE_RESULT_SUCCESS == result )
            *pCount = total_count;

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetApiVersion
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetApiVersion( hDriver, version );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetProperties
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDriver, pDriverProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIPCProperties
    ze_result_t __zecall
    zeDriverGetIPCProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetIPCProperties = dditable->ze.Driver.pfnGetIPCProperties;
        if( nullptr == pfnGetIPCProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetIPCProperties( hDriver, pIPCProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionFunctionAddress
    ze_result_t __zecall
    zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* pFuncName,                          ///< [in] name of the extension function
        void** pfunc                                    ///< [out] pointer to extension function
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetExtensionFunctionAddress = dditable->ze.Driver.pfnGetExtensionFunctionAddress;
        if( nullptr == pfnGetExtensionFunctionAddress )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetExtensionFunctionAddress( hDriver, pFuncName, pfunc );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    ze_result_t __zecall
    zeDeviceGet(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                        ///< if count is larger than the number of devices available, then the
                                                        ///< driver will update the value with the correct number of devices available.
        ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGet = dditable->ze.Device.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGet( hDriver, pCount, phDevices );

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
    /// @brief Intercept function for zeDeviceGetSubDevices
    ze_result_t __zecall
    zeDeviceGetSubDevices(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of sub-devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                        ///< if count is larger than the number of sub-devices available, then the
                                                        ///< driver will update the value with the correct number of sub-devices available.
        ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetSubDevices = dditable->ze.Device.pfnGetSubDevices;
        if( nullptr == pfnGetSubDevices )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetSubDevices( hDevice, pCount, phSubdevices );

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
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDevice, pDeviceProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetComputeProperties
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetComputeProperties( hDevice, pComputeProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetKernelProperties
    ze_result_t __zecall
    zeDeviceGetKernelProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_kernel_properties_t* pKernelProperties///< [in,out] query result for kernel properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetKernelProperties = dditable->ze.Device.pfnGetKernelProperties;
        if( nullptr == pfnGetKernelProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetKernelProperties( hDevice, pKernelProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    ze_result_t __zecall
    zeDeviceGetMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of memory properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< memory properties.
                                                        ///< if count is larger than the number of memory properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< memory properties available.
        ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetMemoryProperties = dditable->ze.Device.pfnGetMemoryProperties;
        if( nullptr == pfnGetMemoryProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetMemoryProperties( hDevice, pCount, pMemProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    ze_result_t __zecall
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnGetCacheProperties = dditable->ze.Device.pfnGetCacheProperties;
        if( nullptr == pfnGetCacheProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetCacheProperties( hDevice, pCacheProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetImageProperties
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetImageProperties( hDevice, pImageProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetP2PProperties
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hPeerDevice = reinterpret_cast<ze_device_object_t*>( hPeerDevice )->handle;

        // forward to device-driver
        result = pfnCanAccessPeer( hDevice, hPeerDevice, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSetLastLevelCacheConfig
    ze_result_t __zecall
    zeDeviceSetLastLevelCacheConfig(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device 
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnSetLastLevelCacheConfig = dditable->ze.Device.pfnSetLastLevelCacheConfig;
        if( nullptr == pfnSetLastLevelCacheConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnSetLastLevelCacheConfig( hDevice, CacheConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueCreate
    ze_result_t __zecall
    zeCommandQueueCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->ze.CommandQueue.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phCommandQueue );

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
    ze_result_t __zecall
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnDestroy = dditable->ze.CommandQueue.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandQueue );

        // release loader handle
        ze_command_queue_factory.release( hCommandQueue );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueExecuteCommandLists
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phCommandLists ) && ( i < numCommandLists ); ++i )
            phCommandLists[ i ] = reinterpret_cast<ze_command_list_object_t*>( phCommandLists[ i ] )->handle;

        // convert loader handle to driver handle
        hFence = ( hFence ) ? reinterpret_cast<ze_fence_object_t*>( hFence )->handle : nullptr;

        // forward to device-driver
        result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueSynchronize
    ze_result_t __zecall
    zeCommandQueueSynchronize(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->dditable;
        auto pfnSynchronize = dditable->ze.CommandQueue.pfnSynchronize;
        if( nullptr == pfnSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnSynchronize( hCommandQueue, timeout );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreate
    ze_result_t __zecall
    zeCommandListCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->ze.CommandList.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phCommandList );

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
    ze_result_t __zecall
    zeCommandListCreateImmediate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCreateImmediate = dditable->ze.CommandList.pfnCreateImmediate;
        if( nullptr == pfnCreateImmediate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreateImmediate( hDevice, altdesc, phCommandList );

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
    ze_result_t __zecall
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnDestroy = dditable->ze.CommandList.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnDestroy( hCommandList );

        // release loader handle
        ze_command_list_factory.release( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListClose
    ze_result_t __zecall
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnClose = dditable->ze.CommandList.pfnClose;
        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnClose( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListReset
    ze_result_t __zecall
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnReset = dditable->ze.CommandList.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnReset( hCommandList );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendBarrier
    ze_result_t __zecall
    zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendBarrier = dditable->ze.CommandList.pfnAppendBarrier;
        if( nullptr == pfnAppendBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryRangesBarrier
    ze_result_t __zecall
    zeCommandListAppendMemoryRangesBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryRangesBarrier = dditable->ze.CommandList.pfnAppendMemoryRangesBarrier;
        if( nullptr == pfnAppendMemoryRangesBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSystemBarrier
    ze_result_t __zecall
    zeDeviceSystemBarrier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnSystemBarrier = dditable->ze.Device.pfnSystemBarrier;
        if( nullptr == pfnSystemBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnSystemBarrier( hDevice );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLMemory
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLMemory(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnRegisterCLMemory = dditable->ze.Device.pfnRegisterCLMemory;
        if( nullptr == pfnRegisterCLMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnRegisterCLMemory( hDevice, context, mem, ptr );

        return result;
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLProgram
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLProgram(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        ze_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnRegisterCLProgram = dditable->ze.Device.pfnRegisterCLProgram;
        if( nullptr == pfnRegisterCLProgram )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnRegisterCLProgram( hDevice, context, program, phModule );

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

        return result;
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLCommandQueue
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLCommandQueue(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnRegisterCLCommandQueue = dditable->ze.Device.pfnRegisterCLCommandQueue;
        if( nullptr == pfnRegisterCLCommandQueue )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );

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
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopy
    ze_result_t __zecall
    zeCommandListAppendMemoryCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryCopy = dditable->ze.CommandList.pfnAppendMemoryCopy;
        if( nullptr == pfnAppendMemoryCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<ze_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryFill
    ze_result_t __zecall
    zeCommandListAppendMemoryFill(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryFill = dditable->ze.CommandList.pfnAppendMemoryFill;
        if( nullptr == pfnAppendMemoryFill )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<ze_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyRegion
    ze_result_t __zecall
    zeCommandListAppendMemoryCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                        ///< ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t::depth is not 0, otherwise it's
                                                        ///< ignored.
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMemoryCopyRegion = dditable->ze.CommandList.pfnAppendMemoryCopyRegion;
        if( nullptr == pfnAppendMemoryCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<ze_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopy
    ze_result_t __zecall
    zeCommandListAppendImageCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopy = dditable->ze.CommandList.pfnAppendImageCopy;
        if( nullptr == pfnAppendImageCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<ze_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<ze_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<ze_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyRegion
    ze_result_t __zecall
    zeCommandListAppendImageCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyRegion = dditable->ze.CommandList.pfnAppendImageCopyRegion;
        if( nullptr == pfnAppendImageCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<ze_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<ze_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<ze_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemory
    ze_result_t __zecall
    zeCommandListAppendImageCopyToMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyToMemory = dditable->ze.CommandList.pfnAppendImageCopyToMemory;
        if( nullptr == pfnAppendImageCopyToMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hSrcImage = reinterpret_cast<ze_image_object_t*>( hSrcImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<ze_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemory
    ze_result_t __zecall
    zeCommandListAppendImageCopyFromMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        ze_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendImageCopyFromMemory = dditable->ze.CommandList.pfnAppendImageCopyFromMemory;
        if( nullptr == pfnAppendImageCopyFromMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hDstImage = reinterpret_cast<ze_image_object_t*>( hDstImage )->handle;

        // convert loader handle to driver handle
        hEvent = ( hEvent ) ? reinterpret_cast<ze_event_object_t*>( hEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryPrefetch
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemAdvise
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    ze_result_t __zecall
    zeEventPoolCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnCreate = dditable->ze.EventPool.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phDevices ) && ( i < numDevices ); ++i )
            phDevices[ i ] = reinterpret_cast<ze_device_object_t*>( phDevices[ i ] )->handle;

        // forward to device-driver
        result = pfnCreate( hDriver, desc, numDevices, phDevices, phEventPool );

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
    ze_result_t __zecall
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnDestroy = dditable->ze.EventPool.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnDestroy( hEventPool );

        // release loader handle
        ze_event_pool_factory.release( hEventPool );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventCreate
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnCreate( hEventPool, desc, phEvent );

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
    ze_result_t __zecall
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnDestroy = dditable->ze.Event.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnDestroy( hEvent );

        // release loader handle
        ze_event_factory.release( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnGetIpcHandle( hEventPool, phIpc );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolOpenIpcHandle
    ze_result_t __zecall
    zeEventPoolOpenIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver to associate with the IPC event pool handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnOpenIpcHandle = dditable->ze.EventPool.pfnOpenIpcHandle;
        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnOpenIpcHandle( hDriver, hIpc, phEventPool );

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
    ze_result_t __zecall
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->dditable;
        auto pfnCloseIpcHandle = dditable->ze.EventPool.pfnCloseIpcHandle;
        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEventPool = reinterpret_cast<ze_event_pool_object_t*>( hEventPool )->handle;

        // forward to device-driver
        result = pfnCloseIpcHandle( hEventPool );

        // release loader handle
        ze_event_pool_factory.release( hEventPool );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    ze_result_t __zecall
    zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                        ///< continuing
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendWaitOnEvents = dditable->ze.CommandList.pfnAppendWaitOnEvents;
        if( nullptr == pfnAppendWaitOnEvents )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phEvents ) && ( i < numEvents ); ++i )
            phEvents[ i ] = reinterpret_cast<ze_event_object_t*>( phEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSignal
    ze_result_t __zecall
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnHostSignal = dditable->ze.Event.pfnHostSignal;
        if( nullptr == pfnHostSignal )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnHostSignal( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSynchronize
    ze_result_t __zecall
    zeEventHostSynchronize(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnHostSynchronize = dditable->ze.Event.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnHostSynchronize( hEvent, timeout );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryStatus
    ze_result_t __zecall
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnQueryStatus = dditable->ze.Event.pfnQueryStatus;
        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnQueryStatus( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendEventReset
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    ze_result_t __zecall
    zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnHostReset = dditable->ze.Event.pfnHostReset;
        if( nullptr == pfnHostReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnHostReset( hEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetTimestamp
    ze_result_t __zecall
    zeEventGetTimestamp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_timestamp_type_t timestampType,        ///< [in] specifies timestamp type to query for that is associated with
                                                        ///< hEvent.
        void* dstptr                                    ///< [in,out] pointer to memory for where timestamp will be written to. The
                                                        ///< size of timestamp is specified in the
                                                        ///< ::ze_event_timestamp_query_type_t definition.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_event_object_t*>( hEvent )->dditable;
        auto pfnGetTimestamp = dditable->ze.Event.pfnGetTimestamp;
        if( nullptr == pfnGetTimestamp )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<ze_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnGetTimestamp( hEvent, timestampType, dstptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceCreate
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandQueue = reinterpret_cast<ze_command_queue_object_t*>( hCommandQueue )->handle;

        // forward to device-driver
        result = pfnCreate( hCommandQueue, desc, phFence );

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
    ze_result_t __zecall
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnDestroy = dditable->ze.Fence.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnDestroy( hFence );

        // release loader handle
        ze_fence_factory.release( hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceHostSynchronize
    ze_result_t __zecall
    zeFenceHostSynchronize(
        ze_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnHostSynchronize = dditable->ze.Fence.pfnHostSynchronize;
        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnHostSynchronize( hFence, timeout );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceQueryStatus
    ze_result_t __zecall
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnQueryStatus = dditable->ze.Fence.pfnQueryStatus;
        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnQueryStatus( hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceReset
    ze_result_t __zecall
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_fence_object_t*>( hFence )->dditable;
        auto pfnReset = dditable->ze.Fence.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFence = reinterpret_cast<ze_fence_object_t*>( hFence )->handle;

        // forward to device-driver
        result = pfnReset( hFence );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetProperties
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDevice, desc, pImageProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageCreate
    ze_result_t __zecall
    zeImageCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->ze.Image.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phImage );

        try
        {
            // convert driver handle to loader handle
            *phImage = reinterpret_cast<ze_image_handle_t>(
                ze_image_factory.getInstance( *phImage, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    ze_result_t __zecall
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_image_object_t*>( hImage )->dditable;
        auto pfnDestroy = dditable->ze.Image.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnDestroy( hImage );

        // release loader handle
        ze_image_factory.release( hImage );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverAllocSharedMem
    ze_result_t __zecall
    zeDriverAllocSharedMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device mem alloc descriptor
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host mem alloc descriptor
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnAllocSharedMem = dditable->ze.Driver.pfnAllocSharedMem;
        if( nullptr == pfnAllocSharedMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handle to driver handle
        hDevice = ( hDevice ) ? reinterpret_cast<ze_device_object_t*>( hDevice )->handle : nullptr;

        // forward to device-driver
        result = pfnAllocSharedMem( hDriver, device_desc, host_desc, size, alignment, hDevice, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverAllocDeviceMem
    ze_result_t __zecall
    zeDriverAllocDeviceMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device mem alloc descriptor
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnAllocDeviceMem = dditable->ze.Driver.pfnAllocDeviceMem;
        if( nullptr == pfnAllocDeviceMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnAllocDeviceMem( hDriver, device_desc, size, alignment, hDevice, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverAllocHostMem
    ze_result_t __zecall
    zeDriverAllocHostMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host mem alloc descriptor
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnAllocHostMem = dditable->ze.Driver.pfnAllocHostMem;
        if( nullptr == pfnAllocHostMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnAllocHostMem( hDriver, host_desc, size, alignment, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverFreeMem
    ze_result_t __zecall
    zeDriverFreeMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnFreeMem = dditable->ze.Driver.pfnFreeMem;
        if( nullptr == pfnFreeMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnFreeMem( hDriver, ptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetMemAllocProperties
    ze_result_t __zecall
    zeDriverGetMemAllocProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetMemAllocProperties = dditable->ze.Driver.pfnGetMemAllocProperties;
        if( nullptr == pfnGetMemAllocProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetMemAllocProperties( hDriver, ptr, pMemAllocProperties, phDevice );

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
    /// @brief Intercept function for zeDriverGetMemAddressRange
    ze_result_t __zecall
    zeDriverGetMemAddressRange(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetMemAddressRange = dditable->ze.Driver.pfnGetMemAddressRange;
        if( nullptr == pfnGetMemAddressRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetMemAddressRange( hDriver, ptr, pBase, pSize );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetMemIpcHandle
    ze_result_t __zecall
    zeDriverGetMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnGetMemIpcHandle = dditable->ze.Driver.pfnGetMemIpcHandle;
        if( nullptr == pfnGetMemIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetMemIpcHandle( hDriver, ptr, pIpcHandle );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverOpenMemIpcHandle
    ze_result_t __zecall
    zeDriverOpenMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnOpenMemIpcHandle = dditable->ze.Driver.pfnOpenMemIpcHandle;
        if( nullptr == pfnOpenMemIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnOpenMemIpcHandle( hDriver, hDevice, handle, flags, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverCloseMemIpcHandle
    ze_result_t __zecall
    zeDriverCloseMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnCloseMemIpcHandle = dditable->ze.Driver.pfnCloseMemIpcHandle;
        if( nullptr == pfnCloseMemIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnCloseMemIpcHandle( hDriver, ptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleCreate
    ze_result_t __zecall
    zeModuleCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->ze.Module.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phModule, phBuildLog );

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
    ze_result_t __zecall
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnDestroy = dditable->ze.Module.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnDestroy( hModule );

        // release loader handle
        ze_module_factory.release( hModule );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogDestroy
    ze_result_t __zecall
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_build_log_object_t*>( hModuleBuildLog )->dditable;
        auto pfnDestroy = dditable->ze.ModuleBuildLog.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModuleBuildLog = reinterpret_cast<ze_module_build_log_object_t*>( hModuleBuildLog )->handle;

        // forward to device-driver
        result = pfnDestroy( hModuleBuildLog );

        // release loader handle
        ze_module_build_log_factory.release( hModuleBuildLog );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogGetString
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModuleBuildLog = reinterpret_cast<ze_module_build_log_object_t*>( hModuleBuildLog )->handle;

        // forward to device-driver
        result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetNativeBinary
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetGlobalPointer
    ze_result_t __zecall
    zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pGlobalName,                        ///< [in] name of global variable in module
        void** pptr                                     ///< [out] device visible pointer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnGetGlobalPointer = dditable->ze.Module.pfnGetGlobalPointer;
        if( nullptr == pfnGetGlobalPointer )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetGlobalPointer( hModule, pGlobalName, pptr );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetKernelNames
    ze_result_t __zecall
    zeModuleGetKernelNames(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of names available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of names.
                                                        ///< if count is larger than the number of names available, then the driver
                                                        ///< will update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_module_object_t*>( hModule )->dditable;
        auto pfnGetKernelNames = dditable->ze.Module.pfnGetKernelNames;
        if( nullptr == pfnGetKernelNames )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetKernelNames( hModule, pCount, pNames );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelCreate
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnCreate( hModule, desc, phKernel );

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
    ze_result_t __zecall
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnDestroy = dditable->ze.Kernel.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnDestroy( hKernel );

        // release loader handle
        ze_kernel_factory.release( hKernel );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetFunctionPointer
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<ze_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGroupSize
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestGroupSize
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetArgumentValue
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetAttribute
    ze_result_t __zecall
    zeKernelSetAttribute(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_attribute_t attr,                     ///< [in] attribute to set
        uint32_t size,                                  ///< [in] size in bytes of kernel attribute value.
        const void* pValue                              ///< [in][optional] pointer to attribute value.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSetAttribute = dditable->ze.Kernel.pfnSetAttribute;
        if( nullptr == pfnSetAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnSetAttribute( hKernel, attr, size, pValue );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetAttribute
    ze_result_t __zecall
    zeKernelGetAttribute(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_attribute_t attr,                     ///< [in] attribute to get. Documentation for ::ze_kernel_attribute_t for
                                                        ///< return type information for pValue.
        uint32_t* pSize,                                ///< [in,out] size in bytes needed for kernel attribute value. If pValue is
                                                        ///< nullptr then the size needed for pValue memory will be written to
                                                        ///< pSize. Only need to query size for arbitrary sized attributes.
        void* pValue                                    ///< [in,out][optional] pointer to attribute value result.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnGetAttribute = dditable->ze.Kernel.pfnGetAttribute;
        if( nullptr == pfnGetAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnGetAttribute( hKernel, attr, pSize, pValue );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIntermediateCacheConfig
    ze_result_t __zecall
    zeKernelSetIntermediateCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_kernel_object_t*>( hKernel )->dditable;
        auto pfnSetIntermediateCacheConfig = dditable->ze.Kernel.pfnSetIntermediateCacheConfig;
        if( nullptr == pfnSetIntermediateCacheConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnSetIntermediateCacheConfig( hKernel, CacheConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnGetProperties( hKernel, pKernelProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernel
    ze_result_t __zecall
    zeCommandListAppendLaunchKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchKernel = dditable->ze.CommandList.pfnAppendLaunchKernel;
        if( nullptr == pfnAppendLaunchKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchCooperativeKernel
    ze_result_t __zecall
    zeCommandListAppendLaunchCooperativeKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchCooperativeKernel = dditable->ze.CommandList.pfnAppendLaunchCooperativeKernel;
        if( nullptr == pfnAppendLaunchCooperativeKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelIndirect
    ze_result_t __zecall
    zeCommandListAppendLaunchKernelIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchKernelIndirect = dditable->ze.CommandList.pfnAppendLaunchKernelIndirect;
        if( nullptr == pfnAppendLaunchKernelIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<ze_kernel_object_t*>( hKernel )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchMultipleKernelsIndirect
    ze_result_t __zecall
    zeCommandListAppendLaunchMultipleKernelsIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less-than or equal-to
                                                        ///< numKernels
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendLaunchMultipleKernelsIndirect = dditable->ze.CommandList.pfnAppendLaunchMultipleKernelsIndirect;
        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<ze_command_list_object_t*>( hCommandList )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phKernels ) && ( i < numKernels ); ++i )
            phKernels[ i ] = reinterpret_cast<ze_kernel_object_t*>( phKernels[ i ] )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEvents[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceMakeMemoryResident
    ze_result_t __zecall
    zeDeviceMakeMemoryResident(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnMakeMemoryResident = dditable->ze.Device.pfnMakeMemoryResident;
        if( nullptr == pfnMakeMemoryResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnMakeMemoryResident( hDevice, ptr, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceEvictMemory
    ze_result_t __zecall
    zeDeviceEvictMemory(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnEvictMemory = dditable->ze.Device.pfnEvictMemory;
        if( nullptr == pfnEvictMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEvictMemory( hDevice, ptr, size );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceMakeImageResident
    ze_result_t __zecall
    zeDeviceMakeImageResident(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnMakeImageResident = dditable->ze.Device.pfnMakeImageResident;
        if( nullptr == pfnMakeImageResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnMakeImageResident( hDevice, hImage );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceEvictImage
    ze_result_t __zecall
    zeDeviceEvictImage(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnEvictImage = dditable->ze.Device.pfnEvictImage;
        if( nullptr == pfnEvictImage )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hImage = reinterpret_cast<ze_image_object_t*>( hImage )->handle;

        // forward to device-driver
        result = pfnEvictImage( hDevice, hImage );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerCreate
    ze_result_t __zecall
    zeSamplerCreate(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->ze.Sampler.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<ze_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, desc, phSampler );

        try
        {
            // convert driver handle to loader handle
            *phSampler = reinterpret_cast<ze_sampler_handle_t>(
                ze_sampler_factory.getInstance( *phSampler, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    ze_result_t __zecall
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_sampler_object_t*>( hSampler )->dditable;
        auto pfnDestroy = dditable->ze.Sampler.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSampler = reinterpret_cast<ze_sampler_object_t*>( hSampler )->handle;

        // forward to device-driver
        result = pfnDestroy( hSampler );

        // release loader handle
        ze_sampler_factory.release( hSampler );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetDriverProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Driver );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zeDriverGet;
            pDdiTable->pfnGetApiVersion                            = loader::zeDriverGetApiVersion;
            pDdiTable->pfnGetProperties                            = loader::zeDriverGetProperties;
            pDdiTable->pfnGetIPCProperties                         = loader::zeDriverGetIPCProperties;
            pDdiTable->pfnGetExtensionFunctionAddress              = loader::zeDriverGetExtensionFunctionAddress;
            pDdiTable->pfnAllocSharedMem                           = loader::zeDriverAllocSharedMem;
            pDdiTable->pfnAllocDeviceMem                           = loader::zeDriverAllocDeviceMem;
            pDdiTable->pfnAllocHostMem                             = loader::zeDriverAllocHostMem;
            pDdiTable->pfnFreeMem                                  = loader::zeDriverFreeMem;
            pDdiTable->pfnGetMemAllocProperties                    = loader::zeDriverGetMemAllocProperties;
            pDdiTable->pfnGetMemAddressRange                       = loader::zeDriverGetMemAddressRange;
            pDdiTable->pfnGetMemIpcHandle                          = loader::zeDriverGetMemIpcHandle;
            pDdiTable->pfnOpenMemIpcHandle                         = loader::zeDriverOpenMemIpcHandle;
            pDdiTable->pfnCloseMemIpcHandle                        = loader::zeDriverCloseMemIpcHandle;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Driver;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetDriverProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

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
__zedllexport ze_result_t __zecall
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetGlobalProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Global );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnInit                                     = loader::zeInit;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetGlobalProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetDeviceProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Device );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zeDeviceGet;
            pDdiTable->pfnGetSubDevices                            = loader::zeDeviceGetSubDevices;
            pDdiTable->pfnGetProperties                            = loader::zeDeviceGetProperties;
            pDdiTable->pfnGetComputeProperties                     = loader::zeDeviceGetComputeProperties;
            pDdiTable->pfnGetKernelProperties                      = loader::zeDeviceGetKernelProperties;
            pDdiTable->pfnGetMemoryProperties                      = loader::zeDeviceGetMemoryProperties;
            pDdiTable->pfnGetMemoryAccessProperties                = loader::zeDeviceGetMemoryAccessProperties;
            pDdiTable->pfnGetCacheProperties                       = loader::zeDeviceGetCacheProperties;
            pDdiTable->pfnGetImageProperties                       = loader::zeDeviceGetImageProperties;
            pDdiTable->pfnGetP2PProperties                         = loader::zeDeviceGetP2PProperties;
            pDdiTable->pfnCanAccessPeer                            = loader::zeDeviceCanAccessPeer;
            pDdiTable->pfnSetLastLevelCacheConfig                  = loader::zeDeviceSetLastLevelCacheConfig;
            pDdiTable->pfnSystemBarrier                            = loader::zeDeviceSystemBarrier;
        #if ZE_ENABLE_OCL_INTEROP
            pDdiTable->pfnRegisterCLMemory                         = loader::zeDeviceRegisterCLMemory;
        #else
            pDdiTable->pfnRegisterCLMemory                         = nullptr;
        #endif
        #if ZE_ENABLE_OCL_INTEROP
            pDdiTable->pfnRegisterCLProgram                        = loader::zeDeviceRegisterCLProgram;
        #else
            pDdiTable->pfnRegisterCLProgram                        = nullptr;
        #endif
        #if ZE_ENABLE_OCL_INTEROP
            pDdiTable->pfnRegisterCLCommandQueue                   = loader::zeDeviceRegisterCLCommandQueue;
        #else
            pDdiTable->pfnRegisterCLCommandQueue                   = nullptr;
        #endif
            pDdiTable->pfnMakeMemoryResident                       = loader::zeDeviceMakeMemoryResident;
            pDdiTable->pfnEvictMemory                              = loader::zeDeviceEvictMemory;
            pDdiTable->pfnMakeImageResident                        = loader::zeDeviceMakeImageResident;
            pDdiTable->pfnEvictImage                               = loader::zeDeviceEvictImage;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetDeviceProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetCommandQueueProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.CommandQueue );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
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
            *pDdiTable = loader::context.drivers.front().dditable.ze.CommandQueue;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetCommandQueueProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetCommandListProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.CommandList );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeCommandListCreate;
            pDdiTable->pfnCreateImmediate                          = loader::zeCommandListCreateImmediate;
            pDdiTable->pfnDestroy                                  = loader::zeCommandListDestroy;
            pDdiTable->pfnClose                                    = loader::zeCommandListClose;
            pDdiTable->pfnReset                                    = loader::zeCommandListReset;
            pDdiTable->pfnAppendBarrier                            = loader::zeCommandListAppendBarrier;
            pDdiTable->pfnAppendMemoryRangesBarrier                = loader::zeCommandListAppendMemoryRangesBarrier;
            pDdiTable->pfnAppendMemoryCopy                         = loader::zeCommandListAppendMemoryCopy;
            pDdiTable->pfnAppendMemoryFill                         = loader::zeCommandListAppendMemoryFill;
            pDdiTable->pfnAppendMemoryCopyRegion                   = loader::zeCommandListAppendMemoryCopyRegion;
            pDdiTable->pfnAppendImageCopy                          = loader::zeCommandListAppendImageCopy;
            pDdiTable->pfnAppendImageCopyRegion                    = loader::zeCommandListAppendImageCopyRegion;
            pDdiTable->pfnAppendImageCopyToMemory                  = loader::zeCommandListAppendImageCopyToMemory;
            pDdiTable->pfnAppendImageCopyFromMemory                = loader::zeCommandListAppendImageCopyFromMemory;
            pDdiTable->pfnAppendMemoryPrefetch                     = loader::zeCommandListAppendMemoryPrefetch;
            pDdiTable->pfnAppendMemAdvise                          = loader::zeCommandListAppendMemAdvise;
            pDdiTable->pfnAppendSignalEvent                        = loader::zeCommandListAppendSignalEvent;
            pDdiTable->pfnAppendWaitOnEvents                       = loader::zeCommandListAppendWaitOnEvents;
            pDdiTable->pfnAppendEventReset                         = loader::zeCommandListAppendEventReset;
            pDdiTable->pfnAppendLaunchKernel                       = loader::zeCommandListAppendLaunchKernel;
            pDdiTable->pfnAppendLaunchCooperativeKernel            = loader::zeCommandListAppendLaunchCooperativeKernel;
            pDdiTable->pfnAppendLaunchKernelIndirect               = loader::zeCommandListAppendLaunchKernelIndirect;
            pDdiTable->pfnAppendLaunchMultipleKernelsIndirect      = loader::zeCommandListAppendLaunchMultipleKernelsIndirect;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetCommandListProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetFenceProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Fence );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
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
            *pDdiTable = loader::context.drivers.front().dditable.ze.Fence;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetFenceProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetEventPoolProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.EventPool );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeEventPoolCreate;
            pDdiTable->pfnDestroy                                  = loader::zeEventPoolDestroy;
            pDdiTable->pfnGetIpcHandle                             = loader::zeEventPoolGetIpcHandle;
            pDdiTable->pfnOpenIpcHandle                            = loader::zeEventPoolOpenIpcHandle;
            pDdiTable->pfnCloseIpcHandle                           = loader::zeEventPoolCloseIpcHandle;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.EventPool;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetEventPoolProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetEventProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Event );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeEventCreate;
            pDdiTable->pfnDestroy                                  = loader::zeEventDestroy;
            pDdiTable->pfnHostSignal                               = loader::zeEventHostSignal;
            pDdiTable->pfnHostSynchronize                          = loader::zeEventHostSynchronize;
            pDdiTable->pfnQueryStatus                              = loader::zeEventQueryStatus;
            pDdiTable->pfnHostReset                                = loader::zeEventHostReset;
            pDdiTable->pfnGetTimestamp                             = loader::zeEventGetTimestamp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Event;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetEventProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetImageProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Image );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zeImageGetProperties;
            pDdiTable->pfnCreate                                   = loader::zeImageCreate;
            pDdiTable->pfnDestroy                                  = loader::zeImageDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Image;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetImageProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetModuleProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Module );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeModuleCreate;
            pDdiTable->pfnDestroy                                  = loader::zeModuleDestroy;
            pDdiTable->pfnGetNativeBinary                          = loader::zeModuleGetNativeBinary;
            pDdiTable->pfnGetGlobalPointer                         = loader::zeModuleGetGlobalPointer;
            pDdiTable->pfnGetKernelNames                           = loader::zeModuleGetKernelNames;
            pDdiTable->pfnGetFunctionPointer                       = loader::zeModuleGetFunctionPointer;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Module;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetModuleProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetModuleBuildLogProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.ModuleBuildLog );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnDestroy                                  = loader::zeModuleBuildLogDestroy;
            pDdiTable->pfnGetString                                = loader::zeModuleBuildLogGetString;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.ModuleBuildLog;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetModuleBuildLogProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetKernelProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Kernel );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeKernelCreate;
            pDdiTable->pfnDestroy                                  = loader::zeKernelDestroy;
            pDdiTable->pfnSetIntermediateCacheConfig               = loader::zeKernelSetIntermediateCacheConfig;
            pDdiTable->pfnSetGroupSize                             = loader::zeKernelSetGroupSize;
            pDdiTable->pfnSuggestGroupSize                         = loader::zeKernelSuggestGroupSize;
            pDdiTable->pfnSuggestMaxCooperativeGroupCount          = loader::zeKernelSuggestMaxCooperativeGroupCount;
            pDdiTable->pfnSetArgumentValue                         = loader::zeKernelSetArgumentValue;
            pDdiTable->pfnSetAttribute                             = loader::zeKernelSetAttribute;
            pDdiTable->pfnGetAttribute                             = loader::zeKernelGetAttribute;
            pDdiTable->pfnGetProperties                            = loader::zeKernelGetProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Kernel;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetKernelProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zeGetSamplerProcAddrTable") );
            result = getTable( version, &drv.dditable.ze.Sampler );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zeSamplerCreate;
            pDdiTable->pfnDestroy                                  = loader::zeSamplerDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.ze.Sampler;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zeGetSamplerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
