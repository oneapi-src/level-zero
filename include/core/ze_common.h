/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_common.h
 *
 * @brief Intel 'One API' Level-Zero API common types
 *
 */
 
#ifndef _ZE_COMMON_H
#define _ZE_COMMON_H
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
#ifndef ZE_MAKE_VERSION
/// @brief Generates generic 'One API' API versions
#define ZE_MAKE_VERSION( _major, _minor )  (( _major << 16 )|( _minor & 0x0000ffff))
#endif // ZE_MAKE_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAJOR_VERSION
/// @brief Extracts 'One API' API major version
#define ZE_MAJOR_VERSION( _ver )  ( _ver >> 16 )
#endif // ZE_MAJOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MINOR_VERSION
/// @brief Extracts 'One API' API minor version
#define ZE_MINOR_VERSION( _ver )  ( _ver & 0x0000ffff )
#endif // ZE_MINOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef __zecall
#if defined(_WIN32)
/// @brief Calling convention for all API functions
#define __zecall  __cdecl
#else
#define __zecall  
#endif // defined(_WIN32)
#endif // __zecall

///////////////////////////////////////////////////////////////////////////////
#ifndef __ze_api_export
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define __ze_api_export  __declspec(dllexport)
#else
#define __ze_api_export  
#endif // defined(_WIN32)
#endif // __ze_api_export

///////////////////////////////////////////////////////////////////////////////
#ifndef __zedllexport
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define __zedllexport  __declspec(dllexport)
#else
#define __zedllexport  
#endif // defined(_WIN32)
#endif // __zedllexport

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_ENABLE_OCL_INTEROP
#if !defined(ZE_ENABLE_OCL_INTEROP)
/// @brief Disable OpenCL interoperability functions if not explicitly defined
#define ZE_ENABLE_OCL_INTEROP  0
#endif // !defined(ZE_ENABLE_OCL_INTEROP)
#endif // ZE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief compiler-independent type
typedef uint8_t ze_bool_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of a driver instance
typedef struct _ze_driver_handle_t *ze_driver_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's device object
typedef struct _ze_device_handle_t *ze_device_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command queue object
typedef struct _ze_command_queue_handle_t *ze_command_queue_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's command list object
typedef struct _ze_command_list_handle_t *ze_command_list_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's fence object
typedef struct _ze_fence_handle_t *ze_fence_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's event pool object
typedef struct _ze_event_pool_handle_t *ze_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's event object
typedef struct _ze_event_handle_t *ze_event_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's image object
typedef struct _ze_image_handle_t *ze_image_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's module object
typedef struct _ze_module_handle_t *ze_module_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of module's build log object
typedef struct _ze_module_build_log_handle_t *ze_module_build_log_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's kernel object
typedef struct _ze_kernel_handle_t *ze_kernel_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Handle of driver's sampler object
typedef struct _ze_sampler_handle_t *ze_sampler_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_IPC_HANDLE_SIZE
/// @brief Maximum IPC handle size
#define ZE_MAX_IPC_HANDLE_SIZE  64
#endif // ZE_MAX_IPC_HANDLE_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC handle to a memory allocation
typedef struct _ze_ipc_mem_handle_t
{
    char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< Opaque data representing an IPC handle

} ze_ipc_mem_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC handle to a event pool allocation
typedef struct _ze_ipc_event_pool_handle_t
{
    char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< Opaque data representing an IPC handle

} ze_ipc_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_BIT
/// @brief Generic macro for enumerator bit masks
#define ZE_BIT( _i )  ( 1 << _i )
#endif // ZE_BIT

///////////////////////////////////////////////////////////////////////////////
/// @brief Defines Return/Error codes
typedef enum _ze_result_t
{
    ZE_RESULT_SUCCESS = 0,                          ///< [Core] success
    ZE_RESULT_NOT_READY = 1,                        ///< [Core] synchronization primitive not signaled
    ZE_RESULT_ERROR_DEVICE_LOST = 0x70000001,       ///< [Core] device hung, reset, was removed, or driver update occurred
    ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY,             ///< [Core] insufficient host memory to satisfy call
    ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY,           ///< [Core] insufficient device memory to satisfy call
    ZE_RESULT_ERROR_MODULE_BUILD_FAILURE,           ///< [Core] error occurred when building module, see build log for details
    ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS = 0x70010000,  ///< [Tools] access denied due to permission level
    ZE_RESULT_ERROR_NOT_AVAILABLE,                  ///< [Tools] resource already in use and simultaneous access not allowed
    ZE_RESULT_ERROR_UNINITIALIZED = 0x78000001,     ///< [Validation] driver is not initialized
    ZE_RESULT_ERROR_UNSUPPORTED_VERSION,            ///< [Validation] generic error code for unsupported versions
    ZE_RESULT_ERROR_UNSUPPORTED_FEATURE,            ///< [Validation] generic error code for unsupported features
    ZE_RESULT_ERROR_INVALID_ARGUMENT,               ///< [Validation] generic error code for invalid arguments
    ZE_RESULT_ERROR_INVALID_NULL_HANDLE,            ///< [Validation] handle argument is not valid
    ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE,           ///< [Validation] object pointed to by handle still in-use by device
    ZE_RESULT_ERROR_INVALID_NULL_POINTER,           ///< [Validation] pointer argument may not be nullptr
    ZE_RESULT_ERROR_INVALID_SIZE,                   ///< [Validation] size argument is invalid (e.g., must not be zero)
    ZE_RESULT_ERROR_UNSUPPORTED_SIZE,               ///< [Validation] size argument is not supported by the device (e.g., too
                                                    ///< large)
    ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT,          ///< [Validation] alignment argument is not supported by the device (e.g.,
                                                    ///< too small)
    ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT, ///< [Validation] synchronization object in invalid state
    ZE_RESULT_ERROR_INVALID_ENUMERATION,            ///< [Validation] enumerator argument is not valid
    ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION,        ///< [Validation] enumerator argument is not supported by the device
    ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT,       ///< [Validation] image format is not supported by the device
    ZE_RESULT_ERROR_INVALID_NATIVE_BINARY,          ///< [Validation] native binary is not supported by the device
    ZE_RESULT_ERROR_INVALID_GLOBAL_NAME,            ///< [Validation] global variable is not found in the module
    ZE_RESULT_ERROR_INVALID_KERNEL_NAME,            ///< [Validation] kernel name is not found in the module
    ZE_RESULT_ERROR_INVALID_FUNCTION_NAME,          ///< [Validation] function name is not found in the module
    ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION,   ///< [Validation] group size dimension is not valid for the kernel or
                                                    ///< device
    ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION, ///< [Validation] global width dimension is not valid for the kernel or
                                                    ///< device
    ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX,  ///< [Validation] kernel argument index is not valid for kernel
    ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE,   ///< [Validation] kernel argument size does not match kernel
    ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE, ///< [Validation] value of kernel attribute is not valid for the kernel or
                                                    ///< device
    ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE,      ///< [Validation] command list type does not match command queue type
    ZE_RESULT_ERROR_OVERLAPPING_REGIONS,            ///< [Validation] copy operations do not support overlapping regions of
                                                    ///< memory
    ZE_RESULT_ERROR_UNKNOWN = 0x7fffffff,           ///< [Core] unknown or internal error

} ze_result_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_driver_uuid_t
typedef struct _ze_driver_uuid_t ze_driver_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_driver_properties_t
typedef struct _ze_driver_properties_t ze_driver_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_driver_ipc_properties_t
typedef struct _ze_driver_ipc_properties_t ze_driver_ipc_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_ipc_mem_handle_t
typedef struct _ze_ipc_mem_handle_t ze_ipc_mem_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_ipc_event_pool_handle_t
typedef struct _ze_ipc_event_pool_handle_t ze_ipc_event_pool_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_uuid_t
typedef struct _ze_device_uuid_t ze_device_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_properties_t
typedef struct _ze_device_properties_t ze_device_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_compute_properties_t
typedef struct _ze_device_compute_properties_t ze_device_compute_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_native_kernel_uuid_t
typedef struct _ze_native_kernel_uuid_t ze_native_kernel_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_kernel_properties_t
typedef struct _ze_device_kernel_properties_t ze_device_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_memory_properties_t
typedef struct _ze_device_memory_properties_t ze_device_memory_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_memory_access_properties_t
typedef struct _ze_device_memory_access_properties_t ze_device_memory_access_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_cache_properties_t
typedef struct _ze_device_cache_properties_t ze_device_cache_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_image_properties_t
typedef struct _ze_device_image_properties_t ze_device_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_p2p_properties_t
typedef struct _ze_device_p2p_properties_t ze_device_p2p_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_command_queue_desc_t
typedef struct _ze_command_queue_desc_t ze_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_command_list_desc_t
typedef struct _ze_command_list_desc_t ze_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_format_desc_t
typedef struct _ze_image_format_desc_t ze_image_format_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_desc_t
typedef struct _ze_image_desc_t ze_image_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_properties_t
typedef struct _ze_image_properties_t ze_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_module_constants_t
typedef struct _ze_module_constants_t ze_module_constants_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_module_desc_t
typedef struct _ze_module_desc_t ze_module_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_kernel_desc_t
typedef struct _ze_kernel_desc_t ze_kernel_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_kernel_properties_t
typedef struct _ze_kernel_properties_t ze_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_group_count_t
typedef struct _ze_group_count_t ze_group_count_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_event_pool_desc_t
typedef struct _ze_event_pool_desc_t ze_event_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_event_desc_t
typedef struct _ze_event_desc_t ze_event_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_sampler_desc_t
typedef struct _ze_sampler_desc_t ze_sampler_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_device_mem_alloc_desc_t
typedef struct _ze_device_mem_alloc_desc_t ze_device_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_host_mem_alloc_desc_t
typedef struct _ze_host_mem_alloc_desc_t ze_host_mem_alloc_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_memory_allocation_properties_t
typedef struct _ze_memory_allocation_properties_t ze_memory_allocation_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_fence_desc_t
typedef struct _ze_fence_desc_t ze_fence_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_copy_region_t
typedef struct _ze_copy_region_t ze_copy_region_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Forward-declare ze_image_region_t
typedef struct _ze_image_region_t ze_image_region_t;


#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_COMMON_H
