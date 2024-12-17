/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_nullddi.cpp
 *
 */
#include "ze_null.h"
#include <cstring>

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetModuleGetDebugInfo
    __zedlllocal ze_result_t ZE_APICALL
    zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDebugInfo = context.zetDdiTable.Module.pfnGetDebugInfo;
        if( nullptr != pfnGetDebugInfo )
        {
            result = pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceGetDebugProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceGetDebugProperties(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        zet_device_debug_properties_t* pDebugProperties ///< [in,out] query result for debug properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDebugProperties = context.zetDdiTable.Device.pfnGetDebugProperties;
        if( nullptr != pfnGetDebugProperties )
        {
            result = pfnGetDebugProperties( hDevice, pDebugProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugAttach
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugAttach(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* phDebug             ///< [out] debug session handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAttach = context.zetDdiTable.Debug.pfnAttach;
        if( nullptr != pfnAttach )
        {
            result = pfnAttach( hDevice, config, phDebug );
        }
        else
        {
            // generic implementation
            *phDebug = reinterpret_cast<zet_debug_session_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugDetach
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDetach = context.zetDdiTable.Debug.pfnDetach;
        if( nullptr != pfnDetach )
        {
            result = pfnDetach( hDebug );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadEvent
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadEvent = context.zetDdiTable.Debug.pfnReadEvent;
        if( nullptr != pfnReadEvent )
        {
            result = pfnReadEvent( hDebug, timeout, event );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugAcknowledgeEvent
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugAcknowledgeEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        const zet_debug_event_t* event                  ///< [in] a pointer to a ::zet_debug_event_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAcknowledgeEvent = context.zetDdiTable.Debug.pfnAcknowledgeEvent;
        if( nullptr != pfnAcknowledgeEvent )
        {
            result = pfnAcknowledgeEvent( hDebug, event );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugInterrupt
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to interrupt
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInterrupt = context.zetDdiTable.Debug.pfnInterrupt;
        if( nullptr != pfnInterrupt )
        {
            result = pfnInterrupt( hDebug, thread );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugResume
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to resume
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnResume = context.zetDdiTable.Debug.pfnResume;
        if( nullptr != pfnResume )
        {
            result = pfnResume( hDebug, thread );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadMemory
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugReadMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadMemory = context.zetDdiTable.Debug.pfnReadMemory;
        if( nullptr != pfnReadMemory )
        {
            result = pfnReadMemory( hDebug, thread, desc, size, buffer );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteMemory
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugWriteMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnWriteMemory = context.zetDdiTable.Debug.pfnWriteMemory;
        if( nullptr != pfnWriteMemory )
        {
            result = pfnWriteMemory( hDebug, thread, desc, size, buffer );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetRegisterSetProperties
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetRegisterSetProperties = context.zetDdiTable.Debug.pfnGetRegisterSetProperties;
        if( nullptr != pfnGetRegisterSetProperties )
        {
            result = pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetThreadRegisterSetProperties
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetThreadRegisterSetProperties = context.zetDdiTable.Debug.pfnGetThreadRegisterSetProperties;
        if( nullptr != pfnGetThreadRegisterSetProperties )
        {
            result = pfnGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadRegisters
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadRegisters = context.zetDdiTable.Debug.pfnReadRegisters;
        if( nullptr != pfnReadRegisters )
        {
            result = pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteRegisters
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnWriteRegisters = context.zetDdiTable.Debug.pfnWriteRegisters;
        if( nullptr != pfnWriteRegisters )
        {
            result = pfnWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGet
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zetDdiTable.MetricGroup.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDevice, pCount, phMetricGroups );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < *pCount ); ++i )
                phMetricGroups[ i ] = reinterpret_cast<zet_metric_group_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.MetricGroup.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hMetricGroup, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMetricValues
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCalculateMetricValues = context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;
        if( nullptr != pfnCalculateMetricValues )
        {
            result = pfnCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGet
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zetDdiTable.Metric.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hMetricGroup, pCount, phMetrics );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetrics ) && ( i < *pCount ); ++i )
                phMetrics[ i ] = reinterpret_cast<zet_metric_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zetDdiTable.Metric.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hMetric, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetContextActivateMetricGroups
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnActivateMetricGroups = context.zetDdiTable.Context.pfnActivateMetricGroups;
        if( nullptr != pfnActivateMetricGroups )
        {
            result = pfnActivateMetricGroups( hContext, hDevice, count, phMetricGroups );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricStreamerOpen
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerOpen(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_streamer_desc_t* desc,               ///< [in,out] metric streamer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification
        zet_metric_streamer_handle_t* phMetricStreamer  ///< [out] handle of metric streamer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOpen = context.zetDdiTable.MetricStreamer.pfnOpen;
        if( nullptr != pfnOpen )
        {
            result = pfnOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
        }
        else
        {
            // generic implementation
            *phMetricStreamer = reinterpret_cast<zet_metric_streamer_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricStreamerMarker
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricStreamerMarker(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
        uint32_t value                                  ///< [in] streamer marker value
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricStreamerMarker = context.zetDdiTable.CommandList.pfnAppendMetricStreamerMarker;
        if( nullptr != pfnAppendMetricStreamerMarker )
        {
            result = pfnAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricStreamerClose
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerClose(
        zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClose = context.zetDdiTable.MetricStreamer.pfnClose;
        if( nullptr != pfnClose )
        {
            result = pfnClose( hMetricStreamer );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricStreamerReadData
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadData = context.zetDdiTable.MetricStreamer.pfnReadData;
        if( nullptr != pfnReadData )
        {
            result = pfnReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolCreate
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryPoolCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zetDdiTable.MetricQueryPool.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
        }
        else
        {
            // generic implementation
            *phMetricQueryPool = reinterpret_cast<zet_metric_query_pool_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zetDdiTable.MetricQueryPool.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hMetricQueryPool );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryCreate
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zetDdiTable.MetricQuery.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hMetricQueryPool, index, phMetricQuery );
        }
        else
        {
            // generic implementation
            *phMetricQuery = reinterpret_cast<zet_metric_query_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zetDdiTable.MetricQuery.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hMetricQuery );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryReset
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zetDdiTable.MetricQuery.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hMetricQuery );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricQueryBegin = context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;
        if( nullptr != pfnAppendMetricQueryBegin )
        {
            result = pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryEnd
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in] must be zero
        ze_event_handle_t* phWaitEvents                 ///< [in][mbz] must be nullptr
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricQueryEnd = context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;
        if( nullptr != pfnAppendMetricQueryEnd )
        {
            result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAppendMetricMemoryBarrier = context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;
        if( nullptr != pfnAppendMetricMemoryBarrier )
        {
            result = pfnAppendMetricMemoryBarrier( hCommandList );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryGetData
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetData = context.zetDdiTable.MetricQuery.pfnGetData;
        if( nullptr != pfnGetData )
        {
            result = pfnGetData( hMetricQuery, pRawDataSize, pRawData );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetKernelGetProfileInfo
    __zedlllocal ze_result_t ZE_APICALL
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_properties_t* pProfileProperties    ///< [out] pointer to profile properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProfileInfo = context.zetDdiTable.Kernel.pfnGetProfileInfo;
        if( nullptr != pfnGetProfileInfo )
        {
            result = pfnGetProfileInfo( hKernel, pProfileProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpCreate
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        const zet_tracer_exp_desc_t* desc,              ///< [in] pointer to tracer descriptor
        zet_tracer_exp_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreate = context.zetDdiTable.TracerExp.pfnCreate;
        if( nullptr != pfnCreate )
        {
            result = pfnCreate( hContext, desc, phTracer );
        }
        else
        {
            // generic implementation
            *phTracer = reinterpret_cast<zet_tracer_exp_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpDestroy(
        zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroy = context.zetDdiTable.TracerExp.pfnDestroy;
        if( nullptr != pfnDestroy )
        {
            result = pfnDestroy( hTracer );
        }
        else
        {
            // generic implementation

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetPrologues
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetPrologues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetPrologues = context.zetDdiTable.TracerExp.pfnSetPrologues;
        if( nullptr != pfnSetPrologues )
        {
            result = pfnSetPrologues( hTracer, pCoreCbs );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetEpilogues
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEpilogues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEpilogues = context.zetDdiTable.TracerExp.pfnSetEpilogues;
        if( nullptr != pfnSetEpilogues )
        {
            result = pfnSetEpilogues( hTracer, pCoreCbs );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetEnabled
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEnabled(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEnabled = context.zetDdiTable.TracerExp.pfnSetEnabled;
        if( nullptr != pfnSetEnabled )
        {
            result = pfnSetEnabled( hTracer, enable );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceGetConcurrentMetricGroupsExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConcurrentMetricGroupsExp = context.zetDdiTable.DeviceExp.pfnGetConcurrentMetricGroupsExp;
        if( nullptr != pfnGetConcurrentMetricGroupsExp )
        {
            result = pfnGetConcurrentMetricGroupsExp( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerCreateExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateExp = context.zetDdiTable.MetricTracerExp.pfnCreateExp;
        if( nullptr != pfnCreateExp )
        {
            result = pfnCreateExp( hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer );
        }
        else
        {
            // generic implementation
            *phMetricTracer = reinterpret_cast<zet_metric_tracer_exp_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerDestroyExp(
        zet_metric_tracer_exp_handle_t hMetricTracer    ///< [in] handle of the metric tracer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroyExp = context.zetDdiTable.MetricTracerExp.pfnDestroyExp;
        if( nullptr != pfnDestroyExp )
        {
            result = pfnDestroyExp( hMetricTracer );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerEnableExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerEnableExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                        ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                        ///< and checking the return status: ::ZE_RESULT_NOT_READY will be returned
                                                        ///< when the tracer is inactive. ::ZE_RESULT_SUCCESS will be returned 
                                                        ///< when the tracer is active.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnableExp = context.zetDdiTable.MetricTracerExp.pfnEnableExp;
        if( nullptr != pfnEnableExp )
        {
            result = pfnEnableExp( hMetricTracer, synchronous );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerDisableExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDisableExp = context.zetDdiTable.MetricTracerExp.pfnDisableExp;
        if( nullptr != pfnDisableExp )
        {
            result = pfnDisableExp( hMetricTracer, synchronous );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerReadDataExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadDataExp = context.zetDdiTable.MetricTracerExp.pfnReadDataExp;
        if( nullptr != pfnReadDataExp )
        {
            result = pfnReadDataExp( hMetricTracer, pRawDataSize, pRawData );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDecoderCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderCreateExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        zet_metric_decoder_exp_handle_t* phMetricDecoder///< [out] handle of the metric decoder object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateExp = context.zetDdiTable.MetricDecoderExp.pfnCreateExp;
        if( nullptr != pfnCreateExp )
        {
            result = pfnCreateExp( hMetricTracer, phMetricDecoder );
        }
        else
        {
            // generic implementation
            *phMetricDecoder = reinterpret_cast<zet_metric_decoder_exp_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDecoderDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderDestroyExp(
        zet_metric_decoder_exp_handle_t phMetricDecoder ///< [in] handle of the metric decoder object
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroyExp = context.zetDdiTable.MetricDecoderExp.pfnDestroyExp;
        if( nullptr != pfnDestroyExp )
        {
            result = pfnDestroyExp( phMetricDecoder );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDecoderGetDecodableMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDecodableMetricsExp = context.zetDdiTable.MetricDecoderExp.pfnGetDecodableMetricsExp;
        if( nullptr != pfnGetDecodableMetricsExp )
        {
            result = pfnGetDecodableMetricsExp( hMetricDecoder, pCount, phMetrics );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetrics ) && ( i < *pCount ); ++i )
                phMetrics[ i ] = reinterpret_cast<zet_metric_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerDecodeExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDecodeExp = context.zetDdiTable.MetricTracerExp.pfnDecodeExp;
        if( nullptr != pfnDecodeExp )
        {
            result = pfnDecodeExp( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMultipleMetricValuesExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCalculateMultipleMetricValuesExp = context.zetDdiTable.MetricGroupExp.pfnCalculateMultipleMetricValuesExp;
        if( nullptr != pfnCalculateMultipleMetricValuesExp )
        {
            result = pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetGlobalTimestampsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetGlobalTimestampsExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        ze_bool_t synchronizedWithHost,                 ///< [in] Returns the timestamps synchronized to the host or the device.
        uint64_t* globalTimestamp,                      ///< [out] Device timestamp.
        uint64_t* metricTimestamp                       ///< [out] Metric timestamp.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetGlobalTimestampsExp = context.zetDdiTable.MetricGroupExp.pfnGetGlobalTimestampsExp;
        if( nullptr != pfnGetGlobalTimestampsExp )
        {
            result = pfnGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetExportDataExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetExportDataExp = context.zetDdiTable.MetricGroupExp.pfnGetExportDataExp;
        if( nullptr != pfnGetExportDataExp )
        {
            result = pfnGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMetricExportDataExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCalculateMetricExportDataExp = context.zetDdiTable.MetricGroupExp.pfnCalculateMetricExportDataExp;
        if( nullptr != pfnCalculateMetricExportDataExp )
        {
            result = pfnCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetExp = context.zetDdiTable.MetricProgrammableExp.pfnGetExp;
        if( nullptr != pfnGetExp )
        {
            result = pfnGetExp( hDevice, pCount, phMetricProgrammables );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetricProgrammables ) && ( i < *pCount ); ++i )
                phMetricProgrammables[ i ] = reinterpret_cast<zet_metric_programmable_exp_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetPropertiesExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        zet_metric_programmable_exp_properties_t* pProperties   ///< [in,out] properties of the metric programmable
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetPropertiesExp = context.zetDdiTable.MetricProgrammableExp.pfnGetPropertiesExp;
        if( nullptr != pfnGetPropertiesExp )
        {
            result = pfnGetPropertiesExp( hMetricProgrammable, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetParamInfoExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetParamInfoExp = context.zetDdiTable.MetricProgrammableExp.pfnGetParamInfoExp;
        if( nullptr != pfnGetParamInfoExp )
        {
            result = pfnGetParamInfoExp( hMetricProgrammable, pParameterCount, pParameterInfo );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetParamValueInfoExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetParamValueInfoExp = context.zetDdiTable.MetricProgrammableExp.pfnGetParamValueInfoExp;
        if( nullptr != pfnGetParamValueInfoExp )
        {
            result = pfnGetParamValueInfoExp( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricCreateFromProgrammableExp2
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateFromProgrammableExp2 = context.zetDdiTable.MetricExp.pfnCreateFromProgrammableExp2;
        if( nullptr != pfnCreateFromProgrammableExp2 )
        {
            result = pfnCreateFromProgrammableExp2( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetricHandles ) && ( i < *pMetricHandleCount ); ++i )
                phMetricHandles[ i ] = reinterpret_cast<zet_metric_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricCreateFromProgrammableExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateFromProgrammableExp = context.zetDdiTable.MetricExp.pfnCreateFromProgrammableExp;
        if( nullptr != pfnCreateFromProgrammableExp )
        {
            result = pfnCreateFromProgrammableExp( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetricHandles ) && ( i < *pMetricHandleCount ); ++i )
                phMetricHandles[ i ] = reinterpret_cast<zet_metric_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceCreateMetricGroupsFromMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateMetricGroupsFromMetricsExp = context.zetDdiTable.DeviceExp.pfnCreateMetricGroupsFromMetricsExp;
        if( nullptr != pfnCreateMetricGroupsFromMetricsExp )
        {
            result = pfnCreateMetricGroupsFromMetricsExp( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMetricGroup ) && ( i < *pMetricGroupCount ); ++i )
                phMetricGroup[ i ] = reinterpret_cast<zet_metric_group_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCreateExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCreateExp = context.zetDdiTable.MetricGroupExp.pfnCreateExp;
        if( nullptr != pfnCreateExp )
        {
            result = pfnCreateExp( hDevice, pName, pDescription, samplingType, phMetricGroup );
        }
        else
        {
            // generic implementation
            *phMetricGroup = reinterpret_cast<zet_metric_group_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupAddMetricExp
    __zedlllocal ze_result_t ZE_APICALL
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnAddMetricExp = context.zetDdiTable.MetricGroupExp.pfnAddMetricExp;
        if( nullptr != pfnAddMetricExp )
        {
            result = pfnAddMetricExp( hMetricGroup, hMetric, pErrorStringSize, pErrorString );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupRemoveMetricExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupRemoveMetricExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
        zet_metric_handle_t hMetric                     ///< [in] Metric handle to be removed from the metric group.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRemoveMetricExp = context.zetDdiTable.MetricGroupExp.pfnRemoveMetricExp;
        if( nullptr != pfnRemoveMetricExp )
        {
            result = pfnRemoveMetricExp( hMetricGroup, hMetric );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCloseExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCloseExp(
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnCloseExp = context.zetDdiTable.MetricGroupExp.pfnCloseExp;
        if( nullptr != pfnCloseExp )
        {
            result = pfnCloseExp( hMetricGroup );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupDestroyExp(
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroyExp = context.zetDdiTable.MetricGroupExp.pfnDestroyExp;
        if( nullptr != pfnDestroyExp )
        {
            result = pfnDestroyExp( hMetricGroup );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDestroyExp(
        zet_metric_handle_t hMetric                     ///< [in] Handle of the metric to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnDestroyExp = context.zetDdiTable.MetricExp.pfnDestroyExp;
        if( nullptr != pfnDestroyExp )
        {
            result = pfnDestroyExp( hMetric );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

} // namespace driver

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricDecoderExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricDecoderExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_decoder_exp_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreateExp                              = driver::zetMetricDecoderCreateExp;

    pDdiTable->pfnDestroyExp                             = driver::zetMetricDecoderDestroyExp;

    pDdiTable->pfnGetDecodableMetricsExp                 = driver::zetMetricDecoderGetDecodableMetricsExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricProgrammableExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricProgrammableExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_programmable_exp_dditable_t* pDdiTable   ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetExp                                 = driver::zetMetricProgrammableGetExp;

    pDdiTable->pfnGetPropertiesExp                       = driver::zetMetricProgrammableGetPropertiesExp;

    pDdiTable->pfnGetParamInfoExp                        = driver::zetMetricProgrammableGetParamInfoExp;

    pDdiTable->pfnGetParamValueInfoExp                   = driver::zetMetricProgrammableGetParamValueInfoExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracerExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricTracerExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_exp_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreateExp                              = driver::zetMetricTracerCreateExp;

    pDdiTable->pfnDestroyExp                             = driver::zetMetricTracerDestroyExp;

    pDdiTable->pfnEnableExp                              = driver::zetMetricTracerEnableExp;

    pDdiTable->pfnDisableExp                             = driver::zetMetricTracerDisableExp;

    pDdiTable->pfnReadDataExp                            = driver::zetMetricTracerReadDataExp;

    pDdiTable->pfnDecodeExp                              = driver::zetMetricTracerDecodeExp;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetDebugProperties                     = driver::zetDeviceGetDebugProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetConcurrentMetricGroupsExp           = driver::zetDeviceGetConcurrentMetricGroupsExp;

    pDdiTable->pfnCreateMetricGroupsFromMetricsExp       = driver::zetDeviceCreateMetricGroupsFromMetricsExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_context_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnActivateMetricGroups                   = driver::zetContextActivateMetricGroups;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnAppendMetricStreamerMarker             = driver::zetCommandListAppendMetricStreamerMarker;

    pDdiTable->pfnAppendMetricQueryBegin                 = driver::zetCommandListAppendMetricQueryBegin;

    pDdiTable->pfnAppendMetricQueryEnd                   = driver::zetCommandListAppendMetricQueryEnd;

    pDdiTable->pfnAppendMetricMemoryBarrier              = driver::zetCommandListAppendMetricMemoryBarrier;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProfileInfo                         = driver::zetKernelGetProfileInfo;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetDebugInfo                           = driver::zetModuleGetDebugInfo;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnAttach                                 = driver::zetDebugAttach;

    pDdiTable->pfnDetach                                 = driver::zetDebugDetach;

    pDdiTable->pfnReadEvent                              = driver::zetDebugReadEvent;

    pDdiTable->pfnAcknowledgeEvent                       = driver::zetDebugAcknowledgeEvent;

    pDdiTable->pfnInterrupt                              = driver::zetDebugInterrupt;

    pDdiTable->pfnResume                                 = driver::zetDebugResume;

    pDdiTable->pfnReadMemory                             = driver::zetDebugReadMemory;

    pDdiTable->pfnWriteMemory                            = driver::zetDebugWriteMemory;

    pDdiTable->pfnGetRegisterSetProperties               = driver::zetDebugGetRegisterSetProperties;

    pDdiTable->pfnReadRegisters                          = driver::zetDebugReadRegisters;

    pDdiTable->pfnWriteRegisters                         = driver::zetDebugWriteRegisters;

    pDdiTable->pfnGetThreadRegisterSetProperties         = driver::zetDebugGetThreadRegisterSetProperties;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::zetMetricGet;

    pDdiTable->pfnGetProperties                          = driver::zetMetricGetProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreateFromProgrammableExp2             = driver::zetMetricCreateFromProgrammableExp2;

    pDdiTable->pfnCreateFromProgrammableExp              = driver::zetMetricCreateFromProgrammableExp;

    pDdiTable->pfnDestroyExp                             = driver::zetMetricDestroyExp;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGet                                    = driver::zetMetricGroupGet;

    pDdiTable->pfnGetProperties                          = driver::zetMetricGroupGetProperties;

    pDdiTable->pfnCalculateMetricValues                  = driver::zetMetricGroupCalculateMetricValues;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroupExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCalculateMultipleMetricValuesExp       = driver::zetMetricGroupCalculateMultipleMetricValuesExp;

    pDdiTable->pfnGetGlobalTimestampsExp                 = driver::zetMetricGroupGetGlobalTimestampsExp;

    pDdiTable->pfnGetExportDataExp                       = driver::zetMetricGroupGetExportDataExp;

    pDdiTable->pfnCalculateMetricExportDataExp           = driver::zetMetricGroupCalculateMetricExportDataExp;

    pDdiTable->pfnCreateExp                              = driver::zetMetricGroupCreateExp;

    pDdiTable->pfnAddMetricExp                           = driver::zetMetricGroupAddMetricExp;

    pDdiTable->pfnRemoveMetricExp                        = driver::zetMetricGroupRemoveMetricExp;

    pDdiTable->pfnCloseExp                               = driver::zetMetricGroupCloseExp;

    pDdiTable->pfnDestroyExp                             = driver::zetMetricGroupDestroyExp;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::zetMetricQueryCreate;

    pDdiTable->pfnDestroy                                = driver::zetMetricQueryDestroy;

    pDdiTable->pfnReset                                  = driver::zetMetricQueryReset;

    pDdiTable->pfnGetData                                = driver::zetMetricQueryGetData;

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
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::zetMetricQueryPoolCreate;

    pDdiTable->pfnDestroy                                = driver::zetMetricQueryPoolDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricStreamer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricStreamerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_streamer_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnOpen                                   = driver::zetMetricStreamerOpen;

    pDdiTable->pfnClose                                  = driver::zetMetricStreamerClose;

    pDdiTable->pfnReadData                               = driver::zetMetricStreamerReadData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's TracerExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetTracerExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnCreate                                 = driver::zetTracerExpCreate;

    pDdiTable->pfnDestroy                                = driver::zetTracerExpDestroy;

    pDdiTable->pfnSetPrologues                           = driver::zetTracerExpSetPrologues;

    pDdiTable->pfnSetEpilogues                           = driver::zetTracerExpSetEpilogues;

    pDdiTable->pfnSetEnabled                             = driver::zetTracerExpSetEnabled;

    return result;
}

#if defined(__cplusplus)
};
#endif
