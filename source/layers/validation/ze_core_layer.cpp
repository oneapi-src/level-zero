/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    ze_result_t __zecall
    zeInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        auto pfnInit = context.zeDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( 1 <= flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnInit( flags );
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
        auto pfnGet = context.zeDdiTable.Driver.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( pCount, phDrivers );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetApiVersion
    ze_result_t __zecall
    zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        auto pfnGetApiVersion = context.zeDdiTable.Driver.pfnGetApiVersion;

        if( nullptr == pfnGetApiVersion )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == version )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetApiVersion( hDriver, version );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetProperties
    ze_result_t __zecall
    zeDriverGetProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Driver.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pDriverProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hDriver, pDriverProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIPCProperties
    ze_result_t __zecall
    zeDriverGetIPCProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
        )
    {
        auto pfnGetIPCProperties = context.zeDdiTable.Driver.pfnGetIPCProperties;

        if( nullptr == pfnGetIPCProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pIPCProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetIPCProperties( hDriver, pIPCProperties );
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
        auto pfnGetExtensionFunctionAddress = context.zeDdiTable.Driver.pfnGetExtensionFunctionAddress;

        if( nullptr == pfnGetExtensionFunctionAddress )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pFuncName )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pfunc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetExtensionFunctionAddress( hDriver, pFuncName, pfunc );
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
        auto pfnGet = context.zeDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hDriver, pCount, phDevices );
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
        auto pfnGetSubDevices = context.zeDdiTable.Device.pfnGetSubDevices;

        if( nullptr == pfnGetSubDevices )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetSubDevices( hDevice, pCount, phSubdevices );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetProperties
    ze_result_t __zecall
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pDeviceProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hDevice, pDeviceProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetComputeProperties
    ze_result_t __zecall
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        auto pfnGetComputeProperties = context.zeDdiTable.Device.pfnGetComputeProperties;

        if( nullptr == pfnGetComputeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pComputeProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetComputeProperties( hDevice, pComputeProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetKernelProperties
    ze_result_t __zecall
    zeDeviceGetKernelProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_kernel_properties_t* pKernelProperties///< [in,out] query result for kernel properties
        )
    {
        auto pfnGetKernelProperties = context.zeDdiTable.Device.pfnGetKernelProperties;

        if( nullptr == pfnGetKernelProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pKernelProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetKernelProperties( hDevice, pKernelProperties );
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
        auto pfnGetMemoryProperties = context.zeDdiTable.Device.pfnGetMemoryProperties;

        if( nullptr == pfnGetMemoryProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    ze_result_t __zecall
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        auto pfnGetMemoryAccessProperties = context.zeDdiTable.Device.pfnGetMemoryAccessProperties;

        if( nullptr == pfnGetMemoryAccessProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pMemAccessProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    ze_result_t __zecall
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
        )
    {
        auto pfnGetCacheProperties = context.zeDdiTable.Device.pfnGetCacheProperties;

        if( nullptr == pfnGetCacheProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCacheProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetCacheProperties( hDevice, pCacheProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetImageProperties
    ze_result_t __zecall
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        auto pfnGetImageProperties = context.zeDdiTable.Device.pfnGetImageProperties;

        if( nullptr == pfnGetImageProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pImageProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetImageProperties( hDevice, pImageProperties );
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
        auto pfnGetP2PProperties = context.zeDdiTable.Device.pfnGetP2PProperties;

        if( nullptr == pfnGetP2PProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hPeerDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pP2PProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
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
        auto pfnCanAccessPeer = context.zeDdiTable.Device.pfnCanAccessPeer;

        if( nullptr == pfnCanAccessPeer )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hPeerDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == value )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnCanAccessPeer( hDevice, hPeerDevice, value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSetLastLevelCacheConfig
    ze_result_t __zecall
    zeDeviceSetLastLevelCacheConfig(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device 
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        auto pfnSetLastLevelCacheConfig = context.zeDdiTable.Device.pfnSetLastLevelCacheConfig;

        if( nullptr == pfnSetLastLevelCacheConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 4 <= CacheConfig )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
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
        auto pfnCreate = context.zeDdiTable.CommandQueue.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phCommandQueue )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 8 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 2 <= desc->mode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 2 <= desc->priority )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDevice, desc, phCommandQueue );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueDestroy
    ze_result_t __zecall
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.CommandQueue.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hCommandQueue );
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
        auto pfnExecuteCommandLists = context.zeDdiTable.CommandQueue.pfnExecuteCommandLists;

        if( nullptr == pfnExecuteCommandLists )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phCommandLists )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( 0 == numCommandLists )
                return ZE_RESULT_ERROR_INVALID_SIZE;

        }

        return pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
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
        auto pfnSynchronize = context.zeDdiTable.CommandQueue.pfnSynchronize;

        if( nullptr == pfnSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSynchronize( hCommandQueue, timeout );
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
        auto pfnCreate = context.zeDdiTable.CommandList.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 8 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDevice, desc, phCommandList );
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
        auto pfnCreateImmediate = context.zeDdiTable.CommandList.pfnCreateImmediate;

        if( nullptr == pfnCreateImmediate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == altdesc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT < altdesc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 8 <= altdesc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 2 <= altdesc->mode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 2 <= altdesc->priority )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreateImmediate( hDevice, altdesc, phCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListDestroy
    ze_result_t __zecall
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.CommandList.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListClose
    ze_result_t __zecall
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        auto pfnClose = context.zeDdiTable.CommandList.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnClose( hCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListReset
    ze_result_t __zecall
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        auto pfnReset = context.zeDdiTable.CommandList.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnReset( hCommandList );
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
        auto pfnAppendBarrier = context.zeDdiTable.CommandList.pfnAppendBarrier;

        if( nullptr == pfnAppendBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendMemoryRangesBarrier = context.zeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;

        if( nullptr == pfnAppendMemoryRangesBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRangeSizes )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pRanges )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSystemBarrier
    ze_result_t __zecall
    zeDeviceSystemBarrier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        auto pfnSystemBarrier = context.zeDdiTable.Device.pfnSystemBarrier;

        if( nullptr == pfnSystemBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSystemBarrier( hDevice );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLMemory
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLMemory(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context clContext,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
        )
    {
        auto pfnRegisterCLMemory = context.zeDdiTable.Device.pfnRegisterCLMemory;

        if( nullptr == pfnRegisterCLMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRegisterCLMemory( hDevice, clContext, mem, ptr );
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLProgram
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLProgram(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context clContext,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        ze_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
        )
    {
        auto pfnRegisterCLProgram = context.zeDdiTable.Device.pfnRegisterCLProgram;

        if( nullptr == pfnRegisterCLProgram )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phModule )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRegisterCLProgram( hDevice, clContext, program, phModule );
    }
    #endif // ZE_ENABLE_OCL_INTEROP

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceRegisterCLCommandQueue
    #if ZE_ENABLE_OCL_INTEROP
    ze_result_t __zecall
    zeDeviceRegisterCLCommandQueue(
        ze_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context clContext,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        auto pfnRegisterCLCommandQueue = context.zeDdiTable.Device.pfnRegisterCLCommandQueue;

        if( nullptr == pfnRegisterCLCommandQueue )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phCommandQueue )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRegisterCLCommandQueue( hDevice, clContext, command_queue, phCommandQueue );
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
        auto pfnAppendMemoryCopy = context.zeDdiTable.CommandList.pfnAppendMemoryCopy;

        if( nullptr == pfnAppendMemoryCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == dstptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == srcptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
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
        auto pfnAppendMemoryFill = context.zeDdiTable.CommandList.pfnAppendMemoryFill;

        if( nullptr == pfnAppendMemoryFill )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pattern )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hEvent );
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
        auto pfnAppendMemoryCopyRegion = context.zeDdiTable.CommandList.pfnAppendMemoryCopyRegion;

        if( nullptr == pfnAppendMemoryCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == dstptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == dstRegion )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == srcptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == srcRegion )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hEvent );
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
        auto pfnAppendImageCopy = context.zeDdiTable.CommandList.pfnAppendImageCopy;

        if( nullptr == pfnAppendImageCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hDstImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hSrcImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
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
        auto pfnAppendImageCopyRegion = context.zeDdiTable.CommandList.pfnAppendImageCopyRegion;

        if( nullptr == pfnAppendImageCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hDstImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hSrcImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
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
        auto pfnAppendImageCopyToMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemory;

        if( nullptr == pfnAppendImageCopyToMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hSrcImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == dstptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
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
        auto pfnAppendImageCopyFromMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemory;

        if( nullptr == pfnAppendImageCopyFromMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hDstImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == srcptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
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
        auto pfnAppendMemoryPrefetch = context.zeDdiTable.CommandList.pfnAppendMemoryPrefetch;

        if( nullptr == pfnAppendMemoryPrefetch )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendMemoryPrefetch( hCommandList, ptr, size );
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
        auto pfnAppendMemAdvise = context.zeDdiTable.CommandList.pfnAppendMemAdvise;

        if( nullptr == pfnAppendMemAdvise )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( 9 <= advice )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
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
        auto pfnCreate = context.zeDdiTable.EventPool.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phEventPool )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 4 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDriver, desc, numDevices, phDevices, phEventPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolDestroy
    ze_result_t __zecall
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.EventPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hEventPool );
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
        auto pfnCreate = context.zeDdiTable.Event.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_EVENT_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 4 <= desc->signal )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 4 <= desc->wait )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hEventPool, desc, phEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventDestroy
    ze_result_t __zecall
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Event.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    ze_result_t __zecall
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        auto pfnGetIpcHandle = context.zeDdiTable.EventPool.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phIpc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetIpcHandle( hEventPool, phIpc );
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
        auto pfnOpenIpcHandle = context.zeDdiTable.EventPool.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phEventPool )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOpenIpcHandle( hDriver, hIpc, phEventPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCloseIpcHandle
    ze_result_t __zecall
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        auto pfnCloseIpcHandle = context.zeDdiTable.EventPool.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEventPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnCloseIpcHandle( hEventPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    ze_result_t __zecall
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendSignalEvent = context.zeDdiTable.CommandList.pfnAppendSignalEvent;

        if( nullptr == pfnAppendSignalEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendSignalEvent( hCommandList, hEvent );
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
        auto pfnAppendWaitOnEvents = context.zeDdiTable.CommandList.pfnAppendWaitOnEvents;

        if( nullptr == pfnAppendWaitOnEvents )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSignal
    ze_result_t __zecall
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnHostSignal = context.zeDdiTable.Event.pfnHostSignal;

        if( nullptr == pfnHostSignal )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnHostSignal( hEvent );
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
        auto pfnHostSynchronize = context.zeDdiTable.Event.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnHostSynchronize( hEvent, timeout );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryStatus
    ze_result_t __zecall
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnQueryStatus = context.zeDdiTable.Event.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnQueryStatus( hEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendEventReset
    ze_result_t __zecall
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendEventReset = context.zeDdiTable.CommandList.pfnAppendEventReset;

        if( nullptr == pfnAppendEventReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendEventReset( hCommandList, hEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostReset
    ze_result_t __zecall
    zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnHostReset = context.zeDdiTable.Event.pfnHostReset;

        if( nullptr == pfnHostReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnHostReset( hEvent );
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
        auto pfnGetTimestamp = context.zeDdiTable.Event.pfnGetTimestamp;

        if( nullptr == pfnGetTimestamp )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 3 <= timestampType )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == dstptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTimestamp( hEvent, timestampType, dstptr );
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
        auto pfnCreate = context.zeDdiTable.Fence.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandQueue )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phFence )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_FENCE_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 0 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hCommandQueue, desc, phFence );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceDestroy
    ze_result_t __zecall
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Fence.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hFence );
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
        auto pfnHostSynchronize = context.zeDdiTable.Fence.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnHostSynchronize( hFence, timeout );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceQueryStatus
    ze_result_t __zecall
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnQueryStatus = context.zeDdiTable.Fence.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnQueryStatus( hFence );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceReset
    ze_result_t __zecall
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnReset = context.zeDdiTable.Fence.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFence )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnReset( hFence );
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
        auto pfnGetProperties = context.zeDdiTable.Image.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pImageProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_IMAGE_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 8 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 5 <= desc->type )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnGetProperties( hDevice, desc, pImageProperties );
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
        auto pfnCreate = context.zeDdiTable.Image.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phImage )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_IMAGE_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 8 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 5 <= desc->type )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDevice, desc, phImage );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    ze_result_t __zecall
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Image.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hImage );
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
        auto pfnAllocSharedMem = context.zeDdiTable.Driver.pfnAllocSharedMem;

        if( nullptr == pfnAllocSharedMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == device_desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == host_desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT < device_desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT < host_desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 2 <= device_desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 4 <= host_desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnAllocSharedMem( hDriver, device_desc, host_desc, size, alignment, hDevice, pptr );
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
        auto pfnAllocDeviceMem = context.zeDdiTable.Driver.pfnAllocDeviceMem;

        if( nullptr == pfnAllocDeviceMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == device_desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT < device_desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 2 <= device_desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnAllocDeviceMem( hDriver, device_desc, size, alignment, hDevice, pptr );
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
        auto pfnAllocHostMem = context.zeDdiTable.Driver.pfnAllocHostMem;

        if( nullptr == pfnAllocHostMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == host_desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT < host_desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 4 <= host_desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnAllocHostMem( hDriver, host_desc, size, alignment, pptr );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverFreeMem
    ze_result_t __zecall
    zeDriverFreeMem(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto pfnFreeMem = context.zeDdiTable.Driver.pfnFreeMem;

        if( nullptr == pfnFreeMem )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFreeMem( hDriver, ptr );
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
        auto pfnGetMemAllocProperties = context.zeDdiTable.Driver.pfnGetMemAllocProperties;

        if( nullptr == pfnGetMemAllocProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pMemAllocProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMemAllocProperties( hDriver, ptr, pMemAllocProperties, phDevice );
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
        auto pfnGetMemAddressRange = context.zeDdiTable.Driver.pfnGetMemAddressRange;

        if( nullptr == pfnGetMemAddressRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMemAddressRange( hDriver, ptr, pBase, pSize );
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
        auto pfnGetMemIpcHandle = context.zeDdiTable.Driver.pfnGetMemIpcHandle;

        if( nullptr == pfnGetMemIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pIpcHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMemIpcHandle( hDriver, ptr, pIpcHandle );
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
        auto pfnOpenMemIpcHandle = context.zeDdiTable.Driver.pfnOpenMemIpcHandle;

        if( nullptr == pfnOpenMemIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 0 <= flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOpenMemIpcHandle( hDriver, hDevice, handle, flags, pptr );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverCloseMemIpcHandle
    ze_result_t __zecall
    zeDriverCloseMemIpcHandle(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto pfnCloseMemIpcHandle = context.zeDdiTable.Driver.pfnCloseMemIpcHandle;

        if( nullptr == pfnCloseMemIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnCloseMemIpcHandle( hDriver, ptr );
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
        auto pfnCreate = context.zeDdiTable.Module.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == desc->pInputModule )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == desc->pBuildFlags )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phModule )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_MODULE_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 1 <= desc->format )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 0 == desc->inputSize )
                return ZE_RESULT_ERROR_INVALID_SIZE;

        }

        return pfnCreate( hDevice, desc, phModule, phBuildLog );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDestroy
    ze_result_t __zecall
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        auto pfnDestroy = context.zeDdiTable.Module.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hModule );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogDestroy
    ze_result_t __zecall
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        auto pfnDestroy = context.zeDdiTable.ModuleBuildLog.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModuleBuildLog )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hModuleBuildLog );
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
        auto pfnGetString = context.zeDdiTable.ModuleBuildLog.pfnGetString;

        if( nullptr == pfnGetString )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModuleBuildLog )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
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
        auto pfnGetNativeBinary = context.zeDdiTable.Module.pfnGetNativeBinary;

        if( nullptr == pfnGetNativeBinary )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
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
        auto pfnGetGlobalPointer = context.zeDdiTable.Module.pfnGetGlobalPointer;

        if( nullptr == pfnGetGlobalPointer )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pGlobalName )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetGlobalPointer( hModule, pGlobalName, pptr );
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
        auto pfnGetKernelNames = context.zeDdiTable.Module.pfnGetKernelNames;

        if( nullptr == pfnGetKernelNames )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetKernelNames( hModule, pCount, pNames );
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
        auto pfnCreate = context.zeDdiTable.Kernel.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == desc->pKernelName )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == desc->pKernelName )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_KERNEL_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 1 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hModule, desc, phKernel );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelDestroy
    ze_result_t __zecall
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        auto pfnDestroy = context.zeDdiTable.Kernel.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hKernel );
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
        auto pfnGetFunctionPointer = context.zeDdiTable.Module.pfnGetFunctionPointer;

        if( nullptr == pfnGetFunctionPointer )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pFunctionName )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pfnFunction )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
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
        auto pfnSetGroupSize = context.zeDdiTable.Kernel.pfnSetGroupSize;

        if( nullptr == pfnSetGroupSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
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
        auto pfnSuggestGroupSize = context.zeDdiTable.Kernel.pfnSuggestGroupSize;

        if( nullptr == pfnSuggestGroupSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == groupSizeX )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == groupSizeY )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == groupSizeZ )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    ze_result_t __zecall
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        auto pfnSuggestMaxCooperativeGroupCount = context.zeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;

        if( nullptr == pfnSuggestMaxCooperativeGroupCount )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == totalGroupCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
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
        auto pfnSetArgumentValue = context.zeDdiTable.Kernel.pfnSetArgumentValue;

        if( nullptr == pfnSetArgumentValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
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
        auto pfnSetAttribute = context.zeDdiTable.Kernel.pfnSetAttribute;

        if( nullptr == pfnSetAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 3 <= attr )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetAttribute( hKernel, attr, size, pValue );
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
        auto pfnGetAttribute = context.zeDdiTable.Kernel.pfnGetAttribute;

        if( nullptr == pfnGetAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 3 <= attr )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetAttribute( hKernel, attr, pSize, pValue );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIntermediateCacheConfig
    ze_result_t __zecall
    zeKernelSetIntermediateCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
        )
    {
        auto pfnSetIntermediateCacheConfig = context.zeDdiTable.Kernel.pfnSetIntermediateCacheConfig;

        if( nullptr == pfnSetIntermediateCacheConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 4 <= CacheConfig )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetIntermediateCacheConfig( hKernel, CacheConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    ze_result_t __zecall
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Kernel.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pKernelProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hKernel, pKernelProperties );
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
        auto pfnAppendLaunchKernel = context.zeDdiTable.CommandList.pfnAppendLaunchKernel;

        if( nullptr == pfnAppendLaunchKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLaunchFuncArgs )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendLaunchCooperativeKernel = context.zeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel;

        if( nullptr == pfnAppendLaunchCooperativeKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLaunchFuncArgs )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendLaunchKernelIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchKernelIndirect;

        if( nullptr == pfnAppendLaunchKernelIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLaunchArgumentsBuffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnAppendLaunchMultipleKernelsIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;

        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phKernels )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pCountBuffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pLaunchArgumentsBuffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
        auto pfnMakeMemoryResident = context.zeDdiTable.Device.pfnMakeMemoryResident;

        if( nullptr == pfnMakeMemoryResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnMakeMemoryResident( hDevice, ptr, size );
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
        auto pfnEvictMemory = context.zeDdiTable.Device.pfnEvictMemory;

        if( nullptr == pfnEvictMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == ptr )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEvictMemory( hDevice, ptr, size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceMakeImageResident
    ze_result_t __zecall
    zeDeviceMakeImageResident(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        auto pfnMakeImageResident = context.zeDdiTable.Device.pfnMakeImageResident;

        if( nullptr == pfnMakeImageResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnMakeImageResident( hDevice, hImage );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceEvictImage
    ze_result_t __zecall
    zeDeviceEvictImage(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        auto pfnEvictImage = context.zeDdiTable.Device.pfnEvictImage;

        if( nullptr == pfnEvictImage )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hImage )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnEvictImage( hDevice, hImage );
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
        auto pfnCreate = context.zeDdiTable.Sampler.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phSampler )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZE_SAMPLER_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 4 <= desc->addressMode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( 1 <= desc->filterMode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDevice, desc, phSampler );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    ze_result_t __zecall
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        auto pfnDestroy = context.zeDdiTable.Sampler.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSampler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hSampler );
    }

} // namespace layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Driver;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zeDriverGet;

    dditable.pfnGetApiVersion                            = pDdiTable->pfnGetApiVersion;
    pDdiTable->pfnGetApiVersion                          = layer::zeDriverGetApiVersion;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zeDriverGetProperties;

    dditable.pfnGetIPCProperties                         = pDdiTable->pfnGetIPCProperties;
    pDdiTable->pfnGetIPCProperties                       = layer::zeDriverGetIPCProperties;

    dditable.pfnGetExtensionFunctionAddress              = pDdiTable->pfnGetExtensionFunctionAddress;
    pDdiTable->pfnGetExtensionFunctionAddress            = layer::zeDriverGetExtensionFunctionAddress;

    dditable.pfnAllocSharedMem                           = pDdiTable->pfnAllocSharedMem;
    pDdiTable->pfnAllocSharedMem                         = layer::zeDriverAllocSharedMem;

    dditable.pfnAllocDeviceMem                           = pDdiTable->pfnAllocDeviceMem;
    pDdiTable->pfnAllocDeviceMem                         = layer::zeDriverAllocDeviceMem;

    dditable.pfnAllocHostMem                             = pDdiTable->pfnAllocHostMem;
    pDdiTable->pfnAllocHostMem                           = layer::zeDriverAllocHostMem;

    dditable.pfnFreeMem                                  = pDdiTable->pfnFreeMem;
    pDdiTable->pfnFreeMem                                = layer::zeDriverFreeMem;

    dditable.pfnGetMemAllocProperties                    = pDdiTable->pfnGetMemAllocProperties;
    pDdiTable->pfnGetMemAllocProperties                  = layer::zeDriverGetMemAllocProperties;

    dditable.pfnGetMemAddressRange                       = pDdiTable->pfnGetMemAddressRange;
    pDdiTable->pfnGetMemAddressRange                     = layer::zeDriverGetMemAddressRange;

    dditable.pfnGetMemIpcHandle                          = pDdiTable->pfnGetMemIpcHandle;
    pDdiTable->pfnGetMemIpcHandle                        = layer::zeDriverGetMemIpcHandle;

    dditable.pfnOpenMemIpcHandle                         = pDdiTable->pfnOpenMemIpcHandle;
    pDdiTable->pfnOpenMemIpcHandle                       = layer::zeDriverOpenMemIpcHandle;

    dditable.pfnCloseMemIpcHandle                        = pDdiTable->pfnCloseMemIpcHandle;
    pDdiTable->pfnCloseMemIpcHandle                      = layer::zeDriverCloseMemIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = layer::zeInit;

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
__zedllexport ze_result_t __zecall
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zeDeviceGet;

    dditable.pfnGetSubDevices                            = pDdiTable->pfnGetSubDevices;
    pDdiTable->pfnGetSubDevices                          = layer::zeDeviceGetSubDevices;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zeDeviceGetProperties;

    dditable.pfnGetComputeProperties                     = pDdiTable->pfnGetComputeProperties;
    pDdiTable->pfnGetComputeProperties                   = layer::zeDeviceGetComputeProperties;

    dditable.pfnGetKernelProperties                      = pDdiTable->pfnGetKernelProperties;
    pDdiTable->pfnGetKernelProperties                    = layer::zeDeviceGetKernelProperties;

    dditable.pfnGetMemoryProperties                      = pDdiTable->pfnGetMemoryProperties;
    pDdiTable->pfnGetMemoryProperties                    = layer::zeDeviceGetMemoryProperties;

    dditable.pfnGetMemoryAccessProperties                = pDdiTable->pfnGetMemoryAccessProperties;
    pDdiTable->pfnGetMemoryAccessProperties              = layer::zeDeviceGetMemoryAccessProperties;

    dditable.pfnGetCacheProperties                       = pDdiTable->pfnGetCacheProperties;
    pDdiTable->pfnGetCacheProperties                     = layer::zeDeviceGetCacheProperties;

    dditable.pfnGetImageProperties                       = pDdiTable->pfnGetImageProperties;
    pDdiTable->pfnGetImageProperties                     = layer::zeDeviceGetImageProperties;

    dditable.pfnGetP2PProperties                         = pDdiTable->pfnGetP2PProperties;
    pDdiTable->pfnGetP2PProperties                       = layer::zeDeviceGetP2PProperties;

    dditable.pfnCanAccessPeer                            = pDdiTable->pfnCanAccessPeer;
    pDdiTable->pfnCanAccessPeer                          = layer::zeDeviceCanAccessPeer;

    dditable.pfnSetLastLevelCacheConfig                  = pDdiTable->pfnSetLastLevelCacheConfig;
    pDdiTable->pfnSetLastLevelCacheConfig                = layer::zeDeviceSetLastLevelCacheConfig;

    dditable.pfnSystemBarrier                            = pDdiTable->pfnSystemBarrier;
    pDdiTable->pfnSystemBarrier                          = layer::zeDeviceSystemBarrier;

#if ZE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLMemory                         = pDdiTable->pfnRegisterCLMemory;
    pDdiTable->pfnRegisterCLMemory                       = layer::zeDeviceRegisterCLMemory;
#else
    dditable.pfnRegisterCLMemory                         = nullptr;
    pDdiTable->pfnRegisterCLMemory                       = nullptr;
#endif

#if ZE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLProgram                        = pDdiTable->pfnRegisterCLProgram;
    pDdiTable->pfnRegisterCLProgram                      = layer::zeDeviceRegisterCLProgram;
#else
    dditable.pfnRegisterCLProgram                        = nullptr;
    pDdiTable->pfnRegisterCLProgram                      = nullptr;
#endif

#if ZE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLCommandQueue                   = pDdiTable->pfnRegisterCLCommandQueue;
    pDdiTable->pfnRegisterCLCommandQueue                 = layer::zeDeviceRegisterCLCommandQueue;
#else
    dditable.pfnRegisterCLCommandQueue                   = nullptr;
    pDdiTable->pfnRegisterCLCommandQueue                 = nullptr;
#endif

    dditable.pfnMakeMemoryResident                       = pDdiTable->pfnMakeMemoryResident;
    pDdiTable->pfnMakeMemoryResident                     = layer::zeDeviceMakeMemoryResident;

    dditable.pfnEvictMemory                              = pDdiTable->pfnEvictMemory;
    pDdiTable->pfnEvictMemory                            = layer::zeDeviceEvictMemory;

    dditable.pfnMakeImageResident                        = pDdiTable->pfnMakeImageResident;
    pDdiTable->pfnMakeImageResident                      = layer::zeDeviceMakeImageResident;

    dditable.pfnEvictImage                               = pDdiTable->pfnEvictImage;
    pDdiTable->pfnEvictImage                             = layer::zeDeviceEvictImage;

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
__zedllexport ze_result_t __zecall
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.CommandQueue;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeCommandQueueCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeCommandQueueDestroy;

    dditable.pfnExecuteCommandLists                      = pDdiTable->pfnExecuteCommandLists;
    pDdiTable->pfnExecuteCommandLists                    = layer::zeCommandQueueExecuteCommandLists;

    dditable.pfnSynchronize                              = pDdiTable->pfnSynchronize;
    pDdiTable->pfnSynchronize                            = layer::zeCommandQueueSynchronize;

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
__zedllexport ze_result_t __zecall
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeCommandListCreate;

    dditable.pfnCreateImmediate                          = pDdiTable->pfnCreateImmediate;
    pDdiTable->pfnCreateImmediate                        = layer::zeCommandListCreateImmediate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeCommandListDestroy;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = layer::zeCommandListClose;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::zeCommandListReset;

    dditable.pfnAppendBarrier                            = pDdiTable->pfnAppendBarrier;
    pDdiTable->pfnAppendBarrier                          = layer::zeCommandListAppendBarrier;

    dditable.pfnAppendMemoryRangesBarrier                = pDdiTable->pfnAppendMemoryRangesBarrier;
    pDdiTable->pfnAppendMemoryRangesBarrier              = layer::zeCommandListAppendMemoryRangesBarrier;

    dditable.pfnAppendMemoryCopy                         = pDdiTable->pfnAppendMemoryCopy;
    pDdiTable->pfnAppendMemoryCopy                       = layer::zeCommandListAppendMemoryCopy;

    dditable.pfnAppendMemoryFill                         = pDdiTable->pfnAppendMemoryFill;
    pDdiTable->pfnAppendMemoryFill                       = layer::zeCommandListAppendMemoryFill;

    dditable.pfnAppendMemoryCopyRegion                   = pDdiTable->pfnAppendMemoryCopyRegion;
    pDdiTable->pfnAppendMemoryCopyRegion                 = layer::zeCommandListAppendMemoryCopyRegion;

    dditable.pfnAppendImageCopy                          = pDdiTable->pfnAppendImageCopy;
    pDdiTable->pfnAppendImageCopy                        = layer::zeCommandListAppendImageCopy;

    dditable.pfnAppendImageCopyRegion                    = pDdiTable->pfnAppendImageCopyRegion;
    pDdiTable->pfnAppendImageCopyRegion                  = layer::zeCommandListAppendImageCopyRegion;

    dditable.pfnAppendImageCopyToMemory                  = pDdiTable->pfnAppendImageCopyToMemory;
    pDdiTable->pfnAppendImageCopyToMemory                = layer::zeCommandListAppendImageCopyToMemory;

    dditable.pfnAppendImageCopyFromMemory                = pDdiTable->pfnAppendImageCopyFromMemory;
    pDdiTable->pfnAppendImageCopyFromMemory              = layer::zeCommandListAppendImageCopyFromMemory;

    dditable.pfnAppendMemoryPrefetch                     = pDdiTable->pfnAppendMemoryPrefetch;
    pDdiTable->pfnAppendMemoryPrefetch                   = layer::zeCommandListAppendMemoryPrefetch;

    dditable.pfnAppendMemAdvise                          = pDdiTable->pfnAppendMemAdvise;
    pDdiTable->pfnAppendMemAdvise                        = layer::zeCommandListAppendMemAdvise;

    dditable.pfnAppendSignalEvent                        = pDdiTable->pfnAppendSignalEvent;
    pDdiTable->pfnAppendSignalEvent                      = layer::zeCommandListAppendSignalEvent;

    dditable.pfnAppendWaitOnEvents                       = pDdiTable->pfnAppendWaitOnEvents;
    pDdiTable->pfnAppendWaitOnEvents                     = layer::zeCommandListAppendWaitOnEvents;

    dditable.pfnAppendEventReset                         = pDdiTable->pfnAppendEventReset;
    pDdiTable->pfnAppendEventReset                       = layer::zeCommandListAppendEventReset;

    dditable.pfnAppendLaunchKernel                       = pDdiTable->pfnAppendLaunchKernel;
    pDdiTable->pfnAppendLaunchKernel                     = layer::zeCommandListAppendLaunchKernel;

    dditable.pfnAppendLaunchCooperativeKernel            = pDdiTable->pfnAppendLaunchCooperativeKernel;
    pDdiTable->pfnAppendLaunchCooperativeKernel          = layer::zeCommandListAppendLaunchCooperativeKernel;

    dditable.pfnAppendLaunchKernelIndirect               = pDdiTable->pfnAppendLaunchKernelIndirect;
    pDdiTable->pfnAppendLaunchKernelIndirect             = layer::zeCommandListAppendLaunchKernelIndirect;

    dditable.pfnAppendLaunchMultipleKernelsIndirect      = pDdiTable->pfnAppendLaunchMultipleKernelsIndirect;
    pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = layer::zeCommandListAppendLaunchMultipleKernelsIndirect;

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
__zedllexport ze_result_t __zecall
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Fence;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeFenceCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeFenceDestroy;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = layer::zeFenceHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = layer::zeFenceQueryStatus;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::zeFenceReset;

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
__zedllexport ze_result_t __zecall
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.EventPool;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeEventPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeEventPoolDestroy;

    dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
    pDdiTable->pfnGetIpcHandle                           = layer::zeEventPoolGetIpcHandle;

    dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
    pDdiTable->pfnOpenIpcHandle                          = layer::zeEventPoolOpenIpcHandle;

    dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
    pDdiTable->pfnCloseIpcHandle                         = layer::zeEventPoolCloseIpcHandle;

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
__zedllexport ze_result_t __zecall
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Event;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeEventCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeEventDestroy;

    dditable.pfnHostSignal                               = pDdiTable->pfnHostSignal;
    pDdiTable->pfnHostSignal                             = layer::zeEventHostSignal;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = layer::zeEventHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = layer::zeEventQueryStatus;

    dditable.pfnHostReset                                = pDdiTable->pfnHostReset;
    pDdiTable->pfnHostReset                              = layer::zeEventHostReset;

    dditable.pfnGetTimestamp                             = pDdiTable->pfnGetTimestamp;
    pDdiTable->pfnGetTimestamp                           = layer::zeEventGetTimestamp;

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
__zedllexport ze_result_t __zecall
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Image;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zeImageGetProperties;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeImageCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeImageDestroy;

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
__zedllexport ze_result_t __zecall
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeModuleCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeModuleDestroy;

    dditable.pfnGetNativeBinary                          = pDdiTable->pfnGetNativeBinary;
    pDdiTable->pfnGetNativeBinary                        = layer::zeModuleGetNativeBinary;

    dditable.pfnGetGlobalPointer                         = pDdiTable->pfnGetGlobalPointer;
    pDdiTable->pfnGetGlobalPointer                       = layer::zeModuleGetGlobalPointer;

    dditable.pfnGetKernelNames                           = pDdiTable->pfnGetKernelNames;
    pDdiTable->pfnGetKernelNames                         = layer::zeModuleGetKernelNames;

    dditable.pfnGetFunctionPointer                       = pDdiTable->pfnGetFunctionPointer;
    pDdiTable->pfnGetFunctionPointer                     = layer::zeModuleGetFunctionPointer;

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
__zedllexport ze_result_t __zecall
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.ModuleBuildLog;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeModuleBuildLogDestroy;

    dditable.pfnGetString                                = pDdiTable->pfnGetString;
    pDdiTable->pfnGetString                              = layer::zeModuleBuildLogGetString;

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
__zedllexport ze_result_t __zecall
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeKernelCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeKernelDestroy;

    dditable.pfnSetIntermediateCacheConfig               = pDdiTable->pfnSetIntermediateCacheConfig;
    pDdiTable->pfnSetIntermediateCacheConfig             = layer::zeKernelSetIntermediateCacheConfig;

    dditable.pfnSetGroupSize                             = pDdiTable->pfnSetGroupSize;
    pDdiTable->pfnSetGroupSize                           = layer::zeKernelSetGroupSize;

    dditable.pfnSuggestGroupSize                         = pDdiTable->pfnSuggestGroupSize;
    pDdiTable->pfnSuggestGroupSize                       = layer::zeKernelSuggestGroupSize;

    dditable.pfnSuggestMaxCooperativeGroupCount          = pDdiTable->pfnSuggestMaxCooperativeGroupCount;
    pDdiTable->pfnSuggestMaxCooperativeGroupCount        = layer::zeKernelSuggestMaxCooperativeGroupCount;

    dditable.pfnSetArgumentValue                         = pDdiTable->pfnSetArgumentValue;
    pDdiTable->pfnSetArgumentValue                       = layer::zeKernelSetArgumentValue;

    dditable.pfnSetAttribute                             = pDdiTable->pfnSetAttribute;
    pDdiTable->pfnSetAttribute                           = layer::zeKernelSetAttribute;

    dditable.pfnGetAttribute                             = pDdiTable->pfnGetAttribute;
    pDdiTable->pfnGetAttribute                           = layer::zeKernelGetAttribute;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zeKernelGetProperties;

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
__zedllexport ze_result_t __zecall
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zeDdiTable.Sampler;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zeSamplerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zeSamplerDestroy;

    return result;
}

#if defined(__cplusplus)
};
#endif
