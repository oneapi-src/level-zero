/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_nullddi.cpp
 *
 */
#include "ze_null.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    __zedlllocal ze_result_t ZE_APICALL
    zeInit(
        ze_init_flags_t flags                           ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInit = context.zeDdiTable.Global.pfnInit;
        if( nullptr != pfnInit )
        {
            result = pfnInit( flags );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGet
    __zedlllocal ze_result_t ZE_APICALL
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zeDdiTable.Driver.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( pCount, phDrivers );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDrivers ) && ( i < *pCount ); ++i )
                phDrivers[ i ] = reinterpret_cast<ze_driver_handle_t>( context.get() );

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetApiVersion = context.zeDdiTable.Driver.pfnGetApiVersion;
        if( nullptr != pfnGetApiVersion )
        {
            result = pfnGetApiVersion( hDriver, version );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Driver.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDriver, pDriverProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIpcProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [out] query result for IPC properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIpcProperties = context.zeDdiTable.Driver.pfnGetIpcProperties;
        if( nullptr != pfnGetIpcProperties )
        {
            result = pfnGetIpcProperties( hDriver, pIpcProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of extension properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< extension properties.
                                                        ///< if count is larger than the number of extension properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< extension properties available.
        ze_driver_extension_properties_t* pExtensionProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< extension properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetExtensionProperties = context.zeDdiTable.Driver.pfnGetExtensionProperties;
        if( nullptr != pfnGetExtensionProperties )
        {
            result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    __zedlllocal ze_result_t ZE_APICALL
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zeDdiTable.Device.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDriver, pCount, phDevices );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDevices ) && ( i < *pCount ); ++i )
                phDevices[ i ] = reinterpret_cast<ze_device_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetSubDevices
    __zedlllocal ze_result_t ZE_APICALL
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetSubDevices = context.zeDdiTable.Device.pfnGetSubDevices;
        if( nullptr != pfnGetSubDevices )
        {
            result = pfnGetSubDevices( hDevice, pCount, phSubdevices );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phSubdevices ) && ( i < *pCount ); ++i )
                phSubdevices[ i ] = reinterpret_cast<ze_device_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Device.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDevice, pDeviceProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetComputeProperties = context.zeDdiTable.Device.pfnGetComputeProperties;
        if( nullptr != pfnGetComputeProperties )
        {
            result = pfnGetComputeProperties( hDevice, pComputeProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetModuleProperties = context.zeDdiTable.Device.pfnGetModuleProperties;
        if( nullptr != pfnGetModuleProperties )
        {
            result = pfnGetModuleProperties( hDevice, pModuleProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCommandQueueGroupProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCommandQueueGroupProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of command queue group properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< command queue group properties.
                                                        ///< if count is larger than the number of command queue group properties
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of command queue group properties available.
        ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< command queue group properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetCommandQueueGroupProperties = context.zeDdiTable.Device.pfnGetCommandQueueGroupProperties;
        if( nullptr != pfnGetCommandQueueGroupProperties )
        {
            result = pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemoryProperties = context.zeDdiTable.Device.pfnGetMemoryProperties;
        if( nullptr != pfnGetMemoryProperties )
        {
            result = pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMemoryAccessProperties = context.zeDdiTable.Device.pfnGetMemoryAccessProperties;
        if( nullptr != pfnGetMemoryAccessProperties )
        {
            result = pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of cache properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< cache properties.
                                                        ///< if count is larger than the number of cache properties available, then
                                                        ///< the driver will update the value with the correct number of cache
                                                        ///< properties available.
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for cache
                                                        ///< properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetCacheProperties = context.zeDdiTable.Device.pfnGetCacheProperties;
        if( nullptr != pfnGetCacheProperties )
        {
            result = pfnGetCacheProperties( hDevice, pCount, pCacheProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetImageProperties = context.zeDdiTable.Device.pfnGetImageProperties;
        if( nullptr != pfnGetImageProperties )
        {
            result = pfnGetImageProperties( hDevice, pImageProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetExternalMemoryProperties = context.zeDdiTable.Device.pfnGetExternalMemoryProperties;
        if( nullptr != pfnGetExternalMemoryProperties )
        {
            result = pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetP2PProperties = context.zeDdiTable.Device.pfnGetP2PProperties;
        if( nullptr != pfnGetP2PProperties )
        {
            result = pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCanAccessPeer = context.zeDdiTable.Device.pfnCanAccessPeer;
        if( nullptr != pfnCanAccessPeer )
        {
            result = pfnCanAccessPeer( hDevice, hPeerDevice, value );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetStatus = context.zeDdiTable.Device.pfnGetStatus;
        if( nullptr != pfnGetStatus )
        {
            result = pfnGetStatus( hDevice );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Context.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hDriver, desc, phContext );
        }
        else
        {
            // generic implementation
            *phContext = reinterpret_cast<ze_context_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Context.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hContext );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetStatus = context.zeDdiTable.Context.pfnGetStatus;
        if( nullptr != pfnGetStatus )
        {
            result = pfnGetStatus( hContext );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.CommandQueue.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, hDevice, desc, phCommandQueue );
        }
        else
        {
            // generic implementation
            *phCommandQueue = reinterpret_cast<ze_command_queue_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.CommandQueue.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hCommandQueue );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnExecuteCommandLists = context.zeDdiTable.CommandQueue.pfnExecuteCommandLists;
        if( nullptr != pfnExecuteCommandLists )
        {
            result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
        }
        else
        {
            // generic implementation
        }

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
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSynchronize = context.zeDdiTable.CommandQueue.pfnSynchronize;
        if( nullptr != pfnSynchronize )
        {
            result = pfnSynchronize( hCommandQueue, timeout );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.CommandList.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, hDevice, desc, phCommandList );
        }
        else
        {
            // generic implementation
            *phCommandList = reinterpret_cast<ze_command_list_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateImmediate = context.zeDdiTable.CommandList.pfnCreateImmediate;
        if( nullptr != pfnCreateImmediate )
        {
            result = pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );
        }
        else
        {
            // generic implementation
            *phCommandList = reinterpret_cast<ze_command_list_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.CommandList.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hCommandList );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.zeDdiTable.CommandList.pfnClose;
        if( nullptr != pfnClose )
        {
            result = pfnClose( hCommandList );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zeDdiTable.CommandList.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hCommandList );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendWriteGlobalTimestamp = context.zeDdiTable.CommandList.pfnAppendWriteGlobalTimestamp;
        if( nullptr != pfnAppendWriteGlobalTimestamp )
        {
            result = pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendBarrier = context.zeDdiTable.CommandList.pfnAppendBarrier;
        if( nullptr != pfnAppendBarrier )
        {
            result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryRangesBarrier = context.zeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;
        if( nullptr != pfnAppendMemoryRangesBarrier )
        {
            result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSystemBarrier = context.zeDdiTable.Context.pfnSystemBarrier;
        if( nullptr != pfnSystemBarrier )
        {
            result = pfnSystemBarrier( hContext, hDevice );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryCopy = context.zeDdiTable.CommandList.pfnAppendMemoryCopy;
        if( nullptr != pfnAppendMemoryCopy )
        {
            result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryFill = context.zeDdiTable.CommandList.pfnAppendMemoryFill;
        if( nullptr != pfnAppendMemoryFill )
        {
            result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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
                                                        ///< copies where ::ze_copy_region_t.depth is not 0, otherwise it's
                                                        ///< ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t.depth is not 0, otherwise it's
                                                        ///< ignored.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryCopyRegion = context.zeDdiTable.CommandList.pfnAppendMemoryCopyRegion;
        if( nullptr != pfnAppendMemoryCopyRegion )
        {
            result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryCopyFromContext = context.zeDdiTable.CommandList.pfnAppendMemoryCopyFromContext;
        if( nullptr != pfnAppendMemoryCopyFromContext )
        {
            result = pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopy = context.zeDdiTable.CommandList.pfnAppendImageCopy;
        if( nullptr != pfnAppendImageCopy )
        {
            result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyRegion = context.zeDdiTable.CommandList.pfnAppendImageCopyRegion;
        if( nullptr != pfnAppendImageCopyRegion )
        {
            result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyToMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemory;
        if( nullptr != pfnAppendImageCopyToMemory )
        {
            result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendImageCopyFromMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemory;
        if( nullptr != pfnAppendImageCopyFromMemory )
        {
            result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemoryPrefetch = context.zeDdiTable.CommandList.pfnAppendMemoryPrefetch;
        if( nullptr != pfnAppendMemoryPrefetch )
        {
            result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMemAdvise = context.zeDdiTable.CommandList.pfnAppendMemAdvise;
        if( nullptr != pfnAppendMemAdvise )
        {
            result = pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.EventPool.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );
        }
        else
        {
            // generic implementation
            *phEventPool = reinterpret_cast<ze_event_pool_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.EventPool.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hEventPool );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Event.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hEventPool, desc, phEvent );
        }
        else
        {
            // generic implementation
            *phEvent = reinterpret_cast<ze_event_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Event.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hEvent );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIpcHandle = context.zeDdiTable.EventPool.pfnGetIpcHandle;
        if( nullptr != pfnGetIpcHandle )
        {
            result = pfnGetIpcHandle( hEventPool, phIpc );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpenIpcHandle = context.zeDdiTable.EventPool.pfnOpenIpcHandle;
        if( nullptr != pfnOpenIpcHandle )
        {
            result = pfnOpenIpcHandle( hContext, hIpc, phEventPool );
        }
        else
        {
            // generic implementation
            *phEventPool = reinterpret_cast<ze_event_pool_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCloseIpcHandle = context.zeDdiTable.EventPool.pfnCloseIpcHandle;
        if( nullptr != pfnCloseIpcHandle )
        {
            result = pfnCloseIpcHandle( hEventPool );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendSignalEvent = context.zeDdiTable.CommandList.pfnAppendSignalEvent;
        if( nullptr != pfnAppendSignalEvent )
        {
            result = pfnAppendSignalEvent( hCommandList, hEvent );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendWaitOnEvents = context.zeDdiTable.CommandList.pfnAppendWaitOnEvents;
        if( nullptr != pfnAppendWaitOnEvents )
        {
            result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSignal = context.zeDdiTable.Event.pfnHostSignal;
        if( nullptr != pfnHostSignal )
        {
            result = pfnHostSignal( hEvent );
        }
        else
        {
            // generic implementation
        }

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
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSynchronize = context.zeDdiTable.Event.pfnHostSynchronize;
        if( nullptr != pfnHostSynchronize )
        {
            result = pfnHostSynchronize( hEvent, timeout );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryStatus = context.zeDdiTable.Event.pfnQueryStatus;
        if( nullptr != pfnQueryStatus )
        {
            result = pfnQueryStatus( hEvent );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendEventReset = context.zeDdiTable.CommandList.pfnAppendEventReset;
        if( nullptr != pfnAppendEventReset )
        {
            result = pfnAppendEventReset( hCommandList, hEvent );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostReset = context.zeDdiTable.Event.pfnHostReset;
        if( nullptr != pfnHostReset )
        {
            result = pfnHostReset( hEvent );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryKernelTimestamp = context.zeDdiTable.Event.pfnQueryKernelTimestamp;
        if( nullptr != pfnQueryKernelTimestamp )
        {
            result = pfnQueryKernelTimestamp( hEvent, dstptr );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendQueryKernelTimestamps = context.zeDdiTable.CommandList.pfnAppendQueryKernelTimestamps;
        if( nullptr != pfnAppendQueryKernelTimestamps )
        {
            result = pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Fence.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hCommandQueue, desc, phFence );
        }
        else
        {
            // generic implementation
            *phFence = reinterpret_cast<ze_fence_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Fence.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hFence );
        }
        else
        {
            // generic implementation

        }

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
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnHostSynchronize = context.zeDdiTable.Fence.pfnHostSynchronize;
        if( nullptr != pfnHostSynchronize )
        {
            result = pfnHostSynchronize( hFence, timeout );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryStatus = context.zeDdiTable.Fence.pfnQueryStatus;
        if( nullptr != pfnQueryStatus )
        {
            result = pfnQueryStatus( hFence );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zeDdiTable.Fence.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hFence );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Image.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDevice, desc, pImageProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Image.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, hDevice, desc, phImage );
        }
        else
        {
            // generic implementation
            *phImage = reinterpret_cast<ze_image_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Image.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hImage );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocShared
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocShared(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocShared = context.zeDdiTable.Mem.pfnAllocShared;
        if( nullptr != pfnAllocShared )
        {
            result = pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocDevice(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocDevice = context.zeDdiTable.Mem.pfnAllocDevice;
        if( nullptr != pfnAllocDevice )
        {
            result = pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocHost
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocHost(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAllocHost = context.zeDdiTable.Mem.pfnAllocHost;
        if( nullptr != pfnAllocHost )
        {
            result = pfnAllocHost( hContext, host_desc, size, alignment, pptr );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFree = context.zeDdiTable.Mem.pfnFree;
        if( nullptr != pfnFree )
        {
            result = pfnFree( hContext, ptr );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAllocProperties = context.zeDdiTable.Mem.pfnGetAllocProperties;
        if( nullptr != pfnGetAllocProperties )
        {
            result = pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
        }
        else
        {
            // generic implementation
            if( nullptr != phDevice ) *phDevice = reinterpret_cast<ze_device_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAddressRange = context.zeDdiTable.Mem.pfnGetAddressRange;
        if( nullptr != pfnGetAddressRange )
        {
            result = pfnGetAddressRange( hContext, ptr, pBase, pSize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIpcHandle = context.zeDdiTable.Mem.pfnGetIpcHandle;
        if( nullptr != pfnGetIpcHandle )
        {
            result = pfnGetIpcHandle( hContext, ptr, pIpcHandle );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpenIpcHandle = context.zeDdiTable.Mem.pfnOpenIpcHandle;
        if( nullptr != pfnOpenIpcHandle )
        {
            result = pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCloseIpcHandle = context.zeDdiTable.Mem.pfnCloseIpcHandle;
        if( nullptr != pfnCloseIpcHandle )
        {
            result = pfnCloseIpcHandle( hContext, ptr );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Module.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );
        }
        else
        {
            // generic implementation
            *phModule = reinterpret_cast<ze_module_handle_t>( context.get() );

            if( nullptr != phBuildLog ) *phBuildLog = reinterpret_cast<ze_module_build_log_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Module.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hModule );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDynamicLink = context.zeDdiTable.Module.pfnDynamicLink;
        if( nullptr != pfnDynamicLink )
        {
            result = pfnDynamicLink( numModules, phModules, phLinkLog );
        }
        else
        {
            // generic implementation
            if( nullptr != phLinkLog ) *phLinkLog = reinterpret_cast<ze_module_build_log_handle_t>( context.get() );

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.ModuleBuildLog.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hModuleBuildLog );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetString = context.zeDdiTable.ModuleBuildLog.pfnGetString;
        if( nullptr != pfnGetString )
        {
            result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetNativeBinary = context.zeDdiTable.Module.pfnGetNativeBinary;
        if( nullptr != pfnGetNativeBinary )
        {
            result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetGlobalPointer = context.zeDdiTable.Module.pfnGetGlobalPointer;
        if( nullptr != pfnGetGlobalPointer )
        {
            result = pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetKernelNames
    __zedlllocal ze_result_t ZE_APICALL
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetKernelNames = context.zeDdiTable.Module.pfnGetKernelNames;
        if( nullptr != pfnGetKernelNames )
        {
            result = pfnGetKernelNames( hModule, pCount, pNames );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Module.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hModule, pModuleProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Kernel.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hModule, desc, phKernel );
        }
        else
        {
            // generic implementation
            *phKernel = reinterpret_cast<ze_kernel_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Kernel.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hKernel );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFunctionPointer = context.zeDdiTable.Module.pfnGetFunctionPointer;
        if( nullptr != pfnGetFunctionPointer )
        {
            result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetGroupSize = context.zeDdiTable.Kernel.pfnSetGroupSize;
        if( nullptr != pfnSetGroupSize )
        {
            result = pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSuggestGroupSize = context.zeDdiTable.Kernel.pfnSuggestGroupSize;
        if( nullptr != pfnSuggestGroupSize )
        {
            result = pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSuggestMaxCooperativeGroupCount = context.zeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;
        if( nullptr != pfnSuggestMaxCooperativeGroupCount )
        {
            result = pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetArgumentValue = context.zeDdiTable.Kernel.pfnSetArgumentValue;
        if( nullptr != pfnSetArgumentValue )
        {
            result = pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetIndirectAccess = context.zeDdiTable.Kernel.pfnSetIndirectAccess;
        if( nullptr != pfnSetIndirectAccess )
        {
            result = pfnSetIndirectAccess( hKernel, flags );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetIndirectAccess = context.zeDdiTable.Kernel.pfnGetIndirectAccess;
        if( nullptr != pfnGetIndirectAccess )
        {
            result = pfnGetIndirectAccess( hKernel, pFlags );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetSourceAttributes
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetSourceAttributes(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes.
                                                        ///< if size is zero, then the driver will update string argument.
                                                        ///< if size is non-zero, then driver will only retrieve string size in bytes.
                                                        ///< if size is larger than source attributes string, then the driver will
                                                        ///< update the string.
        char** pString                                  ///< [in,out][optional] pointer to null-terminated string where kernel
                                                        ///< source attributes are separated by space.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetSourceAttributes = context.zeDdiTable.Kernel.pfnGetSourceAttributes;
        if( nullptr != pfnGetSourceAttributes )
        {
            result = pfnGetSourceAttributes( hKernel, pSize, pString );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetCacheConfig = context.zeDdiTable.Kernel.pfnSetCacheConfig;
        if( nullptr != pfnSetCacheConfig )
        {
            result = pfnSetCacheConfig( hKernel, flags );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zeDdiTable.Kernel.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hKernel, pKernelProperties );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetName = context.zeDdiTable.Kernel.pfnGetName;
        if( nullptr != pfnGetName )
        {
            result = pfnGetName( hKernel, pSize, pName );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchKernel = context.zeDdiTable.CommandList.pfnAppendLaunchKernel;
        if( nullptr != pfnAppendLaunchKernel )
        {
            result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchCooperativeKernel = context.zeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel;
        if( nullptr != pfnAppendLaunchCooperativeKernel )
        {
            result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchKernelIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchKernelIndirect;
        if( nullptr != pfnAppendLaunchKernelIndirect )
        {
            result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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
                                                        ///< number of kernels to launch; value must be less-than or equal-to
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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendLaunchMultipleKernelsIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;
        if( nullptr != pfnAppendLaunchMultipleKernelsIndirect )
        {
            result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMakeMemoryResident = context.zeDdiTable.Context.pfnMakeMemoryResident;
        if( nullptr != pfnMakeMemoryResident )
        {
            result = pfnMakeMemoryResident( hContext, hDevice, ptr, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEvictMemory = context.zeDdiTable.Context.pfnEvictMemory;
        if( nullptr != pfnEvictMemory )
        {
            result = pfnEvictMemory( hContext, hDevice, ptr, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMakeImageResident = context.zeDdiTable.Context.pfnMakeImageResident;
        if( nullptr != pfnMakeImageResident )
        {
            result = pfnMakeImageResident( hContext, hDevice, hImage );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEvictImage = context.zeDdiTable.Context.pfnEvictImage;
        if( nullptr != pfnEvictImage )
        {
            result = pfnEvictImage( hContext, hDevice, hImage );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.Sampler.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, hDevice, desc, phSampler );
        }
        else
        {
            // generic implementation
            *phSampler = reinterpret_cast<ze_sampler_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.Sampler.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hSampler );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemReserve
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemReserve(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReserve = context.zeDdiTable.VirtualMem.pfnReserve;
        if( nullptr != pfnReserve )
        {
            result = pfnReserve( hContext, pStart, size, pptr );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFree = context.zeDdiTable.VirtualMem.pfnFree;
        if( nullptr != pfnFree )
        {
            result = pfnFree( hContext, ptr, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnQueryPageSize = context.zeDdiTable.VirtualMem.pfnQueryPageSize;
        if( nullptr != pfnQueryPageSize )
        {
            result = pfnQueryPageSize( hContext, hDevice, size, pagesize );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zeDdiTable.PhysicalMem.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, hDevice, desc, phPhysicalMemory );
        }
        else
        {
            // generic implementation
            *phPhysicalMemory = reinterpret_cast<ze_physical_mem_handle_t>( context.get() );

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zeDdiTable.PhysicalMem.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hContext, hPhysicalMemory );
        }
        else
        {
            // generic implementation

        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnMap = context.zeDdiTable.VirtualMem.pfnMap;
        if( nullptr != pfnMap )
        {
            result = pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnUnmap = context.zeDdiTable.VirtualMem.pfnUnmap;
        if( nullptr != pfnUnmap )
        {
            result = pfnUnmap( hContext, ptr, size );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetAccessAttribute = context.zeDdiTable.VirtualMem.pfnSetAccessAttribute;
        if( nullptr != pfnSetAccessAttribute )
        {
            result = pfnSetAccessAttribute( hContext, ptr, size, access );
        }
        else
        {
            // generic implementation
        }

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

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAccessAttribute = context.zeDdiTable.VirtualMem.pfnGetAccessAttribute;
        if( nullptr != pfnGetAccessAttribute )
        {
            result = pfnGetAccessAttribute( hContext, ptr, size, access, outSize );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

} // namespace driver

namespace instrumented
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    __zedlllocal ze_result_t ZE_APICALL
    zeInit(
        ze_init_flags_t flags                           ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_init_params_t in_params = {
            &flags
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeInit( flags );

        // capture parameters
        ze_init_params_t out_params = {
            &flags
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Global;
                if( nullptr != table.pfnInitCb )
                    table.pfnInitCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGet
    __zedlllocal ze_result_t ZE_APICALL
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

        // capture parameters
        ze_driver_get_params_t in_params = {
            &pCount,
            &phDrivers
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGet( pCount, phDrivers );

        // capture parameters
        ze_driver_get_params_t out_params = {
            &pCount,
            &phDrivers
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_driver_get_api_version_params_t in_params = {
            &hDriver,
            &version
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetApiVersionCb )
                    table.pfnGetApiVersionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetApiVersion( hDriver, version );

        // capture parameters
        ze_driver_get_api_version_params_t out_params = {
            &hDriver,
            &version
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetApiVersionCb )
                    table.pfnGetApiVersionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_driver_get_properties_params_t in_params = {
            &hDriver,
            &pDriverProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetProperties( hDriver, pDriverProperties );

        // capture parameters
        ze_driver_get_properties_params_t out_params = {
            &hDriver,
            &pDriverProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIpcProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [out] query result for IPC properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_ipc_properties_params_t in_params = {
            &hDriver,
            &pIpcProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetIpcPropertiesCb )
                    table.pfnGetIpcPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetIpcProperties( hDriver, pIpcProperties );

        // capture parameters
        ze_driver_get_ipc_properties_params_t out_params = {
            &hDriver,
            &pIpcProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetIpcPropertiesCb )
                    table.pfnGetIpcPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of extension properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< extension properties.
                                                        ///< if count is larger than the number of extension properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< extension properties available.
        ze_driver_extension_properties_t* pExtensionProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< extension properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_driver_get_extension_properties_params_t in_params = {
            &hDriver,
            &pCount,
            &pExtensionProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Driver;
                if( nullptr != table.pfnGetExtensionPropertiesCb )
                    table.pfnGetExtensionPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDriverGetExtensionProperties( hDriver, pCount, pExtensionProperties );

        // capture parameters
        ze_driver_get_extension_properties_params_t out_params = {
            &hDriver,
            &pCount,
            &pExtensionProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Driver;
                if( nullptr != table.pfnGetExtensionPropertiesCb )
                    table.pfnGetExtensionPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    __zedlllocal ze_result_t ZE_APICALL
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

        // capture parameters
        ze_device_get_params_t in_params = {
            &hDriver,
            &pCount,
            &phDevices
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGet( hDriver, pCount, phDevices );

        // capture parameters
        ze_device_get_params_t out_params = {
            &hDriver,
            &pCount,
            &phDevices
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetCb )
                    table.pfnGetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetSubDevices
    __zedlllocal ze_result_t ZE_APICALL
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

        // capture parameters
        ze_device_get_sub_devices_params_t in_params = {
            &hDevice,
            &pCount,
            &phSubdevices
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetSubDevicesCb )
                    table.pfnGetSubDevicesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetSubDevices( hDevice, pCount, phSubdevices );

        // capture parameters
        ze_device_get_sub_devices_params_t out_params = {
            &hDevice,
            &pCount,
            &phSubdevices
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetSubDevicesCb )
                    table.pfnGetSubDevicesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_device_get_properties_params_t in_params = {
            &hDevice,
            &pDeviceProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetProperties( hDevice, pDeviceProperties );

        // capture parameters
        ze_device_get_properties_params_t out_params = {
            &hDevice,
            &pDeviceProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_get_compute_properties_params_t in_params = {
            &hDevice,
            &pComputeProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetComputePropertiesCb )
                    table.pfnGetComputePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetComputeProperties( hDevice, pComputeProperties );

        // capture parameters
        ze_device_get_compute_properties_params_t out_params = {
            &hDevice,
            &pComputeProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetComputePropertiesCb )
                    table.pfnGetComputePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_get_module_properties_params_t in_params = {
            &hDevice,
            &pModuleProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetModulePropertiesCb )
                    table.pfnGetModulePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetModuleProperties( hDevice, pModuleProperties );

        // capture parameters
        ze_device_get_module_properties_params_t out_params = {
            &hDevice,
            &pModuleProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetModulePropertiesCb )
                    table.pfnGetModulePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCommandQueueGroupProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCommandQueueGroupProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of command queue group properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< command queue group properties.
                                                        ///< if count is larger than the number of command queue group properties
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of command queue group properties available.
        ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< command queue group properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_command_queue_group_properties_params_t in_params = {
            &hDevice,
            &pCount,
            &pCommandQueueGroupProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetCommandQueueGroupPropertiesCb )
                    table.pfnGetCommandQueueGroupPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );

        // capture parameters
        ze_device_get_command_queue_group_properties_params_t out_params = {
            &hDevice,
            &pCount,
            &pCommandQueueGroupProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetCommandQueueGroupPropertiesCb )
                    table.pfnGetCommandQueueGroupPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
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

        // capture parameters
        ze_device_get_memory_properties_params_t in_params = {
            &hDevice,
            &pCount,
            &pMemProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetMemoryPropertiesCb )
                    table.pfnGetMemoryPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetMemoryProperties( hDevice, pCount, pMemProperties );

        // capture parameters
        ze_device_get_memory_properties_params_t out_params = {
            &hDevice,
            &pCount,
            &pMemProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetMemoryPropertiesCb )
                    table.pfnGetMemoryPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_get_memory_access_properties_params_t in_params = {
            &hDevice,
            &pMemAccessProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                    table.pfnGetMemoryAccessPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetMemoryAccessProperties( hDevice, pMemAccessProperties );

        // capture parameters
        ze_device_get_memory_access_properties_params_t out_params = {
            &hDevice,
            &pMemAccessProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetMemoryAccessPropertiesCb )
                    table.pfnGetMemoryAccessPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of cache properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< cache properties.
                                                        ///< if count is larger than the number of cache properties available, then
                                                        ///< the driver will update the value with the correct number of cache
                                                        ///< properties available.
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for cache
                                                        ///< properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_device_get_cache_properties_params_t in_params = {
            &hDevice,
            &pCount,
            &pCacheProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetCachePropertiesCb )
                    table.pfnGetCachePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetCacheProperties( hDevice, pCount, pCacheProperties );

        // capture parameters
        ze_device_get_cache_properties_params_t out_params = {
            &hDevice,
            &pCount,
            &pCacheProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetCachePropertiesCb )
                    table.pfnGetCachePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_get_image_properties_params_t in_params = {
            &hDevice,
            &pImageProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetImagePropertiesCb )
                    table.pfnGetImagePropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetImageProperties( hDevice, pImageProperties );

        // capture parameters
        ze_device_get_image_properties_params_t out_params = {
            &hDevice,
            &pImageProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetImagePropertiesCb )
                    table.pfnGetImagePropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_get_external_memory_properties_params_t in_params = {
            &hDevice,
            &pExternalMemoryProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetExternalMemoryPropertiesCb )
                    table.pfnGetExternalMemoryPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );

        // capture parameters
        ze_device_get_external_memory_properties_params_t out_params = {
            &hDevice,
            &pExternalMemoryProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetExternalMemoryPropertiesCb )
                    table.pfnGetExternalMemoryPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_get_p2_p_properties_params_t in_params = {
            &hDevice,
            &hPeerDevice,
            &pP2PProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetP2PPropertiesCb )
                    table.pfnGetP2PPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );

        // capture parameters
        ze_device_get_p2_p_properties_params_t out_params = {
            &hDevice,
            &hPeerDevice,
            &pP2PProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetP2PPropertiesCb )
                    table.pfnGetP2PPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_can_access_peer_params_t in_params = {
            &hDevice,
            &hPeerDevice,
            &value
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnCanAccessPeerCb )
                    table.pfnCanAccessPeerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceCanAccessPeer( hDevice, hPeerDevice, value );

        // capture parameters
        ze_device_can_access_peer_params_t out_params = {
            &hDevice,
            &hPeerDevice,
            &value
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnCanAccessPeerCb )
                    table.pfnCanAccessPeerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_device_get_status_params_t in_params = {
            &hDevice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Device;
                if( nullptr != table.pfnGetStatusCb )
                    table.pfnGetStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeDeviceGetStatus( hDevice );

        // capture parameters
        ze_device_get_status_params_t out_params = {
            &hDevice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Device;
                if( nullptr != table.pfnGetStatusCb )
                    table.pfnGetStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_context_create_params_t in_params = {
            &hDriver,
            &desc,
            &phContext
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextCreate( hDriver, desc, phContext );

        // capture parameters
        ze_context_create_params_t out_params = {
            &hDriver,
            &desc,
            &phContext
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_context_destroy_params_t in_params = {
            &hContext
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextDestroy( hContext );

        // capture parameters
        ze_context_destroy_params_t out_params = {
            &hContext
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_context_get_status_params_t in_params = {
            &hContext
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnGetStatusCb )
                    table.pfnGetStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextGetStatus( hContext );

        // capture parameters
        ze_context_get_status_params_t out_params = {
            &hContext
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnGetStatusCb )
                    table.pfnGetStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_queue_create_params_t in_params = {
            &hContext,
            &hDevice,
            &desc,
            &phCommandQueue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueCreate( hContext, hDevice, desc, phCommandQueue );

        // capture parameters
        ze_command_queue_create_params_t out_params = {
            &hContext,
            &hDevice,
            &desc,
            &phCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_command_queue_destroy_params_t in_params = {
            &hCommandQueue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueDestroy( hCommandQueue );

        // capture parameters
        ze_command_queue_destroy_params_t out_params = {
            &hCommandQueue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_queue_execute_command_lists_params_t in_params = {
            &hCommandQueue,
            &numCommandLists,
            &phCommandLists,
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnExecuteCommandListsCb )
                    table.pfnExecuteCommandListsCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );

        // capture parameters
        ze_command_queue_execute_command_lists_params_t out_params = {
            &hCommandQueue,
            &numCommandLists,
            &phCommandLists,
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnExecuteCommandListsCb )
                    table.pfnExecuteCommandListsCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_queue_synchronize_params_t in_params = {
            &hCommandQueue,
            &timeout
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandQueue;
                if( nullptr != table.pfnSynchronizeCb )
                    table.pfnSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandQueueSynchronize( hCommandQueue, timeout );

        // capture parameters
        ze_command_queue_synchronize_params_t out_params = {
            &hCommandQueue,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandQueue;
                if( nullptr != table.pfnSynchronizeCb )
                    table.pfnSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_create_params_t in_params = {
            &hContext,
            &hDevice,
            &desc,
            &phCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListCreate( hContext, hDevice, desc, phCommandList );

        // capture parameters
        ze_command_list_create_params_t out_params = {
            &hContext,
            &hDevice,
            &desc,
            &phCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_command_list_create_immediate_params_t in_params = {
            &hContext,
            &hDevice,
            &altdesc,
            &phCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnCreateImmediateCb )
                    table.pfnCreateImmediateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListCreateImmediate( hContext, hDevice, altdesc, phCommandList );

        // capture parameters
        ze_command_list_create_immediate_params_t out_params = {
            &hContext,
            &hDevice,
            &altdesc,
            &phCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCreateImmediateCb )
                    table.pfnCreateImmediateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_command_list_destroy_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListDestroy( hCommandList );

        // capture parameters
        ze_command_list_destroy_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_close_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListClose( hCommandList );

        // capture parameters
        ze_command_list_close_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnCloseCb )
                    table.pfnCloseCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_reset_params_t in_params = {
            &hCommandList
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListReset( hCommandList );

        // capture parameters
        ze_command_list_reset_params_t out_params = {
            &hCommandList
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_write_global_timestamp_params_t in_params = {
            &hCommandList,
            &dstptr,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendWriteGlobalTimestampCb )
                    table.pfnAppendWriteGlobalTimestampCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_write_global_timestamp_params_t out_params = {
            &hCommandList,
            &dstptr,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendWriteGlobalTimestampCb )
                    table.pfnAppendWriteGlobalTimestampCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_barrier_params_t in_params = {
            &hCommandList,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendBarrierCb )
                    table.pfnAppendBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_barrier_params_t out_params = {
            &hCommandList,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendBarrierCb )
                    table.pfnAppendBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_memory_ranges_barrier_params_t in_params = {
            &hCommandList,
            &numRanges,
            &pRangeSizes,
            &pRanges,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                    table.pfnAppendMemoryRangesBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_memory_ranges_barrier_params_t out_params = {
            &hCommandList,
            &numRanges,
            &pRangeSizes,
            &pRanges,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryRangesBarrierCb )
                    table.pfnAppendMemoryRangesBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_context_system_barrier_params_t in_params = {
            &hContext,
            &hDevice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnSystemBarrierCb )
                    table.pfnSystemBarrierCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextSystemBarrier( hContext, hDevice );

        // capture parameters
        ze_context_system_barrier_params_t out_params = {
            &hContext,
            &hDevice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnSystemBarrierCb )
                    table.pfnSystemBarrierCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_memory_copy_params_t in_params = {
            &hCommandList,
            &dstptr,
            &srcptr,
            &size,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyCb )
                    table.pfnAppendMemoryCopyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_memory_copy_params_t out_params = {
            &hCommandList,
            &dstptr,
            &srcptr,
            &size,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyCb )
                    table.pfnAppendMemoryCopyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_memory_fill_params_t in_params = {
            &hCommandList,
            &ptr,
            &pattern,
            &pattern_size,
            &size,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryFillCb )
                    table.pfnAppendMemoryFillCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_memory_fill_params_t out_params = {
            &hCommandList,
            &ptr,
            &pattern,
            &pattern_size,
            &size,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryFillCb )
                    table.pfnAppendMemoryFillCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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
                                                        ///< copies where ::ze_copy_region_t.depth is not 0, otherwise it's
                                                        ///< ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t.depth is not 0, otherwise it's
                                                        ///< ignored.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_command_list_append_memory_copy_region_params_t in_params = {
            &hCommandList,
            &dstptr,
            &dstRegion,
            &dstPitch,
            &dstSlicePitch,
            &srcptr,
            &srcRegion,
            &srcPitch,
            &srcSlicePitch,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                    table.pfnAppendMemoryCopyRegionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_memory_copy_region_params_t out_params = {
            &hCommandList,
            &dstptr,
            &dstRegion,
            &dstPitch,
            &dstSlicePitch,
            &srcptr,
            &srcRegion,
            &srcPitch,
            &srcSlicePitch,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyRegionCb )
                    table.pfnAppendMemoryCopyRegionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_memory_copy_from_context_params_t in_params = {
            &hCommandList,
            &dstptr,
            &hContextSrc,
            &srcptr,
            &size,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyFromContextCb )
                    table.pfnAppendMemoryCopyFromContextCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_memory_copy_from_context_params_t out_params = {
            &hCommandList,
            &dstptr,
            &hContextSrc,
            &srcptr,
            &size,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryCopyFromContextCb )
                    table.pfnAppendMemoryCopyFromContextCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_image_copy_params_t in_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyCb )
                    table.pfnAppendImageCopyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_image_copy_params_t out_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyCb )
                    table.pfnAppendImageCopyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_image_copy_region_params_t in_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &pDstRegion,
            &pSrcRegion,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyRegionCb )
                    table.pfnAppendImageCopyRegionCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_image_copy_region_params_t out_params = {
            &hCommandList,
            &hDstImage,
            &hSrcImage,
            &pDstRegion,
            &pSrcRegion,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyRegionCb )
                    table.pfnAppendImageCopyRegionCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_image_copy_to_memory_params_t in_params = {
            &hCommandList,
            &dstptr,
            &hSrcImage,
            &pSrcRegion,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                    table.pfnAppendImageCopyToMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_image_copy_to_memory_params_t out_params = {
            &hCommandList,
            &dstptr,
            &hSrcImage,
            &pSrcRegion,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyToMemoryCb )
                    table.pfnAppendImageCopyToMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_image_copy_from_memory_params_t in_params = {
            &hCommandList,
            &hDstImage,
            &srcptr,
            &pDstRegion,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                    table.pfnAppendImageCopyFromMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_image_copy_from_memory_params_t out_params = {
            &hCommandList,
            &hDstImage,
            &srcptr,
            &pDstRegion,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendImageCopyFromMemoryCb )
                    table.pfnAppendImageCopyFromMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_memory_prefetch_params_t in_params = {
            &hCommandList,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryPrefetchCb )
                    table.pfnAppendMemoryPrefetchCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemoryPrefetch( hCommandList, ptr, size );

        // capture parameters
        ze_command_list_append_memory_prefetch_params_t out_params = {
            &hCommandList,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemoryPrefetchCb )
                    table.pfnAppendMemoryPrefetchCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_mem_advise_params_t in_params = {
            &hCommandList,
            &hDevice,
            &ptr,
            &size,
            &advice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendMemAdviseCb )
                    table.pfnAppendMemAdviseCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );

        // capture parameters
        ze_command_list_append_mem_advise_params_t out_params = {
            &hCommandList,
            &hDevice,
            &ptr,
            &size,
            &advice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendMemAdviseCb )
                    table.pfnAppendMemAdviseCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_pool_create_params_t in_params = {
            &hContext,
            &desc,
            &numDevices,
            &phDevices,
            &phEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolCreate( hContext, desc, numDevices, phDevices, phEventPool );

        // capture parameters
        ze_event_pool_create_params_t out_params = {
            &hContext,
            &desc,
            &numDevices,
            &phDevices,
            &phEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_event_pool_destroy_params_t in_params = {
            &hEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolDestroy( hEventPool );

        // capture parameters
        ze_event_pool_destroy_params_t out_params = {
            &hEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_create_params_t in_params = {
            &hEventPool,
            &desc,
            &phEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventCreate( hEventPool, desc, phEvent );

        // capture parameters
        ze_event_create_params_t out_params = {
            &hEventPool,
            &desc,
            &phEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_event_destroy_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventDestroy( hEvent );

        // capture parameters
        ze_event_destroy_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_pool_get_ipc_handle_params_t in_params = {
            &hEventPool,
            &phIpc
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolGetIpcHandle( hEventPool, phIpc );

        // capture parameters
        ze_event_pool_get_ipc_handle_params_t out_params = {
            &hEventPool,
            &phIpc
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_pool_open_ipc_handle_params_t in_params = {
            &hContext,
            &hIpc,
            &phEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolOpenIpcHandle( hContext, hIpc, phEventPool );

        // capture parameters
        ze_event_pool_open_ipc_handle_params_t out_params = {
            &hContext,
            &hIpc,
            &phEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_event_pool_close_ipc_handle_params_t in_params = {
            &hEventPool
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.EventPool;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventPoolCloseIpcHandle( hEventPool );

        // capture parameters
        ze_event_pool_close_ipc_handle_params_t out_params = {
            &hEventPool
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.EventPool;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_signal_event_params_t in_params = {
            &hCommandList,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendSignalEventCb )
                    table.pfnAppendSignalEventCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendSignalEvent( hCommandList, hEvent );

        // capture parameters
        ze_command_list_append_signal_event_params_t out_params = {
            &hCommandList,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendSignalEventCb )
                    table.pfnAppendSignalEventCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_wait_on_events_params_t in_params = {
            &hCommandList,
            &numEvents,
            &phEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendWaitOnEventsCb )
                    table.pfnAppendWaitOnEventsCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendWaitOnEvents( hCommandList, numEvents, phEvents );

        // capture parameters
        ze_command_list_append_wait_on_events_params_t out_params = {
            &hCommandList,
            &numEvents,
            &phEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendWaitOnEventsCb )
                    table.pfnAppendWaitOnEventsCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_host_signal_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnHostSignalCb )
                    table.pfnHostSignalCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventHostSignal( hEvent );

        // capture parameters
        ze_event_host_signal_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnHostSignalCb )
                    table.pfnHostSignalCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_event_host_synchronize_params_t in_params = {
            &hEvent,
            &timeout
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventHostSynchronize( hEvent, timeout );

        // capture parameters
        ze_event_host_synchronize_params_t out_params = {
            &hEvent,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_query_status_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventQueryStatus( hEvent );

        // capture parameters
        ze_event_query_status_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_event_reset_params_t in_params = {
            &hCommandList,
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendEventResetCb )
                    table.pfnAppendEventResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendEventReset( hCommandList, hEvent );

        // capture parameters
        ze_command_list_append_event_reset_params_t out_params = {
            &hCommandList,
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendEventResetCb )
                    table.pfnAppendEventResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_host_reset_params_t in_params = {
            &hEvent
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnHostResetCb )
                    table.pfnHostResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventHostReset( hEvent );

        // capture parameters
        ze_event_host_reset_params_t out_params = {
            &hEvent
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnHostResetCb )
                    table.pfnHostResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_event_query_kernel_timestamp_params_t in_params = {
            &hEvent,
            &dstptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Event;
                if( nullptr != table.pfnQueryKernelTimestampCb )
                    table.pfnQueryKernelTimestampCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeEventQueryKernelTimestamp( hEvent, dstptr );

        // capture parameters
        ze_event_query_kernel_timestamp_params_t out_params = {
            &hEvent,
            &dstptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Event;
                if( nullptr != table.pfnQueryKernelTimestampCb )
                    table.pfnQueryKernelTimestampCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_query_kernel_timestamps_params_t in_params = {
            &hCommandList,
            &numEvents,
            &phEvents,
            &dstptr,
            &pOffsets,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendQueryKernelTimestampsCb )
                    table.pfnAppendQueryKernelTimestampsCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_query_kernel_timestamps_params_t out_params = {
            &hCommandList,
            &numEvents,
            &phEvents,
            &dstptr,
            &pOffsets,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendQueryKernelTimestampsCb )
                    table.pfnAppendQueryKernelTimestampsCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_fence_create_params_t in_params = {
            &hCommandQueue,
            &desc,
            &phFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceCreate( hCommandQueue, desc, phFence );

        // capture parameters
        ze_fence_create_params_t out_params = {
            &hCommandQueue,
            &desc,
            &phFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_fence_destroy_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceDestroy( hFence );

        // capture parameters
        ze_fence_destroy_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_fence_host_synchronize_params_t in_params = {
            &hFence,
            &timeout
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceHostSynchronize( hFence, timeout );

        // capture parameters
        ze_fence_host_synchronize_params_t out_params = {
            &hFence,
            &timeout
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnHostSynchronizeCb )
                    table.pfnHostSynchronizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_fence_query_status_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceQueryStatus( hFence );

        // capture parameters
        ze_fence_query_status_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnQueryStatusCb )
                    table.pfnQueryStatusCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_fence_reset_params_t in_params = {
            &hFence
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Fence;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeFenceReset( hFence );

        // capture parameters
        ze_fence_reset_params_t out_params = {
            &hFence
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Fence;
                if( nullptr != table.pfnResetCb )
                    table.pfnResetCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_image_get_properties_params_t in_params = {
            &hDevice,
            &desc,
            &pImageProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Image;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeImageGetProperties( hDevice, desc, pImageProperties );

        // capture parameters
        ze_image_get_properties_params_t out_params = {
            &hDevice,
            &desc,
            &pImageProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Image;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_image_create_params_t in_params = {
            &hContext,
            &hDevice,
            &desc,
            &phImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Image;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeImageCreate( hContext, hDevice, desc, phImage );

        // capture parameters
        ze_image_create_params_t out_params = {
            &hContext,
            &hDevice,
            &desc,
            &phImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Image;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_image_destroy_params_t in_params = {
            &hImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Image;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeImageDestroy( hImage );

        // capture parameters
        ze_image_destroy_params_t out_params = {
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Image;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocShared
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocShared(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_mem_alloc_shared_params_t in_params = {
            &hContext,
            &device_desc,
            &host_desc,
            &size,
            &alignment,
            &hDevice,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnAllocSharedCb )
                    table.pfnAllocSharedCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );

        // capture parameters
        ze_mem_alloc_shared_params_t out_params = {
            &hContext,
            &device_desc,
            &host_desc,
            &size,
            &alignment,
            &hDevice,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnAllocSharedCb )
                    table.pfnAllocSharedCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocDevice(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_mem_alloc_device_params_t in_params = {
            &hContext,
            &device_desc,
            &size,
            &alignment,
            &hDevice,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnAllocDeviceCb )
                    table.pfnAllocDeviceCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );

        // capture parameters
        ze_mem_alloc_device_params_t out_params = {
            &hContext,
            &device_desc,
            &size,
            &alignment,
            &hDevice,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnAllocDeviceCb )
                    table.pfnAllocDeviceCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocHost
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocHost(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_mem_alloc_host_params_t in_params = {
            &hContext,
            &host_desc,
            &size,
            &alignment,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnAllocHostCb )
                    table.pfnAllocHostCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemAllocHost( hContext, host_desc, size, alignment, pptr );

        // capture parameters
        ze_mem_alloc_host_params_t out_params = {
            &hContext,
            &host_desc,
            &size,
            &alignment,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnAllocHostCb )
                    table.pfnAllocHostCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_mem_free_params_t in_params = {
            &hContext,
            &ptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnFreeCb )
                    table.pfnFreeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemFree( hContext, ptr );

        // capture parameters
        ze_mem_free_params_t out_params = {
            &hContext,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnFreeCb )
                    table.pfnFreeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_mem_get_alloc_properties_params_t in_params = {
            &hContext,
            &ptr,
            &pMemAllocProperties,
            &phDevice
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnGetAllocPropertiesCb )
                    table.pfnGetAllocPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );

        // capture parameters
        ze_mem_get_alloc_properties_params_t out_params = {
            &hContext,
            &ptr,
            &pMemAllocProperties,
            &phDevice
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnGetAllocPropertiesCb )
                    table.pfnGetAllocPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_mem_get_address_range_params_t in_params = {
            &hContext,
            &ptr,
            &pBase,
            &pSize
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnGetAddressRangeCb )
                    table.pfnGetAddressRangeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemGetAddressRange( hContext, ptr, pBase, pSize );

        // capture parameters
        ze_mem_get_address_range_params_t out_params = {
            &hContext,
            &ptr,
            &pBase,
            &pSize
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnGetAddressRangeCb )
                    table.pfnGetAddressRangeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_mem_get_ipc_handle_params_t in_params = {
            &hContext,
            &ptr,
            &pIpcHandle
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemGetIpcHandle( hContext, ptr, pIpcHandle );

        // capture parameters
        ze_mem_get_ipc_handle_params_t out_params = {
            &hContext,
            &ptr,
            &pIpcHandle
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnGetIpcHandleCb )
                    table.pfnGetIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_mem_open_ipc_handle_params_t in_params = {
            &hContext,
            &hDevice,
            &handle,
            &flags,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemOpenIpcHandle( hContext, hDevice, handle, flags, pptr );

        // capture parameters
        ze_mem_open_ipc_handle_params_t out_params = {
            &hContext,
            &hDevice,
            &handle,
            &flags,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnOpenIpcHandleCb )
                    table.pfnOpenIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_mem_close_ipc_handle_params_t in_params = {
            &hContext,
            &ptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Mem;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeMemCloseIpcHandle( hContext, ptr );

        // capture parameters
        ze_mem_close_ipc_handle_params_t out_params = {
            &hContext,
            &ptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Mem;
                if( nullptr != table.pfnCloseIpcHandleCb )
                    table.pfnCloseIpcHandleCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_create_params_t in_params = {
            &hContext,
            &hDevice,
            &desc,
            &phModule,
            &phBuildLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleCreate( hContext, hDevice, desc, phModule, phBuildLog );

        // capture parameters
        ze_module_create_params_t out_params = {
            &hContext,
            &hDevice,
            &desc,
            &phModule,
            &phBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_module_destroy_params_t in_params = {
            &hModule
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleDestroy( hModule );

        // capture parameters
        ze_module_destroy_params_t out_params = {
            &hModule
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_dynamic_link_params_t in_params = {
            &numModules,
            &phModules,
            &phLinkLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnDynamicLinkCb )
                    table.pfnDynamicLinkCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleDynamicLink( numModules, phModules, phLinkLog );

        // capture parameters
        ze_module_dynamic_link_params_t out_params = {
            &numModules,
            &phModules,
            &phLinkLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnDynamicLinkCb )
                    table.pfnDynamicLinkCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_build_log_destroy_params_t in_params = {
            &hModuleBuildLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.ModuleBuildLog;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleBuildLogDestroy( hModuleBuildLog );

        // capture parameters
        ze_module_build_log_destroy_params_t out_params = {
            &hModuleBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.ModuleBuildLog;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_build_log_get_string_params_t in_params = {
            &hModuleBuildLog,
            &pSize,
            &pBuildLog
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.ModuleBuildLog;
                if( nullptr != table.pfnGetStringCb )
                    table.pfnGetStringCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleBuildLogGetString( hModuleBuildLog, pSize, pBuildLog );

        // capture parameters
        ze_module_build_log_get_string_params_t out_params = {
            &hModuleBuildLog,
            &pSize,
            &pBuildLog
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.ModuleBuildLog;
                if( nullptr != table.pfnGetStringCb )
                    table.pfnGetStringCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_get_native_binary_params_t in_params = {
            &hModule,
            &pSize,
            &pModuleNativeBinary
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetNativeBinaryCb )
                    table.pfnGetNativeBinaryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetNativeBinary( hModule, pSize, pModuleNativeBinary );

        // capture parameters
        ze_module_get_native_binary_params_t out_params = {
            &hModule,
            &pSize,
            &pModuleNativeBinary
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetNativeBinaryCb )
                    table.pfnGetNativeBinaryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_get_global_pointer_params_t in_params = {
            &hModule,
            &pGlobalName,
            &pSize,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetGlobalPointerCb )
                    table.pfnGetGlobalPointerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetGlobalPointer( hModule, pGlobalName, pSize, pptr );

        // capture parameters
        ze_module_get_global_pointer_params_t out_params = {
            &hModule,
            &pGlobalName,
            &pSize,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetGlobalPointerCb )
                    table.pfnGetGlobalPointerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetKernelNames
    __zedlllocal ze_result_t ZE_APICALL
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

        // capture parameters
        ze_module_get_kernel_names_params_t in_params = {
            &hModule,
            &pCount,
            &pNames
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetKernelNamesCb )
                    table.pfnGetKernelNamesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetKernelNames( hModule, pCount, pNames );

        // capture parameters
        ze_module_get_kernel_names_params_t out_params = {
            &hModule,
            &pCount,
            &pNames
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetKernelNamesCb )
                    table.pfnGetKernelNamesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_get_properties_params_t in_params = {
            &hModule,
            &pModuleProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetProperties( hModule, pModuleProperties );

        // capture parameters
        ze_module_get_properties_params_t out_params = {
            &hModule,
            &pModuleProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_create_params_t in_params = {
            &hModule,
            &desc,
            &phKernel
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelCreate( hModule, desc, phKernel );

        // capture parameters
        ze_kernel_create_params_t out_params = {
            &hModule,
            &desc,
            &phKernel
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_kernel_destroy_params_t in_params = {
            &hKernel
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelDestroy( hKernel );

        // capture parameters
        ze_kernel_destroy_params_t out_params = {
            &hKernel
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_module_get_function_pointer_params_t in_params = {
            &hModule,
            &pFunctionName,
            &pfnFunction
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Module;
                if( nullptr != table.pfnGetFunctionPointerCb )
                    table.pfnGetFunctionPointerCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeModuleGetFunctionPointer( hModule, pFunctionName, pfnFunction );

        // capture parameters
        ze_module_get_function_pointer_params_t out_params = {
            &hModule,
            &pFunctionName,
            &pfnFunction
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Module;
                if( nullptr != table.pfnGetFunctionPointerCb )
                    table.pfnGetFunctionPointerCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_set_group_size_params_t in_params = {
            &hKernel,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetGroupSizeCb )
                    table.pfnSetGroupSizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );

        // capture parameters
        ze_kernel_set_group_size_params_t out_params = {
            &hKernel,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetGroupSizeCb )
                    table.pfnSetGroupSizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_suggest_group_size_params_t in_params = {
            &hKernel,
            &globalSizeX,
            &globalSizeY,
            &globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSuggestGroupSizeCb )
                    table.pfnSuggestGroupSizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );

        // capture parameters
        ze_kernel_suggest_group_size_params_t out_params = {
            &hKernel,
            &globalSizeX,
            &globalSizeY,
            &globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSuggestGroupSizeCb )
                    table.pfnSuggestGroupSizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_suggest_max_cooperative_group_count_params_t in_params = {
            &hKernel,
            &totalGroupCount
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSuggestMaxCooperativeGroupCountCb )
                    table.pfnSuggestMaxCooperativeGroupCountCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );

        // capture parameters
        ze_kernel_suggest_max_cooperative_group_count_params_t out_params = {
            &hKernel,
            &totalGroupCount
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSuggestMaxCooperativeGroupCountCb )
                    table.pfnSuggestMaxCooperativeGroupCountCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_set_argument_value_params_t in_params = {
            &hKernel,
            &argIndex,
            &argSize,
            &pArgValue
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetArgumentValueCb )
                    table.pfnSetArgumentValueCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetArgumentValue( hKernel, argIndex, argSize, pArgValue );

        // capture parameters
        ze_kernel_set_argument_value_params_t out_params = {
            &hKernel,
            &argIndex,
            &argSize,
            &pArgValue
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetArgumentValueCb )
                    table.pfnSetArgumentValueCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_set_indirect_access_params_t in_params = {
            &hKernel,
            &flags
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetIndirectAccessCb )
                    table.pfnSetIndirectAccessCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetIndirectAccess( hKernel, flags );

        // capture parameters
        ze_kernel_set_indirect_access_params_t out_params = {
            &hKernel,
            &flags
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetIndirectAccessCb )
                    table.pfnSetIndirectAccessCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_get_indirect_access_params_t in_params = {
            &hKernel,
            &pFlags
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnGetIndirectAccessCb )
                    table.pfnGetIndirectAccessCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelGetIndirectAccess( hKernel, pFlags );

        // capture parameters
        ze_kernel_get_indirect_access_params_t out_params = {
            &hKernel,
            &pFlags
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnGetIndirectAccessCb )
                    table.pfnGetIndirectAccessCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetSourceAttributes
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetSourceAttributes(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes.
                                                        ///< if size is zero, then the driver will update string argument.
                                                        ///< if size is non-zero, then driver will only retrieve string size in bytes.
                                                        ///< if size is larger than source attributes string, then the driver will
                                                        ///< update the string.
        char** pString                                  ///< [in,out][optional] pointer to null-terminated string where kernel
                                                        ///< source attributes are separated by space.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_kernel_get_source_attributes_params_t in_params = {
            &hKernel,
            &pSize,
            &pString
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnGetSourceAttributesCb )
                    table.pfnGetSourceAttributesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelGetSourceAttributes( hKernel, pSize, pString );

        // capture parameters
        ze_kernel_get_source_attributes_params_t out_params = {
            &hKernel,
            &pSize,
            &pString
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnGetSourceAttributesCb )
                    table.pfnGetSourceAttributesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_set_cache_config_params_t in_params = {
            &hKernel,
            &flags
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnSetCacheConfigCb )
                    table.pfnSetCacheConfigCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelSetCacheConfig( hKernel, flags );

        // capture parameters
        ze_kernel_set_cache_config_params_t out_params = {
            &hKernel,
            &flags
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnSetCacheConfigCb )
                    table.pfnSetCacheConfigCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_get_properties_params_t in_params = {
            &hKernel,
            &pKernelProperties
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelGetProperties( hKernel, pKernelProperties );

        // capture parameters
        ze_kernel_get_properties_params_t out_params = {
            &hKernel,
            &pKernelProperties
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnGetPropertiesCb )
                    table.pfnGetPropertiesCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_kernel_get_name_params_t in_params = {
            &hKernel,
            &pSize,
            &pName
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Kernel;
                if( nullptr != table.pfnGetNameCb )
                    table.pfnGetNameCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeKernelGetName( hKernel, pSize, pName );

        // capture parameters
        ze_kernel_get_name_params_t out_params = {
            &hKernel,
            &pSize,
            &pName
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Kernel;
                if( nullptr != table.pfnGetNameCb )
                    table.pfnGetNameCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_launch_kernel_params_t in_params = {
            &hCommandList,
            &hKernel,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelCb )
                    table.pfnAppendLaunchKernelCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_kernel_params_t out_params = {
            &hCommandList,
            &hKernel,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelCb )
                    table.pfnAppendLaunchKernelCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_launch_cooperative_kernel_params_t in_params = {
            &hCommandList,
            &hKernel,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchCooperativeKernelCb )
                    table.pfnAppendLaunchCooperativeKernelCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_cooperative_kernel_params_t out_params = {
            &hCommandList,
            &hKernel,
            &pLaunchFuncArgs,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchCooperativeKernelCb )
                    table.pfnAppendLaunchCooperativeKernelCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_command_list_append_launch_kernel_indirect_params_t in_params = {
            &hCommandList,
            &hKernel,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelIndirectCb )
                    table.pfnAppendLaunchKernelIndirectCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_kernel_indirect_params_t out_params = {
            &hCommandList,
            &hKernel,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchKernelIndirectCb )
                    table.pfnAppendLaunchKernelIndirectCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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
                                                        ///< number of kernels to launch; value must be less-than or equal-to
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

        // capture parameters
        ze_command_list_append_launch_multiple_kernels_indirect_params_t in_params = {
            &hCommandList,
            &numKernels,
            &phKernels,
            &pCountBuffer,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchMultipleKernelsIndirectCb )
                    table.pfnAppendLaunchMultipleKernelsIndirectCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeCommandListAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        // capture parameters
        ze_command_list_append_launch_multiple_kernels_indirect_params_t out_params = {
            &hCommandList,
            &numKernels,
            &phKernels,
            &pCountBuffer,
            &pLaunchArgumentsBuffer,
            &hSignalEvent,
            &numWaitEvents,
            &phWaitEvents
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.CommandList;
                if( nullptr != table.pfnAppendLaunchMultipleKernelsIndirectCb )
                    table.pfnAppendLaunchMultipleKernelsIndirectCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_context_make_memory_resident_params_t in_params = {
            &hContext,
            &hDevice,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnMakeMemoryResidentCb )
                    table.pfnMakeMemoryResidentCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextMakeMemoryResident( hContext, hDevice, ptr, size );

        // capture parameters
        ze_context_make_memory_resident_params_t out_params = {
            &hContext,
            &hDevice,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnMakeMemoryResidentCb )
                    table.pfnMakeMemoryResidentCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_context_evict_memory_params_t in_params = {
            &hContext,
            &hDevice,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnEvictMemoryCb )
                    table.pfnEvictMemoryCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextEvictMemory( hContext, hDevice, ptr, size );

        // capture parameters
        ze_context_evict_memory_params_t out_params = {
            &hContext,
            &hDevice,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnEvictMemoryCb )
                    table.pfnEvictMemoryCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_context_make_image_resident_params_t in_params = {
            &hContext,
            &hDevice,
            &hImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnMakeImageResidentCb )
                    table.pfnMakeImageResidentCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextMakeImageResident( hContext, hDevice, hImage );

        // capture parameters
        ze_context_make_image_resident_params_t out_params = {
            &hContext,
            &hDevice,
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnMakeImageResidentCb )
                    table.pfnMakeImageResidentCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_context_evict_image_params_t in_params = {
            &hContext,
            &hDevice,
            &hImage
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Context;
                if( nullptr != table.pfnEvictImageCb )
                    table.pfnEvictImageCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeContextEvictImage( hContext, hDevice, hImage );

        // capture parameters
        ze_context_evict_image_params_t out_params = {
            &hContext,
            &hDevice,
            &hImage
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Context;
                if( nullptr != table.pfnEvictImageCb )
                    table.pfnEvictImageCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_sampler_create_params_t in_params = {
            &hContext,
            &hDevice,
            &desc,
            &phSampler
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Sampler;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeSamplerCreate( hContext, hDevice, desc, phSampler );

        // capture parameters
        ze_sampler_create_params_t out_params = {
            &hContext,
            &hDevice,
            &desc,
            &phSampler
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Sampler;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_sampler_destroy_params_t in_params = {
            &hSampler
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.Sampler;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeSamplerDestroy( hSampler );

        // capture parameters
        ze_sampler_destroy_params_t out_params = {
            &hSampler
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.Sampler;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemReserve
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemReserve(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // capture parameters
        ze_virtual_mem_reserve_params_t in_params = {
            &hContext,
            &pStart,
            &size,
            &pptr
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.VirtualMem;
                if( nullptr != table.pfnReserveCb )
                    table.pfnReserveCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeVirtualMemReserve( hContext, pStart, size, pptr );

        // capture parameters
        ze_virtual_mem_reserve_params_t out_params = {
            &hContext,
            &pStart,
            &size,
            &pptr
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.VirtualMem;
                if( nullptr != table.pfnReserveCb )
                    table.pfnReserveCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_virtual_mem_free_params_t in_params = {
            &hContext,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.VirtualMem;
                if( nullptr != table.pfnFreeCb )
                    table.pfnFreeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeVirtualMemFree( hContext, ptr, size );

        // capture parameters
        ze_virtual_mem_free_params_t out_params = {
            &hContext,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.VirtualMem;
                if( nullptr != table.pfnFreeCb )
                    table.pfnFreeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_virtual_mem_query_page_size_params_t in_params = {
            &hContext,
            &hDevice,
            &size,
            &pagesize
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.VirtualMem;
                if( nullptr != table.pfnQueryPageSizeCb )
                    table.pfnQueryPageSizeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeVirtualMemQueryPageSize( hContext, hDevice, size, pagesize );

        // capture parameters
        ze_virtual_mem_query_page_size_params_t out_params = {
            &hContext,
            &hDevice,
            &size,
            &pagesize
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.VirtualMem;
                if( nullptr != table.pfnQueryPageSizeCb )
                    table.pfnQueryPageSizeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_physical_mem_create_params_t in_params = {
            &hContext,
            &hDevice,
            &desc,
            &phPhysicalMemory
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.PhysicalMem;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zePhysicalMemCreate( hContext, hDevice, desc, phPhysicalMemory );

        // capture parameters
        ze_physical_mem_create_params_t out_params = {
            &hContext,
            &hDevice,
            &desc,
            &phPhysicalMemory
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.PhysicalMem;
                if( nullptr != table.pfnCreateCb )
                    table.pfnCreateCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
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

        // capture parameters
        ze_physical_mem_destroy_params_t in_params = {
            &hContext,
            &hPhysicalMemory
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.PhysicalMem;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zePhysicalMemDestroy( hContext, hPhysicalMemory );

        // capture parameters
        ze_physical_mem_destroy_params_t out_params = {
            &hContext,
            &hPhysicalMemory
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.PhysicalMem;
                if( nullptr != table.pfnDestroyCb )
                    table.pfnDestroyCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_virtual_mem_map_params_t in_params = {
            &hContext,
            &ptr,
            &size,
            &hPhysicalMemory,
            &offset,
            &access
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.VirtualMem;
                if( nullptr != table.pfnMapCb )
                    table.pfnMapCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeVirtualMemMap( hContext, ptr, size, hPhysicalMemory, offset, access );

        // capture parameters
        ze_virtual_mem_map_params_t out_params = {
            &hContext,
            &ptr,
            &size,
            &hPhysicalMemory,
            &offset,
            &access
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.VirtualMem;
                if( nullptr != table.pfnMapCb )
                    table.pfnMapCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_virtual_mem_unmap_params_t in_params = {
            &hContext,
            &ptr,
            &size
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.VirtualMem;
                if( nullptr != table.pfnUnmapCb )
                    table.pfnUnmapCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeVirtualMemUnmap( hContext, ptr, size );

        // capture parameters
        ze_virtual_mem_unmap_params_t out_params = {
            &hContext,
            &ptr,
            &size
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.VirtualMem;
                if( nullptr != table.pfnUnmapCb )
                    table.pfnUnmapCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_virtual_mem_set_access_attribute_params_t in_params = {
            &hContext,
            &ptr,
            &size,
            &access
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.VirtualMem;
                if( nullptr != table.pfnSetAccessAttributeCb )
                    table.pfnSetAccessAttributeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeVirtualMemSetAccessAttribute( hContext, ptr, size, access );

        // capture parameters
        ze_virtual_mem_set_access_attribute_params_t out_params = {
            &hContext,
            &ptr,
            &size,
            &access
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.VirtualMem;
                if( nullptr != table.pfnSetAccessAttributeCb )
                    table.pfnSetAccessAttributeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

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

        // capture parameters
        ze_virtual_mem_get_access_attribute_params_t in_params = {
            &hContext,
            &ptr,
            &size,
            &access,
            &outSize
        };

        // create storage locations for callbacks
        std::vector<void*> instanceUserData;
        instanceUserData.resize( context.tracerData.size() );

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zePrologueCbs.VirtualMem;
                if( nullptr != table.pfnGetAccessAttributeCb )
                    table.pfnGetAccessAttributeCb( &in_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        result = driver::zeVirtualMemGetAccessAttribute( hContext, ptr, size, access, outSize );

        // capture parameters
        ze_virtual_mem_get_access_attribute_params_t out_params = {
            &hContext,
            &ptr,
            &size,
            &access,
            &outSize
        };

        // call each callback registered
        for( uint32_t i = 0; i < context.tracerData.size(); ++i )
            if( context.tracerData[ i ].enabled )
            {
                auto& table = context.tracerData[ i ].zeEpilogueCbs.VirtualMem;
                if( nullptr != table.pfnGetAccessAttributeCb )
                    table.pfnGetAccessAttributeCb( &out_params, result,
                        context.tracerData[ i ].userData,
                        &instanceUserData[ i ] );
            }

        return result;
    }

} // namespace instrumented

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
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnInit                                   = instrumented::zeInit;
    else
        pDdiTable->pfnInit                                   = driver::zeInit;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGet                                    = instrumented::zeDriverGet;
    else
        pDdiTable->pfnGet                                    = driver::zeDriverGet;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetApiVersion                          = instrumented::zeDriverGetApiVersion;
    else
        pDdiTable->pfnGetApiVersion                          = driver::zeDriverGetApiVersion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeDriverGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeDriverGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIpcProperties                       = instrumented::zeDriverGetIpcProperties;
    else
        pDdiTable->pfnGetIpcProperties                       = driver::zeDriverGetIpcProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetExtensionProperties                 = instrumented::zeDriverGetExtensionProperties;
    else
        pDdiTable->pfnGetExtensionProperties                 = driver::zeDriverGetExtensionProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGet                                    = instrumented::zeDeviceGet;
    else
        pDdiTable->pfnGet                                    = driver::zeDeviceGet;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetSubDevices                          = instrumented::zeDeviceGetSubDevices;
    else
        pDdiTable->pfnGetSubDevices                          = driver::zeDeviceGetSubDevices;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeDeviceGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeDeviceGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetComputeProperties                   = instrumented::zeDeviceGetComputeProperties;
    else
        pDdiTable->pfnGetComputeProperties                   = driver::zeDeviceGetComputeProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetModuleProperties                    = instrumented::zeDeviceGetModuleProperties;
    else
        pDdiTable->pfnGetModuleProperties                    = driver::zeDeviceGetModuleProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetCommandQueueGroupProperties         = instrumented::zeDeviceGetCommandQueueGroupProperties;
    else
        pDdiTable->pfnGetCommandQueueGroupProperties         = driver::zeDeviceGetCommandQueueGroupProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemoryProperties                    = instrumented::zeDeviceGetMemoryProperties;
    else
        pDdiTable->pfnGetMemoryProperties                    = driver::zeDeviceGetMemoryProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetMemoryAccessProperties              = instrumented::zeDeviceGetMemoryAccessProperties;
    else
        pDdiTable->pfnGetMemoryAccessProperties              = driver::zeDeviceGetMemoryAccessProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetCacheProperties                     = instrumented::zeDeviceGetCacheProperties;
    else
        pDdiTable->pfnGetCacheProperties                     = driver::zeDeviceGetCacheProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetImageProperties                     = instrumented::zeDeviceGetImageProperties;
    else
        pDdiTable->pfnGetImageProperties                     = driver::zeDeviceGetImageProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetExternalMemoryProperties            = instrumented::zeDeviceGetExternalMemoryProperties;
    else
        pDdiTable->pfnGetExternalMemoryProperties            = driver::zeDeviceGetExternalMemoryProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetP2PProperties                       = instrumented::zeDeviceGetP2PProperties;
    else
        pDdiTable->pfnGetP2PProperties                       = driver::zeDeviceGetP2PProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCanAccessPeer                          = instrumented::zeDeviceCanAccessPeer;
    else
        pDdiTable->pfnCanAccessPeer                          = driver::zeDeviceCanAccessPeer;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetStatus                              = instrumented::zeDeviceGetStatus;
    else
        pDdiTable->pfnGetStatus                              = driver::zeDeviceGetStatus;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_context_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeContextCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeContextCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeContextDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeContextDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetStatus                              = instrumented::zeContextGetStatus;
    else
        pDdiTable->pfnGetStatus                              = driver::zeContextGetStatus;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSystemBarrier                          = instrumented::zeContextSystemBarrier;
    else
        pDdiTable->pfnSystemBarrier                          = driver::zeContextSystemBarrier;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnMakeMemoryResident                     = instrumented::zeContextMakeMemoryResident;
    else
        pDdiTable->pfnMakeMemoryResident                     = driver::zeContextMakeMemoryResident;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnEvictMemory                            = instrumented::zeContextEvictMemory;
    else
        pDdiTable->pfnEvictMemory                            = driver::zeContextEvictMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnMakeImageResident                      = instrumented::zeContextMakeImageResident;
    else
        pDdiTable->pfnMakeImageResident                      = driver::zeContextMakeImageResident;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnEvictImage                             = instrumented::zeContextEvictImage;
    else
        pDdiTable->pfnEvictImage                             = driver::zeContextEvictImage;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeCommandQueueCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeCommandQueueCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeCommandQueueDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeCommandQueueDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnExecuteCommandLists                    = instrumented::zeCommandQueueExecuteCommandLists;
    else
        pDdiTable->pfnExecuteCommandLists                    = driver::zeCommandQueueExecuteCommandLists;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSynchronize                            = instrumented::zeCommandQueueSynchronize;
    else
        pDdiTable->pfnSynchronize                            = driver::zeCommandQueueSynchronize;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeCommandListCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeCommandListCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreateImmediate                        = instrumented::zeCommandListCreateImmediate;
    else
        pDdiTable->pfnCreateImmediate                        = driver::zeCommandListCreateImmediate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeCommandListDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeCommandListDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnClose                                  = instrumented::zeCommandListClose;
    else
        pDdiTable->pfnClose                                  = driver::zeCommandListClose;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::zeCommandListReset;
    else
        pDdiTable->pfnReset                                  = driver::zeCommandListReset;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendWriteGlobalTimestamp             = instrumented::zeCommandListAppendWriteGlobalTimestamp;
    else
        pDdiTable->pfnAppendWriteGlobalTimestamp             = driver::zeCommandListAppendWriteGlobalTimestamp;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendBarrier                          = instrumented::zeCommandListAppendBarrier;
    else
        pDdiTable->pfnAppendBarrier                          = driver::zeCommandListAppendBarrier;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryRangesBarrier              = instrumented::zeCommandListAppendMemoryRangesBarrier;
    else
        pDdiTable->pfnAppendMemoryRangesBarrier              = driver::zeCommandListAppendMemoryRangesBarrier;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryCopy                       = instrumented::zeCommandListAppendMemoryCopy;
    else
        pDdiTable->pfnAppendMemoryCopy                       = driver::zeCommandListAppendMemoryCopy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryFill                       = instrumented::zeCommandListAppendMemoryFill;
    else
        pDdiTable->pfnAppendMemoryFill                       = driver::zeCommandListAppendMemoryFill;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryCopyRegion                 = instrumented::zeCommandListAppendMemoryCopyRegion;
    else
        pDdiTable->pfnAppendMemoryCopyRegion                 = driver::zeCommandListAppendMemoryCopyRegion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryCopyFromContext            = instrumented::zeCommandListAppendMemoryCopyFromContext;
    else
        pDdiTable->pfnAppendMemoryCopyFromContext            = driver::zeCommandListAppendMemoryCopyFromContext;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopy                        = instrumented::zeCommandListAppendImageCopy;
    else
        pDdiTable->pfnAppendImageCopy                        = driver::zeCommandListAppendImageCopy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyRegion                  = instrumented::zeCommandListAppendImageCopyRegion;
    else
        pDdiTable->pfnAppendImageCopyRegion                  = driver::zeCommandListAppendImageCopyRegion;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyToMemory                = instrumented::zeCommandListAppendImageCopyToMemory;
    else
        pDdiTable->pfnAppendImageCopyToMemory                = driver::zeCommandListAppendImageCopyToMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendImageCopyFromMemory              = instrumented::zeCommandListAppendImageCopyFromMemory;
    else
        pDdiTable->pfnAppendImageCopyFromMemory              = driver::zeCommandListAppendImageCopyFromMemory;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemoryPrefetch                   = instrumented::zeCommandListAppendMemoryPrefetch;
    else
        pDdiTable->pfnAppendMemoryPrefetch                   = driver::zeCommandListAppendMemoryPrefetch;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendMemAdvise                        = instrumented::zeCommandListAppendMemAdvise;
    else
        pDdiTable->pfnAppendMemAdvise                        = driver::zeCommandListAppendMemAdvise;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendSignalEvent                      = instrumented::zeCommandListAppendSignalEvent;
    else
        pDdiTable->pfnAppendSignalEvent                      = driver::zeCommandListAppendSignalEvent;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendWaitOnEvents                     = instrumented::zeCommandListAppendWaitOnEvents;
    else
        pDdiTable->pfnAppendWaitOnEvents                     = driver::zeCommandListAppendWaitOnEvents;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendEventReset                       = instrumented::zeCommandListAppendEventReset;
    else
        pDdiTable->pfnAppendEventReset                       = driver::zeCommandListAppendEventReset;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendQueryKernelTimestamps            = instrumented::zeCommandListAppendQueryKernelTimestamps;
    else
        pDdiTable->pfnAppendQueryKernelTimestamps            = driver::zeCommandListAppendQueryKernelTimestamps;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchKernel                     = instrumented::zeCommandListAppendLaunchKernel;
    else
        pDdiTable->pfnAppendLaunchKernel                     = driver::zeCommandListAppendLaunchKernel;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchCooperativeKernel          = instrumented::zeCommandListAppendLaunchCooperativeKernel;
    else
        pDdiTable->pfnAppendLaunchCooperativeKernel          = driver::zeCommandListAppendLaunchCooperativeKernel;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchKernelIndirect             = instrumented::zeCommandListAppendLaunchKernelIndirect;
    else
        pDdiTable->pfnAppendLaunchKernelIndirect             = driver::zeCommandListAppendLaunchKernelIndirect;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = instrumented::zeCommandListAppendLaunchMultipleKernelsIndirect;
    else
        pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = driver::zeCommandListAppendLaunchMultipleKernelsIndirect;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeEventCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeEventCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeEventDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeEventDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSignal                             = instrumented::zeEventHostSignal;
    else
        pDdiTable->pfnHostSignal                             = driver::zeEventHostSignal;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSynchronize                        = instrumented::zeEventHostSynchronize;
    else
        pDdiTable->pfnHostSynchronize                        = driver::zeEventHostSynchronize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryStatus                            = instrumented::zeEventQueryStatus;
    else
        pDdiTable->pfnQueryStatus                            = driver::zeEventQueryStatus;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostReset                              = instrumented::zeEventHostReset;
    else
        pDdiTable->pfnHostReset                              = driver::zeEventHostReset;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryKernelTimestamp                   = instrumented::zeEventQueryKernelTimestamp;
    else
        pDdiTable->pfnQueryKernelTimestamp                   = driver::zeEventQueryKernelTimestamp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeEventPoolCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeEventPoolCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeEventPoolDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeEventPoolDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIpcHandle                           = instrumented::zeEventPoolGetIpcHandle;
    else
        pDdiTable->pfnGetIpcHandle                           = driver::zeEventPoolGetIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnOpenIpcHandle                          = instrumented::zeEventPoolOpenIpcHandle;
    else
        pDdiTable->pfnOpenIpcHandle                          = driver::zeEventPoolOpenIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCloseIpcHandle                         = instrumented::zeEventPoolCloseIpcHandle;
    else
        pDdiTable->pfnCloseIpcHandle                         = driver::zeEventPoolCloseIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeFenceCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeFenceCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeFenceDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeFenceDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnHostSynchronize                        = instrumented::zeFenceHostSynchronize;
    else
        pDdiTable->pfnHostSynchronize                        = driver::zeFenceHostSynchronize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryStatus                            = instrumented::zeFenceQueryStatus;
    else
        pDdiTable->pfnQueryStatus                            = driver::zeFenceQueryStatus;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReset                                  = instrumented::zeFenceReset;
    else
        pDdiTable->pfnReset                                  = driver::zeFenceReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeImageGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeImageGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeImageCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeImageCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeImageDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeImageDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeKernelCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeKernelCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeKernelDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeKernelDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetCacheConfig                         = instrumented::zeKernelSetCacheConfig;
    else
        pDdiTable->pfnSetCacheConfig                         = driver::zeKernelSetCacheConfig;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetGroupSize                           = instrumented::zeKernelSetGroupSize;
    else
        pDdiTable->pfnSetGroupSize                           = driver::zeKernelSetGroupSize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSuggestGroupSize                       = instrumented::zeKernelSuggestGroupSize;
    else
        pDdiTable->pfnSuggestGroupSize                       = driver::zeKernelSuggestGroupSize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSuggestMaxCooperativeGroupCount        = instrumented::zeKernelSuggestMaxCooperativeGroupCount;
    else
        pDdiTable->pfnSuggestMaxCooperativeGroupCount        = driver::zeKernelSuggestMaxCooperativeGroupCount;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetArgumentValue                       = instrumented::zeKernelSetArgumentValue;
    else
        pDdiTable->pfnSetArgumentValue                       = driver::zeKernelSetArgumentValue;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetIndirectAccess                      = instrumented::zeKernelSetIndirectAccess;
    else
        pDdiTable->pfnSetIndirectAccess                      = driver::zeKernelSetIndirectAccess;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIndirectAccess                      = instrumented::zeKernelGetIndirectAccess;
    else
        pDdiTable->pfnGetIndirectAccess                      = driver::zeKernelGetIndirectAccess;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetSourceAttributes                    = instrumented::zeKernelGetSourceAttributes;
    else
        pDdiTable->pfnGetSourceAttributes                    = driver::zeKernelGetSourceAttributes;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeKernelGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeKernelGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetName                                = instrumented::zeKernelGetName;
    else
        pDdiTable->pfnGetName                                = driver::zeKernelGetName;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Mem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_mem_dditable_t* pDdiTable                    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocShared                            = instrumented::zeMemAllocShared;
    else
        pDdiTable->pfnAllocShared                            = driver::zeMemAllocShared;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocDevice                            = instrumented::zeMemAllocDevice;
    else
        pDdiTable->pfnAllocDevice                            = driver::zeMemAllocDevice;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnAllocHost                              = instrumented::zeMemAllocHost;
    else
        pDdiTable->pfnAllocHost                              = driver::zeMemAllocHost;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnFree                                   = instrumented::zeMemFree;
    else
        pDdiTable->pfnFree                                   = driver::zeMemFree;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetAllocProperties                     = instrumented::zeMemGetAllocProperties;
    else
        pDdiTable->pfnGetAllocProperties                     = driver::zeMemGetAllocProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetAddressRange                        = instrumented::zeMemGetAddressRange;
    else
        pDdiTable->pfnGetAddressRange                        = driver::zeMemGetAddressRange;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetIpcHandle                           = instrumented::zeMemGetIpcHandle;
    else
        pDdiTable->pfnGetIpcHandle                           = driver::zeMemGetIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnOpenIpcHandle                          = instrumented::zeMemOpenIpcHandle;
    else
        pDdiTable->pfnOpenIpcHandle                          = driver::zeMemOpenIpcHandle;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCloseIpcHandle                         = instrumented::zeMemCloseIpcHandle;
    else
        pDdiTable->pfnCloseIpcHandle                         = driver::zeMemCloseIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeModuleCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeModuleCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeModuleDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeModuleDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDynamicLink                            = instrumented::zeModuleDynamicLink;
    else
        pDdiTable->pfnDynamicLink                            = driver::zeModuleDynamicLink;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetNativeBinary                        = instrumented::zeModuleGetNativeBinary;
    else
        pDdiTable->pfnGetNativeBinary                        = driver::zeModuleGetNativeBinary;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetGlobalPointer                       = instrumented::zeModuleGetGlobalPointer;
    else
        pDdiTable->pfnGetGlobalPointer                       = driver::zeModuleGetGlobalPointer;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetKernelNames                         = instrumented::zeModuleGetKernelNames;
    else
        pDdiTable->pfnGetKernelNames                         = driver::zeModuleGetKernelNames;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetProperties                          = instrumented::zeModuleGetProperties;
    else
        pDdiTable->pfnGetProperties                          = driver::zeModuleGetProperties;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetFunctionPointer                     = instrumented::zeModuleGetFunctionPointer;
    else
        pDdiTable->pfnGetFunctionPointer                     = driver::zeModuleGetFunctionPointer;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeModuleBuildLogDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeModuleBuildLogDestroy;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetString                              = instrumented::zeModuleBuildLogGetString;
    else
        pDdiTable->pfnGetString                              = driver::zeModuleBuildLogGetString;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PhysicalMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetPhysicalMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_physical_mem_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zePhysicalMemCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zePhysicalMemCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zePhysicalMemDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zePhysicalMemDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnCreate                                 = instrumented::zeSamplerCreate;
    else
        pDdiTable->pfnCreate                                 = driver::zeSamplerCreate;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnDestroy                                = instrumented::zeSamplerDestroy;
    else
        pDdiTable->pfnDestroy                                = driver::zeSamplerDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's VirtualMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetVirtualMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_virtual_mem_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnReserve                                = instrumented::zeVirtualMemReserve;
    else
        pDdiTable->pfnReserve                                = driver::zeVirtualMemReserve;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnFree                                   = instrumented::zeVirtualMemFree;
    else
        pDdiTable->pfnFree                                   = driver::zeVirtualMemFree;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnQueryPageSize                          = instrumented::zeVirtualMemQueryPageSize;
    else
        pDdiTable->pfnQueryPageSize                          = driver::zeVirtualMemQueryPageSize;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnMap                                    = instrumented::zeVirtualMemMap;
    else
        pDdiTable->pfnMap                                    = driver::zeVirtualMemMap;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnUnmap                                  = instrumented::zeVirtualMemUnmap;
    else
        pDdiTable->pfnUnmap                                  = driver::zeVirtualMemUnmap;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnSetAccessAttribute                     = instrumented::zeVirtualMemSetAccessAttribute;
    else
        pDdiTable->pfnSetAccessAttribute                     = driver::zeVirtualMemSetAccessAttribute;

    if( instrumented::context.enableTracing )
        pDdiTable->pfnGetAccessAttribute                     = instrumented::zeVirtualMemGetAccessAttribute;
    else
        pDdiTable->pfnGetAccessAttribute                     = driver::zeVirtualMemGetAccessAttribute;

    return result;
}

#if defined(__cplusplus)
};
#endif
