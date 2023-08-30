/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDebugInfo = ze_lib::context->zetDdiTable.Module.pfnGetDebugInfo;
    if( nullptr == pfnGetDebugInfo ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDebugProperties = ze_lib::context->zetDdiTable.Device.pfnGetDebugProperties;
    if( nullptr == pfnGetDebugProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDebugProperties( hDevice, pDebugProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAttach = ze_lib::context->zetDdiTable.Debug.pfnAttach;
    if( nullptr == pfnAttach ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAttach( hDevice, config, phDebug );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDetach = ze_lib::context->zetDdiTable.Debug.pfnDetach;
    if( nullptr == pfnDetach ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDetach( hDebug );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadEvent = ze_lib::context->zetDdiTable.Debug.pfnReadEvent;
    if( nullptr == pfnReadEvent ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadEvent( hDebug, timeout, event );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAcknowledgeEvent = ze_lib::context->zetDdiTable.Debug.pfnAcknowledgeEvent;
    if( nullptr == pfnAcknowledgeEvent ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAcknowledgeEvent( hDebug, event );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInterrupt = ze_lib::context->zetDdiTable.Debug.pfnInterrupt;
    if( nullptr == pfnInterrupt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnInterrupt( hDebug, thread );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnResume = ze_lib::context->zetDdiTable.Debug.pfnResume;
    if( nullptr == pfnResume ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnResume( hDebug, thread );
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
///         + `::ZET_DEBUG_MEMORY_SPACE_TYPE_SLM < desc->type`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadMemory = ze_lib::context->zetDdiTable.Debug.pfnReadMemory;
    if( nullptr == pfnReadMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadMemory( hDebug, thread, desc, size, buffer );
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
///         + `::ZET_DEBUG_MEMORY_SPACE_TYPE_SLM < desc->type`
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnWriteMemory = ze_lib::context->zetDdiTable.Debug.pfnWriteMemory;
    if( nullptr == pfnWriteMemory ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnWriteMemory( hDebug, thread, desc, size, buffer );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRegisterSetProperties = ze_lib::context->zetDdiTable.Debug.pfnGetRegisterSetProperties;
    if( nullptr == pfnGetRegisterSetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetThreadRegisterSetProperties = ze_lib::context->zetDdiTable.Debug.pfnGetThreadRegisterSetProperties;
    if( nullptr == pfnGetThreadRegisterSetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );
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
                                                    ///< equal to the `count` member of ::zet_debug_register_group_properties_t
                                                    ///< for the type
    void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadRegisters = ze_lib::context->zetDdiTable.Debug.pfnReadRegisters;
    if( nullptr == pfnReadRegisters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
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
                                                    ///< or equal to the `count` member of
                                                    ///< ::zet_debug_register_group_properties_t for the type
    void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnWriteRegisters = ze_lib::context->zetDdiTable.Debug.pfnWriteRegisters;
    if( nullptr == pfnWriteRegisters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zetDdiTable.MetricGroup.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( hDevice, pCount, phMetricGroups );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zetDdiTable.MetricGroup.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hMetricGroup, pProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCalculateMetricValues = ze_lib::context->zetDdiTable.MetricGroup.pfnCalculateMetricValues;
    if( nullptr == pfnCalculateMetricValues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zetDdiTable.Metric.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( hMetricGroup, pCount, phMetrics );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zetDdiTable.Metric.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hMetric, pProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnActivateMetricGroups = ze_lib::context->zetDdiTable.Context.pfnActivateMetricGroups;
    if( nullptr == pfnActivateMetricGroups ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnActivateMetricGroups( hContext, hDevice, count, phMetricGroups );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOpen = ze_lib::context->zetDdiTable.MetricStreamer.pfnOpen;
    if( nullptr == pfnOpen ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricStreamerMarker = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricStreamerMarker;
    if( nullptr == pfnAppendMetricStreamerMarker ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnClose = ze_lib::context->zetDdiTable.MetricStreamer.pfnClose;
    if( nullptr == pfnClose ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnClose( hMetricStreamer );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadData = ze_lib::context->zetDdiTable.MetricStreamer.pfnReadData;
    if( nullptr == pfnReadData ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zetDdiTable.MetricQueryPool.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zetDdiTable.MetricQueryPool.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hMetricQueryPool );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zetDdiTable.MetricQuery.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hMetricQueryPool, index, phMetricQuery );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zetDdiTable.MetricQuery.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hMetricQuery );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zetDdiTable.MetricQuery.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hMetricQuery );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricQueryBegin = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricQueryBegin;
    if( nullptr == pfnAppendMetricQueryBegin ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricQueryEnd = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricQueryEnd;
    if( nullptr == pfnAppendMetricQueryEnd ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnAppendMetricMemoryBarrier = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;
    if( nullptr == pfnAppendMetricMemoryBarrier ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnAppendMetricMemoryBarrier( hCommandList );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetData = ze_lib::context->zetDdiTable.MetricQuery.pfnGetData;
    if( nullptr == pfnGetData ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProfileInfo = ze_lib::context->zetDdiTable.Kernel.pfnGetProfileInfo;
    if( nullptr == pfnGetProfileInfo ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProfileInfo( hKernel, pProfileProperties );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCreate = ze_lib::context->zetDdiTable.TracerExp.pfnCreate;
    if( nullptr == pfnCreate ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCreate( hContext, desc, phTracer );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnDestroy = ze_lib::context->zetDdiTable.TracerExp.pfnDestroy;
    if( nullptr == pfnDestroy ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnDestroy( hTracer );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetPrologues = ze_lib::context->zetDdiTable.TracerExp.pfnSetPrologues;
    if( nullptr == pfnSetPrologues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetPrologues( hTracer, pCoreCbs );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEpilogues = ze_lib::context->zetDdiTable.TracerExp.pfnSetEpilogues;
    if( nullptr == pfnSetEpilogues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEpilogues( hTracer, pCoreCbs );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEnabled = ze_lib::context->zetDdiTable.TracerExp.pfnSetEnabled;
    if( nullptr == pfnSetEnabled ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEnabled( hTracer, enable );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCalculateMultipleMetricValuesExp = ze_lib::context->zetDdiTable.MetricGroupExp.pfnCalculateMultipleMetricValuesExp;
    if( nullptr == pfnCalculateMultipleMetricValuesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetGlobalTimestampsExp = ze_lib::context->zetDdiTable.MetricGroupExp.pfnGetGlobalTimestampsExp;
    if( nullptr == pfnGetGlobalTimestampsExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExportDataExp = ze_lib::context->zetDdiTable.MetricGroupExp.pfnGetExportDataExp;
    if( nullptr == pfnGetExportDataExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
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
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnCalculateMetricExportDataExp = ze_lib::context->zetDdiTable.MetricGroupExp.pfnCalculateMetricExportDataExp;
    if( nullptr == pfnCalculateMetricExportDataExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
}

} // extern "C"
