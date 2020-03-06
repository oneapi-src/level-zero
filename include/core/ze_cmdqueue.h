/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_cmdqueue.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Command Queue
 *
 */
 
#ifndef _ZE_CMDQUEUE_H
#define _ZE_CMDQUEUE_H
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
/// @brief API version of ::ze_command_queue_desc_t
typedef enum _ze_command_queue_desc_version_t
{
    ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),   ///< version 0.91

} ze_command_queue_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue flags
typedef enum _ze_command_queue_flag_t
{
    ZE_COMMAND_QUEUE_FLAG_NONE = 0,                 ///< default behavior
    ZE_COMMAND_QUEUE_FLAG_COPY_ONLY = ZE_BIT(0),    ///< command queue only supports enqueuing copy-only command lists
    ZE_COMMAND_QUEUE_FLAG_LOGICAL_ONLY = ZE_BIT(1), ///< command queue is not tied to a physical command queue; driver may
                                                    ///< dynamically assign based on usage
    ZE_COMMAND_QUEUE_FLAG_SINGLE_SLICE_ONLY = ZE_BIT(2),///< command queue reserves and cannot consume more than a single slice.
                                                    ///< 'slice' size is device-specific.  cannot be combined with COPY_ONLY.
    ZE_COMMAND_QUEUE_FLAG_SUPPORTS_COOPERATIVE_KERNELS = ZE_BIT(3), ///< command queue supports command list with cooperative kernels. See
                                                    ///< ::zeCommandListAppendLaunchCooperativeKernel for more details. cannot
                                                    ///< be combined with COPY_ONLY.

} ze_command_queue_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue modes
typedef enum _ze_command_queue_mode_t
{
    ZE_COMMAND_QUEUE_MODE_DEFAULT = 0,              ///< implicit default behavior; uses driver-based heuristics
    ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS,              ///< Device execution always completes immediately on execute;
                                                    ///< Host thread is blocked using wait on implicit synchronization object
    ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS,             ///< Device execution is scheduled and will complete in future;
                                                    ///< explicit synchronization object must be used to determine completeness

} ze_command_queue_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command queue priorities
typedef enum _ze_command_queue_priority_t
{
    ZE_COMMAND_QUEUE_PRIORITY_NORMAL = 0,           ///< [default] normal priority
    ZE_COMMAND_QUEUE_PRIORITY_LOW,                  ///< lower priority than normal
    ZE_COMMAND_QUEUE_PRIORITY_HIGH,                 ///< higher priority than normal

} ze_command_queue_priority_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command Queue descriptor
typedef struct _ze_command_queue_desc_t
{
    ze_command_queue_desc_version_t version;        ///< [in] ::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT
    ze_command_queue_flag_t flags;                  ///< [in] creation flags
    ze_command_queue_mode_t mode;                   ///< [in] operation mode
    ze_command_queue_priority_t priority;           ///< [in] priority
    uint32_t ordinal;                               ///< [in] if logical-only flag is set, then will be ignored;
                                                    ///< if supports-cooperative-kernels is set, then may be ignored;
                                                    ///< else-if copy-only flag is set, then must be less than ::ze_device_properties_t.numAsyncCopyEngines;
                                                    ///< otherwise must be less than
                                                    ///< ::ze_device_properties_t.numAsyncComputeEngines. When using sub-devices
                                                    ///< the ::ze_device_properties_t.numAsyncComputeEngines must be queried
                                                    ///< from the sub-device being used.

} ze_command_queue_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command queue on the device.
/// 
/// @details
///     - The command queue can only be used on the device on which it was
///       created.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clCreateCommandQueue**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandQueue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///         + desc->mode
///         + desc->priority
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeCommandQueueCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command queue.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command queue before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command queue
///     - The application may **not** call this function from simultaneous
///       threads with the same command queue handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clReleaseCommandQueue**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeCommandQueueDestroy(
    ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Executes a command list in a command queue.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - vkQueueSubmit
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phCommandLists`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `0 == numCommandLists`
///     - ::ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zeCommandQueueExecuteCommandLists(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                    ///< to execute
    ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Synchronizes a command queue by waiting on the host.
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
///         + `nullptr == hCommandQueue`
///     - ::ZE_RESULT_NOT_READY
///         + timeout expired
__ze_api_export ze_result_t __zecall
zeCommandQueueSynchronize(
    ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                    ///< returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                    ///< if UINT32_MAX, then function will not return until complete or device
                                                    ///< is lost.
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_CMDQUEUE_H
