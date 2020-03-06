/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_debug.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for Program Debug
 *
 */
 
#ifndef _ZET_DEBUG_H
#define _ZET_DEBUG_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_API_VERSION
/// @brief The API version.
#define ZET_DEBUG_API_VERSION  1
#endif // ZET_DEBUG_API_VERSION

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug session handle
typedef struct _zet_debug_session_handle_t *zet_debug_session_handle_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug configuration: version 1
typedef struct _zet_debug_config_v1_t
{
    int pid;                                        ///< The host process identifier

} zet_debug_config_v1_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug configuration: version-dependent fields
typedef union _zet_debug_config_variants_t
{
    zet_debug_config_v1_t v1;                       ///< Version 1

} zet_debug_config_variants_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug configuration
typedef struct _zet_debug_config_t
{
    uint16_t version;                               ///< The requested program debug API version
    zet_debug_config_variants_t variant;            ///< Version-specific fields

} zet_debug_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Attach to a device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == config`
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid device handle has been supplied
///         + an invalid configuration has been supplied
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + attaching to this device is not supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + caller does not have sufficient permissions
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + a debugger is already attached
__ze_api_export ze_result_t __zecall
zetDebugAttach(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    const zet_debug_config_t* config,               ///< [in] the debug configuration
    zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Close a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle has been supplied
__ze_api_export ze_result_t __zecall
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Query the number of device threads for a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNumThreads`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle has been supplied
__ze_api_export ze_result_t __zecall
zetDebugGetNumThreads(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t* pNumThreads                           ///< [out] the maximal number of threads
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_TIMEOUT_INFINITE
/// @brief An infinite timeout.
#define ZET_DEBUG_TIMEOUT_INFINITE  0xffffffffffffffffull
#endif // ZET_DEBUG_TIMEOUT_INFINITE

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug event flags.
typedef enum _zet_debug_event_flags_t
{
    ZET_DEBUG_EVENT_FLAG_NONE = 0,                  ///< No event flags
    ZET_DEBUG_EVENT_FLAG_STOPPED = ZE_BIT(0),       ///< The reporting thread stopped

} zet_debug_event_flags_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug event types.
typedef enum _zet_debug_event_type_t
{
    ZET_DEBUG_EVENT_INVALID = 0,                    ///< The event is invalid
    ZET_DEBUG_EVENT_DETACHED,                       ///< The tool was detached
    ZET_DEBUG_EVENT_PROCESS_ENTRY,                  ///< The debuggee process created command queues on the device
    ZET_DEBUG_EVENT_PROCESS_EXIT,                   ///< The debuggee process destroyed all command queues on the device
    ZET_DEBUG_EVENT_MODULE_LOAD,                    ///< An in-memory module was loaded onto the device
    ZET_DEBUG_EVENT_MODULE_UNLOAD,                  ///< An in-memory module is about to get unloaded from the device
    ZET_DEBUG_EVENT_EXCEPTION,                      ///< The thread stopped due to a device exception

} zet_debug_event_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Debug detach reason.
typedef enum _zet_debug_detach_reason_t
{
    ZET_DEBUG_DETACH_INVALID = 0,                   ///< The detach reason is not valid
    ZET_DEBUG_DETACH_HOST_EXIT,                     ///< The host process exited

} zet_debug_detach_reason_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_NONE
/// @brief No thread on the device.
#define ZET_DEBUG_THREAD_NONE  0xffffffffffffffffull
#endif // ZET_DEBUG_THREAD_NONE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_DEBUG_THREAD_ALL
/// @brief All threads on the device.
#define ZET_DEBUG_THREAD_ALL  0xfffffffffffffffeull
#endif // ZET_DEBUG_THREAD_ALL

///////////////////////////////////////////////////////////////////////////////
/// @brief Event information for ::ZET_DEBUG_EVENT_DETACHED
typedef struct _zet_debug_event_info_detached_t
{
    uint8_t reason;                                 ///< The detach reason

} zet_debug_event_info_detached_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event information for ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD
typedef struct _zet_debug_event_info_module_t
{
    uint64_t moduleBegin;                           ///< The begin address of the in-memory module
    uint64_t moduleEnd;                             ///< The end address of the in-memory module
    uint64_t load;                                  ///< The load address of the module on the device

} zet_debug_event_info_module_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Event type specific information
typedef union _zet_debug_event_info_t
{
    zet_debug_event_info_detached_t detached;       ///< type == ::ZET_DEBUG_EVENT_DETACHED
    zet_debug_event_info_module_t module;           ///< type == ::ZET_DEBUG_EVENT_MODULE_LOAD/UNLOAD

} zet_debug_event_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief A debug event on the device.
typedef struct _zet_debug_event_t
{
    uint8_t type;                                   ///< The event type
    uint64_t thread;                                ///< The thread reporting the event
    uint64_t flags;                                 ///< A bit-vector of ::zet_debug_event_flags_t
    zet_debug_event_info_t info;                    ///< Event type specific information

} zet_debug_event_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the topmost debug event.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or buffer pointer has been supplied
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///         + the output buffer is too small to hold the event
///     - ::ZE_RESULT_NOT_READY
///         + the timeout expired
__ze_api_export ze_result_t __zecall
zetDebugReadEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
    size_t size,                                    ///< [in] the size of the buffer in bytes
    void* buffer                                    ///< [in,out] a buffer to hold the event data
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Interrupt device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is already stopped or unavailable
__ze_api_export ze_result_t __zecall
zetDebugInterrupt(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resume device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is already running or unavailable
__ze_api_export ze_result_t __zecall
zetDebugResume(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory spaces for Intel Graphics devices.
typedef enum _zet_debug_memory_space_intel_graphics_t
{
    ZET_DEBUG_MEMORY_SPACE_GEN_DEFAULT = 0,         ///< default memory space (attribute may be omitted)
    ZET_DEBUG_MEMORY_SPACE_GEN_SLM,                 ///< shared local memory space

} zet_debug_memory_space_intel_graphics_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Read memory.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid address has been supplied
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the memory cannot be accessed from the supplied thread
__ze_api_export ze_result_t __zecall
zetDebugReadMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
    int memSpace,                                   ///< [in] the (device-specific) memory space
    uint64_t address,                               ///< [in] the virtual address of the memory to read from
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Write memory.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid address has been supplied
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the memory cannot be accessed from the supplied thread
__ze_api_export ze_result_t __zecall
zetDebugWriteMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
    int memSpace,                                   ///< [in] the (device-specific) memory space
    uint64_t address,                               ///< [in] the virtual address of the memory to write to
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Register file types for Intel Graphics devices.
typedef enum _zet_debug_state_intel_graphics_t
{
    ZET_DEBUG_STATE_GEN_INVALID = 0,                ///< An invalid register file
    ZET_DEBUG_STATE_GEN_GRF,                        ///< The general register file
    ZET_DEBUG_STATE_GEN_ACC,                        ///< The accumulator register file
    ZET_DEBUG_STATE_GEN_ADDR,                       ///< The address register file
    ZET_DEBUG_STATE_GEN_FLAG,                       ///< The flags register file

} zet_debug_state_intel_graphics_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief A register file descriptor.
typedef struct _zet_debug_state_section_t
{
    uint16_t type;                                  ///< The register file type type
    uint16_t version;                               ///< The register file version
    uint32_t size;                                  ///< The size of the register file in bytes
    uint64_t offset;                                ///< The offset into the register state area

} zet_debug_state_section_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief A register state descriptor.
typedef struct _zet_debug_state_t
{
    uint32_t size;                                  ///< The size of the register state object in bytes
    uint8_t headerSize;                             ///< The size of the register state descriptor in bytes
    uint8_t secSize;                                ///< The size of the register file descriptors in bytes
    uint16_t numSec;                                ///< The number of register file descriptors

} zet_debug_state_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Read register state.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid offset or size has been supplied
__ze_api_export ze_result_t __zecall
zetDebugReadState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Write register state.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + an invalid debug handle or thread identifier has been supplied
///         + the thread is running or unavailable
///         + an invalid offset or size has been supplied
__ze_api_export ze_result_t __zecall
zetDebugWriteState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_DEBUG_H
