/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
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
                context->zet_debug_session_factory.getInstance( *phDebug, dditable ) );
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
        context->zet_debug_session_factory.release( hDebug );

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
                                                        ///< equal to the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
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
                                                        ///< or equal to the `count` member of ::zet_debug_regset_properties_t for
                                                        ///< the type
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
                    context->zet_metric_group_factory.getInstance( phMetricGroups[ i ], dditable ) );
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
                    context->zet_metric_factory.getInstance( phMetrics[ i ], dditable ) );
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
                context->zet_metric_streamer_factory.getInstance( *phMetricStreamer, dditable ) );
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
        context->zet_metric_streamer_factory.release( hMetricStreamer );

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
                context->zet_metric_query_pool_factory.getInstance( *phMetricQueryPool, dditable ) );
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
        context->zet_metric_query_pool_factory.release( hMetricQueryPool );

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
                context->zet_metric_query_factory.getInstance( *phMetricQuery, dditable ) );
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
        context->zet_metric_query_factory.release( hMetricQuery );

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

        // convert loader handles to driver handles
        auto phWaitEventsLocal = new ze_event_handle_t [numWaitEvents];
        for( size_t i = 0; ( nullptr != phWaitEvents ) && ( i < numWaitEvents ); ++i )
            phWaitEventsLocal[ i ] = reinterpret_cast<ze_event_object_t*>( phWaitEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEventsLocal );
        delete []phWaitEventsLocal;

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
                context->zet_tracer_exp_factory.getInstance( *phTracer, dditable ) );
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
        context->zet_tracer_exp_factory.release( hTracer );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnGetConcurrentMetricGroupsExp = dditable->zet.DeviceExp.pfnGetConcurrentMetricGroupsExp;
        if( nullptr == pfnGetConcurrentMetricGroupsExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetConcurrentMetricGroupsExp( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_context_object_t*>( hContext )->dditable;
        auto pfnCreateExp = dditable->zet.MetricTracerExp.pfnCreateExp;
        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hContext = reinterpret_cast<zet_context_object_t*>( hContext )->handle;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // convert loader handles to driver handles
        auto phMetricGroupsLocal = new zet_metric_group_handle_t [metricGroupCount ];
        for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < metricGroupCount  ); ++i )
            phMetricGroupsLocal[ i ] = reinterpret_cast<zet_metric_group_object_t*>( phMetricGroups[ i ] )->handle;

        // convert loader handle to driver handle
        hNotificationEvent = ( hNotificationEvent ) ? reinterpret_cast<ze_event_object_t*>( hNotificationEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnCreateExp( hContext, hDevice, metricGroupCount, phMetricGroupsLocal, desc, hNotificationEvent, phMetricTracer );
        delete []phMetricGroupsLocal;

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phMetricTracer = reinterpret_cast<zet_metric_tracer_exp_handle_t>(
                context->zet_metric_tracer_exp_factory.getInstance( *phMetricTracer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->dditable;
        auto pfnDestroyExp = dditable->zet.MetricTracerExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnDestroyExp( hMetricTracer );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->dditable;
        auto pfnEnableExp = dditable->zet.MetricTracerExp.pfnEnableExp;
        if( nullptr == pfnEnableExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnEnableExp( hMetricTracer, synchronous );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->dditable;
        auto pfnDisableExp = dditable->zet.MetricTracerExp.pfnDisableExp;
        if( nullptr == pfnDisableExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnDisableExp( hMetricTracer, synchronous );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->dditable;
        auto pfnReadDataExp = dditable->zet.MetricTracerExp.pfnReadDataExp;
        if( nullptr == pfnReadDataExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnReadDataExp( hMetricTracer, pRawDataSize, pRawData );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->dditable;
        auto pfnCreateExp = dditable->zet.MetricDecoderExp.pfnCreateExp;
        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_exp_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnCreateExp( hMetricTracer, phMetricDecoder );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phMetricDecoder = reinterpret_cast<zet_metric_decoder_exp_handle_t>(
                context->zet_metric_decoder_exp_factory.getInstance( *phMetricDecoder, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_decoder_exp_object_t*>( phMetricDecoder )->dditable;
        auto pfnDestroyExp = dditable->zet.MetricDecoderExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        phMetricDecoder = reinterpret_cast<zet_metric_decoder_exp_object_t*>( phMetricDecoder )->handle;

        // forward to device-driver
        result = pfnDestroyExp( phMetricDecoder );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_decoder_exp_object_t*>( hMetricDecoder )->dditable;
        auto pfnGetDecodableMetricsExp = dditable->zet.MetricDecoderExp.pfnGetDecodableMetricsExp;
        if( nullptr == pfnGetDecodableMetricsExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricDecoder = reinterpret_cast<zet_metric_decoder_exp_object_t*>( hMetricDecoder )->handle;

        // forward to device-driver
        result = pfnGetDecodableMetricsExp( hMetricDecoder, pCount, phMetrics );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetrics ) && ( i < *pCount ); ++i )
                phMetrics[ i ] = reinterpret_cast<zet_metric_handle_t>(
                    context->zet_metric_factory.getInstance( phMetrics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_decoder_exp_object_t*>( phMetricDecoder )->dditable;
        auto pfnDecodeExp = dditable->zet.MetricTracerExp.pfnDecodeExp;
        if( nullptr == pfnDecodeExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        phMetricDecoder = reinterpret_cast<zet_metric_decoder_exp_object_t*>( phMetricDecoder )->handle;

        // convert loader handles to driver handles
        auto phMetricsLocal = new zet_metric_handle_t [metricsCount];
        for( size_t i = 0; ( nullptr != phMetrics ) && ( i < metricsCount ); ++i )
            phMetricsLocal[ i ] = reinterpret_cast<zet_metric_object_t*>( phMetrics[ i ] )->handle;

        // forward to device-driver
        result = pfnDecodeExp( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetricsLocal, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries );
        delete []phMetricsLocal;

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMarkerExp
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMarkerExp(
        zet_command_list_handle_t hCommandList,         ///< [in] handle to the command list
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle to the marker metric group.
                                                        ///< ::zet_metric_group_type_exp_flags_t could be used to check whether
                                                        ///< marker is supoported by the metric group.
        uint32_t value                                  ///< [in] marker value
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMarkerExp = dditable->zet.CommandListExp.pfnAppendMarkerExp;
        if( nullptr == pfnAppendMarkerExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnAppendMarkerExp( hCommandList, hMetricGroup, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceEnableMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceEnableMetricsExp(
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be enabled.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnEnableMetricsExp = dditable->zet.DeviceExp.pfnEnableMetricsExp;
        if( nullptr == pfnEnableMetricsExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnableMetricsExp( hDevice );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceDisableMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceDisableMetricsExp(
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be disabled
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnDisableMetricsExp = dditable->zet.DeviceExp.pfnDisableMetricsExp;
        if( nullptr == pfnDisableMetricsExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnDisableMetricsExp( hDevice );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnGetExp = dditable->zet.MetricProgrammableExp.pfnGetExp;
        if( nullptr == pfnGetExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetExp( hDevice, pCount, phMetricProgrammables );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetricProgrammables ) && ( i < *pCount ); ++i )
                phMetricProgrammables[ i ] = reinterpret_cast<zet_metric_programmable_exp_handle_t>(
                    context->zet_metric_programmable_exp_factory.getInstance( phMetricProgrammables[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->dditable;
        auto pfnGetPropertiesExp = dditable->zet.MetricProgrammableExp.pfnGetPropertiesExp;
        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricProgrammable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->handle;

        // forward to device-driver
        result = pfnGetPropertiesExp( hMetricProgrammable, pProperties );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->dditable;
        auto pfnGetParamInfoExp = dditable->zet.MetricProgrammableExp.pfnGetParamInfoExp;
        if( nullptr == pfnGetParamInfoExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricProgrammable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->handle;

        // forward to device-driver
        result = pfnGetParamInfoExp( hMetricProgrammable, pParameterCount, pParameterInfo );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->dditable;
        auto pfnGetParamValueInfoExp = dditable->zet.MetricProgrammableExp.pfnGetParamValueInfoExp;
        if( nullptr == pfnGetParamValueInfoExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricProgrammable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->handle;

        // forward to device-driver
        result = pfnGetParamValueInfoExp( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->dditable;
        auto pfnCreateFromProgrammableExp2 = dditable->zet.MetricExp.pfnCreateFromProgrammableExp2;
        if( nullptr == pfnCreateFromProgrammableExp2 )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricProgrammable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->handle;

        // forward to device-driver
        result = pfnCreateFromProgrammableExp2( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetricHandles ) && ( i < *pMetricHandleCount ); ++i )
                phMetricHandles[ i ] = reinterpret_cast<zet_metric_handle_t>(
                    context->zet_metric_factory.getInstance( phMetricHandles[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->dditable;
        auto pfnCreateFromProgrammableExp = dditable->zet.MetricExp.pfnCreateFromProgrammableExp;
        if( nullptr == pfnCreateFromProgrammableExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricProgrammable = reinterpret_cast<zet_metric_programmable_exp_object_t*>( hMetricProgrammable )->handle;

        // forward to device-driver
        result = pfnCreateFromProgrammableExp( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetricHandles ) && ( i < *pMetricHandleCount ); ++i )
                phMetricHandles[ i ] = reinterpret_cast<zet_metric_handle_t>(
                    context->zet_metric_factory.getInstance( phMetricHandles[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnCreateMetricGroupsFromMetricsExp = dditable->zet.DeviceExp.pfnCreateMetricGroupsFromMetricsExp;
        if( nullptr == pfnCreateMetricGroupsFromMetricsExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreateMetricGroupsFromMetricsExp( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMetricGroup ) && ( i < *pMetricGroupCount ); ++i )
                phMetricGroup[ i ] = reinterpret_cast<zet_metric_group_handle_t>(
                    context->zet_metric_group_factory.getInstance( phMetricGroup[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnCreateExp = dditable->zet.MetricGroupExp.pfnCreateExp;
        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnCreateExp( hDevice, pName, pDescription, samplingType, phMetricGroup );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phMetricGroup = reinterpret_cast<zet_metric_group_handle_t>(
                context->zet_metric_group_factory.getInstance( *phMetricGroup, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnAddMetricExp = dditable->zet.MetricGroupExp.pfnAddMetricExp;
        if( nullptr == pfnAddMetricExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // convert loader handle to driver handle
        hMetric = reinterpret_cast<zet_metric_object_t*>( hMetric )->handle;

        // forward to device-driver
        result = pfnAddMetricExp( hMetricGroup, hMetric, pErrorStringSize, pErrorString );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnRemoveMetricExp = dditable->zet.MetricGroupExp.pfnRemoveMetricExp;
        if( nullptr == pfnRemoveMetricExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // convert loader handle to driver handle
        hMetric = reinterpret_cast<zet_metric_object_t*>( hMetric )->handle;

        // forward to device-driver
        result = pfnRemoveMetricExp( hMetricGroup, hMetric );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnCloseExp = dditable->zet.MetricGroupExp.pfnCloseExp;
        if( nullptr == pfnCloseExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCloseExp( hMetricGroup );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnDestroyExp = dditable->zet.MetricGroupExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnDestroyExp( hMetricGroup );

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_object_t*>( hMetric )->dditable;
        auto pfnDestroyExp = dditable->zet.MetricExp.pfnDestroyExp;
        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMetric = reinterpret_cast<zet_metric_object_t*>( hMetric )->handle;

        // forward to device-driver
        result = pfnDestroyExp( hMetric );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricDecoderExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricDecoderExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_decoder_exp_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricDecoderExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricDecoderExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zet.MetricDecoderExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnCreateExp                                = loader::zetMetricDecoderCreateExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnDestroyExp                               = loader::zetMetricDecoderDestroyExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnGetDecodableMetricsExp                   = loader::zetMetricDecoderGetDecodableMetricsExp;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricDecoderExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricDecoderExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricDecoderExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricProgrammableExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricProgrammableExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_programmable_exp_dditable_t* pDdiTable   ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricProgrammableExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricProgrammableExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zet.MetricProgrammableExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnGetExp                                   = loader::zetMetricProgrammableGetExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnGetPropertiesExp                         = loader::zetMetricProgrammableGetPropertiesExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnGetParamInfoExp                          = loader::zetMetricProgrammableGetParamInfoExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnGetParamValueInfoExp                     = loader::zetMetricProgrammableGetParamValueInfoExp;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricProgrammableExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricProgrammableExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricProgrammableExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracerExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricTracerExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_exp_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricTracerExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricTracerExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zet.MetricTracerExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnCreateExp                                = loader::zetMetricTracerCreateExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnDestroyExp                               = loader::zetMetricTracerDestroyExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnEnableExp                                = loader::zetMetricTracerEnableExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnDisableExp                               = loader::zetMetricTracerDisableExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnReadDataExp                              = loader::zetMetricTracerReadDataExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnDecodeExp                                = loader::zetMetricTracerDecodeExp;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricTracerExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricTracerExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricTracerExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetDeviceProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Device);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGetDebugProperties                       = loader::zetDeviceGetDebugProperties;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.Device;
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
/// @brief Exported function for filling application's DeviceExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetDeviceExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zet.DeviceExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnGetConcurrentMetricGroupsExp             = loader::zetDeviceGetConcurrentMetricGroupsExp;
            }
            if (version >= ZE_API_VERSION_1_10) {
                pDdiTable->pfnCreateMetricGroupsFromMetricsExp         = loader::zetDeviceCreateMetricGroupsFromMetricsExp;
            }
            if (version >= ZE_API_VERSION_1_13) {
                pDdiTable->pfnEnableMetricsExp                         = loader::zetDeviceEnableMetricsExp;
            }
            if (version >= ZE_API_VERSION_1_13) {
                pDdiTable->pfnDisableMetricsExp                        = loader::zetDeviceDisableMetricsExp;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.DeviceExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetDeviceExpProcAddrTable") );
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetContextProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetContextProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Context);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnActivateMetricGroups                     = loader::zetContextActivateMetricGroups;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.Context;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetCommandListProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.CommandList);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnAppendMetricStreamerMarker               = loader::zetCommandListAppendMetricStreamerMarker;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnAppendMetricQueryBegin                   = loader::zetCommandListAppendMetricQueryBegin;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnAppendMetricQueryEnd                     = loader::zetCommandListAppendMetricQueryEnd;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnAppendMetricMemoryBarrier                = loader::zetCommandListAppendMetricMemoryBarrier;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.CommandList;
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
/// @brief Exported function for filling application's CommandListExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetCommandListExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetCommandListExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetCommandListExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zet.CommandListExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_13) {
                pDdiTable->pfnAppendMarkerExp                          = loader::zetCommandListAppendMarkerExp;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.CommandListExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetCommandListExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetCommandListExpProcAddrTable") );
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetKernelProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Kernel);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGetProfileInfo                           = loader::zetKernelGetProfileInfo;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.Kernel;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetModuleProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Module);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGetDebugInfo                             = loader::zetModuleGetDebugInfo;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.Module;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetDebugProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Debug);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnAttach                                   = loader::zetDebugAttach;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnDetach                                   = loader::zetDebugDetach;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnReadEvent                                = loader::zetDebugReadEvent;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnAcknowledgeEvent                         = loader::zetDebugAcknowledgeEvent;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnInterrupt                                = loader::zetDebugInterrupt;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnResume                                   = loader::zetDebugResume;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnReadMemory                               = loader::zetDebugReadMemory;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnWriteMemory                              = loader::zetDebugWriteMemory;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGetRegisterSetProperties                 = loader::zetDebugGetRegisterSetProperties;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnReadRegisters                            = loader::zetDebugReadRegisters;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnWriteRegisters                           = loader::zetDebugWriteRegisters;
            }
            if (version >= ZE_API_VERSION_1_5) {
                pDdiTable->pfnGetThreadRegisterSetProperties           = loader::zetDebugGetThreadRegisterSetProperties;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.Debug;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.Metric);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGet                                      = loader::zetMetricGet;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGetProperties                            = loader::zetMetricGetProperties;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.Metric;
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
/// @brief Exported function for filling application's MetricExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zet.MetricExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_11) {
                pDdiTable->pfnCreateFromProgrammableExp2               = loader::zetMetricCreateFromProgrammableExp2;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnCreateFromProgrammableExp                = loader::zetMetricCreateFromProgrammableExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnDestroyExp                               = loader::zetMetricDestroyExp;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zetGetMetricExpProcAddrTable") );
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricGroupProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricGroup);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGet                                      = loader::zetMetricGroupGet;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGetProperties                            = loader::zetMetricGroupGetProperties;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnCalculateMetricValues                    = loader::zetMetricGroupCalculateMetricValues;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricGroup;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
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
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_2) {
                pDdiTable->pfnCalculateMultipleMetricValuesExp         = loader::zetMetricGroupCalculateMultipleMetricValuesExp;
            }
            if (version >= ZE_API_VERSION_1_5) {
                pDdiTable->pfnGetGlobalTimestampsExp                   = loader::zetMetricGroupGetGlobalTimestampsExp;
            }
            if (version >= ZE_API_VERSION_1_6) {
                pDdiTable->pfnGetExportDataExp                         = loader::zetMetricGroupGetExportDataExp;
            }
            if (version >= ZE_API_VERSION_1_6) {
                pDdiTable->pfnCalculateMetricExportDataExp             = loader::zetMetricGroupCalculateMetricExportDataExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnCreateExp                                = loader::zetMetricGroupCreateExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnAddMetricExp                             = loader::zetMetricGroupAddMetricExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnRemoveMetricExp                          = loader::zetMetricGroupRemoveMetricExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnCloseExp                                 = loader::zetMetricGroupCloseExp;
            }
            if (version >= ZE_API_VERSION_1_9) {
                pDdiTable->pfnDestroyExp                               = loader::zetMetricGroupDestroyExp;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricGroupExp;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricQueryProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricQuery);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnCreate                                   = loader::zetMetricQueryCreate;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnDestroy                                  = loader::zetMetricQueryDestroy;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnReset                                    = loader::zetMetricQueryReset;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnGetData                                  = loader::zetMetricQueryGetData;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricQuery;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricQueryPoolProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricQueryPool);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnCreate                                   = loader::zetMetricQueryPoolCreate;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnDestroy                                  = loader::zetMetricQueryPoolDestroy;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricQueryPool;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetMetricStreamerProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetMetricStreamerProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.MetricStreamer);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnOpen                                     = loader::zetMetricStreamerOpen;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnClose                                    = loader::zetMetricStreamerClose;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnReadData                                 = loader::zetMetricStreamerReadData;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.MetricStreamer;
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
    if( loader::context->zeDrivers.size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : loader::context->zeDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zet_pfnGetTracerExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zetGetTracerExpProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zet.TracerExp);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->zeDrivers.size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnCreate                                   = loader::zetTracerExpCreate;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnDestroy                                  = loader::zetTracerExpDestroy;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnSetPrologues                             = loader::zetTracerExpSetPrologues;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnSetEpilogues                             = loader::zetTracerExpSetEpilogues;
            }
            if (version >= ZE_API_VERSION_1_0) {
                pDdiTable->pfnSetEnabled                               = loader::zetTracerExpSetEnabled;
            }
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->zeDrivers.front().dditable.zet.TracerExp;
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
