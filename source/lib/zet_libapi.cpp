/*
 *
 * Copyright (C) 2019 Intel Corporation
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
    auto pfnGetDebugInfo = ze_lib::context->zetDdiTable.Module.pfnGetDebugInfo;
    if( nullptr == pfnGetDebugInfo )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves debug properties of the device.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
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
    auto pfnGetDebugProperties = ze_lib::context->zetDdiTable.Device.pfnGetDebugProperties;
    if( nullptr == pfnGetDebugProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnAttach = ze_lib::context->zetDdiTable.Debug.pfnAttach;
    if( nullptr == pfnAttach )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAttach( hDevice, config, phDebug );
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
ze_result_t ZE_APICALL
zetDebugDetach(
    zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
    )
{
    auto pfnDetach = ze_lib::context->zetDdiTable.Debug.pfnDetach;
    if( nullptr == pfnDetach )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDetach( hDebug );
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
///         + `nullptr == event`
///     - ::ZE_RESULT_NOT_READY
///         + the timeout expired
ze_result_t ZE_APICALL
zetDebugReadEvent(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then immediately returns the status of the event;
                                                    ///< if UINT64_MAX, then function will not return until complete or device
                                                    ///< is lost.
                                                    ///< Due to external dependencies, timeout may be rounded to the closest
                                                    ///< value allowed by the accuracy of those dependencies.
    zet_debug_event_t* event                        ///< [in,out] a pointer to a ::zet_debug_event_t.
    )
{
    auto pfnReadEvent = ze_lib::context->zetDdiTable.Debug.pfnReadEvent;
    if( nullptr == pfnReadEvent )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadEvent( hDebug, timeout, event );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Acknowledge a debug event.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
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
    auto pfnAcknowledgeEvent = ze_lib::context->zetDdiTable.Debug.pfnAcknowledgeEvent;
    if( nullptr == pfnAcknowledgeEvent )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnAcknowledgeEvent( hDebug, event );
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
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is already stopped or unavailable
ze_result_t ZE_APICALL
zetDebugInterrupt(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread                       ///< [in] the thread to interrupt
    )
{
    auto pfnInterrupt = ze_lib::context->zetDdiTable.Debug.pfnInterrupt;
    if( nullptr == pfnInterrupt )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnInterrupt( hDebug, thread );
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
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is already running or unavailable
ze_result_t ZE_APICALL
zetDebugResume(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread                       ///< [in] the thread to resume
    )
{
    auto pfnResume = ze_lib::context->zetDdiTable.Debug.pfnResume;
    if( nullptr == pfnResume )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnReadMemory = ze_lib::context->zetDdiTable.Debug.pfnReadMemory;
    if( nullptr == pfnReadMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnWriteMemory = ze_lib::context->zetDdiTable.Debug.pfnWriteMemory;
    if( nullptr == pfnWriteMemory )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnWriteMemory( hDebug, thread, desc, size, buffer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves debug register set properties.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
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
    auto pfnGetRegisterSetProperties = ze_lib::context->zetDdiTable.Debug.pfnGetRegisterSetProperties;
    if( nullptr == pfnGetRegisterSetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
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
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is running or unavailable
ze_result_t ZE_APICALL
zetDebugReadRegisters(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread,                      ///< [in] the thread identifier
    uint32_t type,                                  ///< [in] register set type
    uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                    ///< than ::zet_debug_regset_properties_t.count for the type
    uint32_t count,                                 ///< [in] the number of registers to read; start+count must be <=
                                                    ///< zet_debug_register_group_properties_t.count for the type
    void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
    )
{
    auto pfnReadRegisters = ze_lib::context->zetDdiTable.Debug.pfnReadRegisters;
    if( nullptr == pfnReadRegisters )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
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
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + the thread is running or unavailable
ze_result_t ZE_APICALL
zetDebugWriteRegisters(
    zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
    ze_device_thread_t thread,                      ///< [in] the thread identifier
    uint32_t type,                                  ///< [in] register set type
    uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                    ///< than ::zet_debug_regset_properties_t.count for the type
    uint32_t count,                                 ///< [in] the number of registers to write; start+count must be <=
                                                    ///< zet_debug_register_group_properties_t.count for the type
    void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
    )
{
    auto pfnWriteRegisters = ze_lib::context->zetDdiTable.Debug.pfnWriteRegisters;
    if( nullptr == pfnWriteRegisters )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnGet = ze_lib::context->zetDdiTable.MetricGroup.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnGetProperties = ze_lib::context->zetDdiTable.MetricGroup.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnCalculateMetricValues = ze_lib::context->zetDdiTable.MetricGroup.pfnCalculateMetricValues;
    if( nullptr == pfnCalculateMetricValues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnGet = ze_lib::context->zetDdiTable.Metric.pfnGet;
    if( nullptr == pfnGet )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnGetProperties = ze_lib::context->zetDdiTable.Metric.pfnGetProperties;
    if( nullptr == pfnGetProperties )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnActivateMetricGroups = ze_lib::context->zetDdiTable.Context.pfnActivateMetricGroups;
    if( nullptr == pfnActivateMetricGroups )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnOpen = ze_lib::context->zetDdiTable.MetricStreamer.pfnOpen;
    if( nullptr == pfnOpen )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnAppendMetricStreamerMarker = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricStreamerMarker;
    if( nullptr == pfnAppendMetricStreamerMarker )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricStreamer`
ze_result_t ZE_APICALL
zetMetricStreamerClose(
    zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
    )
{
    auto pfnClose = ze_lib::context->zetDdiTable.MetricStreamer.pfnClose;
    if( nullptr == pfnClose )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricStreamer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
ze_result_t ZE_APICALL
zetMetricStreamerReadData(
    zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
    uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                    ///< if UINT32_MAX, then function will retrieve all reports available
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
    auto pfnReadData = ze_lib::context->zetDdiTable.MetricStreamer.pfnReadData;
    if( nullptr == pfnReadData )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnCreate = ze_lib::context->zetDdiTable.MetricQueryPool.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQueryPool`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zetMetricQueryPoolDestroy(
    zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
    )
{
    auto pfnDestroy = ze_lib::context->zetDdiTable.MetricQueryPool.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnCreate = ze_lib::context->zetDdiTable.MetricQuery.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zetMetricQueryDestroy(
    zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
    )
{
    auto pfnDestroy = ze_lib::context->zetDdiTable.MetricQuery.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDestroy( hMetricQuery );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets a metric query object back to inital state.
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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
ze_result_t ZE_APICALL
zetMetricQueryReset(
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
    )
{
    auto pfnReset = ze_lib::context->zetDdiTable.MetricQuery.pfnReset;
    if( nullptr == pfnReset )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
ze_result_t ZE_APICALL
zetCommandListAppendMetricQueryBegin(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    )
{
    auto pfnAppendMetricQueryBegin = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricQueryBegin;
    if( nullptr == pfnAppendMetricQueryBegin )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phWaitEvents`
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
    auto pfnAppendMetricQueryEnd = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricQueryEnd;
    if( nullptr == pfnAppendMetricQueryEnd )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
ze_result_t ZE_APICALL
zetCommandListAppendMetricMemoryBarrier(
    zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
    )
{
    auto pfnAppendMetricMemoryBarrier = ze_lib::context->zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;
    if( nullptr == pfnAppendMetricMemoryBarrier )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnGetData = ze_lib::context->zetDdiTable.MetricQuery.pfnGetData;
    if( nullptr == pfnGetData )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnGetProfileInfo = ze_lib::context->zetDdiTable.Kernel.pfnGetProfileInfo;
    if( nullptr == pfnGetProfileInfo )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hContext`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pUserData`
///         + `nullptr == phTracer`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t ZE_APICALL
zetTracerExpCreate(
    zet_context_handle_t hContext,                  ///< [in] handle of the context object
    const zet_tracer_exp_desc_t* desc,              ///< [in] pointer to tracer descriptor
    zet_tracer_exp_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
    )
{
    auto pfnCreate = ze_lib::context->zetDdiTable.TracerExp.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zetTracerExpDestroy(
    zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
    )
{
    auto pfnDestroy = ze_lib::context->zetDdiTable.TracerExp.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnSetPrologues = ze_lib::context->zetDdiTable.TracerExp.pfnSetPrologues;
    if( nullptr == pfnSetPrologues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnSetEpilogues = ze_lib::context->zetDdiTable.TracerExp.pfnSetEpilogues;
    if( nullptr == pfnSetEpilogues )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
ze_result_t ZE_APICALL
zetTracerExpSetEnabled(
    zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
    ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
    )
{
    auto pfnSetEnabled = ze_lib::context->zetDdiTable.TracerExp.pfnSetEnabled;
    if( nullptr == pfnSetEnabled )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    auto pfnCalculateMultipleMetricValuesExp = ze_lib::context->zetDdiTable.MetricGroupExp.pfnCalculateMultipleMetricValuesExp;
    if( nullptr == pfnCalculateMultipleMetricValuesExp )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
}

} // extern "C"
