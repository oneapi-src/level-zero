/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_libapi.cpp
 *
 * @brief C++ static library for zet
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve debug info from module.
/// 
/// @details
///     - The caller can pass nullptr for pDebugInfo when querying only for
///       size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hModule`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZET_MODULE_DEBUG_INFO_FORMAT_ELF_DWARF < format`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t ZE_APICALL
zetModuleGetDebugInfo(
    zet_module_handle_t hModule,                    ///< [in] handle of the module
    zet_module_debug_info_format_t format,          ///< [in] debug info format requested
    size_t* pSize,                                  ///< [in,out] size of debug info in bytes
    uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnModuleGetDebugInfo_t pfnGetDebugInfo = [&result] {
        auto pfnGetDebugInfo = ze_lib::context->zetDdiTable.load()->Module.pfnGetDebugInfo;
        if( nullptr == pfnGetDebugInfo ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDebugInfo;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDebugInfo = ze_lib::context->zetDdiTable.load()->Module.pfnGetDebugInfo;
    if( nullptr == pfnGetDebugInfo ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves debug properties of the device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDebugProperties`
ze_result_t ZE_APICALL
zetDeviceGetDebugProperties(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    zet_device_debug_properties_t* pDebugProperties ///< [in,out] query result for debug properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDeviceGetDebugProperties_t pfnGetDebugProperties = [&result] {
        auto pfnGetDebugProperties = ze_lib::context->zetDdiTable.load()->Device.pfnGetDebugProperties;
        if( nullptr == pfnGetDebugProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDebugProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDebugProperties( hDevice, pDebugProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDebugProperties = ze_lib::context->zetDdiTable.load()->Device.pfnGetDebugProperties;
    if( nullptr == pfnGetDebugProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDebugProperties( hDevice, pDebugProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Attach to a device.
/// 
/// @details
///     - The device must be enabled for debug; see
///       ::zesSchedulerSetComputeUnitDebugMode.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == config`
///         + `nullptr == phDebug`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + attaching to this device is not supported
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + caller does not have sufficient permissions
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + a debugger is already attached
ze_result_t ZE_APICALL
zetDebugAttach(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    const zet_debug_config_t* config,               ///< [in] the debug configuration
    zet_debug_session_handle_t* phDebug             ///< [out] debug session handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugAttach_t pfnAttach = [&result] {
        auto pfnAttach = ze_lib::context->zetDdiTable.load()->Debug.pfnAttach;
        if( nullptr == pfnAttach ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAttach;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAttach( hDevice, config, phDebug );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAttach = ze_lib::context->zetDdiTable.load()->Debug.pfnAttach;
    if( nullptr == pfnAttach ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAttach( hDevice, config, phDebug );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Close a debug session.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
ze_result_t ZE_APICALL
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugDetach_t pfnDetach = [&result] {
        auto pfnDetach = ze_lib::context->zetDdiTable.load()->Debug.pfnDetach;
        if( nullptr == pfnDetach ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDetach;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDetach( hDebug );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDetach = ze_lib::context->zetDdiTable.load()->Debug.pfnDetach;
    if( nullptr == pfnDetach ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDetach( hDebug );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the topmost debug event.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == event`
///     - ::ZE_RESULT_NOT_READY
///         + the timeout expired
ze_result_t ZE_APICALL
zetDebugReadEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then immediately returns the status of the event;
                                                    ///< if `UINT64_MAX`, then function will not return until complete or
                                                    ///< device is lost.
                                                    ///< Due to external dependencies, timeout may be rounded to the closest
                                                    ///< value allowed by the accuracy of those dependencies.
    zet_debug_event_t* event                        ///< [in,out] a pointer to a ::zet_debug_event_t.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugReadEvent_t pfnReadEvent = [&result] {
        auto pfnReadEvent = ze_lib::context->zetDdiTable.load()->Debug.pfnReadEvent;
        if( nullptr == pfnReadEvent ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReadEvent;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReadEvent( hDebug, timeout, event );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadEvent = ze_lib::context->zetDdiTable.load()->Debug.pfnReadEvent;
    if( nullptr == pfnReadEvent ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadEvent( hDebug, timeout, event );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Acknowledge a debug event.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == event`
ze_result_t ZE_APICALL
zetDebugAcknowledgeEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    const zet_debug_event_t* event                  ///< [in] a pointer to a ::zet_debug_event_t.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugAcknowledgeEvent_t pfnAcknowledgeEvent = [&result] {
        auto pfnAcknowledgeEvent = ze_lib::context->zetDdiTable.load()->Debug.pfnAcknowledgeEvent;
        if( nullptr == pfnAcknowledgeEvent ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAcknowledgeEvent;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAcknowledgeEvent( hDebug, event );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAcknowledgeEvent = ze_lib::context->zetDdiTable.load()->Debug.pfnAcknowledgeEvent;
    if( nullptr == pfnAcknowledgeEvent ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAcknowledgeEvent( hDebug, event );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Interrupt device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is already stopped or unavailable
ze_result_t ZE_APICALL
zetDebugInterrupt(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread                       ///< [in] the thread to interrupt
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugInterrupt_t pfnInterrupt = [&result] {
        auto pfnInterrupt = ze_lib::context->zetDdiTable.load()->Debug.pfnInterrupt;
        if( nullptr == pfnInterrupt ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnInterrupt;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnInterrupt( hDebug, thread );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInterrupt = ze_lib::context->zetDdiTable.load()->Debug.pfnInterrupt;
    if( nullptr == pfnInterrupt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnInterrupt( hDebug, thread );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Resume device threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is already running or unavailable
ze_result_t ZE_APICALL
zetDebugResume(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread                       ///< [in] the thread to resume
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugResume_t pfnResume = [&result] {
        auto pfnResume = ze_lib::context->zetDdiTable.load()->Debug.pfnResume;
        if( nullptr == pfnResume ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnResume;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnResume( hDebug, thread );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnResume = ze_lib::context->zetDdiTable.load()->Debug.pfnResume;
    if( nullptr == pfnResume ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnResume( hDebug, thread );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read memory.
/// 
/// @details
///     - The thread identifier 'all' can be used for accessing the default
///       memory space, e.g. for setting breakpoints.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZET_DEBUG_MEMORY_SPACE_TYPE_ELF < desc->type`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is running or unavailable
///         + the memory cannot be accessed from the supplied thread
ze_result_t ZE_APICALL
zetDebugReadMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread,                      ///< [in] the thread identifier.
    const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
    size_t size,                                    ///< [in] the number of bytes to read
    void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugReadMemory_t pfnReadMemory = [&result] {
        auto pfnReadMemory = ze_lib::context->zetDdiTable.load()->Debug.pfnReadMemory;
        if( nullptr == pfnReadMemory ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReadMemory;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReadMemory( hDebug, thread, desc, size, buffer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadMemory = ze_lib::context->zetDdiTable.load()->Debug.pfnReadMemory;
    if( nullptr == pfnReadMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadMemory( hDebug, thread, desc, size, buffer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Write memory.
/// 
/// @details
///     - The thread identifier 'all' can be used for accessing the default
///       memory space, e.g. for setting breakpoints.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == buffer`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZET_DEBUG_MEMORY_SPACE_TYPE_ELF < desc->type`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is running or unavailable
///         + the memory cannot be accessed from the supplied thread
ze_result_t ZE_APICALL
zetDebugWriteMemory(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread,                      ///< [in] the thread identifier.
    const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
    size_t size,                                    ///< [in] the number of bytes to write
    const void* buffer                              ///< [in] a buffer holding the pattern to write
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugWriteMemory_t pfnWriteMemory = [&result] {
        auto pfnWriteMemory = ze_lib::context->zetDdiTable.load()->Debug.pfnWriteMemory;
        if( nullptr == pfnWriteMemory ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnWriteMemory;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnWriteMemory( hDebug, thread, desc, size, buffer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnWriteMemory = ze_lib::context->zetDdiTable.load()->Debug.pfnWriteMemory;
    if( nullptr == pfnWriteMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnWriteMemory( hDebug, thread, desc, size, buffer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves debug register set properties.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zetDebugGetRegisterSetProperties(
    zet_device_handle_t hDevice,                    ///< [in] device handle
    uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of register set properties available.
                                                    ///< if count is greater than the number of register set properties
                                                    ///< available, then the driver shall update the value with the correct
                                                    ///< number of registry set properties available.
    zet_debug_regset_properties_t* pRegisterSetProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< register set properties.
                                                    ///< if count is less than the number of register set properties available,
                                                    ///< then driver shall only retrieve that number of register set properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugGetRegisterSetProperties_t pfnGetRegisterSetProperties = [&result] {
        auto pfnGetRegisterSetProperties = ze_lib::context->zetDdiTable.load()->Debug.pfnGetRegisterSetProperties;
        if( nullptr == pfnGetRegisterSetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetRegisterSetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRegisterSetProperties = ze_lib::context->zetDdiTable.load()->Debug.pfnGetRegisterSetProperties;
    if( nullptr == pfnGetRegisterSetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves debug register set properties for a given thread.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is running or unavailable
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + the thread argument specifies more than one or a non-existant thread
ze_result_t ZE_APICALL
zetDebugGetThreadRegisterSetProperties(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread,                      ///< [in] the thread identifier specifying a single stopped thread
    uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of register set properties available.
                                                    ///< if count is greater than the number of register set properties
                                                    ///< available, then the driver shall update the value with the correct
                                                    ///< number of registry set properties available.
    zet_debug_regset_properties_t* pRegisterSetProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< register set properties.
                                                    ///< if count is less than the number of register set properties available,
                                                    ///< then driver shall only retrieve that number of register set properties.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugGetThreadRegisterSetProperties_t pfnGetThreadRegisterSetProperties = [&result] {
        auto pfnGetThreadRegisterSetProperties = ze_lib::context->zetDdiTable.load()->Debug.pfnGetThreadRegisterSetProperties;
        if( nullptr == pfnGetThreadRegisterSetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetThreadRegisterSetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetThreadRegisterSetProperties = ze_lib::context->zetDdiTable.load()->Debug.pfnGetThreadRegisterSetProperties;
    if( nullptr == pfnGetThreadRegisterSetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read register state.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is running or unavailable
ze_result_t ZE_APICALL
zetDebugReadRegisters(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread,                      ///< [in] the thread identifier
    uint32_t type,                                  ///< [in] register set type
    uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                    ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                    ///< type
    uint32_t count,                                 ///< [in] the number of registers to read; start+count must be less than or
                                                    ///< equal to the `count` member of ::zet_debug_regset_properties_t for the
                                                    ///< type
    void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugReadRegisters_t pfnReadRegisters = [&result] {
        auto pfnReadRegisters = ze_lib::context->zetDdiTable.load()->Debug.pfnReadRegisters;
        if( nullptr == pfnReadRegisters ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReadRegisters;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadRegisters = ze_lib::context->zetDdiTable.load()->Debug.pfnReadRegisters;
    if( nullptr == pfnReadRegisters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Write register state.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDebug`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is running or unavailable
ze_result_t ZE_APICALL
zetDebugWriteRegisters(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread,                      ///< [in] the thread identifier
    uint32_t type,                                  ///< [in] register set type
    uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                    ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                    ///< type
    uint32_t count,                                 ///< [in] the number of registers to write; start+count must be less than
                                                    ///< or equal to the `count` member of ::zet_debug_regset_properties_t for
                                                    ///< the type
    void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDebugWriteRegisters_t pfnWriteRegisters = [&result] {
        auto pfnWriteRegisters = ze_lib::context->zetDdiTable.load()->Debug.pfnWriteRegisters;
        if( nullptr == pfnWriteRegisters ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnWriteRegisters;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnWriteRegisters = ze_lib::context->zetDdiTable.load()->Debug.pfnWriteRegisters;
    if( nullptr == pfnWriteRegisters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves metric group for a device.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zetMetricGroupGet(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metric groups available.
                                                    ///< if count is greater than the number of metric groups available, then
                                                    ///< the driver shall update the value with the correct number of metric
                                                    ///< groups available.
    zet_metric_group_handle_t* phMetricGroups       ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups.
                                                    ///< if count is less than the number of metric groups available, then
                                                    ///< driver shall only retrieve that number of metric groups.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupGet_t pfnGet = [&result] {
        auto pfnGet = ze_lib::context->zetDdiTable.load()->MetricGroup.pfnGet;
        if( nullptr == pfnGet ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGet;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGet( hDevice, pCount, phMetricGroups );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zetDdiTable.load()->MetricGroup.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( hDevice, pCount, phMetricGroups );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a metric group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zetMetricGroupGetProperties(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zetDdiTable.load()->MetricGroup.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hMetricGroup, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zetDdiTable.load()->MetricGroup.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hMetricGroup, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Calculates metric values from raw data.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZET_METRIC_GROUP_CALCULATION_TYPE_MAX_METRIC_VALUES < type`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawData`
///         + `nullptr == pMetricValueCount`
ze_result_t ZE_APICALL
zetMetricGroupCalculateMetricValues(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
    size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
    const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
    uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metric values to be calculated.
                                                    ///< if count is greater than the number available in the raw data buffer,
                                                    ///< then the driver shall update the value with the actual number of
                                                    ///< metric values to be calculated.
    zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated metrics.
                                                    ///< if count is less than the number available in the raw data buffer,
                                                    ///< then driver shall only calculate that number of metric values.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupCalculateMetricValues_t pfnCalculateMetricValues = [&result] {
        auto pfnCalculateMetricValues = ze_lib::context->zetDdiTable.load()->MetricGroup.pfnCalculateMetricValues;
        if( nullptr == pfnCalculateMetricValues ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCalculateMetricValues;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCalculateMetricValues = ze_lib::context->zetDdiTable.load()->MetricGroup.pfnCalculateMetricValues;
    if( nullptr == pfnCalculateMetricValues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves metric from a metric group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zetMetricGet(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metrics available.
                                                    ///< if count is greater than the number of metrics available, then the
                                                    ///< driver shall update the value with the correct number of metrics available.
    zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics.
                                                    ///< if count is less than the number of metrics available, then driver
                                                    ///< shall only retrieve that number of metrics.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGet_t pfnGet = [&result] {
        auto pfnGet = ze_lib::context->zetDdiTable.load()->Metric.pfnGet;
        if( nullptr == pfnGet ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGet;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGet( hMetricGroup, pCount, phMetrics );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zetDdiTable.load()->Metric.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( hMetricGroup, pCount, phMetrics );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves attributes of a metric.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetric`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zetMetricGetProperties(
    zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    zet_metric_properties_t* pProperties            ///< [in,out] metric properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGetProperties_t pfnGetProperties = [&result] {
        auto pfnGetProperties = ze_lib::context->zetDdiTable.load()->Metric.pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProperties;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProperties( hMetric, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zetDdiTable.load()->Metric.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hMetric, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Activates metric groups.
/// 
/// @details
///     - Immediately reconfigures the device to activate only those metric
///       groups provided.
///     - Any metric groups previously activated but not provided will be
///       deactivated.
///     - Deactivating metric groups that are still in-use will result in
///       undefined behavior.
///     - All metric groups must have different domains, see
///       ::zet_metric_group_properties_t.
///     - The application must **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phMetricGroups) && (0 < count)`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + Multiple metric groups share the same domain
ze_result_t ZE_APICALL
zetContextActivateMetricGroups(
    zet_context_handle_t hContext,                  ///< [in] handle of the context object
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate; must be 0 if `nullptr ==
                                                    ///< phMetricGroups`
    zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to activate.
                                                    ///< nullptr deactivates all previously used metric groups.
                                                    ///< all metrics groups must come from a different domains.
                                                    ///< metric query and metric stream must use activated metric groups.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnContextActivateMetricGroups_t pfnActivateMetricGroups = [&result] {
        auto pfnActivateMetricGroups = ze_lib::context->zetDdiTable.load()->Context.pfnActivateMetricGroups;
        if( nullptr == pfnActivateMetricGroups ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnActivateMetricGroups;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnActivateMetricGroups( hContext, hDevice, count, phMetricGroups );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnActivateMetricGroups = ze_lib::context->zetDdiTable.load()->Context.pfnActivateMetricGroups;
    if( nullptr == pfnActivateMetricGroups ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnActivateMetricGroups( hContext, hDevice, count, phMetricGroups );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens metric streamer for a device.
/// 
/// @details
///     - The notification event must have been created from an event pool that
///       was created using ::ZE_EVENT_POOL_FLAG_HOST_VISIBLE flag.
///     - The duration of the signal event created from an event pool that was
///       created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag is undefined.
///       However, for consistency and orthogonality the event will report
///       correctly as signaled when used by other event API functionality.
///     - The application must **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phMetricStreamer`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zetMetricStreamerOpen(
    zet_context_handle_t hContext,                  ///< [in] handle of the context object
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_streamer_desc_t* desc,               ///< [in,out] metric streamer descriptor
    ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification
    zet_metric_streamer_handle_t* phMetricStreamer  ///< [out] handle of metric streamer
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricStreamerOpen_t pfnOpen = [&result] {
        auto pfnOpen = ze_lib::context->zetDdiTable.load()->MetricStreamer.pfnOpen;
        if( nullptr == pfnOpen ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnOpen;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOpen = ze_lib::context->zetDdiTable.load()->MetricStreamer.pfnOpen;
    if( nullptr == pfnOpen ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Append metric streamer marker into a command list.
/// 
/// @details
///     - The application must ensure the metric streamer is accessible by the
///       device on which the command list was created.
///     - The application must ensure the command list and metric streamer were
///       created on the same context.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
///     - Allow to associate metric stream time based metrics with executed
///       workload.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricStreamer`
ze_result_t ZE_APICALL
zetCommandListAppendMetricStreamerMarker(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
    uint32_t value                                  ///< [in] streamer marker value
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnCommandListAppendMetricStreamerMarker_t pfnAppendMetricStreamerMarker = [&result] {
        auto pfnAppendMetricStreamerMarker = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricStreamerMarker;
        if( nullptr == pfnAppendMetricStreamerMarker ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMetricStreamerMarker;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricStreamerMarker = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricStreamerMarker;
    if( nullptr == pfnAppendMetricStreamerMarker ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes metric streamer.
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same metric streamer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricStreamer`
ze_result_t ZE_APICALL
zetMetricStreamerClose(
    zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricStreamerClose_t pfnClose = [&result] {
        auto pfnClose = ze_lib::context->zetDdiTable.load()->MetricStreamer.pfnClose;
        if( nullptr == pfnClose ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnClose;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnClose( hMetricStreamer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnClose = ze_lib::context->zetDdiTable.load()->MetricStreamer.pfnClose;
    if( nullptr == pfnClose ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnClose( hMetricStreamer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from metric streamer.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricStreamer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
///     - ::ZE_RESULT_WARNING_DROPPED_DATA
///         + Metric streamer data may have been dropped. Reduce sampling period.
ze_result_t ZE_APICALL
zetMetricStreamerReadData(
    zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
    uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                    ///< if `UINT32_MAX`, then function will retrieve all reports available
    size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                    ///< if size is zero, then the driver will update the value with the total
                                                    ///< size in bytes needed for all reports available.
                                                    ///< if size is non-zero, then driver will only retrieve the number of
                                                    ///< reports that fit into the buffer.
                                                    ///< if size is larger than size needed for all reports, then driver will
                                                    ///< update the value with the actual size needed.
    uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing streamer
                                                    ///< reports in raw format
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricStreamerReadData_t pfnReadData = [&result] {
        auto pfnReadData = ze_lib::context->zetDdiTable.load()->MetricStreamer.pfnReadData;
        if( nullptr == pfnReadData ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReadData;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadData = ze_lib::context->zetDdiTable.load()->MetricStreamer.pfnReadData;
    if( nullptr == pfnReadData ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool of metric queries on the context.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phMetricQueryPool`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZET_METRIC_QUERY_POOL_TYPE_EXECUTION < desc->type`
ze_result_t ZE_APICALL
zetMetricQueryPoolCreate(
    zet_context_handle_t hContext,                  ///< [in] handle of the context object
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
    const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
    zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricQueryPoolCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zetDdiTable.load()->MetricQueryPool.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zetDdiTable.load()->MetricQueryPool.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a query pool object.
/// 
/// @details
///     - The application must destroy all query handles created from the pool
///       before destroying the pool itself.
///     - The application must ensure the device is not currently referencing
///       the any query within the pool before it is deleted.
///     - The application must **not** call this function from simultaneous
///       threads with the same query pool handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQueryPool`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zetMetricQueryPoolDestroy(
    zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricQueryPoolDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zetDdiTable.load()->MetricQueryPool.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hMetricQueryPool );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zetDdiTable.load()->MetricQueryPool.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hMetricQueryPool );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates metric query from the pool.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQueryPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phMetricQuery`
ze_result_t ZE_APICALL
zetMetricQueryCreate(
    zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t index,                                 ///< [in] index of the query within the pool
    zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricQueryCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hMetricQueryPool, index, phMetricQuery );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hMetricQueryPool, index, phMetricQuery );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a metric query object.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the query before it is deleted.
///     - The application must **not** call this function from simultaneous
///       threads with the same query handle.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zetMetricQueryDestroy(
    zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricQueryDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hMetricQuery );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hMetricQuery );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets a metric query object back to initial state.
/// 
/// @details
///     - The application must ensure the device is not currently referencing
///       the query before it is reset
///     - The application must **not** call this function from simultaneous
///       threads with the same query handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
ze_result_t ZE_APICALL
zetMetricQueryReset(
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricQueryReset_t pfnReset = [&result] {
        auto pfnReset = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnReset;
        if( nullptr == pfnReset ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReset;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReset( hMetricQuery );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hMetricQuery );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query begin into a command list.
/// 
/// @details
///     - The application must ensure the metric query is accessible by the
///       device on which the command list was created.
///     - The application must ensure the command list and metric query were
///       created on the same context.
///     - This command blocks all following commands from beginning until the
///       execution of the query completes.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
ze_result_t ZE_APICALL
zetCommandListAppendMetricQueryBegin(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnCommandListAppendMetricQueryBegin_t pfnAppendMetricQueryBegin = [&result] {
        auto pfnAppendMetricQueryBegin = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricQueryBegin;
        if( nullptr == pfnAppendMetricQueryBegin ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMetricQueryBegin;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricQueryBegin = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricQueryBegin;
    if( nullptr == pfnAppendMetricQueryBegin ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query end into a command list.
/// 
/// @details
///     - The application must ensure the metric query and events are accessible
///       by the device on which the command list was created.
///     - The application must ensure the command list, events and metric query
///       were created on the same context.
///     - The duration of the signal event created from an event pool that was
///       created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag is undefined.
///       However, for consistency and orthogonality the event will report
///       correctly as signaled when used by other event API functionality.
///     - If numWaitEvents is zero, then all previous commands are completed
///       prior to the execution of the query.
///     - If numWaitEvents is non-zero, then all phWaitEvents must be signaled
///       prior to the execution of the query.
///     - This command blocks all following commands from beginning until the
///       execution of the query completes.
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + `(nullptr == phWaitEvents) && (0 < numWaitEvents)`
ze_result_t ZE_APICALL
zetCommandListAppendMetricQueryEnd(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in] must be zero
    ze_event_handle_t* phWaitEvents                 ///< [in][mbz] must be nullptr
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnCommandListAppendMetricQueryEnd_t pfnAppendMetricQueryEnd = [&result] {
        auto pfnAppendMetricQueryEnd = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricQueryEnd;
        if( nullptr == pfnAppendMetricQueryEnd ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMetricQueryEnd;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricQueryEnd = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricQueryEnd;
    if( nullptr == pfnAppendMetricQueryEnd ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query commands to flush all caches.
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zetCommandListAppendMetricMemoryBarrier(
    zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnCommandListAppendMetricMemoryBarrier_t pfnAppendMetricMemoryBarrier = [&result] {
        auto pfnAppendMetricMemoryBarrier = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricMemoryBarrier;
        if( nullptr == pfnAppendMetricMemoryBarrier ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMetricMemoryBarrier;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMetricMemoryBarrier( hCommandList );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricMemoryBarrier = ze_lib::context->zetDdiTable.load()->CommandList.pfnAppendMetricMemoryBarrier;
    if( nullptr == pfnAppendMetricMemoryBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricMemoryBarrier( hCommandList );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves raw data for a given metric query.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
ze_result_t ZE_APICALL
zetMetricQueryGetData(
    zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                    ///< if size is zero, then the driver will update the value with the total
                                                    ///< size in bytes needed for all reports available.
                                                    ///< if size is non-zero, then driver will only retrieve the number of
                                                    ///< reports that fit into the buffer.
                                                    ///< if size is larger than size needed for all reports, then driver will
                                                    ///< update the value with the actual size needed.
    uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                    ///< reports in raw format
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricQueryGetData_t pfnGetData = [&result] {
        auto pfnGetData = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnGetData;
        if( nullptr == pfnGetData ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetData;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetData = ze_lib::context->zetDdiTable.load()->MetricQuery.pfnGetData;
    if( nullptr == pfnGetData ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve profiling information generated for the kernel.
/// 
/// @details
///     - Module must be created using the following build option:
///         + "-zet-profile-flags <n>" - enable generation of profile
///           information
///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProfileProperties`
ze_result_t ZE_APICALL
zetKernelGetProfileInfo(
    zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
    zet_profile_properties_t* pProfileProperties    ///< [out] pointer to profile properties
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnKernelGetProfileInfo_t pfnGetProfileInfo = [&result] {
        auto pfnGetProfileInfo = ze_lib::context->zetDdiTable.load()->Kernel.pfnGetProfileInfo;
        if( nullptr == pfnGetProfileInfo ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetProfileInfo;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetProfileInfo( hKernel, pProfileProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProfileInfo = ze_lib::context->zetDdiTable.load()->Kernel.pfnGetProfileInfo;
    if( nullptr == pfnGetProfileInfo ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProfileInfo( hKernel, pProfileProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a tracer on the context.
/// 
/// @details
///     - The application must only use the tracer for the context which was
///       provided during creation.
///     - The tracer is created in the disabled state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pUserData`
///         + `nullptr == phTracer`
ze_result_t ZE_APICALL
zetTracerExpCreate(
    zet_context_handle_t hContext,                  ///< [in] handle of the context object
    const zet_tracer_exp_desc_t* desc,              ///< [in] pointer to tracer descriptor
    zet_tracer_exp_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnTracerExpCreate_t pfnCreate = [&result] {
        auto pfnCreate = ze_lib::context->zetDdiTable.load()->TracerExp.pfnCreate;
        if( nullptr == pfnCreate ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreate;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreate( hContext, desc, phTracer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zetDdiTable.load()->TracerExp.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, desc, phTracer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a tracer.
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
///     - The implementation of this function must be thread-safe.
///     - The implementation of this function will stall and wait on any
///       outstanding threads executing callbacks before freeing any Host
///       allocations associated with this tracer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zetTracerExpDestroy(
    zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnTracerExpDestroy_t pfnDestroy = [&result] {
        auto pfnDestroy = ze_lib::context->zetDdiTable.load()->TracerExp.pfnDestroy;
        if( nullptr == pfnDestroy ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroy;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroy( hTracer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zetDdiTable.load()->TracerExp.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hTracer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **before** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t ZE_APICALL
zetTracerExpSetPrologues(
    zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnTracerExpSetPrologues_t pfnSetPrologues = [&result] {
        auto pfnSetPrologues = ze_lib::context->zetDdiTable.load()->TracerExp.pfnSetPrologues;
        if( nullptr == pfnSetPrologues ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetPrologues;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetPrologues( hTracer, pCoreCbs );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetPrologues = ze_lib::context->zetDdiTable.load()->TracerExp.pfnSetPrologues;
    if( nullptr == pfnSetPrologues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetPrologues( hTracer, pCoreCbs );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **after** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t ZE_APICALL
zetTracerExpSetEpilogues(
    zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
    zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnTracerExpSetEpilogues_t pfnSetEpilogues = [&result] {
        auto pfnSetEpilogues = ze_lib::context->zetDdiTable.load()->TracerExp.pfnSetEpilogues;
        if( nullptr == pfnSetEpilogues ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetEpilogues;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetEpilogues( hTracer, pCoreCbs );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEpilogues = ze_lib::context->zetDdiTable.load()->TracerExp.pfnSetEpilogues;
    if( nullptr == pfnSetEpilogues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEpilogues( hTracer, pCoreCbs );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enables (or disables) the tracer
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
ze_result_t ZE_APICALL
zetTracerExpSetEnabled(
    zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
    ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnTracerExpSetEnabled_t pfnSetEnabled = [&result] {
        auto pfnSetEnabled = ze_lib::context->zetDdiTable.load()->TracerExp.pfnSetEnabled;
        if( nullptr == pfnSetEnabled ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnSetEnabled;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnSetEnabled( hTracer, enable );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEnabled = ze_lib::context->zetDdiTable.load()->TracerExp.pfnSetEnabled;
    if( nullptr == pfnSetEnabled ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEnabled( hTracer, enable );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get sets of metric groups which could be collected concurrently.
/// 
/// @details
///     - Re-arrange the input metric groups to provide sets of concurrent
///       metric groups.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == phMetricGroups`
ze_result_t ZE_APICALL
zetDeviceGetConcurrentMetricGroupsExp(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t metricGroupCount,                      ///< [in] metric group count
    zet_metric_group_handle_t * phMetricGroups,     ///< [in,out] metrics groups to be re-arranged to be sets of concurrent
                                                    ///< groups
    uint32_t * pMetricGroupsCountPerConcurrentGroup,///< [in,out][optional][*pConcurrentGroupCount] count of metric groups per
                                                    ///< concurrent group.
    uint32_t * pConcurrentGroupCount                ///< [out] number of concurrent groups.
                                                    ///< The value of this parameter could be used to determine the number of
                                                    ///< replays necessary.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDeviceGetConcurrentMetricGroupsExp_t pfnGetConcurrentMetricGroupsExp = [&result] {
        auto pfnGetConcurrentMetricGroupsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnGetConcurrentMetricGroupsExp;
        if( nullptr == pfnGetConcurrentMetricGroupsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetConcurrentMetricGroupsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetConcurrentMetricGroupsExp( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConcurrentMetricGroupsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnGetConcurrentMetricGroupsExp;
    if( nullptr == pfnGetConcurrentMetricGroupsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConcurrentMetricGroupsExp( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create a metric tracer for a device.
/// 
/// @details
///     - The notification event must have been created from an event pool that
///       was created using ::ZE_EVENT_POOL_FLAG_HOST_VISIBLE flag.
///     - The duration of the signal event created from an event pool that was
///       created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag is undefined.
///       However, for consistency and orthogonality the event will report
///       correctly as signaled when used by other event API functionality.
///     - The application must **not** call this function from simultaneous
///       threads with the same device handle.
///     - The metric tracer is created in disabled state
///     - Metric groups must support sampling type
///       ZET_METRIC_SAMPLING_TYPE_EXP_FLAG_TRACER_BASED
///     - All metric groups must be first activated
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phMetricGroups`
///         + `nullptr == desc`
///         + `nullptr == phMetricTracer`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
ze_result_t ZE_APICALL
zetMetricTracerCreateExp(
    zet_context_handle_t hContext,                  ///< [in] handle of the context object
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t metricGroupCount,                      ///< [in] metric group count
    zet_metric_group_handle_t* phMetricGroups,      ///< [in][range(0, metricGroupCount )] handles of the metric groups to
                                                    ///< trace
    zet_metric_tracer_exp_desc_t* desc,             ///< [in,out] metric tracer descriptor
    ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Note:
                                                    ///< If buffer is not drained when the event it flagged, there is a risk of
                                                    ///< HW event buffer being overrun
    zet_metric_tracer_exp_handle_t* phMetricTracer  ///< [out] handle of the metric tracer
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricTracerCreateExp_t pfnCreateExp = [&result] {
        auto pfnCreateExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnCreateExp;
        if( nullptr == pfnCreateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExp( hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnCreateExp;
    if( nullptr == pfnCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExp( hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroy a metric tracer.
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same metric tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
ze_result_t ZE_APICALL
zetMetricTracerDestroyExp(
    zet_metric_tracer_exp_handle_t hMetricTracer    ///< [in] handle of the metric tracer
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricTracerDestroyExp_t pfnDestroyExp = [&result] {
        auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExp( hMetricTracer );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( hMetricTracer );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Start events collection
/// 
/// @details
///     - Driver implementations must make this API call have as minimal
///       overhead as possible, to allow applications start/stop event
///       collection at any point during execution
///     - The application must **not** call this function from simultaneous
///       threads with the same metric tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
ze_result_t ZE_APICALL
zetMetricTracerEnableExp(
    zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
    ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                    ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                    ///< and checking the return status: ::ZE_RESULT_NOT_READY will be returned
                                                    ///< when the tracer is inactive. ::ZE_RESULT_SUCCESS will be returned 
                                                    ///< when the tracer is active.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricTracerEnableExp_t pfnEnableExp = [&result] {
        auto pfnEnableExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnEnableExp;
        if( nullptr == pfnEnableExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnableExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnableExp( hMetricTracer, synchronous );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnableExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnEnableExp;
    if( nullptr == pfnEnableExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnableExp( hMetricTracer, synchronous );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Stop events collection
/// 
/// @details
///     - Driver implementations must make this API call have as minimal
///       overhead as possible, to allow applications start/stop event
///       collection at any point during execution
///     - The application must **not** call this function from simultaneous
///       threads with the same metric tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
ze_result_t ZE_APICALL
zetMetricTracerDisableExp(
    zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
    ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                    ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                    ///< and checking the return status: ::ZE_RESULT_SUCCESS will be returned
                                                    ///< when the tracer is active or when it is inactive but still has data. 
                                                    ///< ::ZE_RESULT_NOT_READY will be returned when the tracer is inactive and
                                                    ///< has no more data to be retrieved.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricTracerDisableExp_t pfnDisableExp = [&result] {
        auto pfnDisableExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnDisableExp;
        if( nullptr == pfnDisableExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDisableExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDisableExp( hMetricTracer, synchronous );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDisableExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnDisableExp;
    if( nullptr == pfnDisableExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDisableExp( hMetricTracer, synchronous );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read data from the metric tracer
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same metric tracer handle.
///     - Data can be retrieved after tracer is disabled. When buffers are
///       drained ::ZE_RESULT_NOT_READY will be returned
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
///     - ::ZE_RESULT_WARNING_DROPPED_DATA
///         + Metric tracer data may have been dropped.
///     - ::ZE_RESULT_NOT_READY
///         + Metric tracer is disabled and no data is available to read.
ze_result_t ZE_APICALL
zetMetricTracerReadDataExp(
    zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
    size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                    ///< if size is zero, then the driver will update the value with the total
                                                    ///< size in bytes needed for all data available.
                                                    ///< if size is non-zero, then driver will only retrieve that amount of
                                                    ///< data. 
                                                    ///< if size is larger than size needed for all data, then driver will
                                                    ///< update the value with the actual size needed.
    uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                    ///< data in raw format
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricTracerReadDataExp_t pfnReadDataExp = [&result] {
        auto pfnReadDataExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnReadDataExp;
        if( nullptr == pfnReadDataExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnReadDataExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnReadDataExp( hMetricTracer, pRawDataSize, pRawData );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadDataExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnReadDataExp;
    if( nullptr == pfnReadDataExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadDataExp( hMetricTracer, pRawDataSize, pRawData );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create a metric decoder for a given metric tracer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phMetricDecoder`
ze_result_t ZE_APICALL
zetMetricDecoderCreateExp(
    zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
    zet_metric_decoder_exp_handle_t* phMetricDecoder///< [out] handle of the metric decoder object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricDecoderCreateExp_t pfnCreateExp = [&result] {
        auto pfnCreateExp = ze_lib::context->zetDdiTable.load()->MetricDecoderExp.pfnCreateExp;
        if( nullptr == pfnCreateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExp( hMetricTracer, phMetricDecoder );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExp = ze_lib::context->zetDdiTable.load()->MetricDecoderExp.pfnCreateExp;
    if( nullptr == pfnCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExp( hMetricTracer, phMetricDecoder );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroy a metric decoder.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == phMetricDecoder`
ze_result_t ZE_APICALL
zetMetricDecoderDestroyExp(
    zet_metric_decoder_exp_handle_t phMetricDecoder ///< [in] handle of the metric decoder object
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricDecoderDestroyExp_t pfnDestroyExp = [&result] {
        auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricDecoderExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExp( phMetricDecoder );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricDecoderExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( phMetricDecoder );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Return the list of the decodable metrics from the decoder.
/// 
/// @details
///     - The decodable metrics handles returned by this API are defined by the
///       metric groups in the tracer on which the decoder was created.
///     - The decodable metrics handles returned by this API are only valid to
///       decode metrics raw data with ::zetMetricTracerDecodeExp(). Decodable
///       metric handles are not valid to compare with metrics handles included
///       in metric groups.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricDecoder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///         + `nullptr == phMetrics`
ze_result_t ZE_APICALL
zetMetricDecoderGetDecodableMetricsExp(
    zet_metric_decoder_exp_handle_t hMetricDecoder, ///< [in] handle of the metric decoder object
    uint32_t* pCount,                               ///< [in,out] pointer to number of decodable metric in the hMetricDecoder
                                                    ///< handle. If count is zero, then the driver shall 
                                                    ///< update the value with the total number of decodable metrics available
                                                    ///< in the decoder. if count is greater than zero 
                                                    ///< but less than the total number of decodable metrics available in the
                                                    ///< decoder, then only that number will be returned. 
                                                    ///< if count is greater than the number of decodable metrics available in
                                                    ///< the decoder, then the driver shall update the 
                                                    ///< value with the actual number of decodable metrics available. 
    zet_metric_handle_t* phMetrics                  ///< [in,out] [range(0, *pCount)] array of handles of decodable metrics in
                                                    ///< the hMetricDecoder handle provided.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricDecoderGetDecodableMetricsExp_t pfnGetDecodableMetricsExp = [&result] {
        auto pfnGetDecodableMetricsExp = ze_lib::context->zetDdiTable.load()->MetricDecoderExp.pfnGetDecodableMetricsExp;
        if( nullptr == pfnGetDecodableMetricsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetDecodableMetricsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetDecodableMetricsExp( hMetricDecoder, pCount, phMetrics );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDecodableMetricsExp = ze_lib::context->zetDdiTable.load()->MetricDecoderExp.pfnGetDecodableMetricsExp;
    if( nullptr == pfnGetDecodableMetricsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDecodableMetricsExp( hMetricDecoder, pCount, phMetrics );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Decode raw events collected from a tracer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == phMetricDecoder`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
///         + `nullptr == phMetrics`
///         + `nullptr == pSetCount`
///         + `nullptr == pMetricEntriesCount`
ze_result_t ZE_APICALL
zetMetricTracerDecodeExp(
    zet_metric_decoder_exp_handle_t phMetricDecoder,///< [in] handle of the metric decoder object
    size_t* pRawDataSize,                           ///< [in,out] size in bytes of raw data buffer. If pMetricEntriesCount is
                                                    ///< greater than zero but less than total number of 
                                                    ///< decodable metrics available in the raw data buffer, then driver shall
                                                    ///< update this value with actual number of raw 
                                                    ///< data bytes processed.
    uint8_t* pRawData,                              ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                    ///< data in raw format
    uint32_t metricsCount,                          ///< [in] number of decodable metrics in the tracer for which the
                                                    ///< hMetricDecoder handle was provided. See 
                                                    ///< ::zetMetricDecoderGetDecodableMetricsExp(). If metricCount is greater
                                                    ///< than zero but less than the number decodable 
                                                    ///< metrics available in the raw data buffer, then driver shall only
                                                    ///< decode those.
    zet_metric_handle_t* phMetrics,                 ///< [in] [range(0, metricsCount)] array of handles of decodable metrics in
                                                    ///< the decoder for which the hMetricDecoder handle was 
                                                    ///< provided. Metrics handles are expected to be for decodable metrics,
                                                    ///< see ::zetMetricDecoderGetDecodableMetricsExp() 
    uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets. If count is zero, then the
                                                    ///< driver shall update the value with the total
                                                    ///< number of metric sets to be decoded. If count is greater than the
                                                    ///< number available in the raw data buffer, then the
                                                    ///< driver shall update the value with the actual number of metric sets to
                                                    ///< be decoded. There is a 1:1 relation between
                                                    ///< the number of sets and sub-devices returned in the decoded entries.
    uint32_t* pMetricEntriesCountPerSet,            ///< [in,out][optional][range(0, *pSetCount)] buffer of metric entries
                                                    ///< counts per metric set, one value per set.
    uint32_t* pMetricEntriesCount,                  ///< [in,out]  pointer to the total number of metric entries decoded, for
                                                    ///< all metric sets. If count is zero, then the
                                                    ///< driver shall update the value with the total number of metric entries
                                                    ///< to be decoded. If count is greater than zero
                                                    ///< but less than the total number of metric entries available in the raw
                                                    ///< data, then user provided number will be decoded.
                                                    ///< If count is greater than the number available in the raw data buffer,
                                                    ///< then the driver shall update the value with
                                                    ///< the actual number of decodable metric entries decoded. If set to null,
                                                    ///< then driver will only update the value of
                                                    ///< pSetCount.
    zet_metric_entry_exp_t* pMetricEntries          ///< [in,out][optional][range(0, *pMetricEntriesCount)] buffer containing
                                                    ///< decoded metric entries
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricTracerDecodeExp_t pfnDecodeExp = [&result] {
        auto pfnDecodeExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnDecodeExp;
        if( nullptr == pfnDecodeExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDecodeExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDecodeExp( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDecodeExp = ze_lib::context->zetDdiTable.load()->MetricTracerExp.pfnDecodeExp;
    if( nullptr == pfnDecodeExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDecodeExp( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Append a Marker based on the Metric source of the Metric Group, to a
///        Command List.
/// 
/// @details
///     - This function appends a Marker based on the Metric source of the
///       Metric Group, to Command List.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricGroup`
ze_result_t ZE_APICALL
zetCommandListAppendMarkerExp(
    zet_command_list_handle_t hCommandList,         ///< [in] handle to the command list
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle to the marker metric group.
                                                    ///< ::zet_metric_group_type_exp_flags_t could be used to check whether
                                                    ///< marker is supoported by the metric group.
    uint32_t value                                  ///< [in] marker value
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnCommandListAppendMarkerExp_t pfnAppendMarkerExp = [&result] {
        auto pfnAppendMarkerExp = ze_lib::context->zetDdiTable.load()->CommandListExp.pfnAppendMarkerExp;
        if( nullptr == pfnAppendMarkerExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAppendMarkerExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAppendMarkerExp( hCommandList, hMetricGroup, value );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMarkerExp = ze_lib::context->zetDdiTable.load()->CommandListExp.pfnAppendMarkerExp;
    if( nullptr == pfnAppendMarkerExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMarkerExp( hCommandList, hMetricGroup, value );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enable Metrics collection during runtime.
/// 
/// @details
///     - This API enables metric collection for a device/sub-device if not
///       already enabled.
///     - if ZET_ENABLE_METRICS=1 was already set, then calling this api would
///       be a NOP.
///     - This api should be called after calling zeInit().
///     - If device is a root-device handle, then its sub-devices are also
///       enabled.
///     - ::zetDeviceDisableMetricsExp need not be called if if this api returns
///       error.
///     - This API can be used as runtime alternative to setting
///       ZET_ENABLE_METRICS=1.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
ze_result_t ZE_APICALL
zetDeviceEnableMetricsExp(
    zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be enabled.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDeviceEnableMetricsExp_t pfnEnableMetricsExp = [&result] {
        auto pfnEnableMetricsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnEnableMetricsExp;
        if( nullptr == pfnEnableMetricsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnEnableMetricsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnEnableMetricsExp( hDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnableMetricsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnEnableMetricsExp;
    if( nullptr == pfnEnableMetricsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnableMetricsExp( hDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Disable Metrics collection during runtime, if it was already enabled.
/// 
/// @details
///     - This API disables metrics collection for a device/sub-device, if it
///       was previously enabled.
///     - If device is a root-device handle, then its sub-devices are also
///       disabled.
///     - The application has to ensure that all metric operations are complete
///       and all metric resources are released before this API is called.
///     - If there are metric operations in progress or metric resources are not
///       released, then ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE is returned.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
ze_result_t ZE_APICALL
zetDeviceDisableMetricsExp(
    zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be disabled
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDeviceDisableMetricsExp_t pfnDisableMetricsExp = [&result] {
        auto pfnDisableMetricsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnDisableMetricsExp;
        if( nullptr == pfnDisableMetricsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDisableMetricsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDisableMetricsExp( hDevice );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDisableMetricsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnDisableMetricsExp;
    if( nullptr == pfnDisableMetricsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDisableMetricsExp( hDevice );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Calculate one or more sets of metric values from raw data.
/// 
/// @details
///     - This function is similar to ::zetMetricGroupCalculateMetricValues
///       except it may calculate more than one set of metric values from a
///       single data buffer.  There may be one set of metric values for each
///       sub-device, for example.
///     - Each set of metric values may consist of a different number of metric
///       values, returned as the metric value count.
///     - All metric values are calculated into a single buffer; use the metric
///       counts to determine which metric values belong to which set.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZET_METRIC_GROUP_CALCULATION_TYPE_MAX_METRIC_VALUES < type`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawData`
///         + `nullptr == pSetCount`
///         + `nullptr == pTotalMetricValueCount`
ze_result_t ZE_APICALL
zetMetricGroupCalculateMultipleMetricValuesExp(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
    size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
    const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
    uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metric sets to be calculated.
                                                    ///< if count is greater than the number available in the raw data buffer,
                                                    ///< then the driver shall update the value with the actual number of
                                                    ///< metric sets to be calculated.
    uint32_t* pTotalMetricValueCount,               ///< [in,out] pointer to number of the total number of metric values
                                                    ///< calculated, for all metric sets.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metric values to be calculated.
                                                    ///< if count is greater than the number available in the raw data buffer,
                                                    ///< then the driver shall update the value with the actual number of
                                                    ///< metric values to be calculated.
    uint32_t* pMetricCounts,                        ///< [in,out][optional][range(0, *pSetCount)] buffer of metric counts per
                                                    ///< metric set.
    zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pTotalMetricValueCount)] buffer of
                                                    ///< calculated metrics.
                                                    ///< if count is less than the number available in the raw data buffer,
                                                    ///< then driver shall only calculate that number of metric values.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupCalculateMultipleMetricValuesExp_t pfnCalculateMultipleMetricValuesExp = [&result] {
        auto pfnCalculateMultipleMetricValuesExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCalculateMultipleMetricValuesExp;
        if( nullptr == pfnCalculateMultipleMetricValuesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCalculateMultipleMetricValuesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCalculateMultipleMetricValuesExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCalculateMultipleMetricValuesExp;
    if( nullptr == pfnCalculateMultipleMetricValuesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns metric timestamps synchronized with global device timestamps,
///        optionally synchronized with host
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - By default, the global and metrics timestamps are synchronized to the
///       device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == globalTimestamp`
///         + `nullptr == metricTimestamp`
ze_result_t ZE_APICALL
zetMetricGroupGetGlobalTimestampsExp(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    ze_bool_t synchronizedWithHost,                 ///< [in] Returns the timestamps synchronized to the host or the device.
    uint64_t* globalTimestamp,                      ///< [out] Device timestamp.
    uint64_t* metricTimestamp                       ///< [out] Metric timestamp.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupGetGlobalTimestampsExp_t pfnGetGlobalTimestampsExp = [&result] {
        auto pfnGetGlobalTimestampsExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnGetGlobalTimestampsExp;
        if( nullptr == pfnGetGlobalTimestampsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetGlobalTimestampsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetGlobalTimestampsExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnGetGlobalTimestampsExp;
    if( nullptr == pfnGetGlobalTimestampsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Export Metrics Data for system independent calculation.
/// 
/// @details
///     - This function exports raw data and necessary information to perform
///       metrics calculation of collected data in a different system than where
///       data was collected, which may or may not have accelerators.
///     - Implementations can choose to describe the data arrangement of the
///       exported data, using any mechanism which allows users to read and
///       process them.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawData`
///         + `nullptr == pExportDataSize`
ze_result_t ZE_APICALL
zetMetricGroupGetExportDataExp(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    const uint8_t* pRawData,                        ///< [in] buffer of raw data
    size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
    size_t* pExportDataSize,                        ///< [in,out] size in bytes of export data buffer
                                                    ///< if size is zero, then the driver shall update the value with the
                                                    ///< number of bytes necessary to store the exported data.
                                                    ///< if size is greater than required, then the driver shall update the
                                                    ///< value with the actual number of bytes necessary to store the exported data.
    uint8_t * pExportData                           ///< [in,out][optional][range(0, *pExportDataSize)] buffer of exported data.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupGetExportDataExp_t pfnGetExportDataExp = [&result] {
        auto pfnGetExportDataExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnGetExportDataExp;
        if( nullptr == pfnGetExportDataExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetExportDataExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExportDataExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnGetExportDataExp;
    if( nullptr == pfnGetExportDataExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Calculate one or more sets of metric values from exported raw data.
/// 
/// @details
///     - Calculate metrics values using exported data returned by
///       ::zetMetricGroupGetExportDataExp.
///     - This function is similar to
///       ::zetMetricGroupCalculateMultipleMetricValuesExp except it would
///       calculate from exported metric data.
///     - This function could be used to calculate metrics on a system different
///       from where the metric raw data was collected.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZET_METRIC_GROUP_CALCULATION_TYPE_MAX_METRIC_VALUES < type`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pExportData`
///         + `nullptr == pCalculateDescriptor`
///         + `nullptr == pSetCount`
///         + `nullptr == pTotalMetricValueCount`
ze_result_t ZE_APICALL
zetMetricGroupCalculateMetricExportDataExp(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
    size_t exportDataSize,                          ///< [in] size in bytes of exported data buffer
    const uint8_t* pExportData,                     ///< [in][range(0, exportDataSize)] buffer of exported data to calculate
    zet_metric_calculate_exp_desc_t* pCalculateDescriptor,  ///< [in] descriptor specifying calculation specific parameters
    uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metric sets to be calculated.
                                                    ///< if count is greater than the number available in the raw data buffer,
                                                    ///< then the driver shall update the value with the actual number of
                                                    ///< metric sets to be calculated.
    uint32_t* pTotalMetricValueCount,               ///< [in,out] pointer to number of the total number of metric values
                                                    ///< calculated, for all metric sets.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metric values to be calculated.
                                                    ///< if count is greater than the number available in the raw data buffer,
                                                    ///< then the driver shall update the value with the actual number of
                                                    ///< metric values to be calculated.
    uint32_t* pMetricCounts,                        ///< [in,out][optional][range(0, *pSetCount)] buffer of metric counts per
                                                    ///< metric set.
    zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pTotalMetricValueCount)] buffer of
                                                    ///< calculated metrics.
                                                    ///< if count is less than the number available in the raw data buffer,
                                                    ///< then driver shall only calculate that number of metric values.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupCalculateMetricExportDataExp_t pfnCalculateMetricExportDataExp = [&result] {
        auto pfnCalculateMetricExportDataExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCalculateMetricExportDataExp;
        if( nullptr == pfnCalculateMetricExportDataExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCalculateMetricExportDataExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCalculateMetricExportDataExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCalculateMetricExportDataExp;
    if( nullptr == pfnCalculateMetricExportDataExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Query and get the available metric programmable handles.
/// 
/// @details
///     - Query the available programmable handles using *pCount = 0.
///     - Returns all programmable metric handles available in the device.
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zetMetricProgrammableGetExp(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metric programmable handles.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of metric programmable handles available.
                                                    ///< if count is greater than the number of metric programmable handles
                                                    ///< available, then the driver shall update the value with the correct
                                                    ///< number of metric programmable handles available.
    zet_metric_programmable_exp_handle_t* phMetricProgrammables ///< [in,out][optional][range(0, *pCount)] array of handle of metric programmables.
                                                    ///< if count is less than the number of metric programmables available,
                                                    ///< then driver shall only retrieve that number of metric programmables.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricProgrammableGetExp_t pfnGetExp = [&result] {
        auto pfnGetExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetExp;
        if( nullptr == pfnGetExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetExp( hDevice, pCount, phMetricProgrammables );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetExp;
    if( nullptr == pfnGetExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExp( hDevice, pCount, phMetricProgrammables );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the properties of the metric programmable.
/// 
/// @details
///     - Returns the properties of the metric programmable.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricProgrammable`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zetMetricProgrammableGetPropertiesExp(
    zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
    zet_metric_programmable_exp_properties_t* pProperties   ///< [in,out] properties of the metric programmable
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricProgrammableGetPropertiesExp_t pfnGetPropertiesExp = [&result] {
        auto pfnGetPropertiesExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetPropertiesExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetPropertiesExp( hMetricProgrammable, pProperties );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetPropertiesExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetPropertiesExp;
    if( nullptr == pfnGetPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetPropertiesExp( hMetricProgrammable, pProperties );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the information about the parameters of the metric programmable.
/// 
/// @details
///     - Returns information about the parameters of the metric programmable
///       handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricProgrammable`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pParameterCount`
///         + `nullptr == pParameterInfo`
ze_result_t ZE_APICALL
zetMetricProgrammableGetParamInfoExp(
    zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
    uint32_t* pParameterCount,                      ///< [in,out] count of the parameters to retrieve parameter info.
                                                    ///< if value pParameterCount is greater than count of parameters
                                                    ///< available, then pParameterCount will be updated with count of
                                                    ///< parameters available.
                                                    ///< The count of parameters available can be queried using ::zetMetricProgrammableGetPropertiesExp.
    zet_metric_programmable_param_info_exp_t* pParameterInfo///< [in,out][range(1, *pParameterCount)] array of parameter info.
                                                    ///< if parameterCount is less than the number of parameters available,
                                                    ///< then driver shall only retrieve that number of parameter info.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricProgrammableGetParamInfoExp_t pfnGetParamInfoExp = [&result] {
        auto pfnGetParamInfoExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetParamInfoExp;
        if( nullptr == pfnGetParamInfoExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetParamInfoExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetParamInfoExp( hMetricProgrammable, pParameterCount, pParameterInfo );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetParamInfoExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetParamInfoExp;
    if( nullptr == pfnGetParamInfoExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetParamInfoExp( hMetricProgrammable, pParameterCount, pParameterInfo );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the information about the parameter value of the metric
///        programmable.
/// 
/// @details
///     - Returns the value-information about the parameter at the specific
///       ordinal of the metric programmable handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricProgrammable`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pValueInfoCount`
///         + `nullptr == pValueInfo`
ze_result_t ZE_APICALL
zetMetricProgrammableGetParamValueInfoExp(
    zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
    uint32_t parameterOrdinal,                      ///< [in] ordinal of the parameter in the metric programmable
    uint32_t* pValueInfoCount,                      ///< [in,out] count of parameter value information to retrieve.
                                                    ///< if value at pValueInfoCount is greater than count of value info
                                                    ///< available, then pValueInfoCount will be updated with count of value
                                                    ///< info available.
                                                    ///< The count of parameter value info available can be queried using ::zetMetricProgrammableGetParamInfoExp.
    zet_metric_programmable_param_value_info_exp_t* pValueInfo  ///< [in,out][range(1, *pValueInfoCount)] array of parameter value info.
                                                    ///< if pValueInfoCount is less than the number of value info available,
                                                    ///< then driver shall only retrieve that number of value info.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricProgrammableGetParamValueInfoExp_t pfnGetParamValueInfoExp = [&result] {
        auto pfnGetParamValueInfoExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetParamValueInfoExp;
        if( nullptr == pfnGetParamValueInfoExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnGetParamValueInfoExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnGetParamValueInfoExp( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetParamValueInfoExp = ze_lib::context->zetDdiTable.load()->MetricProgrammableExp.pfnGetParamValueInfoExp;
    if( nullptr == pfnGetParamValueInfoExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetParamValueInfoExp( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create metric handles by applying parameter values on the metric
///        programmable handle.
/// 
/// @details
///     - Multiple parameter values could be used to prepare a metric.
///     - If parameterCount = 0, the default value of the metric programmable
///       would be used for all parameters.
///     - The implementation can post-fix a C string to the metric name and
///       description, based on the parameter values chosen.
///     - ::zetMetricProgrammableGetParamInfoExp() returns a list of parameters
///       in a defined order.
///     - Therefore, the list of values passed in to the API should respect the
///       same order such that the desired parameter is set with expected value
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricProgrammable`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pParameterValues`
///         + `nullptr == pName`
///         + `nullptr == pDescription`
///         + `nullptr == pMetricHandleCount`
ze_result_t ZE_APICALL
zetMetricCreateFromProgrammableExp2(
    zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
    uint32_t parameterCount,                        ///< [in] Count of parameters to set.
    zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
    const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                    ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
    const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                    ///< null-terminated character array no longer than
                                                    ///< ::ZET_MAX_METRIC_DESCRIPTION.
    uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< number of metric handles available for this programmable.
                                                    ///< if count is greater than the number of metric handles available, then
                                                    ///< the driver shall update the value with the correct number of metric
                                                    ///< handles available.
    zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                    ///< if count is less than the number of metrics available, then driver
                                                    ///< shall only retrieve that number of metric handles.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricCreateFromProgrammableExp2_t pfnCreateFromProgrammableExp2 = [&result] {
        auto pfnCreateFromProgrammableExp2 = ze_lib::context->zetDdiTable.load()->MetricExp.pfnCreateFromProgrammableExp2;
        if( nullptr == pfnCreateFromProgrammableExp2 ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateFromProgrammableExp2;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateFromProgrammableExp2( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateFromProgrammableExp2 = ze_lib::context->zetDdiTable.load()->MetricExp.pfnCreateFromProgrammableExp2;
    if( nullptr == pfnCreateFromProgrammableExp2 ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateFromProgrammableExp2( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create metric handles by applying parameter values on the metric
///        programmable handle.
/// 
/// @details
///     - This API is deprecated. Please use
///       ::zetMetricCreateFromProgrammableExp2()
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricProgrammable`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pParameterValues`
///         + `nullptr == pName`
///         + `nullptr == pDescription`
///         + `nullptr == pMetricHandleCount`
ze_result_t ZE_APICALL
zetMetricCreateFromProgrammableExp(
    zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
    zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
    uint32_t parameterCount,                        ///< [in] Count of parameters to set.
    const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                    ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
    const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                    ///< null-terminated character array no longer than
                                                    ///< ::ZET_MAX_METRIC_DESCRIPTION.
    uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< number of metric handles available for this programmable.
                                                    ///< if count is greater than the number of metric handles available, then
                                                    ///< the driver shall update the value with the correct number of metric
                                                    ///< handles available.
    zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                    ///< if count is less than the number of metrics available, then driver
                                                    ///< shall only retrieve that number of metric handles.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricCreateFromProgrammableExp_t pfnCreateFromProgrammableExp = [&result] {
        auto pfnCreateFromProgrammableExp = ze_lib::context->zetDdiTable.load()->MetricExp.pfnCreateFromProgrammableExp;
        if( nullptr == pfnCreateFromProgrammableExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateFromProgrammableExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateFromProgrammableExp( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateFromProgrammableExp = ze_lib::context->zetDdiTable.load()->MetricExp.pfnCreateFromProgrammableExp;
    if( nullptr == pfnCreateFromProgrammableExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateFromProgrammableExp( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create multiple metric group handles from metric handles.
/// 
/// @details
///     - Creates multiple metric groups from metrics which were created using
///       ::zetMetricCreateFromProgrammableExp2().
///     - Metrics whose Hardware resources do not overlap are added to same
///       metric group.
///     - The metric groups created using this API are managed by the
///       application and cannot be retrieved using ::zetMetricGroupGet().
///     - The created metric groups are ready for activation and collection.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == phMetrics`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + metricGroupCount is lesser than the number of metric group handles that could be created.
ze_result_t ZE_APICALL
zetDeviceCreateMetricGroupsFromMetricsExp(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device.
    uint32_t metricCount,                           ///< [in] number of metric handles.
    zet_metric_handle_t * phMetrics,                ///< [in] metric handles to be added to the metric groups.
    const char * pMetricGroupNamePrefix,            ///< [in] prefix to the name created for the metric groups. Must point to a
                                                    ///< null-terminated character array no longer than
                                                    ///< ::ZET_MAX_METRIC_GROUP_NAME_PREFIX_EXP.
    const char * pDescription,                      ///< [in] pointer to description of the metric groups. Must point to a
                                                    ///< null-terminated character array no longer than
                                                    ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
    uint32_t * pMetricGroupCount,                   ///< [in,out] pointer to the number of metric group handles to be created.
                                                    ///< if pMetricGroupCount is zero, then the driver shall update the value
                                                    ///< with the maximum possible number of metric group handles that could be created.
                                                    ///< if pMetricGroupCount is greater than the number of metric group
                                                    ///< handles that could be created, then the driver shall update the value
                                                    ///< with the correct number of metric group handles generated.
                                                    ///< if pMetricGroupCount is lesser than the number of metric group handles
                                                    ///< that could be created, then ::ZE_RESULT_ERROR_INVALID_ARGUMENT is returned.
    zet_metric_group_handle_t* phMetricGroup        ///< [in,out][optional][range(0, *pMetricGroupCount)] array of handle of
                                                    ///< metric group handles.
                                                    ///< Created Metric group handles.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnDeviceCreateMetricGroupsFromMetricsExp_t pfnCreateMetricGroupsFromMetricsExp = [&result] {
        auto pfnCreateMetricGroupsFromMetricsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnCreateMetricGroupsFromMetricsExp;
        if( nullptr == pfnCreateMetricGroupsFromMetricsExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateMetricGroupsFromMetricsExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateMetricGroupsFromMetricsExp( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateMetricGroupsFromMetricsExp = ze_lib::context->zetDdiTable.load()->DeviceExp.pfnCreateMetricGroupsFromMetricsExp;
    if( nullptr == pfnCreateMetricGroupsFromMetricsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateMetricGroupsFromMetricsExp( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Create metric group handle.
/// 
/// @details
///     - This API is deprecated. Please use
///       ::zetDeviceCreateMetricGroupsFromMetricsExp 
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pName`
///         + `nullptr == pDescription`
///         + `nullptr == phMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x7 < samplingType`
ze_result_t ZE_APICALL
zetMetricGroupCreateExp(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    const char* pName,                              ///< [in] pointer to metric group name. Must point to a null-terminated
                                                    ///< character array no longer than ::ZET_MAX_METRIC_GROUP_NAME.
    const char* pDescription,                       ///< [in] pointer to metric group description. Must point to a
                                                    ///< null-terminated character array no longer than
                                                    ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
    zet_metric_group_sampling_type_flags_t samplingType,///< [in] Sampling type for the metric group.
    zet_metric_group_handle_t* phMetricGroup        ///< [in,out] Created Metric group handle
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupCreateExp_t pfnCreateExp = [&result] {
        auto pfnCreateExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCreateExp;
        if( nullptr == pfnCreateExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCreateExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCreateExp( hDevice, pName, pDescription, samplingType, phMetricGroup );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreateExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCreateExp;
    if( nullptr == pfnCreateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreateExp( hDevice, pName, pDescription, samplingType, phMetricGroup );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Add a metric handle to the metric group handle created using
///        ::zetDeviceCreateMetricGroupsFromMetricsExp.
/// 
/// @details
///     - Reasons for failing to add the metric could be queried using
///       pErrorString
///     - Multiple additions of same metric would add the metric only once to
///       the hMetricGroup
///     - Metric handles from multiple domains may be used in a single metric
///       group.
///     - Metric handles from different sourceIds (refer
///       ::zet_metric_programmable_exp_properties_t) are not allowed in a
///       single metric group.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///         + `nullptr == hMetric`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + If a Metric handle from a pre-defined metric group is requested to be added.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + If the metric group is currently activated.
ze_result_t ZE_APICALL
zetMetricGroupAddMetricExp(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
    zet_metric_handle_t hMetric,                    ///< [in] Metric to be added to the group.
    size_t * pErrorStringSize,                      ///< [in,out][optional] Size of the error string to query, if an error was
                                                    ///< reported during adding the metric handle.
                                                    ///< if *pErrorStringSize is zero, then the driver shall update the value
                                                    ///< with the size of the error string in bytes.
    char* pErrorString                              ///< [in,out][optional][range(0, *pErrorStringSize)] Error string.
                                                    ///< if *pErrorStringSize is less than the length of the error string
                                                    ///< available, then driver shall only retrieve that length of error string.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupAddMetricExp_t pfnAddMetricExp = [&result] {
        auto pfnAddMetricExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnAddMetricExp;
        if( nullptr == pfnAddMetricExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnAddMetricExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnAddMetricExp( hMetricGroup, hMetric, pErrorStringSize, pErrorString );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAddMetricExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnAddMetricExp;
    if( nullptr == pfnAddMetricExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAddMetricExp( hMetricGroup, hMetric, pErrorStringSize, pErrorString );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Remove a metric from the metric group handle created using
///        ::zetDeviceCreateMetricGroupsFromMetricsExp.
/// 
/// @details
///     - Remove an already added metric handle from the metric group.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///         + `nullptr == hMetric`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + If trying to remove a metric not previously added to the metric group
///         + If the input metric group is a pre-defined metric group
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + If the metric group is currently activated
ze_result_t ZE_APICALL
zetMetricGroupRemoveMetricExp(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
    zet_metric_handle_t hMetric                     ///< [in] Metric handle to be removed from the metric group.
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupRemoveMetricExp_t pfnRemoveMetricExp = [&result] {
        auto pfnRemoveMetricExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnRemoveMetricExp;
        if( nullptr == pfnRemoveMetricExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnRemoveMetricExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnRemoveMetricExp( hMetricGroup, hMetric );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnRemoveMetricExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnRemoveMetricExp;
    if( nullptr == pfnRemoveMetricExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnRemoveMetricExp( hMetricGroup, hMetric );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes a created metric group using
///        ::zetDeviceCreateMetricGroupsFromMetricsExp, so that it can be
///        activated.
/// 
/// @details
///     - Finalizes the ::zetMetricGroupAddMetricExp and
///       ::zetMetricGroupRemoveMetricExp operations on the metric group.
///     - This is a necessary step before activation of the created metric
///       group.
///     - Add / Remove of metrics is possible after ::zetMetricGroupCloseExp.
///       However, a call to ::zetMetricGroupCloseExp is necessary after
///       modifying the metric group.
///     - Implementations could choose to add new metrics to the group during
///       ::zetMetricGroupCloseExp, which are related and might add value to the
///       metrics already added by the application
///     - Applications can query the list of metrics in the metric group using
///       ::zetMetricGet
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + If the input metric group is a pre-defined metric group
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + If the metric group is currently activated
ze_result_t ZE_APICALL
zetMetricGroupCloseExp(
    zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupCloseExp_t pfnCloseExp = [&result] {
        auto pfnCloseExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCloseExp;
        if( nullptr == pfnCloseExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnCloseExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnCloseExp( hMetricGroup );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCloseExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnCloseExp;
    if( nullptr == pfnCloseExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCloseExp( hMetricGroup );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroy a metric group created using
///        ::zetDeviceCreateMetricGroupsFromMetricsExp.
/// 
/// @details
///     - Metric handles created using ::zetMetricCreateFromProgrammableExp2 and
///       are part of the metricGroup are not destroyed.
///     - It is necessary to call ::zetMetricDestroyExp for each of the metric
///       handles (created from ::zetMetricCreateFromProgrammableExp2) to
///       destroy them.
///     - It is not necessary to remove the metrics in the metricGroup before
///       destroying it.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + If trying to destroy a pre-defined metric group
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + If trying to destroy an activated metric group
ze_result_t ZE_APICALL
zetMetricGroupDestroyExp(
    zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricGroupDestroyExp_t pfnDestroyExp = [&result] {
        auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExp( hMetricGroup );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricGroupExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( hMetricGroup );
    #endif
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroy a metric created using ::zetMetricCreateFromProgrammableExp2.
/// 
/// @details
///     - If a metric is added to a metric group, the metric has to be removed
///       using ::zetMetricGroupRemoveMetricExp before it can be destroyed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetric`
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + If trying to destroy a metric from pre-defined metric group
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + If trying to destroy a metric currently added to a metric group
ze_result_t ZE_APICALL
zetMetricDestroyExp(
    zet_metric_handle_t hMetric                     ///< [in] Handle of the metric to destroy
    )
{
    #ifdef L0_STATIC_LOADER_BUILD
    ze_result_t result = ZE_RESULT_SUCCESS;
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    static const zet_pfnMetricDestroyExp_t pfnDestroyExp = [&result] {
        auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp ) {
            result = ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return pfnDestroyExp;
    }();
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }
    return pfnDestroyExp( hMetric );
    #else
    if(ze_lib::destruction) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroyExp = ze_lib::context->zetDdiTable.load()->MetricExp.pfnDestroyExp;
    if( nullptr == pfnDestroyExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroyExp( hMetric );
    #endif
}

} // extern "C"
