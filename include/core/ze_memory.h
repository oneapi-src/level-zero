/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_memory.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Memory
 *
 */
 
#ifndef _ZE_MEMORY_H
#define _ZE_MEMORY_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_mem_alloc_desc_t
typedef enum _ze_device_mem_alloc_desc_version_t
{
    ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} ze_device_mem_alloc_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported memory allocation flags
typedef enum _ze_device_mem_alloc_flag_t
{
    ZE_DEVICE_MEM_ALLOC_FLAG_DEFAULT = 0,           ///< implicit default behavior; uses driver-based heuristics
    ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_CACHED = ZE_BIT( 0 ), ///< device should cache allocation
    ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_UNCACHED = ZE_BIT( 1 ),   ///< device should not cache allocation (UC)

} ze_device_mem_alloc_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device mem alloc descriptor
typedef struct _ze_device_mem_alloc_desc_t
{
    ze_device_mem_alloc_desc_version_t version;     ///< [in] ::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT
    ze_device_mem_alloc_flag_t flags;               ///< [in] flags specifying additional allocation controls
    uint32_t ordinal;                               ///< [in] ordinal of the device's local memory to allocate from;
                                                    ///< must be less than the count returned from ::zeDeviceGetMemoryProperties

} ze_device_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_host_mem_alloc_desc_t
typedef enum _ze_host_mem_alloc_desc_version_t
{
    ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

} ze_host_mem_alloc_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported host memory allocation flags
typedef enum _ze_host_mem_alloc_flag_t
{
    ZE_HOST_MEM_ALLOC_FLAG_DEFAULT = 0,             ///< implicit default behavior; uses driver-based heuristics
    ZE_HOST_MEM_ALLOC_FLAG_BIAS_CACHED = ZE_BIT( 0 ),   ///< host should cache allocation
    ZE_HOST_MEM_ALLOC_FLAG_BIAS_UNCACHED = ZE_BIT( 1 ), ///< host should not cache allocation (UC)
    ZE_HOST_MEM_ALLOC_FLAG_BIAS_WRITE_COMBINED = ZE_BIT( 2 ),   ///< host memory should be allocated write-combined (WC)

} ze_host_mem_alloc_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Host mem alloc descriptor
typedef struct _ze_host_mem_alloc_desc_t
{
    ze_host_mem_alloc_desc_version_t version;       ///< [in] ::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT
    ze_host_mem_alloc_flag_t flags;                 ///< [in] flags specifying additional allocation controls

} ze_host_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory that is shared between the host and one or more
///        devices
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
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT < device_desc->version`
///         + `::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT < host_desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + device_desc->flags
///         + host_desc->flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDriverAllocSharedMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device mem alloc descriptor
    const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host mem alloc descriptor
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
    void** pptr                                     ///< [out] pointer to shared allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates memory specific to a device
/// 
/// @details
///     - A device allocation is owned by a specific device.
///     - In general, a device allocation may only be accessed by the device
///       that owns it.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == device_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT < device_desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + device_desc->flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDriverAllocDeviceMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device mem alloc descriptor
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    void** pptr                                     ///< [out] pointer to device allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Allocates host memory
/// 
/// @details
///     - A host allocation is owned by the host process.
///     - Host allocations are accessible by the host and all devices within the
///       driver driver.
///     - Host allocations are frequently used as staging areas to transfer data
///       to or from devices.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == host_desc`
///         + `nullptr == pptr`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT < host_desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + host_desc->flags
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_SIZE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeDriverAllocHostMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host mem alloc descriptor
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** pptr                                     ///< [out] pointer to host allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Frees allocated host memory, device memory, or shared memory
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the memory before it is freed
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this memory
///     - The application may **not** call this function from simultaneous
///       threads with the same pointer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
__ze_api_export ze_result_t __zecall
zeDriverFreeMem(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    void* ptr                                       ///< [in][release] pointer to memory to free
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_memory_allocation_properties_t
typedef enum _ze_memory_allocation_properties_version_t
{
    ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ), ///< version 0.91

} ze_memory_allocation_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation type
typedef enum _ze_memory_type_t
{
    ZE_MEMORY_TYPE_UNKNOWN = 0,                     ///< the memory pointed to is of unknown type
    ZE_MEMORY_TYPE_HOST,                            ///< the memory pointed to is a host allocation
    ZE_MEMORY_TYPE_DEVICE,                          ///< the memory pointed to is a device allocation
    ZE_MEMORY_TYPE_SHARED,                          ///< the memory pointed to is a shared ownership allocation

} ze_memory_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory allocation properties queried using
///        ::zeDriverGetMemAllocProperties
typedef struct _ze_memory_allocation_properties_t
{
    ze_memory_allocation_properties_version_t version;  ///< [in] ::ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
    ze_memory_type_t type;                          ///< [out] type of allocated memory
    uint64_t id;                                    ///< [out] identifier for this allocation

} ze_memory_allocation_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a memory allocation
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pMemAllocProperties`
__ze_api_export ze_result_t __zecall
zeDriverGetMemAllocProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
    ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
    );

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
__ze_api_export ze_result_t __zecall
zeDriverGetMemAddressRange(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] memory pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates an IPC memory handle for the specified allocation in the
///        sending process
/// 
/// @details
///     - Takes a pointer to the base of a device memory allocation and exports
///       it for use in another process.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
///         + `nullptr == pIpcHandle`
__ze_api_export ze_result_t __zecall
zeDriverGetMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr,                                ///< [in] pointer to the device memory allocation
    ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported IPC memory flags
typedef enum _ze_ipc_memory_flag_t
{
    ZE_IPC_MEMORY_FLAG_NONE = 0,                    ///< No special flags

} ze_ipc_memory_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
///        process
/// 
/// @details
///     - Takes an IPC memory handle from a sending process and associates it
///       with a device pointer usable in this process.
///     - The device pointer in this process should not be freed with
///       ::zeDriverFreeMem, but rather with ::zeDriverCloseMemIpcHandle.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + flags
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pptr`
__ze_api_export ze_result_t __zecall
zeDriverOpenMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    ze_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** pptr                                     ///< [out] pointer to device allocation in this process
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes an IPC memory handle in a receiving process
/// 
/// @details
///     - Closes an IPC memory handle by unmapping memory that was opened in
///       this process using ::zeDriverOpenMemIpcHandle.
///     - The application may **not** call this function from simultaneous
///       threads with the same pointer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == ptr`
__ze_api_export ze_result_t __zecall
zeDriverCloseMemIpcHandle(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const void* ptr                                 ///< [in][release] pointer to device allocation in this process
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_MEMORY_H
