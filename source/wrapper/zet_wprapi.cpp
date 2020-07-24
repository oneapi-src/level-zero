/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_wprapi.cpp
 * @version v1.0-r1.0.4.8
 *
 * @brief C++ wrapper of zet
 *
 */
#include "zet_api.hpp"
#include "ze_singleton.h"

#define _ZE_STRING(s) #s
#define ZE_STRING(s) _ZE_STRING(s)

namespace zet
{
#if !defined(__GNUC__)
#pragma region common
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region device
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region context
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region cmdlist
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region module
#endif
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
    /// @throws result_t
    void ZE_APICALL
    Module::GetDebugInfo(
        debug_info_format_t format,                     ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        auto result = static_cast<result_t>( ::zetModuleGetDebugInfo(
            reinterpret_cast<zet_module_handle_t>( getHandle() ),
            static_cast<zet_module_debug_info_format_t>( format ),
            pSize,
            pDebugInfo ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Module::GetDebugInfo" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region debug
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Debug::Debug( 
        debug_session_handle_t handle                   ///< [in] debug session handle
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves debug properties of the device.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetDebugProperties(
        debug_properties_t* pDebugProperties            ///< [in,out] query result for debug properties
        )
    {
        auto result = static_cast<result_t>( ::zetDeviceGetDebugProperties(
            reinterpret_cast<zet_device_handle_t>( getHandle() ),
            reinterpret_cast<zet_device_debug_properties_t*>( pDebugProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Device::GetDebugProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Attach to a device.
    /// 
    /// @details
    ///     - The device must be enabled for debug; see
    ///       ::zesSchedulerSetComputeUnitDebugMode.
    /// 
    /// @returns
    ///     - Debug*: debug session handle
    /// 
    /// @throws result_t
    Debug* ZE_APICALL
    Debug::Attach(
        Device* pDevice,                                ///< [in] device handle
        const config_t* config                          ///< [in] the debug configuration
        )
    {
        zet_debug_session_handle_t hDebug;

        auto result = static_cast<result_t>( ::zetDebugAttach(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const zet_debug_config_t*>( config ),
            &hDebug ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Attach" );

        Debug* pDebug = nullptr;

        try
        {
            pDebug = new Debug( reinterpret_cast<debug_session_handle_t>( hDebug ) );
        }
        catch( std::bad_alloc& )
        {
            delete pDebug;
            pDebug = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Attach" );
        }

        return pDebug;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Close a debug session.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::Detach(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetDebugDetach(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Detach" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read the topmost debug event.
    /// 
    /// @returns
    ///     - ze::bool_t:'0' when ZE::RESULT_NOT_READY
    /// @throws result_t
    ze::bool_t ZE_APICALL
    Debug::ReadEvent(
        uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the event;
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        event_t* event                                  ///< [in,out] a pointer to a ::zet_debug_event_t.
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadEvent(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            timeout,
            reinterpret_cast<zet_debug_event_t*>( event ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::ReadEvent" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Acknowledge a debug event.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::AcknowledgeEvent(
        const event_t* event                            ///< [in] a pointer to a ::zet_debug_event_t.
        )
    {
        auto result = static_cast<result_t>( ::zetDebugAcknowledgeEvent(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            reinterpret_cast<const zet_debug_event_t*>( event ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::AcknowledgeEvent" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Interrupt device threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::Interrupt(
        ze::Device::thread_t thread                     ///< [in] the thread to interrupt
        )
    {
        auto result = static_cast<result_t>( ::zetDebugInterrupt(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            *reinterpret_cast<ze_device_thread_t*>( &thread ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Interrupt" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Resume device threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::Resume(
        ze::Device::thread_t thread                     ///< [in] the thread to resume
        )
    {
        auto result = static_cast<result_t>( ::zetDebugResume(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            *reinterpret_cast<ze_device_thread_t*>( &thread ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::Resume" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read memory.
    /// 
    /// @details
    ///     - The thread identifier 'all' can be used for accessing the default
    ///       memory space, e.g. for setting breakpoints.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::ReadMemory(
        ze::Device::thread_t thread,                    ///< [in] the thread identifier.
        const memory_space_desc_t* desc,                ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadMemory(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            *reinterpret_cast<ze_device_thread_t*>( &thread ),
            reinterpret_cast<const zet_debug_memory_space_desc_t*>( desc ),
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::ReadMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Write memory.
    /// 
    /// @details
    ///     - The thread identifier 'all' can be used for accessing the default
    ///       memory space, e.g. for setting breakpoints.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::WriteMemory(
        ze::Device::thread_t thread,                    ///< [in] the thread identifier.
        const memory_space_desc_t* desc,                ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto result = static_cast<result_t>( ::zetDebugWriteMemory(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            *reinterpret_cast<ze_device_thread_t*>( &thread ),
            reinterpret_cast<const zet_debug_memory_space_desc_t*>( desc ),
            size,
            buffer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::WriteMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves debug register set properties.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::GetRegisterSetProperties(
        Device* pDevice,                                ///< [in] device handle
        uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of register set properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< register set properties.
                                                        ///< if count is larger than the number of register set properties
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of registry set properties available.
        regset_properties_t* pRegisterSetProperties     ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< register set properties
        )
    {
        auto result = static_cast<result_t>( ::zetDebugGetRegisterSetProperties(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            pCount,
            reinterpret_cast<zet_debug_regset_properties_t*>( pRegisterSetProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::GetRegisterSetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Read register state.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::ReadRegisters(
        ze::Device::thread_t thread,                    ///< [in] the thread identifier
        regset_type_t type,                             ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than ::zet_debug_regset_properties_t.count for the type
        uint32_t count,                                 ///< [in] the number of registers to read; start+count must be <=
                                                        ///< zet_debug_register_group_properties_t.count for the type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        )
    {
        auto result = static_cast<result_t>( ::zetDebugReadRegisters(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            *reinterpret_cast<ze_device_thread_t*>( &thread ),
            static_cast<zet_debug_regset_type_t>( type ),
            start,
            count,
            pRegisterValues ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::ReadRegisters" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Write register state.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Debug::WriteRegisters(
        ze::Device::thread_t thread,                    ///< [in] the thread identifier
        regset_type_t type,                             ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than ::zet_debug_regset_properties_t.count for the type
        uint32_t count,                                 ///< [in] the number of registers to write; start+count must be <=
                                                        ///< zet_debug_register_group_properties_t.count for the type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        )
    {
        auto result = static_cast<result_t>( ::zetDebugWriteRegisters(
            reinterpret_cast<zet_debug_session_handle_t>( getHandle() ),
            *reinterpret_cast<ze_device_thread_t*>( &thread ),
            static_cast<zet_debug_regset_type_t>( type ),
            start,
            count,
            pRegisterValues ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Debug::WriteRegisters" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region metric
#endif
    ///////////////////////////////////////////////////////////////////////////////
    MetricGroup::MetricGroup( 
        metric_group_handle_t handle,                   ///< [in] handle of metric group object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    static singleton_factory_t<MetricGroup, metric_group_handle_t> g_MetricGroupFactory;

    ///////////////////////////////////////////////////////////////////////////////
    Metric::Metric( 
        metric_handle_t handle,                         ///< [in] handle of metric object
        MetricGroup* pMetricGroup                       ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pMetricGroup( pMetricGroup )
    {
    }

    static singleton_factory_t<Metric, metric_handle_t> g_MetricFactory;

    ///////////////////////////////////////////////////////////////////////////////
    MetricStreamer::MetricStreamer( 
        metric_streamer_handle_t handle,                ///< [in] handle of metric streamer object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the metric streamer
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQueryPool::MetricQueryPool( 
        metric_query_pool_handle_t handle,              ///< [in] handle of metric query pool object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the metric query pool
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    MetricQuery::MetricQuery( 
        metric_query_handle_t handle,                   ///< [in] handle of metric query object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves metric group for a device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    MetricGroup::Get(
        Device* pDevice,                                ///< [in] pointer to the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metric groups available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< metric groups.
                                                        ///< if count is larger than the number of metric groups available, then
                                                        ///< the driver will update the value with the correct number of metric
                                                        ///< groups available.
        MetricGroup** ppMetricGroups                    ///< [in,out][optional][range(0, *pCount)] array of pointer to metric
                                                        ///< groups
        )
    {
        thread_local std::vector<zet_metric_group_handle_t> hMetricGroups;
        hMetricGroups.resize( ( ppMetricGroups ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetMetricGroupGet(
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            pCount,
            hMetricGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::Get" );

        for( uint32_t i = 0; ( ppMetricGroups ) && ( i < *pCount ); ++i )
            ppMetricGroups[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMetricGroups ) && ( i < *pCount ); ++i )
                ppMetricGroups[ i ] = g_MetricGroupFactory.getInstance( reinterpret_cast<metric_group_handle_t>( hMetricGroups[ i ] ), pDevice );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    MetricGroup::GetProperties(
        properties_t* pProperties                       ///< [in,out] metric group properties
        )
    {
        auto result = static_cast<result_t>( ::zetMetricGroupGetProperties(
            reinterpret_cast<zet_metric_group_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_group_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Calculates metric values from raw data.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    MetricGroup::CalculateMetricValues(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        calculation_type_t type,                        ///< [in] calculation type to be applied on raw data
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
        typed_value_t* pMetricValues                    ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated
                                                        ///< metrics
        )
    {
        auto result = static_cast<result_t>( ::zetMetricGroupCalculateMetricValues(
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            static_cast<zet_metric_group_calculation_type_t>( type ),
            rawDataSize,
            pRawData,
            pMetricValueCount,
            reinterpret_cast<zet_typed_value_t*>( pMetricValues ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricGroup::CalculateMetricValues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves metric from a metric group.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Metric::Get(
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of metrics available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of metrics.
                                                        ///< if count is larger than the number of metrics available, then the
                                                        ///< driver will update the value with the correct number of metrics available.
        Metric** ppMetrics                              ///< [in,out][optional][range(0, *pCount)] array of pointer to metrics
        )
    {
        thread_local std::vector<zet_metric_handle_t> hMetrics;
        hMetrics.resize( ( ppMetrics ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zetMetricGet(
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            pCount,
            hMetrics.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Metric::Get" );

        for( uint32_t i = 0; ( ppMetrics ) && ( i < *pCount ); ++i )
            ppMetrics[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMetrics ) && ( i < *pCount ); ++i )
                ppMetrics[ i ] = g_MetricFactory.getInstance( reinterpret_cast<metric_handle_t>( hMetrics[ i ] ), pMetricGroup );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::Metric::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a metric.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Metric::GetProperties(
        properties_t* pProperties                       ///< [in,out] metric properties
        )
    {
        auto result = static_cast<result_t>( ::zetMetricGetProperties(
            reinterpret_cast<zet_metric_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Metric::GetProperties" );
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
    /// @throws result_t
    void ZE_APICALL
    Context::ActivateMetricGroups(
        Device* pDevice,                                ///< [in] pointer to the device
        uint32_t count,                                 ///< [in] metric group count to activate; must be 0 if `nullptr ==
                                                        ///< phMetricGroups`
        MetricGroup** ppMetricGroups                    ///< [in][optional][range(0, count)] handles of the metric groups to activate.
                                                        ///< nullptr deactivates all previously used metric groups.
                                                        ///< all metrics groups must come from a different domains.
                                                        ///< metric query and metric stream must use activated metric groups.
        )
    {
        thread_local std::vector<zet_metric_group_handle_t> hMetricGroups;
        hMetricGroups.resize( 0 );
        hMetricGroups.reserve( count );
        for( uint32_t i = 0; i < count; ++i )
            hMetricGroups.emplace_back( ( ppMetricGroups ) ? reinterpret_cast<zet_metric_group_handle_t>( ppMetricGroups[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zetContextActivateMetricGroups(
            reinterpret_cast<zet_context_handle_t>( getHandle() ),
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            count,
            hMetricGroups.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Context::ActivateMetricGroups" );
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
    ///     - MetricStreamer*: handle of metric streamer
    /// 
    /// @throws result_t
    MetricStreamer* ZE_APICALL
    MetricStreamer::Open(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device
        MetricGroup* pMetricGroup,                      ///< [in] pointer to the metric group
        desc_t* desc,                                   ///< [in,out] metric streamer descriptor
        ze::Event* pNotificationEvent                   ///< [in][optional] event used for report availability notification
        )
    {
        zet_metric_streamer_handle_t hMetricStreamer;

        auto result = static_cast<result_t>( ::zetMetricStreamerOpen(
            reinterpret_cast<zet_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<zet_metric_streamer_desc_t*>( desc ),
            ( pNotificationEvent ) ? reinterpret_cast<ze_event_handle_t>( pNotificationEvent->getHandle() ) : nullptr,
            &hMetricStreamer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricStreamer::Open" );

        MetricStreamer* pMetricStreamer = nullptr;

        try
        {
            pMetricStreamer = new MetricStreamer( reinterpret_cast<metric_streamer_handle_t>( hMetricStreamer ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricStreamer;
            pMetricStreamer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricStreamer::Open" );
        }

        return pMetricStreamer;
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
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMetricStreamerMarker(
        MetricStreamer* pMetricStreamer,                ///< [in] pointer to the metric streamer
        uint32_t value                                  ///< [in] streamer marker value
        )
    {
        auto result = static_cast<result_t>( ::zetCommandListAppendMetricStreamerMarker(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_streamer_handle_t>( pMetricStreamer->getHandle() ),
            value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricStreamerMarker" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes metric streamer.
    /// 
    /// @details
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same metric streamer handle.
    /// 
    /// @throws result_t
    void ZE_APICALL
    MetricStreamer::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetMetricStreamerClose(
            reinterpret_cast<zet_metric_streamer_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricStreamer::Close" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reads data from metric streamer.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    MetricStreamer::ReadData(
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
        auto result = static_cast<result_t>( ::zetMetricStreamerReadData(
            reinterpret_cast<zet_metric_streamer_handle_t>( getHandle() ),
            maxReportCount,
            pRawDataSize,
            pRawData ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricStreamer::ReadData" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a pool of metric queries on the context.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - MetricQueryPool*: handle of metric query pool
    /// 
    /// @throws result_t
    MetricQueryPool* ZE_APICALL
    MetricQueryPool::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device
        MetricGroup* pMetricGroup,                      ///< [in] metric group associated with the query object.
        const desc_t* desc                              ///< [in] metric query pool descriptor
        )
    {
        zet_metric_query_pool_handle_t hMetricQueryPool;

        auto result = static_cast<result_t>( ::zetMetricQueryPoolCreate(
            reinterpret_cast<zet_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<zet_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<zet_metric_group_handle_t>( pMetricGroup->getHandle() ),
            reinterpret_cast<const zet_metric_query_pool_desc_t*>( desc ),
            &hMetricQueryPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQueryPool::Create" );

        MetricQueryPool* pMetricQueryPool = nullptr;

        try
        {
            pMetricQueryPool = new MetricQueryPool( reinterpret_cast<metric_query_pool_handle_t>( hMetricQueryPool ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricQueryPool;
            pMetricQueryPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricQueryPool::Create" );
        }

        return pMetricQueryPool;
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
    /// @throws result_t
    void ZE_APICALL
    MetricQueryPool::Destroy(
        MetricQueryPool* pMetricQueryPool               ///< [in][release] pointer to the metric query pool
        )
    {
        auto result = static_cast<result_t>( ::zetMetricQueryPoolDestroy(
            reinterpret_cast<zet_metric_query_pool_handle_t>( pMetricQueryPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQueryPool::Destroy" );

        delete pMetricQueryPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates metric query from the pool.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - MetricQuery*: handle of metric query
    /// 
    /// @throws result_t
    MetricQuery* ZE_APICALL
    MetricQuery::Create(
        MetricQueryPool* pMetricQueryPool,              ///< [in] pointer to the metric query pool
        uint32_t index                                  ///< [in] index of the query within the pool
        )
    {
        zet_metric_query_handle_t hMetricQuery;

        auto result = static_cast<result_t>( ::zetMetricQueryCreate(
            reinterpret_cast<zet_metric_query_pool_handle_t>( pMetricQueryPool->getHandle() ),
            index,
            &hMetricQuery ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Create" );

        MetricQuery* pMetricQuery = nullptr;

        try
        {
            pMetricQuery = new MetricQuery( reinterpret_cast<metric_query_handle_t>( hMetricQuery ), nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pMetricQuery;
            pMetricQuery = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Create" );
        }

        return pMetricQuery;
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
    /// @throws result_t
    void ZE_APICALL
    MetricQuery::Destroy(
        MetricQuery* pMetricQuery                       ///< [in][release] pointer to metric query
        )
    {
        auto result = static_cast<result_t>( ::zetMetricQueryDestroy(
            reinterpret_cast<zet_metric_query_handle_t>( pMetricQuery->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Destroy" );

        delete pMetricQuery;
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
    /// @throws result_t
    void ZE_APICALL
    MetricQuery::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetMetricQueryReset(
            reinterpret_cast<zet_metric_query_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query begin into a command list.
    /// 
    /// @details
    ///     - The application must ensure the metric query is accessible by the
    ///       device on which the command list was created.
    ///     - The application must ensure the command list and metric query were
    ///       created on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMetricQueryBegin(
        MetricQuery* pMetricQuery                       ///< [in] pointer to the metric query
        )
    {
        auto result = static_cast<result_t>( ::zetCommandListAppendMetricQueryBegin(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_query_handle_t>( pMetricQuery->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricQueryBegin" );
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
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMetricQueryEnd(
        MetricQuery* pMetricQuery,                      ///< [in] pointer to the metric query
        ze::Event* pSignalEvent,                        ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze::Event** ppWaitEvents                        ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zetCommandListAppendMetricQueryEnd(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ),
            reinterpret_cast<zet_metric_query_handle_t>( pMetricQuery->getHandle() ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricQueryEnd" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends metric query commands to flush all caches.
    /// 
    /// @details
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMetricMemoryBarrier(
        void
        )
    {
        auto result = static_cast<result_t>( ::zetCommandListAppendMetricMemoryBarrier(
            reinterpret_cast<zet_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::CommandList::AppendMetricMemoryBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves raw data for a given metric query.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    MetricQuery::GetData(
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
        auto result = static_cast<result_t>( ::zetMetricQueryGetData(
            reinterpret_cast<zet_metric_query_handle_t>( getHandle() ),
            pRawDataSize,
            pRawData ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::MetricQuery::GetData" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region pin
#endif
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
    ///     - profile_properties_t: pointer to profile properties
    /// 
    /// @throws result_t
    Kernel::profile_properties_t ZE_APICALL
    Kernel::GetProfileInfo(
        void
        )
    {
        zet_profile_properties_t profileProperties;

        auto result = static_cast<result_t>( ::zetKernelGetProfileInfo(
            reinterpret_cast<zet_kernel_handle_t>( getHandle() ),
            &profileProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::Kernel::GetProfileInfo" );

        return *reinterpret_cast<profile_properties_t*>( &profileProperties );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region tracing
#endif
    ///////////////////////////////////////////////////////////////////////////////
    TracerExp::TracerExp( 
        tracer_exp_handle_t handle,                     ///< [in] handle of tracer object
        Driver* pDriver,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the tracer object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
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
    ///     - TracerExp*: pointer to handle of tracer object created
    /// 
    /// @throws result_t
    TracerExp* ZE_APICALL
    TracerExp::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        const desc_t* desc                              ///< [in] pointer to tracer descriptor
        )
    {
        zet_tracer_exp_handle_t hTracer;

        auto result = static_cast<result_t>( ::zetTracerExpCreate(
            reinterpret_cast<zet_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<const zet_tracer_exp_desc_t*>( desc ),
            &hTracer ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::TracerExp::Create" );

        TracerExp* pTracer = nullptr;

        try
        {
            pTracer = new TracerExp( reinterpret_cast<tracer_exp_handle_t>( hTracer ), nullptr, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pTracer;
            pTracer = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zet::TracerExp::Create" );
        }

        return pTracer;
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
    /// @throws result_t
    void ZE_APICALL
    TracerExp::Destroy(
        TracerExp* pTracer                              ///< [in][release] pointer to tracer object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zetTracerExpDestroy(
            reinterpret_cast<zet_tracer_exp_handle_t>( pTracer->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::TracerExp::Destroy" );

        delete pTracer;
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
    /// @throws result_t
    void ZE_APICALL
    TracerExp::SetPrologues(
        core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto result = static_cast<result_t>( ::zetTracerExpSetPrologues(
            reinterpret_cast<zet_tracer_exp_handle_t>( getHandle() ),
            reinterpret_cast<zet_core_callbacks_t*>( pCoreCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::TracerExp::SetPrologues" );
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
    /// @throws result_t
    void ZE_APICALL
    TracerExp::SetEpilogues(
        core_callbacks_t* pCoreCbs                      ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto result = static_cast<result_t>( ::zetTracerExpSetEpilogues(
            reinterpret_cast<zet_tracer_exp_handle_t>( getHandle() ),
            reinterpret_cast<zet_core_callbacks_t*>( pCoreCbs ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::TracerExp::SetEpilogues" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Enables (or disables) the tracer
    /// 
    /// @details
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same tracer handle.
    /// 
    /// @throws result_t
    void ZE_APICALL
    TracerExp::SetEnabled(
        ze::bool_t enable                               ///< [in] enable the tracer if true; disable if false
        )
    {
        auto result = static_cast<result_t>( ::zetTracerExpSetEnabled(
            reinterpret_cast<zet_tracer_exp_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( enable ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zet::TracerExp::SetEnabled" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
} // namespace zet

namespace zet
{
#if !defined(__GNUC__)
#pragma region common
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts structure_type_t to std::string
    std::string to_string( const structure_type_t val )
    {
        std::string str;

        switch( val )
        {
        case structure_type_t::METRIC_GROUP_PROPERTIES:
            str = "structure_type_t::METRIC_GROUP_PROPERTIES";
            break;

        case structure_type_t::METRIC_PROPERTIES:
            str = "structure_type_t::METRIC_PROPERTIES";
            break;

        case structure_type_t::METRIC_STREAMER_DESC:
            str = "structure_type_t::METRIC_STREAMER_DESC";
            break;

        case structure_type_t::METRIC_QUERY_POOL_DESC:
            str = "structure_type_t::METRIC_QUERY_POOL_DESC";
            break;

        case structure_type_t::PROFILE_PROPERTIES:
            str = "structure_type_t::PROFILE_PROPERTIES";
            break;

        case structure_type_t::DEVICE_DEBUG_PROPERTIES:
            str = "structure_type_t::DEVICE_DEBUG_PROPERTIES";
            break;

        case structure_type_t::DEBUG_MEMORY_SPACE_DESC:
            str = "structure_type_t::DEBUG_MEMORY_SPACE_DESC";
            break;

        case structure_type_t::DEBUG_REGSET_PROPERTIES:
            str = "structure_type_t::DEBUG_REGSET_PROPERTIES";
            break;

        case structure_type_t::TRACER_EXP_DESC:
            str = "structure_type_t::TRACER_EXP_DESC";
            break;

        default:
            str = "structure_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_properties_t to std::string
    std::string to_string( const base_properties_t val )
    {
        std::string str;
        
        str += "base_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "base_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_desc_t to std::string
    std::string to_string( const base_desc_t val )
    {
        std::string str;
        
        str += "base_desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "base_desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_type_t to std::string
    std::string to_string( const value_type_t val )
    {
        std::string str;

        switch( val )
        {
        case value_type_t::UINT32:
            str = "value_type_t::UINT32";
            break;

        case value_type_t::UINT64:
            str = "value_type_t::UINT64";
            break;

        case value_type_t::FLOAT32:
            str = "value_type_t::FLOAT32";
            break;

        case value_type_t::FLOAT64:
            str = "value_type_t::FLOAT64";
            break;

        case value_type_t::BOOL8:
            str = "value_type_t::BOOL8";
            break;

        default:
            str = "value_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts value_t to std::string
    std::string to_string( const value_t val )
    {
        std::string str;
        
        str += "value_t::ui32 : ";
        str += std::to_string(val.ui32);
        str += "\n";
        
        str += "value_t::ui64 : ";
        str += std::to_string(val.ui64);
        str += "\n";
        
        str += "value_t::fp32 : ";
        str += std::to_string(val.fp32);
        str += "\n";
        
        str += "value_t::fp64 : ";
        str += std::to_string(val.fp64);
        str += "\n";
        
        str += "value_t::b8 : ";
        str += std::to_string(val.b8);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts typed_value_t to std::string
    std::string to_string( const typed_value_t val )
    {
        std::string str;
        
        str += "typed_value_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "typed_value_t::value : ";
        str += to_string(val.value);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region device
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::debug_property_flags_t to std::string
    std::string to_string( const Device::debug_property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::DEBUG_PROPERTY_FLAG_ATTACH) & bits )
            str += "DEBUG_PROPERTY_FLAG_ATTACH | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::debug_properties_t to std::string
    std::string to_string( const Device::debug_properties_t val )
    {
        std::string str;
        
        str += "Device::debug_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::debug_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::debug_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region context
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region cmdlist
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region module
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::debug_info_format_t to std::string
    std::string to_string( const Module::debug_info_format_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::debug_info_format_t::ELF_DWARF:
            str = "Module::debug_info_format_t::ELF_DWARF";
            break;

        default:
            str = "Module::debug_info_format_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_flags_t to std::string
    std::string to_string( const Kernel::profile_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Kernel::PROFILE_FLAG_REGISTER_REALLOCATION) & bits )
            str += "PROFILE_FLAG_REGISTER_REALLOCATION | ";
        
        if( static_cast<uint32_t>(Kernel::PROFILE_FLAG_FREE_REGISTER_INFO) & bits )
            str += "PROFILE_FLAG_FREE_REGISTER_INFO | ";

        return ( str.size() > 3 ) 
            ? "Kernel::{ " + str.substr(0, str.size() - 3) + " }"
            : "Kernel::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_token_type_t to std::string
    std::string to_string( const Kernel::profile_token_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Kernel::profile_token_type_t::FREE_REGISTER:
            str = "Kernel::profile_token_type_t::FREE_REGISTER";
            break;

        default:
            str = "Kernel::profile_token_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_properties_t to std::string
    std::string to_string( const Kernel::profile_properties_t val )
    {
        std::string str;
        
        str += "Kernel::profile_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Kernel::profile_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Kernel::profile_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Kernel::profile_properties_t::numTokens : ";
        str += std::to_string(val.numTokens);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_free_register_token_t to std::string
    std::string to_string( const Kernel::profile_free_register_token_t val )
    {
        std::string str;
        
        str += "Kernel::profile_free_register_token_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Kernel::profile_free_register_token_t::size : ";
        str += std::to_string(val.size);
        str += "\n";
        
        str += "Kernel::profile_free_register_token_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::profile_register_sequence_t to std::string
    std::string to_string( const Kernel::profile_register_sequence_t val )
    {
        std::string str;
        
        str += "Kernel::profile_register_sequence_t::start : ";
        str += std::to_string(val.start);
        str += "\n";
        
        str += "Kernel::profile_register_sequence_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region debug
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_flags_t to std::string
    std::string to_string( const Debug::event_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Debug::EVENT_FLAG_NEED_ACK) & bits )
            str += "EVENT_FLAG_NEED_ACK | ";

        return ( str.size() > 3 ) 
            ? "Debug::{ " + str.substr(0, str.size() - 3) + " }"
            : "Debug::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_type_t to std::string
    std::string to_string( const Debug::event_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::event_type_t::INVALID:
            str = "Debug::event_type_t::INVALID";
            break;

        case Debug::event_type_t::DETACHED:
            str = "Debug::event_type_t::DETACHED";
            break;

        case Debug::event_type_t::PROCESS_ENTRY:
            str = "Debug::event_type_t::PROCESS_ENTRY";
            break;

        case Debug::event_type_t::PROCESS_EXIT:
            str = "Debug::event_type_t::PROCESS_EXIT";
            break;

        case Debug::event_type_t::MODULE_LOAD:
            str = "Debug::event_type_t::MODULE_LOAD";
            break;

        case Debug::event_type_t::MODULE_UNLOAD:
            str = "Debug::event_type_t::MODULE_UNLOAD";
            break;

        case Debug::event_type_t::THREAD_STOPPED:
            str = "Debug::event_type_t::THREAD_STOPPED";
            break;

        case Debug::event_type_t::THREAD_UNAVAILABLE:
            str = "Debug::event_type_t::THREAD_UNAVAILABLE";
            break;

        default:
            str = "Debug::event_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::detach_reason_t to std::string
    std::string to_string( const Debug::detach_reason_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::detach_reason_t::INVALID:
            str = "Debug::detach_reason_t::INVALID";
            break;

        case Debug::detach_reason_t::HOST_EXIT:
            str = "Debug::detach_reason_t::HOST_EXIT";
            break;

        default:
            str = "Debug::detach_reason_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_type_t to std::string
    std::string to_string( const Debug::memory_space_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::memory_space_type_t::DEFAULT:
            str = "Debug::memory_space_type_t::DEFAULT";
            break;

        case Debug::memory_space_type_t::SLM:
            str = "Debug::memory_space_type_t::SLM";
            break;

        default:
            str = "Debug::memory_space_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::regset_type_t to std::string
    std::string to_string( const Debug::regset_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Debug::regset_type_t::INVALID:
            str = "Debug::regset_type_t::INVALID";
            break;

        case Debug::regset_type_t::GPR:
            str = "Debug::regset_type_t::GPR";
            break;

        case Debug::regset_type_t::ACC:
            str = "Debug::regset_type_t::ACC";
            break;

        case Debug::regset_type_t::ADDR:
            str = "Debug::regset_type_t::ADDR";
            break;

        case Debug::regset_type_t::FLAG:
            str = "Debug::regset_type_t::FLAG";
            break;

        default:
            str = "Debug::regset_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::regset_flags_t to std::string
    std::string to_string( const Debug::regset_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Debug::REGSET_FLAG_READ_ONLY) & bits )
            str += "REGSET_FLAG_READ_ONLY | ";

        return ( str.size() > 3 ) 
            ? "Debug::{ " + str.substr(0, str.size() - 3) + " }"
            : "Debug::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::config_t to std::string
    std::string to_string( const Debug::config_t val )
    {
        std::string str;
        
        str += "Debug::config_t::pid : ";
        str += std::to_string(val.pid);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_detached_t to std::string
    std::string to_string( const Debug::event_info_detached_t val )
    {
        std::string str;
        
        str += "Debug::event_info_detached_t::reason : ";
        str += to_string(val.reason);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_module_t to std::string
    std::string to_string( const Debug::event_info_module_t val )
    {
        std::string str;
        
        str += "Debug::event_info_module_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Debug::event_info_module_t::moduleBegin : ";
        str += std::to_string(val.moduleBegin);
        str += "\n";
        
        str += "Debug::event_info_module_t::moduleEnd : ";
        str += std::to_string(val.moduleEnd);
        str += "\n";
        
        str += "Debug::event_info_module_t::load : ";
        str += std::to_string(val.load);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_thread_stopped_t to std::string
    std::string to_string( const Debug::event_info_thread_stopped_t val )
    {
        std::string str;
        
        str += "Debug::event_info_thread_stopped_t::thread : ";
        str += to_string(val.thread);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_info_t to std::string
    std::string to_string( const Debug::event_info_t val )
    {
        std::string str;
        
        str += "Debug::event_info_t::detached : ";
        str += to_string(val.detached);
        str += "\n";
        
        str += "Debug::event_info_t::module : ";
        str += to_string(val.module);
        str += "\n";
        
        str += "Debug::event_info_t::thread : ";
        str += to_string(val.thread);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::event_t to std::string
    std::string to_string( const Debug::event_t val )
    {
        std::string str;
        
        str += "Debug::event_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Debug::event_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Debug::event_t::info : ";
        str += to_string(val.info);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::memory_space_desc_t to std::string
    std::string to_string( const Debug::memory_space_desc_t val )
    {
        std::string str;
        
        str += "Debug::memory_space_desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Debug::memory_space_desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Debug::memory_space_desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Debug::memory_space_desc_t::address : ";
        str += std::to_string(val.address);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Debug::regset_properties_t to std::string
    std::string to_string( const Debug::regset_properties_t val )
    {
        std::string str;
        
        str += "Debug::regset_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Debug::regset_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Debug::regset_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Debug::regset_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Debug::regset_properties_t::count : ";
        str += std::to_string(val.count);
        str += "\n";
        
        str += "Debug::regset_properties_t::valueType : ";
        str += to_string(val.valueType);
        str += "\n";
        
        str += "Debug::regset_properties_t::valueSize : ";
        str += std::to_string(val.valueSize);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region metric
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::sampling_type_flags_t to std::string
    std::string to_string( const MetricGroup::sampling_type_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(MetricGroup::SAMPLING_TYPE_FLAG_EVENT_BASED) & bits )
            str += "SAMPLING_TYPE_FLAG_EVENT_BASED | ";
        
        if( static_cast<uint32_t>(MetricGroup::SAMPLING_TYPE_FLAG_TIME_BASED) & bits )
            str += "SAMPLING_TYPE_FLAG_TIME_BASED | ";

        return ( str.size() > 3 ) 
            ? "MetricGroup::{ " + str.substr(0, str.size() - 3) + " }"
            : "MetricGroup::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::calculation_type_t to std::string
    std::string to_string( const MetricGroup::calculation_type_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricGroup::calculation_type_t::METRIC_VALUES:
            str = "MetricGroup::calculation_type_t::METRIC_VALUES";
            break;

        case MetricGroup::calculation_type_t::MAX_METRIC_VALUES:
            str = "MetricGroup::calculation_type_t::MAX_METRIC_VALUES";
            break;

        default:
            str = "MetricGroup::calculation_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricGroup::properties_t to std::string
    std::string to_string( const MetricGroup::properties_t val )
    {
        std::string str;
        
        str += "MetricGroup::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "MetricGroup::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "MetricGroup::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "MetricGroup::properties_t::description : ";
        str += val.description;
        str += "\n";
        
        str += "MetricGroup::properties_t::samplingType : ";
        str += to_string(val.samplingType);
        str += "\n";
        
        str += "MetricGroup::properties_t::domain : ";
        str += std::to_string(val.domain);
        str += "\n";
        
        str += "MetricGroup::properties_t::metricCount : ";
        str += std::to_string(val.metricCount);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::type_t to std::string
    std::string to_string( const Metric::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Metric::type_t::DURATION:
            str = "Metric::type_t::DURATION";
            break;

        case Metric::type_t::EVENT:
            str = "Metric::type_t::EVENT";
            break;

        case Metric::type_t::EVENT_WITH_RANGE:
            str = "Metric::type_t::EVENT_WITH_RANGE";
            break;

        case Metric::type_t::THROUGHPUT:
            str = "Metric::type_t::THROUGHPUT";
            break;

        case Metric::type_t::TIMESTAMP:
            str = "Metric::type_t::TIMESTAMP";
            break;

        case Metric::type_t::FLAG:
            str = "Metric::type_t::FLAG";
            break;

        case Metric::type_t::RATIO:
            str = "Metric::type_t::RATIO";
            break;

        case Metric::type_t::RAW:
            str = "Metric::type_t::RAW";
            break;

        default:
            str = "Metric::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Metric::properties_t to std::string
    std::string to_string( const Metric::properties_t val )
    {
        std::string str;
        
        str += "Metric::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Metric::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Metric::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Metric::properties_t::description : ";
        str += val.description;
        str += "\n";
        
        str += "Metric::properties_t::component : ";
        str += val.component;
        str += "\n";
        
        str += "Metric::properties_t::tierNumber : ";
        str += std::to_string(val.tierNumber);
        str += "\n";
        
        str += "Metric::properties_t::metricType : ";
        str += to_string(val.metricType);
        str += "\n";
        
        str += "Metric::properties_t::resultType : ";
        str += to_string(val.resultType);
        str += "\n";
        
        str += "Metric::properties_t::resultUnits : ";
        str += val.resultUnits;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricStreamer::desc_t to std::string
    std::string to_string( const MetricStreamer::desc_t val )
    {
        std::string str;
        
        str += "MetricStreamer::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "MetricStreamer::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "MetricStreamer::desc_t::notifyEveryNReports : ";
        str += std::to_string(val.notifyEveryNReports);
        str += "\n";
        
        str += "MetricStreamer::desc_t::samplingPeriod : ";
        str += std::to_string(val.samplingPeriod);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::type_t to std::string
    std::string to_string( const MetricQueryPool::type_t val )
    {
        std::string str;

        switch( val )
        {
        case MetricQueryPool::type_t::PERFORMANCE:
            str = "MetricQueryPool::type_t::PERFORMANCE";
            break;

        case MetricQueryPool::type_t::EXECUTION:
            str = "MetricQueryPool::type_t::EXECUTION";
            break;

        default:
            str = "MetricQueryPool::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts MetricQueryPool::desc_t to std::string
    std::string to_string( const MetricQueryPool::desc_t val )
    {
        std::string str;
        
        str += "MetricQueryPool::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "MetricQueryPool::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "MetricQueryPool::desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "MetricQueryPool::desc_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region pin
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region tracing
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts api_tracing_exp_version_t to std::string
    std::string to_string( const api_tracing_exp_version_t val )
    {
        std::string str;

        switch( val )
        {
        case api_tracing_exp_version_t::_1_0:
            str = "api_tracing_exp_version_t::_1_0";
            break;

        default:
            str = "api_tracing_exp_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts TracerExp::desc_t to std::string
    std::string to_string( const TracerExp::desc_t val )
    {
        std::string str;
        
        str += "TracerExp::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "TracerExp::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "TracerExp::desc_t::pUserData : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pUserData);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
} // namespace zet
