/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_cmdlist.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Command List
 *
 */
 
#ifndef _ZE_CMDLIST_H
#define _ZE_CMDLIST_H
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
/// @brief API version of ::ze_command_list_desc_t
typedef enum _ze_command_list_desc_version_t
{
    ZE_COMMAND_LIST_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} ze_command_list_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported command list creation flags
typedef enum _ze_command_list_flag_t
{
    ZE_COMMAND_LIST_FLAG_NONE = 0,                  ///< default behavior
    ZE_COMMAND_LIST_FLAG_COPY_ONLY = ZE_BIT(0),     ///< command list **only** contains copy operations (and synchronization primitives).
                                                    ///< this command list may **only** be submitted to a command queue created
                                                    ///< with ::ZE_COMMAND_QUEUE_FLAG_COPY_ONLY.
    ZE_COMMAND_LIST_FLAG_RELAXED_ORDERING = ZE_BIT(1),  ///< driver may reorder programs and copys between barriers and
                                                    ///< synchronization primitives.
                                                    ///< using this flag may increase Host overhead of ::zeCommandListClose.
                                                    ///< therefore, this flag should **not** be set for low-latency usage-models.
    ZE_COMMAND_LIST_FLAG_MAXIMIZE_THROUGHPUT = ZE_BIT(2),   ///< driver may perform additional optimizations that increase dexecution
                                                    ///< throughput. 
                                                    ///< using this flag may increase Host overhead of ::zeCommandListClose and ::zeCommandQueueExecuteCommandLists.
                                                    ///< therefore, this flag should **not** be set for low-latency usage-models.
    ZE_COMMAND_LIST_FLAG_EXPLICIT_ONLY = ZE_BIT(3), ///< command list should be optimized for submission to a single command
                                                    ///< queue and device engine.
                                                    ///< driver **must** disable any implicit optimizations for distributing
                                                    ///< work across multiple engines.
                                                    ///< this flag should be used when applications want full control over
                                                    ///< multi-engine submission and scheduling.

} ze_command_list_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Command List descriptor
typedef struct _ze_command_list_desc_t
{
    ze_command_list_desc_version_t version;         ///< [in] ::ZE_COMMAND_LIST_DESC_VERSION_CURRENT
    ze_command_list_flag_t flags;                   ///< [in] creation flags

} ze_command_list_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device for submitting commands to any
///        command queue.
/// 
/// @details
///     - The command list can only be used on the device on which it was
///       created.
///     - The command list is created in the 'open' state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeCommandListCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a command list on the device with an implicit command queue
///        for immediate submission of commands.
/// 
/// @details
///     - The command list can only be used on the device on which it was
///       created.
///     - The command list is created in the 'open' state and never needs to be
///       closed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == altdesc`
///         + `nullptr == phCommandList`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_COMMAND_QUEUE_DESC_VERSION_CURRENT < altdesc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + altdesc->flags
///         + altdesc->mode
///         + altdesc->priority
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
__ze_api_export ze_result_t __zecall
zeCommandListCreateImmediate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
    ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a command list.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command list before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this command list.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeCommandListDestroy(
    ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a command list; ready to be executed by a command queue.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
__ze_api_export ze_result_t __zecall
zeCommandListClose(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset a command list to initial (empty) state; ready for appending
///        commands.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the command list before it is reset
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
__ze_api_export ze_result_t __zecall
zeCommandListReset(
    ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_CMDLIST_H
