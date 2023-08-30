/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_parameter_validation.cpp
 *
 */
#include "ze_validation_layer.h"
#include "ze_parameter_validation.h"

namespace validation_layer
{

    ze_result_t
    ZEParameterValidation::zeInit(
        ze_init_flags_t flags                           ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        if( 0x3 < flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDriverGet(
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
        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == version )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDriverGetProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pDriverProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pDriverProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pIpcProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pIpcProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDriverGetExtensionProperties(
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
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pExtensionProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == name )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == ppFunctionAddress )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDriverGetLastErrorDescription(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ppString )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGet(
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
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetRootDevice(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phRootDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetSubDevices(
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
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pDeviceProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pDeviceProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pComputeProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pComputeProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetModuleProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pModuleProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pModuleProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetCommandQueueGroupProperties(
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
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pCommandQueueGroupProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetMemoryProperties(
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
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pMemProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pMemAccessProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pMemAccessProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetCacheProperties(
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
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pCacheProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pImageProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pImageProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetExternalMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pExternalMemoryProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pExternalMemoryProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetP2PProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hPeerDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pP2PProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pP2PProperties);
    }


    ze_result_t
    ZEParameterValidation::zeDeviceCanAccessPeer(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hPeerDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == value )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetStatus(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetGlobalTimestamps(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                        ///< Device's global timestamp value
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hostTimestamp )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == deviceTimestamp )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeContextCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phContext )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x1 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeContextCreateEx(
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
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phContext )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x1 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( (nullptr == phDevices) && (0 < numDevices) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeContextDestroy(
        ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeContextGetStatus(
        ze_context_handle_t hContext                    ///< [in] handle of context object
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandQueueCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phCommandQueue )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS < desc->mode )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_HIGH < desc->priority )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        if( nullptr == hCommandQueue )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandQueueExecuteCommandLists(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    {
        if( nullptr == hCommandQueue )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phCommandLists )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0 == numCommandLists )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandQueueSynchronize(
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
        if( nullptr == hCommandQueue )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0xf < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeCommandListCreateImmediate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == altdesc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < altdesc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS < altdesc->mode )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_HIGH < altdesc->priority )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(altdesc);
    }


    ze_result_t
    ZEParameterValidation::zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendWriteGlobalTimestamp(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == dstptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListHostSynchronize(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendMemoryRangesBarrier(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pRangeSizes )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pRanges )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeContextSystemBarrier(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendMemoryCopy(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == dstptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == srcptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendMemoryFill(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pattern )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendMemoryCopyRegion(
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

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendMemoryCopyFromContext(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hContextSrc )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == dstptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == srcptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendImageCopy(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDstImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hSrcImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendImageCopyRegion(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDstImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hSrcImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendImageCopyToMemory(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hSrcImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == dstptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendImageCopyFromMemory(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDstImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == srcptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendMemoryPrefetch(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendMemAdvise(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_MEMORY_ADVICE_CLEAR_SYSTEM_MEMORY_PREFERRED_LOCATION < advice )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventPoolCreate(
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
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phEventPool )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0xf < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == desc->count )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        if( (nullptr == phDevices) && (0 < numDevices) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        if( nullptr == hEventPool )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventCreate(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        if( nullptr == hEventPool )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x7 < desc->signal )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0x7 < desc->wait )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        if( nullptr == hEventPool )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phIpc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventPoolPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventPoolOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event pool handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phEventPool )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        if( nullptr == hEventPool )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                        ///< continuing
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phEvents )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventHostSynchronize(
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
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventQueryKernelTimestamp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
        )
    {
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == dstptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendQueryKernelTimestamps(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phEvents )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == dstptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFenceCreate(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    {
        if( nullptr == hCommandQueue )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phFence )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x1 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        if( nullptr == hFence )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFenceHostSynchronize(
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
        if( nullptr == hFence )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        if( nullptr == hFence )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        if( nullptr == hFence )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeImageGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pImageProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_IMAGE_TYPE_BUFFER < desc->type )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        auto retVal = ZE_RESULT_SUCCESS;
        retVal = ParameterValidation::validateExtensions(desc);
        if(retVal)
            return retVal;
        retVal = ParameterValidation::validateExtensions(pImageProperties);
        return retVal;
    }


    ze_result_t
    ZEParameterValidation::zeImageCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phImage )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_IMAGE_TYPE_BUFFER < desc->type )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        if( nullptr == hImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemAllocShared(
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
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == device_desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == host_desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x7 < device_desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0xf < host_desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        if( 0 != (alignment & (alignment - 1)) )
            return ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT;

        auto retVal = ZE_RESULT_SUCCESS;
        retVal = ParameterValidation::validateExtensions(device_desc);
        if(retVal)
            return retVal;
        retVal = ParameterValidation::validateExtensions(host_desc);
        return retVal;
    }


    ze_result_t
    ZEParameterValidation::zeMemAllocDevice(
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
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == device_desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x7 < device_desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        if( 0 != (alignment & (alignment - 1)) )
            return ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT;

        return ParameterValidation::validateExtensions(device_desc);
    }


    ze_result_t
    ZEParameterValidation::zeMemAllocHost(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == host_desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0xf < host_desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        if( 0 != (alignment & (alignment - 1)) )
            return ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT;

        return ParameterValidation::validateExtensions(host_desc);
    }


    ze_result_t
    ZEParameterValidation::zeMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemGetAllocProperties(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pMemAllocProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pMemAllocProperties);
    }


    ze_result_t
    ZEParameterValidation::zeMemGetAddressRange(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemGetIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pIpcHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemGetIpcHandleFromFileDescriptorExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        uint64_t handle,                                ///< [in] file descriptor
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pIpcHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemGetFileDescriptorFromIpcHandleExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t ipcHandle,                  ///< [in] IPC memory handle
        uint64_t* pHandle                               ///< [out] Returned file descriptor
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation.
                                                        ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( 0x3 < flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemCloseIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemSetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t attr          ///< [in] Atomic access attributes to set for the specified range.
                                                        ///< Must be 0 (default) or a valid combination of ::ze_memory_atomic_attr_exp_flag_t.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x7f < attr )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeMemGetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t* pAttr        ///< [out] Atomic access attributes for the specified range
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pAttr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == desc->pInputModule )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phModule )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_MODULE_FORMAT_NATIVE < desc->format )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == desc->inputSize )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        if( nullptr == hModule )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleDynamicLink(
        uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to
                                                        ///< dynamically link together.
        ze_module_build_log_handle_t* phLinkLog         ///< [out][optional] pointer to handle of dynamic link log.
        )
    {
        if( nullptr == phModules )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        if( nullptr == hModuleBuildLog )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleBuildLogGetString(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        if( nullptr == hModuleBuildLog )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pSize )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleGetNativeBinary(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        if( nullptr == hModule )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pSize )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pGlobalName,                        ///< [in] name of global variable in module
        size_t* pSize,                                  ///< [in,out][optional] size of global variable
        void** pptr                                     ///< [in,out][optional] device visible pointer
        )
    {
        if( nullptr == hModule )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pGlobalName )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleGetKernelNames(
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
        if( nullptr == hModule )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleGetProperties(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
        )
    {
        if( nullptr == hModule )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pModuleProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pModuleProperties);
    }


    ze_result_t
    ZEParameterValidation::zeKernelCreate(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        )
    {
        if( nullptr == hModule )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == desc->pKernelName )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeModuleGetFunctionPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        if( nullptr == hModule )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pFunctionName )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pfnFunction )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelSetGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelSuggestGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == groupSizeX )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == groupSizeY )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == groupSizeZ )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == totalGroupCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelSetArgumentValue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelSetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( 0x7 < flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelGetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pFlags )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelGetSourceAttributes(
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
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pSize )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelSetCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                        ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( 0x3 < flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pKernelProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pKernelProperties);
    }


    ze_result_t
    ZEParameterValidation::zeKernelGetName(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                        ///< bytes.
        char* pName                                     ///< [in,out][optional] char pointer to kernel name.
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pSize )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendLaunchKernel(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pLaunchFuncArgs )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendLaunchCooperativeKernel(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pLaunchFuncArgs )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendLaunchKernelIndirect(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pLaunchArgumentsBuffer )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendLaunchMultipleKernelsIndirect(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phKernels )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pCountBuffer )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pLaunchArgumentsBuffer )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeContextMakeMemoryResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeContextEvictMemory(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeContextMakeImageResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeContextEvictImage(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeSamplerCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phSampler )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_SAMPLER_ADDRESS_MODE_MIRROR < desc->addressMode )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_SAMPLER_FILTER_MODE_LINEAR < desc->filterMode )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        if( nullptr == hSampler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeVirtualMemReserve(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in][optional] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeVirtualMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to free.
        size_t size                                     ///< [in] size in bytes to free; must be page aligned.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeVirtualMemQueryPageSize(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t size,                                    ///< [in] unaligned allocation size in bytes
        size_t* pagesize                                ///< [out] pointer to page size to use for start address and size
                                                        ///< alignments.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pagesize )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zePhysicalMemCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phPhysicalMemory )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x1 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == desc->size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zePhysicalMemDestroy(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hPhysicalMemory )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeVirtualMemMap(
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
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hPhysicalMemory )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_MEMORY_ACCESS_ATTRIBUTE_READONLY < access )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeVirtualMemUnmap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to unmap.
        size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeVirtualMemSetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_MEMORY_ACCESS_ATTRIBUTE_READONLY < access )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeVirtualMemGetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t* access,           ///< [out] query result for page access attribute.
        size_t* outSize                                 ///< [out] query result for size of virtual address range, starting at ptr,
                                                        ///< that shares same access attribute.
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == access )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == outSize )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0 == size )
            return ZE_RESULT_ERROR_UNSUPPORTED_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeKernelSetGlobalOffsetExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t offsetX,                               ///< [in] global offset for X dimension to use for this kernel
        uint32_t offsetY,                               ///< [in] global offset for Y dimension to use for this kernel
        uint32_t offsetZ                                ///< [in] global offset for Z dimension to use for this kernel
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceReserveCacheExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t cacheLevel,                              ///< [in] cache level where application want to reserve. If zero, then the
                                                        ///< driver shall default to last level of cache and attempt to reserve in
                                                        ///< that cache.
        size_t cacheReservationSize                     ///< [in] value for reserving size, in bytes. If zero, then the driver
                                                        ///< shall remove prior reservation
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceSetCacheAdviceExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        void* ptr,                                      ///< [in] memory pointer to query
        size_t regionSize,                              ///< [in] region size, in pages
        ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_CACHE_EXT_REGION_NON_RESERVED < cacheRegion )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeEventQueryTimestampsExp(
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
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeImageGetMemoryPropertiesExp(
        ze_image_handle_t hImage,                       ///< [in] handle of image object
        ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
        )
    {
        if( nullptr == hImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pMemoryProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pMemoryProperties);
    }


    ze_result_t
    ZEParameterValidation::zeImageViewCreateExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phImageView )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_IMAGE_TYPE_BUFFER < desc->type )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeImageViewCreateExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == desc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phImageView )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < desc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_IMAGE_TYPE_BUFFER < desc->type )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(desc);
    }


    ze_result_t
    ZEParameterValidation::zeKernelSchedulingHintExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
        )
    {
        if( nullptr == hKernel )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pHint )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x7 < pHint->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(pHint);
    }


    ze_result_t
    ZEParameterValidation::zeDevicePciGetPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
        ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pPciProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pPciProperties);
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendImageCopyToMemoryExt(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hSrcImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == dstptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeCommandListAppendImageCopyFromMemoryExt(
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
        if( nullptr == hCommandList )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDstImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == srcptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( (nullptr == phWaitEvents) && (0 < numWaitEvents) )
            return ZE_RESULT_ERROR_INVALID_SIZE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeImageGetAllocPropertiesExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_image_handle_t hImage,                       ///< [in] handle of image object to query
        ze_image_allocation_ext_properties_t* pImageAllocProperties ///< [in,out] query result for image allocation properties
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hImage )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pImageAllocProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pImageAllocProperties);
    }


    ze_result_t
    ZEParameterValidation::zeModuleInspectLinkageExt(
        ze_linkage_inspection_ext_desc_t* pInspectDesc, ///< [in] pointer to linkage inspection descriptor structure.
        uint32_t numModules,                            ///< [in] number of modules to be inspected pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to be
                                                        ///< inspected for import dependencies.
        ze_module_build_log_handle_t* phLog             ///< [out] pointer to handle of linkage inspection log. Log object will
                                                        ///< contain separate lists of imports, un-resolvable imports, and exports.
        )
    {
        if( nullptr == pInspectDesc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phModules )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phLog )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x7 < pInspectDesc->flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(pInspectDesc);
    }


    ze_result_t
    ZEParameterValidation::zeMemFreeExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        if( nullptr == hContext )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pMemFreeDesc )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == ptr )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( 0x3 < pMemFreeDesc->freePolicy )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(pMemFreeDesc);
    }


    ze_result_t
    ZEParameterValidation::zeFabricVertexGetExp(
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
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFabricVertexGetSubVerticesExp(
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
        if( nullptr == hVertex )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFabricVertexGetPropertiesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
        )
    {
        if( nullptr == hVertex )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pVertexProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pVertexProperties);
    }


    ze_result_t
    ZEParameterValidation::zeFabricVertexGetDeviceExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
        )
    {
        if( nullptr == hVertex )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeDeviceGetFabricVertexExp(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phVertex )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFabricEdgeGetExp(
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
        if( nullptr == hVertexA )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hVertexB )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFabricEdgeGetVerticesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge instance
        ze_fabric_vertex_handle_t* phVertexA,           ///< [out] fabric vertex connected to one end of the given fabric edge.
        ze_fabric_vertex_handle_t* phVertexB            ///< [out] fabric vertex connected to other end of the given fabric edge.
        )
    {
        if( nullptr == hEdge )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phVertexA )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phVertexB )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeFabricEdgeGetPropertiesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
        ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
        )
    {
        if( nullptr == hEdge )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pEdgeProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pEdgeProperties);
    }


    ze_result_t
    ZEParameterValidation::zeEventQueryKernelTimestampsExt(
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
        if( nullptr == hEvent )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pResults);
    }


    ze_result_t
    ZEParameterValidation::zeRTASBuilderCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pDescriptor )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == phBuilder )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_RTAS_BUILDER_EXP_VERSION_CURRENT < pDescriptor->builderVersion )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(pDescriptor);
    }


    ze_result_t
    ZEParameterValidation::zeRTASBuilderGetBuildPropertiesExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
        )
    {
        if( nullptr == hBuilder )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pBuildOpDescriptor )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_RTAS_FORMAT_EXP_INVALID < pBuildOpDescriptor->rtasFormat )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_HIGH < pBuildOpDescriptor->buildQuality )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0x3 < pBuildOpDescriptor->buildFlags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        auto retVal = ZE_RESULT_SUCCESS;
        retVal = ParameterValidation::validateExtensions(pBuildOpDescriptor);
        if(retVal)
            return retVal;
        retVal = ParameterValidation::validateExtensions(pProperties);
        return retVal;
    }


    ze_result_t
    ZEParameterValidation::zeDriverRTASFormatCompatibilityCheckExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_exp_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_exp_t rtasFormatB                ///< [in] operand B
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZE_RTAS_FORMAT_EXP_INVALID < rtasFormatA )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_RTAS_FORMAT_EXP_INVALID < rtasFormatB )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeRTASBuilderBuildExp(
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
        if( nullptr == hBuilder )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pBuildOpDescriptor )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pScratchBuffer )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pRtasBuffer )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZE_RTAS_FORMAT_EXP_INVALID < pBuildOpDescriptor->rtasFormat )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZE_RTAS_BUILDER_BUILD_QUALITY_HINT_EXP_HIGH < pBuildOpDescriptor->buildQuality )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( 0x3 < pBuildOpDescriptor->buildFlags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ParameterValidation::validateExtensions(pBuildOpDescriptor);
    }


    ze_result_t
    ZEParameterValidation::zeRTASBuilderDestroyExp(
        ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    {
        if( nullptr == hBuilder )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeRTASParallelOperationCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phParallelOperation )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeRTASParallelOperationGetPropertiesExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    {
        if( nullptr == hParallelOperation )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZEParameterValidation::zeRTASParallelOperationJoinExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    {
        if( nullptr == hParallelOperation )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZEParameterValidation::zeRTASParallelOperationDestroyExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    {
        if( nullptr == hParallelOperation )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }

}