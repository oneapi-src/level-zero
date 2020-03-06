/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_metric.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for Metric
 *
 */
 
#ifndef _ZET_METRIC_H
#define _ZET_METRIC_H
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
__ze_api_export ze_result_t __zecall
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
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_GROUP_NAME
/// @brief Maximum metric group name string size
#define ZET_MAX_METRIC_GROUP_NAME  256
#endif // ZET_MAX_METRIC_GROUP_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_GROUP_DESCRIPTION
/// @brief Maximum metric group description string size
#define ZET_MAX_METRIC_GROUP_DESCRIPTION  256
#endif // ZET_MAX_METRIC_GROUP_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric group sampling type
typedef enum _zet_metric_group_sampling_type_t
{
    ZET_METRIC_GROUP_SAMPLING_TYPE_EVENT_BASED = ZE_BIT(0), ///< Event based sampling
    ZET_METRIC_GROUP_SAMPLING_TYPE_TIME_BASED = ZE_BIT(1),  ///< Time based sampling

} zet_metric_group_sampling_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_group_properties_t
typedef enum _zet_metric_group_properties_version_t
{
    ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ), ///< version 0.91

} zet_metric_group_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric group properties queried using ::zetMetricGroupGetProperties
typedef struct _zet_metric_group_properties_t
{
    zet_metric_group_properties_version_t version;  ///< [in] ::ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
    char name[ZET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
    char description[ZET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
    zet_metric_group_sampling_type_t samplingType;  ///< [out] metric group sampling type
    uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                    ///< groups from different domains.
    uint32_t maxCommandQueueOrdinal;                ///< [out] tracers and queries of this metric group cannot be submitted to
                                                    ///< a command queue with a larger ordinal value.
                                                    ///< See ::ze_command_queue_desc_t for more information on how to specify
                                                    ///< the command queue's ordinal.
    uint32_t metricCount;                           ///< [out] metric count belonging to this group

} zet_metric_group_properties_t;

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
__ze_api_export ze_result_t __zecall
zetMetricGroupGetProperties(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric types
typedef enum _zet_metric_type_t
{
    ZET_METRIC_TYPE_DURATION,                       ///< Metric type: duration
    ZET_METRIC_TYPE_EVENT,                          ///< Metric type: event
    ZET_METRIC_TYPE_EVENT_WITH_RANGE,               ///< Metric type: event with range
    ZET_METRIC_TYPE_THROUGHPUT,                     ///< Metric type: throughput
    ZET_METRIC_TYPE_TIMESTAMP,                      ///< Metric type: timestamp
    ZET_METRIC_TYPE_FLAG,                           ///< Metric type: flag
    ZET_METRIC_TYPE_RATIO,                          ///< Metric type: ratio
    ZET_METRIC_TYPE_RAW,                            ///< Metric type: raw

} zet_metric_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported value types
typedef enum _zet_value_type_t
{
    ZET_VALUE_TYPE_UINT32,                          ///< 32-bit unsigned-integer
    ZET_VALUE_TYPE_UINT64,                          ///< 64-bit unsigned-integer
    ZET_VALUE_TYPE_FLOAT32,                         ///< 32-bit floating-point
    ZET_VALUE_TYPE_FLOAT64,                         ///< 64-bit floating-point
    ZET_VALUE_TYPE_BOOL8,                           ///< 8-bit boolean

} zet_value_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Union of values
typedef union _zet_value_t
{
    uint32_t ui32;                                  ///< [out] 32-bit unsigned-integer
    uint64_t ui64;                                  ///< [out] 32-bit unsigned-integer
    float fp32;                                     ///< [out] 32-bit floating-point
    double fp64;                                    ///< [out] 64-bit floating-point
    ze_bool_t b8;                                   ///< [out] 8-bit boolean

} zet_value_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Typed value
typedef struct _zet_typed_value_t
{
    zet_value_type_t type;                          ///< [out] type of value
    zet_value_t value;                              ///< [out] value

} zet_typed_value_t;

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
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawData`
///         + `nullptr == pMetricValueCount`
__ze_api_export ze_result_t __zecall
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
    );

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
__ze_api_export ze_result_t __zecall
zetMetricGet(
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of metrics available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                    ///< if count is larger than the number of metrics available, then the
                                                    ///< driver will update the value with the correct number of metrics available.
    zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics
    );

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_NAME
/// @brief Maximum metric name string size
#define ZET_MAX_METRIC_NAME  256
#endif // ZET_MAX_METRIC_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_DESCRIPTION
/// @brief Maximum metric description string size
#define ZET_MAX_METRIC_DESCRIPTION  256
#endif // ZET_MAX_METRIC_DESCRIPTION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_COMPONENT
/// @brief Maximum metric component string size
#define ZET_MAX_METRIC_COMPONENT  256
#endif // ZET_MAX_METRIC_COMPONENT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZET_MAX_METRIC_RESULT_UNITS
/// @brief Maximum metric result units string size
#define ZET_MAX_METRIC_RESULT_UNITS  256
#endif // ZET_MAX_METRIC_RESULT_UNITS

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_properties_t
typedef enum _zet_metric_properties_version_t
{
    ZET_METRIC_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),   ///< version 0.91

} zet_metric_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric properties queried using ::zetMetricGetProperties
typedef struct _zet_metric_properties_t
{
    zet_metric_properties_version_t version;        ///< [in] ::ZET_METRIC_PROPERTIES_VERSION_CURRENT
    char name[ZET_MAX_METRIC_NAME];                 ///< [out] metric name
    char description[ZET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
    char component[ZET_MAX_METRIC_COMPONENT];       ///< [out] metric component
    uint32_t tierNumber;                            ///< [out] number of tier
    zet_metric_type_t metricType;                   ///< [out] metric type
    zet_value_type_t resultType;                    ///< [out] metric result type
    char resultUnits[ZET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

} zet_metric_properties_t;

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
__ze_api_export ze_result_t __zecall
zetMetricGetProperties(
    zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
    zet_metric_properties_t* pProperties            ///< [in,out] metric properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Activates metric groups.
/// 
/// @details
///     - MetricGroup must be active until MetricQueryGetDeta and
///       ::zetMetricTracerClose.
///     - Conflicting metric groups cannot be activated, in such case tha call
///       would fail.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
__ze_api_export ze_result_t __zecall
zetDeviceActivateMetricGroups(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    uint32_t count,                                 ///< [in] metric group count to activate. 0 to deactivate.
    zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to
                                                    ///< activate. NULL to deactivate.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_tracer_desc_t
typedef enum _zet_metric_tracer_desc_version_t
{
    ZET_METRIC_TRACER_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

} zet_metric_tracer_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric tracer descriptor
typedef struct _zet_metric_tracer_desc_t
{
    zet_metric_tracer_desc_version_t version;       ///< [in] ::ZET_METRIC_TRACER_DESC_VERSION_CURRENT
    uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                    ///< will be signalled
    uint32_t samplingPeriod;                        ///< [in,out] tracer sampling period in nanoseconds

} zet_metric_tracer_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Opens metric tracer for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phMetricTracer`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZET_METRIC_TRACER_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zetMetricTracerOpen(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
    zet_metric_tracer_desc_t* desc,                 ///< [in,out] metric tracer descriptor
    ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Must
                                                    ///< be device to host type.
    zet_metric_tracer_handle_t* phMetricTracer      ///< [out] handle of metric tracer
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Append metric tracer marker into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricTracer`
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricTracerMarker(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_tracer_handle_t hMetricTracer,       ///< [in] handle of the metric tracer
    uint32_t value                                  ///< [in] tracer marker value
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Closes metric tracer.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same metric tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
__ze_api_export ze_result_t __zecall
zetMetricTracerClose(
    zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from metric tracer.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pRawDataSize`
__ze_api_export ze_result_t __zecall
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
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_metric_query_pool_desc_t
typedef enum _zet_metric_query_pool_desc_version_t
{
    ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

} zet_metric_query_pool_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric query pool types
typedef enum _zet_metric_query_pool_flag_t
{
    ZET_METRIC_QUERY_POOL_FLAG_PERFORMANCE,         ///< Performance metric query pool.
    ZET_METRIC_QUERY_POOL_FLAG_SKIP_EXECUTION,      ///< Skips workload execution between begin/end calls.

} zet_metric_query_pool_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Metric query pool description
typedef struct _zet_metric_query_pool_desc_t
{
    zet_metric_query_pool_desc_version_t version;   ///< [in] ::ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT
    zet_metric_query_pool_flag_t flags;             ///< [in] Query pool type.
    uint32_t count;                                 ///< [in] Internal slots count within query pool object.

} zet_metric_query_pool_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a pool of metric queries.
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
///         + `nullptr == hMetricGroup`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phMetricQueryPool`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->flags
__ze_api_export ze_result_t __zecall
zetMetricQueryPoolCreate(
    zet_device_handle_t hDevice,                    ///< [in] handle of the device
    zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
    const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
    zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a query pool object.
/// 
/// @details
///     - The application is responsible for destroying all query handles
///       created from the pool before destroying the pool itself
///     - The application is responsible for making sure the device is not
///       currently referencing the any query within the pool before it is
///       deleted
///     - The application may **not** call this function from simultaneous
///       threads with the same query pool handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQueryPool`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zetMetricQueryPoolDestroy(
    zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates metric query object.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQueryPool`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phMetricQuery`
__ze_api_export ze_result_t __zecall
zetMetricQueryCreate(
    zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
    uint32_t index,                                 ///< [in] index of the query within the pool
    zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a metric query object.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the query before it is deleted
///     - The application may **not** call this function from simultaneous
///       threads with the same query handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zetMetricQueryDestroy(
    zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Resets a metric query object back to inital state.
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the query before it is reset
///     - The application may **not** call this function from simultaneous
///       threads with the same query handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMetricQuery`
__ze_api_export ze_result_t __zecall
zetMetricQueryReset(
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query begin into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricQueryBegin(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query end into a command list.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
///         + `nullptr == hMetricQuery`
///     - ::ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricQueryEnd(
    zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
    ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Appends metric query commands to flush all caches.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hCommandList`
__ze_api_export ze_result_t __zecall
zetCommandListAppendMetricMemoryBarrier(
    zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
    );

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
__ze_api_export ze_result_t __zecall
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
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_METRIC_H
