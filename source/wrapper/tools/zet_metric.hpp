/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_metric.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Tool APIs for Metric
 *
 */
#ifndef _ZET_METRIC_HPP
#define _ZET_METRIC_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

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

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported value types
    enum class value_type_t
    {
        UINT32,                                         ///< 32-bit unsigned-integer
        UINT64,                                         ///< 64-bit unsigned-integer
        FLOAT32,                                        ///< 32-bit floating-point
        FLOAT64,                                        ///< 64-bit floating-point
        BOOL8,                                          ///< 8-bit boolean

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Union of values
    union value_t
    {
        uint32_t ui32;                                  ///< [out] 32-bit unsigned-integer
        uint64_t ui64;                                  ///< [out] 32-bit unsigned-integer
        float fp32;                                     ///< [out] 32-bit floating-point
        double fp64;                                    ///< [out] 64-bit floating-point
        ze::bool_t b8;                                  ///< [out] 8-bit boolean

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Typed value
    struct typed_value_t
    {
        value_type_t type;                              ///< [out] type of value
        value_t value;                                  ///< [out] value

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric group
    class MetricGroup
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group sampling type
        enum class sampling_type_t
        {
            EVENT_BASED = ZE_BIT(0),                        ///< Event based sampling
            TIME_BASED = ZE_BIT(1),                         ///< Time based sampling

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_group_properties_t
        enum class properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric group properties queried using ::zetMetricGroupGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZET_METRIC_GROUP_PROPERTIES_VERSION_CURRENT
            char name[ZET_MAX_METRIC_GROUP_NAME];           ///< [out] metric group name
            char description[ZET_MAX_METRIC_GROUP_DESCRIPTION]; ///< [out] metric group description
            sampling_type_t samplingType;                   ///< [out] metric group sampling type
            uint32_t domain;                                ///< [out] metric group domain number. Cannot use simultaneous metric
                                                            ///< groups from different domains.
            uint32_t maxCommandQueueOrdinal;                ///< [out] tracers and queries of this metric group cannot be submitted to
                                                            ///< a command queue with a larger ordinal value.
                                                            ///< See ::ze_command_queue_desc_t for more information on how to specify
                                                            ///< the command queue's ordinal.
            uint32_t metricCount;                           ///< [out] metric count belonging to this group

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_group_handle_t m_handle = nullptr;       ///< [in] handle of metric group object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricGroup( void ) = delete;
        MetricGroup( 
            metric_group_handle_t handle,                   ///< [in] handle of metric group object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricGroup( void ) = default;

        MetricGroup( MetricGroup const& other ) = delete;
        void operator=( MetricGroup const& other ) = delete;

        MetricGroup( MetricGroup&& other ) = delete;
        void operator=( MetricGroup&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves metric group for a device.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __zecall
        Get(
            Device* pDevice,                                ///< [in] pointer to the device
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metric groups available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< metric groups.
                                                            ///< if count is larger than the number of metric groups available, then
                                                            ///< the driver will update the value with the correct number of metric
                                                            ///< groups available.
            MetricGroup** ppMetricGroups = nullptr          ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                            ///< groups
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pProperties                       ///< [in,out] metric group properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Calculates metric values from raw data.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __zecall
        CalculateMetricValues(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
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
            typed_value_t* pMetricValues = nullptr          ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                            ///< metrics
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric
    class Metric
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric types
        enum class type_t
        {
            DURATION,                                       ///< Metric type: duration
            EVENT,                                          ///< Metric type: event
            EVENT_WITH_RANGE,                               ///< Metric type: event with range
            THROUGHPUT,                                     ///< Metric type: throughput
            TIMESTAMP,                                      ///< Metric type: timestamp
            FLAG,                                           ///< Metric type: flag
            RATIO,                                          ///< Metric type: ratio
            RAW,                                            ///< Metric type: raw

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_properties_t
        enum class properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric properties queried using ::zetMetricGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZET_METRIC_PROPERTIES_VERSION_CURRENT
            char name[ZET_MAX_METRIC_NAME];                 ///< [out] metric name
            char description[ZET_MAX_METRIC_DESCRIPTION];   ///< [out] metric description
            char component[ZET_MAX_METRIC_COMPONENT];       ///< [out] metric component
            uint32_t tierNumber;                            ///< [out] number of tier
            type_t metricType;                              ///< [out] metric type
            value_type_t resultType;                        ///< [out] metric result type
            char resultUnits[ZET_MAX_METRIC_RESULT_UNITS];  ///< [out] metric result units

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_handle_t m_handle;                       ///< [in] handle of metric object
        MetricGroup* m_pMetricGroup;                    ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Metric( void ) = delete;
        Metric( 
            metric_handle_t handle,                         ///< [in] handle of metric object
            MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
            );

        ~Metric( void ) = default;

        Metric( Metric const& other ) = delete;
        void operator=( Metric const& other ) = delete;

        Metric( Metric&& other ) = delete;
        void operator=( Metric&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getMetricgroup( void ) const { return m_pMetricGroup; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves metric from a metric group.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        static void __zecall
        Get(
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of metrics available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                            ///< if count is larger than the number of metrics available, then the
                                                            ///< driver will update the value with the correct number of metrics available.
            Metric** ppMetrics = nullptr                    ///< [in,out][optional][range(0, *pCount)] array of pointer to metrics
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a metric.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pProperties                       ///< [in,out] metric properties
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric tracer
    class MetricTracer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_tracer_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric tracer descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZET_METRIC_TRACER_DESC_VERSION_CURRENT
            uint32_t notifyEveryNReports;                   ///< [in,out] number of collected reports after which notification event
                                                            ///< will be signalled
            uint32_t samplingPeriod;                        ///< [in,out] tracer sampling period in nanoseconds

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_tracer_handle_t m_handle;                ///< [in] handle of metric tracer object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric tracer

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricTracer( void ) = delete;
        MetricTracer( 
            metric_tracer_handle_t handle,                  ///< [in] handle of metric tracer object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric tracer
            );

        ~MetricTracer( void ) = default;

        MetricTracer( MetricTracer const& other ) = delete;
        void operator=( MetricTracer const& other ) = delete;

        MetricTracer( MetricTracer&& other ) = delete;
        void operator=( MetricTracer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens metric tracer for a device.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// @returns
        ///     - MetricTracer*: handle of metric tracer
        /// 
        /// @throws result_t
        static MetricTracer* __zecall
        Open(
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
            desc_t* desc,                                   ///< [in,out] metric tracer descriptor
            ze::Event* pNotificationEvent = nullptr         ///< [in][optional] event used for report availability notification. Must
                                                            ///< be device to host type.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes metric tracer.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same metric tracer handle.
        /// @throws result_t
        void __zecall
        Close(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reads data from metric tracer.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        ReadData(
            uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                            ///< if UINT32_MAX, then function will retrieve all reports available
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
                                                            ///< if size is larger than size needed for all reports, then driver will
                                                            ///< update the value with the actual size needed.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                            ///< reports in raw format
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query pool
    class MetricQueryPool
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::zet_metric_query_pool_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool types
        enum class flag_t
        {
            PERFORMANCE,                                    ///< Performance metric query pool.
            SKIP_EXECUTION,                                 ///< Skips workload execution between begin/end calls.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Metric query pool description
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZET_METRIC_QUERY_POOL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::PERFORMANCE;             ///< [in] Query pool type.
            uint32_t count;                                 ///< [in] Internal slots count within query pool object.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_pool_handle_t m_handle;            ///< [in] handle of metric query pool object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the metric query pool

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQueryPool( void ) = delete;
        MetricQueryPool( 
            metric_query_pool_handle_t handle,              ///< [in] handle of metric query pool object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the metric query pool
            );

        ~MetricQueryPool( void ) = default;

        MetricQueryPool( MetricQueryPool const& other ) = delete;
        void operator=( MetricQueryPool const& other ) = delete;

        MetricQueryPool( MetricQueryPool&& other ) = delete;
        void operator=( MetricQueryPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool of metric queries.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - MetricQueryPool*: handle of metric query pool
        /// 
        /// @throws result_t
        static MetricQueryPool* __zecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            MetricGroup* pMetricGroup,                      ///< [in] metric group associated with the query object.
            const desc_t* desc                              ///< [in] metric query pool descriptor
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
        /// @throws result_t
        static void __zecall
        Destroy(
            MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for metric query
    class MetricQuery
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        metric_query_handle_t m_handle;                 ///< [in] handle of metric query object
        Device* m_pDevice;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        MetricQuery( void ) = delete;
        MetricQuery( 
            metric_query_handle_t handle,                   ///< [in] handle of metric query object
            Device* pDevice                                 ///< [in] pointer to owner object
            );

        ~MetricQuery( void ) = default;

        MetricQuery( MetricQuery const& other ) = delete;
        void operator=( MetricQuery const& other ) = delete;

        MetricQuery( MetricQuery&& other ) = delete;
        void operator=( MetricQuery&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates metric query object.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - MetricQuery*: handle of metric query
        /// 
        /// @throws result_t
        static MetricQuery* __zecall
        Create(
            MetricQueryPool* pMetricQueryPool,              ///< [in] pointer to the metric query pool
            uint32_t index                                  ///< [in] index of the query within the pool
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Deletes a metric query object.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the query before it is deleted
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query handle.
        /// @throws result_t
        static void __zecall
        Destroy(
            MetricQuery* pMetricQuery                       ///< [in][release] pointer to metric query
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Resets a metric query object back to inital state.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the query before it is reset
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same query handle.
        /// @throws result_t
        void __zecall
        Reset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves raw data for a given metric query.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetData(
            size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                            ///< if size is zero, then the driver will update the value with the total
                                                            ///< size in bytes needed for all reports available.
                                                            ///< if size is non-zero, then driver will only retrieve the number of
                                                            ///< reports that fit into the buffer.
                                                            ///< if size is larger than size needed for all reports, then driver will
                                                            ///< update the value with the actual size needed.
            uint8_t* pRawData = nullptr                     ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                            ///< reports in raw format
            );

    };

} // namespace zet

namespace zet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( const value_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_t to std::string
    std::string to_string( const value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_t to std::string
    std::string to_string( const typed_value_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type_t to std::string
    std::string to_string( const MetricGroup::sampling_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_version_t to std::string
    std::string to_string( const MetricGroup::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_t to std::string
    std::string to_string( const MetricGroup::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( const Metric::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_version_t to std::string
    std::string to_string( const Metric::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_t to std::string
    std::string to_string( const Metric::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_version_t to std::string
    std::string to_string( const MetricTracer::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricTracer::desc_t to std::string
    std::string to_string( const MetricTracer::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_version_t to std::string
    std::string to_string( const MetricQueryPool::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::flag_t to std::string
    std::string to_string( const MetricQueryPool::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_t to std::string
    std::string to_string( const MetricQueryPool::desc_t val );

} // namespace zet
#endif // defined(__cplusplus)
#endif // _ZET_METRIC_HPP
