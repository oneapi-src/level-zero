/*
 * ***THIS FILE IS GENERATED. ***
 * See handle_lifetime.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_handle_lifetime.cpp
 *
 */
#include "ze_validation_layer.h"
#include "ze_handle_lifetime.h"

namespace validation_layer
{
    ze_result_t
    ZEHandleLifetimeValidation::zeDriverGetApiVersionEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDriverGetPropertiesEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDriverGetIpcPropertiesEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDriverGetExtensionPropertiesEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDriverGetExtensionFunctionAddressEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDriverGetLastErrorDescriptionEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetRootDeviceEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetSubDevicesEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetPropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetComputePropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetModulePropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetCommandQueueGroupPropertiesEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetMemoryPropertiesEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetMemoryAccessPropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetCachePropertiesEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetImagePropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetExternalMemoryPropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetP2PPropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hPeerDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceCanAccessPeerEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hPeerDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetStatusEpilogue(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetGlobalTimestampsEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                        ///< Device's global timestamp value
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextCreateEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextCreateExEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phDevices) && (i < numDevices); ++i){
            if (!context.handleLifetime->isHandleValid( phDevices[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextDestroyEpilogue(
        ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
        )
    { 
        
        if (hContext && context.handleLifetime->isHandleValid( hContext )){
            if (context.handleLifetime->hasDependents( hContext )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hContext);
            context.handleLifetime->removeHandle( hContext );
        } else if (!context.handleLifetime->isHandleValid( hContext )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextGetStatusEpilogue(
        ze_context_handle_t hContext                    ///< [in] handle of context object
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandQueueCreateEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandQueueDestroyEpilogue(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    { 
        
        if (hCommandQueue && context.handleLifetime->isHandleValid( hCommandQueue )){
            if (context.handleLifetime->hasDependents( hCommandQueue )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hCommandQueue);
            context.handleLifetime->removeHandle( hCommandQueue );
        } else if (!context.handleLifetime->isHandleValid( hCommandQueue )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandQueueExecuteCommandListsEpilogue(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandQueue )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phCommandLists) && (i < numCommandLists); ++i){
            if (!context.handleLifetime->isHandleValid( phCommandLists[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        for (size_t i = 0; ( nullptr != phCommandLists) && (i < numCommandLists); ++i){
            if (context.handleLifetime->isOpen( phCommandLists[i] )){
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;
            }
        }
        if (hFence && !context.handleLifetime->isHandleValid( hFence )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandQueueSynchronizeEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandQueue )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandQueueGetOrdinalEpilogue(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandQueue )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandQueueGetIndexEpilogue(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pIndex                                ///< [out] command queue index within the group
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandQueue )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListCreateEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListCreateImmediateEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListDestroyEpilogue(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    { 
        
        if (hCommandList && context.handleLifetime->isHandleValid( hCommandList )){
            if (context.handleLifetime->hasDependents( hCommandList )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hCommandList);
            context.handleLifetime->removeHandle( hCommandList );
        } else if (!context.handleLifetime->isHandleValid( hCommandList )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListCloseEpilogue(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        context.handleLifetime->close( hCommandList );
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListResetEpilogue(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        context.handleLifetime->reset( hCommandList );
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendWriteGlobalTimestampEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListHostSynchronizeEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListGetDeviceHandleEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_device_handle_t* phDevice                    ///< [out] handle of the device on which the command list was created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListGetContextHandleEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the command list was created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListGetOrdinalEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal to which command list is submitted
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListImmediateGetIndexEpilogue(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t* pIndex                                ///< [out] command queue index within the group to which the immediate
                                                        ///< command list is submitted
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandListImmediate )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListIsImmediateEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_bool_t* pIsImmediate                         ///< [out] Boolean indicating whether the command list is an immediate
                                                        ///< command list (true) or not (false)
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendBarrierEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendMemoryRangesBarrierEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextSystemBarrierEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendMemoryCopyEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendMemoryFillEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendMemoryCopyRegionEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendMemoryCopyFromContextEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hContextSrc )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendImageCopyEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hDstImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hSrcImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendImageCopyRegionEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hDstImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hSrcImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendImageCopyToMemoryEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hSrcImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendImageCopyFromMemoryEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hDstImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendMemoryPrefetchEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendMemAdviseEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolCreateEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phDevices) && (i < numDevices); ++i){
            if (!context.handleLifetime->isHandleValid( phDevices[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolDestroyEpilogue(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    { 
        
        if (hEventPool && context.handleLifetime->isHandleValid( hEventPool )){
            if (context.handleLifetime->hasDependents( hEventPool )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hEventPool);
            context.handleLifetime->removeHandle( hEventPool );
        } else if (!context.handleLifetime->isHandleValid( hEventPool )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventCreateEpilogue(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEventPool )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventDestroyEpilogue(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    { 
        
        if (hEvent && context.handleLifetime->isHandleValid( hEvent )){
            if (context.handleLifetime->hasDependents( hEvent )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hEvent);
            context.handleLifetime->removeHandle( hEvent );
        } else if (!context.handleLifetime->isHandleValid( hEvent )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolGetIpcHandleEpilogue(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEventPool )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolPutIpcHandleEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolOpenIpcHandleEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event pool handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolCloseIpcHandleEpilogue(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEventPool )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendSignalEventEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendWaitOnEventsEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                        ///< continuing
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        for (size_t i = 0; ( nullptr != phEvents) && (i < numEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventHostSignalEpilogue(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventHostSynchronizeEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventQueryStatusEpilogue(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendEventResetEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventHostResetEpilogue(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventQueryKernelTimestampEpilogue(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendQueryKernelTimestampsEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        for (size_t i = 0; ( nullptr != phEvents) && (i < numEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventGetEventPoolEpilogue(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_pool_handle_t* phEventPool             ///< [out] handle of the event pool for the event
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventGetSignalScopeEpilogue(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pSignalScope            ///< [out] signal event scope. This is the scope of relevant cache
                                                        ///< hierarchies that are flushed on a signal action before the event is
                                                        ///< triggered. May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventGetWaitScopeEpilogue(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pWaitScope              ///< [out] wait event scope. This is the scope of relevant cache
                                                        ///< hierarchies invalidated on a wait action after the event is complete.
                                                        ///< May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolGetContextHandleEpilogue(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the event pool was created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEventPool )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventPoolGetFlagsEpilogue(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_event_pool_flags_t* pFlags                   ///< [out] creation flags used to create the event pool; may be 0 or a
                                                        ///< valid combination of ::ze_event_pool_flag_t
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEventPool )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFenceCreateEpilogue(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandQueue )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFenceDestroyEpilogue(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    { 
        
        if (hFence && context.handleLifetime->isHandleValid( hFence )){
            if (context.handleLifetime->hasDependents( hFence )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hFence);
            context.handleLifetime->removeHandle( hFence );
        } else if (!context.handleLifetime->isHandleValid( hFence )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFenceHostSynchronizeEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hFence )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFenceQueryStatusEpilogue(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFence )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFenceResetEpilogue(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFence )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageGetPropertiesEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageCreateEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageDestroyEpilogue(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    { 
        
        if (hImage && context.handleLifetime->isHandleValid( hImage )){
            if (context.handleLifetime->hasDependents( hImage )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hImage);
            context.handleLifetime->removeHandle( hImage );
        } else if (!context.handleLifetime->isHandleValid( hImage )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemAllocSharedEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hDevice && !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemAllocDeviceEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemAllocHostEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        void** pptr                                     ///< [out] pointer to host allocation
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemFreeEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemGetAllocPropertiesEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemGetAddressRangeEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemGetIpcHandleEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemGetIpcHandleFromFileDescriptorExpEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        uint64_t handle,                                ///< [in] file descriptor
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemGetFileDescriptorFromIpcHandleExpEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t ipcHandle,                  ///< [in] IPC memory handle
        uint64_t* pHandle                               ///< [out] Returned file descriptor
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemPutIpcHandleEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemOpenIpcHandleEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation.
                                                        ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemCloseIpcHandleEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemSetAtomicAccessAttributeExpEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t attr          ///< [in] Atomic access attributes to set for the specified range.
                                                        ///< Must be 0 (default) or a valid combination of ::ze_memory_atomic_attr_exp_flag_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemGetAtomicAccessAttributeExpEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t* pAttr        ///< [out] Atomic access attributes for the specified range
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleCreateEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleDestroyEpilogue(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    { 
        
        if (hModule && context.handleLifetime->isHandleValid( hModule )){
            if (context.handleLifetime->hasDependents( hModule )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hModule);
            context.handleLifetime->removeHandle( hModule );
        } else if (!context.handleLifetime->isHandleValid( hModule )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleDynamicLinkEpilogue(
        uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to
                                                        ///< dynamically link together.
        ze_module_build_log_handle_t* phLinkLog         ///< [out][optional] pointer to handle of dynamic link log.
        )
    { 
        
        for (size_t i = 0; ( nullptr != phModules) && (i < numModules); ++i){
            if (!context.handleLifetime->isHandleValid( phModules[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleBuildLogDestroyEpilogue(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    { 
        
        if (hModuleBuildLog && context.handleLifetime->isHandleValid( hModuleBuildLog )){
            if (context.handleLifetime->hasDependents( hModuleBuildLog )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hModuleBuildLog);
            context.handleLifetime->removeHandle( hModuleBuildLog );
        } else if (!context.handleLifetime->isHandleValid( hModuleBuildLog )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleBuildLogGetStringEpilogue(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hModuleBuildLog )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleGetNativeBinaryEpilogue(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hModule )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleGetGlobalPointerEpilogue(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pGlobalName,                        ///< [in] name of global variable in module
        size_t* pSize,                                  ///< [in,out][optional] size of global variable
        void** pptr                                     ///< [in,out][optional] device visible pointer
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hModule )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleGetKernelNamesEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hModule )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleGetPropertiesEpilogue(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hModule )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelCreateEpilogue(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hModule )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelDestroyEpilogue(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    { 
        
        if (hKernel && context.handleLifetime->isHandleValid( hKernel )){
            if (context.handleLifetime->hasDependents( hKernel )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hKernel);
            context.handleLifetime->removeHandle( hKernel );
        } else if (!context.handleLifetime->isHandleValid( hKernel )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleGetFunctionPointerEpilogue(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hModule )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSetGroupSizeEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSuggestGroupSizeEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSuggestMaxCooperativeGroupCountEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSetArgumentValueEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSetIndirectAccessEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelGetIndirectAccessEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelGetSourceAttributesEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSetCacheConfigEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                        ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelGetPropertiesEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelGetNameEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                        ///< bytes.
        char* pName                                     ///< [in,out][optional] char pointer to kernel name.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendLaunchKernelEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendLaunchCooperativeKernelEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendLaunchKernelIndirectEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendLaunchMultipleKernelsIndirectEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        for (size_t i = 0; ( nullptr != phKernels) && (i < numKernels); ++i){
            if (!context.handleLifetime->isHandleValid( phKernels[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextMakeMemoryResidentEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextEvictMemoryEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextMakeImageResidentEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeContextEvictImageEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeSamplerCreateEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeSamplerDestroyEpilogue(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    { 
        
        if (hSampler && context.handleLifetime->isHandleValid( hSampler )){
            if (context.handleLifetime->hasDependents( hSampler )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hSampler);
            context.handleLifetime->removeHandle( hSampler );
        } else if (!context.handleLifetime->isHandleValid( hSampler )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeVirtualMemReserveEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in][optional] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeVirtualMemFreeEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to free.
        size_t size                                     ///< [in] size in bytes to free; must be page aligned.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeVirtualMemQueryPageSizeEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t size,                                    ///< [in] unaligned allocation size in bytes
        size_t* pagesize                                ///< [out] pointer to page size to use for start address and size
                                                        ///< alignments.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zePhysicalMemCreateEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zePhysicalMemDestroyEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
        )
    { 
        
        if (hContext && context.handleLifetime->isHandleValid( hContext )){
            if (context.handleLifetime->hasDependents( hContext )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hContext);
            context.handleLifetime->removeHandle( hContext );
        } else if (!context.handleLifetime->isHandleValid( hContext )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hPhysicalMemory && context.handleLifetime->isHandleValid( hPhysicalMemory )){
            if (context.handleLifetime->hasDependents( hPhysicalMemory )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hPhysicalMemory);
            context.handleLifetime->removeHandle( hPhysicalMemory );
        } else if (!context.handleLifetime->isHandleValid( hPhysicalMemory )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeVirtualMemMapEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hPhysicalMemory )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeVirtualMemUnmapEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to unmap.
        size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeVirtualMemSetAccessAttributeEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeVirtualMemGetAccessAttributeEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t* access,           ///< [out] query result for page access attribute.
        size_t* outSize                                 ///< [out] query result for size of virtual address range, starting at ptr,
                                                        ///< that shares same access attribute.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSetGlobalOffsetExpEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t offsetX,                               ///< [in] global offset for X dimension to use for this kernel
        uint32_t offsetY,                               ///< [in] global offset for Y dimension to use for this kernel
        uint32_t offsetZ                                ///< [in] global offset for Z dimension to use for this kernel
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceReserveCacheExtEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t cacheLevel,                              ///< [in] cache level where application want to reserve. If zero, then the
                                                        ///< driver shall default to last level of cache and attempt to reserve in
                                                        ///< that cache.
        size_t cacheReservationSize                     ///< [in] value for reserving size, in bytes. If zero, then the driver
                                                        ///< shall remove prior reservation
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceSetCacheAdviceExtEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        void* ptr,                                      ///< [in] memory pointer to query
        size_t regionSize,                              ///< [in] region size, in pages
        ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventQueryTimestampsExpEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageGetMemoryPropertiesExpEpilogue(
        ze_image_handle_t hImage,                       ///< [in] handle of image object
        ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageViewCreateExtEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageViewCreateExpEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeKernelSchedulingHintExpEpilogue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDevicePciGetPropertiesExtEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
        ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendImageCopyToMemoryExtEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hSrcImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListAppendImageCopyFromMemoryExtEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hDstImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageGetAllocPropertiesExtEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_image_handle_t hImage,                       ///< [in] handle of image object to query
        ze_image_allocation_ext_properties_t* pImageAllocProperties ///< [in,out] query result for image allocation properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeModuleInspectLinkageExtEpilogue(
        ze_linkage_inspection_ext_desc_t* pInspectDesc, ///< [in] pointer to linkage inspection descriptor structure.
        uint32_t numModules,                            ///< [in] number of modules to be inspected pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to be
                                                        ///< inspected for import dependencies.
        ze_module_build_log_handle_t* phLog             ///< [out] pointer to handle of linkage inspection log. Log object will
                                                        ///< contain separate lists of imports, un-resolvable imports, and exports.
        )
    { 
        
        for (size_t i = 0; ( nullptr != phModules) && (i < numModules); ++i){
            if (!context.handleLifetime->isHandleValid( phModules[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemFreeExtEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFabricVertexGetExpEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFabricVertexGetSubVerticesExpEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hVertex )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFabricVertexGetPropertiesExpEpilogue(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hVertex )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFabricVertexGetDeviceExpEpilogue(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hVertex )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDeviceGetFabricVertexExpEpilogue(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFabricEdgeGetExpEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hVertexA )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hVertexB )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFabricEdgeGetVerticesExpEpilogue(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge instance
        ze_fabric_vertex_handle_t* phVertexA,           ///< [out] fabric vertex connected to one end of the given fabric edge.
        ze_fabric_vertex_handle_t* phVertexB            ///< [out] fabric vertex connected to other end of the given fabric edge.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEdge )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeFabricEdgeGetPropertiesExpEpilogue(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
        ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEdge )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeEventQueryKernelTimestampsExtEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASBuilderCreateExpEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASBuilderGetBuildPropertiesExpEpilogue(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hBuilder )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeDriverRTASFormatCompatibilityCheckExpEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_exp_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_exp_t rtasFormatB                ///< [in] operand B
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASBuilderBuildExpEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hBuilder )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hParallelOperation && !context.handleLifetime->isHandleValid( hParallelOperation )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASBuilderDestroyExpEpilogue(
        ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hBuilder )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASParallelOperationCreateExpEpilogue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASParallelOperationGetPropertiesExpEpilogue(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hParallelOperation )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASParallelOperationJoinExpEpilogue(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hParallelOperation )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeRTASParallelOperationDestroyExpEpilogue(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hParallelOperation )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeMemGetPitchFor2dImageEpilogue(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        size_t imageWidth,                              ///< [in] imageWidth
        size_t imageHeight,                             ///< [in] imageHeight
        unsigned int elementSizeInBytes,                ///< [in] Element size in bytes
        size_t * rowPitch                               ///< [out] rowPitch
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeImageGetDeviceOffsetExpEpilogue(
        ze_image_handle_t hImage,                       ///< [in] handle of the image
        uint64_t* pDeviceOffset                         ///< [out] bindless device offset for image
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hImage )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListCreateCloneExpEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle to source command list (the command list to clone)
        ze_command_list_handle_t* phClonedCommandList   ///< [out] pointer to handle of the cloned command list
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListImmediateAppendCommandListsExpEpilogue(
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
        
        if ( !context.handleLifetime->isHandleValid( hCommandListImmediate )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phCommandLists) && (i < numCommandLists); ++i){
            if (!context.handleLifetime->isHandleValid( phCommandLists[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListGetNextCommandIdExpEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_command_id_exp_desc_t* desc,   ///< [in] pointer to mutable command identifier descriptor
        uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListUpdateMutableCommandsExpEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_commands_exp_desc_t* desc      ///< [in] pointer to mutable commands descriptor; multiple descriptors may
                                                        ///< be chained via `pNext` member
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListUpdateMutableCommandSignalEventExpEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        ze_event_handle_t hSignalEvent                  ///< [in][optional] handle of the event to signal on completion
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZEHandleLifetimeValidation::zeCommandListUpdateMutableCommandWaitEventsExpEpilogue(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        uint32_t numWaitEvents,                         ///< [in][optional] the number of wait events
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phWaitEvents) && (i < numWaitEvents); ++i){
            if (!context.handleLifetime->isHandleValid( phWaitEvents[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
}