/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "zet_lib.h"

extern "C" {

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
ze_result_t __zecall
zetDebugAttach(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    const zet_debug_config_t* config,               ///< [in] the debug configuration
    zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
    )
{
    auto pfnAttach = zet_lib::context.ddiTable.Debug.pfnAttach;
    if( nullptr == pfnAttach )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAttach( hDevice, config, hDebug );
}

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
ze_result_t __zecall
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    )
{
    auto pfnDetach = zet_lib::context.ddiTable.Debug.pfnDetach;
    if( nullptr == pfnDetach )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDetach( hDebug );
}

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
ze_result_t __zecall
zetDebugGetNumThreads(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t* pNumThreads                           ///< [out] the maximal number of threads
    )
{
    auto pfnGetNumThreads = zet_lib::context.ddiTable.Debug.pfnGetNumThreads;
    if( nullptr == pfnGetNumThreads )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetNumThreads( hDebug, pNumThreads );
}

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
ze_result_t __zecall
zetDebugReadEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
    size_t size,                                    ///< [in] the size of the buffer in bytes
    void* buffer                                    ///< [in,out] a buffer to hold the event data
    )
{
    auto pfnReadEvent = zet_lib::context.ddiTable.Debug.pfnReadEvent;
    if( nullptr == pfnReadEvent )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadEvent( hDebug, timeout, size, buffer );
}

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
ze_result_t __zecall
zetDebugInterrupt(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
    )
{
    auto pfnInterrupt = zet_lib::context.ddiTable.Debug.pfnInterrupt;
    if( nullptr == pfnInterrupt )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnInterrupt( hDebug, threadid );
}

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
ze_result_t __zecall
zetDebugResume(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
    )
{
    auto pfnResume = zet_lib::context.ddiTable.Debug.pfnResume;
    if( nullptr == pfnResume )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnResume( hDebug, threadid );
}

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
ze_result_t __zecall
zetDebugReadMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
    int memSpace,                                   ///< [in] the (device-specific) memory space
    uint64_t address,                               ///< [in] the virtual address of the memory to read from
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
    )
{
    auto pfnReadMemory = zet_lib::context.ddiTable.Debug.pfnReadMemory;
    if( nullptr == pfnReadMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadMemory( hDebug, threadid, memSpace, address, size, buffer );
}

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
ze_result_t __zecall
zetDebugWriteMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context or ::ZET_DEBUG_THREAD_NONE
    int memSpace,                                   ///< [in] the (device-specific) memory space
    uint64_t address,                               ///< [in] the virtual address of the memory to write to
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    )
{
    auto pfnWriteMemory = zet_lib::context.ddiTable.Debug.pfnWriteMemory;
    if( nullptr == pfnWriteMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnWriteMemory( hDebug, threadid, memSpace, address, size, buffer );
}

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
ze_result_t __zecall
zetDebugReadState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
    )
{
    auto pfnReadState = zet_lib::context.ddiTable.Debug.pfnReadState;
    if( nullptr == pfnReadState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadState( hDebug, threadid, offset, size, buffer );
}

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
ze_result_t __zecall
zetDebugWriteState(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t threadid,                              ///< [in] the thread context
    uint64_t offset,                                ///< [in] the offset into the register state area
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    )
{
    auto pfnWriteState = zet_lib::context.ddiTable.Debug.pfnWriteState;
    if( nullptr == pfnWriteState )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnWriteState( hDebug, threadid, offset, size, buffer );
}

} // extern "C"
