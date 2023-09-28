/*
 * ***THIS FILE IS GENERATED. ***
 * See handle_lifetime.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_handle_lifetime.cpp
 *
 */
#include "ze_validation_layer.h"
#include "ze_handle_lifetime.h"

namespace validation_layer
{
    ze_result_t
    ZETHandleLifetimeValidation::zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hModule )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDeviceGetDebugProperties(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        zet_device_debug_properties_t* pDebugProperties ///< [in,out] query result for debug properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugAttach(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* phDebug             ///< [out] debug session handle
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugReadEvent(
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
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugAcknowledgeEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        const zet_debug_event_t* event                  ///< [in] a pointer to a ::zet_debug_event_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to interrupt
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to resume
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugReadMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugWriteMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugGetRegisterSetProperties(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugGetThreadRegisterSetProperties(
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
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugReadRegisters(
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
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetDebugWriteRegisters(
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
        
        if ( !context.handleLifetime->isHandleValid( hDebug )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGroupGet(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGroupCalculateMetricValues(
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
        
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGet(
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
        
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMetric )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetContextActivateMetricGroups(
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
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phMetricGroups) && (i < count); ++i){
            if (!context.handleLifetime->isHandleValid( phMetricGroups[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricStreamerOpen(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_streamer_desc_t* desc,               ///< [in,out] metric streamer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification
        zet_metric_streamer_handle_t* phMetricStreamer  ///< [out] handle of metric streamer
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hNotificationEvent && !context.handleLifetime->isHandleValid( hNotificationEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetCommandListAppendMetricStreamerMarker(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
        uint32_t value                                  ///< [in] streamer marker value
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hMetricStreamer )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricStreamerClose(
        zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMetricStreamer )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricStreamerReadData(
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
        
        if ( !context.handleLifetime->isHandleValid( hMetricStreamer )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricQueryPoolCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    { 
        
        if (hMetricQueryPool && context.handleLifetime->isHandleValid( hMetricQueryPool )){
            if (context.handleLifetime->hasDependents( hMetricQueryPool )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hMetricQueryPool);
            context.handleLifetime->removeHandle( hMetricQueryPool );
        } else if (!context.handleLifetime->isHandleValid( hMetricQueryPool )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMetricQueryPool )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    { 
        
        if (hMetricQuery && context.handleLifetime->isHandleValid( hMetricQuery )){
            if (context.handleLifetime->hasDependents( hMetricQuery )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hMetricQuery);
            context.handleLifetime->removeHandle( hMetricQuery );
        } else if (!context.handleLifetime->isHandleValid( hMetricQuery )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMetricQuery )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hMetricQuery )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in] must be zero
        ze_event_handle_t* phWaitEvents                 ///< [in][mbz] must be nullptr
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        if ( !context.handleLifetime->isHandleValid( hMetricQuery )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (hSignalEvent && !context.handleLifetime->isHandleValid( hSignalEvent )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hCommandList )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (!context.handleLifetime->isOpen( hCommandList )){
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricQueryGetData(
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
        
        if ( !context.handleLifetime->isHandleValid( hMetricQuery )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_properties_t* pProfileProperties    ///< [out] pointer to profile properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hKernel )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetTracerExpCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        const zet_tracer_exp_desc_t* desc,              ///< [in] pointer to tracer descriptor
        zet_tracer_exp_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hContext )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetTracerExpDestroy(
        zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
        )
    { 
        
        if (hTracer && context.handleLifetime->isHandleValid( hTracer )){
            if (context.handleLifetime->hasDependents( hTracer )){
                return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
            }
            context.handleLifetime->removeDependent( hTracer);
            context.handleLifetime->removeHandle( hTracer );
        } else if (!context.handleLifetime->isHandleValid( hTracer )) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetTracerExpSetPrologues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hTracer )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetTracerExpSetEpilogues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hTracer )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetTracerExpSetEnabled(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hTracer )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGroupCalculateMultipleMetricValuesExp(
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
        
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGroupGetGlobalTimestampsExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        ze_bool_t synchronizedWithHost,                 ///< [in] Returns the timestamps synchronized to the host or the device.
        uint64_t* globalTimestamp,                      ///< [out] Device timestamp.
        uint64_t* metricTimestamp                       ///< [out] Metric timestamp.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGroupGetExportDataExp(
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
        
        if ( !context.handleLifetime->isHandleValid( hMetricGroup )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZETHandleLifetimeValidation::zetMetricGroupCalculateMetricExportDataExp(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
}