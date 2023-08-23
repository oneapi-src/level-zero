/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_ldrddi.cpp
 *
 */
#include "ze_loader_internal.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    zet_driver_factory_t                zet_driver_factory;
    zet_device_factory_t                zet_device_factory;
    zet_context_factory_t               zet_context_factory;
    zet_command_list_factory_t          zet_command_list_factory;
    zet_module_factory_t                zet_module_factory;
    zet_kernel_factory_t                zet_kernel_factory;
    zet_metric_group_factory_t          zet_metric_group_factory;
    zet_metric_factory_t                zet_metric_factory;
    zet_metric_streamer_factory_t       zet_metric_streamer_factory;
    zet_metric_query_pool_factory_t     zet_metric_query_pool_factory;
    zet_metric_query_factory_t          zet_metric_query_factory;
    zet_tracer_exp_factory_t            zet_tracer_exp_factory;
    zet_debug_session_factory_t         zet_debug_session_factory;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_module_object_t*>( hModule )->dditable;
        auto pfnGetDebugInfo = dditable->zet.Module.pfnGetDebugInfo;
        if( nullptr == pfnGetDebugInfo )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<zet_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnGetDebugProperties = dditable->zet.Device.pfnGetDebugProperties;
        if( nullptr == pfnGetDebugProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetDebugProperties( hDevice, pDebugProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnAttach = dditable->zet.Debug.pfnAttach;
        if( nullptr == pfnAttach )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnAttach( hDevice, config, phDebug );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phDebug = reinterpret_cast<zet_debug_session_handle_t>(
                zet_debug_session_factory.getInstance( *phDebug, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnDetach = dditable->zet.Debug.pfnDetach;
        if( nullptr == pfnDetach )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnDetach( hDebug );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        zet_debug_session_factory.release( hDebug );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnReadEvent = dditable->zet.Debug.pfnReadEvent;
        if( nullptr == pfnReadEvent )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnReadEvent( hDebug, timeout, event );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnAcknowledgeEvent = dditable->zet.Debug.pfnAcknowledgeEvent;
        if( nullptr == pfnAcknowledgeEvent )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnAcknowledgeEvent( hDebug, event );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnInterrupt = dditable->zet.Debug.pfnInterrupt;
        if( nullptr == pfnInterrupt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnInterrupt( hDebug, thread );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnResume = dditable->zet.Debug.pfnResume;
        if( nullptr == pfnResume )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnResume( hDebug, thread );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnReadMemory = dditable->zet.Debug.pfnReadMemory;
        if( nullptr == pfnReadMemory )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnReadMemory( hDebug, thread, desc, size, buffer );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnWriteMemory = dditable->zet.Debug.pfnWriteMemory;
        if( nullptr == pfnWriteMemory )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnWriteMemory( hDebug, thread, desc, size, buffer );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnGetRegisterSetProperties = dditable->zet.Debug.pfnGetRegisterSetProperties;
        if( nullptr == pfnGetRegisterSetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnGetThreadRegisterSetProperties = dditable->zet.Debug.pfnGetThreadRegisterSetProperties;
        if( nullptr == pfnGetThreadRegisterSetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnReadRegisters = dditable->zet.Debug.pfnReadRegisters;
        if( nullptr == pfnReadRegisters )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnWriteRegisters = dditable->zet.Debug.pfnWriteRegisters;
        if( nullptr == pfnWriteRegisters )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnGet = dditable->zet.MetricGroup.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGet( hDevice, pCount, phMetricGroups );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < *pCount ); ++i )
                phMetricGroups[ i ] = reinterpret_cast<zet_metric_group_handle_t>(
                    zet_metric_group_factory.getInstance( phMetricGroups[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnGetProperties = dditable->zet.MetricGroup.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMetricGroup, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnCalculateMetricValues = dditable->zet.MetricGroup.pfnCalculateMetricValues;
        if( nullptr == pfnCalculateMetricValues )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnGet = dditable->zet.Metric.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGet( hMetricGroup, pCount, phMetrics );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetrics ) && ( i < *pCount ); ++i )
                phMetrics[ i ] = reinterpret_cast<zet_metric_handle_t>(
                    zet_metric_factory.getInstance( phMetrics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_object_t*>( hMetric )->dditable;
        auto pfnGetProperties = dditable->zet.Metric.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetric = reinterpret_cast<zet_metric_object_t*>( hMetric )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMetric, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_context_object_t*>( hContext )->dditable;
        auto pfnActivateMetricGroups = dditable->zet.Context.pfnActivateMetricGroups;
        if( nullptr == pfnActivateMetricGroups )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<zet_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // convert loader handles to driver handles
        auto phMetricGroupsLocal = new zet_metric_group_handle_t [count];
        for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < count ); ++i )
            phMetricGroupsLocal[ i ] = reinterpret_cast<zet_metric_group_object_t*>( phMetricGroups[ i ] )->handle;

        // forward to device-driver
        result = pfnActivateMetricGroups( hContext, hDevice, count, phMetricGroupsLocal );
        delete []phMetricGroupsLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_context_object_t*>( hContext )->dditable;
        auto pfnOpen = dditable->zet.MetricStreamer.pfnOpen;
        if( nullptr == pfnOpen )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<zet_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // convert loader handle to driver handle
        hNotificationEvent = ( hNotificationEvent ) ? reinterpret_cast<ze_event_object_t*>( hNotificationEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phMetricStreamer = reinterpret_cast<zet_metric_streamer_handle_t>(
                zet_metric_streamer_factory.getInstance( *phMetricStreamer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricStreamerMarker = dditable->zet.CommandList.pfnAppendMetricStreamerMarker;
        if( nullptr == pfnAppendMetricStreamerMarker )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricStreamer = reinterpret_cast<zet_metric_streamer_object_t*>( hMetricStreamer )->handle;

        // forward to device-driver
        result = pfnAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_streamer_object_t*>( hMetricStreamer )->dditable;
        auto pfnClose = dditable->zet.MetricStreamer.pfnClose;
        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricStreamer = reinterpret_cast<zet_metric_streamer_object_t*>( hMetricStreamer )->handle;

        // forward to device-driver
        result = pfnClose( hMetricStreamer );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        zet_metric_streamer_factory.release( hMetricStreamer );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_streamer_object_t*>( hMetricStreamer )->dditable;
        auto pfnReadData = dditable->zet.MetricStreamer.pfnReadData;
        if( nullptr == pfnReadData )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricStreamer = reinterpret_cast<zet_metric_streamer_object_t*>( hMetricStreamer )->handle;

        // forward to device-driver
        result = pfnReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->zet.MetricQueryPool.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<zet_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phMetricQueryPool = reinterpret_cast<zet_metric_query_pool_handle_t>(
                zet_metric_query_pool_factory.getInstance( *phMetricQueryPool, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;
        auto pfnDestroy = dditable->zet.MetricQueryPool.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        result = pfnDestroy( hMetricQueryPool );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        zet_metric_query_pool_factory.release( hMetricQueryPool );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;
        auto pfnCreate = dditable->zet.MetricQuery.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        result = pfnCreate( hMetricQueryPool, index, phMetricQuery );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phMetricQuery = reinterpret_cast<zet_metric_query_handle_t>(
                zet_metric_query_factory.getInstance( *phMetricQuery, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnDestroy = dditable->zet.MetricQuery.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnDestroy( hMetricQuery );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        zet_metric_query_factory.release( hMetricQuery );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnReset = dditable->zet.MetricQuery.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnReset( hMetricQuery );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricQueryBegin = dditable->zet.CommandList.pfnAppendMetricQueryBegin;
        if( nullptr == pfnAppendMetricQueryBegin )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricQueryEnd = dditable->zet.CommandList.pfnAppendMetricQueryEnd;
        if( nullptr == pfnAppendMetricQueryEnd )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // convert loader handle to driver handle
        hSignalEvent = ( hSignalEvent ) ? reinterpret_cast<ze_event_object_t*>( hSignalEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricMemoryBarrier = dditable->zet.CommandList.pfnAppendMetricMemoryBarrier;
        if( nullptr == pfnAppendMetricMemoryBarrier )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnAppendMetricMemoryBarrier( hCommandList );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnGetData = dditable->zet.MetricQuery.pfnGetData;
        if( nullptr == pfnGetData )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnGetData( hMetricQuery, pRawDataSize, pRawData );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_kernel_object_t*>( hKernel )->dditable;
        auto pfnGetProfileInfo = dditable->zet.Kernel.pfnGetProfileInfo;
        if( nullptr == pfnGetProfileInfo )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<zet_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnGetProfileInfo( hKernel, pProfileProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_context_object_t*>( hContext )->dditable;
        auto pfnCreate = dditable->zet.TracerExp.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<zet_context_object_t*>( hContext )->handle;

        // forward to device-driver
        result = pfnCreate( hContext, desc, phTracer );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phTracer = reinterpret_cast<zet_tracer_exp_handle_t>(
                zet_tracer_exp_factory.getInstance( *phTracer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->dditable;
        auto pfnDestroy = dditable->zet.TracerExp.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnDestroy( hTracer );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        // release loader handle
        zet_tracer_exp_factory.release( hTracer );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->dditable;
        auto pfnSetPrologues = dditable->zet.TracerExp.pfnSetPrologues;
        if( nullptr == pfnSetPrologues )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetPrologues( hTracer, pCoreCbs );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->dditable;
        auto pfnSetEpilogues = dditable->zet.TracerExp.pfnSetEpilogues;
        if( nullptr == pfnSetEpilogues )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetEpilogues( hTracer, pCoreCbs );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->dditable;
        auto pfnSetEnabled = dditable->zet.TracerExp.pfnSetEnabled;
        if( nullptr == pfnSetEnabled )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_exp_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetEnabled( hTracer, enable );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnCalculateMultipleMetricValuesExp = dditable->zet.MetricGroupExp.pfnCalculateMultipleMetricValuesExp;
        if( nullptr == pfnCalculateMultipleMetricValuesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnGetGlobalTimestampsExp = dditable->zet.MetricGroupExp.pfnGetGlobalTimestampsExp;
        if( nullptr == pfnGetGlobalTimestampsExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnGetExportDataExp = dditable->zet.MetricGroupExp.pfnGetExportDataExp;
        if( nullptr == pfnGetExportDataExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnCalculateMetricExportDataExp = dditable->zet.MetricGroupExp.pfnCalculateMetricExportDataExp;
        if( nullptr == pfnCalculateMetricExportDataExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetDeviceProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Device);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetDebugProperties                       = loader::zetDeviceGetDebugProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetDeviceProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_context_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetContextProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Context);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnActivateMetricGroups                     = loader::zetContextActivateMetricGroups;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.Context;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetContextProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetCommandListProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.CommandList);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnAppendMetricStreamerMarker               = loader::zetCommandListAppendMetricStreamerMarker;
            pDdiTable->pfnAppendMetricQueryBegin                   = loader::zetCommandListAppendMetricQueryBegin;
            pDdiTable->pfnAppendMetricQueryEnd                     = loader::zetCommandListAppendMetricQueryEnd;
            pDdiTable->pfnAppendMetricMemoryBarrier                = loader::zetCommandListAppendMetricMemoryBarrier;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetCommandListProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetKernelProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Kernel);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProfileInfo                           = loader::zetKernelGetProfileInfo;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.Kernel;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetKernelProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetModuleProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Module);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetDebugInfo                             = loader::zetModuleGetDebugInfo;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.Module;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetModuleProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Debug table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetDebugProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Debug);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnAttach                                   = loader::zetDebugAttach;
            pDdiTable->pfnDetach                                   = loader::zetDebugDetach;
            pDdiTable->pfnReadEvent                                = loader::zetDebugReadEvent;
            pDdiTable->pfnAcknowledgeEvent                         = loader::zetDebugAcknowledgeEvent;
            pDdiTable->pfnInterrupt                                = loader::zetDebugInterrupt;
            pDdiTable->pfnResume                                   = loader::zetDebugResume;
            pDdiTable->pfnReadMemory                               = loader::zetDebugReadMemory;
            pDdiTable->pfnWriteMemory                              = loader::zetDebugWriteMemory;
            pDdiTable->pfnGetRegisterSetProperties                 = loader::zetDebugGetRegisterSetProperties;
            pDdiTable->pfnReadRegisters                            = loader::zetDebugReadRegisters;
            pDdiTable->pfnWriteRegisters                           = loader::zetDebugWriteRegisters;
            pDdiTable->pfnGetThreadRegisterSetProperties           = loader::zetDebugGetThreadRegisterSetProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.Debug;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetDebugProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Metric);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zetMetricGet;
            pDdiTable->pfnGetProperties                            = loader::zetMetricGetProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.Metric;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricGroupProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricGroup);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zetMetricGroupGet;
            pDdiTable->pfnGetProperties                            = loader::zetMetricGroupGetProperties;
            pDdiTable->pfnCalculateMetricValues                    = loader::zetMetricGroupCalculateMetricValues;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.MetricGroup;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricGroupProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroupExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricGroupExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricGroupExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zet.MetricGroupExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCalculateMultipleMetricValuesExp         = loader::zetMetricGroupCalculateMultipleMetricValuesExp;
            pDdiTable->pfnGetGlobalTimestampsExp                   = loader::zetMetricGroupGetGlobalTimestampsExp;
            pDdiTable->pfnGetExportDataExp                         = loader::zetMetricGroupGetExportDataExp;
            pDdiTable->pfnCalculateMetricExportDataExp             = loader::zetMetricGroupCalculateMetricExportDataExp;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.MetricGroupExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricGroupExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricGroupExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricQueryProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricQuery);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zetMetricQueryCreate;
            pDdiTable->pfnDestroy                                  = loader::zetMetricQueryDestroy;
            pDdiTable->pfnReset                                    = loader::zetMetricQueryReset;
            pDdiTable->pfnGetData                                  = loader::zetMetricQueryGetData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.MetricQuery;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricQueryProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricQueryPoolProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricQueryPool);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zetMetricQueryPoolCreate;
            pDdiTable->pfnDestroy                                  = loader::zetMetricQueryPoolDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.MetricQueryPool;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricQueryPoolProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricStreamer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricStreamerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_streamer_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricStreamerProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricStreamerProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricStreamer);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnOpen                                     = loader::zetMetricStreamerOpen;
            pDdiTable->pfnClose                                    = loader::zetMetricStreamerClose;
            pDdiTable->pfnReadData                                 = loader::zetMetricStreamerReadData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.MetricStreamer;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricStreamerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricStreamerProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's TracerExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetTracerExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->drivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetTracerExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetTracerExpProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.TracerExp);
        if(getTableResult == ZE_RESULT_SUCCESS) 
            atLeastOneDriverValid = true;
        else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->drivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zetTracerExpCreate;
            pDdiTable->pfnDestroy                                  = loader::zetTracerExpDestroy;
            pDdiTable->pfnSetPrologues                             = loader::zetTracerExpSetPrologues;
            pDdiTable->pfnSetEpilogues                             = loader::zetTracerExpSetEpilogues;
            pDdiTable->pfnSetEnabled                               = loader::zetTracerExpSetEnabled;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->drivers.front().dditable.zet.TracerExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetTracerExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetTracerExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
