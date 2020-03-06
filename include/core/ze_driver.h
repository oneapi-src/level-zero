/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_driver.h
 *
 * @brief Intel 'One API' Level-Zero APIs
 *
 */
 
#ifndef _ZE_DRIVER_H
#define _ZE_DRIVER_H
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
/// @brief Supported initialization flags
typedef enum _ze_init_flag_t
{
    ZE_INIT_FLAG_NONE = 0,                          ///< default behavior
    ZE_INIT_FLAG_GPU_ONLY = ZE_BIT(0),              ///< only initialize GPU drivers

} ze_init_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the 'One API' driver and must be called before any other
///        API function
/// 
/// @details
///     - If this function is not called then all other functions will return
///       ::ZE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of a driver per process will be initialized.
///     - This function is thread-safe for scenarios where multiple libraries
///       may initialize the driver simultaneously.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
__ze_api_export ze_result_t __zecall
zeInit(
    ze_init_flag_t flags                            ///< [in] initialization flags
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves driver instances
/// 
/// @details
///     - A driver represents a collection of physical devices.
///     - The application may pass nullptr for pDrivers when only querying the
///       number of drivers.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - clGetPlatformIDs
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDriverGet(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                    ///< if count is zero, then the loader will update the value with the total
                                                    ///< number of drivers available.
                                                    ///< if count is non-zero, then the loader will only retrieve that number
                                                    ///< of drivers.
                                                    ///< if count is larger than the number of drivers available, then the
                                                    ///< loader will update the value with the correct number of drivers available.
    ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported API versions
/// 
/// @details
///     - API versions contain major and minor attributes, use
///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
typedef enum _ze_api_version_t
{
    ZE_API_VERSION_1_0 = ZE_MAKE_VERSION( 0, 91 ),  ///< 0.91

} ze_api_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns the API version supported by the specified driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == version`
__ze_api_export ze_result_t __zecall
zeDriverGetApiVersion(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_api_version_t* version                       ///< [out] api version
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_driver_properties_t
typedef enum _ze_driver_properties_version_t
{
    ZE_DRIVER_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} ze_driver_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DRIVER_UUID_SIZE
/// @brief Maximum driver universal unique id (UUID) size in bytes
#define ZE_MAX_DRIVER_UUID_SIZE  16
#endif // ZE_MAX_DRIVER_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Driver universal unique id (UUID)
typedef struct _ze_driver_uuid_t
{
    uint8_t id[ZE_MAX_DRIVER_UUID_SIZE];            ///< Opaque data representing a driver UUID

} ze_driver_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Driver properties queried using ::zeDriverGetProperties
typedef struct _ze_driver_properties_t
{
    ze_driver_properties_version_t version;         ///< [in] ::ZE_DRIVER_PROPERTIES_VERSION_CURRENT
    ze_driver_uuid_t uuid;                          ///< [out] universal unique identifier.
    uint32_t driverVersion;                         ///< [out] driver version
                                                    ///< The driver version is a non-zero, monotonically increasing value where
                                                    ///< higher values always indicate a more recent version.

} ze_driver_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves properties of the driver.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetPlatformInfo**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDriverProperties`
__ze_api_export ze_result_t __zecall
zeDriverGetProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_driver_ipc_properties_t
typedef enum _ze_driver_ipc_properties_version_t
{
    ZE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} ze_driver_ipc_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief IPC properties queried using ::zeDriverGetIPCProperties
typedef struct _ze_driver_ipc_properties_t
{
    ze_driver_ipc_properties_version_t version;     ///< [in] ::ZE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT
    ze_bool_t memsSupported;                        ///< [out] Supports passing memory allocations between processes. See
                                                    ///< ::::zeDriverGetMemIpcHandle.
    ze_bool_t eventsSupported;                      ///< [out] Supports passing events between processes. See
                                                    ///< ::::zeEventPoolGetIpcHandle.

} ze_driver_ipc_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves IPC attributes of the driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pIPCProperties`
__ze_api_export ze_result_t __zecall
zeDriverGetIPCProperties(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    ze_driver_ipc_properties_t* pIPCProperties      ///< [out] query result for IPC properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves an extension function for the specified driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clGetExtensionFunctionAddressForPlatform**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFuncName`
///         + `nullptr == pfunc`
__ze_api_export ze_result_t __zecall
zeDriverGetExtensionFunctionAddress(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    const char* pFuncName,                          ///< [in] name of the extension function
    void** pfunc                                    ///< [out] pointer to extension function
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_DRIVER_H
