/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_layer.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetInit
    ze_result_t __zecall
    zetInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        auto pfnInit = context.zetDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( 1 <= flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnInit( flags );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugAttach
    ze_result_t __zecall
    zetDebugAttach(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* hDebug              ///< [out] debug session handle
        )
    {
        auto pfnAttach = context.zetDdiTable.Debug.pfnAttach;

        if( nullptr == pfnAttach )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == config )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnAttach( hDevice, config, hDebug );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugDetach
    ze_result_t __zecall
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    {
        auto pfnDetach = context.zetDdiTable.Debug.pfnDetach;

        if( nullptr == pfnDetach )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDetach( hDebug );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetNumThreads
    ze_result_t __zecall
    zetDebugGetNumThreads(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t* pNumThreads                           ///< [out] the maximal number of threads
        )
    {
        auto pfnGetNumThreads = context.zetDdiTable.Debug.pfnGetNumThreads;

        if( nullptr == pfnGetNumThreads )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNumThreads )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetNumThreads( hDebug, pNumThreads );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadEvent
    ze_result_t __zecall
    zetDebugReadEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t timeout,                               ///< [in] timeout in milliseconds (or ::ZET_DEBUG_TIMEOUT_INFINITE)
        size_t size,                                    ///< [in] the size of the buffer in bytes
        void* buffer                                    ///< [in,out] a buffer to hold the event data
        )
    {
        auto pfnReadEvent = context.zetDdiTable.Debug.pfnReadEvent;

        if( nullptr == pfnReadEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadEvent( hDebug, timeout, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugInterrupt
    ze_result_t __zecall
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto pfnInterrupt = context.zetDdiTable.Debug.pfnInterrupt;

        if( nullptr == pfnInterrupt )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnInterrupt( hDebug, threadid );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugResume
    ze_result_t __zecall
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
        )
    {
        auto pfnResume = context.zetDdiTable.Debug.pfnResume;

        if( nullptr == pfnResume )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnResume( hDebug, threadid );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadMemory
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
        auto pfnReadMemory = context.zetDdiTable.Debug.pfnReadMemory;

        if( nullptr == pfnReadMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadMemory( hDebug, threadid, memSpace, address, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteMemory
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
        auto pfnWriteMemory = context.zetDdiTable.Debug.pfnWriteMemory;

        if( nullptr == pfnWriteMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnWriteMemory( hDebug, threadid, memSpace, address, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadState
    ze_result_t __zecall
    zetDebugReadState(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the register state
        )
    {
        auto pfnReadState = context.zetDdiTable.Debug.pfnReadState;

        if( nullptr == pfnReadState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadState( hDebug, threadid, offset, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteState
    ze_result_t __zecall
    zetDebugWriteState(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid,                              ///< [in] the thread context
        uint64_t offset,                                ///< [in] the offset into the register state area
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto pfnWriteState = context.zetDdiTable.Debug.pfnWriteState;

        if( nullptr == pfnWriteState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDebug )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == buffer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnWriteState( hDebug, threadid, offset, size, buffer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGet
    ze_result_t __zecall
    zetMetricGroupGet(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< metric groups.
                                                        ///< if count is larger than the number of metric groups available, then
                                                        ///< the driver will update the value with the correct number of metric
                                                        ///< groups available.
        zet_metric_group_handle_t* phMetricGroups       ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups
        )
    {
        auto pfnGet = context.zetDdiTable.MetricGroup.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hDevice, pCount, phMetricGroups );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetProperties
    ze_result_t __zecall
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.MetricGroup.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hMetricGroup, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMetricValues
    ze_result_t __zecall
    zetMetricGroupCalculateMetricValues(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric values to be calculated.
                                                        ///< if count is non-zero, then driver will only calculate that number of
                                                        ///< metric values.
                                                        ///< if count is larger than the number available in the raw data buffer,
                                                        ///< then the driver will update the value with the actual number of metric
                                                        ///< values to be calculated.
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                        ///< metrics
        )
    {
        auto pfnCalculateMetricValues = context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;

        if( nullptr == pfnCalculateMetricValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRawData )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pMetricValueCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGet
    ze_result_t __zecall
    zetMetricGet(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metrics available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                        ///< if count is larger than the number of metrics available, then the
                                                        ///< driver will update the value with the correct number of metrics available.
        zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics
        )
    {
        auto pfnGet = context.zetDdiTable.Metric.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hMetricGroup, pCount, phMetrics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGetProperties
    ze_result_t __zecall
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.Metric.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetric )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hMetric, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceActivateMetricGroups
    ze_result_t __zecall
    zetDeviceActivateMetricGroups(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
        zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                        ///< activate. NULL to deactivate.
        )
    {
        auto pfnActivateMetricGroups = context.zetDdiTable.Device.pfnActivateMetricGroups;

        if( nullptr == pfnActivateMetricGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnActivateMetricGroups( hDevice, count, phMetricGroups );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerOpen
    ze_result_t __zecall
    zetMetricTracerOpen(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_tracer_desc_t* desc,                 ///< [in,out] metric tracer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Must
                                                        ///< be device to host type.
        zet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
        )
    {
        auto pfnOpen = context.zetDdiTable.MetricTracer.pfnOpen;

        if( nullptr == pfnOpen )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZET_METRIC_TRACER_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        }

        return pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricTracerMarker
    ze_result_t __zecall
    zetCommandListAppendMetricTracerMarker(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t value                                  ///< [in] tracer marker value
        )
    {
        auto pfnAppendMetricTracerMarker = context.zetDdiTable.CommandList.pfnAppendMetricTracerMarker;

        if( nullptr == pfnAppendMetricTracerMarker )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerClose
    ze_result_t __zecall
    zetMetricTracerClose(
        zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
        )
    {
        auto pfnClose = context.zetDdiTable.MetricTracer.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnClose( hMetricTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerReadData
    ze_result_t __zecall
    zetMetricTracerReadData(
        zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
        uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                        ///< if UINT32_MAX, then function will retrieve all reports available
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< reports in raw format
        )
    {
        auto pfnReadData = context.zetDdiTable.MetricTracer.pfnReadData;

        if( nullptr == pfnReadData )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRawDataSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolCreate
    ze_result_t __zecall
    zetMetricQueryPoolCreate(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQueryPool.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricGroup )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

            if( 1 <= desc->flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolDestroy
    ze_result_t __zecall
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQueryPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hMetricQueryPool );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryCreate
    ze_result_t __zecall
    zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQuery.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQueryPool )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnCreate( hMetricQueryPool, index, phMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryDestroy
    ze_result_t __zecall
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQuery.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryReset
    ze_result_t __zecall
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        auto pfnReset = context.zetDdiTable.MetricQuery.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnReset( hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    ze_result_t __zecall
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        auto pfnAppendMetricQueryBegin = context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;

        if( nullptr == pfnAppendMetricQueryBegin )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryEnd
    ze_result_t __zecall
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
        )
    {
        auto pfnAppendMetricQueryEnd = context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;

        if( nullptr == pfnAppendMetricQueryEnd )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    ze_result_t __zecall
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        auto pfnAppendMetricMemoryBarrier = context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;

        if( nullptr == pfnAppendMetricMemoryBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hCommandList )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnAppendMetricMemoryBarrier( hCommandList );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryGetData
    ze_result_t __zecall
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
        auto pfnGetData = context.zetDdiTable.MetricQuery.pfnGetData;

        if( nullptr == pfnGetData )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMetricQuery )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRawDataSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetData( hMetricQuery, pRawDataSize, pRawData );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetModuleGetDebugInfo
    ze_result_t __zecall
    zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        auto pfnGetDebugInfo = context.zetDdiTable.Module.pfnGetDebugInfo;

        if( nullptr == pfnGetDebugInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hModule )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 0 <= format )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pSize )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetKernelGetProfileInfo
    ze_result_t __zecall
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
        )
    {
        auto pfnGetProfileInfo = context.zetDdiTable.Kernel.pfnGetProfileInfo;

        if( nullptr == pfnGetProfileInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hKernel )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pInfo )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProfileInfo( hKernel, pInfo );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanGet
    ze_result_t __zecall
    zetSysmanGet(
        zet_device_handle_t hDevice,                    ///< [in] Handle of the device
        zet_sysman_version_t version,                   ///< [in] Sysman version that application was built with
        zet_sysman_handle_t* phSysman                   ///< [out] Handle for accessing Sysman features
        )
    {
        auto pfnGet = context.zetDdiTable.Sysman.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 65536 <= version )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == phSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hDevice, version, phSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceGetProperties
    ze_result_t __zecall
    zetSysmanDeviceGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
        )
    {
        auto pfnDeviceGetProperties = context.zetDdiTable.Sysman.pfnDeviceGetProperties;

        if( nullptr == pfnDeviceGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnDeviceGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetSupportedModes
    ze_result_t __zecall
    zetSysmanSchedulerGetSupportedModes(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of scheduler modes.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of supported modes.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< supported scheduler modes.
                                                        ///< if count is larger than the number of supported scheduler modes, then
                                                        ///< the driver will update the value with the correct number of supported
                                                        ///< scheduler modes that are returned.
        zet_sched_mode_t* pModes                        ///< [in,out][optional][range(0, *pCount)] Array of supported scheduler
                                                        ///< modes
        )
    {
        auto pfnSchedulerGetSupportedModes = context.zetDdiTable.Sysman.pfnSchedulerGetSupportedModes;

        if( nullptr == pfnSchedulerGetSupportedModes )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerGetSupportedModes( hSysman, pCount, pModes );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetCurrentMode
    ze_result_t __zecall
    zetSysmanSchedulerGetCurrentMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
        )
    {
        auto pfnSchedulerGetCurrentMode = context.zetDdiTable.Sysman.pfnSchedulerGetCurrentMode;

        if( nullptr == pfnSchedulerGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerGetCurrentMode( hSysman, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetTimeoutModeProperties
    ze_result_t __zecall
    zetSysmanSchedulerGetTimeoutModeProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zet_sched_timeout_properties_t* pConfig         ///< [in] Will contain the current parameters for this mode.
        )
    {
        auto pfnSchedulerGetTimeoutModeProperties = context.zetDdiTable.Sysman.pfnSchedulerGetTimeoutModeProperties;

        if( nullptr == pfnSchedulerGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerGetTimeoutModeProperties( hSysman, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetTimesliceModeProperties
    ze_result_t __zecall
    zetSysmanSchedulerGetTimesliceModeProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zet_sched_timeslice_properties_t* pConfig       ///< [in] Will contain the current parameters for this mode.
        )
    {
        auto pfnSchedulerGetTimesliceModeProperties = context.zetDdiTable.Sysman.pfnSchedulerGetTimesliceModeProperties;

        if( nullptr == pfnSchedulerGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerGetTimesliceModeProperties( hSysman, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetTimeoutMode
    ze_result_t __zecall
    zetSysmanSchedulerSetTimeoutMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetTimeoutMode = context.zetDdiTable.Sysman.pfnSchedulerSetTimeoutMode;

        if( nullptr == pfnSchedulerSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerSetTimeoutMode( hSysman, pProperties, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetTimesliceMode
    ze_result_t __zecall
    zetSysmanSchedulerSetTimesliceMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetTimesliceMode = context.zetDdiTable.Sysman.pfnSchedulerSetTimesliceMode;

        if( nullptr == pfnSchedulerSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerSetTimesliceMode( hSysman, pProperties, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetExclusiveMode
    ze_result_t __zecall
    zetSysmanSchedulerSetExclusiveMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetExclusiveMode = context.zetDdiTable.Sysman.pfnSchedulerSetExclusiveMode;

        if( nullptr == pfnSchedulerSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerSetExclusiveMode( hSysman, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerSetComputeUnitDebugMode
    ze_result_t __zecall
    zetSysmanSchedulerSetComputeUnitDebugMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        ze_bool_t* pNeedReboot                          ///< [in] Will be set to TRUE if a system reboot is needed to apply the new
                                                        ///< scheduler mode.
        )
    {
        auto pfnSchedulerSetComputeUnitDebugMode = context.zetDdiTable.Sysman.pfnSchedulerSetComputeUnitDebugMode;

        if( nullptr == pfnSchedulerSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNeedReboot )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSchedulerSetComputeUnitDebugMode( hSysman, pNeedReboot );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileGetSupported
    ze_result_t __zecall
    zetSysmanPerformanceProfileGetSupported(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of performance profiles.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of supported performance profiles.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< supported performance profiles.
                                                        ///< if count is larger than the number of supported performance profiles,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< supported performance profiles that are returned.
        zet_perf_profile_t* pProfiles                   ///< [in,out][optional][range(0, *pCount)] Array of supported performance
                                                        ///< profiles
        )
    {
        auto pfnPerformanceProfileGetSupported = context.zetDdiTable.Sysman.pfnPerformanceProfileGetSupported;

        if( nullptr == pfnPerformanceProfileGetSupported )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPerformanceProfileGetSupported( hSysman, pCount, pProfiles );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileGet
    ze_result_t __zecall
    zetSysmanPerformanceProfileGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_perf_profile_t* pProfile                    ///< [in] The performance profile currently loaded.
        )
    {
        auto pfnPerformanceProfileGet = context.zetDdiTable.Sysman.pfnPerformanceProfileGet;

        if( nullptr == pfnPerformanceProfileGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProfile )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPerformanceProfileGet( hSysman, pProfile );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileSet
    ze_result_t __zecall
    zetSysmanPerformanceProfileSet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_perf_profile_t profile                      ///< [in] The performance profile to load.
        )
    {
        auto pfnPerformanceProfileSet = context.zetDdiTable.Sysman.pfnPerformanceProfileSet;

        if( nullptr == pfnPerformanceProfileSet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 2 <= profile )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnPerformanceProfileSet( hSysman, profile );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanProcessesGetState
    ze_result_t __zecall
    zetSysmanProcessesGetState(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of processes currently using the device.
                                                        ///< if count is non-zero, then driver will only retrieve that number of processes.
                                                        ///< if count is larger than the number of processes, then the driver will
                                                        ///< update the value with the correct number of processes that are returned.
        zet_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                        ///< one for each process currently using the device
        )
    {
        auto pfnProcessesGetState = context.zetDdiTable.Sysman.pfnProcessesGetState;

        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnProcessesGetState( hSysman, pCount, pProcesses );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceReset
    ze_result_t __zecall
    zetSysmanDeviceReset(
        zet_sysman_handle_t hSysman                     ///< [in] Sysman handle for the device
        )
    {
        auto pfnDeviceReset = context.zetDdiTable.Sysman.pfnDeviceReset;

        if( nullptr == pfnDeviceReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDeviceReset( hSysman );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceGetRepairStatus
    ze_result_t __zecall
    zetSysmanDeviceGetRepairStatus(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zet_repair_status_t* pRepairStatus              ///< [in] Will indicate if the device was repaired
        )
    {
        auto pfnDeviceGetRepairStatus = context.zetDdiTable.Sysman.pfnDeviceGetRepairStatus;

        if( nullptr == pfnDeviceGetRepairStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pRepairStatus )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnDeviceGetRepairStatus( hSysman, pRepairStatus );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetProperties
    ze_result_t __zecall
    zetSysmanPciGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
        )
    {
        auto pfnPciGetProperties = context.zetDdiTable.Sysman.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetProperties( hSysman, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetState
    ze_result_t __zecall
    zetSysmanPciGetState(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
        )
    {
        auto pfnPciGetState = context.zetDdiTable.Sysman.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetState( hSysman, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetBars
    ze_result_t __zecall
    zetSysmanPciGetBars(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of bars.
                                                        ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                        ///< if count is larger than the number of bar, then the driver will update
                                                        ///< the value with the correct number of bars that are returned.
        zet_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of bar properties
        )
    {
        auto pfnPciGetBars = context.zetDdiTable.Sysman.pfnPciGetBars;

        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetBars( hSysman, pCount, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetStats
    ze_result_t __zecall
    zetSysmanPciGetStats(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        auto pfnPciGetStats = context.zetDdiTable.Sysman.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetStats( hSysman, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGet
    ze_result_t __zecall
    zetSysmanPowerGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_pwr_handle_t* phPower                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnPowerGet = context.zetDdiTable.Sysman.pfnPowerGet;

        if( nullptr == pfnPowerGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPowerGet( hSysman, pCount, phPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetProperties
    ze_result_t __zecall
    zetSysmanPowerGetProperties(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanPower.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPower, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetEnergyCounter
    ze_result_t __zecall
    zetSysmanPowerGetEnergyCounter(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_energy_counter_t* pEnergy             ///< [in] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto pfnGetEnergyCounter = context.zetDdiTable.SysmanPower.pfnGetEnergyCounter;

        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pEnergy )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetEnergyCounter( hPower, pEnergy );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetLimits
    ze_result_t __zecall
    zetSysmanPowerGetLimits(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_sustained_limit_t* pSustained,        ///< [in][optional] The sustained power limit.
        zet_power_burst_limit_t* pBurst,                ///< [in][optional] The burst power limit.
        zet_power_peak_limit_t* pPeak                   ///< [in][optional] The peak power limit.
        )
    {
        auto pfnGetLimits = context.zetDdiTable.SysmanPower.pfnGetLimits;

        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerSetLimits
    ze_result_t __zecall
    zetSysmanPowerSetLimits(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        const zet_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit.
        const zet_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit.
        const zet_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit.
        )
    {
        auto pfnSetLimits = context.zetDdiTable.SysmanPower.pfnSetLimits;

        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetEnergyThreshold
    ze_result_t __zecall
    zetSysmanPowerGetEnergyThreshold(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_energy_threshold_t* pThreshold              ///< [in] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        auto pfnGetEnergyThreshold = context.zetDdiTable.SysmanPower.pfnGetEnergyThreshold;

        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThreshold )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetEnergyThreshold( hPower, pThreshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerSetEnergyThreshold
    ze_result_t __zecall
    zetSysmanPowerSetEnergyThreshold(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        auto pfnSetEnergyThreshold = context.zetDdiTable.SysmanPower.pfnSetEnergyThreshold;

        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetEnergyThreshold( hPower, threshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGet
    ze_result_t __zecall
    zetSysmanFrequencyGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_freq_handle_t* phFrequency           ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFrequencyGet = context.zetDdiTable.Sysman.pfnFrequencyGet;

        if( nullptr == pfnFrequencyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFrequencyGet( hSysman, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetProperties
    ze_result_t __zecall
    zetSysmanFrequencyGetProperties(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanFrequency.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFrequency, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetAvailableClocks
    ze_result_t __zecall
    zetSysmanFrequencyGetAvailableClocks(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of frequencies available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                        ///< If count is larger than the number of frequencies available, then the
                                                        ///< driver will update the value with the correct number of frequencies available.
        double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                        ///< MHz and sorted from slowest to fastest
        )
    {
        auto pfnGetAvailableClocks = context.zetDdiTable.SysmanFrequency.pfnGetAvailableClocks;

        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetRange
    ze_result_t __zecall
    zetSysmanFrequencyGetRange(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_range_t* pLimits                       ///< [in] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetRange = context.zetDdiTable.SysmanFrequency.pfnGetRange;

        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencySetRange
    ze_result_t __zecall
    zetSysmanFrequencySetRange(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        const zet_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnSetRange = context.zetDdiTable.SysmanFrequency.pfnSetRange;

        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetState
    ze_result_t __zecall
    zetSysmanFrequencyGetState(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanFrequency.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hFrequency, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetThrottleTime
    ze_result_t __zecall
    zetSysmanFrequencyGetThrottleTime(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_throttle_time_t* pThrottleTime         ///< [in] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetThrottleTime = context.zetDdiTable.SysmanFrequency.pfnGetThrottleTime;

        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThrottleTime )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetThrottleTime( hFrequency, pThrottleTime );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetCapabilities
    ze_result_t __zecall
    zetSysmanFrequencyOcGetCapabilities(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_capabilities_t* pOcCapabilities          ///< [in] Pointer to the capabilities structure ::zet_oc_capabilities_t.
        )
    {
        auto pfnOcGetCapabilities = context.zetDdiTable.SysmanFrequency.pfnOcGetCapabilities;

        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcCapabilities )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetConfig
    ze_result_t __zecall
    zetSysmanFrequencyOcGetConfig(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_config_t* pOcConfiguration               ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
        )
    {
        auto pfnOcGetConfig = context.zetDdiTable.SysmanFrequency.pfnOcGetConfig;

        if( nullptr == pfnOcGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcConfiguration )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetConfig( hFrequency, pOcConfiguration );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetConfig
    ze_result_t __zecall
    zetSysmanFrequencyOcSetConfig(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_config_t* pOcConfiguration,              ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
        ze_bool_t* pDeviceRestart                       ///< [in,out] This will be set to true if the device needs to be restarted
                                                        ///< in order to enable the new overclock settings.
        )
    {
        auto pfnOcSetConfig = context.zetDdiTable.SysmanFrequency.pfnOcSetConfig;

        if( nullptr == pfnOcSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcConfiguration )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pDeviceRestart )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetIccMax
    ze_result_t __zecall
    zetSysmanFrequencyOcGetIccMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in] Will contain the maximum current limit in Amperes on successful
                                                        ///< return.
        )
    {
        auto pfnOcGetIccMax = context.zetDdiTable.SysmanFrequency.pfnOcGetIccMax;

        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcIccMax )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetIccMax( hFrequency, pOcIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetIccMax
    ze_result_t __zecall
    zetSysmanFrequencyOcSetIccMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        auto pfnOcSetIccMax = context.zetDdiTable.SysmanFrequency.pfnOcSetIccMax;

        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetIccMax( hFrequency, ocIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetTjMax
    ze_result_t __zecall
    zetSysmanFrequencyOcGetTjMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in] Will contain the maximum temperature limit in degrees Celsius on
                                                        ///< successful return.
        )
    {
        auto pfnOcGetTjMax = context.zetDdiTable.SysmanFrequency.pfnOcGetTjMax;

        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcTjMax )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetTjMax( hFrequency, pOcTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetTjMax
    ze_result_t __zecall
    zetSysmanFrequencyOcSetTjMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        auto pfnOcSetTjMax = context.zetDdiTable.SysmanFrequency.pfnOcSetTjMax;

        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetTjMax( hFrequency, ocTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGet
    ze_result_t __zecall
    zetSysmanEngineGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_engine_handle_t* phEngine            ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnEngineGet = context.zetDdiTable.Sysman.pfnEngineGet;

        if( nullptr == pfnEngineGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEngineGet( hSysman, pCount, phEngine );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetProperties
    ze_result_t __zecall
    zetSysmanEngineGetProperties(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanEngine.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hEngine, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetActivity
    ze_result_t __zecall
    zetSysmanEngineGetActivity(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        auto pfnGetActivity = context.zetDdiTable.SysmanEngine.pfnGetActivity;

        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetActivity( hEngine, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGet
    ze_result_t __zecall
    zetSysmanStandbyGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_standby_handle_t* phStandby          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnStandbyGet = context.zetDdiTable.Sysman.pfnStandbyGet;

        if( nullptr == pfnStandbyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnStandbyGet( hSysman, pCount, phStandby );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetProperties
    ze_result_t __zecall
    zetSysmanStandbyGetProperties(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanStandby.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hStandby, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetMode
    ze_result_t __zecall
    zetSysmanStandbyGetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
        )
    {
        auto pfnGetMode = context.zetDdiTable.SysmanStandby.pfnGetMode;

        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMode( hStandby, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbySetMode
    ze_result_t __zecall
    zetSysmanStandbySetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        auto pfnSetMode = context.zetDdiTable.SysmanStandby.pfnSetMode;

        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 1 <= mode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetMode( hStandby, mode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGet
    ze_result_t __zecall
    zetSysmanFirmwareGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_firmware_handle_t* phFirmware        ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFirmwareGet = context.zetDdiTable.Sysman.pfnFirmwareGet;

        if( nullptr == pfnFirmwareGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFirmwareGet( hSysman, pCount, phFirmware );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetProperties
    ze_result_t __zecall
    zetSysmanFirmwareGetProperties(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        zet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanFirmware.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFirmware, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetChecksum
    ze_result_t __zecall
    zetSysmanFirmwareGetChecksum(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        auto pfnGetChecksum = context.zetDdiTable.SysmanFirmware.pfnGetChecksum;

        if( nullptr == pfnGetChecksum )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pChecksum )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetChecksum( hFirmware, pChecksum );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareFlash
    ze_result_t __zecall
    zetSysmanFirmwareFlash(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto pfnFlash = context.zetDdiTable.SysmanFirmware.pfnFlash;

        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pImage )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFlash( hFirmware, pImage, size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGet
    ze_result_t __zecall
    zetSysmanMemoryGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_mem_handle_t* phMemory               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnMemoryGet = context.zetDdiTable.Sysman.pfnMemoryGet;

        if( nullptr == pfnMemoryGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnMemoryGet( hSysman, pCount, phMemory );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetProperties
    ze_result_t __zecall
    zetSysmanMemoryGetProperties(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanMemory.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hMemory, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetState
    ze_result_t __zecall
    zetSysmanMemoryGetState(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_state_t* pState                         ///< [in] Will contain the current health and allocated memory.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanMemory.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hMemory, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetBandwidth
    ze_result_t __zecall
    zetSysmanMemoryGetBandwidth(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        auto pfnGetBandwidth = context.zetDdiTable.SysmanMemory.pfnGetBandwidth;

        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pBandwidth )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetBandwidth( hMemory, pBandwidth );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGet
    ze_result_t __zecall
    zetSysmanFabricPortGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_fabric_port_handle_t* phPort         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFabricPortGet = context.zetDdiTable.Sysman.pfnFabricPortGet;

        if( nullptr == pfnFabricPortGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFabricPortGet( hSysman, pCount, phPort );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetProperties
    ze_result_t __zecall
    zetSysmanFabricPortGetProperties(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_properties_t* pProperties       ///< [in] Will contain properties of the Fabric Port.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanFabricPort.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPort, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetLinkType
    ze_result_t __zecall
    zetSysmanFabricPortGetLinkType(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        ze_bool_t verbose,                              ///< [in] Set to true to get a more detailed report.
        zet_fabric_link_type_t* pLinkType               ///< [in] Will contain details about the link attached to the Fabric port.
        )
    {
        auto pfnGetLinkType = context.zetDdiTable.SysmanFabricPort.pfnGetLinkType;

        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLinkType )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetLinkType( hPort, verbose, pLinkType );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetConfig
    ze_result_t __zecall
    zetSysmanFabricPortGetConfig(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_config_t* pConfig               ///< [in] Will contain configuration of the Fabric Port.
        )
    {
        auto pfnGetConfig = context.zetDdiTable.SysmanFabricPort.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hPort, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortSetConfig
    ze_result_t __zecall
    zetSysmanFabricPortSetConfig(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        const zet_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        auto pfnSetConfig = context.zetDdiTable.SysmanFabricPort.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hPort, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetState
    ze_result_t __zecall
    zetSysmanFabricPortGetState(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_state_t* pState                 ///< [in] Will contain the current state of the Fabric Port
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanFabricPort.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hPort, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetThroughput
    ze_result_t __zecall
    zetSysmanFabricPortGetThroughput(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_throughput_t* pThroughput       ///< [in] Will contain the Fabric port throughput counters and maximum
                                                        ///< bandwidth.
        )
    {
        auto pfnGetThroughput = context.zetDdiTable.SysmanFabricPort.pfnGetThroughput;

        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThroughput )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetThroughput( hPort, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGet
    ze_result_t __zecall
    zetSysmanTemperatureGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_temp_handle_t* phTemperature         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnTemperatureGet = context.zetDdiTable.Sysman.pfnTemperatureGet;

        if( nullptr == pfnTemperatureGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnTemperatureGet( hSysman, pCount, phTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetProperties
    ze_result_t __zecall
    zetSysmanTemperatureGetProperties(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanTemperature.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hTemperature, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetConfig
    ze_result_t __zecall
    zetSysmanTemperatureGetConfig(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zet_temp_config_t* pConfig                      ///< [in] Returns current configuration.
        )
    {
        auto pfnGetConfig = context.zetDdiTable.SysmanTemperature.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hTemperature, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureSetConfig
    ze_result_t __zecall
    zetSysmanTemperatureSetConfig(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        const zet_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        auto pfnSetConfig = context.zetDdiTable.SysmanTemperature.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hTemperature, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetState
    ze_result_t __zecall
    zetSysmanTemperatureGetState(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        double* pTemperature                            ///< [in] Will contain the temperature read from the specified sensor in
                                                        ///< degrees Celcius.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanTemperature.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hTemperature, pTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGet
    ze_result_t __zecall
    zetSysmanPsuGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_psu_handle_t* phPsu                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnPsuGet = context.zetDdiTable.Sysman.pfnPsuGet;

        if( nullptr == pfnPsuGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPsuGet( hSysman, pCount, phPsu );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetProperties
    ze_result_t __zecall
    zetSysmanPsuGetProperties(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanPsu.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPsu, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetState
    ze_result_t __zecall
    zetSysmanPsuGetState(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanPsu.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hPsu, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGet
    ze_result_t __zecall
    zetSysmanFanGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_fan_handle_t* phFan                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnFanGet = context.zetDdiTable.Sysman.pfnFanGet;

        if( nullptr == pfnFanGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFanGet( hSysman, pCount, phFan );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetProperties
    ze_result_t __zecall
    zetSysmanFanGetProperties(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanFan.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFan, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetConfig
    ze_result_t __zecall
    zetSysmanFanGetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        auto pfnGetConfig = context.zetDdiTable.SysmanFan.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanSetConfig
    ze_result_t __zecall
    zetSysmanFanSetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        auto pfnSetConfig = context.zetDdiTable.SysmanFan.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetState
    ze_result_t __zecall
    zetSysmanFanGetState(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        uint32_t* pSpeed                                ///< [in] Will contain the current speed of the fan in the units requested.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanFan.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 1 <= units )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pSpeed )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hFan, units, pSpeed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGet
    ze_result_t __zecall
    zetSysmanLedGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_led_handle_t* phLed                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnLedGet = context.zetDdiTable.Sysman.pfnLedGet;

        if( nullptr == pfnLedGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnLedGet( hSysman, pCount, phLed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetProperties
    ze_result_t __zecall
    zetSysmanLedGetProperties(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanLed.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hLed, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetState
    ze_result_t __zecall
    zetSysmanLedGetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanLed.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedSetState
    ze_result_t __zecall
    zetSysmanLedSetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const zet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        auto pfnSetState = context.zetDdiTable.SysmanLed.pfnSetState;

        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGet
    ze_result_t __zecall
    zetSysmanRasGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_ras_handle_t* phRas                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnRasGet = context.zetDdiTable.Sysman.pfnRasGet;

        if( nullptr == pfnRasGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRasGet( hSysman, pCount, phRas );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetProperties
    ze_result_t __zecall
    zetSysmanRasGetProperties(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanRas.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hRas, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetConfig
    ze_result_t __zecall
    zetSysmanRasGetConfig(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zet_ras_config_t* pConfig                       ///< [in] Will be populed with the current RAS configuration - thresholds
                                                        ///< used to trigger events
        )
    {
        auto pfnGetConfig = context.zetDdiTable.SysmanRas.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hRas, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasSetConfig
    ze_result_t __zecall
    zetSysmanRasSetConfig(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        const zet_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        auto pfnSetConfig = context.zetDdiTable.SysmanRas.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hRas, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetState
    ze_result_t __zecall
    zetSysmanRasGetState(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        uint64_t* pTotalErrors,                         ///< [in] The number total number of errors that have occurred
        zet_ras_details_t* pDetails                     ///< [in][optional] Breakdown of where errors have occurred
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanRas.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pTotalErrors )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hRas, clear, pTotalErrors, pDetails );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventGet
    ze_result_t __zecall
    zetSysmanEventGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zet_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
        )
    {
        auto pfnEventGet = context.zetDdiTable.Sysman.pfnEventGet;

        if( nullptr == pfnEventGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEventGet( hSysman, phEvent );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventGetConfig
    ze_result_t __zecall
    zetSysmanEventGetConfig(
        zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        zet_event_config_t* pConfig                     ///< [in] Will contain the current event configuration (list of registered
                                                        ///< events).
        )
    {
        auto pfnGetConfig = context.zetDdiTable.SysmanEvent.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hEvent, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventSetConfig
    ze_result_t __zecall
    zetSysmanEventSetConfig(
        zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        const zet_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
        )
    {
        auto pfnSetConfig = context.zetDdiTable.SysmanEvent.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hEvent, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventGetState
    ze_result_t __zecall
    zetSysmanEventGetState(
        zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device.
        ze_bool_t clear,                                ///< [in] Indicates if the event list for this device should be cleared.
        uint32_t* pEvents                               ///< [in] Bitfield of events ::zet_sysman_event_type_t that have been
                                                        ///< triggered by this device.
        )
    {
        auto pfnGetState = context.zetDdiTable.SysmanEvent.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEvent )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hEvent, clear, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventListen
    ze_result_t __zecall
    zetSysmanEventListen(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t timeout,                               ///< [in] How long to wait in milliseconds for events to arrive. Set to
                                                        ///< ::ZET_EVENT_WAIT_NONE will check status and return immediately. Set to
                                                        ///< ::ZET_EVENT_WAIT_INFINITE to block until events arrive.
        uint32_t count,                                 ///< [in] Number of handles in phEvents
        zet_sysman_event_handle_t* phEvents,            ///< [in][range(0, count)] Handle of events that should be listened to
        uint32_t* pEvents                               ///< [in] Bitfield of events ::zet_sysman_event_type_t that have been
                                                        ///< triggered by any of the supplied event handles. If timeout is not
                                                        ///< ::ZET_EVENT_WAIT_INFINITE and this value is
                                                        ///< ::ZET_SYSMAN_EVENT_TYPE_NONE, then a timeout has occurred.
        )
    {
        auto pfnListen = context.zetDdiTable.SysmanEvent.pfnListen;

        if( nullptr == pfnListen )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnListen( hDriver, timeout, count, phEvents, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGet
    ze_result_t __zecall
    zetSysmanDiagnosticsGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        zet_sysman_diag_handle_t* phDiagnostics         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type
        )
    {
        auto pfnDiagnosticsGet = context.zetDdiTable.Sysman.pfnDiagnosticsGet;

        if( nullptr == pfnDiagnosticsGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hSysman )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGetProperties
    ze_result_t __zecall
    zetSysmanDiagnosticsGetProperties(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        zet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        auto pfnGetProperties = context.zetDdiTable.SysmanDiagnostics.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hDiagnostics, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGetTests
    ze_result_t __zecall
    zetSysmanDiagnosticsGetTests(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of tests available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                        ///< If count is larger than the number of tests available, then the driver
                                                        ///< will update the value with the correct number of tests available.
        zet_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                        ///< increasing value of ::zet_diag_test_t.index
        )
    {
        auto pfnGetTests = context.zetDdiTable.SysmanDiagnostics.pfnGetTests;

        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTests( hDiagnostics, pCount, pTests );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsRunTests
    ze_result_t __zecall
    zetSysmanDiagnosticsRunTests(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZET_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZET_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zet_diag_result_t* pResult                      ///< [in] The result of the diagnostics
        )
    {
        auto pfnRunTests = context.zetDdiTable.SysmanDiagnostics.pfnRunTests;

        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pResult )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRunTests( hDiagnostics, start, end, pResult );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerCreate
    ze_result_t __zecall
    zetTracerCreate(
        zet_driver_handle_t hDriver,                    ///< [in] handle of the driver
        const zet_tracer_desc_t* desc,                  ///< [in] pointer to tracer descriptor
        zet_tracer_handle_t* phTracer                   ///< [out] pointer to handle of tracer object created
        )
    {
        auto pfnCreate = context.zetDdiTable.Tracer.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == desc )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == desc->pUserData )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == phTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZET_TRACER_DESC_VERSION_CURRENT < desc->version )
                return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        }

        return pfnCreate( hDriver, desc, phTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerDestroy
    ze_result_t __zecall
    zetTracerDestroy(
        zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
        )
    {
        auto pfnDestroy = context.zetDdiTable.Tracer.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnDestroy( hTracer );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetPrologues
    ze_result_t __zecall
    zetTracerSetPrologues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto pfnSetPrologues = context.zetDdiTable.Tracer.pfnSetPrologues;

        if( nullptr == pfnSetPrologues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCoreCbs )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetPrologues( hTracer, pCoreCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEpilogues
    ze_result_t __zecall
    zetTracerSetEpilogues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto pfnSetEpilogues = context.zetDdiTable.Tracer.pfnSetEpilogues;

        if( nullptr == pfnSetEpilogues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCoreCbs )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetEpilogues( hTracer, pCoreCbs );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEnabled
    ze_result_t __zecall
    zetTracerSetEnabled(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        auto pfnSetEnabled = context.zetDdiTable.Tracer.pfnSetEnabled;

        if( nullptr == pfnSetEnabled )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTracer )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetEnabled( hTracer, enable );
    }

} // namespace layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = layer::zetInit;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnActivateMetricGroups                     = pDdiTable->pfnActivateMetricGroups;
    pDdiTable->pfnActivateMetricGroups                   = layer::zetDeviceActivateMetricGroups;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAppendMetricTracerMarker                 = pDdiTable->pfnAppendMetricTracerMarker;
    pDdiTable->pfnAppendMetricTracerMarker               = layer::zetCommandListAppendMetricTracerMarker;

    dditable.pfnAppendMetricQueryBegin                   = pDdiTable->pfnAppendMetricQueryBegin;
    pDdiTable->pfnAppendMetricQueryBegin                 = layer::zetCommandListAppendMetricQueryBegin;

    dditable.pfnAppendMetricQueryEnd                     = pDdiTable->pfnAppendMetricQueryEnd;
    pDdiTable->pfnAppendMetricQueryEnd                   = layer::zetCommandListAppendMetricQueryEnd;

    dditable.pfnAppendMetricMemoryBarrier                = pDdiTable->pfnAppendMetricMemoryBarrier;
    pDdiTable->pfnAppendMetricMemoryBarrier              = layer::zetCommandListAppendMetricMemoryBarrier;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetDebugInfo                             = pDdiTable->pfnGetDebugInfo;
    pDdiTable->pfnGetDebugInfo                           = layer::zetModuleGetDebugInfo;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProfileInfo                           = pDdiTable->pfnGetProfileInfo;
    pDdiTable->pfnGetProfileInfo                         = layer::zetKernelGetProfileInfo;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricGroup;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zetMetricGroupGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetMetricGroupGetProperties;

    dditable.pfnCalculateMetricValues                    = pDdiTable->pfnCalculateMetricValues;
    pDdiTable->pfnCalculateMetricValues                  = layer::zetMetricGroupCalculateMetricValues;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Metric;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zetMetricGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetMetricGetProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricTracer;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnOpen                                     = pDdiTable->pfnOpen;
    pDdiTable->pfnOpen                                   = layer::zetMetricTracerOpen;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = layer::zetMetricTracerClose;

    dditable.pfnReadData                                 = pDdiTable->pfnReadData;
    pDdiTable->pfnReadData                               = layer::zetMetricTracerReadData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricQueryPool;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zetMetricQueryPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zetMetricQueryPoolDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.MetricQuery;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zetMetricQueryCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zetMetricQueryDestroy;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = layer::zetMetricQueryReset;

    dditable.pfnGetData                                  = pDdiTable->pfnGetData;
    pDdiTable->pfnGetData                                = layer::zetMetricQueryGetData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Tracer;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = layer::zetTracerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = layer::zetTracerDestroy;

    dditable.pfnSetPrologues                             = pDdiTable->pfnSetPrologues;
    pDdiTable->pfnSetPrologues                           = layer::zetTracerSetPrologues;

    dditable.pfnSetEpilogues                             = pDdiTable->pfnSetEpilogues;
    pDdiTable->pfnSetEpilogues                           = layer::zetTracerSetEpilogues;

    dditable.pfnSetEnabled                               = pDdiTable->pfnSetEnabled;
    pDdiTable->pfnSetEnabled                             = layer::zetTracerSetEnabled;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Sysman;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = layer::zetSysmanGet;

    dditable.pfnDeviceGetProperties                      = pDdiTable->pfnDeviceGetProperties;
    pDdiTable->pfnDeviceGetProperties                    = layer::zetSysmanDeviceGetProperties;

    dditable.pfnSchedulerGetSupportedModes               = pDdiTable->pfnSchedulerGetSupportedModes;
    pDdiTable->pfnSchedulerGetSupportedModes             = layer::zetSysmanSchedulerGetSupportedModes;

    dditable.pfnSchedulerGetCurrentMode                  = pDdiTable->pfnSchedulerGetCurrentMode;
    pDdiTable->pfnSchedulerGetCurrentMode                = layer::zetSysmanSchedulerGetCurrentMode;

    dditable.pfnSchedulerGetTimeoutModeProperties        = pDdiTable->pfnSchedulerGetTimeoutModeProperties;
    pDdiTable->pfnSchedulerGetTimeoutModeProperties      = layer::zetSysmanSchedulerGetTimeoutModeProperties;

    dditable.pfnSchedulerGetTimesliceModeProperties      = pDdiTable->pfnSchedulerGetTimesliceModeProperties;
    pDdiTable->pfnSchedulerGetTimesliceModeProperties    = layer::zetSysmanSchedulerGetTimesliceModeProperties;

    dditable.pfnSchedulerSetTimeoutMode                  = pDdiTable->pfnSchedulerSetTimeoutMode;
    pDdiTable->pfnSchedulerSetTimeoutMode                = layer::zetSysmanSchedulerSetTimeoutMode;

    dditable.pfnSchedulerSetTimesliceMode                = pDdiTable->pfnSchedulerSetTimesliceMode;
    pDdiTable->pfnSchedulerSetTimesliceMode              = layer::zetSysmanSchedulerSetTimesliceMode;

    dditable.pfnSchedulerSetExclusiveMode                = pDdiTable->pfnSchedulerSetExclusiveMode;
    pDdiTable->pfnSchedulerSetExclusiveMode              = layer::zetSysmanSchedulerSetExclusiveMode;

    dditable.pfnSchedulerSetComputeUnitDebugMode         = pDdiTable->pfnSchedulerSetComputeUnitDebugMode;
    pDdiTable->pfnSchedulerSetComputeUnitDebugMode       = layer::zetSysmanSchedulerSetComputeUnitDebugMode;

    dditable.pfnPerformanceProfileGetSupported           = pDdiTable->pfnPerformanceProfileGetSupported;
    pDdiTable->pfnPerformanceProfileGetSupported         = layer::zetSysmanPerformanceProfileGetSupported;

    dditable.pfnPerformanceProfileGet                    = pDdiTable->pfnPerformanceProfileGet;
    pDdiTable->pfnPerformanceProfileGet                  = layer::zetSysmanPerformanceProfileGet;

    dditable.pfnPerformanceProfileSet                    = pDdiTable->pfnPerformanceProfileSet;
    pDdiTable->pfnPerformanceProfileSet                  = layer::zetSysmanPerformanceProfileSet;

    dditable.pfnProcessesGetState                        = pDdiTable->pfnProcessesGetState;
    pDdiTable->pfnProcessesGetState                      = layer::zetSysmanProcessesGetState;

    dditable.pfnDeviceReset                              = pDdiTable->pfnDeviceReset;
    pDdiTable->pfnDeviceReset                            = layer::zetSysmanDeviceReset;

    dditable.pfnDeviceGetRepairStatus                    = pDdiTable->pfnDeviceGetRepairStatus;
    pDdiTable->pfnDeviceGetRepairStatus                  = layer::zetSysmanDeviceGetRepairStatus;

    dditable.pfnPciGetProperties                         = pDdiTable->pfnPciGetProperties;
    pDdiTable->pfnPciGetProperties                       = layer::zetSysmanPciGetProperties;

    dditable.pfnPciGetState                              = pDdiTable->pfnPciGetState;
    pDdiTable->pfnPciGetState                            = layer::zetSysmanPciGetState;

    dditable.pfnPciGetBars                               = pDdiTable->pfnPciGetBars;
    pDdiTable->pfnPciGetBars                             = layer::zetSysmanPciGetBars;

    dditable.pfnPciGetStats                              = pDdiTable->pfnPciGetStats;
    pDdiTable->pfnPciGetStats                            = layer::zetSysmanPciGetStats;

    dditable.pfnPowerGet                                 = pDdiTable->pfnPowerGet;
    pDdiTable->pfnPowerGet                               = layer::zetSysmanPowerGet;

    dditable.pfnFrequencyGet                             = pDdiTable->pfnFrequencyGet;
    pDdiTable->pfnFrequencyGet                           = layer::zetSysmanFrequencyGet;

    dditable.pfnEngineGet                                = pDdiTable->pfnEngineGet;
    pDdiTable->pfnEngineGet                              = layer::zetSysmanEngineGet;

    dditable.pfnStandbyGet                               = pDdiTable->pfnStandbyGet;
    pDdiTable->pfnStandbyGet                             = layer::zetSysmanStandbyGet;

    dditable.pfnFirmwareGet                              = pDdiTable->pfnFirmwareGet;
    pDdiTable->pfnFirmwareGet                            = layer::zetSysmanFirmwareGet;

    dditable.pfnMemoryGet                                = pDdiTable->pfnMemoryGet;
    pDdiTable->pfnMemoryGet                              = layer::zetSysmanMemoryGet;

    dditable.pfnFabricPortGet                            = pDdiTable->pfnFabricPortGet;
    pDdiTable->pfnFabricPortGet                          = layer::zetSysmanFabricPortGet;

    dditable.pfnTemperatureGet                           = pDdiTable->pfnTemperatureGet;
    pDdiTable->pfnTemperatureGet                         = layer::zetSysmanTemperatureGet;

    dditable.pfnPsuGet                                   = pDdiTable->pfnPsuGet;
    pDdiTable->pfnPsuGet                                 = layer::zetSysmanPsuGet;

    dditable.pfnFanGet                                   = pDdiTable->pfnFanGet;
    pDdiTable->pfnFanGet                                 = layer::zetSysmanFanGet;

    dditable.pfnLedGet                                   = pDdiTable->pfnLedGet;
    pDdiTable->pfnLedGet                                 = layer::zetSysmanLedGet;

    dditable.pfnRasGet                                   = pDdiTable->pfnRasGet;
    pDdiTable->pfnRasGet                                 = layer::zetSysmanRasGet;

    dditable.pfnEventGet                                 = pDdiTable->pfnEventGet;
    pDdiTable->pfnEventGet                               = layer::zetSysmanEventGet;

    dditable.pfnDiagnosticsGet                           = pDdiTable->pfnDiagnosticsGet;
    pDdiTable->pfnDiagnosticsGet                         = layer::zetSysmanDiagnosticsGet;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanPower;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanPowerGetProperties;

    dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
    pDdiTable->pfnGetEnergyCounter                       = layer::zetSysmanPowerGetEnergyCounter;

    dditable.pfnGetLimits                                = pDdiTable->pfnGetLimits;
    pDdiTable->pfnGetLimits                              = layer::zetSysmanPowerGetLimits;

    dditable.pfnSetLimits                                = pDdiTable->pfnSetLimits;
    pDdiTable->pfnSetLimits                              = layer::zetSysmanPowerSetLimits;

    dditable.pfnGetEnergyThreshold                       = pDdiTable->pfnGetEnergyThreshold;
    pDdiTable->pfnGetEnergyThreshold                     = layer::zetSysmanPowerGetEnergyThreshold;

    dditable.pfnSetEnergyThreshold                       = pDdiTable->pfnSetEnergyThreshold;
    pDdiTable->pfnSetEnergyThreshold                     = layer::zetSysmanPowerSetEnergyThreshold;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanFrequency;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanFrequencyGetProperties;

    dditable.pfnGetAvailableClocks                       = pDdiTable->pfnGetAvailableClocks;
    pDdiTable->pfnGetAvailableClocks                     = layer::zetSysmanFrequencyGetAvailableClocks;

    dditable.pfnGetRange                                 = pDdiTable->pfnGetRange;
    pDdiTable->pfnGetRange                               = layer::zetSysmanFrequencyGetRange;

    dditable.pfnSetRange                                 = pDdiTable->pfnSetRange;
    pDdiTable->pfnSetRange                               = layer::zetSysmanFrequencySetRange;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanFrequencyGetState;

    dditable.pfnGetThrottleTime                          = pDdiTable->pfnGetThrottleTime;
    pDdiTable->pfnGetThrottleTime                        = layer::zetSysmanFrequencyGetThrottleTime;

    dditable.pfnOcGetCapabilities                        = pDdiTable->pfnOcGetCapabilities;
    pDdiTable->pfnOcGetCapabilities                      = layer::zetSysmanFrequencyOcGetCapabilities;

    dditable.pfnOcGetConfig                              = pDdiTable->pfnOcGetConfig;
    pDdiTable->pfnOcGetConfig                            = layer::zetSysmanFrequencyOcGetConfig;

    dditable.pfnOcSetConfig                              = pDdiTable->pfnOcSetConfig;
    pDdiTable->pfnOcSetConfig                            = layer::zetSysmanFrequencyOcSetConfig;

    dditable.pfnOcGetIccMax                              = pDdiTable->pfnOcGetIccMax;
    pDdiTable->pfnOcGetIccMax                            = layer::zetSysmanFrequencyOcGetIccMax;

    dditable.pfnOcSetIccMax                              = pDdiTable->pfnOcSetIccMax;
    pDdiTable->pfnOcSetIccMax                            = layer::zetSysmanFrequencyOcSetIccMax;

    dditable.pfnOcGetTjMax                               = pDdiTable->pfnOcGetTjMax;
    pDdiTable->pfnOcGetTjMax                             = layer::zetSysmanFrequencyOcGetTjMax;

    dditable.pfnOcSetTjMax                               = pDdiTable->pfnOcSetTjMax;
    pDdiTable->pfnOcSetTjMax                             = layer::zetSysmanFrequencyOcSetTjMax;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanEngine;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanEngineGetProperties;

    dditable.pfnGetActivity                              = pDdiTable->pfnGetActivity;
    pDdiTable->pfnGetActivity                            = layer::zetSysmanEngineGetActivity;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanStandby;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanStandbyGetProperties;

    dditable.pfnGetMode                                  = pDdiTable->pfnGetMode;
    pDdiTable->pfnGetMode                                = layer::zetSysmanStandbyGetMode;

    dditable.pfnSetMode                                  = pDdiTable->pfnSetMode;
    pDdiTable->pfnSetMode                                = layer::zetSysmanStandbySetMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanFirmware;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanFirmwareGetProperties;

    dditable.pfnGetChecksum                              = pDdiTable->pfnGetChecksum;
    pDdiTable->pfnGetChecksum                            = layer::zetSysmanFirmwareGetChecksum;

    dditable.pfnFlash                                    = pDdiTable->pfnFlash;
    pDdiTable->pfnFlash                                  = layer::zetSysmanFirmwareFlash;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanMemory;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanMemoryGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanMemoryGetState;

    dditable.pfnGetBandwidth                             = pDdiTable->pfnGetBandwidth;
    pDdiTable->pfnGetBandwidth                           = layer::zetSysmanMemoryGetBandwidth;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fabric_port_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanFabricPort;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanFabricPortGetProperties;

    dditable.pfnGetLinkType                              = pDdiTable->pfnGetLinkType;
    pDdiTable->pfnGetLinkType                            = layer::zetSysmanFabricPortGetLinkType;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zetSysmanFabricPortGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zetSysmanFabricPortSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanFabricPortGetState;

    dditable.pfnGetThroughput                            = pDdiTable->pfnGetThroughput;
    pDdiTable->pfnGetThroughput                          = layer::zetSysmanFabricPortGetThroughput;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanTemperature;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanTemperatureGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zetSysmanTemperatureGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zetSysmanTemperatureSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanTemperatureGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanPsu;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanPsuGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanPsuGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanFan;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanFanGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zetSysmanFanGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zetSysmanFanSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanFanGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanLed;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanLedGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanLedGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = layer::zetSysmanLedSetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanRas;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanRasGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zetSysmanRasGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zetSysmanRasSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanRasGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanDiagnostics;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = layer::zetSysmanDiagnosticsGetProperties;

    dditable.pfnGetTests                                 = pDdiTable->pfnGetTests;
    pDdiTable->pfnGetTests                               = layer::zetSysmanDiagnosticsGetTests;

    dditable.pfnRunTests                                 = pDdiTable->pfnRunTests;
    pDdiTable->pfnRunTests                               = layer::zetSysmanDiagnosticsRunTests;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEvent table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_event_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.SysmanEvent;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = layer::zetSysmanEventGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = layer::zetSysmanEventSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = layer::zetSysmanEventGetState;

    dditable.pfnListen                                   = pDdiTable->pfnListen;
    pDdiTable->pfnListen                                 = layer::zetSysmanEventListen;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Debug table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = layer::context.zetDdiTable.Debug;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( layer::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAttach                                   = pDdiTable->pfnAttach;
    pDdiTable->pfnAttach                                 = layer::zetDebugAttach;

    dditable.pfnDetach                                   = pDdiTable->pfnDetach;
    pDdiTable->pfnDetach                                 = layer::zetDebugDetach;

    dditable.pfnGetNumThreads                            = pDdiTable->pfnGetNumThreads;
    pDdiTable->pfnGetNumThreads                          = layer::zetDebugGetNumThreads;

    dditable.pfnReadEvent                                = pDdiTable->pfnReadEvent;
    pDdiTable->pfnReadEvent                              = layer::zetDebugReadEvent;

    dditable.pfnInterrupt                                = pDdiTable->pfnInterrupt;
    pDdiTable->pfnInterrupt                              = layer::zetDebugInterrupt;

    dditable.pfnResume                                   = pDdiTable->pfnResume;
    pDdiTable->pfnResume                                 = layer::zetDebugResume;

    dditable.pfnReadMemory                               = pDdiTable->pfnReadMemory;
    pDdiTable->pfnReadMemory                             = layer::zetDebugReadMemory;

    dditable.pfnWriteMemory                              = pDdiTable->pfnWriteMemory;
    pDdiTable->pfnWriteMemory                            = layer::zetDebugWriteMemory;

    dditable.pfnReadState                                = pDdiTable->pfnReadState;
    pDdiTable->pfnReadState                              = layer::zetDebugReadState;

    dditable.pfnWriteState                               = pDdiTable->pfnWriteState;
    pDdiTable->pfnWriteState                             = layer::zetDebugWriteState;

    return result;
}

#if defined(__cplusplus)
};
#endif
